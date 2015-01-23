int snake=0;
int rizePannel=0;
double aspectKoef=1;
#include"broatcaser.cpp"
#define CONTRL  37
char recPath[512];
char vrecPath[512];
char videoRecFolder[512]="recvideo/";
#define REVERCERGB
#define GLBILD
#define min(x,y)  (((x)>(y))?(y):(x))
#define CCORLEN (7+6)
#define RECORDSOUND
double fraqFilter=0.1;
int syntaxControll(char*p);
#define WINDOWCOMPILE 0
#define NONBLOCK
//#define WINDOWCOMPILE 8
double pifColorSpeedr=0.01;
double pifColorSpeedg=0.11;
double pifColorSpeedb=1.11;
int showColorSeq=1;
void *__gxx_personality_v0;
int pifPosition=1;
short int keys[256];
int pifRepeat=1;
int pifParity=1;
int filterMegaFlag=0;

//double filterMegaValue;

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
   Uint32 getSoundKoefsColor(int i,double old){return 0;}
//#include "SDL_opengl.h"
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <time.h> 

#include"myserver.cpp"
#include "opencv.c"
#include"life.cpp"
#include"wave2screen.cpp"

#include "timeutil.cpp"
#ifdef NONBLOCK
    #include <fcntl.h>
#endif
#include"koefs.cpp"

#include"ascillators.cpp"

#define BUFSIZE 128
int msgid;

struct msgp {
    long mtype;
    char s[128];

};

void*modeData;
int mode,H,W;
//#include<sys/ipc.h>
//#include<sys/msg.h>
//#include <sys/types.h>
#define SVIDKEY 7373
#include "graphutil.cpp"
#include"timbre.cpp"

#include"speq2screen.cpp"
#include"drawlayer.cpp"
#include"drawplatespeq.cpp"
#include"drawsurfacespeq.cpp"

#include"fillsignal.cpp"
struct signal *mysignal;

#include"waves.cpp"
//#include "netutil.cpp"
//#include "pipeutil.c"
//#include <sys/socket.h>

#include "snake.cpp"
//  GLuint texture; // Texture object handle
#include "hohloma.cpp"
#include "4d.cpp"
#include "barcode.cpp"
//#include "slcf.cpp"
#include "piano.cpp"
#include "mixer.cpp"

int rgbMixerDepth=10;
int moveNoiseDiv=0;
int moveNoiseCount=10;
int pifDeep=13;
int pifNaked=1;
int pifColored=1;
double pifDWind=1/100000.0;
double pifDScale=1;
double pifDAngle=M_PI/10000;

int soundControllFlag=0;
double hearingVolume;
double amplifierKoef=100;
double amplifierKoefHighValue=1.5;
double amplifierKoefLowValue=1000;

#include"drawcurrent.cpp"

#include "soundutil.cpp"
#include"quickspeq.cpp"
#include "pifagor.cpp"
#include"myplay.cpp"


#include"viewfreqs.cpp"

//#include "filters/nosound.cpp"
//int SVIDanswer(const char*p);
void drawStars(SDL_Surface* screen){
    putpixel(screen,rand() % (screen->w),rand() % (screen->h),rand()); 
//    SDL_Flip( screen ); 
}


Uint32 frames;







#define dEqEps 1e-10
#define dEq(a,b) ((fabs((a)-(b))<dEqEps)?1:0)

int    lcurrentFps=-100;
int    lpifPosition=-100;
int    lpifColored=-100;
int    lpifNaked=-100;
int    lpifDeep=-100;

int ltimeSynk=-100;

double lpifDAngle=-100.;
double lpifDScale=-100.;
double lpifDWind=-100.;

double lbassrithm=-100;
double lmelodyrithm=-100;
double lallrithm=-100;
int lmtarget=-100;
int ltarget=-100;
double lrx=-100;
double lry=-100;
double lrxy=-100;


int connected=0;
void sendAllMass();


void sendSoundRawData(){
 if(!dEq(lbassrithm,bassrithm)){
        printf("set bassrithm %lf\n",bassrithm);
        lbassrithm= bassrithm ;
 }
if(!dEq(lmelodyrithm,melodyrithm)){
        printf("set melodyrithm %lf\n",melodyrithm);
        lmelodyrithm= melodyrithm ;
 }
 if(!dEq(lallrithm,allrithm)){
        printf("set allrithm %lf\n",allrithm);
        lallrithm= allrithm ;
 }
 
 
// lmelodyrithm=-100;
// lallrithm=-100;
 if(lmtarget!=mtarget){
        printf("set mtarget %d\n",mtarget);
         lmtarget = mtarget ;
 }
 
 
// lmtarget=-100;
 if(ltarget!=target){
        printf("set target %d\n",target);
         ltarget = target ;
 }
 
 
// ltarget=-100;
 if(!dEq(lrx,rx)){
        printf("set rx %f\n",rx);
         lrx = rx ;
 }

 if(!dEq(lry,ry)){
        printf("set ry %f\n",ry);
         lry = ry ;
 }
 if(!dEq(lrxy,rxy)){
        printf("set rxy %f\n",rxy);
         lrxy = rxy ;
 }

// lrx=-100;
// lry=-100;
        


}
double llrithmp=-1;
double lhearingVolume=-1;
double lamplifierKoef=-100;
int faded=50;
int orblurd=0;
    //orblurd
int noiseC=0;
int noiseV=0;
int noiseColor=0;
/*#define LAYEROPTS 9
double layerOpt[LAYEROPTS]={0.4,0.1,0,0,0,0.1,0.1,0,0};
*/
#include"editpannels.cpp"


#include"sendrecive.cpp"

Uint32 lastRecive;
void writeAllValues(int writeAll);
void writeAllValues(){
   writeAllValues(0);

}

void writeAllValues(int writeAll){
    if(!writeAll){
      if(!connected)
          return;
      if(GetTickCount()-lastRecive>400){
            return;
        }      
    }
    if(connected && showColorSeq){
//        writeColorSeq();
        writeColorSeq3();
    }

    sendAllMass(stdout,writeAll);
    sendSoundRawData();
    writeSoundControllValue(stdout,writeAll);
    writeVolume();
    sendMas("colorCorrector",stdout,writeAll);
    sendFilters(stdout,writeAll);

    if(!dEq(hearingVolume,lhearingVolume)){
        printf("set hearingVolume %f\n",hearingVolume);
        lhearingVolume=hearingVolume;
    }
   if(!dEq(amplifierKoef,lamplifierKoef)){
        printf("set amplifierKoef %f\n",amplifierKoef);
        lamplifierKoef=amplifierKoef;
    }
 /*  sending it in sendrecive.cpp   
    if(lsoundControllFlag!=soundControllFlag){
        printf("set soundControllFlag %d\n",soundControllFlag);
        lsoundControllFlag=soundControllFlag;
    }
    if(lcolorSeqVar!=colorSeqVar){
        printf("set colorSeqVar %d\n",colorSeqVar);
        lcolorSeqVar=colorSeqVar;
    }
 
*/    
    if(rithmp!=llrithmp){
        printf("set rithmp %d\n",rithmp);
        llrithmp=rithmp;
    }
/*    if(!dEq(pifDWind,lpifDWind)){
        printf("set pifDWind %lf\n",pifDWind);
        lpifDWind=pifDWind;
    }
    if(!dEq(pifDScale,lpifDScale)){
        printf("set pifDScale %lf\n",pifDScale);
           lpifDScale=pifDScale  ;
    }
    if(!dEq(pifDAngle,lpifDAngle)){
        printf("set pifDAngle %lf\n",pifDAngle);
           lpifDAngle= pifDAngle ;
    }
    
    
    
    if(pifDeep!=lpifDeep){
        printf("set pifDeep %d\n",pifDeep);
         lpifDeep  = pifDeep ;
    }
    
    if(pifNaked!=lpifNaked){
        printf("set pifNaked %d\n",pifNaked);
          lpifNaked =pifNaked  ;
    }
    if(pifColored!=lpifColored){
        printf("set pifColored %d\n",pifColored);
          lpifColored = pifColored ;
    }*/
    if(pifPosition!=lpifPosition){
        printf("set pifPosition %d\n",pifPosition);
           lpifPosition=pifPosition  ;
    }
    if(currentFps!=lcurrentFps){
        printf("set currentFps %d\n",currentFps);
    
           lcurrentFps=currentFps  ;
    }
    
    if(ltimeSynk!=timeSynk){
        printf("set timeSynk %d\n",timeSynk);
    
           ltimeSynk=timeSynk  ;
    }

    fflush(stdout);
    
    
}

