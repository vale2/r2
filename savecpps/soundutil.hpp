#ifndef SOUNDUILMOD
#define SOUNDUILMOD
#include"quickspeq.cpp"
#include"drawcurrent.cpp"
Uint32 GetTickCount(void);
//int keys[256];
int ALLFRAQ=0; 
int colorSeqVar=0;
double minColorSeqFreq=1.;
 #include <stdio.h>
 #include <stdlib.h>
   #ifdef RECORDSOUND

 #include "portaudio.h"
#endif
// #include "sdlutils.cpp"
 #include "fft.cpp"
// #include "timeutil.cpp"
 
 
 /* #define SAMPLE_RATE (17932) // Test failure to open with this value. */
 #define SAMPLE_RATE (44100)
 #define FRAMES_PER_BUFFER (512)
 #define NUM_SECONDS (1)

 /* #define DITHER_FLAG (paDitherOff) */
 #define DITHER_FLAG (0)
 
 #define WRITE_TO_FILE (0)
 
 /* Select sample format. */
 /*#if 1
 #define PA_SAMPLE_TYPE paFloat32
 typedef float SAMPLE;
 #define SAMPLE_SILENCE (0.0f)
 #define PRINTF_S_FORMAT "%.8f"
 #elif 1*/
 #define PA_SAMPLE_TYPE paInt16
 typedef short SAMPLE;
 #define SAMPLE_SILENCE (0)
 #define PRINTF_S_FORMAT "%d"
 /*#elif 0
 #define PA_SAMPLE_TYPE paInt8
 typedef char SAMPLE;
 #define SAMPLE_SILENCE (0)
 #define PRINTF_S_FORMAT "%d"
 #else
 #define PA_SAMPLE_TYPE paUInt8
 typedef unsigned char SAMPLE;
 #define SAMPLE_SILENCE (128)
 #define PRINTF_S_FORMAT "%d"
 #endif
 */
 
 //double notes[12]={523.25, 554.36 ,587.33, 622.25 ,659.26, 698.46, 739.99 ,783.99,830.61 ,880.00, 932.32 ,987.77};
 //int colors[12]={1,1,1,1,256,256,256,256,256*256,256*256,256*256,256*256}; //0 - blue, 1 - red, 2 - green
 
 //int colors[12]={1,1,1,1,256*256,256*256,256*256,256*256,256,256,256,256}; //0 - blue, 1 - red, 2 - green


  ////
//  #define N 8192
 // #define K 13
 // #define N 1024
  #define N 1024
  #define NK 10
  ShortComplex sound_arr[N];
  double sound_a[N];
  double sound_fi[N];
  double sound_freq[N];  



 
 typedef struct{
  int begin; /* Index into sample array. */
  int end;
  int len;
  char lostData;
  SAMPLE *buff1;
  SAMPLE *buff2;

 }  soundData;

struct nota{
    short int ok;
    signed char tone;
    int volume;
    double freq;
  //  double*freqs;
  //  double*amps;
   // int col;
};
struct nota getNota(int k);
 
 /* This routine will be called by the PortAudio engine when audio is needed.
 ** It may be called at interrupt level on some machines so don't do anything
 ** that could mess up the system like calling malloc() or free().
 */
 
 #define TONEEPS 0.001
 int detectTone(double freq){
    double c1=523.25;
    double ton;
    double d=554.36/523.25;
   int i;
    while(freq<c1){
        c1=c1/2.;
    }
    while(freq>c1*2){
        c1=c1*2.;
    }
   freq=freq/c1;
   for(i=0;freq/d-1>TONEEPS;freq=freq/d,i++);
   if(i>11)
    i=11;
   return i;
  
 }
 
 int detectOk(double freq){
    double c1=523.25;
  //  double ton;
//    double d=554.36/523.25;
   int i=1;
    while(freq<c1){
        c1=c1/2.;
        i--;
    }
    while(freq>c1*2){
        c1=c1*2.;
        i++;
    }
 
   return i;
  }
 
 
 /*
 int findColor(int o){
    double ak=1./512;
    double k,kk;
    int n,nn;
    double f;
    f=sound_freq[o];
    n=0;
    nn=0;
    kk=10;
    
    do{
        k=fabs(1.-f/(ak*notes[n]));
        if(k<kk){
            nn=n;
            kk=k;
        }
        n++;
        if(n>=12){
            n=0;
            ak=ak*2.;
        }
            
    
    
    }while(ak<64.);
    
    
 
    return nn;
 
 
 }*/
 int findDeep(double*a,int n,int w,double findEps,int minok,int lastvalue){
    int i,r,k,m,j,rr;
    double sum,max;
    max=0;
    r=lastvalue;
    r=-1;
    rr=0;
    for(i=n;i>0;i--){
        k=0;
        sum=0;
        if(getNota(i).ok>=minok){
            rr=i;
        
        }
        for(j=-w;j<=w;j++){
            if(i+j>=0&&i+j<n && getNota(i+j).ok>=minok && a[i+j]>findEps){
              m=w+1-abs(j);
              sum+=a[i+j]*m*m;
              k++;
            }
            sum/=k;
            if(max<sum){
                r=i;
                max=sum;
            
            }
        
        }
    
    }
    if(r<0){
        r=rr;
    }
     
    return r;
 }
 
 
 #ifdef RECORDSOUND
 
 
 static int recordCallback( const void *inputBuffer, void *outputBuffer,
  unsigned long framesPerBuffer,
  const PaStreamCallbackTimeInfo* timeInfo,
  PaStreamCallbackFlags statusFlags,
  void *userData ){
      soundData *data = (soundData*)userData;
      const SAMPLE *rptr = (const SAMPLE*)inputBuffer;
      SAMPLE *wptr1 = data->buff1 + data->end;
      SAMPLE *wptr2 = data->buff2 + data->end;

      long framesToCalc;
      long i;
      unsigned long framesLeft = data->len - data->end + data->begin-1;
 
      (void) outputBuffer; /* Prevent unused variable warnings. */
      (void) timeInfo;
      (void) statusFlags;
      (void) userData;

      if( framesLeft < framesPerBuffer ){
          framesToCalc = framesLeft;
          data->lostData=1;
          //printf("LOST!!!\n");
          //fflush(stdout);
      }else{
          framesToCalc = framesPerBuffer;
      }
 
      if( inputBuffer == NULL ){
          for( i=0; i<framesToCalc; i++ , data->end++){
              if( data->end == data->len){
                data->end =0;
                wptr1=data->buff1;
                wptr2=data->buff2;
                
              }
              *wptr1++ = SAMPLE_SILENCE;
              *wptr2++ = SAMPLE_SILENCE;
              
          }
      }else{
          for( i=0; i<framesToCalc; i++ ,data->end++){
              if( data->end == data->len){
                data->end =0;
                wptr1=data->buff1;
                wptr2=data->buff2;
              }
              *wptr1++ = *rptr++;
              *wptr2++ = *rptr++;
               
          }
      }

      return paContinue;
}
#endif
int findMedian(double*a,int n,double eps){
    double r,d;
    int i;
    r=0;d=0;
    for(i=0;i<n;i++){
        if(*a>eps){
            d=d+*a/1000.;
            r=r+*a*i/1000.;
        }
        a++; 
    }
    return r/d;
}

