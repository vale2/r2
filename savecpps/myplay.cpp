#include "portaudio.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>
//#define PLAY_SAMPLE_RATE 
 #define PLAY_SAMPLE_RATE (44100)
 #define SQPLSR (210)
 #define PLAY_FRAMES_PER_BUFFER (128)

// #define PLAY_FRAMES_PER_BUFFER (256)
//#define PLAYBUFLEN (1024)

//#define PLAYBUFLEN (2049)
//#define PLAYBUFLEN (4096)
#define PLAYBUFLEN (8192)

void hearZones();
#define PLAY_N 1024
long double panfr[PLAY_N]={0.5,.5,.5,.5,.5,.5,.5,.5,.5,0.5};

 long double pfr[PLAY_N]={0.0,.0,.0,.01,.05,.07,.08,.09,.095,1};
 long double pfr1[PLAY_N]={0.0,.0,.0,.01,.05,.07,.08,.09,.095,1};

 long double afr[PLAY_N]={0.0,.0,.0,.01,.05,.07,.08,.09,.095,1};
 long double afr1[PLAY_N]={0.0,.0,.0,.01,.05,.07,.08,.09,.095,1};


 long double fr[PLAY_N]={50,100,150,200,250,300,350,400,450,500};
 long double fr1[PLAY_N]={50,100,150,200,250,300,350,400,450,500};


 unsigned int frid[PLAY_N];


 long double ufr[PLAY_N]={0};
 long double dphfr[PLAY_N]={0};
 
 long double afr_tre[PLAY_N];
 long double fr_tre[PLAY_N];
 long double ufr_tre[PLAY_N];

 long double afr_vib[PLAY_N];
 long double fr_vib[PLAY_N];
 long double ufr_vib[PLAY_N];

 int locked=0;
pthread_t playtid;



 int play_n=10;
double simpleVol=10000;
double mysin(double a);

struct playme{
    short r[PLAYBUFLEN];
    short l[PLAYBUFLEN];
    unsigned int b,e;
    unsigned long skipped;
    int status; 

long double *panfr;
long double *afr;
long double *pfr;

long double *fr;
long double *ufr;

long double *afr_vib;
long double *fr_vib;
long double *ufr_vib;

long double *afr_tre;
long double *fr_tre;
long double *ufr_tre;


long double *dphfr;
double*simpleVol;

int *play_n;
int*locked;

}pldata;