//    lsoundControllFlag=-1
  //      lcolorSeqVar=-1


int readValue(char*name,char*value){
    
      //  lsoundControllFlag=-1
     //   lcolorSeqVar=-1

    if(!readSoundControllValue(name,value)){
        return 0;
    }

    if(!strcmp(name,"autoPifDeep")){
        sscanf(value,"%d",&autoPifDeep);
        lautoPifDeep=autoPifDeep;
        return 0;
    }



    
    if(!strcmp(name,"pifDWind")){
        sscanf(value,"%lf",&pifDWind);
        lpifDWind=pifDWind;
        return 0;
    }

    if(!strcmp(name,"pifDScale")){
        sscanf(value,"%lf",&pifDScale);
        lpifDScale=pifDScale;
        return 0;
    }

    if(!strcmp(name,"pifDAngle")){
        sscanf(value,"%lf",&pifDAngle);
        lpifDAngle=pifDAngle;
        return 0;
    }

    if(!strcmp(name,"pifColorSpeedr")){
        sscanf(value,"%lf",&pifColorSpeedr);
        lpifColorSpeedr=pifColorSpeedr;
        return 0;
    }

    if(!strcmp(name,"pifColorSpeedg")){
        sscanf(value,"%lf",&pifColorSpeedg);
        lpifColorSpeedg=pifColorSpeedg;
        return 0;
    }

    if(!strcmp(name,"pifColorSpeedb")){
        sscanf(value,"%lf",&pifColorSpeedb);
        lpifColorSpeedb=pifColorSpeedb;
        return 0;
    }

    if(!strcmp(name,"faded")){
        sscanf(value,"%d",&faded);
        lfaded=faded;
        return 0;
    }
    if(!strcmp(name,"orblurd")){
        sscanf(value,"%d",&orblurd);
        lorblurd=orblurd;
        return 0;
    }
    
    


    if(!strcmp(name,"rgbMixerDepth")){
        sscanf(value,"%d",&rgbMixerDepth);
        lrgbMixerDepth=rgbMixerDepth;
        return 0;
    }

    if(!strcmp(name,"noiseC")){
        sscanf(value,"%d",&noiseC);
        lnoiseC=noiseC;
        return 0;
    }

    if(!strcmp(name,"noiseV")){
        sscanf(value,"%d",&noiseV);
        lnoiseV=noiseV;
        return 0;
    }

    if(!strcmp(name,"noiseColor")){
        sscanf(value,"%d",&noiseColor);
        lnoiseColor=noiseColor;
        return 0;
    }

    if(!strcmp(name,"pifDeep")){
        sscanf(value,"%d",&pifDeep);
        lpifDeep=pifDeep;
        return 0;
    }

    if(!strcmp(name,"pifNaked")){
        sscanf(value,"%d",&pifNaked);
        lpifNaked=pifNaked;
        return 0;
    }

    if(!strcmp(name,"pifColored")){
        sscanf(value,"%d",&pifColored);
        lpifColored=pifColored;
        return 0;
    }
    if(!strcmp(name,"pifPosition")){
        sscanf(value,"%d",&pifPosition);
        lpifPosition=pifPosition;
        return 0;
    }
    

    return 1;
}



SDL_Surface*tempBuf=NULL;
//SDL_Surface* outputScreen = NULL;


/*

    koefs[0]=bassrithm;
    koefs[1]=melodyrithm;
    koefs[2]=allrithm;
    koefs[3]=mtarget;
    koefs[4]=target;
    koefs[5]=rx;
    koefs[6]=ry;


*/



void mod2PI(double&a){
    while(a>=2*M_PI){
        a=a-2*M_PI;
    }
    while(a<0.){
        a=a+2*M_PI;
    }
}
extern        int startOqcl;
extern  int finOqcl;

void pifSoundControll(double *sk,double *zero,double*dkoef,double *ck,double *pk,double*maxpk,double*minpk){
    int i,j;
    //angles :3,5,12
    
    
  /*  printf("SoundKoef: ");
    for(i=0;i<KOEFNUM;i++)
        printf("%f ",sk[i]);
    printf("\n");
    
    
    */
    
    mod2PI(dkoefacc[3]);
    mod2PI(dkoefacc[5]);
    mod2PI(dkoefacc[12]);

    mod2PI(zeros[3]);
    mod2PI(zeros[5]);
    mod2PI(zeros[12]);

    mod2PI(koefascellacc[3]);
    mod2PI(koefascellacc[5]);
    mod2PI(koefascellacc[12]);
    
    
    
    

    
    for(i=0;i<DRAWKOEFNUM;i++){
      //  printf("drawKoef %d: ",i);
        dkoefacc[i]=dkoefacc[i]+dkoef[i];
        pk[i]=zeros[i]+dkoefacc[i];
        koefascellacc[i]=koefascellacc[i]+koefascell[i];
        double t;
        t=koefascellamp[i]*ascell(i,koefascellacc[i]);
        ascellValue[i]=t;
       // koefascellacc[i]=savePeriod(i,koefascellacc[i]);
     //   if(t>0.0001){
       //     printf("%d:%f\n",i,t);
        //}
        pk[i]=pk[i]+t;
        
        for(j=0;j<KOEFNUM;j++){
            pk[i]=pk[i]+sk[j]*ck[i*KOEFNUM+j];
            if(fabs(ck[i*KOEFNUM+j])>0.0001){
        //        printf("%d <-> %d\n",i,j);
            
            }
        
        }
       // printf("S(pk)=%f",pk[i]);
        if(pk[i]>maxpk[i]){
            pk[i]=maxpk[i];
        }
        if(pk[i]<minpk[i]){
            pk[i]=minpk[i];
        }
        
        //printf("(%f)\n",pk[i]);
    
    }
    if(autoPifDeep){

    
        pk[0]=maxoqs;
        pk[15]=0;
    
    }

    
    
}
/*
unsigned char *mask;
int maskW=0;
int maskH=0;*/ 
#include"interfer.cpp"
struct layer *mask=NULL;
struct layer *mask2=NULL;
struct layer *osd=NULL;