double MaxDanceFreq=20;

void  findNMax(double*a,double*freq,int n, int*out,int col,double eps){
    int i,j,r,flag,k;
    double max;    
    for(i=0;i<col;i++){
        max=-1;
        r=0;
        for(j=0;j<n;j++){
            if(max<a[j]&&a[j]>eps&&freq[j]<MaxDanceFreq){
                flag=1;
                for(k=0;k<i;k++){
                    if(out[k]==j){
                        flag=0;
                        break;
                    }
                }
                if(flag){
                    max=a[j];
                    r=j;
                }
                
            
            }
        }
        out[i]=r;    
        //printf("found:%d ",r);
    }
    //printf("\n");

}

/*



void findNMaxC(double*a,int n, int c,int*out,int col,double eps,int *cr1,int*cr2,int dist,double filter){
    int i,j,r,flag,k;
    double max;    
    for(i=0;i<col;i++){
        max=-1;
        r=-1;
        for(j=0;j<n;j++){
            if(sound_freq[j]>filter&&max<a[j]&&a[j]>eps && colors[findColor(j)]==c){
                flag=1;
                for(k=0;k<i;k++){
                    if(abs(out[k]-j)<dist){
                        flag=0;
                        break;
                    }
                }
                for(k=0;k<col;k++){
                    if(abs(cr1[k]-j)<dist||abs(cr2[k]-j)<dist){
                        flag=0;
                        break;
                    }
                }
                if(flag){
                    max=a[j];
                    r=j;
                }
                
            
            }
        }
        if(r>0.)
            out[i]=r;    
    }

}

*/
/*
void findNMaxC(double*a,int n, int c,int*out,int col,double eps,int *cr1,int*cr2,int dist){
    int i,j,r,flag,k;
    double max;    
    for(i=0;i<col;i++){
        max=-1;
        r=0;
        for(j=0;j<n;j++){
            if(max<a[j]&&a[j]>eps && colors[findColor(j)]==c){
                flag=1;
                for(k=0;k<i;k++){
                    if(abs(out[k]-j)<dist){
                        flag=0;
                        break;
                    }
                }
                for(k=0;k<col;k++){
                    if(abs(cr1[k]-j)<dist||abs(cr2[k]-j)<dist){
                        flag=0;
                        break;
                    }
                }
                if(flag){
                    max=a[j];
                    r=j;
                }
                
            
            }
        }
        out[i]=r;    
    }

}*/
 #include <cmath>
 double rx=0;
 double ry=0;
 double rxy=0;
 /*
void drawRithm(SDL_Surface*screen,double*a,double*fi,double*freq,int n){
    double r[2];
    double norm[2];
    int i;
    double t;
    r[0]=0;
    r[1]=0;
    norm[0]=0;
    norm[1]=0;
    t=GetTickCount()/1000.;
    for(i=0;i<n;i++){
        if(freq[i]>0.00001 && !std::isnan( a[i]) && !std::isnan( freq[i]) && !std::isnan( fi[i])){
            r[i%2]+=a[i]*sin(freq[i]*t+fi[i]);
            norm[i%2]+=a[i];
        }
    
    }
    if(fabs(norm[0])>0.0000001)
        r[0]=r[0]*100/norm[0];
    if(fabs(norm[1])>0.0000001)
        r[1]=r[1]*100/norm[1];
    
    //printf("rythm:%f\n",r);
    ry+=r[0];
    rx+=r[1];
    ry=ry*0.4;
    rx=rx*0.4;
    drawSqr(screen,screen->w-110+rx,screen->h/2+ry-10,screen->w-90+rx,screen->h/2+ry+10,WHITE);


}
*/
int addMelodyTorithm=0;
void calcRithm(double*a,double*fi,double*freq,double*la,double*lfi,double*lfreq,int n,int Tc,int T,double t0,double lt0){
    
    double r[3];
    double norm[3];
    char calced[3];
    char lcalced[3];
    double lr[3];
    double lnorm[3];

    int i;
    double t;
    for(i=0;i<3;i++){
        r[i]=0;
        norm[i]=0;
        lr[i]=0;
        lnorm[i]=0;
        calced[i]=0;
        lcalced[i]=0;
    }    
    
    t=GetTickCount()/1000.;
    for(i=0;i<n;i++){
        if(freq[i]>0.00001 && freq[i]<MaxDanceFreq && !std::isnan( a[i]) && !std::isnan( freq[i]) && !std::isnan( fi[i])){
            r[i%2]+=a[i]*sin(freq[i]*(t-t0)+fi[i]);
            norm[i%2]+=a[i];
            calced[i%2]=1;
            r[2]+=a[i]*sin(freq[i]*(t-t0)+fi[i]);
            norm[2]+=a[i];
            calced[2]=1;
        }
        if(lfreq[i]>0.00001 &&lfreq[i]<MaxDanceFreq && !std::isnan( la[i]) && !std::isnan( lfreq[i]) && !std::isnan( lfi[i])){
            lr[i%2]+=la[i]*sin(lfreq[i]*(t-lt0)+lfi[i]);
            lnorm[i%2]+=la[i];
            lcalced[i%2]=1;
            lr[2]+=la[i]*sin(lfreq[i]*(t-lt0)+lfi[i]);
            lnorm[2]+=la[i];
            lcalced[2]=1;
        }
    
    }
    for(i=0;i<3;i++){
        if(calced[i]){
            if(fabs(norm[i])>0.0000001){
                r[i]=r[i]*1000/norm[i];
            }
        }else{
            r[i]=-1000;
        }
        if(lcalced[i]){
            if(fabs(lnorm[i])>0.0000001)
                lr[i]=lr[i]*1000/lnorm[i];
        }else{
            lr[i]=-1000;
        }
    }
    //printf("rythm:%f\n",r);
    ry =(r[0]*Tc+lr[0]*(T-Tc))/T;
    rx =(r[1]*Tc+lr[1]*(T-Tc))/T;
    rxy=(r[2]*Tc+lr[2]*(T-Tc))/T;
    
   // ry=ry*0.4;
   // rx=rx*0.4;
    //drawSqr(screen,screen->w-110+rx,screen->h/2+ry-10,screen->w-90+rx,screen->h/2+ry+10,WHITE);


}