void playSint2();
 static int playCallback( const void *inputBuffer, void *outputBuffer,
  unsigned long framesPerBuffer,
  const PaStreamCallbackTimeInfo* timeInfo,
  PaStreamCallbackFlags statusFlags,
  void *userData )
 {
  struct playme *data = (struct playme*)userData;
  short *wptr = (short*)outputBuffer;
  unsigned int i;
 
  (void) inputBuffer; /* Prevent unused variable warnings. */
  (void) timeInfo;
  (void) statusFlags;
  (void) userData;
  data->e=(data->e)%PLAYBUFLEN;
  if(data->status<=0){
    data->status=0;
    return paComplete;
    
  }
  int j;
  for(j=0;j<framesPerBuffer;j++){
    if(data->e!=data->b){
        *wptr=data->r[data->e];
        wptr++;
        *wptr=data->l[data->e];
        wptr++;
        (data->e)++;
        data->e=(data->e)%PLAYBUFLEN;
    }else{
        double vr,vl,v,v_vib,v_tre;
    vr=0;
    vl=0;
//    *(data->locked)=1;
        (data->skipped)++;
/*        
        
        
        
        
                int i;
//        double vr,vl,v,v_vib;
        vr=0;
        vl=0;
        for(i=0;i<*(data->play_n);i++){
            
            v=data->afr[i]*mysin(data->ufr[i]/SQPLSR*2.*M_PI);///fr[i];
            data->ufr[i]+=data->fr[i]/SQPLSR;
            while(data->ufr[i]>=SQPLSR)
                data->ufr[i]-=SQPLSR;

            data->ufr_vib[i]+=data->fr_vib[i]/SQPLSR;
            while(data->ufr_vib[i]>=SQPLSR)
                data->ufr_vib[i]-=SQPLSR;
                
            v_vib=data->afr_vib[i]*mysin(data->ufr_vib[i]/SQPLSR*2.*M_PI);
            
            v=*(data->simpleVol)*(v*(1+v_vib));
            vr+=v*panfr[i];
            vl+=v*(1-panfr[i]);


            vr+=v*data->panfr[i];
            vl+=v*(1-data->panfr[i]);
            
            
        }
        if(vr>32000||vr<-32000||vl>32000||vl<-32000){
            *data->simpleVol*=0.99;
            //svupdate=1;
       
       }
        if(vr>32767)
            vr=32767;
        if(vr<-32767)
            vr=-32767;
        if(vl<-32767)
            vl=-32767;
        if(vl>32767)
            vl=32767;
            
        
        
        
        
        
  */      
        
        
        
        
        *wptr=vr;
        wptr++;
        *wptr=vl;
        wptr++;

    }

  }
   *(data->locked)=0;
   return paContinue;
 }
 /*
void* playfunc(void *arg){
      while(1){
            
 
       }

}


*/
int initMyPlay(){
//   return -100;

  PaStreamParameters inputParameters,
  outputParameters;
  PaStream* stream;
  PaError err = paNoError;
  pldata.b=0;
  pldata.e=0;
  pldata.skipped=0;
  pldata.panfr=panfr;
pldata.afr=afr;
pldata.pfr=pfr;

pldata.fr=fr;
pldata.ufr=ufr;

pldata.afr_vib=afr_vib;
pldata.fr_vib=fr_vib;
pldata.ufr_vib=ufr_vib;

pldata.afr_vib=afr_tre;
pldata.fr_vib=fr_tre;
pldata.ufr_vib=ufr_tre;


pldata.dphfr=dphfr;
pldata.simpleVol=&simpleVol;
pldata.play_n=&play_n;
pldata.locked=&locked;
  
  
  
  outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
  if (outputParameters.device == paNoDevice) {
      fprintf(stderr,"Error: No default output device.\n");
      return -1;
  }
  outputParameters.channelCount = 2; /* stereo output */
  outputParameters.sampleFormat = paInt16;
  outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
  outputParameters.hostApiSpecificStreamInfo = NULL;
 
  fprintf(stderr,"\n=== Now playing back. ===\n"); 
  err = Pa_OpenStream(
  &stream,
  NULL, /* no input */
  &outputParameters,
  PLAY_SAMPLE_RATE,
  PLAY_FRAMES_PER_BUFFER,
  paClipOff, /* we won't output out of range samples so don't bother clipping them */
  playCallback,
  &pldata );
  
  err = Pa_StartStream( stream );
  
  
 // while( ( err = Pa_IsStreamActive( stream ) ) == 1 ) Pa_Sleep(100);
 
 // err = Pa_CloseStream( stream );
  /*       err = pthread_create(&playtid, NULL, &playfunc,NULL);
        if (err != 0)
            fprintf(stderr,"\ncan't create thread 1.0 :[%s]", strerror(err));
        else
            fprintf(stderr,"\n Thread 1.0 created successfully\n");

 */
 

}
void ssp2frafr(struct soundSpeq & ssp){
    play_n=ssp.n;
    int i;
    for(i=0;i<ssp.n;i++){
        afr[i]=ssp.amps[i]/ssp.maxAmps[i];
        fr[i]=ssp.freqs[i];
    
    }

}
void loadFreqs2frafr(double *freqs,double*amps,int n){
    play_n=n;
    int i;
    for(i=0;i<n;i++){
        afr[i]=amps[i]/65536.;
        fr[i]=freqs[i];
    }
    if(play_n>250)
        play_n=250;
}
#define MPDEEP 1000
double sinBuf[PLAY_SAMPLE_RATE];

double mpbuf[MPDEEP+1][2*MPDEEP+2];
double mp(double p,double v){
    return v;
    return mpbuf[(int)(p*MPDEEP)][(int)((v+1)*MPDEEP)];
}


