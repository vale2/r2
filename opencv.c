#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "options.cpp"
#ifdef GLBILD
#include"mygl.h"
#endif
volatile int recVideo=0;

#define OCVTH 3
#define RECFRN 120
volatile Uint32 recVideoImgFrN[RECFRN];
volatile int recVideoImgReady[RECFRN];
volatile int recVideoImgW=0;
volatile int recVideoImgH=0;
volatile Uint32* volatile recVideoImgPtr[RECFRN];//={NULL,NULL};


CvCapture *camera[OCVTH];
volatile int ocvFrameReady[OCVTH];

int firstVideo[OCVTH]={1,1,1};
int ocvfps[OCVTH];
volatile int nPlayList[OCVTH]={0,0,0};
volatile int lockFreeBufs[OCVTH]={0,0,0};

int lnPlayList[OCVTH]={-100,-100,-100};


volatile int nvideoFiles[OCVTH]={0,0,0};
volatile int curVideoFile[OCVTH]={0,0,0};
volatile int lastCurVideoFile[OCVTH]={0,0,0};
volatile int setCurVideoFile[OCVTH]={0,0,0};


volatile double OVCpercentPos[OCVTH];
volatile double OVCpercentSetPos[OCVTH]={-1,-1,-1};;

volatile double OVCLoopBegin[OCVTH]={0,0,0};
volatile double OVCLoopEnd[OCVTH]={1,1,1};
volatile double OVCVideoSpeed[OCVTH]={1,1,1};
//videoSpeed
char videoFiles[OCVTH][128][128];
void closeVideo(int n){
    cvReleaseCapture(&(camera[n]));
}
void genOcvPLName(char*s,int n){
    if(n==0){
        sprintf(s,"videos.pls");
    }else{
        sprintf(s,"videos%d.pls",n);
    }
}
void loadOcvPlayList(int thr,int n){
    FILE*f;
    char s[129];
    nvideoFiles[thr]=0;
    genOcvPLName(s,n);
    fprintf(stderr,"openCV playList: (%s)",s);
    f=fopen(s,"r");
    if(f==NULL){
        fprintf(stderr," FILED TO OPEN\n");
        return;
    }
    fprintf(stderr," successfully oppened\n");
    
    curVideoFile[thr]=0;
    while(!feof(f)&&nvideoFiles[thr]<127){
        videoFiles[thr][nvideoFiles[thr]][0]=0;
        fscanf(f,"%s",videoFiles[thr][nvideoFiles[thr]++]);
        if(videoFiles[thr][nvideoFiles[thr]-1][0]==0 || (nvideoFiles[thr]>1&&!strcmp(videoFiles[thr][nvideoFiles[thr]-1],videoFiles[thr][nvideoFiles[thr]-2]))){
            nvideoFiles[thr]--;
        }else{
//            fprintf(stderr,"openCV file: (%s)\n",videoFiles[thr][nvideoFiles[thr]-1]);
        }
    }
    fclose(f);

}

void loadVideoPlaylist(int th){
//    for(int i=0;i<OCVTH;i++)
        loadOcvPlayList(th,0);
}