double findRithm(double * a,int n,double eps,double minfreq,double maxfreq){
    double r;
    int i;
    r=0;
    for(i=1;i<n;i++){
        if(sound_freq[i]>minfreq && sound_freq[i]>maxfreq)
            break;
        if(a[i]>eps && sound_freq[i]>minfreq && sound_freq[i]<maxfreq)
            r=r+a[i];
    
    }
    return r;


}


  int cur=0,target;
  int mcur=0,mtarget;
  #define RITHMLEN 256
  #define RITHMK 8
  #define BASSPASS 120.
  #define MELODYPASS 1500.
  #define ALLPASS 44000.
  
  #define RITHMEPS 1.
  //double rithm[RITHMLEN];
  ShortComplex rithm[RITHMLEN];
  double rithma[RITHMLEN];
  double rithmfi[RITHMLEN];
  double rithmfreq[RITHMLEN];
  
  #define KO 1
  int reds[KO];
  int greens[KO];
  int blues[KO];
  #define RO 500        
  int rithms[RO];
  double ra[RO];
  double rfi[RO];
  double rfreq[RO];
  double lra[RO];
  double lrfi[RO];
  double lrfreq[RO];
         
  
  
  
  
  int rithmp=0;
  
 
 #ifdef RECORDSOUND
 
  PaError err = paNoError;
  PaStreamParameters inputParameters;
  PaStream* stream;
  soundData data;
#endif
  int totalFrames;
  int numSamples;
  int numBytes;


int initSound(){
  int i;
  #ifdef RECORDSOUND
  data.len = totalFrames = NUM_SECONDS * SAMPLE_RATE; /* Record for a few seconds. */
  data.begin = 0;
  data.end = 0;
  data.lostData=0;
  numSamples = totalFrames;
  
  numBytes = numSamples * sizeof(SAMPLE);
  data.buff1 = (SAMPLE *) malloc( numBytes ); /* From now on, recordedSamples is initialised. */
  data.buff2 = (SAMPLE *) malloc( numBytes ); /* From now on, recordedSamples is initialised. */
  if( data.buff1 == NULL || data.buff2 == NULL ){
    printf("Could not allocate record array.\n");
    fflush(stdout);
    return -1;
  }

  for( i=0; i<numSamples; i++){ 
    data.buff1[i] = 0;
    data.buff2[i] = 0;

  }
 
  err = Pa_Initialize();
  if( err != paNoError ){
    return -2;
  
  } 
  inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
  if (inputParameters.device == paNoDevice) {
    fprintf(stderr,"Error: No default input device.\n");
    return -3;
  }
  inputParameters.channelCount = 2; 
  inputParameters.sampleFormat = PA_SAMPLE_TYPE;
 // inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency;
   inputParameters.suggestedLatency = 0.0001;
  inputParameters.hostApiSpecificStreamInfo = NULL;
   printf("lat:%f\n",inputParameters.suggestedLatency);
  /* Record some audio. -------------------------------------------- */
  err = Pa_OpenStream(&stream,&inputParameters, NULL, /* &outputParameters, */  SAMPLE_RATE,  FRAMES_PER_BUFFER,  paClipOff, /* we won't output out of range samples so don't bother clipping them */
  recordCallback,
  &data );
  if( err != paNoError ) {
    printf("Error while opening stream\n");
    return -4;
  
  }
 
  err = Pa_StartStream( stream );
  if( err != paNoError ){
      printf("Error while starting stream\n");
      return -5;
  }
//int x,y;
 // x=0;
 
  //int j;
 /* show1=(int*)malloc(screen->w*(sizeof(int)));
  show2=(int*)malloc(screen->w*(sizeof(int)));
  if(show1==NULL || show2==NULL){
    return -10;
  }*/
  
  
  ////
  
    #endif
    return 0;
}


#define NOTES 3
#define MAINNOTES 2
#define MAXMAINOK 3
#define MINMAINOK 0

struct nota notes[NOTES];
int foundNotes=0;
int Nmax= (N + 1) / 2;
int foundMainNotes=0;


struct nota getNota(int k){
    struct nota r;
    r.freq=sound_freq[k];
    r.volume=sound_a[k]*100.;
    if(r.volume>65535)
        r.volume=65535;
    r.ok=detectOk(r.freq);
    r.tone=detectTone(r.freq);
    
    return r;

}



int NoteTableOk=0;
double freqs[12][(N+1)/2];
double amps[12][(N+1)/2];
int facols[12];

void calcNoteTable(){
    if(NoteTableOk)
        return;
    NoteTableOk=1;
    /*for(int i=0;i<NOTES;i++){
        notes[i].freqs=(double*)malloc(sizeof(double)*Nmax);
        notes[i].amps=(double*)malloc(sizeof(double)*Nmax);
        if(notes[i].freqs==NULL || notes[i].amps==NULL){
            printf("MEMo\n");
            fflush(stdout);
        
        }
    }*/
    printf("MEMo ok!\n");
    fflush(stdout);

}



void showCollectedNotes(SDL_Surface*screen,struct nota n){
  int x;
  struct rgb c;
  Uint32 p;
  struct hsv_colour hsv_c; 
  struct rgb_colour rgb_c;
  double v;
  v=(n.volume)*2;
  if(v>65535){
    v=65535;
  }
//  x=n.freq/sound_freq[Nmax-1]*screen->w;
  hsv_c.v=0.99;
  hsv_c.h=n.tone/12.;
  hsv_c.s=v/65536.0;
  hsv2rgb(&hsv_c,&rgb_c);
  c=rgb_colour2rgb(&rgb_c);
  rgb2pixel(c.r,c.g,c.b,&p);

//  drawSqr(screen,x-3,screen->h/2-3,x+3,screen->h/2+3,p);
  
  x=n.tone*30;
  
  bar(screen,x,40,x+29,70,p);
  
  
    


}