int llh,llw;
#include"gparticles.cpp"
#include"ok_colorline.cpp"
#include"soundField.cpp"
int drawGLZ=0;
double minDistance=10;
double maxDistance=100;

int GLLINE =1;
int BADBUF[800*600];
int GLDRAW=1;
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

//

char *video2;
int video2h,video2w;
struct layer qsl;
void draw(SDL_Surface* screen,SDL_Surface* filter,double*sk){
  // SDL_FillRect(screen,NULL, 0x000000);
 //  SDL_FillRect(filter,NULL, 0x000000);
//    plog("rabbit draw");
    
    if(faded!=255){
        GLLINE=0;
    }else{
        GLLINE=1;
    }
    GLLINE=1;
    orOpacity=((unsigned int)(getOpt("orOpacity")*255))*256*256*256;
    putPixelMetod=getOpt("glBlendMetod")>0.5?0:1;
    if(layerOpt[6]*screen->h<1.){
        layerOpt[6]=0.00001+1./screen->h;
    }
    if(layerOpt[5]*screen->w<1.){
        layerOpt[5]=0.00001+1./screen->w;
    }
    if(mask==NULL){
        mask=makeLayer(layerOpt[5]*screen->w,layerOpt[6]*screen->h,getOpt("interferPart"));
        if(mask==NULL)
            return;
        mask2=makeLayer(layerOpt[5]*screen->w,layerOpt[6]*screen->h,getOpt("interferPart"));
        if(mask2==NULL)
            return;
        llh=layerOpt[6]*screen->h;
        llw=layerOpt[5]*screen->w;
    }
    if(llh!=(int)layerOpt[6]*screen->h|| llw!=(int)layerOpt[5]*screen->w){
        llh=layerOpt[6]*screen->h;
        llw=layerOpt[5]*screen->w;
         mask=resizeLayer(mask,layerOpt[5]*screen->w,layerOpt[6]*screen->h,getOpt("interferPart"));
         if(mask==NULL)
            return;
         mask2=resizeLayer(mask2,layerOpt[5]*screen->w,layerOpt[6]*screen->h,getOpt("interferPart"));
         if(mask2==NULL)
            return;
       
    
    }  
    if(mode!=6 && !drawGLZ && ! GLLINE){
         fade(screen,faded);
         orblur(screen,orblurd);
         addNoise(screen,noiseC,noiseV,noiseColor);
  
   }
   

   /* if(tempBuf == NULL){
        //printf("init smooth!\n");
        tempBuf=cloneScreen(screen);
    }
    if(tempBuf!=NULL){
        
        smooth(screen,tempBuf);
        copySurface(tempBuf,screen);
    }*/
    fraqFilter=0;//1;//layerOpt[7];
    if(fraqFilter<0.001)
        fraqFilter=0.001;
    if(layerOpt[7]<0.001)
        layerOpt[7]=0.001;
    interFer(mask,layerOpt[7]*100,getOpt("interferPart"),calcOpt("interferGamma"));
    morph(mask2,mask,calcOpt("interferMorphSpeed"));
    if(getOpt("wave2sceen1")){
        wave2screenOutput(tex_wave2sceen);
        
    }

    if(getOpt("qsPlateOp1") >0.0001||getOpt("qsPlateOp2") >0.0001||getOpt("qsPlateOp3") >0.0001){
         drawPlateSpeq(tex_qsPlate,&qsAll,calcOpt("qsPlateRGamma")*3.,calcOpt("qsPlateA0")*4,calcOpt("qsPlateNormLen"));
    }
    if(getOpt("timbre1")>0.00001||getOpt("timbre2")>0.00001||getOpt("timbre3")>0.00001){
          //proccessTimbre(sound_freq,sound_a,sound_fi,Nmax);
          drawTimbres(tex_timbre,calcOpt("timbre_a1")*2*M_PI,calcOpt("timbre_a2")*2*M_PI,calcOpt("timbre_r")*10,calcOpt("timbre_fov")*160+0.0001);


    }

    
    if(getOpt("soundSpeq1") >0.0001||getOpt("soundSpeq2") >0.0001||getOpt("soundSpeq3") >0.0001){
//        fprintf(stderr,"ssp1\n");
        drawSoundSpeq(soundSpeqtex,&ssp1,calcOpt("soundSpeq_r")*10,calcOpt("soundSpeq_a1")*2*M_PI,calcOpt("soundSpeq_a2")*2*M_PI,calcOpt("soundSpeq_a3")*2*M_PI,calcOpt("soundSpeq_fov")*160+0.0000001,calcOpt("soundSpeq_len"),calcOpt("soundSpeq_width") );

    }
    if(getOpt("soundSpeqSquare1") >0.0001||getOpt("soundSpeqSquare2") >0.0001||getOpt("soundSpeqSquare3") >0.0001){
//    void (GLuint tex,struct soundSpeq*ssp,double r,double a1,double a2,double a3,double fov,double len,double width ){
    
        drawSoundSpeqSquare(soundSpeqSquaretex,&ssp1,calcOpt("soundSpeqSquare_r")*10,calcOpt("soundSpeqSquare_a1")*2*M_PI,calcOpt("soundSpeqSquare_a2")*2*M_PI,calcOpt("soundSpeqSquare_a3")*2*M_PI,calcOpt("soundSpeqSquare_fov")*160+0.0000001,calcOpt("soundSpeqSquare_len"),calcOpt("soundSpeqSquare_width") );

    }
    

    
    
    if(getOpt("qsLayer1") >0.0001||getOpt("qsLayer2") >0.0001||getOpt("qsLayer3") >0.0001){
        //fprintf(stderr,"%f ",getOpt("qsLayer1"));
        //fprintf(stderr,"%f ",getOpt("qsLayer2"));
        //fprintf(stderr,"%f\n",getOpt("qsLayer3"));
//        qs2layer(&qsAll,&qsl);
  //      drawLayer(tex_qs,&qsl, calcOpt("qsLayer_r")*10,calcOpt("qsLayer_a1")*2*M_PI,calcOpt("qsLayer_a2")*2*M_PI);
      draw3dDisesSpiral(tex_qs,&qsAll, calcOpt("qsLayer_r")*10,calcOpt("qsLayer_a1")*2*M_PI,calcOpt("qsLayer_a2")*2*M_PI,calcOpt("qsLayer_a3")*2*M_PI,calcOpt("qsLayer_pow")*10,calcOpt("qsLayer_rpow")*2,calcOpt("qsLayer_r0"),calcOpt("qsLayer_fov")*160+0.0000001,calcOpt("qsLayer_len")*10,calcOpt("qsLayer_rAsum")-0.5,calcOpt("qsLayer_pAlpha"), calcOpt("qsLayer_pZero"),calcOpt("qsLayer_lZero"),calcOpt("qsLayer_normLen"),2*calcOpt("qsLayer_disValueKoef"),calcOpt("qsLayer_minPointValue"),calcOpt("qsLayer_lineWidth")*40+0.00000001,calcOpt("qsLayer_platesType"),calcOpt("qsLayer_sideShift"));
   
    
    }
    
    
    
    if(getOpt("qsSurf1") >0.0001||getOpt("qsSurf2") >0.0001||getOpt("qsSurf3") >0.0001){
    
        drawSurfaceSpeq(tex_qsSurf,&qsAll,calcOpt("qsSurf_r")*10,calcOpt("qsSurf_a1")*2*M_PI,calcOpt("qsSurf_a2")*2*M_PI,calcOpt("qsSurf_fov")*160+0.0000001,calcOpt("qsSurf_pw")*30,calcOpt("qsSurf_mindl"));
    }    
    if(getOpt("touchSpeq1")>0.00001 && touchSpeq_ready){
//         fprintf(stderr,"drawSpec finished\n");
  //       fflush(stderr)

         drawSpec(tex_touch,calcOpt("touchSpeq_r")*10,calcOpt("touchSpeq_a1")*2*M_PI,calcOpt("touchSpeq_a2")*2*M_PI,calcOpt("touchSpeq_fov")*160,calcOpt("touchSpeq_pwks"),calcOpt("touchSpeq_minfreq"),calcOpt("touchSpeq_maxfreq"),calcOpt("touchSpeq_pwksr"),calcOpt("touchSpeq_type"));
    //     fprintf(stderr,"drawSpec finished\n");

//         touchSpeq(b_freqs,b_sound_a,touchSpeq_ks,touchSpeq_vs,Nmax);
         //=1;
    }
        
    
    
    
    switch (mode){
        case 1: drawSnake(screen); break;   
        case 2:drawHohloma(screen); break;      
        case 3:draw4d(screen); break;
        case 4:drawbarcode(screen); break;
//pifDeep,pifNaked,pifColored,pifDWind,pifDScale,pifDAngle,pifColorSpeedr,pifColorSpeedg,pifColorSpeedb,pifRepeat,pifParity        
        case 5: 
        
        if(glOpt[14]<0.999){
            pifSoundControll(sk,zeros,dkoef,controllKoef,drawKoef,maxDrawKoef,minDrawKoef);
            drawKoefLatency(drawKoef,drawLatKoef);
        }
//        drawMask(screen,mask2,0.2);
      //  fprintf(stderr,"drawPif!\n");
       // fflush(stderr);
        extern double pifSoft;
        pifSoft=layerOpt[10];
        pifWight=layerOpt[11];
//        if(drawGLZ)
  //          startGlPif();
        if(GLLINE){
        //    makeFB();
//            glBindFramebuffer(GL_FRAMEBUFFER, renderFBO);
           // производим очистку буферов цвета и глубины
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          // glEnable(GL_ALPHA_TEST);
        glViewport(0, 0, GLW, GLH);
        
        glMatrixMode(GL_PROJECTION);
//        glPushMatrix();
        glLoadIdentity();
        glOrtho(0.0f,  GLW, GLH, 0.0f, -1.0f, 1.0f);
       
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
//        glColorMask(1,1,1,1);
  
        if(1||glOpt[14]<0.999){
        
              glClearColor(0,0,0,1);

              glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT   );
               glDisable(GL_DEPTH_TEST);
               glDisable(GL_BLEND);
               glDisable(GL_ALPHA_TEST);
                   
              glEnable(GL_COLOR_LOGIC_OP);        
              glLogicOp(GL_OR);
             // glColor4f(1.0f,1.0f,1.0f,1);

               glDisable(GL_TEXTURE_2D);
               glEnable(GL_LINE_SMOOTH);
         
           }
        }    
        
        if(glOpt[14]<0.999)
            drawPifagor(screen,drawKoef);
        
        if(!drawGLZ){
            prepareOrSeqNo2();
            if(!GLLINE){
                if(layerOpt[0]>=0.02){

                        mixBWSizedOr(screen,mask2,layerOpt[0],layerOpt[1]*255,((int)(layerOpt[2]*255))  +256*((int)(layerOpt[3]*255)) + 256*256*((int)  (layerOpt[4]*255)));}
            }else{
//                getNextFrame(&video2,&video2h,&video2w);
  //  glEnable(GL_TEXTURE_2D);
    
    //            glBindTexture(GL_TEXTURE_2D, vct);
      //          glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, video2w,video2h,
        //        0, GL_BGR, GL_UNSIGNED_BYTE, video2);
          //      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            
                if(layerOpt[0]>=0.02)
                mixBWSizedOrGL(mask2,layerOpt[0],layerOpt[1]*255,((int)(layerOpt[2]*255))  +256*((int)(layerOpt[3]*255)) + 256*256*((int)(layerOpt[4]*255)),-1,screen->w,screen->h);
            }
      
        // drawMask(screen,mask2,0.6,127);
       // mulMix(screen,mask,1);
            if(osd!=NULL){
//                mixBWSized(screen,osd,1,0,0);
                  mixBWSized(screen,osd,(sk[0]+sk[2]),0,0);
                  //layer2particles(screen,osd,0.006,0.1,0.1,0.9);
    
            }
        }
        
//        GLDRAW=0;
                   
  //     glFlush();
    //   glFinish();

      // SDL_GL_SwapBuffers();

        if(GLLINE){
            glDisable(GL_LINE_SMOOTH);

          //glBindFramebuffer(GL_FRAMEBUFFER, 0);
          
      // glFlush();
      // glFinish();
        
               glDisable(GL_COLOR_LOGIC_OP);        
               glEnable(GL_TEXTURE_2D);
               glEnable(GL_ALPHA_TEST);
          //   glEnable(GL_BLEND);
  //           glBlendFunc(GL_SRC_ALPHA, GL_ONE/*_MINUS_SRC_ALPHA*/);

            if(glscinit && (glOpt[14]<0.999)){
//                glBindTexture(GL_TEXTURE_2D, sct);
                glBindTexture(GL_TEXTURE_2D, sct);
                glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, GLW, GLH, 0);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
             //   glReadPixels(0, 0, GLW, GLH, GL_BGR, GL_UNSIGNED_BYTE, BADBUF);
                
        //       if(!(rand()%10)){
          //      FILE*f;
            //    f=fopen("dump.d","w");
              //   fwrite(BADBUF,GLW, GLH*4,f);
              //  fclose(f);
              //  fprintf(stderr,"DUMPED!\n");
              //  }
      /*          glBindTexture(GL_TEXTURE_2D, sct);
                glColor4f(1.0f,1.0f,1.0f,0.4);
                glBegin(GL_TRIANGLE_STRIP);
                    glTexCoord2f (0.0,0.0); glVertex2f (GLW*0.4,GLH*0.4);
                    glTexCoord2f (0.0,1.0); glVertex2f (GLW*0.4,GLH*0.6);
                    glTexCoord2f (1.0,0.0); glVertex2f (0+GLW*0.6,GLH*0.4);
                    glTexCoord2f (1.0,1.0); glVertex2f (0+GLW*0.6,GLH*0.6);
               glEnd();
*/
            }
      //     glFlush();
        //    glFinish();
          //  SDL_GL_SwapBuffers();
           
  //     glBindTexture(GL_TEXTURE_2D, lsct);
    
           
 

        }
        
        
