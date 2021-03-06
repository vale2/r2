 /* udp-broadcast-client.c
  * udp datagram client
  * Get datagram stock market quotes from UDP broadcast:
  * see below the step by step explanation
  */
  #include <stdio.h>
  #include <unistd.h>
  #include <stdlib.h>
  #include <errno.h>
  #include <string.h>
  #include <time.h>
  #include <signal.h>
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
//#include"func.c" 
/* mkaddr.c
  * The mkaddr() Subroutine using inet_aton
  * Make a socket address:
  */
  #include <stdio.h>
  #include <unistd.h>
  #include <stdlib.h>
  #include <errno.h>
  #include <ctype.h>
  #include <string.h>
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <netdb.h>
 
 /*
  * Create an AF_INET Address:
  *
  * ARGUMENTS:
  * 1. addr Ptr to area
  * where address is
  * to be placed.
  * 2. addrlen Ptr to int that
  * will hold the final
  * address length.
  * 3. str_addr The input string
  * format hostname, and
  * port.
  * 4. protocol The input string
  * indicating the
  * protocol being used.
  * NULL implies  tcp .
  * RETURNS:
  * 0 Success.
  * -1 Bad host part.
  * -2 Bad port part.
  *
  * NOTES:
  *  *  for the host portion of the
  * address implies INADDR_ANY.
  *
  *  *  for the port portion will
  * imply zero for the port (assign
  * a port number).
  *
  * EXAMPLES:
  *  www.lwn.net:80 
  *  localhost:telnet 
  *  *:21 
  *  *:* 
  *  ftp.redhat.com:ftp 
  *  sunsite.unc.edu 
  *  sunsite.unc.edu:* 
  */
  int mkaddr(void *addr,
             int *addrlen,
             char *str_addr,
             char *protocol) {
 
  char *inp_addr = strdup(str_addr);
  char *host_part = strtok(inp_addr, (char*)":" );
  char *port_part = strtok(NULL, "\n" );
  struct sockaddr_in *ap =
  (struct sockaddr_in *) addr;
  struct hostent *hp = NULL;
  struct servent *sp = NULL;
  char *cp;
  long lv;
 
 /*
  * Set input defaults:
  */
  if ( !host_part ) {
	host_part =  (char*)"*" ;
  }
  if ( !port_part ) {
	port_part =  (char*)"*" ;
  }
  if ( !protocol ) {
	protocol =  (char*)"tcp" ;
  }
 
 /*
  * Initialize the address structure:
  */
  memset(ap,0,*addrlen);
  ap->sin_family = AF_INET;
  ap->sin_port = 0;
  ap->sin_addr.s_addr = INADDR_ANY;
 
 /*
  * Fill in the host address:
  */
  if ( strcmp(host_part, "*" ) == 0 ) {
	; /* Leave as INADDR_ANY */
//    printf("host *\n");
  }
  else if ( isdigit(*host_part) ) {
   /*
	* Numeric IP address:
	*/
  //  printf("host (%s)\n",host_part);
	
	ap->sin_addr.s_addr =
	inet_addr(host_part);
	// if ( ap->sin_addr.s_addr == INADDR_NONE ) {
	if ( !inet_aton(host_part,&ap->sin_addr) ) {
           return -1;
	}
  } 
  else {
 /*
  * Assume a hostname:
  */
	hp = gethostbyname(host_part);
	if ( !hp ) {
		return -1;
	}
	if ( hp->h_addrtype != AF_INET ) {
		return -1;
	}
	ap->sin_addr = * (struct in_addr *)
					  hp->h_addr_list[0];
  }
 
 /*
  * Process an optional port #:
  */
  if ( !strcmp(port_part, "*" ) ) {
	/* Leave as wild (zero) */
  }
  else if ( isdigit(*port_part) ) {
 /*
  * Process numeric port #:
  */
	lv = strtol(port_part,&cp,10);
	if ( cp != NULL && *cp ) {
		return -2;
	}
	if ( lv < 0L || lv >= 32768 ) {
		return -2;
	}
	ap->sin_port = htons( (short)lv);
  } 
  else {
 /*
  * Lookup the service:
  */
	sp = getservbyname( port_part, protocol);
	if ( !sp ) {
		return -2;
	}
	ap->sin_port = (short) sp->s_port;
  }
 
 /* 
  * Return address length 
  */
  *addrlen = sizeof *ap;
 
  free(inp_addr);
  return 0;
  }

  #ifndef TRUE
  #define TRUE 1
  #define FALSE 0
  #endif

  extern int mkaddr(
                    void *addr,
                    int *addrlen,
                    char *str_addr,
                    char *protocol);