int openVideo(int th,const char*name){
    
    camera[th]=cvCaptureFromFile(name);
    if (camera[th]==NULL){
        fprintf(stderr,"camera %s is null\n",(char*)name);
        sleep(1);
        return -1;
    }
    fprintf(stderr,"camera %s is active now\n",(char*)name);
    return 0;
}
int ovclife[OCVTH]={0,0,0};
int ovcAutoSwitch[OCVTH]={0,0,0};
volatile int stillImage[OCVTH]={0,0,0};
int isImage(char*s){
    int l;
    l=strlen(s);
    if(s[l-1]=='g' 
     &&s[l-2]=='p' 
     &&s[l-3]=='j' 
     &&s[l-4]=='.' 
||
       s[l-1]=='p' 
     &&s[l-2]=='m' 
     &&s[l-3]=='b' 
     &&s[l-4]=='.' 
||
       s[l-1]=='g' 
     &&s[l-2]=='n' 
     &&s[l-3]=='p' 
     &&s[l-4]=='.'){
     
        return 1;
     }
     return 0;

}
int imgH[OCVTH],imhW[OCVTH];
char*IMG[OCVTH];
void my_loadImage(int th,char*s){
    int h,w;
    SDL_Surface *image = IMG_Load ( s );
    char *ri;
   fprintf(stderr,"My_loadImage\n");
//   fprintf(stderr,"depth:%d widthStep:%d ",img->depth,img->widthStep);
  //          fprintf(stderr,"w:%d h:%d\n",img->width,img->height);

    if(image!=NULL){
        fprintf(stderr,"Loaded %d x %d\n",image->w,image->h);
        if(imgH[th]*imhW[th]<image->w*image->h){
            if(IMG[th]!=NULL)
                free(IMG[th]);
             IMG[th]=(char*)malloc(image->w*image->h*3);
        
        }          
        if(IMG[th]!=NULL){
            ri=(char*)image->pixels;
            h=image->h;
            w=image->w;
            for(int x=0;x<w;x++){
                for(int y=0;y<h;y++){
                    IMG[th][(x+y*w)*3]=ri[(x+y*w)*3];
                    IMG[th][(x+y*w)*3+1]=ri[(x+y*w)*3+1];
                    IMG[th][(x+y*w)*3+2]=ri[(x+y*w)*3+2];                    
                }
            }
            fprintf(stderr,"Copyed ;)\n");
            imgH[th]=h;
            imhW[th]=w;
            //memcpy(IMG,image->pixels,image->w*image->h*3);
        
        }

        SDL_FreeSurface ( image );
    
    }
    
}
void openCurVideoFile(int th){
    if(camera[th]!=NULL){
          closeVideo(th);
    }
//    nvideoFiles=0;
 //   curVideoFile=0;
    firstVideo[th]=1;
    camera[th]=NULL;
    if(curVideoFile[th]<nvideoFiles[th]&&curVideoFile[th]>=0){
        if(isImage(videoFiles[th][curVideoFile[th]])){
            stillImage[th]=1;
            my_loadImage(th,videoFiles[th][curVideoFile[th]]);   
            ocvfps[th]=1;
        }else{
            stillImage[th]=0;
            openVideo(th,videoFiles[th][curVideoFile[th]]);
            OVCpercentSetPos[th]=OVCLoopBegin[th];
            ocvfps[th] = (int) cvGetCaptureProperty(camera[th], CV_CAP_PROP_FPS);
      

        }
        ovclife[th]=0;
    }else{
//        camera=cvCaptureFromCAM(CV_CAP_ANY);
        int c;
        c=curVideoFile[th];
        if(c>0){
            camera[th]=cvCaptureFromCAM(0);
        }else{
            camera[th]=cvCaptureFromCAM(-c-1);
        
        }
        if(camera[th]!=NULL){
            fprintf(stderr,"Default camera is active now\n");

        }else{
            fprintf(stderr,"Can't open Default camera\n");
        }
        ocvfps[th]=1;

        sleep(1);
        ovclife[th]=1;
    }
}

double lOVCpercentPos[OCVTH]={-1,-1,-1};
double lOVCLoopBegin[OCVTH]={0,0,0};
double lOVCLoopEnd[OCVTH]={1,1,1};
extern int recAudio;


char _rBuf[256];
const char* multiTh(int th,const char*s,char *rBuf){
    if(th==0){
        return s;
    }
    sprintf(rBuf,"%s_th%d",s,th);
    return rBuf;

}
const char* multiTh(int th,const char*s){
    return multiTh(th,s,_rBuf);

}
Uint32 startRec;
int lnvf[OCVTH]={-1,-1,-1};;
extern unsigned int recFrN;