//        if(drawGLZ)
  //          endGlPif();

       // fprintf(stderr,"drawPif ok!\n");
       // fflush(stderr);
        //prepareDefSeqNo2();
        //SeqNo2
        
        break;
        
        case 6: drawSound(screen);break;
        
        case 7:
        
        
     //   drawMask(screen,mask2,0.7,0,255,0);
     //    fade(screen,128);
     //    lines(mask2,1);
      //   linesDraw(screen,1);
        
        drawSpector(screen,0,0,screen->w/2,screen->h/2,sound_freq,sound_a,Nmax,1000.);
        drawSpector(screen,screen->w/2,0,screen->w-1,screen->h/2,b_sound_freq,b_sound_a,Nmax,1.);

        drawSpector(screen,0,screen->h/2,screen->w/2,screen->h-1,c_sound_freq,c_sound_a,Nmax,1.);
        drawSpector(screen,screen->w/2,screen->h/2,screen->w-1,screen->h-1,d_sound_freq,d_sound_a,Nmax,1.);

        
         break;
        case 8:
            int d;
          d=(screen->w-screen->h);            
            drawQs(screen,d,0,screen->w,screen->h-1,&qsAll);
     
     
     ////     calcOqColorline(qsAll);
     //     drawOqColorLines(screen);
            
     //       drawQsDis(screen,0,0,d,d);   
            break;
     case 0:
           // int d;
         
     
        //   calcOqColorline(qsAll);
           drawOqColorLines(screen);
            
     //       drawQsDis(screen,0,0,d,d);   
            break;
     case 9:
          drawSoundField();  
            break;
     
        default: 
         drawStars(screen);break;
        
    }
   // drawPifagor(filter,10+rand()%5);
   // drawPiano(filter,4+rand()%3);
   // addNoise(filter,10,255,0);
    if(mode!=6)
        rgbMixer(screen,filter,(rgbMixerDepth==11)?ascell(0,frames):rgbMixerDepth ,frames*M_PI/100.0);
    
    moveNoise(screen,moveNoiseDiv,moveNoiseCount);
    frames++;  
    
    holdFPS(60);  
    //if(filterMegaFlag){
        //filtermega(screen,outputScreen,controlMega(sk));
        //for(int i=0;i<screen->h;i++){
         //   memcpy(((char*)screen->pixels)+i*(screen->w*4+screen->pitch),((char*)outputScreen->pixels)+i*(outputScreen->w*4+outputScreen->pitch),screen->w*4);
       // }

      //  for(int x=0;x<screen->w;x++){
        //    for(int y=0;y<screen->h;y++){
          //      putpixel(screen,x,y,getpixel(outputScreen,x,y));
            //}
        
      //  }
  //      memcpy(screen->pixels,outputScreen->pixels,screen->h*(screen->w*4+screen->pitch));
        
        