int sinBufInited=0;
double __sign(double a){
    if(a>=0)
        return 1.;
    return -1;
}
void initRnd();
void initmysin(){
    int i;
    if(sinBufInited)
        return;
    sinBufInited=1;
    initRnd();
    for(i=0;i<PLAY_SAMPLE_RATE;i++)
        sinBuf[i]=sin(i*2*M_PI/PLAY_SAMPLE_RATE);
    int j;
    for(i=0;i<MPDEEP+1;i++){
        for(j=0;j<2*MPDEEP+2;j++){
            double v,p;
            v=j/(double)MPDEEP -1;
            p=i/(double)MPDEEP;
            
            mpbuf[i][j]=__sign(v)*pow(fabs(v),4*p);
        
        }
    }
}


double mysin(double a){
    return sinBuf[(unsigned int)(a/2./M_PI*PLAY_SAMPLE_RATE)];

}
double fl=100;
double lsv=0;
double maxSimpleVol=65536;
Uint32 lastCalcPlay=0;



double rndpool[100][20000];
int rndcur[100];
void initRnd(){
    int i,j;
    for(i=0;i<100;i++)
        for(j=0;j<20000;j++){
            rndpool[i][j]=1.+i/100.* (  pow( (rand()%1000)/1000.,1./(i*10.+1.)) *((rand()%2 -0.5)*2));
        
        }
}
double rnd(double r){
    int n;
    n=(int)(r*100.);
    double ret;
    ret= rndpool[n][rndcur[n]];
    rndcur[n]+=rand()%10;
    rndcur[n]%=20000;

//    fprintf(stderr,"r=%lf, ret=%lf\n",r,ret);

    return ret;
    
}

double uf=0;
void metod2(){
        double allafr,af;
        double vol,p,v;
        vol=fabs(getOpt("myplay_simpleVol"));
        int i,ii;
        allafr=0;
        for(i=0;i<play_n;i++){
           afr[i]=afr1[i];
           fr[i]=fr1[i];
            allafr+=afr[i];
        }
      while((pldata.b+1)%PLAYBUFLEN!=pldata.e){
          p=(rand()%65536)/65536.;
            ii=play_n-1;
            af=0;
            for(i=0;i<play_n;i++){
                af+=afr[i]/allafr;
               if(af>=p && ii==play_n-1){
                  ii=i;
               }
            }
          uf+=fr[ii]/SQPLSR;
          while(uf>=SQPLSR)
                uf-=SQPLSR;
                
        v=32000*(vol*mysin(uf/SQPLSR*2.*M_PI));
        pldata.r[pldata.b]=v;
        pldata.l[pldata.b]=v;
        pldata.b++;        
        pldata.b%=PLAYBUFLEN;
      
      }


}

