#ifdef GLBILD

#include "mygl.h"


int initPaint=0;
extern int GLW;
extern int GLH;
extern GLuint tmpt;

GLuint pPatterns[OCVTH];
GLuint pFrames[OCVTH];
GLuint ptmpPatterns[100];
int shlen=0;
GLuint pShow;
char pPatternsReady[OCVTH];

//int calibrate
extern int calibrate;
extern double calibrateX;
extern double calibrateY;
extern double calibrateQ;
int calCam;
int calState=0;
int calSubState=0;
int calTimer=0;
double cals1x[8]={-1,0,-1,0,-1,1,-1,1};
double cals1y[8]={-1,0,-1,1,-1,0,-1,1};
#define CAL1T 10
char *frame=NULL;
int frameh=0;
int framew=0;

int eP[OCVTH]={1,1,1};
void  clearPattern(int cam){
    eP[cam]=1;
}

void add2pattern(int cam,char*f,int fh,int fw){
        glBindTexture(GL_TEXTURE_2D, tmpt);
        glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, GLW, GLH, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  
       glEnable(GL_BLEND);
       glBlendFunc(GL_SRC_ALPHA,GL_ONE);
      
        if(!eP[cam]){
                glBindTexture(GL_TEXTURE_2D, pPatterns[cam]);
                glColor4f(1,1,1,1);
                glBegin(GL_TRIANGLE_STRIP);
                        glTexCoord2f (0.0,1.0); glVertex2f (0.0,0.0);
                        glTexCoord2f (0.0,0.0); glVertex2f (0.0,0+GLH);
                        glTexCoord2f (1.0,1.0); glVertex2f (0+GLW,0.0);
                        glTexCoord2f (1.0,0.0); glVertex2f (0+GLW,GLH);
  
                glEnd();
           glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

        }
       glBindTexture(GL_TEXTURE_2D, ptmpPatterns[0]);
       glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fw, fh,
        0, GL_BGR, GL_UNSIGNED_BYTE, f);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    
                glBegin(GL_TRIANGLE_STRIP);
                        glTexCoord2f (0.0,1.0); glVertex2f (0.0,0.0);
                        glTexCoord2f (0.0,0.0); glVertex2f (0.0,0+GLH);
                        glTexCoord2f (1.0,1.0); glVertex2f (0+GLW,0.0);
                        glTexCoord2f (1.0,0.0); glVertex2f (0+GLW,GLH);
  
                glEnd();
       
      glBindTexture(GL_TEXTURE_2D, pPatterns[cam]);
      glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, GLW, GLH, 0);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
 


       glBlendFunc(GL_SRC_ALPHA,GL_ONE);
        eP[cam]=0;

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        glBindTexture(GL_TEXTURE_2D, tmpt);
        glColor4f(1,1,1,1);
        glBegin(GL_TRIANGLE_STRIP);
                glTexCoord2f (0.0,1.0); glVertex2f (0.0,0.0);
                glTexCoord2f (0.0,0.0); glVertex2f (0.0,0+GLH);
                glTexCoord2f (1.0,1.0); glVertex2f (0+GLW,0.0);
                glTexCoord2f (1.0,0.0); glVertex2f (0+GLW,GLH);
  
       glEnd();

    
}



Uint32*findBuf=NULL;

void findInScreen(double &x,double &y){
    double q;
    if(findBuf==NULL){
        findBuf=(Uint32*)malloc(GLH*GLW*4);
        if(findBuf==NULL) {x=-1000;y=-1000;return;}
    
    }
    
    glReadPixels(0, 0, GLW, GLH, GL_RGBA, GL_UNSIGNED_INT, findBuf);
    findPoint(GLW,GLH,findBuf,0.1,x,y,q);
}
void addGridPoint(int cam,double x,double y,double fx,double fy){
    fprintf(stderr,"%d:",cam);
    fprintf(stderr,"%f - %f  ;",x,fx);
    fprintf(stderr,"%f - %f\n",y,fy);
}

