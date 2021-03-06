

extern int makeScreenShoot;
extern char* screenShoot;
extern int screenShootW;
extern int screenShootH;

int ssn=0;
int ssflag=0;
int sspos;
int sscur=0;
void startScreenShoot(int n){
    if(ssflag==0){
        ssflag=1;
        ssn=n;
        sscur=0;
    }
}
void resizeSS(){
    char*r;
    int nw,nh;
    nw=100;
    nh=screenShootH*nw/screenShootW;
    r=(char*)malloc(nw*nh*4);
    if(r==NULL){
        return;
    }
    for(int x=0;x<nw;x++)
       for(int y=0;y<nh;y++){
        int xx,yy;
        xx=x*screenShootW/nw;
        yy=y*screenShootH/nh;
        
         * ((unsigned*)(r+(x+y*nw)*4)) =          *((unsigned*) (screenShoot+(xx+yy*screenShootW)*4)); 

       
       }
    free(screenShoot);
    screenShoot=r;
    screenShootW=nw;
    screenShootH=nh;

}
extern int connected;
void doScreenShoot(){
    if(!connected){
        ssflag=0;
    }
    if(ssflag==1&&makeScreenShoot==0){
        makeScreenShoot=1;
        ssflag=2;
        fprintf(stderr,"ss: pass 1\n");
    }
    if(ssflag==2&&makeScreenShoot==0){
        ssflag=3;
        sspos=0;
        resizeSS();
        printf("screenShoot_init %d",sscur);
        printf(" %d",screenShootW);
        printf(" %d\n",screenShootH);
        fprintf(stderr,"ss: pass 2\n");
        sspos=0;
    }
    if(ssflag==3&&sspos<screenShootW*screenShootH){
        for(int i=0;i<100&&sspos<screenShootW*screenShootH;sspos++,i++){
             printf("screenShoot_pixel %d ",(int)sspos);
        fprintf(stdout,"%u\n",*((unsigned*)(screenShoot+sspos*4)));
        }
        
        fprintf(stderr,"ss: prog 3:%d\n",sspos);


    }else
    if(ssflag==3){

        sscur++;
        if(sscur<ssn){
            ssflag=1;        
         fprintf(stderr,"ss: pass 3 cont\n");
            
        }else{
            ssflag=0;
         fprintf(stderr,"ss: pass 3 fin\n");

        }
    }
}

char *ssd[16];
int ssdh[16];
int ssdw[16];
int curssd=-1;
void initDSS(int n,int w,int h){
    curssd=-1;
    if(n>=0&&n<16){
        if(ssd[n]!=NULL){
            free(ssd[n]);
        }
        ssd[n]=(char*)malloc(w*h*4);
        if(ssd[n]!=NULL){
            memset(ssd[n],0,w*h*4);
            curssd=n;
            ssdh[n]=h;
            ssdw[n]=w;
            fprintf(stderr,"Well init ss %d\n",n);
            return;
        }
    }
    fprintf(stderr,"Error initing ss %d",n);

}
void pixelDSS(unsigned  pos,int pixel){
    if(curssd!=-1 && ssd[curssd]!=NULL && pos>=0&&pos<ssdh[curssd]*ssdw[curssd]){
      //  fprintf(stderr,"set Pixel %u\n",pos);
        *((unsigned*)(ssd[curssd]+ pos*4))=pixel;
    
    }else{
        //  fprintf(stderr,"not set Pixel %u\n",pos);

    }
}