void playMyPlay(){
 //return;
// if(maxSimpleVol<getOpt("maxSimpleVol")){
  //  maxSimpleVol=getOpt("maxSimpleVol");
// }
 if(getOpt("myplay")<0.5){
    if(pldata.status==1){
         pldata.status=-1;
         fprintf(stderr,"Colosing output sound seqence\n");
    }
    return;
 }else{
    if(pldata.status==-1){
         fprintf(stderr,"waiting output sound seqence colosing\n");

        return;
    }
    if(pldata.status==0){
         fprintf(stderr,"Starting output sound seqence\n");

        pldata.status=1;
        initMyPlay();    
    }
 
 }
 initmysin();
 if(GetTickCount()-lastCalcPlay>10){
    lastCalcPlay=GetTickCount();
    if(getOpt("myplay_mode")<0.5){
         hearZones();   
    }else{
         playSint2();
    }
 }
        int svupdate=0;
  int svBack=1;
  double nsv=getOpt("myplay_simpleVol");
  if(fabs(nsv-lsv)>0.001){
      lsv=nsv*.004+lsv*.996;
      svBack=0;
  }else{
    lsv=nsv;
  }
 
 
  simpleVol=maxSimpleVol*lsv;
  int loops=0;
  if(getOpt("myplay_metod")>0.5){
        metod2();
  
  }else{
      while((pldata.b+1)%PLAYBUFLEN!=pldata.e){
        while(locked);  
        if(loops>PLAYBUFLEN*2)
            break;
        loops++;
        unsigned int sk;
        sk=0;
        while(pldata.skipped){
          int i;
          for(i=0;i<play_n;i++){
              ufr[i]+=fr[i]/SQPLSR;
              while(ufr[i]>=SQPLSR)
                  ufr[i]-=SQPLSR;
            
          }
            pldata.skipped--;
            sk++;
        }
        if(sk){
            fprintf(stderr,"myPlay skipped:%d (play_n = %ld)\n",sk,play_n);
        
        }
        int i;
        double vr,vl,v,v_vib,v_tre;
        vr=0;
        vl=0;
        for(i=0;i<play_n;i++){
            
            v=afr[i]*mysin(ufr[i]/SQPLSR*2.*M_PI);///fr[i];
            
            ufr_tre[i]+=(fr_tre[i])/SQPLSR;
            while(ufr_tre[i]>=SQPLSR)
                ufr_tre[i]-=SQPLSR;

            v_tre=1+afr_tre[i]*mysin(ufr_tre[i]/SQPLSR*2.*M_PI);

            
            
            ufr[i]+=(fr[i]*v_tre*rnd(pfr[i]))/SQPLSR;
            
            afr[i]=afr[i]*0.999+afr1[i]*0.001;
            pfr[i]=pfr[i]*0.999+pfr1[i]*0.001;

            
            fr[i]=fr[i]*0.999+fr1[i]*0.001;
            
            
            
            while(ufr[i]>=SQPLSR)
                ufr[i]-=SQPLSR;
        
            ufr_vib[i]+=fr_vib[i]/SQPLSR;
           
            while(ufr_vib[i]>=SQPLSR)
                ufr_vib[i]-=SQPLSR;
                
            

            v_vib=afr_vib[i]*mysin(ufr_vib[i]/SQPLSR*2.*M_PI);

            v=simpleVol*(v*(1+v_vib));
            vr+=v*panfr[i];
            vl+=v*(1-panfr[i]);
            
            
        }
        if(vr>32000||vr<-32000||vl>32000||vl<-32000){
            simpleVol*=0.99;
            svupdate=1;
       
       }
        if(vr>32767)
            vr=32767;
        if(vr<-32767)
            vr=-32767;
        if(vl<-32767)
            vl=-32767;
        if(vl>32767)
            vl=32767;
            
        if(vr>16000||vr<-16000||vl>16000||vl<-16000)
            fl=100;
        
        pldata.r[pldata.b]=vr;
        pldata.l[pldata.b]=vl;
        pldata.b++;        
        pldata.b%=PLAYBUFLEN;
    }
  }
  fl*=0.99;
  if(fl<10 && simpleVol>0){
       simpleVol*=1.001;
  }
  if(simpleVol>maxSimpleVol){
    maxSimpleVol=simpleVol;
  }
  if(svBack){
    setOpt("myplay_simpleVol",simpleVol/maxSimpleVol);
  }
  // setOpt("maxSimpleVol",maxSimpleVol);
  
}
double v[24];
double k[24];
double msh[24];
int hearZinit=0;
double hearZtime=0;
double kr[25]={20, 100, 200, 300, 400, 510, 630, 770, 920, 1080, 1270, 1480, 1720, 2000, 2320, 2700, 3150, 3700, 4400, 5300, 6400, 7700, 9500, 12000, 15500};
/*
long double afr[PLAY_N]={0.0,.0,.0,.01,.05,.07,.08,.09,.095,1};
long double fr[PLAY_N]={50,100,150,200,250,300,350,400,450,500};
long double ufr[PLAY_N]={0};
int play_n=10;

*/

void vksh2frafr(double *v,double *k,double*sh,double*p){
    int i;
    double f1,f2;
    play_n=0;
    for(i=0;i<24;i++,play_n+=2){
        f1=kr[i];
        f2=kr[i+1];
        afr[play_n]=v[i];
        
        afr[play_n+1]=v[i]*k[i];
        fr[play_n]=f1;
        fr[play_n+1]=(f1+3*f2)/4*(1-k[i])+f2*k[i];
        panfr[play_n]=p[i];
        panfr[play_n+1]=p[i];
    }
    

}
int s2_frn;
long double s2_afr[PLAY_N]={0.0,.0,.0,.01,.05,.07,.08,.09,.095,1};
long double s2_afr0[PLAY_N]={0.0,.0,.0,.01,.05,.07,.08,.09,.095,1};

long double s2_pfr[PLAY_N]={0.0,.0,.0,.01,.05,.07,.08,.09,.095,1};
long double s2_pfr0[PLAY_N]={0.0,.0,.0,.01,.05,.07,.08,.09,.095,1};