//        SDL_Flip( outputScreen ); 
        //SDL_Flip( screen ); 
    //} else{
    if(mode!=9 && !drawGLZ && GLDRAW){
        GLShowScreen(screen);
    }
   //     SDL_Flip( screen ); 
    //}
    GLenum err;
            err=glGetError();
            if(err!=GL_NO_ERROR){
                fprintf(stderr,"GLERR:%d\n",(int)err);
            
            }else{
//               fprintf(stderr,"GL NO ERRORS!!\n");
            }
}
int moveTimes=1;
void move(double*sk){
int i,j;
    for(j=0;j<moveTimes;j++){
    switch(mode){
        case 1:for(i=0;i<3;i++) moveSnake();break;   
        case 2:moveHohloma();break;   
        case 3:move4d();break;
        case 4:movebarcode();break;   

    }

}
}
SDL_Surface* screen= NULL;
void setMode(int newMode){
        if(mode==2&&newMode!=2){
            closeHohloma();     
        }
        if(mode == 3 && newMode!=3){
            close4d();
        }
        if(mode == 4 && newMode!=4){
            checkBars();
        }
        
        switch(newMode){
            case 1:if(mode==1)
                    break;
                    
                if(modeData!=NULL){
                    free(modeData);
                }
                modeData=malloc(2*sizeof(snake));
                if(modeData!=NULL){
                    mode=1;
                    zeroSnake();                    
                }
                break;
              case 2:if(mode==2)
                        break;
                    mode=2;
                    zeroHohloma(screen);
                break;  
              case 3:if(mode==3)
                        break;
                    mode=3;
                    init4d();
                break;  
                case 4:if(mode==4)
                        break;
                    mode=4;
                    initbarcode(screen);
                break; 
                case 5:if(mode==5)
                        break;
                    mode=5;
                   // initslcf();
                break;
              default:if(mode==newMode)
                        break;
                    if(modeData!=NULL){
                        free(modeData);
                       
                    }
                    modeData=NULL;
                    mode=newMode;
                   break;   
            
            
        }


}



