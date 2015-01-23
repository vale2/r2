#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "options.cpp"
volatile int recVideo=0;


CvCapture *camera;
volatile int ocvFrameReady;

int firstVideo=1;

volatile int nPlayList=0;
int lnPlayList=-100;


volatile int nvideoFiles=0;
volatile int curVideoFile=0;
volatile int lastCurVideoFile=0;
volatile int setCurVideoFile=0;;


volatile double OVCpercentPos;
volatile double OVCpercentSetPos=-1;;

volatile double OVCLoopBegin=0;
volatile double OVCLoopEnd=0;
volatile double OVCVideoSpeed=1;
//videoSpeed
char videoFiles[128][128];
void closeVideo(){
    cvReleaseCapture(&camera);
}
void genOcvPLName(char*s,int n){
    if(n==0){
        sprintf(s,"videos.pls");
    }else{
        sprintf(s,"videos%d.pls",n);
    }
}
void loadOcvPlayList(int n){
    FILE*f;
    char s[129];
    nvideoFiles=0;
    genOcvPLName(s,n);
    fprintf(stderr,"openCV playList: (%s)",s);
    f=fopen(s,"r");
    if(f==NULL){
        fprintf(stderr," FILED TO OPEN\n");
        return;
    }
    fprintf(stderr," successfully oppened\n");
    
    curVideoFile=0;
    while(!feof(f)&&nvideoFiles<127){
        videoFiles[nvideoFiles][0]=0;
        fscanf(f,"%s",videoFiles[nvideoFiles++]);
        if(videoFiles[nvideoFiles-1][0]==0 || (nvideoFiles>1&&!strcmp(videoFiles[nvideoFiles-1],videoFiles[nvideoFiles-2]))){
            nvideoFiles--;
        }else{
            fprintf(stderr,"openCV file: (%s)\n",videoFiles[nvideoFiles-1]);
        }
    }
    fclose(f);

}

void loadVideoPlaylist(){
    loadOcvPlayList(0);
}




int openVideo(const char*name){
    
    camera=cvCaptureFromFile(name);
    if (camera==NULL){
        fprintf(stderr,"camera %s is null\n",(char*)name);
        return -1;
    }
    fprintf(stderr,"camera %s is active now\n",(char*)name);
    return 0;
}
int ovclife=0;
volatile int stillImage=0;
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
int imgH,imhW;
char*IMG;
void my_loadImage(char*s){
    int h,w;
    SDL_Surface *image = IMG_Load ( s );
    char *ri;
   fprintf(stderr,"My_loadImage\n");
//   fprintf(stderr,"depth:%d widthStep:%d ",img->depth,img->widthStep);
  //          fprintf(stderr,"w:%d h:%d\n",img->width,img->height);

    if(image!=NULL){
        fprintf(stderr,"Loaded %d x %d\n",image->w,image->h);
        if(imgH*imhW<image->w*image->h){
            if(IMG!=NULL)
                free(IMG);
             IMG=(char*)malloc(image->w*image->h*3);
        
        }          
        if(IMG!=NULL){
            ri=(char*)image->pixels;
            h=image->h;
            w=image->w;
            for(int x=0;x<w;x++){
                for(int y=0;y<h;y++){
                    IMG[(x+y*w)*3]=ri[(x+y*w)*3];
                    IMG[(x+y*w)*3+1]=ri[(x+y*w)*3+1];
                    IMG[(x+y*w)*3+2]=ri[(x+y*w)*3+2];                    
                }
            }
            fprintf(stderr,"Copyed ;)\n");
            imgH=h;
            imhW=w;
            //memcpy(IMG,image->pixels,image->w*image->h*3);
        
        }

        SDL_FreeSurface ( image );
    
    }
    
}
void openCurVideoFile(){
    if(camera!=NULL){
          closeVideo();
    }
//    nvideoFiles=0;
 //   curVideoFile=0;
    firstVideo=1;
    camera=NULL;
    if(curVideoFile<nvideoFiles&&curVideoFile>=0){
        if(isImage(videoFiles[curVideoFile])){
            stillImage=1;
            my_loadImage(videoFiles[curVideoFile]);   
        }else{
            stillImage=0;
            openVideo(videoFiles[curVideoFile]);
            OVCpercentSetPos=OVCLoopBegin;      

        }
        ovclife=0;
    }else{
//        camera=cvCaptureFromCAM(CV_CAP_ANY);
        int c;
        c=curVideoFile;
        if(c>0){
            camera=cvCaptureFromCAM(0);
        }else{
            camera=cvCaptureFromCAM(-c-1);
        
        }
        if(camera!=NULL){
            fprintf(stderr,"Default camera is active now\n");

        }else{
            fprintf(stderr,"Can't open Default camera\n");
        }
        sleep(1);
        ovclife=1;
    }
}

