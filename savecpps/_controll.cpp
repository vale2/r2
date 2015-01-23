int mode=5;
#define CONTRL  37

#define min(x,y)  (((x)>(y))?(y):(x))
#define CCORLEN (7+6)
#include"glopts.cpp"
int syntaxControll(char*p);

int showColorSeq=1;
double pifColorSpeedr=0.01;
double pifColorSpeedg=0.01;
double pifColorSpeedb=0.01;
double fraqFilter=0.;

#include <SDL/SDL.h>
Uint32 lastRecive;

//#include "SDL_opengl.h"
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <time.h> 

#include <fcntl.h>
int H,W;
#include "graphutil.cpp"
#include "piano.cpp"


#include"koefs.cpp"
#include"mousecontroll.cpp"




short int keys[256];
int soundControllFlag=0;

//int currentFps;

#include"colors.cpp"
double hearingVolume;
double amplifierKoef=100;
double amplifierKoefHighValue=1.5;
double amplifierKoefLowValue=1000;
int faded=50;
int orblurd=0;
int rgbMixerDepth=10;
int rgbMixerDepthAuto=0;
int noiseC=0;
int noiseV=0;
int noiseColor=0;



#include "timeutil.cpp"
#include"drawcurrent.cpp"
#include "soundutil.cpp"
#include "sendrecive.cpp"
#include "saveload.cpp"


#define KEY_ESC 9
#define KEY_1 10
#define KEY_2 11
#define KEY_3 12
#define KEY_4 13
#define KEY_5 14
#define KEY_6 15
#define KEY_7 16

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





int pifDeep=13;
int pifNaked=1;
int pifColored=1;
double pifDWind=1/100000.0;
double pifDScale=1;
double pifDAngle=M_PI/10000;


int pifPosition=1;





int lpifDeep=13;
int lpifNaked=1;
int lpifColored=1;
double lpifDWind=1/100000.0;
double lpifDScale=1;
double lpifDAngle=M_PI/10000;
/*double lpifColorSpeedr=0.01;
double lpifColorSpeedg=0.01;
double lpifColorSpeedb=0.01;

*/
int lpifPosition=1;



    


int pageScreen=0;
#include"colors.cpp"

Uint32 frames=0;
int slowWork=0;
void takeItEasy(){
   struct timespec tw = {0,30};
   struct timespec tr;
   nanosleep (&tw, &tr);

}

void checkZerro(){
     if(fabs(pifDWind)<0.00000016)
         pifDWind=0.00000016;


}

#include"pifkeyboardcontroll.cpp"
#include"soundkeyboardcontroll.cpp"
#include"editpannels.cpp"

void incFilterPannelValue(int pannel,int param){
    param=param%LAYEROPTS;
    layerOpt[param]=layerOpt[param]+0.02;
    if(layerOpt[param]>1.)
        layerOpt[param]=1.;
    

}
void decFilterPannelValue(int pannel,int param){
    param=param%LAYEROPTS;
    layerOpt[param]=layerOpt[param]-0.02;
    if(layerOpt[param]<0.)
        layerOpt[param]=0.;
    

}
void incPannelValue(int pannel,int param){
    double d;
    double v;
    if(panel_no[pannel]<0){
        incFilterPannelValue(pannel,param);
        return;
    }
    
    pannel=panel_no[pannel];
    d=maxPannelValue[pannel]/20.;
    if(param==0){
        if(maxDrawKoef[pannel]<-d||maxDrawKoef[pannel]>-0.000001){
                    maxDrawKoef[pannel]=d+maxDrawKoef[pannel];
        }else{
            maxDrawKoef[pannel]=0.0;
        }
    }else
    if(param==1){
        if(zeros[pannel]<-d||zeros[pannel]>-0.000001){
                    zeros[pannel]=d+zeros[pannel];
        }else{
            zeros[pannel]=0.0;
        }
    }else if(param==2){
        if(drawLatKoef[pannel]<-d||drawLatKoef[pannel]>-0.000001){
                    drawLatKoef[pannel]=drawLatKoef[pannel]+d;
        }else{
            drawLatKoef[pannel]=0.0;
        }
    }else{
        param=param-PREGDOEFS;
        v=controllKoef[pannel*KOEFNUM+param];
        if(v<-d||v>-0.000001){
                    v=d+v;
        }else{
            v=0.0;
        }
        controllKoef[pannel*KOEFNUM+param]=v;
    }
}

