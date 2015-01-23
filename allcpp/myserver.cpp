#ifndef MYSERVER
#define MYSERVER

#include <fstream>  
#include <string.h>  
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
    #define printf netprintf
    #define fprintf netfprintf
int mySend(const char*s);
#include"netprintf.cpp"

#define SERVER_PORT  8000

#define TRUE             1
#define FALSE            0
   int    i, len, rc, on = 1;
   int    listen_sd, max_sd, new_sd;
   int    desc_ready, end_server = FALSE;
   int    close_conn;
   char   buffer[80];
   struct sockaddr_in   addr;
   struct timeval       timeout;
   fd_set        master_set, working_set;
char s[128];
int lastRecvSocet=-1;
int mySend(const char*s){
    if(lastRecvSocet!=-1){
        rc = send(lastRecvSocet, s, strlen(s), MSG_DONTWAIT);
        if (rc < 0){
            return -1;
        }
    }
    return 0;
}
int rendsmth=0;
void syntax(char*s){
    printf("SYNTAX:%s\n",s);
    rendsmth++;
}

int initServer (){
   /*************************************************************/
   /* Create an AF_INET stream socket to receive incoming       */
   /* connections on                                            */
   /*************************************************************/
   listen_sd = socket(AF_INET, SOCK_STREAM, 0);
   if (listen_sd < 0)
   {
      perror("socket() failed");
      return -1;    
   }

   /*************************************************************/
   /* Allow socket descriptor to be reuseable                   */
   /*************************************************************/
   rc = setsockopt(listen_sd, SOL_SOCKET,  SO_REUSEADDR,
                   (char *)&on, sizeof(on));
   if (rc < 0)
   {
      perror("setsockopt() failed");
      close(listen_sd);
      return -1;    
   }

   /*************************************************************/
   /* Set socket to be non-blocking.  All of the sockets for    */
   /* the incoming connections will also be non-blocking since  */
   /* they will inherit that state from the listening socket.   */
   /*************************************************************/
   rc = ioctl(listen_sd, FIONBIO, (char *)&on);
   if (rc < 0)
   {
      perror("ioctl() failed");
      close(listen_sd);
      return -1;    
   }

   /*************************************************************/
   /* Bind the socket                                           */
   /*************************************************************/
   memset(&addr, 0, sizeof(addr));
   addr.sin_family      = AF_INET;
   addr.sin_addr.s_addr = htonl(INADDR_ANY);
   addr.sin_port        = htons(SERVER_PORT);
   rc = bind(listen_sd,
             (struct sockaddr *)&addr, sizeof(addr));
   if (rc < 0)
   {
      perror("bind() failed");
      close(listen_sd);
      return -1;    
   }

   /*************************************************************/
   /* Set the listen back log                                   */
   /*************************************************************/
   rc = listen(listen_sd, 32);
   if (rc < 0)
   {
      perror("listen() failed");
      close(listen_sd);
      return -1;    
   }

   /*************************************************************/
   /* Initialize the master fd_set                              */
   /*************************************************************/
   FD_ZERO(&master_set);
   max_sd = listen_sd;
   FD_SET(listen_sd, &master_set);

   /*************************************************************/
   /* Initialize the timeval struct to 3 minutes.  If no        */
   /* activity after 3 minutes this program will end.           */
   /*************************************************************/
   timeout.tv_sec  = 0;//3 * 60;
   timeout.tv_usec = 10;

   /*************************************************************/
   /* Loop waiting for incoming connects or for incoming data   */
   /* on any of the connected sockets.                          */
   /*************************************************************/
    return 0;
}

#define RECVBUFSIZE 65536
char recvBuf[RECVBUFSIZE];
int recvBufCur;

int addNetData(char*buffer,int len){
int i;

for(i=0;i<len;i++){
        recvBuf[recvBufCur]=buffer[i];  
        if(recvBuf[recvBufCur]=='\n'){
            recvBuf[recvBufCur]=0;
            //syntax(recvBuf);
            syntaxControll(recvBuf);
            recvBufCur=0;
            continue;
        }
        recvBufCur++;
        if(recvBufCur>=RECVBUFSIZE-1){
            recvBufCur=0;
        }
    }

}