long double s2_fr[PLAY_N]={50,100,150,200,250,300,350,400,450,500};
long double s2_fr0[PLAY_N]={50,100,150,200,250,300,350,400,450,500};

unsigned int s2_frid[PLAY_N];
long double s2_ufr[PLAY_N]={0};

long double s2_afr_vib[PLAY_N]={0.0,.0,.0,.01,.05,.07,.08,.09,.095,1};
long double s2_fr_vib[PLAY_N]={50,100,150,200,250,300,350,400,450,500};
long double s2_ufr_vib[PLAY_N]={0};

long double s2_afr_tre[PLAY_N]={0.0,.0,.0,.01,.05,.07,.08,.09,.095,1};
long double s2_fr_tre[PLAY_N]={50,100,150,200,250,300,350,400,450,500};
long double s2_ufr_tre[PLAY_N]={0};


long double s2_panfr[PLAY_N]={0.5,.5,.5,.5,.5,.5,.5,.5,.5,0.5};

double dekos(double kos,double w){
    double d=dis(w,1);
    //d*x=1-kos;
    double x;
    x=(1-kos)/d;
    if(x>1)
     x=1;
     return x;
}
void playSin2freq(double amp,double freq,double kos,double pan,double ww,double dd,double a_vib,double fr_vib,double a_tre,double fr_tre,double pfr,int nsint,int ngar,int noq){
    double dfr,f1,f2,w,a1,a2;
    if(s2_frn>=PLAY_N-1)
        return;
//    fprintf(stderr,"pfr=%lf\n",pfr);
    /*
    a1+a2=amp
    a2=a1*d;
    a1(1+d)=amp;
    a1=amp/(1+d);
    */
    double d;
/*  //  if(kos>0.99){
        a1=amp;
        f1=freq;
        a2=0;
        f2=freq+critWidth(freq)*0.03;
    //}else{
  */  
        d=dekos(kos,ww);
        a1=amp/(1+d);

        a2=a1*d;
        w=critWidth(freq);
   // dfr=w*0.25*(1-kos);//
        dfr=w*(ww);
        f1=(freq*(a1+a2)-dfr*a2)/(a1+a2);
        f2=f1+dfr;
     //}
//    (f1*a1+f1*a2+dfr*a2)=freq*(a1+a2);
    
    //(f1*a1+(f1+dfr)*a2)/(a1+a2)=freq;
    
    s2_afr[s2_frn]=a1;
    s2_pfr[s2_frn]=pfr;
    
    s2_fr[s2_frn]=f1;
    s2_panfr[s2_frn]=pan;
    s2_frid[s2_frn]=nsint+ 12*ngar +noq*12*16;
    
    s2_afr_vib[s2_frn]=a_vib;
    s2_fr_vib[s2_frn]=fr_vib;
 
    s2_afr_tre[s2_frn]=a_tre;
    s2_fr_tre[s2_frn]=fr_tre;

    if(a1>0.0001)
        s2_frn++;
//    return;

//    fprintf(stderr,"a2=%lf\n",a2);
//    if(a2>0.000001){
        s2_afr[s2_frn]=a2;///*kos;
        s2_pfr[s2_frn]=pfr;///*kos;
       
        s2_fr[s2_frn]=f2;
        s2_panfr[s2_frn]=pan;
        s2_afr_vib[s2_frn]=a_vib;
        s2_fr_vib[s2_frn]=fr_vib;
       
        s2_afr_tre[s2_frn]=a_tre;
        s2_fr_tre[s2_frn]=fr_tre;
        s2_frid[s2_frn]=nsint+ 12*ngar + noq*12*16 +2*12*16;
        if(a2>0.0001)

        s2_frn++;
      
  //  }
}

