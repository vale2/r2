#include<stdio.h> 
#include<fcntl.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <math.h>

#define min(x,y)  (((x)>(y))?(y):(x))
/*

int inpipe,outpipe;
int dataready;
const char *inpipename="inpipe";
const char *outpipename="outpipe";

void signal_callback_handler(int signum){
   printf("Caught signal %d\n",signum);
   if(signum == 10){
        printf("User signal #10\n");
        dataready=1;        
        return;
   
   }
   // Cleanup and close up stuff here

   // Terminate program
   exit(signum);
}


int dataflag=0;
char pipedata[1024];
          
int pipedatasize=0;

void pipelisten(){
    SDL_Event event;
    int er;
    printf("Listing %s pipe\n",inpipename);
    while(1){
        while(dataflag){
            while(dataflag && SDL_PollEvent(&event)){
                switch (event.type) {
                    case SDL_USEREVENT:	if(event.user.type==6){ dataflag=0; }break;
                    default:SDL_PushEvent(&event); break;                
                }
                sleep(1);
             }
        }
        inpipe=open(inpipename,O_RDWR);
        if(inpipe < 0) {
            continue;
        }
        pipedatasize=read(inpipe,pipedata,1024);
        close(inpipe);
        printf("Readed %d controll bytes\n",pipedatasize);
        event.type=SDL_USEREVENT;
        event.user.type=7;
        event.user.code=pipedatasize; 
        event.user.data1=pipedata;  
        event.user.data1=NULL;            
        er=SDL_PushEvent(&event);
        printf("Sand sdl_event with code %d\n",er);       
        dataflag=1;        
    }
    



}

int pid=0;
int initPipes(){
    
   dataready=0;
   signal(SIGUSR1, signal_callback_handler);

    inpipe = mkfifo(inpipename,0666); 
    if(inpipe<0) {
      //return 1;
    }
    outpipe = mkfifo(outpipename,0666);

    if(outpipe<0) {
        //return 2;
    }
    printf("fork for pipe\n");
    pid = fork ();
    if (pid == (pid_t) 0) {
        //            child process
        
        pipelisten();
    }
    return 0;
}
int getData(char *p,int size){
   /* if(dataready){
        dataready=0;
        inpipe=open(inpipename,O_RDWR);
        if(inpipe < 0) {
            return -1;
        }
        read(inpipe,p,size);
        close(inpipe);
        
    }       
    return 0;*/
  /*  if(dataflag){
        memcpy(p,pipedata,min(size,pipedatasize));   
        if(size>=pipedatasize){
            dataflag=0;        
        }
        return pipedatasize;
    }
    
    
    return 0;
}


int putData(char *p,int size){
    outpipe=open(outpipename,O_RDWR);
    if(outpipe < 0) {
        return -1;
    }
    write(outpipe,p,size);
    close(outpipe);
    return 0;
}


int CgetData(char *p,int size){
    
    inpipe=open(outpipename,O_RDWR);
    if(inpipe < 0) {
        return -1;
    }
    read(inpipe,p,size);
    close(inpipe);
        
    return 0;
}

int CputData(char *p,int size){
    outpipe=open(inpipename,O_RDWR);
    if(outpipe < 0) {
        return -1;
    }
    write(outpipe,p,size);
    close(outpipe);
    return 0;
}


*/