void showNota(SDL_Surface*screen,struct nota n){
/*    n.volume;
    n.tone
    n.ak
    n.freq
  */
  int x;
  struct rgb c;
  Uint32 p;
  struct hsv_colour hsv_c; 
  struct rgb_colour rgb_c;
  double v;
  v=(n.volume);
  if(v>65535){
    v=65535;
  }
  x=n.freq/sound_freq[Nmax-1]*screen->w;
  hsv_c.v=0.99;
  hsv_c.h=n.tone/12.;
  hsv_c.s=v/65536.0;
  hsv2rgb(&hsv_c,&rgb_c);
  c=rgb_colour2rgb(&rgb_c);
  rgb2pixel(c.r,c.g,c.b,&p);

  drawSqr(screen,x-3,screen->h/2-3,x+3,screen->h/2+3,p);
  
  x=n.tone*30;
  
  bar(screen,x,0,x+29,30,p);
  
  
    
}
double noteCollector[12];
int noteBusy[12];

void findNotes(int volumeEps){
    int i,j,flag,k;
    struct nota n,m;
    ///Main notes;
    double max;
    calcNoteTable();
    for(i=0;i<12;i++){
        noteCollector[i]=0;
        noteBusy[i]=0;
    }    
    
    foundNotes=0;
    for(i=0;i<MAINNOTES;i++){
        m.volume=0;
        
        for(j=0;j<Nmax;j++){
            n=getNota(j);
            if(n.ok>MAXMAINOK)
                break;
            if(n.ok<MINMAINOK)
                continue;
            if(n.volume>m.volume && n.volume>volumeEps){
                flag=1;
                for(k=0;k<foundNotes;k++){
                    if(notes[k].tone==n.tone){
                        flag=0;
                        break;
                    }
                }
                if(flag){
                    m=n;
                }
                
            
            }
        
        }
        if(m.volume!=0){
          notes[foundNotes++]=m; 
          noteBusy[m.tone]=1;
         // printf("Nota %d: %d, %d:%d\n",foundNotes,m.ok,m.tone,m.volume);
        }   
    }
    foundMainNotes=foundNotes;
    ///Collector
    

    double allcol=0;
    for(j=0;j<Nmax;j++){
         n=getNota(j);
         if(n.ok<=MINMAINOK)
                continue;
        if(n.volume<=volumeEps)
            continue;
        allcol=allcol+sound_a[j];
        noteCollector[n.tone]=noteCollector[n.tone]+sound_a[j];
    }

    for(i=foundMainNotes;i<NOTES;i++){
        max=-1;
        for(j=0;j<12;j++){
            if(max<noteCollector[j] && !noteBusy[j] ){
                max=noteCollector[j];
                k=j;            
            }
        
        }
        if(max>allcol/11 && 100000*max/Nmax > volumeEps ){
           
           notes[foundNotes].tone=k;
           notes[foundNotes].volume=10000*max/Nmax;
           if(notes[foundNotes].volume>65535)
             notes[foundNotes].volume=65535;
           
         //  printf("Collected Nota %d: %d:%d\n",foundNotes,k,notes[foundNotes].volume);
           
           
           
           foundNotes++; 
           
           //printf("foundNotes:%d\n",foundNotes);
           // fflush(stdout);           
           noteBusy[k]=1;
        }
    }
           //printf("foundNotes:%d\n",foundNotes);
            //fflush(stdout);           
    
    
   // return;
    for(i=0;i<12;i++){
        facols[i]=0;
    }
     for(i=0;i<Nmax;i++){
        n=getNota(i);
        if(noteBusy[n.tone]!=-1 && n.volume>volumeEps){
            k=n.tone;
            freqs[k][facols[k]]=n.freq;
            amps[k][facols[k]]=n.volume/65536.;
            facols[k]++;
            //printf("col:%d\n",facols[k]);
            //fflush(stdout);
            
            
            
        }
        
        
        
    }
    
    
    
}



int sound_k=0;
double bassrithm=0.;
double allrithm=0.;
double melodyrithm=0;
int deepWidth=20;

int seqAccR[SEQLEN];
int seqAccG[SEQLEN];
int seqAccB[SEQLEN];

struct rgb fvc[N];
char lfvc[N];
char cfvc=1;

struct rgb freqValue2Color(int k){
       double value,sat,tone;
       Uint32 p;
       struct rgb c;
       struct hsv_colour hsv_c; 
       struct rgb_colour rgb_c;
       if(lfvc[k] == cfvc){
            return fvc[k];
       }
       value=sound_a[k]/7-20;//-50;
       sat=(detectOk(sound_freq[k])+30)*5;
       if(value<0.)
        value=0.;
       if(sat<0.)
        sat=0.;
        if(sat>99.)
            sat=99.;
       if(value>99.)
            value=99.;
       tone=detectTone(sound_freq[k]);
      
       hsv_c.v=value/100.;
       hsv_c.h=tone/12;
       hsv_c.s=sat/100.;
       hsv2rgb(&hsv_c,&rgb_c);
 
       c= rgb_colour2rgb(&rgb_c);
       lfvc[k]=cfvc;
       fvc[k]=c;
       

 
       return c;
}