int play_n_bug=100;
void s2fr2fr(){
    int i,j;
    double w,reverb;
    double nearfreq;
    int upped[PLAY_N];
    reverb=calcOpt("myplay_reverb");
    nearfreq=calcOpt("myplay_nearfreq");
    for(int i=0;i<PLAY_N;i++)
        upped[i]=0;
    int ufr_used[PLAY_N];
    int used_newPlace[PLAY_N];
    
    for(i=0;i<play_n;i++){
        ufr_used[i]=0;
    } 
    
    for(i=0;i<s2_frn;i++){
        w=critWidth(s2_fr[i]);
/*        for(j=i+1;j<s2_frn;j++){
            if(fabs(s2_fr[i]-s2_fr[j])<0.03*w){
                s2_panfr[i]=(s2_panfr[i]*s2_afr[i]+s2_panfr[j]*s2_afr[j])/(s2_afr[i]+s2_afr[j]);
                s2_afr[i]+=s2_afr[j];

                s2_afr_vib[i]=(s2_afr_vib[i]+s2_afr_vib[j])/2;
                s2_fr_vib[i]=(s2_fr_vib[i]+s2_fr_vib[j])/2;
                
                s2_ufr_vib[i]=(s2_ufr_vib[i]+s2_ufr_vib[j])/2;
                
                
                s2_fr[j]=0;
                s2_afr[j]=0;            
                
            }        
        }*/
        int fou;
        double dfr,ddd;
        dfr=10000;
        //ufr_used[i];
        fou=-1;
        for(j=0;j<play_n;j++){
            ddd=fabs(s2_fr[i]-fr[j]);
            double dff;
            if(s2_fr[i]>fr[j])
                dff=fr[j]/s2_fr[i];
            else
                dff=s2_fr[i]/fr[j];
                
            if(s2_frid[i]== frid[j] && nearfreq<dff  && !ufr_used[j]){
                dfr=ddd;
                fou=j;                
            }
        }
        if(fou>=0){
            s2_ufr[i]=ufr[fou];
            s2_fr0[i]=fr[fou];
            s2_afr0[i]=afr[fou];
            s2_pfr0[i]=pfr[fou];
            
            s2_ufr_vib[i]=ufr_vib[fou];
            s2_ufr_tre[i]=ufr_tre[fou];

            ufr_used[fou]=1;
            used_newPlace[fou]=i;
        }else{
            s2_ufr[i]=0;
            s2_fr0[i]=s2_fr[i];
            s2_afr0[i]=0;

            s2_pfr0[i]=pfr[i];

            s2_ufr_vib[i]=0;
            s2_ufr_tre[i]=0;
        
        
        }
        
        
    }    
    
    //s2_frn;
    for(i=0;i<play_n;i++){
        if(ufr_used[i]==0 || s2_afr[used_newPlace[i]]<afr[i]*reverb){
            if(ufr_used[i]){
                s2_afr[used_newPlace[i]]=0;
                s2_afr0[used_newPlace[i]]=0;
                
            }
            s2_afr[s2_frn]=afr[i]*reverb;
            s2_afr0[s2_frn]=afr[i];
            s2_frid[s2_frn]=frid[i];
            s2_fr0[s2_frn]=fr[i];
            s2_fr[s2_frn]=fr[i];
            
            s2_ufr[s2_frn]=ufr[i];
            s2_panfr[s2_frn]=panfr[i];
            s2_frn++;
            if(s2_frn>=PLAY_N)
                break;
        }
    }
//    fprintf(stderr,"s2_frn:%ld\n",s2_frn);
  /* 
    for(i=0;i<s2_frn;i++){
        w=critWidth(s2_fr[i]);
        for(j=i+1;j<s2_frn;j++){
            if(fabs(s2_fr[i]-s2_fr[j])<0.05*w && fabs(s2_ufr[i]-s2_ufr[j])<0.01){
                s2_panfr[i]=(s2_panfr[i]*s2_afr[i]+s2_panfr[j]*s2_afr[j])/(s2_afr[i]+s2_afr[j]);
                s2_afr[i]+=s2_afr[j];
                s2_ufr[i]=s2_ufr[i]/2+s2_ufr[j]/2;
                
                
                s2_afr_vib[i]=s2_afr_vib[i]+s2_afr_vib[j];
                s2_fr_vib[i]=s2_fr_vib[i]+s2_fr_vib[j];
                s2_ufr_vib[i]=s2_ufr_vib[i]+s2_ufr_vib[j];

                
                s2_fr[j]=0;
                s2_afr[j]=0;            
                
            }        
        }
    }  
*/  /*
   if(s2_frn>play_n_bug){
      int s2_frn_non_zero;
      //s2_frn
      s2_frn_non_zero=0;
        for(i=0;i<s2_frn;i++){
          if(s2_afr[i]>0.001 && s2_fr[i]>16 && s2_fr[i]<15000){
            s2_frn_non_zero++;
          }
        }
        int nu;
        double minamp;
        while(s2_frn_non_zero>play_n_bug){
            nu=-1;
            minamp=100;
            for(i=0;i<s2_frn;i++){
              if(s2_afr[i]>0.001 && s2_fr[i]>16 && s2_fr[i]<15000){
                if(minamp>s2_afr[i]){
                    nu=i;
                    minamp=s2_afr[i];
                }
              }
            }
            if(nu>0){
                s2_frn_non_zero--;
                s2_afr[nu]=0;
            }else break;
        
        }
   
   }*/
   
   while(locked);
  // locked=1;
   play_n=0;
    for(i=0;i<s2_frn;i++){
        if((s2_afr[i]>0.001 || s2_afr0[i]>0.001) && ((s2_fr[i]>16 && s2_fr[i]<15000 )|| (s2_fr0[i]>16 && s2_fr0[i]<15000))){
            afr[play_n]=s2_afr0[i];
            afr1[play_n]=s2_afr[i];
            pfr1[play_n]=s2_pfr[i];
            
            frid[play_n]=s2_frid[i];
            fr[play_n]=s2_fr0[i];
            
            fr1[play_n]=s2_fr[i];
            
            
            panfr[play_n]=s2_panfr[i];
            ufr[play_n]=s2_ufr[i];
            
            afr_vib[play_n]=s2_afr_vib[i];
            fr_vib[play_n]=s2_fr_vib[i];
            ufr_vib[play_n]=s2_ufr_vib[i];

            afr_tre[play_n]=s2_afr_tre[i];
            fr_tre[play_n]=s2_fr_tre[i];
            ufr_tre[play_n]=s2_ufr_tre[i];
            
            while(ufr[i]>=SQPLSR)
                ufr[i]-=SQPLSR;

            play_n++;
            if(play_n>=PLAY_N)
                break;
        }
    }
//    locked=0;
    
}
#define SINT2GARS 16
void playSint2Voice(double *v,double*gars,double*gars_kos,int sint){
    double amp,pan,kos,bamp,camp,a_vib,fr_vib,a_tre,fr_tre,pfr;
    double bfreq,cfreq,pitch,chroma,w,d,ptchroma,dchroma;
    if(v[1]<0)
        return;
    amp=v[0];
//    pitch=pow(2,v[1]*log(15000)/log(2));//mel2gz(v[1]*3150*0.75);
      pitch=mel2gz(v[1]*gz2mel(15000));
    chroma=v[2];
    kos=v[3];
    pan=v[4];
    w=v[5];
    d=v[6];
    a_vib=v[7];
    fr_vib=v[8]*16;

    a_tre=v[9];
    fr_tre=v[10]*16;

    pfr=v[11];

    while(chroma>1)
        chroma-=1;
    while(chroma<0)
        chroma+=1;
    if(amp>1)
        amp=1;
    if(amp<0)
        amp=0;
    if(kos>1)
        kos=1;
    if(kos<0)
        kos=1;
    if(pan>1)
        pan=1;
    if(pan<0)
        pan=1;
   
    
    ptchroma=getChroma(pitch);
    dchroma=chroma-ptchroma;
    if(dchroma>0.5)
        dchroma=dchroma-1;
    if(dchroma<-0.5)
        dchroma=dchroma+1;

    bfreq=pitch*pow(2,dchroma);
    if(pitch>bfreq){
        cfreq=bfreq*2;
    }else{
        cfreq=bfreq;
        bfreq/=2;
    }
    double dd;
    dd=log(pitch/bfreq)/log(2.);
    bamp=amp*(1-dd);
    camp=amp*dd;
    for(int i=0;i<SINT2GARS;i++){
        if(bamp*gars[i]>0.0001)
           playSin2freq(bamp*gars[i],bfreq*(i+1),kos*gars_kos[i],pan,w,d,a_vib,fr_vib,a_tre,fr_tre,pfr,sint,i,0);
        if(camp*gars[i]>0.0001)
           playSin2freq(camp*gars[i],cfreq*(i+1),kos*gars_kos[i],pan,w,d,a_vib,fr_vib,a_tre,fr_tre,pfr,sint,i,0);
    }
    
//    fprintf(stderr,"%lf :: %lf* ",chroma,getChroma(bfreq));
  //  fprintf(stderr," %lf :: %lf\n ",pitch,bfreq);
    

}
void playSint2(){
    int optsN=13;
    const char *optss[]={"volume","pitchHeight","chromaHeight","kos","pan","width","density","vibrate_amp","vibrate_fr","tremolo_amp","tremolo_fr","sinpow","garMetod"};
    double optsv[optsN];
    double gar[SINT2GARS];
    double gar_kos[SINT2GARS];
    char s[100];
    int i,voice;
    s2_frn=0;
    for(voice=0;voice<12;voice++){
        for(i=0;i<optsN;i++){
            sprintf(s,"myplay_sint2_voce%d_%s",voice,optss[i]);
            optsv[i]=calcOpt(s);
            if(i==0&&optsv[i]<0.0001){
                break;
            }
        }
        
        if(optsv[0]>0.0001){
                
                if(optsv[12]<0.5){
                    for(i=0;i<SINT2GARS;i++){
                        sprintf(s,"myplay_sint2_voce%d_gar%d",voice,i);
                        gar[i]=calcOpt(s);
                    }
                    for(i=0;i<SINT2GARS;i++){
                        sprintf(s,"myplay_sint2_voce%d_gar_kos%d",voice,i);
                        gar_kos[i]=calcOpt(s);
                    }
                }else{
                    for(i=0;i<16;i++){
                       // sprintf(s,"myplay_sint2_voce%d_gar%d",voice,i);
                        sprintf(s,"myplay_sint2_voce%d_gar%d",voice,i);
                        gar[i]=calcOpt(s,i);
//                        gar[i]=koefsAr16[0][i];
                        
                        gar_kos[i]=1;
                        //calcOpt(s);
                    }
                }
            playSint2Voice(optsv,gar,gar_kos,voice);
        }
    
    }
    s2fr2fr();
}



