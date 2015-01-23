#define IPSEND
#define REVERCERGB
#include"/home/7/r2/glrabbit/_controll.cpp"
int main( int argc, char* args[]){ 
/*    addServer("192.168.211.165",8000,8001);
    addServer("10.42.0.1",8000,8001);
    addServer("192.168.44.113",8000,8001);
    addServer("192.168.0.48",8000,8001);
    addServer("192.168.43.6956cvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv ",8000,8001);
*/
     FILE*f;
    char name[128];
    int a,b;
    f=fopen("hosts.lst","r");
    if(f!=NULL){
        while(!feof(f)){
            b=-1;
            fscanf(f,"%s %d %d",name,&a,&b);
//            a=8000;b=8001;
            fprintf(stderr,"server: <%s>,%d ",name,a);
            fprintf(stderr," %d\n",b);
            addServer(name,a,b);
        }
        fclose(f);
    }
     int r;
    while(myConnect());
    r= controll_main(argc,args);
    myDisconnect();
    return r;
}