void processOpenCV(){
    int nvf;
    
    for(int i=0;i<OCVTH;i++){
        
        
        nvf=getOpt(multiTh(i,"videoFileNum"));
        setOpt(multiTh(i,"videoFileN"),nvideoFiles[i]);
        double a,b;
        b=OVCpercentPos[i];
        a=getOpt(multiTh(i,"OVCpercentPos"));
        if(lOVCpercentPos[i]>0.&&fabs(lOVCpercentPos[i]-a)>0.00001){
            OVCpercentSetPos[i]=a;
        
        }
        lOVCpercentPos[i]= b   ;
        setOpt(multiTh(i,"OVCpercentPos"),b);
        
         a= getOpt(multiTh(i,"OVCLoopBegin"));
         if(fabs(a-lOVCLoopBegin[i])>0.00001){
            lOVCLoopBegin[i]=a;
            OVCLoopBegin[i]=lOVCLoopBegin[i];
         
         
         }
         
         a= getOpt(multiTh(i,"OVCLoopEnd"));
         if(fabs(a-lOVCLoopEnd[i])>0.00001){
            lOVCLoopEnd[i]=a;
            OVCLoopEnd[i]=lOVCLoopEnd[i];
         }
         
    /*
        volatile double OVCLoopBegin=0;
    volatile double OVCLoopEnd=1;
    */
        
        
       
        if(nvf!=lnvf[i]){
            setCurVideoFile[i]=nvf;
            lnvf[i]=nvf;
         //   closeVideo();
         //   camera=NULL;
        }
        
  }
  
  
  
     
  if(getOpt("recVideo")>0.5){
        if(recVideo==0 && recAudio==0){
//            startRec=GetTickCount();
            int i;
             for(i=0;i<RECFRN;i++)
                recVideoImgReady[i]=0;
            recVideo=1;
            recAudio=1;
            recFrN=1; 
               
               
                      
        
        }else if(recVideo==1 && recAudio==1){
          //  if((GetTickCount()-startRec)/1000.>getOpt("recSplitTime")){
            //    recVideo=0;
              //  recAudio=0;        
            
           // }
        
        }else{
            recVideo=0;
            recAudio=0;
        }
        
     
     
     }else{
         recVideo=0;
         recAudio=0;    
     }
        
}

void takeItEasy(){
   struct timespec tw = {0,300};
   struct timespec tr;
   nanosleep (&tw, &tr);

}


double localSpeed[OCVTH]={1,1,1};
double speedAcc[OCVTH]={0,0,0};
double ovcAutoSwitchAcc[OCVTH];
double ovcAutoSwitchLimit[OCVTH];
Uint32 lastTick[OCVTH];
int  getNextFrame(char**p,int*rh,int*rw,int n){
    int h,w,s,type;
    s=0;
    double percent;
    
       
    if(curVideoFile[n]!=setCurVideoFile[n]){
        curVideoFile[n]=setCurVideoFile[n];
        closeVideo(n);
        camera[n]=NULL;
        stillImage[n]=0;
    }
    if(camera[n]!=NULL){
    //        IplImage *img=cvQueryFrame(camera);
          Uint32 ti,lti;
          ti=GetTickCount();
          lti=ti;
          ti-=lastTick[n];
          lastTick[n]=lti;
          double tkoef;
          tkoef=1;
          if(ti<2000){
            tkoef=ti*ocvfps[n]/1000.;
          
          }
          
          speedAcc[n]+=localSpeed[n]*tkoef;
          ovcAutoSwitchAcc[n]+=localSpeed[n];
          while(speedAcc[n]<-2.){
            speedAcc[n]=-2.;
          }
          if(speedAcc[n]>=1.){
           
              IplImage *img;
              while(speedAcc[n]>=1.){
                 cvGrabFrame(camera[n]);
                 speedAcc[n]-=1.;
              }
              img=cvRetrieveFrame(camera[n]);
    
    
            if(img==NULL){
                openCurVideoFile(n);
                return -2;
            }
            if(OVCpercentSetPos[n]>0){
                double a=OVCpercentSetPos[n];
               double b;
               if(!ovclife[n]){
                    b=cvGetCaptureProperty(camera[n],CV_CAP_PROP_FRAME_COUNT);
               
                    cvSetCaptureProperty(camera[n],CV_CAP_PROP_POS_FRAMES,a*b);
                }
                OVCpercentSetPos[n]=-1;
            }
            h=img->height;
            w=img->width;
            if(firstVideo[n]){     
                firstVideo[n]=0;
                fprintf(stderr,"ncha:%d alpha:%d ",img->nChannels,img->alphaChannel);
                fprintf(stderr,"depth:%d widthStep:%d ",img->depth,img->widthStep);
                fprintf(stderr,"w:%d h:%d\n",img->width,img->height);
            }
    
            if(*p!=NULL && (*rh)* (*rw) <h*w){
               while(lockFreeBufs[n]);

                free(*p);
                *p=NULL;
            }
            if(*p==NULL){
                *p=(char*)malloc(h*w*3);
                if(*p==NULL)
                    return -3;
            
            }
            //fprintf(stderr,"Waiting in openCV for staring read video\n");
            if(!ovclife[n]){
                percent=cvGetCaptureProperty(camera[n],CV_CAP_PROP_POS_AVI_RATIO);
            }else{
                percent=0;
            }
            OVCpercentPos[n]=percent;
//            fprintf(stderr,"percent:%f\n",percent);
        while(ocvFrameReady[n])takeItEasy();
            //ocvFrameReady=0;
            //fprintf(stderr,"Started coping in openCV \n");
        for(int y=0;y<h;y++){
            memcpy(*p+y*w*3,img->imageData+y*img->widthStep,img->widthStep);
        }
        *rh=h;*rw=w;
        
       }else{
           while(ocvFrameReady[n])takeItEasy();
    
       }
        localSpeed[n]=OVCVideoSpeed[n];
        if(nPlayList[n]!=lnPlayList[n]){
            lnPlayList[n]=nPlayList[n];
            loadOcvPlayList(n,nPlayList[n]);
        }
        
        ocvFrameReady[n]=1;
       
       // fprintf(stderr,"Copied in openCV,returning\n");
//volatile double =0;
        
//        fprintf(stderr,"OVCLoopEnd:%f\n",OVCLoopEnd);
        if(percent>=OVCLoopEnd[n]-0.00001 &&!ovclife[n]){
            
            
            if(camera[n]!=NULL){
              closeVideo(n);
            }
            camera[n]=NULL;
            OVCpercentSetPos[n]=OVCLoopBegin[n];      
            if(ovcAutoSwitch[n]){
                curVideoFile[n]=(curVideoFile[n]+1)%nvideoFiles[n];
                setCurVideoFile[n]=(curVideoFile[n]+1)%nvideoFiles[n];
                
                fprintf(stderr,"AutoSwitch on %d camera\n",n);
            }
        }
        return 0;
    //double t2=(double)cvGetTickCount();
    //printf("time: %gms  fps: %.2g\n",(t2-t1)/(cvGetTickFrequency()*1000.), 1000./((t2-t1)/(cvGetTickFrequency()*1000.)));
    //cvShowImage("img",img);
    }else if(stillImage[n]){
        
        h=imgH[n];
        w=imhW[n];
        if(*p!=NULL && (*rh)* (*rw) <h*w){
            while(lockFreeBufs[n]);
            free(*p);
            *p=NULL;
        }
        if(*p==NULL){
            *p=(char*)malloc(h*w*3);
            if(*p==NULL)
                return -3;
        }
        while(ocvFrameReady[n])takeItEasy();
        memcpy(*p,IMG[n],h*w*3);
        *rh=h;*rw=w;
        ocvFrameReady[n]=1;
        if(ovcAutoSwitch[n]&&ovcAutoSwitchAcc[n]>=ovcAutoSwitchLimit[n]){
                setCurVideoFile[n]=(curVideoFile[n]+1)%nvideoFiles[n];
                curVideoFile[n]=(curVideoFile[n]+1)%nvideoFiles[n];
            
                ovcAutoSwitchAcc[n]=0;
        }

        
        
        return 0;
    
    }
    openCurVideoFile(n);
    return -1;
}