void calcSoundColorSeqByAFCMixingGamma(double minFreq,double maxFreqm,double mixDist,double cvr,double cvg,double cvb){
    double r,g,b,a,lr,lg,lb,rr,gg,bb;
    struct rgb c;
    int k,i,n,ln,n0;
    ln=-1;
    n0=0;
    cfvc++;
    lr=0;lg=0;lb=0;
    for(k=0;k<Nmax;k++){
       if(sound_freq[k]*mixDist<minFreq)
            continue;
       r=0;g=0;b=0;a=0;
       for(i=k;sound_freq[i]>sound_freq[k]/mixDist && i>0;i--){
           c=freqValue2Color(i);
           r=r+((double)c.r)/sound_freq[i]*(sound_freq[i]-sound_freq[k]/mixDist);
           g=g+((double)c.g)/sound_freq[i]*(sound_freq[i]-sound_freq[k]/mixDist);
           b=b+((double)c.b)/sound_freq[i]*(sound_freq[i]-sound_freq[k]/mixDist);
           a=a+(sound_freq[i]-sound_freq[k]/mixDist)/sound_freq[i];
       
       }
       for(i=k+1;sound_freq[i]<sound_freq[k]*mixDist && i<Nmax;i++){
           c=freqValue2Color(i);
           r=r+((double)c.r)/sound_freq[i] *(sound_freq[k]*mixDist-sound_freq[i]);
           g=g+((double)c.g)/sound_freq[i]*(sound_freq[k]*mixDist-sound_freq[i]);
           b=b+((double)c.b)/sound_freq[i]*(sound_freq[k]*mixDist-sound_freq[i]);
           a=a+(sound_freq[k]*mixDist-sound_freq[i])/sound_freq[i] ;
       
       }
       r=r/a;
       g=g/a;
       b=b/a;
       //n=log(k)/log(Nmax)*SEQLEN;
       //n=k*SEQLEN/Nmax;
       n=log(k)/log(Nmax)*(SEQLEN);
       if(ln==-1){
        n0=n;
        ln=0;
        lr=r;
        lg=g;
        lb=b;
        continue;
       }else{
       // n=n-n0;
       }
       if(n==ln){
          lr=r/2+lr/2;
          lg=g/2+lg/2;
          lb=b/2+lb/2;
          
       
       }else{
           if(n-ln>6*5){
                n=ln+6*5;
            
            }
     
     
           for(i=ln;i<=n && i<SEQLEN;i++){
               rr=((r*(i-ln)   +  lr*(n-i))/(n-ln))*cvr;
               gg=((g*(i-ln)   +  lg*(n-i))/(n-ln))*cvg;
               bb=((b*(i-ln)   +  lb*(n-i))/(n-ln))*cvb;
               if(rr>255)
                rr=255;
               if(gg>255)
               gg=255;
               if(bb>255)
                bb=255;
               c.r=rr;
               c.g=gg;
               c.b=bb;
               
               colorSeq2Buf[i]=*((Uint32*)&c );
            }
           lr=r;
           lg=g;
           lb=b;
           ln=n;
      }     
    }
    
}




void calcSoundColorSeqByAFC(){
    double sat; 
    double value,tone;
    int k,i;
    Uint32 p;
    struct rgb c;
    struct hsv_colour hsv_c; 
    struct rgb_colour rgb_c;
//sound_a,sound_fi,sound_freq
    for(i=0;i<SEQLEN;i++){
        seqAccR[i]=0;
        seqAccG[i]=0;
        seqAccB[i]=0;
        
    
    }
    i=0;
    int li;
    for(k=1;k<Nmax;k++){
        //continue;
       value=sound_a[k]/7-20;//-50;
       sat=(detectOk(sound_freq[k])+30)*5;
       if(value<0.)
        value=0.;
       if(sat<0.)
        sat=0.;
        if(sat>99.)
            sat=99.;
       if(value>99.)
            value=99.;
       tone=detectTone(sound_freq[k]);
      
       hsv_c.v=value/100.;
       hsv_c.h=tone/12;
       hsv_c.s=sat/100.;
       hsv2rgb(&hsv_c,&rgb_c);
       c=rgb_colour2rgb(&rgb_c);
       li=i;
       i=log(k)/log(Nmax)*SEQLEN*5;//k*SEQLEN/Nmax;
       if(i-li>6*5){
            i=li+6*5;
       }
       //i=(k+2)/(Nmax+2)*5*SEQLEN;
       if(li!=i){
        int i0,ii;
        i0=(li+i)/2;
        ii=(i-li) ;
       
        for(;li<i;li++){
            if(sound_freq[k]>minColorSeqFreq){
       
                seqAccR[li%SEQLEN]+=c.r*(ii-2*abs(li-i0))/ii;
                seqAccG[li%SEQLEN]+=c.g*(ii-2*abs(li-i0))/ii;
                seqAccB[li%SEQLEN]+=c.b*(ii-2*abs(li-i0))/ii;
            }
        }
       }
       else{
           if(sound_freq[k]>minColorSeqFreq){
               seqAccR[i%SEQLEN]+=c.r;
               seqAccG[i%SEQLEN]+=c.g;
               seqAccB[i%SEQLEN]+=c.b;
           }       
       
       }


//       colorSeq2Buf[k*SEQLEN/Nmax]=*((Uint32*)&c );
    }
    for(i=0;i<SEQLEN;i++){

       if(seqAccR[i]>255){
            seqAccR[i]=255;       
       }
       if(seqAccG[i]>255){
            seqAccG[i]=255;       
       }
       if(seqAccB[i]>255){
            seqAccB[i]=255;       
       }
       
       c.r=seqAccR[i];
       c.g=seqAccG[i];
       c.b=seqAccB[i];


       colorSeq2Buf[i]=*((Uint32*)&c );
    }
    
}




/*
void calcSoundColorSeqByAFC(){
    double sat; 
    double value,tone;
    int k,i;
    Uint32 p;
    struct rgb c;
    struct hsv_colour hsv_c; 
    struct rgb_colour rgb_c;
//sound_a,sound_fi,sound_freq
    for(i=0;i<SEQLEN;i++){
        seqAccR[i]=0;
        seqAccG[i]=0;
        seqAccB[i]=0;
        
    
    }
    i=0;
    int li;
    for(k=1;k<Nmax;k++){
       if(sound_freq[k]<minColorSeqFreq)
        continue;
       value=sound_a[k]/7-20;//-50;
       sat=(detectOk(sound_freq[k])+30)*5;
       if(value<0.)
        value=0.;
       if(sat<0.)
        sat=0.;
        if(sat>99.)
            sat=99.;
       if(value>99.)
            value=99.;
       tone=detectTone(sound_freq[k]);
      
       hsv_c.v=value/100.;
       hsv_c.h=tone/12;
       hsv_c.s=sat/100.;
       hsv2rgb(&hsv_c,&rgb_c);
       c=rgb_colour2rgb(&rgb_c);
       li=i;
       i=log(k+2)/log(Nmax+2)*5*SEQLEN;//k*SEQLEN/Nmax;
       if(li!=i){
        int i0,ii;
        i0=(li+i)/2;
        ii=(i-li) ;
        for(;li<i;li++){
           seqAccR[li%SEQLEN]+=c.r*(ii-2*abs(li-i0))/ii;
           seqAccG[li%SEQLEN]+=c.g*(ii-2*abs(li-i0))/ii;
           seqAccB[li%SEQLEN]+=c.b*(ii-2*abs(li-i0))/ii;
        }
       }
       else{
           seqAccR[i%SEQLEN]+=c.r;
           seqAccG[i%SEQLEN]+=c.g;
           seqAccB[i%SEQLEN]+=c.b;
       
       
       }


//       colorSeq2Buf[k*SEQLEN/Nmax]=*((Uint32*)&c );
    }
    for(i=0;i<SEQLEN;i++){

       if(seqAccR[i]>255){
            seqAccR[i]=255;       
       }
       if(seqAccG[i]>255){
            seqAccG[i]=255;       
       }
       if(seqAccB[i]>255){
            seqAccB[i]=255;       
       }
       
       c.r=seqAccR[i];
       c.g=seqAccG[i];
       c.b=seqAccB[i];


       colorSeq2Buf[i]=*((Uint32*)&c );
    }
    
}


*/