/*
 * This function reports the error and
 * exits back to the shell:
 */
 static void
 displayError(const char *on_what) {
     fputs(strerror(errno),stderr);
     fputs(": ",stderr);
     fputs(on_what,stderr);
     fputc('\n',stderr);
     exit(1);
}



void addServer(const char*name,int inport,int outport);
int broatListner(char *pattern);
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

int broatListnerFlag=0;
int one;
pthread_t brtid;

void* broatL(void *arg){

    broatListner((char*)"Follow me");    
        
}
void initBroatListner(){
    if(!broatListnerFlag){
        broatListnerFlag=1;
        
        
        int err = pthread_create(&brtid, NULL, &broatL,(void*) &one);
//        if (err != 0)
  //          fprintf(stderr,"\ncan't create thread 1.0 :[%s]", strerror(err));
    //    else
      //      fprintf(stderr,"\n Thread 1.0 created successfully\n");

        
        
        
    }

}

int broatListner(char *pattern) {
     int z;
     socklen_t x;
     struct sockaddr_in adr;  /* AF_INET */
     struct sockaddr adrFrom;  
     int len_inet;            /* length */
     socklen_t s;                   /* Socket */
     char dgram[512];         /* Recv buffer */
     static int so_reuseaddr = TRUE;
     static char
     *bc_addr = (char*)"*:8002";
     x=sizeof(adrFrom);
    /*
     * Use a server address from the command
     * line, if one has been provided.
     * Otherwise, this program will default
     * to using the arbitrary address
     * 127.0.0.:
     */

    /*
     * Create a UDP socket to use:
     */
     s = socket(AF_INET,SOCK_DGRAM,0);
     if ( s == -1 )
        displayError("socket()");

    /*
     * Form the broadcast address:
     */
     len_inet = sizeof adr;

     z = mkaddr(&adr,
                &len_inet,
                bc_addr,
                (char*)"udp");

     if ( z == -1 )
        displayError("Bad broadcast address");

    /*
     * Allow multiple listeners on the
     * broadcast address:
     */
     z = setsockopt(s,
                    SOL_SOCKET,
                    SO_REUSEADDR,
                    &so_reuseaddr,
                    sizeof so_reuseaddr);

     if ( z == -1 )
        displayError("setsockopt(SO_REUSEADDR)");

    /*
     * Bind our socket to the broadcast address:
     */
     z = bind(s,
             (struct sockaddr *)&adr,
             len_inet);

     if ( z == -1 )
        displayError("bind(2)");
     int i;
     for (;;) {
        /*
         * Wait for a broadcast message:
         */
         z = recvfrom(s,      /* Socket */
                      dgram,  /* Receiving buffer */
                      sizeof dgram,/* Max rcv buf size */
                      0,      /* Flags: no options */
                      (struct sockaddr *)&adrFrom, /* Addr */
                      &x);    /* Addr len, in & out */

         if ( z < 0 )
            displayError("recvfrom(2)"); /* else err */
         /*
        unsigned chort sa_family;   // address family, AF_xxx
    char           sa_data[14
         
         */
         
         //printf("RECV:%d [",(int)adrFrom.sa_family);
        // for(i=2;i<6;i++){
         //  printf("%d ",(unsigned char)adrFrom.sa_data[i]);
         
         
         
         //}
         //printf("]\n");
        
         //fwrite(dgram,z,1,stdout);
         //putchar('\n');

         int i;
         int flag;
         flag=1;
         for(i=0;i<z && pattern[i];i++){
            if(dgram[i]!=pattern[i]){
                flag=0;
            }
         }
         if(pattern[i]!=0){
            flag=0;
         }         
         
         if(flag){
            char ip[128];
            sprintf(ip,"%d.%d.%d.%d",(unsigned char)adrFrom.sa_data[2],(unsigned char)adrFrom.sa_data[3],(unsigned char)adrFrom.sa_data[4],(unsigned char)adrFrom.sa_data[5]);
            addServer(ip,8001,8000);
            addServer(ip,8000,8001);
         }
         
//         fflush(stdout);
     }

     return 0;
 }