int execConfig(const char*s){
    FILE*f;
    char st[1024];
    f=fopen(s,"rt");
    if(f==NULL){
        printf("Can't exec \"%s\"\n",s);
        return 1;
    }
    while(!feof(f)){
        fgets(st,1023,f);
        syntaxControll(st);
    }
    fclose(f);
    return 1;
}
#include"screenshoot.cpp"
int syntaxControll(char*p){
    char term[256];
    char buf[256];
    int t1,i,t2;
    char s1[256];
    char s2[256];
    double t,a,z,f;
   // printf("SyntaxControll:%s\n",p);

   
    while(*p){
        sscanf(p,"%s",term);
        p+=skeep(p);
        if(!strcmp(term,"setColorSeq3")){
            p+=readColorSeq3(p);
        }
        
        if(!strcmp(term,"empty")){
            lastRecive=GetTickCount();
        }
        if(!strcmp(term,"osd")){
            osd=recvLayer(osd,p);
        
        }
        
        if(!strcmp(term,"connect")){
            lastRecive=GetTickCount();
            connected=1;
            printf("connect\n");
            fflush(stdout);
        }
        if(!strcmp(term,"disconnect")){
            connected=0;
            printf("disconnect\n");
            fflush(stdout);
        }
        
        
        
        
        
        if(!strcmp(term,"getmode")){
            printf("mode %d\n",mode);
            fflush(stdout);
           // SVIDanswer(buf);
        }
        if(!strcmp(term,"exec")){
           sscanf(p,"%s",buf);
           p+=skeep(p);
           execConfig(buf);
        }
        if(!strcmp(term,"setVideoRecFolder")){
           sscanf(p,"%s",videoRecFolder);
           p+=skeep(p);
//           execConfig(buf);
        }
        if(!strcmp(term,"screenShoot")){
           int n;
           sscanf(p,"%d",&n);
           p+=skeep(p);
           startScreenShoot(n);
           fprintf(stderr,"screenning%d\n",n);
        }
        
        if(!strcmp(term,"exit")){
            printf("Exiting\n");
            return 1;
           // SVIDanswer(buf);
        }
        if(!strcmp(term,"setascell")){
            
           // //printf("(%s)\n",p);
           sscanf(p,"%d",&t1);
           p+=skeep(p);
           sscanf(p,"%d",&t2);
           p+=skeep(p);
           
           for(i=0;i<t2;i++){
             sscanf(p,"%lf",&t);
             p+=skeep(p);
             sscanf(p,"%lf",&a);
             p+=skeep(p);
             sscanf(p,"%lf",&z);
             p+=skeep(p);
             sscanf(p,"%lf",&f);
             p+=skeep(p);
             if(i==0){
                setAscellator(t1,t,a,z,f);
             }else{
                addAscellator(t1,t,a,z,f);
             }
           // printf("%lf %lf %lf %lf\n",t,a,z,f);
           }
           
           
//           printf("moveTimes:%d\n",moveTimes);
          //  p+=skeep(p);
//            setMode(t1,screen);
            
            
           // SVIDanswer(buf);
        }
        
        if(!strcmp(term,"movetimes")){
            
            //printf("(%s)\n",p);
            sscanf(p,"%d",&moveTimes);
           printf("moveTimes:%d\n",moveTimes);
            p+=skeep(p);
//            setMode(t1,screen);
            
            
           // SVIDanswer(buf);
        }
        if(!strcmp(term,"setnoise")){
           sscanf(p,"%d %d %d",&noiseC,&noiseV,&noiseColor);
          // printf("noise:%d %d %d\n",noiseC,noiseV,noiseColor);
           p+=skeep(p);p+=skeep(p);p+=skeep(p);
           
        }
        
        if(!strcmp(term,"rgbmixer")){
            
            //printf("(%s)\n",p);
            sscanf(p,"%d",&rgbMixerDepth);
            if(rgbMixerDepth>11)
                rgbMixerDepth=11;
            if(rgbMixerDepth<0)
                rgbMixerDepth=0;
            printf("rgbMixerDepth:%d\n",rgbMixerDepth);
            p+=skeep(p);
//            setMode(t1,screen);
            
            
           // SVIDanswer(buf);
        }
        
        if(!strcmp(term,"setmode")){
            //printf("(%s)\n",p);
            sscanf(p,"%d",&t1);
            p+=skeep(p);
            setMode(t1);
       
            
        }
        
        if(!strcmp(term,"set")){
            sscanf(p,"%128s",s1);
            p+=skeep(p);
            sscanf(p,"%128s",s2);
            p+=skeep(p);
            if(readValue(s1,s2)){
                printf("Unknown value %s\n",s1);
            
            }
        }
        if(!strcmp(term,"SetMas")){
            double f1;
            sscanf(p,"%128s",s1);
            p+=skeep(p);
            sscanf(p,"%d",&t1);
            p+=skeep(p);
            sscanf(p,"%lf",&f1);
            p+=skeep(p);
            
            if(readMasValue(s1,t1,f1)){
                printf("Unknown mas value %s %d\n",s1,t1);
            }
        }
        if(!strcmp(term,"setOpt")){
            double f1;
            s1[0]=4;
            t1=-32764;
            
            f1=NAN;
            sscanf(p,"%128s",s1);
            
            p+=skeep(p);
            sscanf(p,"%d",&t1);
            p+=skeep(p);
            sscanf(p,"%lf",&f1);
            p+=skeep(p);            
            if(s1[0]!=4 && t1!=-32764 && f1!=NAN){
                if(setOptFromClient(s1,t1,f1)){
                    fprintf(stderr,"Cant setOpt %s %d\n",s1,t1);
                }else{
                    fprintf(stdout,"setLOpt %s %d %lf\n",s1,t1,f1);
                
                }
            }
        }
        if(!strcmp(term,"setLOpt")){
            double f1;
            s1[0]=4;
            t1=-32764;
            
            f1=NAN;
            sscanf(p,"%128s",s1);
            
            p+=skeep(p);
            sscanf(p,"%d",&t1);
            p+=skeep(p);
            sscanf(p,"%lf",&f1);
            p+=skeep(p);            
            if(s1[0]!=4 && t1!=-32764 && f1!=NAN){
               setLOpt(s1,t1,f1);
            }
        }
        
        
        //readMasValue
        
        
        if(!strcmp(term,"writeAllValues")){
            writeAllValues(1);
        
        }
        if(!strcmp(term,"spectrReqest")){
            int w;
            sscanf(p,"%d",&w);
            p+=skeep(p);
            sendSpector(w);        
        }
     //   if(!strcmp(term,"setColorSeq"){
       //     p+=readColorSeq(p);
       // }
        
   
    }
    return 0;
}

#define COMMANDLEN 65536
char command[COMMANDLEN];
int ccur=0;

#define KEY_ESC 9
#define KEY_1 10
#define KEY_2 11
#define KEY_3 12
#define KEY_4 13
#define KEY_5 14
#define KEY_6 15
#define KEY_7 16
#define KEY_8 17
#define KEY_9 18

#define KEY_F1 67
#define KEY_F2 68
#define KEY_F3 69
#define KEY_F4 70
#define KEY_F5 71
#define KEY_F6 72
#define KEY_F7 73
#define KEY_F8 74
#define KEY_F9 75
#define KEY_F10 76
#define KEY_F11 95
#define KEY_F12 96
#define KEY_DELL 119



/*
double pifDeepBass=1/700.;
double pifDeepRithm=1/500;
double pifDeepCur=14./((N + 1) / 2);

double rxMax=1./100.;
double ryMax=1./100.;
*/
int timetowrite=0;
#include"pifkeyboardcontroll.cpp"
#include"soundkeyboardcontroll.cpp"
#include"saveload.cpp"
struct playList*pls=NULL;
int plsn=0;
int curpls=0;
int curRabbit=-100;

void mySaveBMP(SDL_Surface* bitmap,char*name);
#include"bmp2layer.cpp"
int keyboardControll(){
    int i;
    if(keys[KEY_ESC]){
        return 1;
    
    }
    
    if(keys[KEY_F12]==2){
            if(keys[CONTRL]){
                char*p;
                p=saveTimeStamp();
            }else{
                loadNext();
            }
        
        }
    
    if(keys[KEY_F11]==2){
            if(!keys[CONTRL]){
                loadPrev();
            }else{
                saveCurrent();
            }
        
        }
    
    
    
    for(int i=0;i<10;i++){
        if(keys[i+KEY_F1]==2){
            char name[32];
            sprintf(name,"quick_%d.r2",i+1);
            if(keys[CONTRL]){
                save_rabbit(name);
            }else{
                load_rabbit(name);
            }
        
        }
    
    }

    
    
    timeKeyboardControll();
    for(i=KEY_1;i<=KEY_9;i++){
        if(keys[i]){
            setMode(i-KEY_1);
        }    
    
    }
    /*
    if(keys[21]==2){
         moveNoiseDiv++;
   }
   if(keys[20]==2){
        if(moveNoiseDiv)
         moveNoiseDiv--;
    
    }*/
    if(keys[31]==2){
        if(faded>20)
                 faded-=10;
        else if(faded>10)
               faded-=2;
         else
             if(faded>0)
             faded--;
     }  
     
     
                         
    if(keys[32]==2){
           if(faded<10)
              faded++;
           else if(faded<20)
              faded+=2;
           else if(faded<255)
              faded+=10;
           if(faded>255)
              faded=255;
     }
     //RGBMIXER
     /*if(keys[33]==2){
        if(rgbMixerDepth==11) 
            rgbMixerDepth=ascell(0,frames);
     } */  // p
     if(keys[34]==2){
        if(rgbMixerDepth && rgbMixerDepth!=11)
            rgbMixerDepth--;
     }  // [
     if(keys[35]==2){
        if(rgbMixerDepth<10)rgbMixerDepth++;
     }       // ]
     if(keys[51]==2){
        filterMegaFlag=!filterMegaFlag;
     }                         // \
     ///NOISE   noiseC  0..100   ,noiseV 0..255  ,noiseColor 0..1
     
     
     
     if(keys[24]==2){
        if(noiseC<100)noiseC++;
     }                                // q
     if(keys[25]){
        if(noiseV<255)noiseV++;
     }                                // w
     if(keys[38]){
        if(noiseC>0)noiseC--;
     }                                  // a
     if(keys[39]){
        if(noiseV>1)noiseV--;
     }                                  // s
     if(keys[26] == 2){
        noiseColor=!noiseColor;
     }                                // d
                              ///  PIFAGOR
                           //int pifDeep=13;int pifNaked=1;int pifColored=1;
                                   // g
                              
                              
                              
                            /*  default:printf("keydown:%d \n",event.key.keysym.scancode); break;
                              }    break;*/
            


    //if()
    if(keys[KEY_DELL]){
        makeScreenShoot=1;
        timetowrite=1;
        fprintf(stderr,"Making ScreenShot\n");
        fflush(stderr);
        
     
    }
     
    if(timetowrite && ! makeScreenShoot){
        fprintf(stderr,"Copied from gl\n");
        fflush(stderr);
        timetowrite=0;
        char name[128];
        unsigned  int sec= time(NULL);
        sprintf(name,"screenshot/screenshot_%u.bmp",sec);
//      screenShoot=scrshooot(screenShootW,screenShootH);
        if(screenShoot!=NULL){
                fprintf(stderr,"size: %d x %d \n",screenShootW,screenShootH);
                fflush(stderr);
                fprintf(stderr,"name: %s\n",name);
                fflush(stderr);
                
                mySaveBMP(screenShoot,screenShootW,screenShootH, name);
                fprintf(stderr,"Saved to disc\n");
                fflush(stderr);

                free(screenShoot);
                screenShoot=NULL;
                fprintf(stderr,"freeed\n");
                fflush(stderr);

        }else{
            fprintf(stderr,"Error Grabbing screen\n");
        } 
     
    }   
    
    pifKeyboardControll();
    soundKeyboardControll();
    for(i=0;i<256;i++)
        if(keys[i])
            keys[i]=1;
    return 0;
}