double vv[24];
double kk[24];
double shsh[24];
double vvv[24];
double kkk[24];
double shshsh[24];
double p[24];
double pp[24];
double ppp[24];
 
void hearZones(){
    int i;
    hearZtime=GetTickCount()/100.;   

    if(!hearZinit){
        hearZinit=1;
        for(i=0;i<24;i++){
            p[i]=1./(rand()%1000+1);
            v[i]=1./(rand()%1000+1);
            k[i]=1./(rand()%1000+1);
            msh[i]=1./(rand()%1000+1);
        }
    }
    for(i=0;i<24;i++){
              vv[i]+=v[i];
              if(vv[i]>=2*M_PI)
                  vv[i]-=2*M_PI;
              vvv[i]=0.5+sin(vv[i])/2;

              pp[i]+=p[i];
              if(pp[i]>=2*M_PI)
                  pp[i]-=2*M_PI;
              ppp[i]=0.5+sin(pp[i])/2;

              kk[i]+=k[i];
              if(kk[i]>=2*M_PI)
                  kk[i]-=2*M_PI;
              kkk[i]=0.5+sin(kk[i])/2;
            
              shsh[i]+=msh[i];
              if(shsh[i]>=2*M_PI)
                  shsh[i]-=2*M_PI;
              shshsh[i]=0.5+sin(shsh[i])/2;
 
           if(i%2==0)
                vvv[i]=0;
 
    }
 //   if(rand()%100==3)
    for(i=0;i<24;i++){
            double d,a;
            d=(rand()%101 -50)/10.;
            a=1/v[i];
            if(a+d>0&&a+d<1001)
                v[i]=1/(a+d);
                


            d=(rand()%101 -50)/10.;
            a=1/k[i];
            if(a+d>0&&a+d<1001)
                k[i]=1/(a+d);


            d=(rand()%101 -50)/10.;
            a=1/msh[i];
            if(a+d>0&&a+d<1001)
                msh[i]=1/(a+d);
            d=(rand()%101 -50)/10.;
            a=1/p[i];
            if(a+d>0&&a+d<1001)
                p[i]=1/(a+d);

               
  }
    
    vksh2frafr(vvv,kkk,shshsh,ppp);

}