void decPannelValue(int pannel,int param){
    double d;
    double v;
    if(panel_no[pannel]<0){
        decFilterPannelValue(pannel,param);
        return;
    }

    pannel=panel_no[pannel];
    d=maxPannelValue[pannel]/20.;
    if(param==0){
        if(maxDrawKoef[pannel]>d||maxDrawKoef[pannel]<0.000001){
                    maxDrawKoef[pannel]=maxDrawKoef[pannel]-d;
        }else{
            maxDrawKoef[pannel]=0.0;
        }
    }else
    if(param==1){
        if(zeros[pannel]>d||zeros[pannel]<0.000001){
                    zeros[pannel]=zeros[pannel]-d;
        }else{
            zeros[pannel]=0.0;
        }
    }else if(param==2){
        if(drawLatKoef[pannel]>d||drawLatKoef[pannel]<0.000001){
                    drawLatKoef[pannel]=drawLatKoef[pannel]-d;
        }else{
            drawLatKoef[pannel]=0.0;
        }
    }else{
        param=param-PREGDOEFS;
        v=controllKoef[pannel*KOEFNUM+param];
        if(v>d||v<0.000001){
                    v=v-d;
        }else{
            v=0.0;
        }
        controllKoef[pannel*KOEFNUM+param]=v;
    }
}