unsigned lastLoad=0;
int allowNextPreset(double *k){
    double silence=0.2;
    if(getOpt("autoPlayAllowVolume")>0.001){
        silence=getOpt("autoPlayAllowVolume");
    }
    if(k[0]+k[1]+k[2]>silence)
        return 0;
    return 1;
}
int controll(SDL_Surface *screen){
    SDL_Event event;
    char buf[BUFSIZE+1]="";
    int datasize;
    int msgid,size;
    struct msgp a;
//    if(soundControllFlag){
  //      soundControll();
    
    //}
    processOpenCV();
    doScreenShoot();
    processPaint();
    
    
    if(getOpt("autoPlay")>0.5){
        double time=60;
       // fprintf(stderr,".\n");
        if(plsn<2){
            fprintf(stderr,"Error starting autoPlay, there is no playlists\n");                
            setOpt("autoPlay",0);
        }else{
            if(curpls!=1){
                fprintf(stderr,"Starting autoPlay %d rabbits\n",pls[1].len);                
                curpls=1;
            }
            if(curRabbit<0||curRabbit>=pls[1].len){
                curRabbit=0;
            }
            if(getOpt("autoPlayTime")>0.001){
                time=getOpt("autoPlayTime");
            }
        
            double cfp=30;
            if(currentFps>20)
                cfp=currentFps;
            if(GetTickCount()-lastLoad>time*1000 && allowNextPreset(soundKoefs)){
                char *s;
                lastLoad=GetTickCount();
                if(getOpt("autoPlayShuffle")>0.5){
                    s=loadNextShuffle();
                }else{
                    s=loadNext();
                }
                if(s!=NULL)
                    fprintf(stderr,"autoPlay:%s\n",s);
                else
                    fprintf(stderr,"autoPlay:NULL\n");
                    
            }
        }
    
    }
    
    
   if(rgbMixerDepth == 11){
        int a;
        a=(int)ascell(0,frames);
        if(a!=lastrgbMixerAuto)
            printf("set rgbMixerDepthAuto %d\n",a);
        lastrgbMixerAuto=a;
   }
    writeAllValues();
    
    
    #ifdef NONBLOCK
       int c;
    do{
       c=getc(stdin);
       if(c!=EOF && c!=-1){
           if(c==10){

              command[ccur]=0; 
            //    printf("enter!(%s)\n",command);
              if(syntaxControll(command))
                return 1;
              ccur=0;
           }else{
               if(ccur<COMMANDLEN-1){
                   command[ccur++]=c;
               }else{
                   ccur=0;
               }
           }
       }
    }while(c!=-1);
    #endif


   // size=msgrcv(msgid,&a,sizeof(struct msgp),1,IPC_NOWAIT );
    size=0;
    if(size>0 ){
         syntaxControll(a.s);
     }
    
    
    
    if(mode==1 && checkLokalSnake() && !(rand()%200)){
        setMode(0);
        setMode(1);  
    
    }
    
   /* if(mode==1 && !(rand()%1000)  && !(rand()%30)){
        setMode(0,screen);
        setMode(1,screen);
    }*/
    
    
    while(SDL_PollEvent(&event)){
        switch (event.type) {
            case SDL_KEYDOWN: keys[event.key.keysym.scancode]=2;break;
            case SDL_KEYUP: keys[event.key.keysym.scancode]=0;break;
            
            case SDL_QUIT: return 1; break;
           
        }
    }
    if(keyboardControll())
        return 1;
    
     
    
    
    doServer();
    return 0;
}
void initStdIn(){
#ifdef NONBLOCK

    int flags;
    flags = fcntl(0, F_GETFL); /* get current file status flags */
    flags |= O_NONBLOCK;		/* turn off blocking flag */
     fcntl(0, F_SETFL, flags);		/* set up non-blocking read */
 #endif

}


double maxkoefs[KOEFNUM];
double minkoefs[KOEFNUM];

void acc(double *koefs,double*speed,int n){
    int i;
    for(i=0;i<n;i++){
        if(maxkoefs[i]<koefs[i]){
            maxkoefs[i]=koefs[i];        
        }
        if(minkoefs[i]>koefs[i]){
            minkoefs[i]=koefs[i];        
        }
        maxkoefs[i]=(maxkoefs[i]*speed[i]+koefs[i])/(speed[i]+1);
        minkoefs[i]=(minkoefs[i]*speed[i]+koefs[i])/(speed[i]+1);
        if(maxkoefs[i]-minkoefs[i]<0.0001){
            maxkoefs[i]=minkoefs[i]+0.0001;
        }
        koefs[i]=(koefs[i]-minkoefs[i])/(maxkoefs[i]-minkoefs[i]);
    }    
}