void calcSoundColorSeqByNotes(){
    double r,g,b,a,s;
    int t,i,k,j;
    double tr[NOTES];
    double tg[NOTES];
    double tb[NOTES];
    struct rgb c;
    Uint32 p;
    struct hsv_colour hsv_c; 
    struct rgb_colour rgb_c;
    
    for(i=0;i<foundNotes;i++){
            t=notes[i].tone;
            hsv_c.v=0.99;
            hsv_c.h=t/12.;
            hsv_c.s=0.99;
            hsv2rgb(&hsv_c,&rgb_c);
            c=rgb_colour2rgb(&rgb_c);
            tr[t]=c.r/255.;          
            tg[t]=c.g/255.;          
            tb[t]=c.b/255.;          
            //printf("%f %f %f\n",tr[t],tg[t],tb[t]);
    }
    
     //printf("foundNotes:%d\n",foundNotes);
            
    
    for(i=0;i<SEQLEN;i++){
            r=0;g=0;b=0;a=0;
           for(j=0;j<foundNotes;j++){
                t=notes[j].tone;
                //printf("facols[t]:%d\n",facols[t]);
                for(k=0;k<facols[t];k++){
                    double f;
                    
                    f=freqs[t][k];
                    f=log(f);
                    if(f<0.001)
                        f=0.001;
                    //f=1;
                    //printf("f[%d]:%f %f",k,f,amps[t][k]);
                    s=(cos(i*f/SEQLEN*2*M_PI)+1)*amps[t][k];
                    r=r+ tr[t]*s;
                    g=g+ tg[t]*s;
                    b=b+ tb[t]*s;
                    a=a+s;
                }                    
            //    printf("\n");
            
            }
            
            

            
            
            c.r=255*r/a;
            c.g=255*g/a;
            c.b=255*b/a;        
            
            colorSeq2Buf[i]=*((Uint32*)&c );
        }

}
double rt0=0;
double lrt0=0;
double nrt0=0;
int ryly1[RITHMLEN];
int ryly2[RITHMLEN];
int ryly[RITHMLEN];
int lrithmp=0;
void drawRithm(SDL_Surface* sc,ShortComplex* r){
        double max=-1e10;
        double min=1e10;
        int h,h0,x,y,w,i,y1;
        h=100;
        w=300;  
        h0=100;  
        
        if(rithmp<0||rithmp>=RITHMLEN)
            return;
        for(i=0;i<rithmp;i++){
            if(r[i].re>max){
                max=r[i].re;
            }
            if(r[i].re<min){
                min=r[i].re;
            }
        }
        if(fabs(max-min)<0.00001){
              min=max-0.00001;
        }

        for(i=0;i<rithmp;i++){
                x=sc->w-w+i*w/RITHMLEN;
                y=h0 + h -  (r[i].re-min)*h/(max-min);
                drawLine(sc,x,h+h0,x,y,0x00ff00);
              //  rectangle(sc,x-2,y-2,x+2,y+2,0x0ff00);
                rectangle(sc,x-1,ryly[i]-4,x+1,ryly[i]+4,0x0000ff);
                rectangle(sc,x-1,ryly1[i]-1,x+1,ryly1[i]+6,0xff0000);
                rectangle(sc,x-1,ryly2[i]-1,x+1,ryly2[i]+1,0xffffff);

        }
     
     
        int y2;         
        
        x=x=sc->w-w+rithmp*w/RITHMLEN;
        y1=h0 + h -  (rx+100)*h/(200) ;
        y= h0 + h - (ry+100)*h/200;
        y2=h0 + h -  (rx+ry+200)*h/(400) ;
        
        if(lrithmp>rithmp)
            lrithmp=0;
        for(i=lrithmp;i<=rithmp;i++){
            ryly1[i]=y1;
            ryly2[i]=y2;
            ryly[i]=y;
        }
        lrithmp=rithmp;

        rectangle(sc,x-3,y-3,x+3,y+3,0x0000ff);
        rectangle(sc,x-5,y1-5,x+5,y1+5,0xff0000);
        rectangle(sc,x-10,y2-10,x+10,y2+10,0xffffff);
            

        double graphTime;
        graphTime=(double)N*RITHMLEN/SAMPLE_RATE;
        double label;
        if(MaxDanceFreq>0.00001 && MaxDanceFreq <1000.)
            for(label=0;label<graphTime;label=label+1./MaxDanceFreq){
                int x;
                x=sc->w-w +  label*w/graphTime;
                rectangle(sc,x,h0 + h,x,h0 + h+10,0x00ff20);    
        
            }
        
}    
 

double AFCacc[(N + 1) / 2];
int AFCaccAge=0;
int maxAFCaccAge=1000;
inline void putS2(int a);
inline void putS1(int a);

struct qs qsAll;
struct qs _qsAll;


 
 #ifdef RECORDSOUND
 