char*ovcvideo[3]={NULL,NULL,NULL};
int ocvh[3]={0,0,0};
int ocvw[3]={0,0,0};

Uint32 ocvTex[3];


int  getFrame(int th,char**p,int*rh,int*rw){
    int h,w,s,type;
    s=0;
    fprintf(stderr,"OLD getframe\n");
    return -1;
    if(ocvFrameReady[th] == 0){
        fprintf(stderr,"Dropped\n");

        return -1;
    }
    double sp;
//(int th,char*s,char *rBuf){


    ovcAutoSwitch[th]=getOpt(multiTh(th,"ovcAutoSwitch"))>0.5?1:0;
    
    
    ovcAutoSwitchLimit[th]=getOpt(multiTh(th,"ovcAutoSwitchLimit"))*100.;
    sp=calcOpt(multiTh(th,"videoSpeed"));
    int npls;
    npls=getOpt(multiTh(th,"nOCVPlayList"));
    OVCVideoSpeed[th]=sp*3;
    
    h=ocvh[th];
    w=ocvw[th];
        if(*p!=NULL && (*rh)* (*rw) <h*w){
            while(lockFreeBufs[th]);
            free(*p);
            *p=NULL;
        }
        if(*p==NULL){
            *p=(char*)malloc(h*w*3);
            if(*p==NULL)
                return -3;
        
        }
//        ocvFrameReady=0;
        memcpy(*p,ovcvideo[th],h*w*3);
        *rh=h;*rw=w;
    nPlayList[th]=npls;
    ocvFrameReady[th]=0;
    //fprintf(stderr,"Copied in rabbit\n");


    return 0;
}
int  getFrame(int th, Uint32 &thTex){
    int s,type;
    s=0;
    double sp;
//(int th,char*s,char *rBuf){
   //fprintf(stderr,"getFrame start\n");
  // fflush(stderr);
  char*ptr;
  int w,h;
  lockFreeBufs[th]=1;
  ptr=ovcvideo[th];
  w=ocvw[th];
  h=ocvh[th];
  
    if(ocvFrameReady[th] == 0 || ptr == NULL || w<=0 || h<=0){
        thTex=ocvTex[th];

        fprintf(stderr,"Dropped\n");
  // fflush(stderr);
  lockFreeBufs[th]=0;

        return -1;
    }

    ovcAutoSwitch[th]=getOpt(multiTh(th,"ovcAutoSwitch"))>0.5?1:0;
    
    
    ovcAutoSwitchLimit[th]=getOpt(multiTh(th,"ovcAutoSwitchLimit"))*100.;
    sp=calcOpt(multiTh(th,"videoSpeed"));
    int npls;
    npls=getOpt(multiTh(th,"nOCVPlayList"));

    OVCVideoSpeed[th]=sp*3;
    
    
    thTex=ocvTex[th];
//   fprintf(stderr,"getFrame before bind\n");
  // fflush(stderr);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, thTex);
  // fprintf(stderr,"getFrame after bind\n");
  // fprintf(stderr,"getFrame w=%d h=%d\n",w,h);
  // fflush(stderr);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h,
        0, GL_BGR, GL_UNSIGNED_BYTE, ptr);
  lockFreeBufs[th]=0;

  // fprintf(stderr,"getFrame after glTexImage2D\n");
 //  fflush(stderr);
    
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

   //fprintf(stderr,"getFrame after parametri\n");
  // fflush(stderr);
    
    nPlayList[th]=npls;
    ocvFrameReady[th]=0;
    //fprintf(stderr,"Copied in rabbit\n");

   //fprintf(stderr,"getFrame end\n");
  // fflush(stderr);

    return 0;
}

