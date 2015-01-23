 /* udp-broadcast-server.c:
  * udp broadcast server example 
  * Example Stock Index Broadcast:
  */
  #include <stdio.h>
  #include <unistd.h>
  #include <stdlib.h>
  #include <errno.h>
  #include <string.h>
  #include <time.h>
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
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
  char *host_part = strtok(inp_addr, ":" );
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
    printf("host *\n");
  }
  else if ( isdigit(*host_part) ) {
   /*
	* Numeric IP address:
	*/
    printf("host (%s)\n",host_part);
	
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
 
  #define MAXQ 4
 /*
  static struct {
	  char *index;
	  int start;
	  int volit;
	  int current;
  } quotes[] = {
	  { "DJIA", 1030330, 375 },
	  { "NASDAQ", 276175, 125 },
	  { "S&P 500", 128331, 50 },
	  { "TSE 300", 689572, 75 },
  };
 */
 /*
  * Initialize:
  */
 
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
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

void* boratcaser(void *arg); 
void startBoratcaser(){
    pthread_t brtid;
    int err = pthread_create(&brtid, NULL, &boratcaser,(void*) NULL);
}

#define BRINT 10
#include <sys/socket.h>

#include <arpa/inet.h>

#include <sys/types.h>

#include <sys/ioctl.h>

#include <string.h>

#include <net/if.h>

#include <errno.h>

#include <stdio.h>


#include <sys/socket.h>

#include <arpa/inet.h>

#include <sys/types.h>

#include <sys/ioctl.h>

#include <string.h>

#include <net/if.h>

#include <errno.h>

#include <stdio.h>

void   sockaddr2chars(struct sockaddr ad,char *s){
    sprintf(s,"%d.%d.%d.%d",(unsigned char)ad.sa_data[2],(unsigned char)ad.sa_data[3],(unsigned char)ad.sa_data[4],(unsigned char)ad.sa_data[5]);
}


int getIntr(char**ads){
int sock;                                                          // дескриптор сокета
int res=0;
struct sockaddr_in *in_addr;                             // структура интернет адреса (поля)
struct sockaddr_in *in2_addr;                             // структура интернет адреса (поля)

struct ifreq ifdata;                                            // структура - параметр
struct ifreq ifdata2;                                            // структура - параметр

struct if_nameindex*     ifNameIndex;                // структура интерфейсов и их индексов

sock = socket(AF_INET, SOCK_DGRAM, 0);     // открываем дескриптор сокета

if (sock < 0) {

printf("Не удалось открыть сокет, ошибка: %s\n", strerror(errno));

return -1;

}

ifNameIndex = if_nameindex();

if (ifNameIndex) {                                             // если удалось получить данные

while (ifNameIndex->if_index) {             // пока имеются данные

    memset(&ifdata, 0, sizeof(ifdata));                                           // очищаем структуру

    strncpy(ifdata.ifr_name, ifNameIndex->if_name, IFNAMSIZ);      // получаем имя следующего интерфейса

    // получаем IP адрес с помощью SIOCGIFADDR, одновременно проверяя результат
    if (ioctl(sock, SIOCGIFADDR, &ifdata) < 0) {

         printf("Не получить IP адрес для %s, ошибка: %s\n", ifdata.ifr_name, strerror(errno));

    //close(sock);
        ++ifNameIndex;                                   // переходим к следующему интерфейсу

        continue;
     }
    memset(&ifdata2, 0, sizeof(ifdata));                                           // очищаем структуру

    strncpy(ifdata2.ifr_name, ifNameIndex->if_name, IFNAMSIZ);      // получаем имя следующего интерфейса

    if (ioctl(sock, SIOCGIFMETRIC, &ifdata2) < 0) {

         printf("Не получить IP адрес для %s, ошибка: %s\n", ifdata2.ifr_name, strerror(errno));

    //close(sock);
        ++ifNameIndex;                                   // переходим к следующему интерфейсу

        continue;
     }

     
     

    // преобразовываем из массива байт в структуру sockaddr_in

    in_addr = (struct sockaddr_in *) &ifdata.ifr_addr;
    in2_addr = (struct sockaddr_in *) &ifdata.ifr_broadaddr;

    char bf[128];
    sockaddr2chars(ifdata2.ifr_netmask,bf);
    
    printf("Интерфейс %s (%s) индекес %i IP адрес: %s\n", ifdata.ifr_name,bf, ifNameIndex->if_index, inet_ntoa(in_addr->sin_addr));
    char*p;
    char s[128];
    char s2[128];
    int a,b,c;
    p=inet_ntoa(in_addr->sin_addr);
    strcpy(s,p);
    sscanf(s,"%d.%d.%d",&a,&b,&c);
    sprintf(s2,"%d.%d.%d.255:8002",a,b,c);
    p=(char*)malloc(strlen(s2)+1);
    strcpy(p,s2);
    if(res<BRINT){
        ads[res]=p;
        res++;    
    }   
    
        ++ifNameIndex;                                   // переходим к следующему интерфейсу


}

}

close(sock);

return res;

}

void takeItSlow(){
   struct timespec tw = {1,00};
   struct timespec tr;
   nanosleep (&tw, &tr);

}

void* boratcaser(void *arg) {
	  short x;    /* index of Stock Indexes */
	  double I0;  /* Initial index value */
	  double I;   /* Index value */
	  char bcbuf[512], *bp;/* Buffer and ptr */
	  int z;      /* Status return code */
	  int s[BRINT];      /* Socket */
//	  struct sockaddr_in adr_srvr;/* AF_INET */
	//  int len_srvr;               /* length */
	  struct sockaddr_in adr_bc[BRINT];  /* AF_INET */
	  int len_bc;                 /* length */
	  static int so_broadcast = TRUE;
	  //
	  char *bc_addr[BRINT];// = (char*)"*:8002";
	  len_bc = sizeof (adr_bc[0]);
	  int brint;
	  brint=getIntr(bc_addr);
	 int i;
	 for(i=0;i<brint;i++){	 
    	  z = mkaddr(
	    	  &(adr_bc[i]), /* Returned address */
	    	  &len_bc, /* Returned length */
	    	  bc_addr[i], /* Input string addr */
	    	  (char*)"udp"); /* UDP protocol */
	 
	      if ( z == -1 )
	    	displayError("Bad broadcast address");
	 
	 /*
	  * Create a UDP socket to use:
	  */
	      s[i] = socket(AF_INET,SOCK_DGRAM,0);
	      if ( s[i] == -1 )
	    	displayError("socket()");
	 
	 /*
	  * Allow broadcasts:
	  */
	      z = setsockopt(s[i],
					 SOL_SOCKET,
					 SO_BROADCAST,
					 &so_broadcast,
					 sizeof so_broadcast);
	 
	    if ( z == -1 )
		    displayError("setsockopt(SO_BROADCAST)");
	    
	  }    
      sprintf(bcbuf,"Follow me");

	  while(1) {
	    for(i=0;i<brint;i++){
		     z = sendto(s[i],
					 bcbuf,
					 strlen(bcbuf),
					 0,
					(struct sockaddr *)&(adr_bc[i]),
					len_bc); 
		 
		    if ( z == -1 )
			    displayError("sendto()");
          }
          takeItSlow();
		//  sleep(1);
		  
	  }
 }