int main( int argc, char* args[] ) { 
    int i,x,y,c,flag,windowflag,windowXRes,windowYRes,window2XRes,window2YRes;
    //The images 
    mysignal=initSignal(12,10);
    
    qsl.p=NULL;
    int doumode=0;
    SDL_Surface* hello = NULL; 
    //SDL_Surface* screen = NULL;
    SDL_Surface* filter = NULL;
    SDL_Surface *trueScreen = NULL ;
    SDL_Surface *controllscreen=NULL;
    int windowXPos,windowYPos;
    const SDL_VideoInfo* myPointer;
    modeData=NULL;
    windowflag=0;
    flag=1;
    int preparefade=0;
    int noframe=0;
//    openVideo("");
    srand (time(NULL));
    SDL_putenv((char*)"SDL_VIDEO_WINDOW_POS=0,0");
    initStdIn();
    initServer ();
    startBoratcaser();
    int bitmapResX,bitmapResY;
    bitmapResX=-1;
    pls=loadPlaylists(plsn);    
  //  loadVideoPlaylist();
   startOCVProcess();
    for(i=1;i<argc;i++){
        fprintf(stderr,"Catch:%s\n",args[i]);
        if(!strcmp(args[i],"-aspectKoef") && i+1<argc){
            i++;
            sscanf(args[i],"%lf",&aspectKoef);

            fprintf(stderr,"aspectKoef (%f)\n",aspectKoef);

        }
        if(!strcmp(args[i],"-snake") && i+1<argc){
            snake=1;
            fprintf(stderr,"Turning into SNAKE mode\n");
            
        }
        if(!strcmp(args[i],"-window") && i+1<argc){
            windowXRes=-1;
            windowYRes=-1;
            i++;
            sscanf(args[i],"%dx%d",&windowXRes,&windowYRes);
            if(windowXRes > 0 && windowYRes > 0 ){
                windowflag=1;  
     
            }
            fprintf(stderr,"wind(%dx%d)\n",windowXRes,windowYRes);

        }
        if(!strcmp(args[i],"-calcbitmap") && i+1<argc){
            bitmapResX=-1;
            bitmapResY=-1;
            i++;
            sscanf(args[i],"%dx%d",&bitmapResX,&bitmapResY);
//            if(bitmapResX > 0 && bitmapResY > 0 ){
  //              windowflag=1;  
    // 
      //      }
        }
        if(!strcmp(args[i],"-noframe")){
            noframe=1;
        }
        if(!strcmp(args[i],"-preparefade")){
            preparefade=1;
        }
        
        if(!strcmp(args[i],"-position") && i+1<argc){
            windowXPos=-1;
            windowYPos=-1;
            i++;
            sscanf(args[i],"%dx%d",&windowXPos,&windowYPos);
            printf("Set position:%d x %d",windowXPos,windowYPos);
        }
         
    
    }

    // initPipes();
     //Start SDL 
     if(windowXPos >= 0 && windowYPos >= 0 ){
                char tmps[128];
                sprintf(tmps,"SDL_VIDEO_WINDOW_POS=%d,%d",windowXPos,windowYPos);
                SDL_putenv(tmps);
                printf("%s\n",tmps);
     }
     SDL_Init( SDL_INIT_EVERYTHING ); 
     //Set up screen 
    if(initSound()){
        fprintf(stderr,"cant init sound\n");
//        fflush (stdout);
    }
//     if(initMyPlay()){
  //      fprintf(stderr,"cant init myplay\n");
  //      fflush (stdout);
     
    // }
     
     
     zeroAsc();
     myPointer = SDL_GetVideoInfo();
     W=myPointer->current_w;
     H=myPointer->current_h;
     if(windowflag){
        W=windowXRes;
        H=windowYRes;
     }        
     GLW=W;
     GLH=H;
     REALW=W;
     REALH=H;
     if(bitmapResX>0 && bitmapResY>0){
        GLW=bitmapResX;
        GLH=bitmapResY;
        W=GLW;
        H=GLH;
     }
     fprintf(stderr,"Making Gl surface %dx%d\n",REALW,REALH);

     SDL_Surface *glScreen = NULL ;

        
        
     glScreen = SDL_SetVideoMode(REALW , REALH, 32, SDL_HWSURFACE |  ((windowflag&&(!doumode))&&(!noframe)?0:SDL_NOFRAME)|SDL_GL_DOUBLEBUFFER |SDL_OPENGL );     
// glScreen = SDL_SetVideoMode(GLW , GLH, 32, SDL_HWSURFACE |  ((windowflag&&(!doumode))&&(!noframe)?0:SDL_NOFRAME)|SDL_GL_DOUBLEBUFFER |SDL_OPENGL ); 
//     fprintf(stderr,"Making Gl surface %dx%d\n",GLW,GLH);
     screen = CreateSurface(0,W,H,glScreen);
//     IMG_Init(IMG_INIT_PNG);
     
     preparePutPixel(screen);
//     outputScreen=cloneScreen(screen);
     screenW=screen->w;
     screenH=screen->h;
     diag=sqrt(screenH*screenH+screenW*screenW);
     
     
     filter=cloneScreen(screen);
     initFade(screen);
     if(filter==NULL){
        printf("Cant create filter surface\n");
        return 1;
     }
     SDL_ShowCursor(0);
// drawPifagor(filter);
     drawPiano(filter,8);
     zerroTable();
     if(preparefade){
        prepareFade(screen,filter);
     }

     mode=0;
     G=6;
     L=0.0001;
     M=0.001;
     SNL=3;
     K=0.001;
     C=10;

     setMode(2);
     execConfig("config");
    
    // setNetcontroll();
// plog("before zerro");
 setZeroPifControllKoef();
// plog("before load current");

 if(!snake){
     load_rabbit("current.r2");
 }else{
     load_rabbit("current_snake.r2");
 
 
 }
 Uint32 lcontroll=0;
    init_GL();
    int pary;
     while(flag){
        //printf("draw\n");
        //fflush(stdout);
      //  plog("rabbit loop");
        pary++;
        if(getOpt("myplay")>=0.5||snake){
            playMyPlay();
        }
        if(!snake && !calcSound_new(soundKoefs)){
//         if(!viewFreqs(soundKoefs)){
        
           acc(soundKoefs,accspeed,KOEFNUM);
        
//        fprintf(stderr,"draw!\n");
  //      fflush(stderr);
              draw(screen,filter,soundKoefs);
    //    fprintf(stderr,"draw! ok\n");
      //  fflush(stderr);
       
       // printf("move\n");
        //fflush(stdout);
       // for(i=0;i<10;i++)
            move(soundKoefs);
        }

 //       if(pary%2){
          
          if(GetTickCount()-lcontroll>60){
            lcontroll=GetTickCount();
            if(controll(screen)  /*|| getOpt("exit")>0.5*/){
                
                break;
            }       
          }
   //     }
      // printf("%lf\n",pifColorSpeedr); 
     }
     

     
      //Quit SDL 
      fprintf(stderr,"Saving current\n");fflush(stderr);
 if(!snake){
      save_rabbit("current.r2");
 }else{
      save_rabbit("current_snake.r2");
 }


      fprintf(stderr,"Closing sound\n");fflush(stderr);
      closeSound();
      fprintf(stderr,"Closing rgbmixer\n");fflush(stderr);
      closeRgbMixer();
      fprintf(stderr,"Closing fades\n");fflush(stderr);
      closeFades();
      fprintf(stderr,"Closing SDL\n");fflush(stderr);
      SDL_Quit();
      fprintf(stderr,"Closing dynamic options\n");fflush(stderr);
      freeOpts();      
      fprintf(stderr,"Closing IP server\n");fflush(stderr);

      closeServer();

      fprintf(stderr,"Closing openCV module\n");fflush(stderr);
//      closeVideo();



      fprintf(stderr,"All correct!\n");fflush(stderr);
      printf("%c",EOF); 
      return 0;
}