int calcSound(double*koefs){
    int i;
    
  //  if( (err = Pa_IsStreamActive( stream ) ) != 1){
  //      return -1;
  //  }
     
   // Pa_Sleep(10);
   // printf("Actual latencity:%f\n",Pa_GetStreamInfo(stream)->inputLatency);
    while(data.begin!=data.end){
    
    for(;sound_k<N&&data.begin!=data.end;sound_k++,data.begin++,data.begin%=data.len){
            putS2(data.buff1[data.begin]);
            putS1(data.buff2[data.begin]);

            sound_arr[sound_k].re= (data.buff1[data.begin]+(double)data.buff2[data.begin]);
            sound_arr[sound_k].im= 0.0;
    }
    //return 0;
   double maxValue;
    if(sound_k==N){
      //   printf("hi!\n");
    //    fflush(stdout);
        maxValue=0;
        for(i=0;i<N;i++){
            if(maxValue<fabs(sound_arr[i].re))
                maxValue=fabs(sound_arr[i].re);
        }  
        hearingVolume=maxValue/65556;
        if(maxValue<700)
            maxValue=700;

        if(hearingVolume< 0.00000001){
            hearingVolume=0.00000001;
        }
        
        if(drawAddaptiveVolumeValue>65535./maxValue){
            drawAddaptiveVolumeValue=65535./maxValue;
        }else{
            drawAddaptiveVolumeValue= (99*drawAddaptiveVolumeValue+ 65535./maxValue)/100;
        }
//        if(amplifierKoef<1.)
  //          amplifierKoef=1;
            
            
        if(amplifierKoef>65535/maxValue)
            amplifierKoef=65535/maxValue;
        else{
            amplifierKoef=(amplifierKoef*9999+65535/maxValue)/10000;
        
            if(amplifierKoef<amplifierKoefHighValue)
                 amplifierKoef=amplifierKoefHighValue;
            
            
            if(amplifierKoef>amplifierKoefLowValue)
                 amplifierKoef=amplifierKoefLowValue;
        
        
        
        }
        //printf("maxValue: %f\n",maxValue);
        for(i=0;i<N;i++){
            sound_arr[i].re=sound_arr[i].re*amplifierKoef;
        }  
        
        
        
        #define sound_EPS 1000. 
      
        fft(sound_arr, NK, false);
        
        Nmax= (N + 1) / 2;
        
        for(i=0;i<Nmax;i++){
            sound_a[i]=sqrt(sound_arr[i].re*sound_arr[i].re + sound_arr[i].im*sound_arr[i].im);///N;
            
            if(sound_a[i]<sound_EPS){
                sound_a[i]=0.;
            }
            
            if(sound_freq[i]>BASSPASS)
                sound_a[i]=sound_a[i]/10000.*sqrt(i);
            else
                 sound_a[i]=sound_a[i]/20000.;
           
            
          //  sound_a[i]=sound_a[i]/10000.*sqrt(i);
            if(AFCacc[i]<sound_a[i])
                AFCacc[i]=sound_a[i];
            AFCaccAge++;

            
            
            
            
            sound_fi[i]=atan2(sound_arr[i].im, sound_arr[i].re);
            sound_fi[i]+= M_PI/2.;
            if (sound_fi[i] > M_PI)
                sound_fi[i]-= 2.*M_PI;
            sound_freq[i]= (SAMPLE_RATE *(double) i) / N;
            //printf("freqq:%f \n",sound_freq[i]);
        }
//        double*sound_a,double*freqs,int n,int tones,int minoq,int maxoq,struct qs*r
        //speq2qs(sound_a,sound_freq,Nmax,12,-3,6,&_qsAll);
        //QSmorph(qsAll,_qsAll,layerOpt[2]);
        //printf("\n");
        fprintf(stderr,"%f\n",layerOpt[2]);
        fflush(stderr);
       printf("%f\n",layerOpt[2]);
       fflush(stdout);
       // SDL_FillRect(screen,NULL, 0x000000);
        
       //showAmp(screen,a,fi,freq,Nmax);

        double findEps=200.;
        double findRithmEps=2.;
        
        target=findDeep(sound_a,Nmax,Nmax/deepWidth,findEps,MAXMAINOK,cur);
        
        
        cur=(target);//+2*cur)/3;
        
        findNotes(30000);                   
        
        
        
        mtarget=findMedian(sound_a,Nmax,findEps);
        mcur=mtarget;//+19*mcur)/20;
        melodyrithm=findRithm(sound_a,Nmax,findEps,BASSPASS,MELODYPASS);;

        bassrithm=findRithm(sound_a,Nmax,findEps,0,BASSPASS);        
        rithm[rithmp].re=bassrithm+(addMelodyTorithm?melodyrithm:0);
        
        allrithm=findRithm(sound_a,Nmax,findEps,MELODYPASS,ALLPASS);
        
        
        rithm[rithmp++].im=0;
        
        
        if(rithmp==RITHMLEN){
           lrt0=rt0;
           rt0=nrt0;
           nrt0=GetTickCount()/1000.;

            rithmp=0;
            fft(rithm, RITHMK, false);
            int rithmNmax= (RITHMLEN + 1) / 2;
            for(i=0;i<rithmNmax;i++){
                rithma[i]=2*sqrt(rithm[i].re*rithm[i].re + rithm[i].im*rithm[i].im)/N;
                if(rithma[i]<RITHMEPS){
                    rithma[i]=0.;
                }
                //rithma[i]=rithma[i]/10000.*sqrt(i);
                rithmfi[i]=atan2(rithm[i].im, rithm[i].re);
                rithmfi[i]+= M_PI/2.;
                if (rithmfi[i] > M_PI)
                    rithmfi[i]-= 2.*M_PI;
                rithmfreq[i]= (SAMPLE_RATE *(double) i)/N / RITHMLEN;
            //  printf("%f ",freq[i]);
            }
            findNMax(rithma,rithmfreq,rithmNmax,rithms,RO,findRithmEps);
            for(i=0;i<RO;i++){
                lra[i]=ra[i];
                lrfi[i]=rfi[i];
                lrfreq[i]=rfreq[i];
            }

            for(i=0;i<RO;i++){
                ra[i]=rithma[rithms[i]];
                rfi[i]=rithmfi[rithms[i]];
                rfreq[i]=rithmfreq[rithms[i]];
                
            }
            
        
        }

        //drawRithm(screen,ra,rfi,rfreq,RO);

            
 
        
        //SDL_Flip( screen );
        sound_k=0;
        //break;
    }
     
    if(data.lostData){
         printf("Lost data!\n");
        data.lostData=0;
    }
     //fflush(stdout);
  //   SDL_Flip( screen ); 
  //}
    }
    calcRithm(ra,rfi,rfreq,lra,lrfi,lrfreq,RO,rithmp,RITHMLEN,rt0,lrt0);

    
    if(soundControllFlag){
        koefs[0]=bassrithm;
        koefs[1]=melodyrithm;
        koefs[2]=allrithm;
        koefs[3]=mtarget;
        koefs[4]=target;
        koefs[5]=rx;
        koefs[6]=ry;
        koefs[7]=rxy;

        if(colorSeqVar==0)
            initColorSeq2(pifColorSpeedr,pifColorSpeedg,pifColorSpeedb);
        else if(colorSeqVar==1)
            calcSoundColorSeqByNotes();
        else if(colorSeqVar==2){
            calcSoundColorSeqByAFC();
        
        }else if(colorSeqVar==3){
            calcSoundColorSeqByAFCMixingGamma(30,48000,2,2,1.3,2);
        }
        //printf("calcsoundSeq\n");
    }
    
    return 0;
}