void callibrateCorner(int cam,char*f,int fh,int fw,double x,double y){
        glBindTexture(GL_TEXTURE_2D, tmpt);
        glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, GLW, GLH, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  
       glEnable(GL_BLEND);
//       glBlendFunc(GL_SRC_ALPHA,GL_ONE);
       glBlendFunc(GL_ONE,GL_ONE);

       glBindTexture(GL_TEXTURE_2D, ptmpPatterns[0]);
       glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fw, fh,
        0, GL_BGR, GL_UNSIGNED_BYTE, f);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

       
                glBegin(GL_TRIANGLE_STRIP);
                        glTexCoord2f (0.0,1.0); glVertex2f (0.0,0.0);
                        glTexCoord2f (0.0,0.0); glVertex2f (0.0,0+GLH);
                        glTexCoord2f (1.0,1.0); glVertex2f (0+GLW,0.0);
                        glTexCoord2f (1.0,0.0); glVertex2f (0+GLW,GLH);
  
                glEnd();

      
        if(!eP[cam]){
        //     fprintf(stderr,"SUBSTACT\n");
          //   fflush(stderr);
            glBlendEquation(GL_FUNC_SUBTRACT);
            // fprintf(stderr,"GL_ONE,GL_ONE\n");
            // fflush(stderr);

            glBlendFunc(GL_ONE,GL_ONE);
           //  fprintf(stderr,"pPatterns[cam]\n");
           //  fflush(stderr);

                glBindTexture(GL_TEXTURE_2D, pPatterns[cam]);
                glColor4f(1,1,1,1);
           //  fprintf(stderr,"GL_TRIANGLE_STRIP\n");
          //   fflush(stderr);

                glBegin(GL_TRIANGLE_STRIP);
                        glTexCoord2f (0.0,1.0); glVertex2f (0.0,0.0);
                        glTexCoord2f (0.0,0.0); glVertex2f (0.0,0+GLH);
                        glTexCoord2f (1.0,1.0); glVertex2f (0+GLW,0.0);
                        glTexCoord2f (1.0,0.0); glVertex2f (0+GLW,GLH);
  
                glEnd();
           //  fprintf(stderr,"ADD\n");
           //  fflush(stderr);

          glBlendEquation(GL_FUNC_ADD);

        }else{
          fprintf(stderr,"Need pattern, but it is not ready!\n");
          fflush(stderr);

        
        }

                    
      if(shlen>=99)
          shlen=98;
      glBindTexture(GL_TEXTURE_2D, ptmpPatterns[shlen++]);
      glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, GLW, GLH, 0);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
       double fx,fy;
       findInScreen(fx,fy);
//       x <-> fx;
  //     y <-> fy;
       addGridPoint(cam,x,y,fx,fy);
       glBlendFunc(GL_SRC_ALPHA,GL_ONE);
//        eP[cam]=0;

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        glBindTexture(GL_TEXTURE_2D, tmpt);
        glColor4f(1,1,1,1);
        glBegin(GL_TRIANGLE_STRIP);
                glTexCoord2f (0.0,1.0); glVertex2f (0.0,0.0);
                glTexCoord2f (0.0,0.0); glVertex2f (0.0,0+GLH);
                glTexCoord2f (1.0,1.0); glVertex2f (0+GLW,0.0);
                glTexCoord2f (1.0,0.0); glVertex2f (0+GLW,GLH);
  
       glEnd();

    
    


}
int pParity=0;
int shframe=0;
void processPaint(){
    if(!initPaint){
          initPaint=1;
          glGenTextures(OCVTH, pFrames);
          glGenTextures(OCVTH, pPatterns);
          glGenTextures(100, ptmpPatterns);    
    }
   if(calState==0){
        if(getOpt("calibrateCam0")>0.5){
            calState=1;
            calCam=0;        
            calTimer=0;
            calSubState=0;
            clearPattern(calCam);
        }
         if(getOpt("calibrateCam1")>0.5){
            calState=1;
            calCam=1;        
            calTimer=0;
            calSubState=0;
            clearPattern(calCam);
        }      
         if(getOpt("calibrateCam2")>0.5){
            calState=1;
            calCam=2;        
            calTimer=0;
            calSubState=0;
            clearPattern(calCam);
        }  
    }
    if(calState==1){
            if(calTimer>CAL1T){
                calTimer=0;
                if(calSubState<7){
                    calSubState++;
                }else{
                    calState=2;            
                    shframe=0;
                    calTimer=0;

                }
            
            }
            calibrate=1;
            
            calibrateX=cals1x[calSubState];
            calibrateY=cals1y[calSubState];
            calibrateQ=0.1;
            int fr;
            fr=getFrame(calCam,&(frame),&(frameh),&(framew));
            if(!fr){
                calTimer++;
                if(calSubState == 0){
                    if(1||calTimer>CAL1T/2){
                       fprintf(stderr,"add2pattern ... ");
                       fflush(stderr);
                       add2pattern(calCam,frame,frameh,framew);
                       fprintf(stderr,"done!\n");
                       fflush(stderr);
    
                    }
                }else{
                    fprintf(stderr,"callibrateCorner ... ");
                    fflush(stderr);
                    callibrateCorner(calCam,frame,frameh,framew,cals1x[calSubState],cals1y[calSubState]);
                       fprintf(stderr,"done!\n");
                       fflush(stderr);
                
                }
            
            }
          
    }
    if(calState==2){
        calTimer++;
        if(calTimer>3){
           shframe++;
           calTimer=0;
            if(shframe>=shlen){
                calState=3;    
                calTimer=0;
                shframe=0;
            } 
        }
        pShow=pPatterns[calCam];
        calibrate=2;
        
        
    }
     if(calState==3){
        calTimer++;
        if(calTimer>3){
           shframe++;
           calTimer=0;
            if(shframe>=shlen)
                calState=4;     
        }
        pShow= ptmpPatterns[shframe];
       
        calibrate=2;
        
        
    }
    
    
    if(calState==4){
        calState=0;
        setOpt("calibrateCam0",0);
        setOpt("calibrateCam1",0);
        setOpt("calibrateCam2",0);
        calibrate=0;
    }
    

}
#endif