//ocvFrameReady
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
void* pf(void *arg){
      int n;
      n=*((int*)arg);
      loadVideoPlaylist(n);
        while(1){
            getNextFrame(&(ovcvideo[n]),&(ocvh[n]),&(ocvw[n]),n);
      }

}
pthread_t tid;

#define RECFPS 16
Uint32 recStart;
Uint32 recFrames;
char*recBuf=NULL;
char vtimestamp[32];

void* ocvWV(void *arg){
        CvVideoWriter* wr=NULL;
        IplImage *im=NULL;
        int i;
//        fprintf(stderr,"Rec video Priority: %d\n",getThreadPriority());
       /* pthread_t thId = pthread_self();
        pthread_attr_t thAttr;
        int policy = 0;
        int min_prio_for_policy = 0;

        pthread_attr_init(&thAttr);
        pthread_attr_getschedpolicy(&thAttr, &policy);
        min_prio_for_policy = sched_get_priority_min(policy);

        pthread_setschedprio(thId, min_prio_for_policy);
        pthread_attr_destroy(&thAttr);      
        */
        while(1){
            if(recVideo){
                if(wr==NULL){
                    takeItEasy();
                    CvSize s;
                    while(1){
                       int br;
                       br=0;                        
                        for(i=0;i<RECFRN;i++)
                            if(recVideoImgReady[i]){
                                br=1;               
                                recStart=recVideoImgFrN[i];
                                break;
                            }         
                        if(br)
                            break;                        
                        takeItEasy();
                    }
                    s.width = recVideoImgW;
                    s.height = recVideoImgH;
                    if(recBuf == NULL){
                        recBuf=(char*)malloc(3*recVideoImgW*recVideoImgH);
                    }
                    unsigned u;
                    time_t ltime;
                    ltime=time(NULL);
                    struct tm *tm;
                    tm=localtime(&ltime);
                    sprintf(vtimestamp,"%04d%02d%02d%02d%02d%02d", tm->tm_year+1900, tm->tm_mon, 
                    tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
                    sprintf(vrecPath,"%s%s.avi",videoRecFolder,vtimestamp);
//                    strcpy(ltimestamp)
         //           recAudioFile=fopen(recPath,"wb");
//
//                    wr=cvCreateVideoWriter(vrecPath, CV_FOURCC('D', 'I', 'V', 'X'), RECFPS, s, 1 );
                    wr=cvCreateVideoWriter(vrecPath, CV_FOURCC('F','L','V','1'), RECFPS, s, 1 );


                    if(wr!=NULL){
                        fprintf(stderr,"Rec file successfully oppened\n");
                    }else{
                        fprintf(stderr,"Rec file cannot be oppened\n");
                    }
                    
                    if(im==NULL){
                        im= cvCreateImageHeader(s,IPL_DEPTH_8U,3);          
                        if(im!=NULL){
                            fprintf(stderr,"Rec img Buf successfully created\n");
                        }
                    }
                    
                    recFrames=0;
                    
                }else{
//                    im.nSize=sizeof(im);
  //                  im.ID=0;
    //                im.nChannels=4;
    
                    Uint32 nowTime,foundTime;
                    int num;
                    num=-1;
                    nowTime=recStart+recFrames*1000./RECFPS;
                    while(1){
                        if(!recVideo)
                            break;
                        for(i=0;i<RECFRN;i++){
                            if(recVideoImgFrN[i]<nowTime){
                                    recVideoImgReady[i]=0;
                                }
                        }
                        for(i=RECFRN-1;i>=0;i--){
                             if(recVideoImgReady[i]){
                                if(recVideoImgFrN[i]>=nowTime&&(num==-1 || recVideoImgFrN[i]<foundTime)){
                                    foundTime=recVideoImgFrN[i];
                                    num=i;                                
                                }
                             
                             }    
                        
                        }
                        if(num!=-1){
//                           fprintf(stderr,"found Frame %d in %d\n",recFrames,num);
                                for(i=RECFRN-1;i>=0;i--){
                                     if(recVideoImgReady[i]){
                                        if(recVideoImgFrN[i]>=nowTime&&recVideoImgFrN[i]<foundTime){
                                            foundTime=recVideoImgFrN[i];
                                            num=i;                                
                                        }
                                     
                                     }    
                                
                                }


                            break;
                        }
                        takeItEasy(); 
                    }
                    if(recVideo){
                        if(num!=-1){
                            memcpy(recBuf,(void*)recVideoImgPtr[num],recVideoImgW*recVideoImgH*3);
                            recVideoImgReady[num]=0;
                        
                        
                            cvSetData(im,recBuf,recVideoImgW*3);
                       // while(recVideo && (GetTickCount()-recStart)/1000.*(double)(RECFPS)>recFrames){
                            while(nowTime<=foundTime){
                                cvWriteFrame(wr, im);   
                                recFrames++;
                                nowTime=recStart+recFrames*1000./RECFPS;
                            }
                        }
                        //}
                        //fprintf(stderr,".");

                    }
                }            
            }else{
                
                if(wr!=NULL){
                    cvReleaseVideoWriter(&wr);
                    wr=NULL;
                    fprintf(stderr,"Rec file closed\n");
                    char s[512];
                    char s2[512];
                    
                    sprintf(s2,"%s%s.sh",videoRecFolder,vtimestamp);
                    
                    FILE*f;
                    f=fopen(s2,"w");
                    if(f!=NULL){
                       sprintf(s,"%srabbit_%s.avi",videoRecFolder,vtimestamp);
                       fprintf(f,"#!/bin/sh\nmencoder %s -audiofile ",vrecPath);
                       fprintf(f,"%s -oac copy -ovc copy -o",recPath);
                       fprintf(f," %s\n",s);
                       fprintf(f,"rm %s\n",vrecPath);
                       fprintf(f,"rm %s\n",recPath);
                       fprintf(f,"rm %s.sh\n",vtimestamp);
                       
                       fclose(f);                       
                    }
                    //if(fork() == 0){
                      //  execlp("mencoder",vrecPath,"-audiofile",recPath,"-oac","copy","-ovc","copy","-o",s,(char*)NULL);
                        //exit(0);
                   // }
                }
                if(im!=NULL){
                    //cvReleaseImage(&im);
                    cvReleaseImageHeader(&im);
                    im=NULL;
                    fprintf(stderr,"Rec buffer relized\n");
                }
//                if(recBuf!=NULL){
  //                  free(recBuf);
    //            }
                takeItEasy();
            }

        
          
        }
}

int videoN[3];
void startOCVProcess(){
        int err;
        

        videoN[0]=0;
        videoN[1]=1;
        videoN[2]=2;
        
        err = pthread_create(&tid, NULL, &pf,(void*) &(videoN[0]));
        if (err != 0)
            fprintf(stderr,"\ncan't create thread 1.0 :[%s]", strerror(err));
        else
            fprintf(stderr,"\n Thread 1.0 created successfully\n");


        err = pthread_create(&tid, NULL, &pf,(void*) &(videoN[1]));
        if (err != 0)
            fprintf(stderr,"\ncan't create thread 1.0 :[%s]", strerror(err));
        else
            fprintf(stderr,"\n Thread 1.0 created successfully\n");


        err = pthread_create(&tid, NULL, &pf,(void*) &(videoN[2]));
        if (err != 0)
            fprintf(stderr,"\ncan't create thread 1.0 :[%s]", strerror(err));
        else
            fprintf(stderr,"\n Thread 1.0 created successfully\n");

        err = pthread_create(&tid, NULL, &ocvWV, NULL);
        if (err != 0)
            fprintf(stderr,"\ncan't create thread 2 :[%s]", strerror(err));
        else
            fprintf(stderr,"\n Thread 2 created successfully\n");


}
struct p2d{
   double x,y,l,q;
};


int fpw,fph;
Uint32*fpf;
Uint32 *fpfl;
int fpflh=-1;
int fpflw=-1;



double fpq;


inline int sumrgb(Uint32 a){
    return (a&255) + ((a/256)&255) + ((a/256/256)&255);
}
int prepare_fpfl(){
    int x,y,ls;
    if(fpflh<0||fpflw<0||fpflh*fpflw<(fpw+1)*(fph+1)){
        if(fpfl!=NULL){
            free(fpfl);
        
        }
        fpflh=(fph+1);
        fpflw=(fpw+1);
        fpfl=(Uint32*)malloc(fpflw*fpflh*sizeof(Uint32));
        if(fpfl==NULL){
            return -1;
        }
    
    }
//    fpfl[0]=0;
    for(x=0;x<fpflw;x++){
        fpfl[x]=0;//fpfl[x-1]+sumrgb(fpf[x-1]);
    }    

    for(y=1;y<fpflh;y++)
        fpfl[y*fpflw]=0;
        ls=0;
        for(x=1;x<fpflw;x++){
            int adr;
            adr=x-1+(y-1)*fpw;
            
            ls+=sumrgb(fpf[adr]);
            
            fpfl[x+y*fpflw]=fpfl[x+(y-1)*fpflw]+ls;
        }    
    return 0;
}

double getLight(double dx,double dy){
    int x,y;
    x=dx*fpflw;
    y=dy*fpflh;
    if(x>=0&&x<fpflw && y>=0&&y<fpflh){
        return fpfl[x+y*fpflw];
    
    }
    return 0;
}


double inline maxdouble(double a,double b){
    if(a>b)
        return a;
    return b;

}

struct  p2d findLight(double x1,double y1,double x2,double y2){
    double r,s;
    struct  p2d rr;
    r=getLight(x2,y2)+getLight(x1,y1)-getLight(x2,y1)-getLight(x1,y2);
    s=fpw*fph*(x2-x1)*(y2-y1);
    if(s<0.001){
        rr.l=-1;
        rr.x=0;
        rr.y=0;
        return rr;
    }    
    r=r/s;
    rr.l=r;
    rr.x=(x1+x2)/2;
    rr.y=(y1+y2)/2;
    rr.q=maxdouble(x2-x1,y2-y1);
}

struct  p2d findMaxLight(double x1,double y1,double x2,double y2){
    struct p2d r,rm;
    double w,h;
    w=x2-x1;
    h=y2-y1;
    rm=findLight(x1,y1,x2,y2);
    if(x2-x1<fpq || y2-y1<fpq){
         return rm;
    }
    for(i=0;i<4;i++){
        r=findMaxLight(x1+(w/2)*(i%2),y1+(w/2)*(i/2),x1+w/2+(w/2)*(i%2),y1+w/2+(w/2)*(i/2));
        if(r.l>rm.l){
            rm=r;        
        }
    }
    return rm;       
} 

void findPoint(int w,int h,Uint32*frame,double q,double &rx,double &ry,double &rq){
    struct p2d r;
    fph=h;
    fpw=w;
    fpf=frame;
    fpq=q;
    r=findMaxLight(0,0,1,1);
    rx=r.x;
    ry=r.y;
    rq=r.q;
}


#include"paint.cpp"