void interfaceKeyboardControll(){

    if(keys[KEY_F12]==2){
            if(keys[CONTRL]){
                char*p;
                p=saveNext();
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
  
  
    if(keys[65]==2){
        pageScreen++;
        pageScreen=pageScreen&1;
//        printf("pageScreen chanGet to %d\n",pageScreen);
    }
    
    if(keys[113]==2){
        if(keys[50]){
            curEditPannel=curEditPannel+ PANNELS -1;
            curEditPannel=curEditPannel%PANNELS;
        }else{
            curEditParam=curEditParam+ DRAWKOEFNUM -1;
            curEditParam=curEditParam%DRAWKOEFNUM;
        
        }

    }
    if(keys[114]==2){
        if(keys[50]){
            curEditPannel=curEditPannel+ 1;
            curEditPannel=curEditPannel%PANNELS;
        }else{
            curEditParam=curEditParam+1;
            curEditParam=curEditParam%DRAWKOEFNUM;
        
        }

    }
    if(keys[111]==2){
            incPannelValue(curEditPannel,curEditParam);

    }
    if(keys[116]==2){
            decPannelValue(curEditPannel,curEditParam);

    }
    
    
//    113//left
  //  111//up
    //114//right
   // 116//down


}
void mouseControll(){
    


}
int keyboardControll(){
    int i;
    if(pageScreen==1){
        printf("spectrReqest %d\n",300);
    
    }
    
    
    if(keys[KEY_ESC]){
        return 1;
    
    }
    
    interfaceKeyboardControll();
    
    
    
   /* for(i=KEY_1;i<=KEY_6;i++){
        if(keys[i]){
            setMode(i-KEY_1);
        }    
    
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
/*     if(keys[33]==2){
        if(rgbMixerDepth==11) 
            rgbMixerDepth=0;
     } */  // p
     if(keys[34]==2){
        if(rgbMixerDepth && rgbMixerDepth!=11)
            rgbMixerDepth--;
     }  // [
     if(keys[35]==2){
        if(rgbMixerDepth<10)rgbMixerDepth++;
     }       // ]
     if(keys[51]==2){
       // filterMegaFlag=!filterMegaFlag;
     }                         // \
                     // \
     ///NOISE   noiseC  0..100   ,noiseV 0..255  ,noiseColor 0..1
     if(keys[24]){
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
    soundKeyboardControll();
    if(pageScreen==0){
        pifKeyboardControll();
        mouseControll();
    }
    for(i=0;i<256;i++)
        if(keys[i])
            keys[i]=1;
    return 0;
}


#define LEPS 0.0000000001
void writeAllValues(){
    printf("empty\n");
    
    writeSoundControllValue();
    writeVolume();
    sendMas("colorCorrector",stdout,1);
    sendAllMass();
    sendFilters();
 //   if(connected && showColorSeq){
//        writeColorSeq();
     //   writeColorSeq3();
   // }
   
   
   
    if(fabs(pifDWind-lpifDWind)>LEPS)
        printf("set pifDWind %lf,%lf\n",pifDWind,lpifDWind);
    if(fabs(pifDScale-lpifDScale)>LEPS)
        printf("set pifDScale %lf\n",pifDScale);
    if(fabs(pifDAngle-lpifDAngle)>LEPS)
        printf("set pifDAngle %lf\n",pifDAngle);
    if(fabs(pifColorSpeedr-lpifColorSpeedr)>LEPS)
        printf("set pifColorSpeedr %lf\n",pifColorSpeedr);
    if(fabs(pifColorSpeedg-lpifColorSpeedg)>LEPS)
        printf("set pifColorSpeedg %lf\n",pifColorSpeedg);
    if(fabs(pifColorSpeedb-lpifColorSpeedb)>LEPS)
        printf("set pifColorSpeedb %lf\n",pifColorSpeedb);
    
    
    
    if(faded!=lfaded)
        printf("set faded %d\n",faded);
    if(rgbMixerDepth!=lrgbMixerDepth)
        printf("set rgbMixerDepth %d\n",rgbMixerDepth);
    if(noiseC!=lnoiseC)
        printf("set noiseC %d\n",noiseC);
    if(noiseV!=lnoiseV)
        printf("set noiseV %d\n",noiseV);
    if(noiseColor!=lnoiseColor)
        printf("set noiseColor %d\n",noiseColor);
    if(pifDeep!=lpifDeep)
        printf("set pifDeep %d\n",pifDeep);
 
    if(pifNaked!=lpifNaked)
        printf("set pifNaked %d\n",pifNaked);
    if(pifColored!=lpifColored)
        printf("set pifColored %d\n",pifColored);
    if(pifPosition!=lpifPosition)
        printf("set pifPosition %d\n",pifPosition);
    //printf("%c\n",4);
    fflush(stdout);
    
    
 lfaded=faded;
 lrgbMixerDepth=rgbMixerDepth;
 lnoiseC=noiseC;
 lnoiseV=noiseV;
 lnoiseColor=noiseColor;


 lpifDeep=pifDeep;
 lpifNaked=pifNaked;
 lpifColored=pifColored;
 lpifDWind=pifDWind;
 lpifDScale=pifDScale;
 lpifDAngle=pifDAngle;
 lpifColorSpeedr=pifColorSpeedr;
 lpifColorSpeedg=pifColorSpeedg;
 lpifColorSpeedb=pifColorSpeedb;


 lpifPosition=pifPosition;
}

int readRawSoundData(char*name,char*value){
  /*
double lbassrithm=-100;
double lmelodyrithm=-100;
double lallrithm=-100;
int lmtarget=-100;
int ltarget=-100;
double lrx=-100;
double lry=-100;
double lrxy=-100;
*/
    
    if(!strcmp(name,"bassrithm")){
        sscanf(value,"%lf",&bassrithm);
        //lbassrithm=bassrithm;
        
        return 0;
    }

    if(!strcmp(name,"melodyrithm")){
        sscanf(value,"%lf",&melodyrithm);
        //lmelodyrithm=melodyrithm;
        
        return 0;
    }
    if(!strcmp(name,"allrithm")){
        sscanf(value,"%lf",&allrithm);
        //lallrithm=allrithm;
        
        return 0;
    }




    if(!strcmp(name,"mtarget")){
        sscanf(value,"%d",&mtarget);
        //lmtarget=mtarget;
        
        return 0;
    }
    if(!strcmp(name,"target")){
        sscanf(value,"%d",&target);
        //ltarget=target;
        
        return 0;
    }


    if(!strcmp(name,"rx")){
        sscanf(value,"%lf",&rx);
        //lrx=rx;
        
        return 0;
    }

    if(!strcmp(name,"ry")){
        sscanf(value,"%lf",&ry);
        //lry=ry;
        
        return 0;
    }
    if(!strcmp(name,"rxy")){
        sscanf(value,"%lf",&rxy);
        //lrxy=rxy;
        return 0;
    }


   

    return -1;
}



int readValue(char*name,char*value){

   
    if(!readRawSoundData(name,value)){
        return 0;
    }
    if(!readSoundControllValue(name,value)){
        return 0;
    }
    
    if(!strcmp(name,"autoPifDeep")){
        sscanf(value,"%d",&autoPifDeep);
        lautoPifDeep=autoPifDeep;
        return 0;
    }

    
    
    if(!strcmp(name,"currentFps")){
        sscanf(value,"%d",&currentFps);
       // lhearingVolume=hearingVolume;
       //printf("hearingVolume to %f!",hearingVolume);
        return 0;
    }
    
    
    if(!strcmp(name,"hearingVolume")){
        sscanf(value,"%lf",&hearingVolume);
       // lhearingVolume=hearingVolume;
       //printf("hearingVolume to %f!",hearingVolume);
        return 0;
    }
    
    
    

    
    if(!strcmp(name,"amplifierKoef")){
        sscanf(value,"%lf",&amplifierKoef);
       // lamplifierKoef=amplifierKoef;
        return 0;
    }

    
    
    
    
   if(!strcmp("rithmp",name)){
       
       sscanf(value,"%d",&rithmp);
       
     
   
   }
   
    
    if(!strcmp(name,"pifDWind")){
        sscanf(value,"%lf",&pifDWind);
        lpifDWind=pifDWind;
        return 0;
    }
    if(!strcmp(name,"rgbMixerDepthAuto")){
        sscanf(value,"%d",&rgbMixerDepthAuto);
//        lpifDWind=pifDWind;
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
    if(!strcmp(name,"orblurd")){
        sscanf(value,"%d",&orblurd);
        lorblurd=orblurd;
        return 0;
    }

    if(!strcmp(name,"faded")){
        sscanf(value,"%d",&faded);
        lfaded=faded;
        
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
        lpifColored=lpifColored;
        return 0;
    }

    return 1;
}
int connectflag=0;
#include"screenshoot.cpp"
int connected;
int syntaxControll(char*p){
    char term[256];
    char buf[256];
    int t1,i,t2;
    char s1[256];
    char s2[256];
    double t,a,z,f;
   // printf("SyntaxControll:%s\n",p);
    lastRecive= GetTickCount();
    while(*p){
        term[0]=0;
        sscanf(p,"%s",term);
        p+=skeep(p);
        
        
       if(!strcmp(term,"setmode")){
            int t1;
            sscanf(p,"%d",&t1);
            p+=skeep(p);
            mode=t1;
        }

        
        if(!strcmp(term,"setSpector")){
            reciveSpector(p);
        }
        if(!strcmp(term,"setColorSeq3")){
            p+=readColorSeq3(p);
        }

        
        if(!strcmp(term,"SetMas")){
            int n;
            double v;
            sscanf(p,"%128s",s1);
            p+=skeep(p);
            sscanf(p,"%d",&n);
            p+=skeep(p);
            sscanf(p,"%lf",&v);
            p+=skeep(p);
            readMasValue(s1,n,v);
        }
        if(!strcmp(term,"setLOpt")){
/*            double f1;
            sscanf(p,"%128s",s1);
            p+=skeep(p);
            sscanf(p,"%d",&t1);
            p+=skeep(p);
            sscanf(p,"%lf",&f1);
            p+=skeep(p);            
            if(setOpt(s1,t1,f1)){
                printf("Cant setOpt %s %d\n",s1,t1);
            }*/
            int n;
            double v;
            s1[0]=4;
            n=-32764;
            v=NAN;

            sscanf(p,"%128s",s1);
            p+=skeep(p);
            sscanf(p,"%d",&n);
            p+=skeep(p);
            sscanf(p,"%lf",&v);
            p+=skeep(p);
            if(s1[0]!=4 && n!=-32764 && v!=NAN){
                if(!setLOpt(s1,n,v)){
//                    fprintf("setLOpt %s %d %lf\n",s1,n,v);
                }
            }
        }

        if(!strcmp(term,"setOpt")){
/*            double f1;
            sscanf(p,"%128s",s1);
            p+=skeep(p);
            sscanf(p,"%d",&t1);
            p+=skeep(p);
            sscanf(p,"%lf",&f1);
            p+=skeep(p);            
            if(setOpt(s1,t1,f1)){
                printf("Cant setOpt %s %d\n",s1,t1);
            }*/
            int n;
            double v;
            s1[0]=4;
            n=-32764;
            v=NAN;

            sscanf(p,"%128s",s1);
            p+=skeep(p);
            sscanf(p,"%d",&n);
            p+=skeep(p);
            sscanf(p,"%lf",&v);
            p+=skeep(p);
            if(s1[0]!=4 && n!=-32764 && v!=NAN){
                if(!setOptFromClient(s1,n,v)){
                    fprintf(stdout,"setLOpt %s %d %lf\n",s1,n,v);
                }
            }
        }
        if(!strcmp(term,"screenShoot_init")){
            int a,b,c;
            fprintf(stderr,"sss_init:%s\n",p);
            sscanf(p,"%d",&a);
            p+=skeep(p);
            sscanf(p,"%d",&b);
            p+=skeep(p);
            sscanf(p,"%d",&c);
            p+=skeep(p);
            initDSS(a,b,c);
        }
        if(!strcmp(term,"screenShoot_pixel")){
            int a;
            unsigned int b;
            sscanf(p,"%d",&a);
            p+=skeep(p);
            sscanf(p,"%u",&b);
            p+=skeep(p);
            pixelDSS(a,b);
        }
        
        if(!strcmp(term,"connect")){
            connectflag++;
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
        if(!strcmp(term,"writeAllValues")){
            writeAllValues();
        
        }
        if(!strcmp(term,"setColorSeq")){
            p+=readColorSeq(p);
        }
        
   
    }
    opts2koefsAr16();
    return 0;
}





SDL_Surface* screen= NULL;

void initStdIn(){


    int flags;
    flags = fcntl(0, F_GETFL); /* get current file status flags */
    flags |= O_NONBLOCK;		/* turn off blocking flag */
     fcntl(0, F_SETFL, flags);		/* set up non-blocking read */


}


#include"drawcontroll.cpp"


void modifyMode(){
    mode=butParam;
}


void drawAddons(SDL_Surface*screen,double x1,double y1,double x2,double y2){
    x1*=screen->w;
    y1*=screen->h;
    x2*=screen->w;
    y2*=screen->h;
    double w,h,xm,rx2;
    w=(x2-x1);
    xm=(x1+x1+x2)/3;
    h=y2-y1;
    rx2=x2;
    x2=x1+w*2/3;
    

    bar(screen,x1,y1,xm,y1+h/3,GREEN);
    addButton(x1,y1,xm,y1+h/3,0,rizeQslControll);

    bar(screen,x1,y1+h/3,xm,y1+2*h/3,CYAN);
    addButton(x1,y1+h/3,x2,y1+2*h/3,0,rizeQsPlateControll);

    bar(screen,x1,y1+2*h/3,xm,y2,BLUE);
    addButton(x1,y1+2*h/3,xm,y2,0,rizeQsSurfControll);


    bar(screen,xm,y1+h/3,x2,y1+2*h/3,WHITE);
    addButton(xm,y1+h/3,x2,y1+2*h/3,0,rizeTouchControll);


    bar(screen,xm,y1,x2,y1+h/3,YELLOW);
    addButton(xm,y1,x2,y1+h/3,0,rizeSoundSpeqControll);

    bar(screen,xm,y1+2*h/3,x2,y2,CYAN);
    addButton(xm,y1+2*h/3,x2,y2,0,rizeSoundSpeqSquareControll);



    bar(screen,x2,y1,rx2,y1+h/3,RED);
    addButton(x2,y1,rx2,y1+h/3,0,rizedrawLifeControll);




}
void placeMyplayControll(int x1,int y1,int x2,int y2,SDL_Surface*screen){
    bar(screen,x1,y1,x2,y2,MAGENTA);
    addButton(x1,y1,x2,y2,0,rizeMyplayControll);
}
void drawPifControll(SDL_Surface*screen){

    SDL_FillRect(screen,NULL, 0x000000);
        
    drawNoise(0,0,3*screen->w/13,2*screen->h/3,screen);
    //  drawColorSpeed(3*screen->w/13,0,6*screen->w/13-1,screen->h/3,screen);
    drawSaveLoadButts(8*screen->w/13,screen->h/8,screen->w-1,screen->h/4,screen);

    drawPiano(8*screen->w/13,screen->h/4,11*screen->w/13,screen->h/3,screen);
    //drawMoveSpeed(7*screen->w/10,screen->h/3,screen->w-1,screen->h-1,screen);
    
    
    drawSubFraqControll(0,2*screen->h/3,2*screen->w/10,screen->h-1,screen);
    drawPifDeep(2*screen->w/10,2*screen->h/3,4*screen->w/10,screen->h-1,screen);
    drawWind(4*screen->w/10,2*screen->h/3,6*screen->w/10,screen->h-1,screen);
    drawPifScale(6*screen->w/10,2*screen->h/3,7*screen->w/10,screen->h-1,screen);
    drawCircleSeq(7*screen->w/10,2*screen->h/3,8*screen->w/10,5*screen->h/6,screen);
    drawCircleSeqSymm(7*screen->w/10,5*screen->h/6,8*screen->w/10,screen->h-1,screen);
    drawPifAngle(8*screen->w/10,2*screen->h/3,screen->w-1,screen->h-1,screen);
    
    
    
    
    drawColorSeq(1,1,screen->w/3,screen->h/3,screen);
    
    
    drawGLPannelStack(screen,screen->w/6,screen->h/6,screen->w/3,screen->h/3);

    addButton(1,screen->h/9,screen->w/6/3,2*screen->h/9,0,rizeSensorsSpeed);


    addButton(screen->w/6/3,screen->h/9,2*screen->w/6/3,2*screen->h/9,0,rizeOpenCVControll);
    
    addButton(2*screen->w/6/3,screen->h/9,screen->w/6,2*screen->h/9,0,rizeColorLineOpt);
    



    bar(screen,1,screen->h/9,screen->w/6/3,2*screen->h/9,BLUE);
    
    bar(screen,screen->w/18,screen->h/9,2*screen->w/18,2*screen->h/9,RED);

    bar(screen,2*screen->w/18,screen->h/9,screen->w/6,2*screen->h/9,YELLOW);
    
    
    drawSpiralTransform(screen->w/3,0,6*screen->w/13,screen->h/6,screen);
    drawMegaTransform(screen->w/3,screen->h/6+1,6*screen->w/13,screen->h/3,screen);
    
   // drawOSDButts(11*screen->w/13,screen->h/4,screen->w-1,screen->h/3,screen);
    placeMyplayControll(11*screen->w/13,screen->h/4,screen->w-1,screen->h/3,screen);
    
    
    
    
    
    //drawPifNaked(0,2*screen->h/3,screen->w/10,screen->h-1,screen);
    //drawPifColored(screen->w/10,2*screen->h/3,2*screen->w/10,screen->h-1,screen);
    //drawPifPosition(2*screen->w/11,screen->h/3,3*screen->w/11,2*screen->h/3,screen);
    //drawPifSigns(4*screen->w/10,2*screen->h/3,7*screen->w/10,screen->h-1,screen);
  
  
  
  
    drawInput(screen,0,0.4,0.2,0.6);
      
    int a,b,c,d,w,h;
    w=screen->w;
    h=screen->h;
    a=0*w;
    b=0.4*h;
    c=0.20*w;
    d=0.6*h;
    addButton(a,b,c,d,0,rizeKoefsSensorSetup);

    if(centerSwitch==0){
        setOpt("send_qsAll_ks",0);

        drawRithm(screen,screen->w/4,screen->h*0.4,0.75*screen->w,screen->h*0.6,rithm);
    }else if(centerSwitch==1){
       // drawRithm(screen,screen->w/4,,0.75*screen->w,screen->h*0.6,rithm);
         setOpt("send_qsAll_ks",1);

         calcQSDis(&qsAll);
         drawQs(screen,screen->w*0.3,screen->h*0.4,screen->w*0.7,screen->h*0.6,&qsAll);
         addButton(screen->w*0.3,screen->h*0.4,screen->w*0.7,screen->h*0.6,0,rizeDrawQs);

    }else if(centerSwitch==2){
            setOpt("send_qsAll_ks",1);
            calcQSDis(&qsAll);
            calcOqColorline(qsAll,1);
            drawOqColorLines(screen,screen->w*0.3,screen->h*0.4,screen->w*0.7,screen->h*0.6);
            addButton(screen->w*0.3,screen->h*0.4,screen->w*0.7,screen->h*0.6,0,rizeDrawOqColorLines);
    
    }else if(centerSwitch==3){
            setOpt("send_qsAll_ks",0);

       // drawRithm(screen,screen->w/4,,0.75*screen->w,screen->h*0.6,rithm);
         //calcQSDis(&qsAll);
     //    drawQs(screen,screen->w*0.3,screen->h*0.4,screen->w*0.7,screen->h*0.6,&qsAll);
       //  addButton(screen->w*0.3,screen->h*0.4,screen->w*0.7,screen->h*0.6,0,rizeDrawQs);
//       drawMonitor(screen,screen->w*0.3,screen->h*0.4,screen->w*0.7,screen->h*0.5,"allMajors");
  //     drawMonitor(screen,screen->w*0.3,screen->h*0.5,screen->w*0.7,screen->h*0.6,"allMinors");
//        const char *s[]={"orOpacity","back","gray","antiPuddle","glBlendMetod","videoFile1","videoFile2","videoFile3"};
//          const char *s[]={"gray","pifInterOp1","pifInterOp1_q","pifInterSize1","pifInterOp2","pifInterOp2_q","pifInterSize2","pifInterOp3","pifInterOp3_q","pifInterSize3","pifInterOp4","pifInterOp4_q","pifInterSize4"};
  
  //      Uint32 c[]={0x888888,BLUE,BLUE,BLUE,CYAN,CYAN,CYAN,WHITE,WHITE,WHITE,RED,RED,RED};


          const char *s[]={"gray","pifInterOp2","pifInterOp2_q","pifInterSize2","pifInterOp3","pifInterOp3_q","pifInterSize3","pifInterOp4","pifInterOp4_q","pifInterSize4","interferMorphSpeed","interferGamma","wave2sceen1"};
  
        Uint32 c[]={0x888888,CYAN,CYAN,CYAN,WHITE,WHITE,WHITE,RED,RED,RED,BLUE,RED,YELLOW,BLUE};
//        drawOptStack(screen,screen->w*0.3,screen->h*0.4,screen->w*0.7,screen->h*0.6,s,c,13);
    drawOptStackRBKoefs(screen,screen->w*0.3,screen->h*0.4,screen->w*0.7,screen->h*0.6,s,c,13);
    }
    else if(centerSwitch==4){
//        char *s[]={"orOpacity","back","gray","antiPuddle","glBlendMetod"};
            setOpt("send_qsAll_ks",0);

        #define MODES 10
        Uint32 c[MODES]={CYAN,BLUE,GREEN,0xaaaaaa,WHITE,VIOLVET,RED,GREEN,BLACK,CYAN|VIOLVET};
        int x1,y1,x2,y2;
        x1=screen->w*0.3;
        y1=screen->h*0.4;
        x2=screen->w*0.7;
        y2=screen->h*0.6;
        int h,w;
        w=x2-x1;
        h=y2-y1;
        for(int i=0;i<MODES;i++){
            int x,y;
            x=x1+w*i/MODES+w/2/MODES;
            y=y1+h/2;
            
            if(mode==i){
                bar(screen,x-w/3/MODES,y-h/3,x+w/3/MODES,y+h/3,c[i]);
            }else{
                bar(screen,x-w/4/MODES,y-h/4,x+w/4/MODES,y+h/4,c[i]);
            }
            rectangle(screen,x-w/2/MODES,y-h/2,x+w/2/MODES,y+h/2,BORDERCOLOR);
            addButton(x-w/2/MODES,y-h/2,x+w/2/MODES,y+h/2,i,modifyMode);
            
        }
    }
    drawCenterSwitcher(screen,screen->w/4,screen->h/3,0.75*screen->w,screen->h*0.4);
    
    
    drawOutput(screen,0.75,0.4,1,0.6);  
    drawAddons(screen,0.75,0.4,1,0.6);
    
    drawFade(6*screen->w/13,0,7*screen->w/13-1,screen->h/6,screen);
    drawOrblur(7*screen->w/13,0,8*screen->w/13-1,screen->h/6,screen);
    
    
    drawMaskFilter(6*screen->w/13,screen->h/6+1,8*screen->w/13-1,screen->h/3,screen);
    //(6*screen->w/13,screen->h/6+1,8*screen->w/13-1,screen->h/3,screen);
    
//  
    //drawPiano(screen);


}
#include"interfer.cpp"
extern int netstatus;
void draw(SDL_Surface*screen){
    frames++;
    clearButtons();
    clearEvalues();    
    if(netstatus==0){
        putpixel(screen,rand()%screen->w,rand()%screen->h,0x00ff00);    
    
    }else{
        if(pageScreen==0){
            rizePannel=0;
            drawPifControll(screen);
            drawCurrent(screen);
          
            showDialog(screen);
            markSelectedValue(screen);
        }else if(pageScreen==1){
            drawSound(screen);
    
    
        }
    }
    
    
    showDrops(screen);
    SDL_Flip( screen ); 
    



}
#define KEY_ESC 9
#define KEY_1 10
#define KEY_2 11
#define KEY_3 12
#define KEY_4 13
#define KEY_5 14
#define KEY_6 15
#define KEY_7 16

#define COMMANDLEN (2*1024*1024)
char command[COMMANDLEN];
int ccur=0;
int badcommand=0;

void checkConnect(){
#ifdef IPSEND
        while(1){
            char s[100];
            char c;
            c=getnetc();
            sprintf(s,"[%d]",c);
            mySend(s);
        }
       #endif 
}



int recive(){
    #ifndef IPSEND
    int c;
    while(1){
        c=getc(stdin);
        if(c!=EOF && c!=-1){

           if(c==10){
             //  printf("enter!\n");
              
              if(!badcommand){
                command[ccur]=0; 
                ccur=0;
                badcommand=0;
                if(syntaxControll(command))
                    return 1;
                
              }else{
                ccur=0;
              }
           }else{
               if(ccur<COMMANDLEN-1){
                   command[ccur++]=c;
               }else{
                    badcommand=1;
               }
           }
       }
    if(c==-1)
        return 0;
    }
  return 0;
  #else
  
    return checkRecvData(); 
  //      c=getnetc();
   #endif 
    
}
#define BUFSIZE 128
int clickflag=0;
int controll(){
    SDL_Event event;
    char buf[BUFSIZE+1]="";
    int datasize;
    int msgid,size;

    recive();
    #ifdef IPSEND

    if(connectflag && GetTickCount() - lastRecive >3300 ){
        myDisconnect();
    }
    #endif
    checkZerro(); 
    while(SDL_PollEvent(&event)){

        
        
        switch (event.type) {
            case SDL_KEYDOWN: keys[event.key.keysym.scancode]=2;break;
            case SDL_KEYUP: keys[event.key.keysym.scancode]=0;break;
            case SDL_MOUSEBUTTONDOWN:
             //   if(event.button.x>W/2){               //event.button.y;
               //     loadNext();
               // }else{
                //    loadPrev();
               // }break;
                clickflag=1;

                if(clickMouse(event.button.x,event.button.y)){
                    addDrop(event.button.x,event.button.y);
                    clickflag=2;
                }
                
                selectEValue(event.button.x,event.button.y);
                break;
            case SDL_MOUSEMOTION:
                clickflag=2;
                modifySelected(event.motion.x,event.motion.y);
                if(event.motion.state)
                    sclickMouse(event.motion.x,event.motion.y);
            break;
            case SDL_MOUSEBUTTONUP:
                if(clickflag==1){
                    if(clickRelizeMouse(event.button.x,event.button.y)){
                        addDrop(event.button.x,event.button.y);
                
                    }
                }
                modifySelected(event.button.x,event.button.y);
                relizeSelectedValue();
             
             break;   
            case SDL_QUIT: return 1; break;
           
        }
    }
    if(keyboardControll())
        return 1;
    
     
    
    
    
    return 0;
       
}


int sync_(SDL_Surface*screen){
    connectflag=0;
    copy2lvalues();
    printf("\nconnect\n");
    while(!connectflag){
        printf("\nconnect\n");
        int x,y;
        if(screen!=NULL){
            x=rand()%screen->w;
            y=rand()%screen->h;
            putpixel(screen,x,y,GREEN);
            SDL_Flip( screen ); 
    
        }
        fflush(stdout);    
        recive();
        if(controll()){
            return 1;
        }       
    
    }
    return 0;
}
int sync_(){
    sync_(NULL);

}
int controll_main( int argc, char* args[] ) { 
    int i,x,y,c,flag,windowflag,windowXRes,windowYRes;
    //The images 
    SDL_Surface* hello = NULL; 
    //SDL_Surface* screen = NULL;
    SDL_Surface* filter = NULL;
    SDL_Surface *trueScreen = NULL ;
    const SDL_VideoInfo* myPointer;

    windowflag=0;
    flag=1;
    int windowXPos=0;
    int windowYPos=0;
    int noframe=0;
    printf("hi!\n");
//    checkConnect();
    srand (time(NULL));
    SDL_putenv((char*)"SDL_VIDEO_WINDOW_POS=0,0");
    initStdIn();
    cl=&cl3;
    for(i=1;i<argc;i++){
        if(!strcmp(args[i],"-sleep") && i+1<argc){
            int t;
            i++;
            sscanf(args[i],"%d",&t);
            sleep(t);            
        }  
        if(!strcmp(args[i],"-slowwork")){
            slowWork=1;
        }  
        if(!strcmp(args[i],"-noframe")){
            noframe=1;
        }
        
        if(!strcmp(args[i],"-position") && i+1<argc){
            windowXPos=-1;
            windowYPos=-1;
            i++;
            sscanf(args[i],"%dx%d",&windowXPos,&windowYPos);
           // printf("Set position:%d x %d",windowXPos,windowYPos);
        }

        
        if(!strcmp(args[i],"-window") && i+1<argc){
            windowXRes=-1;
            windowYRes=-1;
            i++;
            sscanf(args[i],"%dx%d",&windowXRes,&windowYRes);
            if(windowXRes > 0 && windowYRes > 0 ){
                windowflag=1;  
        
            }
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
     
     
     myPointer = SDL_GetVideoInfo();
     W=myPointer->current_w;
     H=myPointer->current_h;
     if(windowflag){
        W=windowXRes;
        H=windowYRes;
     }        
     screen = SDL_SetVideoMode(W , H, 32, SDL_HWSURFACE |  (windowflag&&(!noframe)?0:SDL_NOFRAME) | SDL_DOUBLEBUF/*|SDL_GL_DOUBLEBUFFER |SDL_OPENGL */); 

    // SDL_ShowCursor(0);
//    SDL_ShowCursor(0);
    mode=5;
    preparePutPixel(screen);

    for(i=0;i<256;i++)
        keys[i]=0;
    
    if(sync_(screen)){
             SDL_Quit();
             printf("EOF:%c",EOF);
             fflush(stdout);
             return 1;
    }
 
    printf("writeAllValues\n");
    if(sync_(screen)){
             SDL_Quit();
             printf("EOF:%c",EOF);
             fflush(stdout);
     
             return 1;
    }
   printf("writeAllValues\n");
   sleep(1);
   for(i=0;i<100;i++){
        recive();
   }
   //
   //  load_rabbit("current.r2");
    reallocQs(&qsAll,12,6+3+1);
    zeroOqColorLine();
    while(flag){
 //       for(i=0;i<10000;i++){
   //         for(int j=0;j<1000;j++){}
     //   }
        draw(screen);
        if(controll()){
            break;
        } 
        syncSoundData();   
        writeAllValues();
        if(slowWork){
            
            
            takeItEasy();
            
        }
 
     }
     

     
      //Quit SDL 
     // closeRgbMixer();
    //  save_rabbit("current.r2");
      SDL_Quit(); 
      printf("\ndisconnect\n");
      fflush(stdout);
      sleep(1);
      for(int i=0;i<100;i++){
          controll();      
      }
     // sleep(1);
      return 0;
}


