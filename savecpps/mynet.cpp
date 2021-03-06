#ifndef MYNET
#define MYNET

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <SDL/SDL.h>
#include"timeutil.cpp"
//#include <android/log.h>
#include <errno.h>
int netstatus=0;


void perror2(const char*s1,const char*s2){
    char bf[132];
    sprintf(bf,"%s : %s\n",s1,s2);
    fwrite(bf,strlen(bf),1,stderr);


}

struct  myhost{
    char name[128];
    int inport,outport;
}hosts[1024];
volatile int nhost=0;
int lhost=0;
void myDisconnect();
void mySend(const char*s);
void addServer(const char*name,int inport,int outport){
    int i;
    if(nhost>1022)
        return;
    for(i=0;i<nhost;i++){
        if(!strcmp(hosts[i].name,name) && hosts[i].inport==inport&& hosts[i].outport==outport)
            return;
    }
    strcpy(hosts[nhost].name,name);
    hosts[nhost].inport=inport;
    hosts[nhost].outport=outport;
    char bf[32];
    sprintf(bf,"[%s:%d:%d]\n",name,inport,outport);
    fwrite(bf,strlen(bf),1,stderr);
    nhost++;
}


int inSoc=-1;
//int outSoc=-1;
extern Uint32  lastRecive;
#include"broatlistner.cpp"
int myConnect(){
    int sock=socket(PF_INET,SOCK_STREAM,0);
    struct sockaddr_in peerAddr;
    int ret;
    char*server=hosts[lhost].name;
    int inport=hosts[lhost].inport;
    int outport=hosts[lhost].outport;
    int valopt; 
    long arg; 
    fd_set myset; 
    struct timeval tv; 
    socklen_t lon; 
    
    initBroatListner();
    lhost++;
    lhost=lhost%nhost;
    
    peerAddr.sin_family=AF_INET;
    peerAddr.sin_port=htons(inport);
    peerAddr.sin_addr.s_addr=inet_addr(server);
   
    fcntl(sock, F_SETFL, fcntl(sock, F_GETFL) | O_NONBLOCK);
   
    ret=connect(sock,(struct sockaddr *)&peerAddr,sizeof(peerAddr));
    if (ret != 0) { 
         if (errno == EINPROGRESS) { 
            tv.tv_sec = 1; 
            tv.tv_usec = 0; 
            FD_ZERO(&myset); 
            FD_SET(sock, &myset); 
            if (select(sock+1, NULL, &myset, NULL, &tv) > 0) { 
               lon = sizeof(int); 
               getsockopt(sock, SOL_SOCKET, SO_ERROR, (void*)(&valopt), &lon); 
               if (valopt) { 
                  //fprintf(stderr, "Error in connection() %d - %s\n", valopt, strerror(valopt)); 
                  //exit(0); 
                  perror2("connect failed",server);
                  close(sock);
//                  outSoc=-1;
                  inSoc=-1;
                  return -1;
               } 
            } 
            else { 
                  perror2("connect failed",server);
                  close(sock);
  //                outSoc=-1;
                  inSoc=-1;
                  return -1;
            } 
         } 
         else { 
                  perror2("connect failed",server);
                  close(sock);
    //              outSoc=-1;
                  inSoc=-1;
                  return -1;
         } 
    } 
    
    
    
    inSoc=sock;
 /*
    sock=socket(PF_INET,SOCK_STREAM,0);
    fcntl(sock, F_SETFL, fcntl(sock, F_GETFL) | O_NONBLOCK);

    peerAddr.sin_family=AF_INET;
    peerAddr.sin_port=htons(outport);
    peerAddr.sin_addr.s_addr=inet_addr(server);
    ret=connect(sock,(struct sockaddr *)&peerAddr,sizeof(peerAddr));
    if (ret != 0) { 
         if (errno == EINPROGRESS) { 
            tv.tv_sec = 1; 
            tv.tv_usec = 0; 
            FD_ZERO(&myset); 
            FD_SET(sock, &myset); 
            if (select(sock+1, NULL, &myset, NULL, &tv) > 0) { 
               lon = sizeof(int); 
               getsockopt(sock, SOL_SOCKET, SO_ERROR, (void*)(&valopt), &lon); 
               if (valopt) { 
                  //fprintf(stderr, "Error in connection() %d - %s\n", valopt, strerror(valopt)); 
                  //exit(0); 
                  perror("connect failed");
                  close(sock);
                  outSoc=-1;
                 // inSoc=-1;
                  myDisconnect();
                  return -1;
               } 
            } 
            else { 
                  perror("connect failed");
                  close(sock);
                  outSoc=-1;
                  //inSoc=-1;
                  myDisconnect();
                  return -1;
            } 
         } 
         else { 
                  perror("connect failed");
                  close(sock);
                  outSoc=-1;
                  //inSoc=-1;
                  myDisconnect();
                  return -1;
         } 
    } 
        
//    fcntl(sock, F_SETFL, fcntl(sock, F_GETFL) | O_NONBLOCK);
    outSoc=sock;*/
    netstatus=1;
    lastRecive= GetTickCount();
    mySend("\nconnect\n");
    return 0;
}
extern  int connectflag;
void myDisconnect(){
    connectflag=0;
    if(inSoc!=-1){
        shutdown(inSoc,SHUT_RDWR);
        close(inSoc);
        inSoc=-1;
    }
//    if(outSoc!=-1){
  //      shutdown(outSoc,SHUT_RDWR);
    //    close(outSoc);
      //  outSoc=-1;
    //}
    netstatus=0;
}

int errCount=0;

void  mabyReconnect(){
    errCount++;
    if(errCount>10000){
          myDisconnect();
          
          myConnect();
          errCount=0;
    }
}
void   itIsOk(){
    errCount=0;

}

void mySend(const char*s){
     if(inSoc==-1){
//        mabyReconnect();
          myDisconnect();
          myConnect();

        return;
     }
     
     if(send(inSoc,s,strlen(s),0) == -1){
 //      mabyReconnect();
       
       //   myDisconnect();
       //   myConnect();
     }
    else{
         //  itIsOk();

    }
}

void mySyntax(char*s){
    char buf[2048];
    
    sprintf(buf,"recived:[%s]\n",s);
  //  mySend(buf);
    fwrite(buf,strlen(buf),1,stderr);

}


#define RECVBUFSIZE 65536
char recvBuf[RECVBUFSIZE];
int recvBufCur;
int syntaxControll(char*p);
int checkRecvData(){
    int r=0;
    int rv=0;
    //int errno;
     if(inSoc==-1){
        //mabyReconnect();
          myDisconnect();
          myConnect();
         return 0;
     }

    while(recvBufCur<RECVBUFSIZE-1 &&  (rv=recv(inSoc,recvBuf+recvBufCur,1,0)) >0){
        if(recvBuf[recvBufCur]=='\n'){
            recvBuf[recvBufCur]=0;
           // mySyntax(recvBuf);
            syntaxControll(recvBuf);
            recvBufCur=0;
            continue;
            r=1;
        }
        recvBufCur++;
    }
    if(recvBufCur>=RECVBUFSIZE-1){
        recvBufCur=0;
    }
 //   int errno;
   // errno=sock_errno();
    if(rv==-1 && errno!=EAGAIN && errno!=EWOULDBLOCK){
          //mabyReconnect();
          myDisconnect();
          myConnect();
    }else{
        //itIsOk();
    }
    return r;
}
int getnetc(){
    char a;
    int r;
    r=recv(inSoc,&a,1,0);
    if(r==0)
        return -1;
    return a;
}

#include"netprintf.cpp"




#endif