int  doServer(){
//     printf(".");
   
      /**********************************************************/
      /* Copy the master fd_set over to the working fd_set.     */
      /**********************************************************/
      memcpy(&working_set, &master_set, sizeof(master_set));

      /**********************************************************/
      /* Call select() and wait 5 minutes for it to complete.   */
      /**********************************************************/
     // printf("Waiting on select()...\n");
      rc = select(max_sd + 1, &working_set, NULL, NULL, &timeout);

      /**********************************************************/
      /* Check to see if the select call failed.                */
      /**********************************************************/
      if (rc < 0)
      {
         perror("  select() failed");
         return 1;
      }

      /**********************************************************/
      /* Check to see if the 5 minute time out expired.         */
      /**********************************************************/
      if (rc == 0)
      {
       //  printf("  select() timed out.  Continuing program.\n");
        return 0;
      }

      /**********************************************************/
      /* One or more descriptors are readable.  Need to         */
      /* determine which ones they are.                         */
      /**********************************************************/
      desc_ready = rc;
      for (i=0; i <= max_sd  &&  desc_ready > 0; ++i)
      {
         /*******************************************************/
         /* Check to see if this descriptor is ready            */
         /*******************************************************/
         if (FD_ISSET(i, &working_set))
         {
            /****************************************************/
            /* A descriptor was found that was readable - one   */
            /* less has to be looked for.  This is being done   */
            /* so that we can stop looking at the working set   */
            /* once we have found all of the descriptors that   */
            /* were ready.                                      */
            /****************************************************/
            desc_ready -= 1;

            /****************************************************/
            /* Check to see if this is the listening socket     */
            /****************************************************/
            if (i == listen_sd)
            {
         //      printf("  Listening socket is readable\n");
               /*************************************************/
               /* Accept all incoming connections that are      */
               /* queued up on the listening socket before we   */
               /* loop back and call select again.              */
               /*************************************************/
               do
               {
                  /**********************************************/
                  /* Accept each incoming connection.  If       */
                  /* accept fails with EWOULDBLOCK, then we     */
                  /* have accepted all of them.  Any other      */
                  /* failure on accept will cause us to end the */
                  /* server.                                    */
                  /**********************************************/
                  new_sd = accept(listen_sd, NULL, NULL);
                  if (new_sd < 0)
                  {
                     if (errno != EWOULDBLOCK)
                     {
                        perror("  accept() failed");
                        end_server = TRUE;
                     }
                     break;
                  }

                  /**********************************************/
                  /* Add the new incoming connection to the     */
                  /* master read set                            */
                  /**********************************************/
                  fprintf(stderr,"  New incoming connection - %d\n", new_sd);
                  FD_SET(new_sd, &master_set);
                  if (new_sd > max_sd)
                     max_sd = new_sd;

                  /**********************************************/
                  /* Loop back up and accept another incoming   */
                  /* connection                                 */
                  /**********************************************/
               } while (new_sd != -1);
            }

            /****************************************************/
            /* This is not the listening socket, therefore an   */
            /* existing connection must be readable             */
            /****************************************************/
            else
            {
             //  printf("  Descriptor %d is readable\n", i);
               close_conn = FALSE;
               /*************************************************/
               /* Receive all incoming data on this socket      */
               /* before we loop back and call select again.    */
               /*************************************************/
               do
               {
                  /**********************************************/
                  /* Receive data on this connection until the  */
                  /* recv fails with EWOULDBLOCK.  If any other */
                  /* failure occurs, we will close the          */
                  /* connection.                                */
                  /**********************************************/
                 // printf("RECV START\n");
                  rc = recv(i, buffer, sizeof(buffer),MSG_DONTWAIT);
                  //printf("RECV END\n");
                  if (rc < 0)
                  {
                     if (errno != EWOULDBLOCK)
                     {
                        perror("  recv() failed");
                        close_conn = TRUE;
                     }else{
                        lastRecvSocet=i;
                     }
                     break;
                  }

                  /**********************************************/
                  /* Check to see if the connection has been    */
                  /* closed by the client                       */
                  /**********************************************/
                  if (rc == 0)
                  {
                     fprintf(stderr,"  Connection closed\n");
                     close_conn = TRUE;
                     break;
                  }

                  /**********************************************/
                  /* Data was recevied                          */
                  /**********************************************/
                  len = rc;
                 /// fprintf(stderr,"  %d bytes received\n", len);
                  //memcpy(s,buffer,len);
                  //s[len+1]=0;
                  //syntax(s);
                  addNetData(buffer,len);
                  
                  
                  /**********************************************/
                  /* Echo the data back to the client           */
                  /**********************************************/
                /*  rc = send(i, buffer, len, MSG_DONTWAIT);
                  if (rc < 0)
                  {
                     perror("  send() failed");
                     close_conn = TRUE;
                     break;
                  }*/

               } while (TRUE);

               /*************************************************/
               /* If the close_conn flag was turned on, we need */
               /* to clean up this active connection.  This     */
               /* clean up process includes removing the        */
               /* descriptor from the master set and            */
               /* determining the new maximum descriptor value  */
               /* based on the bits that are still turned on in */
               /* the master set.                               */
               /*************************************************/
               if (close_conn)
               {
                  close(i);
                  FD_CLR(i, &master_set);
                  if (i == max_sd)
                  {
                     while (FD_ISSET(max_sd, &master_set) == FALSE)
                        max_sd -= 1;
                  }
               }
            } /* End of existing connection is readable */
         } /* End of if (FD_ISSET(i, &working_set)) */
      } /* End of loop through selectable descriptors */

   return 0;
   }
   
   /*************************************************************/
   /* Cleanup all of the sockets that are open                  */
   /*************************************************************/
 void closeServer(){
   for (i=0; i <= max_sd; ++i)
   {
      if (FD_ISSET(i, &master_set))
         close(i);
   }
}

void myDisconnect(){
   closeServer();
   initServer ();
}

/*
int main(){
    initServer ();
    while(!doServer()){
    //    printf("%s\n",s);
        if(rendsmth){
            mySend("smth\n");
            rendsmth--;
            
        }
    } 
    closeServer();
    return 0;
}*/


#endif