double lOVCpercentPos=-1;
double lOVCLoopBegin=0;
double lOVCLoopEnd=1;
extern int recAudio;
void processOpenCV(){
    int nvf;
    nvf=getOpt("videoFileNum");
    setOpt("videoFileN",nvideoFiles);
    double a,b;
    b=OVCpercentPos;
    a=getOpt("OVCpercentPos");
    if(lOVCpercentPos>0.&&fabs(lOVCpercentPos-a)>0.00001){
        OVCpercentSetPos=a;
    
    }
    lOVCpercentPos= b   ;
    setOpt("OVCpercentPos",b);
    
     a= getOpt("OVCLoopBegin");
     if(fabs(a-lOVCLoopBegin)>0.00001){
        lOVCLoopBegin=a;
        OVCLoopBegin=lOVCLoopBegin;
     }
     
     a= getOpt("OVCLoopEnd");
     if(fabs(a-lOVCLoopEnd)>0.00001){
        lOVCLoopEnd=a;
        OVCLoopEnd=lOVCLoopEnd;
     }
     
/*
    volatile double OVCLoopBegin=0;
volatile double OVCLoopEnd=1;
*/
    
    
   
    if(nvf!=curVideoFile){
        setCurVideoFile=nvf;
     //   closeVideo();
     //   camera=NULL;
    }
    
    
    if(getOpt("recVideo")>0.5){
        recVideo=1;
        recAudio=1;
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


double localSpeed=1;
double speedAcc=0;
int  getNextFrame(char**p,int*rh,int*rw){
    int h,w,s,type;
    s=0;
    double percent;
    
       
    if(curVideoFile!=setCurVideoFile){
        curVideoFile=setCurVideoFile;
        closeVideo();
        camera=NULL;
        stillImage=0;
    }
    if(camera!=NULL){
    //        IplImage *img=cvQueryFrame(camera);
          speedAcc+=localSpeed;
          
          if(speedAcc<-2.){
            speedAcc=-2.;
          }
          if(speedAcc>=1.){
           
              IplImage *img;
              while(speedAcc>=1.){
                 cvGrabFrame(camera);
                 speedAcc-=1.;
              }
              img=cvRetrieveFrame(camera);
    
    
            if(img==NULL){
                openCurVideoFile();
                return -2;
            }
            if(OVCpercentSetPos>0){
                double a=OVCpercentSetPos;
               double b;
               if(!ovclife){
                    b=cvGetCaptureProperty(camera,CV_CAP_PROP_FRAME_COUNT);
               
                    cvSetCaptureProperty(camera,CV_CAP_PROP_POS_FRAMES,a*b);
                }
                OVCpercentSetPos=-1;
            }
            h=img->height;
            w=img->width;
            if(firstVideo){     
                firstVideo=0;
                fprintf(stderr,"ncha:%d alpha:%d ",img->nChannels,img->alphaChannel);
                fprintf(stderr,"depth:%d widthStep:%d ",img->depth,img->widthStep);
                fprintf(stderr,"w:%d h:%d\n",img->width,img->height);
            }
    
            if(*p!=NULL && (*rh)* (*rw) <h*w){
                free(*p);
                *p=NULL;
            }
            if(*p==NULL){
                *p=(char*)malloc(h*w*3);
                if(*p==NULL)
                    return -3;
            
            }
            //fprintf(stderr,"Waiting in openCV for staring read video\n");
            if(!ovclife){
                percent=cvGetCaptureProperty(camera,CV_CAP_PROP_POS_AVI_RATIO);
            }else{
                percent=0;
            }
            OVCpercentPos=percent;
//            fprintf(stderr,"percent:%f\n",percent);
        while(ocvFrameReady)takeItEasy();
            //ocvFrameReady=0;
            //fprintf(stderr,"Started coping in openCV \n");
        for(int y=0;y<h;y++){
            memcpy(*p+y*w*3,img->imageData+y*img->widthStep,img->widthStep);
        }
        *rh=h;*rw=w;
        
       }else{
           while(ocvFrameReady)takeItEasy();
    
       }
        localSpeed=OVCVideoSpeed;
        if(nPlayList!=lnPlayList){
            lnPlayList=nPlayList;
            loadOcvPlayList(nPlayList);
        }
        
        ocvFrameReady=1;
       
       // fprintf(stderr,"Copied in openCV,returning\n");
//volatile double =0;
        
//        fprintf(stderr,"OVCLoopEnd:%f\n",OVCLoopEnd);
        if(percent>=OVCLoopEnd-0.00001 &&!ovclife){
            if(camera!=NULL){
              closeVideo();
            }
            camera=NULL;
            OVCpercentSetPos=OVCLoopBegin;      
        }
        return 0;
    //double t2=(double)cvGetTickCount();
    //printf("time: %gms  fps: %.2g\n",(t2-t1)/(cvGetTickFrequency()*1000.), 1000./((t2-t1)/(cvGetTickFrequency()*1000.)));
    //cvShowImage("img",img);
    }else if(stillImage){
        
        h=imgH;
        w=imhW;
        if(*p!=NULL && (*rh)* (*rw) <h*w){
            free(*p);
            *p=NULL;
        }
        if(*p==NULL){
            *p=(char*)malloc(h*w*3);
            if(*p==NULL)
                return -3;
        }
        while(ocvFrameReady)takeItEasy();
        memcpy(*p,IMG,h*w*3);
        *rh=h;*rw=w;
        ocvFrameReady=1;
        return 0;
    
    }
    openCurVideoFile();
    return -1;
}

char*ovcvideo[3];
int ocvh[3];
int ocvw[3];


int  getFrame(char**p,int*rh,int*rw){
    int h,w,s,type;
    s=0;
    if(ocvFrameReady == 0){
        fprintf(stderr,"Dropped\n");

        return -1;
    }
    double sp;
    sp=calcOpt("videoSpeed");
    int npls;
    npls=getOpt("nOCVPlayList");
    OVCVideoSpeed=sp;
    
    h=ocvh;
    w=ocvw;
        if(*p!=NULL && (*rh)* (*rw) <h*w){
            free(*p);
            *p=NULL;
        }
        if(*p==NULL){
            *p=(char*)malloc(h*w*3);
            if(*p==NULL)
                return -3;
        
        }
//        ocvFrameReady=0;
        memcpy(*p,ovcvideo,h*w*3);
        *rh=h;*rw=w;
    nPlayList=npls;
    ocvFrameReady=0;
    //fprintf(stderr,"Copied in rabbit\n");


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
      loadVideoPlaylist();
        while(1){
            getNextFrame(&(ovcvideo[n]),&(ocvh[n]),&(ocvw[n]));
      }

}
pthread_t tid;


volatile int recVideoImgReady=0;
volatile int recVideoImgW=0;
volatile int recVideoImgH=0;
volatile Uint32* recVideoImgPtr=NULL;
#define RECFPS 30
Uint32 recStart;
Uint32 recFrames;
char*recBuf=NULL;
void* ocvWV(void *arg){
        CvVideoWriter* wr=NULL;
        IplImage *im=NULL;
        while(1){
            if(recVideo){
                if(wr==NULL){
                    takeItEasy();
                    CvSize s;
                    while(!recVideoImgReady)takeItEasy();
                    s.width = recVideoImgW;
                    s.height = recVideoImgH;
                    if(recBuf == NULL){
                        recBuf=(char*)malloc(3*recVideoImgW*recVideoImgH);
                    }
                    wr=cvCreateVideoWriter("recvideo/one.avi", CV_FOURCC('D', 'I', 'V', 'X'), RECFPS, s, 1 );
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
                    recStart=GetTickCount();
                    recFrames=0;
                    
                }else{
//                    im.nSize=sizeof(im);
  //                  im.ID=0;
    //                im.nChannels=4;
                    while(recVideo && (GetTickCount()-recStart)/1000.*(double)(RECFPS)<recFrames){
                        takeItEasy();
                    }
                       
                    if(recVideo){
                        if(recVideoImgReady!=0){
                            memcpy(recBuf,(void*)recVideoImgPtr,recVideoImgW*recVideoImgH*3);
                            recVideoImgReady=0;
                        }
                        cvSetData(im,recBuf,recVideoImgW*3);
                        cvWriteFrame(wr, im);   
                        
                        recFrames++;
                        //fprintf(stderr,".");

                    }
                }            
            }else{
                if(wr!=NULL){
                    cvReleaseVideoWriter(&wr);
                    wr=NULL;
                    fprintf(stderr,"Rec file closed\n");
                
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

/*        err = pthread_create(&tid, NULL, &ocvWV, NULL);
        if (err != 0)
            fprintf(stderr,"\ncan't create thread 2 :[%s]", strerror(err));
        else
            fprintf(stderr,"\n Thread 2 created successfully\n");

*/
}