#endif

int closeSound(){
//  if( err < 0 ) {
  //      printf("Error!\n");
    //    return -6;
    
 // }
  #ifdef RECORDSOUND

  err = Pa_CloseStream( stream );
  if( err != paNoError ){
  
        return -7;
  }
  //SDL_Quit(); 
  Pa_Terminate();
  if( data.buff1 ) /* Sure it is NULL or valid. */
      free( data.buff1 );
  if( data.buff2 ) /* Sure it is NULL or valid. */
      free( data.buff2 );
  /*if(show1!=NULL)
    free(show1);
  if(show2!=NULL)
    free(show2);*/
 #endif
  return 0;




}



void showAmp(SDL_Surface* screen,double*a,double*fi,double *freq,int n){
    int x,k,y,c2;
    struct rgb c;
    double tone,volume;
    double value;
//    struct hsv_colour hsv; 
  //  struct rgb_colour rgb;
    Uint32 p;
//    hsv_degrees_percent hsv;
  //  rgb_percent rgb;
    
    struct hsv_colour hsv_c; 
    struct rgb_colour rgb_c;
    
    
    
    //printf("n:%d\n",n);
    
    for(x=0;x<screen->w;x++){
        k=x*n/screen->w;
        y=screen->h-a[k]/3.-1;
        
       volume=a[k]/3.;
       value=a[k]/7.;
        if(volume>99.)
            volume=99.;
       if(value>99.)
            value=99.;
       // volume=1;
       tone=detectTone(freq[k]);
       
      /* hsv.v=value;
       hsv.h=tone*360/12;
       hsv.s=volume;
       rgb=hsv2rgb(hsv);
       c=(rgb_percent2rgb(rgb));
      */
       hsv_c.v=value/100.;
       hsv_c.h=tone/12;
       hsv_c.s=volume/100.;
       hsv2rgb(&hsv_c,&rgb_c);
       c=rgb_colour2rgb(&rgb_c);
       
       rgb2pixel(c.r,c.g,c.b,&p);
       // if(x%10==0)
       //     printf("n, k, freq, tone:%d, %d, %f, %f\n",n,k,freq[k],tone);
       // c=hsv2rgb(tone*360./12.,volume,1);
        
        
        //if(a[k]>10){
        //    putPixel(screen,x,y,GREEN);
        
        
        drawLine(screen,x,y,x,screen->h-1,p);
        //}
    
    }
   // printf("!\n");
 //   fflush(stdout);


}

void drawLabel(SDL_Surface* screen,int x,int w,Uint32 c){
     drawSqr(screen,x-w,screen->h/2-w,x+w,screen->h/2+w,c);
     


}
void drawHLabel(SDL_Surface* screen,int x,int y,int w,Uint32 c){
     drawSqr(screen,screen->w-x-w,screen->h/2+y-w,screen->w-x+w,screen->h/2+y+w,c);
}



void drawSound(SDL_Surface* screen){
      int i,x;
      
       SDL_FillRect(screen,NULL, 0x000000);
       drawCurrent(screen);
       
       showAmp(screen,sound_a,sound_fi,sound_freq,Nmax);    
//       for(x=0;x<Nmax;x++){
  //          if(getNota(x).ok==cur)
    //            break;
      // }
       drawLabel(screen,cur*screen->w/Nmax,screen->w/deepWidth,WHITE);
        
        
        
        for(i=0;i<foundMainNotes;i++){
            showNota(screen,notes[i]);
        }
        for(i=foundMainNotes;i<foundNotes;i++){
            showCollectedNotes(screen,notes[i]);
        }
        
        
        drawLabel(screen,mcur*screen->w/Nmax,6,WHITE);
        drawHLabel(screen,100,bassrithm/10.,6,WHITE);

        drawHLabel(screen,200,melodyrithm/100.,6,WHITE);

        //drawRithm(screen,ra,rfi,rfreq,RO);
        drawSqr(screen,screen->w-110+rx,screen->h/2+ry-10,screen->w-90+rx,screen->h/2+ry+10,WHITE);
        drawRithm(screen,rithm);
}


int lastrgbMixerAuto=-1;



inline int calcColor(int*seq,double t,int n){
    double r;
    double norm;
    
    int i;
    r=0;
    norm=0;
    for(i=0;i<n;i++){        
        if(sound_freq[seq[i]]>0.00001 && !std::isnan( sound_a[seq[i]]) && !std::isnan( sound_freq[seq[i]]) && !std::isnan( sound_fi[seq[i]])){
            r+=sound_a[seq[i]]*sin(t/sound_freq[seq[i]]+sound_fi[seq[i]]);
            //printf("freq:%f\n",sound_freq[seq[i]]);
            norm+=sound_a[seq[i]];
        }
    
    }
    if(fabs(norm)>0.0000001)
        return (r)*256/norm;
    return 0;
}


void calcColorSound(){
    int i;
    double c;
    c=(double)SEQLEN/20.;
    for(i=0;i<SEQLEN;i++){
            struct rgb a;
            int r,g,b;
            *((Uint32*)&a )=colorSeq2Buf[i];
            r=a.r;
            g=a.g;
            b=a.b;
            r+=calcColor(reds,(double)i / c,KO)/2;
            g+=calcColor(greens,(double)i /c,KO)/2;
            b+=calcColor(blues,(double)i /c,KO)/2;        
            if(r<0)
                r=0;
            if(r>255)
                r=255;
            if(g<0)
                g=0;
            if(g>255)
                g=255;
            if(b<0)
                b=0;
            if(b>255)
                b=255;
                
            a.r=r;
            a.g=g;
            a.b=b;
           
            colorSeq2Buf[i]=*((Uint32*)&a );
    }
}



int syncllrithmp=0;
void syncSoundData(){
     if(syncllrithmp<rithmp){
         for(int i=syncllrithmp;i<=rithmp;i++)
              rithm[i].re=bassrithm+(addMelodyTorithm?melodyrithm:0);
        syncllrithmp=rithmp;
     }else if(syncllrithmp>rithmp){
         for(int i=0;i<RITHMLEN;i++)
              rithm[i].re=0;
      
       syncllrithmp=rithmp;
     }        

       Nmax= (N + 1) / 2;
        
        for(int i=0;i<Nmax;i++){
            sound_freq[i]= (SAMPLE_RATE *(double) i) / N;

        }
        cur=target;
        mcur=mtarget;
}
#endif