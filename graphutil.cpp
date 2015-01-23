#ifndef GRAPHUTILMOD
#define GRAPHUTILMOD
#include"SDL/SDL.h"
int GLH,GLW;
int REALW,REALH;
double spiral=0.0;
double mega=0.0;
#include"filters/SPIRAL.cpp"
#include"filters/nosound.cpp"
#include"hsv.cpp"
int makeScreenShoot=0;
char* screenShoot=NULL;
int screenShootW,screenShootH;

#ifdef GLBILD
#include "mygl.h"

double lredgamma, lgreengamma,lbluegamma;

void applyGamma(){
    double allgamma,redgamma, greengamma,bluegamma;
    allgamma=3*getOpt("allgamma");
    redgamma=allgamma*getOpt("redgamma");
    greengamma=allgamma*getOpt("greengamma");
    bluegamma=allgamma*getOpt("bluegamma");
    if(fabs(lredgamma-redgamma)+ fabs(lgreengamma-greengamma)+fabs(lbluegamma-bluegamma)>0.01){
       lredgamma=redgamma;
       lgreengamma=greengamma;
       lbluegamma=bluegamma;
       if(-0.5>SDL_SetGamma(redgamma, greengamma,bluegamma)){
            fprintf(stderr,"No gamma ;( \n");
    
    
       }else{
           fprintf(stderr,"Gamma! :) \n");
    
    
       }
    }
}
//#include <GL/glew.h>

//#include <GL/gl.h>
GLuint sct;
GLuint lsct;
GLuint vct[OCVTH];
GLuint readyBufTex;
GLuint tmpt;
GLuint tex_qs;
GLuint tex_timbre;
GLuint  tex_qsPlate;
GLuint tmp2t;
GLuint tex_wave2sceen;
GLuint tex_qsSurf;
GLuint tex_touch;
GLuint maskt;
GLuint itex;
GLuint lctex[100];
GLuint soundSpeqtex;
GLuint soundSpeqSquaretex;

int putPixelMetod=0;
int glscinit =0;

/*
void startGlPif(){
    
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70,(double)640/480,1,1000);

  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glPushMatrix();
            
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(0,0,10000 ,0,0,0, 0,1,0);
  glDisable(GL_BLEND);
 
 // glEnable(GL_BLEND);
 // glEnable(GL_DEPTH_TEST);
  glPointSize(2.0);

  glBegin(GL_LINE_STRIP);
  

}
void endGlPif(){
  glDisable(GL_BLEND);
  glDisable (GL_DEPTH_TEST);

  glEnd();
  glFlush();
  SDL_GL_SwapBuffers();
  glPopMatrix();
  glPopAttrib();


}
*/

void blur_tex_zoom_in(GLuint tex, int passes,int WIDTH,int HEIGHT)
{
    int i;
    /*double s,c;
    s=sin(3.14/180);
    c=cos(3.14/180);
    */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, tex);
    while (passes > 0) {
        for (i = 0; i < 2; i++) {
            glColor4f(1.0f,1.0f,1.0f,1.0 / (i+1));
            glBegin(GL_TRIANGLE_STRIP);
                glTexCoord2f(0 + (i*0.5)/WIDTH, 1 - (i*0.5)/HEIGHT); glVertex2f(0, 0);
                glTexCoord2f(0 + (i*0.5)/WIDTH, 0 + (i*0.5)/HEIGHT); glVertex2f(0, HEIGHT);
                glTexCoord2f(1 - (i*0.5)/WIDTH, 1 - (i*0.5)/HEIGHT); glVertex2f(WIDTH, 0);
                glTexCoord2f(1 - (i*0.5)/WIDTH, 0 + (i*0.5)/HEIGHT); glVertex2f(WIDTH, HEIGHT);
            glEnd ();
        }
        glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, WIDTH, HEIGHT, 0);
        passes--;
    }
    glDisable(GL_BLEND);
}
//extern double glOpt[4];
#include"glopts.cpp"
extern struct layer *mask2;

double ROTASYM=1;
double roty(double x,double y,double ang){
 	return 0.5 + cos(ang) * (y-0.5) - sin(ang) * (x-0.5)*GLW/GLH*ROTASYM;

}
double rotx(double x,double y,double ang){
  return  0.5+ cos(ang) * (x-0.5) + sin(ang) * (y-0.5)*GLH/GLW/ROTASYM;


}

struct SDL_Surface *scrshooot(){
  unsigned int *screenPixels = new unsigned int[GLW*GLH*4];
  struct SDL_Surface *bitmap;
  if (screenPixels){
    // Read the pixels
    glReadPixels(0, 0, GLW, GLH, GL_RGBA, GL_UNSIGNED_INT, screenPixels);
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
      bitmap = SDL_CreateRGBSurfaceFrom(screenPixels, GLW, GLH, 32, GLW*4,
      0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    #else
      bitmap = SDL_CreateRGBSurfaceFrom(screenPixels, GLW, GLH, 32, GLW*4,
      0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
    #endif
    
    // Write the file
    //SDL_SaveBMP(bitmap, "screenshot.bmp");
    
    // Free everything
  //  SDL_FreeSurface(bitmap);
    delete[] screenPixels;
  }
  return bitmap;
}
char *scrshooot(int &w,int&h){
  unsigned int *screenPixels =(unsigned int*) malloc(GLW*GLH*sizeof(unsigned int));
  unsigned int *screenPixels2 =(unsigned int*) malloc(GLW*GLH*sizeof(unsigned int));
  
  struct SDL_Surface *bitmap;
  w=0;
  h=0;
  if (screenPixels){
    // Read the pixels
    w=GLW;
    h=GLH;
    glReadPixels(0, 0, GLW, GLH, GL_BGRA, GL_UNSIGNED_BYTE, screenPixels);
    
    // Write the file
    //SDL_SaveBMP(bitmap, "screenshot.bmp");
    
    // Free everything
  //  SDL_FreeSurface(bitmap);
    w=GLW;
    h=GLH;
    if(screenPixels2){
        int x,y;
        for(x=0;x<w;x++)
            for(y=0;y<h;y++){
                screenPixels2[x+y*w]=screenPixels[x+(h-1-y)*w];
            }
        free(screenPixels);
        return (char*)screenPixels2;

    }
  }
  return (char*)screenPixels;
}
extern volatile int recVideo;
extern volatile int recVideoImgReady[RECFRN];
extern volatile int recVideoImgW;
extern volatile int recVideoImgH;
extern volatile Uint32* volatile recVideoImgPtr[RECFRN];
extern volatile Uint32 recVideoImgFrN[RECFRN];
unsigned int recFrN;
void sendFrameToRec(){
  if(!recVideo)
    return;
  
  for(i=0;i<RECFRN;i++){
      if(recVideoImgPtr[i]==NULL){
        recVideoImgPtr[i]=(Uint32*)malloc(GLW*GLH*3);
        recVideoImgW=GLW;
        recVideoImgH=GLH;
      }
    }  
  
  
/*  if(recVideoImgPtr[0]!=NULL&&    (recVideoImgW!=GLW||
    recVideoImgH!=GLH)){
    free((unsigned int *)recVideoImgPtr);
    recVideoImgPtr=(Uint32*)malloc(GLW*GLH*3);
    recVideoImgW=GLW;
    recVideoImgH=GLH;
  }*/
  int saved=0;
  for(i=0;i<RECFRN;i++){
      if(recVideoImgReady[i]==0){
          if(recVideoImgPtr[i]==NULL)
             continue;  
          glReadPixels(0, 0, GLW, GLH, GL_BGR, GL_UNSIGNED_BYTE,(unsigned int *) recVideoImgPtr[i]);
          recVideoImgFrN[i]=GetTickCount();
       //   recFrN++;
          recVideoImgReady[i]=1;
      
      
          return;

      }
      //break;
  
   }
   fprintf(stderr,"Rec Video quie overflowed\n");
  

}


#define GLTEXDELAYN 20
GLuint delayTex[GLTEXDELAYN];
double delayGlOpt[GLTEXDELAYN][GLOPTS];
int delayGlCount[GLTEXDELAYN];
int delayTexCur=0;
extern GLuint colorTexture;
extern int GLLINE;
extern int BADBUF[800*600];
void mixBWSizedOrGL_tex(struct layer*l,double value,double middle,GLuint tex,double alpha,int screenW,int screenH);

void screen2GlInter(SDL_Surface* screen,double alpha,double middle){
        glBindTexture(GL_TEXTURE_2D, sct);
        if(mode!=5 || !GLLINE){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screen->w, screen->h,
            0, GL_RGBA, GL_UNSIGNED_BYTE, screen->pixels);
            //blur_tex_zoom_in(sct,9,screen->w, screen->h);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
       }else{
       }
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE); 
        mixBWSizedOrGL_tex(mask2,1,-256+2*256*middle,sct,alpha,GLW,GLH);
}


void screen2Gl(SDL_Surface* screen,double alpha){
        glBindTexture(GL_TEXTURE_2D, sct);

        if(mode!=5 || !GLLINE){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screen->w, screen->h,
            0, GL_RGBA, GL_UNSIGNED_BYTE, screen->pixels);
            //blur_tex_zoom_in(sct,9,screen->w, screen->h);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
       }else{
           // glBindTexture(GL_TEXTURE_2D, colorTexture);

      //      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screen->w, screen->h,
        //    0, GL_BGR, GL_UNSIGNED_BYTE, BADBUF);
            //blur_tex_zoom_in(sct,9,screen->w, screen->h);
          //  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
       
       
       
       }
//          glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
       //   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
   //
   //    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  //   glBlendFunc(GL_ZERO,GL_ONE);
// glBlendFunc(GL_DST_COLOR, GL_SRC_COLOR) ;
 
 
 
         glBlendFunc(GL_SRC_ALPHA,GL_ONE); 
 
     //     glBlendFunc(GL_ZERO,GL_ONE); 
// glBlendFunc(GL_DST_COLOR, GL_SRC_COLOR); 
 
 
 
 //
 //  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
     // glBlendFunc(GL_ONE , GL_ONE);
  
   //    glBlendFunc(GL_SRC_ALPHA,GL_SRC_ALPHA);
 //       glDisable(GL_BLEND);

        //glBindTexture(GL_TEXTURE_2D, sct);
        glColor4f(1.0f,1.0f,1.0f,alpha);
        glBegin(GL_TRIANGLE_STRIP);
                glTexCoord2f (0.0,0.0); glVertex2f (0.0,0.0);
                glTexCoord2f (0.0,1.0); glVertex2f (0.0,0+GLH);
                glTexCoord2f (1.0,0.0); glVertex2f (0+GLW,0.0);
                glTexCoord2f (1.0,1.0); glVertex2f (0+GLW,GLH);
  
//  GLW/2,GLH/2, 3*GLW/4, 3*GLH/4
  /*              glTexCoord2f (0.0,0.0); glVertex2f (GLW/2,GLH/2);
                glTexCoord2f (0.0,1.0); glVertex2f (GLW/2,GLH/2+GLH);
                glTexCoord2f (1.0,0.0); glVertex2f (0+GLW+GLW/2,GLH/2);
                glTexCoord2f (1.0,1.0); glVertex2f (0+GLW+GLW/2,GLH/2+GLH);
  */
       glEnd();

        //glEnable(GL_BLEND);

}

double videoZoom[OCVTH];
double videoAspect[OCVTH];
double videoPosX[OCVTH];
double videoPosY[OCVTH];

void * genLCircle(double p,int w,int h){
    Uint32*b,*bb;
    b=(Uint32*)malloc(w*h*sizeof(Uint32));
    if(b==NULL)
        return NULL;
    bb=b;
    for(int y=0;y<h;y++)
        for(int x=0;x<w;x++,bb++){
            double l,ax,ay;
            ay=(y-h/2.)/(h/2.);
            ax=(x-w/2.)/(w/2.);
            l=1-pow(sqrt(ax*ax+ay*ay)/sqrt(2.),p);
            Uint32 c;
            if(l<0)
                l=0;
            if(l>1)
                l=1;
            c=l*255;
            *bb=c | c*256 | c*256*256 |c*256*(unsigned)256*256;
        }
    
    return b;
}

double llcp=-100;
void applyLCircle(double p){
    void*ptr;
    return;
    if(fabs(llcp-p)>0.0001){
        
        ptr=genLCircle(p,GLW,GLH);    
        if(ptr==NULL)
            return;
        glBindTexture(GL_TEXTURE_2D, lctex[0]);
        glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, GLW, GLH,
                0, GL_RGBA, GL_UNSIGNED_BYTE, ptr);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    free(ptr);
    llcp=p;
  }
  glBlendFunc(GL_ZERO,GL_SRC_ALPHA);
  glBindTexture(GL_TEXTURE_2D, lctex[0]);
  glColor4f(1.0f,1.0f,1.0f,1);
 /* glBegin(GL_TRIANGLE_STRIP);
       glTexCoord2f (0,0); glVertex2f (0.0,GLH);
       glTexCoord2f (0,1); glVertex2f (0.0,0);
       glTexCoord2f (1,0); glVertex2f (0+GLW,GLH );
       glTexCoord2f (1,1); glVertex2f (0+GLW,0);
  glEnd();
  */
  glBindTexture(GL_TEXTURE_2D, tmp2t);
  glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, GLW, GLH, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE);
  glBindTexture(GL_TEXTURE_2D, tmp2t);
        glColor4f(1,1,1,1);
        glBegin(GL_TRIANGLE_STRIP);
                glTexCoord2f (0.0,1.0); glVertex2f (0.0,0.0);
                glTexCoord2f (0.0,0.0); glVertex2f (0.0,0+GLH);
                glTexCoord2f (1.0,1.0); glVertex2f (0+GLW,0.0);
                glTexCoord2f (1.0,0.0); glVertex2f (0+GLW,GLH);
  
       glEnd();

}
void placeTexOnGlScreen(double alpha,int th,Uint32 thTex){
    //    fprintf(stderr,"VIDEOPLAY\n");
          double zoomx,zoom,zoomTang;
          double zoomy;
//          double alpha;
          double shiftA,shiftL;
          double x1,y1,x2,y2;
          zoom=(videoZoom[th]-0.5);
          zoomTang=(videoAspect[th]-0.5);

          zoomx=zoom+zoomTang;
          zoomy=zoom-zoomTang;
          
          
          x1=zoomx+videoPosX[th]-0.5;
          y1=zoomy+videoPosY[th]-0.5;
          x2=videoPosX[th]+0.5-zoomx;
          y2=videoPosY[th]+0.5-zoomy;
          
          
//          ROTASYM=my_glOpt[7]/0.5;



        glBindTexture(GL_TEXTURE_2D, thTex);
        if(alpha>0.000001){
           glEnable(GL_BLEND);
           glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA/*GL_ONE*/);
           glColor4f(1.0f,1.0f,1.0f,alpha);
           glBegin(GL_TRIANGLE_STRIP);
                glTexCoord2f (x1,y1); glVertex2f (0.0,0.0);
                glTexCoord2f (x1,y2); glVertex2f (0.0,0+GLH);
                glTexCoord2f (x2,y1); glVertex2f (0+GLW,0.0);
                glTexCoord2f (x2,y2); glVertex2f (0+GLW,GLH);
           glEnd();
       }
}
void placeTexOnGlScreen(void*p,int h,int w,double alpha,int th){
    //    fprintf(stderr,"VIDEOPLAY\n");
          double zoomx,zoom,zoomTang;
          double zoomy;
//          double alpha;
          double shiftA,shiftL;
          double x1,y1,x2,y2;
          zoom=(videoZoom[th]-0.5);
          zoomTang=(videoAspect[th]-0.5);

          zoomx=zoom+zoomTang;
          zoomy=zoom-zoomTang;
          
          
          x1=zoomx+videoPosX[th]-0.5;
          y1=zoomy+videoPosY[th]-0.5;
          x2=videoPosX[th]+0.5-zoomx;
          y2=videoPosY[th]+0.5-zoomy;
          
          
//          ROTASYM=my_glOpt[7]/0.5;



        glBindTexture(GL_TEXTURE_2D, vct[th]);
        if(p!=NULL){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h,
            0, GL_BGR, GL_UNSIGNED_BYTE, p);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

        }        

//        glBindTexture(GL_TEXTURE_2D, sct);
        if(alpha>0.000001){
           glEnable(GL_BLEND);
           glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA/*GL_ONE*/);

           glColor4f(1.0f,1.0f,1.0f,alpha);
           glBegin(GL_TRIANGLE_STRIP);
                glTexCoord2f (x1,y1); glVertex2f (0.0,0.0);
                glTexCoord2f (x1,y2); glVertex2f (0.0,0+GLH);
                glTexCoord2f (x2,y1); glVertex2f (0+GLW,0.0);
                glTexCoord2f (x2,y2); glVertex2f (0+GLW,GLH);
           glEnd();
       }
}


extern int drawGLZ;
char*video[OCVTH];
int videoh[OCVTH];
int videow[OCVTH];


void mixBWSizedOrGL(struct layer*l,double value,double middle,char*img,int imgw,int imgh,double alpha,int screenW,int screenH);


void mixBWSizedOrGL(struct layer*l,double value,int middle,Uint32 color,int tex,int screenW,int screenH);
  void mixBWSizedOrGL_Transform(struct layer*l,double value,int middle,Uint32 color,int tex,int screenW,int screenH,

double ax,double ay,
double bx,double by);
void mixBWSizedOrGL_Transform_Op(struct layer*l,double value,int middle,Uint32 color,int tex,int screenW,int screenH,
double bx,double ay,
double ax,double by,double op);
void mixBWSizedOrGL_Transform_Op_Fast(struct layer*l,double value,int middle,Uint32 color,int tex,int screenW,int screenH,
double bx,double ay,
double ax,double by,double op);


void mixBWSizedOrGLOp_Fast(struct layer*l,double value,int middle,Uint32 color,int tex,int screenW,int screenH,double op);

void mixBWSizedOrGLOp(struct layer*l,double value,int middle,Uint32 color,int tex,int screenW,int screenH,double op);

/*inline void zeroone(double &a){
    if(a<0.)
        a=0.;
    if(a>1.)
        a=1.;

}*/

inline void transform(double sp,double me,double &x,double&y){
    double r,a;
    x-=0.5;
    y-=0.5;
    r=sqrt(x*x+y*y);
    a=atan2(y,x)+r*sp*M_PI;
    r=pow(r*2,1-me)/2;
    x=cos(a+r*sp)*r+0.5;
    y=sin(a+r*sp)*r+0.5;
}

void applyInterferMaskbyBrightness(struct layer*l,double op){
/*    glBindTexture(GL_TEXTURE_2D, tmpt);
//        glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, 2*GLW, 2*GLH, 0);
    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, GLW, GLH, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);//GL_ONE_MINUS_SRC_ALPHA

    glColor4f(1.0f,1.0f,1.0f,1);
    
    glBegin(GL_TRIANGLE_STRIP);
       glTexCoord2f (0.0,0.0); glVertex2f (0.0,0.0);
       glTexCoord2f (0.0,1.0); glVertex2f (0.0,0+GLH);
       glTexCoord2f (1.0,0.0); glVertex2f (0+GLW,0.0);
       glTexCoord2f (1.0,1.0); glVertex2f (0+GLW,GLH);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, maskt);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, l->w, l->h,
            0, GL_ALPHA, GL_UNSIGNED_BYTE, l->p);

    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(1.0f,1.0f,1.0f,op1);
    
    glBegin(GL_TRIANGLE_STRIP);
       glTexCoord2f (0.0,0.0); glVertex2f (0.0,0.0);
       glTexCoord2f (0.0,1.0); glVertex2f (0.0,0+GLH);
       glTexCoord2f (1.0,0.0); glVertex2f (0+GLW,0.0);
       glTexCoord2f (1.0,1.0); glVertex2f (0+GLW,GLH);
    glEnd();



    glBindTexture(GL_TEXTURE_2D, tmpt);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);//GL_ONE_MINUS_SRC_ALPHA
    glColor4f(1.0f,1.0f,1.0f,op2);
    glBegin(GL_TRIANGLE_STRIP);
       glTexCoord2f (0.0,0.0); glVertex2f (0.0,0.0);
       glTexCoord2f (0.0,1.0); glVertex2f (0.0,0+GLH);
       glTexCoord2f (1.0,0.0); glVertex2f (0+GLW,0.0);
       glTexCoord2f (1.0,1.0); glVertex2f (0+GLW,GLH);
    glEnd();

*/
}
void saveGlScreen(){
    glEnable(GL_TEXTURE_2D);
  
    glBindTexture(GL_TEXTURE_2D, tmpt);
    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, GLW, GLH, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}
void saveGlScreen2Tex(GLuint tex){
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, tex);
    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, GLW, GLH, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  //  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

//    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}
void restoreGlScreen(){
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

void transformScreen(double sp,double me,double step){
    step=1-step;
    if(step<0.02)
        step=0.02;
    
    glBindTexture(GL_TEXTURE_2D, tmpt);
//        glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, 2*GLW, 2*GLH, 0);
    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, GLW, GLH, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glColor4f(1,1,1,1);

    double x,y,xx,yy,ax,ay,bx,by,cx,cy,dx,dy;
    for(x=0;x<1;x+=step){
        for(y=0;y<1;y+=step){
            xx=x+step;
            yy=y+step;
            if(xx>1.)
                xx=1.;
            if(yy>1.)
                yy=1.;
            ax=x;
            ay=y;
            bx=xx;
            by=y;
            cx=xx;
            cy=yy;
            dx=x;
            dy=yy;
            transform(sp,me,ax,ay);
            transform(sp,me,bx,by);
            transform(sp,me,cx,cy);
            transform(sp,me,dx,dy);
                  glBegin(GL_QUADS);
                  glTexCoord2f (ax,ay); glVertex2f (x*GLW,GLH-y*GLH);
                  glTexCoord2f (bx,by); glVertex2f (xx*GLW,GLH-y*GLH);
                  glTexCoord2f (cx,cy); glVertex2f (xx*GLW,GLH-yy*GLH);
                  glTexCoord2f (dx,dy); glVertex2f (x*GLW,GLH-yy*GLH);
  
           glEnd();
            
                
        }
    }
    
}

double calcScrBright(){
        glBindTexture(GL_TEXTURE_2D, tmpt);
        glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, GLW, GLH, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        
/*        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glBindTexture(GL_TEXTURE_2D, tmpt);*/
        glColor4f(1,1,1,1);
        glBegin(GL_TRIANGLE_STRIP);
                glTexCoord2f (0.0,1.0); glVertex2f (0.0,0.0);
                glTexCoord2f (0.0,0.0); glVertex2f (0.0,0+1);
                glTexCoord2f (1.0,1.0); glVertex2f (0+1,0.0);
                glTexCoord2f (1.0,0.0); glVertex2f (0+1,1);
  
       glEnd();
       
       Uint32 pixels[3];
       glReadPixels(0,GLH-1, 1, 1, GL_RGB, GL_UNSIGNED_INT, pixels);

/*        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        glBindTexture(GL_TEXTURE_2D, tmpt);
        glColor4f(1,1,1,1);
        glBegin(GL_TRIANGLE_STRIP);
                glTexCoord2f (0.0,1.0); glVertex2f (0.0,0.0);
                glTexCoord2f (0.0,0.0); glVertex2f (0.0,0+GLH);
                glTexCoord2f (1.0,1.0); glVertex2f (0+GLW,0.0);
                glTexCoord2f (1.0,0.0); glVertex2f (0+GLW,GLH);
  
       glEnd();
*/
{
        glColor4f(0,0,0,1);
        glBegin(GL_TRIANGLE_STRIP);
//                glTexCoord2f (0.0,1.0);
                 glVertex2f (0.0,0.0);
  //              glTexCoord2f (0.0,0.0); 
                glVertex2f (0.0,0+1);
                //glTexCoord2f (1.0,1.0); 
                glVertex2f (0+1,0.0);
                //glTexCoord2f (1.0,0.0);
                 glVertex2f (0+1,1);
  
       glEnd();


}

    
    double res;
    res=pixels[0]+(double)pixels[1]/4+(double)pixels[2]/4;
//    fprintf(stderr,"bri:%lf ; ",res);
  //  fprintf(stderr,"%d %d %d\n",pixels[0],pixels[1],pixels[2]);

    return res;


}
double lbright=-1;
int calibrate=0;
//int calibrateCam=-1;
double calibrateX=1;
double calibrateY=1;
double calibrateQ=0.5;
 
 
void drawCalibatePoint(double x,double y,double q){
    double x1,y1,x2,y2,w,h;
    w=q*GLW;
    h=q*GLH;
    x1=(GLW-w)*x;
    y1=(GLH-h)*y;
    x2=x1+w;
    y2=y1+h;
    glDisable(GL_TEXTURE_2D);
    glColor4f(1,1,1,1);
    glBegin(GL_QUADS);
            glVertex2f (x1,y1);
            glVertex2f (x1,y2);
            glVertex2f (x2,y2);
            glVertex2f (x2,y1);
    glEnd();
    glEnable(GL_TEXTURE_2D);

}

void showGl(double op,GLuint t){
        if(op<0.000001)
             return;
        glBindTexture(GL_TEXTURE_2D, t);
        glColor4f(1,1,1,op);
        glBegin(GL_TRIANGLE_STRIP);
                glTexCoord2f (0.0,1.0); glVertex2f (0.0,0.0);
                glTexCoord2f (0.0,0.0); glVertex2f (0.0,0+GLH);
                glTexCoord2f (1.0,1.0); glVertex2f (0+GLW,0.0);
                glTexCoord2f (1.0,0.0); glVertex2f (0+GLW,GLH);
  
       glEnd();



}
int nframe;
#define DISTEXRES 64 
Uint32 disTex[256];
Uint32 disTex1d[256];

void genDis(Uint32*ptr,int value){
    int x,y;
    if(value==0)
        for(x=0;x<DISTEXRES*DISTEXRES;x++)
            ptr[x]=0xffffffff;
    else
    for(x=0;x<1000*DISTEXRES/256*DISTEXRES/256;x++){
        ptr[rand()%(DISTEXRES) +DISTEXRES*(rand()%(DISTEXRES))]=0x000000ff;//0;//0xffffff00;
    
    }

}
void genDis1d(Uint32*ptr,int value){
    int x,y;
    if(value==0)
        for(x=0;x<DISTEXRES;x++)
            ptr[x]=0xffffffff;
    else
    for(x=0;x<10*DISTEXRES/256;x++){
        ptr[rand()%(DISTEXRES)]=0x000000ff;//0;//0xffffff00;
    
    }

}
void genDisTex(){
    Uint32 tex[DISTEXRES*DISTEXRES];
         glEnable(GL_TEXTURE_2D);

    for(i=0;i<256;i++){
        genDis(tex,i);
              
        glBindTexture(GL_TEXTURE_2D, disTex[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, DISTEXRES, DISTEXRES,
        0, GL_BGRA, GL_UNSIGNED_BYTE, tex);        
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,  GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_REPEAT);
  
    
    
    }
         glEnable(GL_TEXTURE_1D);

    for(i=0;i<256;i++){
        genDis1d(tex,i);
              
        glBindTexture(GL_TEXTURE_1D, disTex1d[i]);
        glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, DISTEXRES, 
        0, GL_BGRA, GL_UNSIGNED_BYTE, tex);        
                glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S,  GL_REPEAT);
                glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T,  GL_REPEAT);
  
    
    
    }
//         glDisable(GL_TEXTURE_2D);
disTex[0]=0;
disTex1d[0]=0;
glDisable(GL_TEXTURE_1D);
}
void GLShowScreen(SDL_Surface* screen){
  //        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //    glDisable(GL_DEPTH_TEST);
//    fprintf(stderr,"!\n");
      nframe++;
      applyGamma();
        double my_glOpt[GLOPTS];
        int ndelay;
        calcGlOpt(my_glOpt);
         glEnable(GL_TEXTURE_2D);
    char rb[128];

    for(int th=0;th<OCVTH;th++){
   //     vfop1[th]=calcOpt(multiTh(th,"videoFile1",rb));
     //   vfop2[th]=calcOpt(multiTh(th,"videoFile2",rb));
       // vfop3[th]=calcOpt(multiTh(th,"videoFile3",rb));


       videoZoom[th]=calcOpt(multiTh(th,"videoZoom",rb));
       videoAspect[th]=calcOpt(multiTh(th,"videoAspect",rb));
       videoPosX[th]=calcOpt(multiTh(th,"videoPosX",rb));
       videoPosY[th]=calcOpt(multiTh(th,"videoPosY",rb));
    }
       // if(my_glOpt[0]>0.0001||)
        
//        glViewport(0,0, GLW, GLH);
/*
        glMatrixMode(GL_PROJECTION);
//        glPushMatrix();
        glLoadIdentity();
        glOrtho(0.0f, GLW, GLH, 0.0f, -1.0f, 1.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
         glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
*/
         glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

     glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if(!glscinit){
        glscinit=1;
        delayTexCur=0;
        glGenTextures(1, &sct);
        glGenTextures(1, &lsct);
        glGenTextures(OCVTH, vct);
        glGenTextures(1, &tmpt);
        glGenTextures(1, &tex_qs);
        glGenTextures(1, &tex_timbre);
        glGenTextures(1, &tex_qsPlate);
        glGenTextures(1, &tex_qsSurf);
        glGenTextures(1, &tex_wave2sceen);
        glGenTextures(1, &tex_touch);
        glGenTextures(1, &soundSpeqtex);
        glGenTextures(1, &soundSpeqSquaretex);


        glGenTextures(1, &itex);
        glGenTextures(1, &tmp2t);


        glGenTextures(1, &readyBufTex);
        glGenTextures(1, &maskt);
        glGenTextures(100,lctex);
        glGenTextures(GLTEXDELAYN,delayTex);
        glGenTextures(3, ocvTex);

        glGenTextures(256, disTex);
        glGenTextures(256, disTex1d);
        genDisTex();


//        [];

        
        
        glBindTexture(GL_TEXTURE_2D, lsct);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screen->w, screen->h,
        0, GL_BGRA, GL_UNSIGNED_BYTE, screen->pixels);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        
 
        return;
    }else{
//        if(my_glOpt[1]>0.05)
  //          blur_tex_zoom_in(lsct,my_glOpt[1]*10,GLW, GLH);
//            #define GLOPTS 4
//double glOpt[GLOPTS];
//double lglOpt[GLOPTS];

    }
    double vfop1[OCVTH];
    double vfop2[OCVTH];
    double vfop3[OCVTH];
    Uint32 thTex[OCVTH];
    for(int th=0;th<OCVTH;th++){
        vfop1[th]=calcOpt(multiTh(th,"videoFile1",rb));
        vfop2[th]=calcOpt(multiTh(th,"videoFile2",rb));
        vfop3[th]=calcOpt(multiTh(th,"videoFile3",rb));


        if(vfop1[th]+vfop2[th]+vfop3[th]>0.00001){
            int fr;
            
            fr=getFrame(th,thTex[th]);
            double vfsize=0;
            
            vfsize=getOpt("vf1size");
//.            mixBWSizedOrGL
            if(vfsize<=0.0001){
                if(fr==0)
                    placeTexOnGlScreen(vfop1[th],th,thTex[th]);
                else
                    placeTexOnGlScreen(vfop1[th],th,thTex[th]);

            }else{
                
//                mixBWSizedOrGL(mask2,1,vfsize,video,videow,videoh,vfop1,screenW,screenH);
            
            }
     }
   }
   double vfsize=0;
            
   vfsize=getOpt("pifInterSize1");
//.
   if(vfsize<0.0001){
       screen2Gl(screen,1.f-my_glOpt[14]);
       showGl(calcOpt("qsLayer1"),tex_qs);
       showGl(calcOpt("qsSurf1"),tex_qsSurf);

       
       showGl(calcOpt("qsPlateOp1"),tex_qsPlate);
       showGl(calcOpt("soundSpeq1"),soundSpeqtex);
       showGl(calcOpt("soundSpeqSquare1"),soundSpeqSquaretex);

//       fprintf(stderr,"soundSpeq1_place\n");

       showGl(calcOpt("wave2sceen1"),tex_wave2sceen);
//         drawSpec(tex_touch,calcOpt("touchSpeq_r")*2,calcOpt("touchSpeq_a1")*2*M_PI,calcOpt("touchSpeq_a2")*2*M_PI,calcOpt("touchSpeq_fov")*2*M_PI){
       showGl(getOpt("touchSpeq1"),tex_touch);
 
        
//        getOpt("")


   }else{
              double op=calcOpt("pifInterOp1");
               double op2=calcOpt("pifInterOp1_q");

       screen2Gl(screen,(1.f-my_glOpt[14])*op);
       showGl(calcOpt("qsLayer1"),tex_qs);
//                 drawTimbres(tex_timbre,calcOpt("timbre_a1")*2*M_PI,calcOpt("timbre_a2")*2*M_PI,calcOpt("timbre_r")*10,calcOpt("timbre_fov")*160+0.0001);
       showGl(calcOpt("timbre1"),tex_timbre);

       
       showGl(calcOpt("qsSurf1"),tex_qsSurf);

       showGl(calcOpt("qsPlateOp1"),tex_qsPlate);
       showGl(calcOpt("soundSpeq1"),soundSpeqtex);
       showGl(calcOpt("soundSpeqSquare1"),soundSpeqSquaretex);
             
             
       screen2GlInter(screen,(1.f-my_glOpt[14])*op2,vfsize);
   
   }
    
    if(my_glOpt[0]>0.0001){
  //  fprintf(stderr,"VIDEOREVERB\n");
     //   glBlendEquation(GL_);
      vfsize=getOpt("pifInterSize2");
       glEnable(GL_BLEND);
       glBlendFunc(GL_SRC_ALPHA,getOpt("glBlendMetod")>0.5?GL_ONE_MINUS_SRC_ALPHA:GL_ONE);//);
 
   // glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

  //        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);//);

  //!!          glBlendFunc(GL_SRC_ALPHA,GL_SRC_ALPHA);//);
      //    glBlendFunc(GL_SRC_COLOR,GL_SRC_COLOR);//);

       //   glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);//);
        
          glBindTexture(GL_TEXTURE_2D, lsct);
//          double ap;
  //        ap=getOpt("antiPuddle");
    //      fprintf(stderr,"ap:%f\n",ap);
  //        glColor4f(my_glOpt[0],my_glOpt[0],my_glOpt[0],my_glOpt[0]);
        glColor4f(1,1,1,my_glOpt[0]);
//glBlendColor(1,1,1,my_glOpt[0]);
          double zoomx,zoom,zoomTang;
          double zoomy;
          double alpha;
          double shiftA,shiftL;
          double x1,y1,x2,y2;
          zoom=(my_glOpt[2]-0.5)/10.;
          zoomTang=(my_glOpt[3]-0.5)/10.;
          
          alpha=(my_glOpt[4]-0.5)/5.;
          
          shiftL=my_glOpt[5];
          shiftA=(my_glOpt[6]-0.5)*2*M_PI;
          
          zoomx=zoom+zoomTang;
          zoomy=zoom-zoomTang;
          
          
          x1=zoomx+cos(shiftA)*shiftL/10.;
          y1=zoomy+sin(shiftA)*shiftL/10.;
          x2=1-zoomx+cos(shiftA)*shiftL/10.;
          y2=1-zoomy+sin(shiftA)*shiftL/10.;
          
          
          ROTASYM=my_glOpt[7]/0.5;
          if(vfsize<0.0001){
       
                   glBegin(GL_TRIANGLE_STRIP);
                    glTexCoord2f (rotx(x1,y1,alpha),roty(x1,y1,alpha)); glVertex2f (0.0,GLH);
                    glTexCoord2f (rotx(x1,y2,alpha),roty(x1,y2,alpha)); glVertex2f (0.0,0);
                    glTexCoord2f (rotx(x2,y1,alpha),roty(x2,y1,alpha)); glVertex2f (0+GLW,GLH );
                    glTexCoord2f (rotx(x2,y2,alpha),roty(x2,y2,alpha)); glVertex2f (0+GLW,0);
  
  /*                  glTexCoord2f (rotx(x1,y1,alpha),roty(x1,y1,alpha)); glVertex2f (0,2*GLH);
                    glTexCoord2f (rotx(x1,y2,alpha),roty(x1,y2,alpha)); glVertex2f (0,0);
                    glTexCoord2f (rotx(x2,y1,alpha),roty(x2,y1,alpha)); glVertex2f (2*GLW,2*GLH);
                    glTexCoord2f (rotx(x2,y2,alpha),roty(x2,y2,alpha)); glVertex2f (2*GLW,0);
  */
           glEnd();
        
       }else{
//      vfsize=getOpt("pifInterSize2");
              double op=calcOpt("pifInterOp2");
               double op2=calcOpt("pifInterOp2_q");

                glColor4f(1.0f,1.0f,1.0f,op*my_glOpt[0]);
                  glBegin(GL_TRIANGLE_STRIP);
                        glTexCoord2f (rotx(x1,y1,alpha),roty(x1,y1,alpha)); glVertex2f (0.0,GLH);
                        glTexCoord2f (rotx(x1,y2,alpha),roty(x1,y2,alpha)); glVertex2f (0.0,0);
                        glTexCoord2f (rotx(x2,y1,alpha),roty(x2,y1,alpha)); glVertex2f (0+GLW,GLH );
                        glTexCoord2f (rotx(x2,y2,alpha),roty(x2,y2,alpha)); glVertex2f (0+GLW,0);
                   glEnd();
          
          if(vfsize<0.99){
                glColor4f(1.0f,1.0f,1.0f,op2*my_glOpt[0]);

            mixBWSizedOrGL_Transform(mask2,1,-256+2*256*vfsize,0,lsct,GLW,GLH,
          rotx(x1,y1,alpha),roty(x1,y1,alpha),
          rotx(x2,y2,alpha),roty(x2,y2,alpha)
          );
                }else{
//               applyInterferMaskbyBrightness(mask2,op2*my_glOpt[0]); 
                
              mixBWSizedOrGL_Transform_Op_Fast(mask2,1,-256+2*256*vfsize,0,lsct,GLW,GLH,
          rotx(x1,y1,alpha),roty(x1,y1,alpha),
          rotx(x2,y2,alpha),roty(x2,y2,alpha),op2*my_glOpt[0]
          );    
                }

          
          
       }



        ndelay=my_glOpt[9]*(GLTEXDELAYN-1);
//        transformScreen(calcOpt("spiral1"),calcOpt("mega1"),0.1);
        
        
        
        
        glBindTexture(GL_TEXTURE_2D, lsct);
//        glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, 2*GLW, 2*GLH, 0);
          glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, GLW, GLH, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  //      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


    }


    for(int th=0;th<OCVTH;th++){
        if(vfop2[th]>0.00001){
//        getFrame(&video,&videoh,&videow);
//        placeTexOnGlScreen(NULL,videoh,videow,vfop2);
          //  double vfsize=0;
            
//            vfsize=getOpt("vf2size");
//.            mixBWSizedOrGL
  //          if(vfsize<=0.0001){
                placeTexOnGlScreen(vfop2[th],th,thTex[th]);
    //        }else{
                
      //          mixBWSizedOrGL(mask2,1,vfsize,NULL,videow,videoh,vfop2,screenW,screenH);
            
        //    }

        }
    }

    showGl(calcOpt("qsLayer2"),tex_qs);
    showGl(calcOpt("timbre2"),tex_timbre);
   showGl(calcOpt("qsSurf2"),tex_qsSurf);
 
    showGl(calcOpt("qsPlateOp2"),tex_qsPlate);
    showGl(calcOpt("soundSpeq2"),soundSpeqtex);
     showGl(calcOpt("soundSpeqSquare2"),soundSpeqSquaretex);

    if(my_glOpt[8]>0.0001){
//    fprintf(stderr,"VIDEODELAY\n");

        glBlendFunc(GL_SRC_ALPHA,getOpt("glBlendMetod")>0.5?GL_ONE_MINUS_SRC_ALPHA:GL_ONE);//);
     
     //   glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

      //    glBlendEquation(GL_MAX);
     //!!       glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);//);

          int curDelay;
          int steps,st;//VideoDelay Steps
          steps=1+my_glOpt[11]*(ndelay-1);
            if(steps<1)
                steps=1;
      vfsize=getOpt("pifInterSize3");
        double sp2=calcOpt("spiral2")/10;
        double me2=calcOpt("mega2")/10;

          for(st=0;st<steps;st++){
              curDelay=(delayTexCur+GLTEXDELAYN-ndelay+st)%GLTEXDELAYN;
              glBindTexture(GL_TEXTURE_2D, delayTex[curDelay]);
              double op;
              op=my_glOpt[8]/steps;
              glColor4f(1.0f,1.0f,1.0f,op/*delayGlOpt[curDelay][0]*/);

              double zoomx,zoom,zoomTang;
              double zoomy;
              double alpha;
              double shiftA,shiftL;
              double x1,y1,x2,y2;
              zoom=(my_glOpt[10])*(delayGlOpt[curDelay][2])/10.;
              zoomTang=(my_glOpt[10])*(delayGlOpt[curDelay][3])/10.;
          
              alpha=(my_glOpt[10])*(delayGlOpt[curDelay][4])/5.;
              
              shiftL=(my_glOpt[10])*delayGlOpt[curDelay][5];
              shiftA=(my_glOpt[10])*(delayGlOpt[curDelay][6])*2*M_PI;
          
              zoomx=zoom+zoomTang;
              zoomy=zoom-zoomTang;
          
          
              x1=zoomx+cos(shiftA)*shiftL/10.;
              y1=zoomy+sin(shiftA)*shiftL/10.;
              x2=1-zoomx+cos(shiftA)*shiftL/10.;
              y2=1-zoomy+sin(shiftA)*shiftL/10.;
          
          
              ROTASYM=my_glOpt[7]/0.5;
            if(vfsize<0.0001){
                  glBegin(GL_TRIANGLE_STRIP);
                        glTexCoord2f (rotx(x1,y1,alpha),roty(x1,y1,alpha)); glVertex2f (0.0,GLH);
                        glTexCoord2f (rotx(x1,y2,alpha),roty(x1,y2,alpha)); glVertex2f (0.0,0);
                        glTexCoord2f (rotx(x2,y1,alpha),roty(x2,y1,alpha)); glVertex2f (0+GLW,GLH );
                        glTexCoord2f (rotx(x2,y2,alpha),roty(x2,y2,alpha)); glVertex2f (0+GLW,0);
                   glEnd();
              }else{
//      vfsize=getOpt("pifInterSize2");
             double op=calcOpt("pifInterOp3");
               double op2=calcOpt("pifInterOp3_q");

                glColor4f(1.0f,1.0f,1.0f,op * my_glOpt[8]/steps);
                  glBegin(GL_TRIANGLE_STRIP);
                        glTexCoord2f (rotx(x1,y1,alpha),roty(x1,y1,alpha)); glVertex2f (0.0,GLH);
                        glTexCoord2f (rotx(x1,y2,alpha),roty(x1,y2,alpha)); glVertex2f (0.0,0);
                        glTexCoord2f (rotx(x2,y1,alpha),roty(x2,y1,alpha)); glVertex2f (0+GLW,GLH );
                        glTexCoord2f (rotx(x2,y2,alpha),roty(x2,y2,alpha)); glVertex2f (0+GLW,0);
                   glEnd();
  
//  GLW/2,GLH/2, 3*GLW/4, 3*GLH/4
  /*              glTexCoord2f (0.0,0.0); glVertex2f (GLW/2,GLH/2);
                glTexCoord2f (0.0,1.0); glVertex2f (GLW/2,GLH/2+GLH);
                glTexCoord2f (1.0,0.0); glVertex2f (0+GLW+GLW/2,GLH/2);
                glTexCoord2f (1.0,1.0); glVertex2f (0+GLW+GLW/2,GLH/2+GLH);
  */
//       glEnd();

               if(vfsize<0.99){
                     glColor4f(1.0f,1.0f,1.0f,op2* my_glOpt[8]/steps);
                


                  mixBWSizedOrGL_Transform(mask2,1,-256+2*256*vfsize,0,delayTex[curDelay],GLW,GLH,
                  rotx(x1,y1,alpha),roty(x1,y1,alpha),
                  rotx(x2,y2,alpha),roty(x2,y2,alpha)
          
                  );
                  }else{
                    mixBWSizedOrGL_Transform_Op_Fast(mask2,1,-256+2*256*vfsize,0,delayTex[curDelay],GLW,GLH,
                    rotx(x1,y1,alpha),roty(x1,y1,alpha),
                    rotx(x2,y2,alpha),roty(x2,y2,alpha),op2* my_glOpt[8]/steps
          
                  );
                  
                  }
                  
              }

               

            }

    

    glBindTexture(GL_TEXTURE_2D, delayTex[delayTexCur]);
    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, GLW, GLH, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  //      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    }
 
//    delayTex[delayTexCur]
     for(int th=0;th<OCVTH;th++){

     if(vfop3[th]>0.00001){
//        getFrame(&video,&videoh,&videow);
            //double vfsize=getOpt("vf3size");

          //  if(vfsize<=0.0001){
             //   placeTexOnGlScreen(NULL,videoh[th],videow[th],vfop3[th],th);
             placeTexOnGlScreen(vfop3[th],th,thTex[th]);

        //    }else{
                
      //          mixBWSizedOrGL(mask2,1,-256+2*vfsize*256,NULL,videow,videoh,vfop3,screenW,screenH);
            
    //        }
    }
    }
  showGl(calcOpt("qsLayer3"),tex_qs);
  showGl(calcOpt("timbre3"),tex_timbre);

  showGl(calcOpt("qsSurf3"),tex_qsSurf);

  showGl(calcOpt("qsPlateOp3"),tex_qsPlate);
  showGl(calcOpt("soundSpeq3"),soundSpeqtex);
  showGl(calcOpt("soundSpeqSquare3"),soundSpeqSquaretex);

    vfsize=getOpt("pifInterSize4");
    lbright=calcScrBright();

    if(vfsize>0.00001){
    
                double op=5.*calcOpt("pifInterOp4");
                double op2=5.*calcOpt("pifInterOp4_q");
                //fprintf(stderr,"pifInterSize4: oop:%lf\n",op);  
                
                glBindTexture(GL_TEXTURE_2D, readyBufTex);
                glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, GLW, GLH, 0);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
                
                glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//         double op=getOpt("pifInterOp4");
  //              double op2=getOpt("pifInterOp4_q");

                double opp;
                opp=op;
                while(opp>0.){
                    glColor4f(1.0f,1.0f,1.0f,(opp<=1)?opp:1.);
                    glBegin(GL_TRIANGLE_STRIP);
                    glTexCoord2f (0.0,1.0); glVertex2f (0.0,0.0);
                    glTexCoord2f (0.0,0.0); glVertex2f (0.0,0+GLH);
                    glTexCoord2f (1.0,1.0); glVertex2f (0+GLW,0.0);
                    glTexCoord2f (1.0,0.0); glVertex2f (0+GLW,GLH);
                    glEnd();
                    opp-=1.0;
                }
//  GLW/2,GLH/2, 3*GLW/4, 3*GLH/4
  /*              glTexCoord2f (0.0,0.0); glVertex2f (GLW/2,GLH/2);
                glTexCoord2f (0.0,1.0); glVertex2f (GLW/2,GLH/2+GLH);
                glTexCoord2f (1.0,0.0); glVertex2f (0+GLW+GLW/2,GLH/2);
                glTexCoord2f (1.0,1.0); glVertex2f (0+GLW+GLW/2,GLH/2+GLH);
  */

                if(op2>0.0001){
                    if(vfsize<0.99){
                     
                        opp=op2;
                        while(opp>0.){
                              glColor4f(1.0f,1.0f,1.0f,(opp<=1)?opp:1.);
                              //glColor4f(1.0f,1.0f,1.0f,op2);
                              mixBWSizedOrGL(mask2,1,-256+2*vfsize*256,0,readyBufTex,GLW,GLH);
                            opp-=1.;
                        }             
                     
                     }else{
                        mixBWSizedOrGLOp_Fast(mask2,1,vfsize*256,0,readyBufTex,GLW,GLH,op2);
                
                    }
                }
  }
  
  if(makeScreenShoot){
      if(screenShoot!=NULL){
        free(screenShoot);
        screenShoot=NULL;
      }
      fprintf(stderr,"SC!\n");
      makeScreenShoot=0;
      screenShoot=scrshooot(screenShootW,screenShootH);
  }

    glDisable(GL_BLEND);
  int j;
   for(j=0;j<GLOPTS;j++){
            delayGlOpt[delayTexCur][j]=0;
    }
   delayGlCount[delayTexCur]=0;


   if(my_glOpt[13]<0.001){
        for(i=0;i<GLTEXDELAYN;i++){
//        i=delayTexCur;
            delayGlCount[i]++;
            for(j=0;j<GLOPTS;j++){
                    if(j!=5&&j!=0)    
                        delayGlOpt[i][j]+=(my_glOpt[j]-0.5);//delayGlCount[i];
                    else if(j!=0)
                        delayGlOpt[i][j]=delayGlOpt[i][j]+my_glOpt[j]*(1+delayGlCount[i]*my_glOpt[12]);
            }
        }
    }else{
        double l1,l2,a1,a2,a,ll,aa;
        for(i=0;i<GLTEXDELAYN;i++){
//        i=delayTexCur;
            delayGlCount[i]++;
            
           l1=delayGlOpt[i][5];
           a1=(delayGlOpt[i][6])*2*M_PI;
           l2=my_glOpt[5]*(1+delayGlCount[i]*my_glOpt[12]);
           a2=my_glOpt[6]*2*M_PI;
           a=my_glOpt[4];
           ll=atan2(
            (cos(a1)*l1)*(cos(a1)*l1) + (sin(a2+a)*l2)*(sin(a2+a)*l2),           
           (sin(a1)*l1)*(sin(a1)*l1) + (sin(a2+a)*l2)*(sin(a2+a)*l2));
           aa=a1+a2;
//           delayGlOpt[i][4]=ll;
           delayGlOpt[i][5]=ll;
  //         delayGlOpt[i][6]=aa;
            
            //delayGlOpt[i][5]=delayGlOpt[i][5]+my_glOpt[5]*(1+delayGlCount[i]*my_glOpt[12]);

            for(j=0;j<GLOPTS;j++){
                    if(j!=5&&j!=0)    
                        delayGlOpt[i][j]+=(my_glOpt[j]-0.5)*(1+delayGlCount[i]*my_glOpt[12]);//delayGlCount[i];
            }
        }
    }
    delayTexCur++;
    if(delayTexCur>=GLTEXDELAYN)
         delayTexCur=0;


     //  glMatrixMode(GL_PROJECTION);
//        glPopMatrix();
      //  glMatrixMode(GL_MODELVIEW);
//         glViewport(GLW/2,GLH/2, 3*GLW/4, 3*GLH/4);
           
      applyLCircle(calcOpt("lcircle"));
    
    
    sendFrameToRec();    
    if(GLW!=REALW||GLH!=REALH){
      //  fprintf(stderr,"REALW! %d %d",REALW,REALH);
      //  fprintf(stderr,"(%d %d)\n",GLW,GLH);
        glBindTexture(GL_TEXTURE_2D, tmpt);
        glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, GLW, GLH, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          // glEnable(GL_ALPHA_TEST);
        glViewport(0, 0, REALW, REALH);

        glMatrixMode(GL_PROJECTION);
//        glPushMatrix();
        glLoadIdentity();
        glOrtho(0.0f,  REALW, REALH, 0.0f, -1.0f, 1.0f);
       
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
//        glColorMask(1,1,1,1);
       // glClearColor(0,0,0,1);

       // glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT   );

        
        
        
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        glBindTexture(GL_TEXTURE_2D, tmpt);
        glColor4f(1,1,1,1);
        glBegin(GL_TRIANGLE_STRIP);
                glTexCoord2f (0.0,1.0); glVertex2f (0.0,0.0);
                glTexCoord2f (0.0,0.0); glVertex2f (0.0,0+REALH);
                glTexCoord2f (1.0,1.0); glVertex2f (0+REALW,0.0);
                glTexCoord2f (1.0,0.0); glVertex2f (0+REALW,REALH);
  
       glEnd();

    
    }
    
//     glFlush();


       if(calibrate==1){
           glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
           glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
           if(calibrateX>=0 && calibrateY >=0 && calibrateQ >=0
           && 
            calibrateX<=1 && calibrateY <=1 && calibrateQ <=1){
                drawCalibatePoint(calibrateX,calibrateY,calibrateQ);            
            }
           
       
       
       }else if(calibrate==2){
            
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        glBindTexture(GL_TEXTURE_2D, pShow);
        glColor4f(1,1,1,1);
        glBegin(GL_TRIANGLE_STRIP);
                glTexCoord2f (0.0,1.0); glVertex2f (0.0,0.0);
                glTexCoord2f (0.0,0.0); glVertex2f (0.0,0+REALH);
                glTexCoord2f (1.0,1.0); glVertex2f (0+REALW,0.0);
                glTexCoord2f (1.0,0.0); glVertex2f (0+REALW,REALH);
  
       glEnd();
   
       
       }
//       glFinish();
  //     glBindTexture(GL_TEXTURE_2D, lsct);
    
       SDL_GL_SwapBuffers();
 


}

#else 
void GLShowScreen(SDL_Surface* screen){
}
#endif
SDL_Surface* CreateSurface(Uint32 flags,int width,int height,const SDL_Surface* display)
{
  // 'display' is the surface whose format you want to match
  //  if this is really the display format, then use the surface returned from SDL_SetVideoMode

  const SDL_PixelFormat& fmt = *(display->format);
  return SDL_CreateRGBSurface(flags,width,height,
                  fmt.BitsPerPixel,
                  fmt.Rmask,fmt.Gmask,fmt.Bmask,fmt.Amask );
}


inline void colorDxy(int&dx,int&dy);
void setSpiral(double a){
    spiral=a;
    fltransformSpiral=spiral*100;
}
void setMega(double a){
    mega=a;
    //fltransformSpiral=spiral*100;
}


inline void transformXY(int &x,int &y){
    if(fabs(spiral)>0.1){
        //int fltransformSpiral;
        transformSpiral(x,y);
    }
    if(fabs(mega)>0.01){
        //int fltransformSpiral;
        transformMega(x,y,1-mega);
    }
    
    



}


#define SEQLEN 256
#define SEQMOD2 255

Uint32 seqno2=0;

Uint32 colorSeq2Buf[SEQLEN];
int colorSeq2BufDx[SEQLEN];
int colorSeq2BufDy[SEQLEN];
int colorSeq2BufNeedLine[SEQLEN];
double colorSeq2BufWidth[SEQLEN];

Uint32 *_colorSeq2Buf;
int* _colorSeq2BufDy;
int* _colorSeq2BufDx;
double *_colorSeq2BufWidth;
int *_colorSeq2BufNeedLine;
int colorSeq2BufReady=0;
double ColorSeq2Speedr;
double ColorSeq2Speedg;
double ColorSeq2Speedb;
void inline swapint(int&a,int&b){
    int t;
    t=a;
    a=b;
    b=t;
}



void initColorSeq2(double speedr,double speedg,double speedb){
    Uint64  i,n;
    if(!colorSeq2BufReady || fabs(ColorSeq2Speedr-speedr)>0.000001|| fabs(ColorSeq2Speedg-speedg)>0.000001|| fabs(ColorSeq2Speedb-speedb)>0.000001){
        colorSeq2BufReady=1;
        ColorSeq2Speedr=speedr;
        ColorSeq2Speedg=speedg;
        ColorSeq2Speedb=speedb;
        
       // printf("Calc colorspeed %lf\n",speed);
       /*if(colorSeq2Len==-1)
          n=262144;
        else{
            n=colorSeq2Len;
        }*/
        for(i=0;i<SEQLEN;i++){
            struct rgb a;
            a.r=255*(cos(i*speedb*M_PI/100+M_PI)+1)/2;
            a.g=255*(cos(i*speedg*M_PI/80+M_PI)+1)/2;
            a.b=255*(cos(i*speedr*M_PI/120+M_PI)+1)/2;        
            colorSeq2Buf[i]=*((Uint32*)&a );
        }
    }

}
#include"ok_colorline.cpp"
inline Uint32 colorSeq3(int a);
extern int  colorDeep;
extern struct colorLine*cl;
double pifTimeKoef=1;
Uint32 lastTimeFraqDeep[20][200];
 Uint32 GetTickCount(void);
extern int     currentFps;
void prepareSeqNo2(int deep){
    int i;
    /*Uint32 t=GetTickCount();
    Uint32 dt;
    
    for(i=199;i>0;i--)
        lastTimeFraqDeep[deep][i]=lastTimeFraqDeep[deep][i-1];
    lastTimeFraqDeep[deep][0]=t;
    
    pifTimeKoef=1/200.;
    for(i=1;i<200;i++){
        dt=t-lastTimeFraqDeep[deep][i];
        if(dt>100){
            pifTimeKoef=dt/10./i;
         }
    }*/
    if(currentFps<1)
        pifTimeKoef=25;
    else
        pifTimeKoef=25./currentFps;
    
  //  fprintf(stderr,"pifTimeKoef:%lf\n",pifTimeKoef);
//    if(pifTimeKoef>10)
        
    seqno2=cl->seqno3[deep];
    _colorSeq2Buf=cl->oqColorline[deep];
    _colorSeq2BufDx=cl->oqColorlineDx[deep];
    _colorSeq2BufDy=cl->oqColorlineDy[deep];
    _colorSeq2BufNeedLine=cl->colorSeq2BufNeedLine[deep];
    _colorSeq2BufWidth=cl->oqColorlineWidth[deep];
}
void posColorLine(int a,int max){
    seqno2=a*SEQMOD2/max;
}
       
void prepareDefSeqNo2(){
//    seqno2=cl->seqno3[deep];
    _colorSeq2Buf=colorSeq2Buf;
    _colorSeq2BufDx=colorSeq2BufDx;
    _colorSeq2BufDy=colorSeq2BufDy;
    _colorSeq2BufNeedLine=colorSeq2BufNeedLine;
    _colorSeq2BufWidth=colorSeq2BufWidth;

}

void prepareOrSeqNo2(){
    seqno2=cl->orseqno3;
    _colorSeq2Buf=cl->orOqColorline;
    _colorSeq2BufDx=colorSeq2BufDx;
    _colorSeq2BufDy=colorSeq2BufDy;
    _colorSeq2BufNeedLine=colorSeq2BufNeedLine;
    _colorSeq2BufWidth=colorSeq2BufWidth;

}
inline Uint32 colorSeq2(){
//    return colorSeq3(colorDeep);
    seqno2++;
    return _colorSeq2Buf[seqno2&SEQMOD2];
}
inline void colorDxy(int&dx,int&dy){
    dx=_colorSeq2BufDx[seqno2&SEQMOD2];
    dy=_colorSeq2BufDy[seqno2&SEQMOD2];
}
inline double colorWidth(){
    return _colorSeq2BufWidth[seqno2&SEQMOD2];
}

inline int needLineSeq(){
    return _colorSeq2BufNeedLine[seqno2&SEQMOD2];

}

    


struct splash{
    int x,y,state,duration,r;
    struct splash* next;
}*splashes=NULL;

int swapt;
inline void swap(int &a,int &b){
    swapt=a;
    a=b;    
    b=swapt;
}
#define sign(a) (((a)>=0)?1:-1)



void addpixel(SDL_Surface *surface, int x, int y, Uint32 pixel,Uint32 mask)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

   if((*(Uint32 *)p + pixel)&mask > (*(Uint32 *)p)&mask){
    *(Uint32 *)p += pixel;
   }else{
    (*(Uint32 *)p)&=mask;
   
   }
}

void plusPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    int r,g,b;
    /* Here p is the address to the pixel we want to set */
    Uint32 *p = (Uint32*)((Uint8 *)surface->pixels + y * surface->pitch + x * bpp);
   r=((struct rgb*)p)->r +(int)(((struct rgb*)(&pixel))->r);
   g=((struct rgb*)p)->g +(int)(((struct rgb*)(&pixel))->g);
   b=((struct rgb*)p)->b +(int)(((struct rgb*)(&pixel))->b);
   if(r>255)
    r=255;
   if(g>255)
    g=255;
    if(b>255)
        b=255;
   ((struct rgb*)p)->r=r;
   ((struct rgb*)p)->g=g;   
   ((struct rgb*)p)->b=b;   
   
   
   
}



void addSplash(int x,int y,int r){
    struct splash*s;
    s=(struct splash*)malloc(sizeof(struct splash));
    if(s==NULL)
        return;
    s->next=splashes;
    s->x=x;
    s->y=y;
    s->state=0;
    s->duration=2;
    s->r=r;
    splashes=s;
}

void drawSplashes(SDL_Surface *sc){
    struct splash* s;
    int x,y,r;
    for(s=splashes;s;s=s->next){
        if(s->state==0){
            s->state++;
            for(x=-s->r;x<=s->r;x++)
                for(y=-s->r;y<=s->r;y++){
                    if(s->x+x>=0 && s->x+x<sc->w&&s->y+y>=0&&s->y+y<sc->h&&
                    
                    
                    x*x+y*y<s->r*s->r){
                        r=s->r*s->r - x*x+y*y;
                        r=r*255/r;
                        r=r | r<<8 | r<<16;
                        
                        addpixel(sc,s->x+x,s->y+y,r,255 | 255<<8 | 255<<16);    
                    
                    }
                    
                
                }
            
        
        }else{
            
        
        }
    
    }

}

unsigned int  inline getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    unsigned int *q;
    q=(unsigned int*)p;
    return *q;
}



int putPixelBufy[2000];
void preparePutPixel(SDL_Surface *s){
    int i;
    for(i=0;i<s->h;i++){
        putPixelBufy[i]=i * s->pitch/4;
    }
}
unsigned int orOpacity;

void inline putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel){
    if(x<0||x>=surface->w||y<0||y>=surface->h)
        return;
    *((Uint32 *)surface->pixels + putPixelBufy[y] + x) = pixel| orOpacity;
}
void inline orpixel(SDL_Surface *surface, int x, int y, Uint32 pixel){
    if(x<0||x>=surface->w||y<0||y>=surface->h)
        return;
    *((Uint32 *)surface->pixels + putPixelBufy[y] + x) |= pixel | orOpacity;
}

unsigned int inline  viewPixel(SDL_Surface *sc,int x,int y){
    if(x>=0&&x<sc->w && y>=0 && y< sc->h){
        return getpixel(sc,x,y);
    
    }
    return 0;
}

void inline setPixel(SDL_Surface *sc,int x,int y,int c){
    if(x>=0&&x<sc->w && y>=0 && y< sc->h){
        putpixel(sc,x,y,c);
    
    }

}
void drawLine(SDL_Surface *sc,int x1, int y1, int x2, int y2,int c) {
    //transformXY(x1,y1);    

    //transformXY(x2,y2);    

    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    //
    int error = deltaX - deltaY;
    //
    if(x1<0&&x2<0||x1>=sc->w&&x2>=sc->w
        ||
       y1<0&&y2<0 || y1>=sc->w&&y2>=sc->w
    
    )return;
    
    setPixel(sc, x2, y2, c);
    while(x1 != x2 || y1 != y2) {
        setPixel(sc,x1, y1,c);
        const int error2 = error * 2;
        //
        if(error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
    }
 
}
void orLine(SDL_Surface *sc,int x1, int y1, int x2, int y2,int c) {
    //transformXY(x1,y1);    

    //transformXY(x2,y2);    

    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    //
    int error = deltaX - deltaY;
    //
    if(x1<0&&x2<0||x1>=sc->w&&x2>=sc->w
        ||
       y1<0&&y2<0 || y1>=sc->w&&y2>=sc->w
    
    )return;
    
    orpixel(sc, x2, y2, c);
    while(x1 != x2 || y1 != y2) {
        orpixel(sc,x1, y1,c);
        const int error2 = error * 2;
        //
        if(error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
    }
 
}

void drawColoredLine(SDL_Surface *sc,int x1, int y1, int x2, int y2,Uint32(*colorSeq)()) {
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    //
    int error = deltaX - deltaY;
    //
    setPixel(sc, x2, y2, (*colorSeq)());
    while(x1 != x2 || y1 != y2) {
        setPixel(sc,x1, y1,(*colorSeq)());
        const int error2 = error * 2;
        //
        if(error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
    }
 
}

inline Uint32 colorSeq2();



inline void drawColoredLineSeq2(SDL_Surface *sc,int x1, int y1, int x2, int y2) {
//    transformXY(x1,y1);
 //   transformXY(x2,y2);    
    if((x1<0&&x2<0)||(x1>sc->w&&x2>sc->w)||(y1<0&&y2<0)||(y1>sc->h&&y2>sc->h))
       return;
    
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    //
    int error = deltaX - deltaY;
    //
    int dx,dy;
    colorDxy(dx,dy);
    putpixel(sc, x2+dx, y2+dy, colorSeq2());
    while(x1 != x2 || y1 != y2) {
        colorDxy(dx,dy);
    
        putpixel(sc,x1+dx, y1+dy,colorSeq2());
        const int error2 = error * 2;
        //
        if(error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
    }
 
}
inline void orDrawColoredLineSeq2(SDL_Surface *sc,int x1, int y1, int x2, int y2) {
//    transformXY(x1,y1);
 //   transformXY(x2,y2);    
    if((x1<0&&x2<0)||(x1>sc->w&&x2>sc->w)||(y1<0&&y2<0)||(y1>sc->h&&y2>sc->h))
       return;
    
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    //
    int error = deltaX - deltaY;
    //
    int dx,dy;
    colorDxy(dx,dy);
    int lx,ly;
    lx=x1+dx;
    ly=y1+dy;
    Uint32 color;
    color=colorSeq2();
   
   // orpixel(sc, x2+dx, y2+dy, colorSeq2());
    while(x1 != x2 || y1 != y2) {
        colorDxy(dx,dy);
    
      //  orpixel(sc,x1+dx, y1+dy,colorSeq2());
        if(needLineSeq())
            orLine(sc,lx,ly,x1+dx, y1+dy,color);
        else{
            orpixel(sc,x1+dx, y1+dy,color);
        
        }
        lx=x1+dx;
        ly=y1+dy;
        color=colorSeq2();
   
        const int error2 = error * 2;
        //
        if(error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
    }
 
}
#ifdef GLBILD
#include"mygl.h"
//#include <GL/gl.h>
//#include <GL/glew.h>

//#include <GL/glu.h>
double getMaxLineWidth(){
    double r;
    //glGetDoublev(GL_ALIASED_LINE_WIDTH_RANGE,&r);
    r=25;
    return r;
}

inline void orGLLine(int x1,int y1,int x2,int y2,Uint32 c1,Uint32 c2,double width){
 //   glColor3ub(c&255, (c/256)&255, (c /256/256)&255);
    glLineWidth(width);
//glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glColor4ubv((const GLubyte*)&c1);
    glVertex2i(x1,y1);
    glColor4ubv((const GLubyte*)&c2);
    glVertex2i(x2,y2);
    glEnd();
}
inline void GLColoredLineSeq2(int x1, int y1, int x2, int y2) {
//    transformXY(x1,y1);
 //   transformXY(x2,y2);    
//    if((x1<0&&x2<0)||(x1>sc->w&&x2>sc->w)||(y1<0&&y2<0)||(y1>sc->h&&y2>sc->h))
  //     return;
    
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    //
    int error = deltaX - deltaY;
    //
    int dx,dy;
    colorDxy(dx,dy);
    int lx,ly;
    lx=x1+dx;
    ly=y1+dy;
    Uint32 color,color2;
    color=colorSeq2();
   
   // orpixel(sc, x2+dx, y2+dy, colorSeq2());
    while(x1 != x2 || y1 != y2) {
        colorDxy(dx,dy);
        color2=colorSeq2();
    
      //  orpixel(sc,x1+dx, y1+dy,colorSeq2());
    //    if(needLineSeq())
            orGLLine(lx,ly,x1+dx, y1+dy,color,color2,colorWidth());
      //  else{
        //    orpixel(sc,x1+dx, y1+dy,color);
        
      //  }
        color=color2;
        lx=x1+dx;
        ly=y1+dy;
   
        const int error2 = error * 2;
        //
        if(error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
    }
 
}




inline void glLine3d(int x1,int y1,int z1,Uint32 c1,int x2,int y2,int z2,Uint32 c2){
 //   glColor4bv((const GLbyte *)&c1);
  // glColor4ub(c1&255, (c1/256)&255, (c1/256/256)&255,(c1/256/256/256)&255);
   glColor4ub(255,255,255,255);
  
    glVertex3d(x1,y1,z1);
    

//    glColor4bv((const GLbyte *)&c2);
//     glColor4ub(c2&255, (c2/256)&255, (c2/256/256)&255,(c2/256/256/256)&255);
   glColor4ub(255,255,255,255);

    glVertex3d(x2,y2,z2);
    fprintf(stderr,"glline! %d %d ",x1,y1);
    fprintf(stderr,"%d %d ",z1,x2);
    fprintf(stderr,"%d %d\n",y2,z2);
}
inline void drawGlZColoredLineSeq2(int x1, int y1, int x2, int y2,int z) {
//    transformXY(x1,y1);
 //   transformXY(x2,y2);    
//    if((x1<0&&x2<0)||(x1>sc->w&&x2>sc->w)||(y1<0&&y2<0)||(y1>sc->h&&y2>sc->h))
  //     return;
  //  fprintf(stderr,"вкпдясды2!\n");
   glColor4ub(255,255,255,255);
  
    glVertex3d(x1,y1,z);
    

//    glColor4bv((const GLbyte *)&c2);
//     glColor4ub(c2&255, (c2/256)&255, (c2/256/256)&255,(c2/256/256/256)&255);
   glColor4ub(255,255,255,255);

    glVertex3d(x2,y2,z);
    return;
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    //
    int error = deltaX - deltaY;
    //
    int dx,dy;
    colorDxy(dx,dy);
    int lx,ly;
    lx=x1+dx;
    ly=y1+dy;
    Uint32 color1,color2;
    color1=colorSeq2();
   
   // orpixel(sc, x2+dx, y2+dy, colorSeq2());
    while(x1 != x2 || y1 != y2) {
        colorDxy(dx,dy);
    
      //  orpixel(sc,x1+dx, y1+dy,colorSeq2());
    //    if(needLineSeq())
       color2=colorSeq2();
   
       glLine3d(lx,ly,z,color1,x1+dx, y1+dy,z,color2);
      color1=color2;
      //  else{
        //    orpixel(sc,x1+dx, y1+dy,color);
        
        //}
        lx=x1+dx;
        ly=y1+dy;
        
        const int error2 = error * 2;
        //
        if(error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
    }
 
}


#else
inline void glLine3d(int x1,int y1,int z1,Uint32 c1,int x2,int y2,int z2,Uint32 c2){}
inline void drawGlZColoredLineSeq2(int x1, int y1, int x2, int y2,int z) {}
double getMaxLineWidth(){
    return 1;
}

#endif



inline void pixel2rgb(Uint32 p,int &r,int &g,int &b){
    
    
    r=((struct rgb*)(&p))->r;
    g=((struct rgb*)(&p))->g;
    b=((struct rgb*)(&p))->b;
}
inline void rgb2pixel(int r,int g,int b,Uint32 *p){
//    *p=(((Uint32)g)*65536+b)*65536+r;
       ((struct rgb*)p)->r=r;
       ((struct rgb*)p)->g=g;
       ((struct rgb*)p)->b=b;
       


}
void     drawSqr(SDL_Surface *sc,int x1,int y1,int x2,int y2,int color){
    
    int x;
    if(x1>x2)
        swap(x1,x2);
    if(y1>y2)
        swap(y1,y2);
     
    for(x=x1;x<=x2;x++){
        setPixel(sc,x,y1,color);
        setPixel(sc,x,y2,color);           
    } 
    for(x=y1;x<=y2;x++){
        setPixel(sc,x1,x,color);
        setPixel(sc,x2,x,color);           
    }
}


SDL_Surface *cloneScreen(SDL_Surface *screen){
    const SDL_PixelFormat& fmt = *(screen->format);
  return SDL_CreateRGBSurface(screen->flags,screen->w,screen->h,
                  fmt.BitsPerPixel,
                  fmt.Rmask,fmt.Gmask,fmt.Bmask,fmt.Amask );




}


inline void circle(SDL_Surface* sc, int x, int y, int r,Uint32 color){
        transformXY(x,y);    

        int x1,y1,yk = 0;
        int sigma,delta,f;

        x1 = 0;
        y1 = r;
        delta = 2*(1-r);

        do
        {
                putpixel(sc,x+x1,y+y1,color);
                putpixel(sc,x-x1,y+y1,color);
                putpixel(sc,x+x1,y-y1,color);
                putpixel(sc,x-x1,y-y1,color);

                f = 0;
                if (y1 < yk)
                        break;
                if (delta < 0)
                {
                        sigma = 2*(delta+y1)-1;
                        if (sigma <= 0)
                        {
                                x1++;
                                delta += 2*x1+1;
                                f = 1;
                        }
                }
                else
                if (delta > 0)
                {
                        sigma = 2*(delta-x1)-1;
                        if (sigma > 0)
                        {
                                y1--;
                                delta += 1-2*y1;
                                f = 1;
                        }
                }
                if (!f)
                {
                        x1++;
                        y1--;
                        delta += 2*(x1-y1-1);
                }
        }
        while(1);
}
inline void circleColorSeq(SDL_Surface* sc, int x, int y, int r){
        transformXY(x,y);    

        int x1,y1,yk = 0;
        int sigma,delta,f;
        Uint32 color;
        x1 = 0;
        y1 = r;
        delta = 2*(1-r);

        do
        {       
                    int dx,dy;
                    colorDxy(dx,dy);

                color=colorSeq2();
                orpixel(sc,x+x1+dx,y+y1+dy,color);
                orpixel(sc,x-x1+dx,y+y1+dy,color);
                orpixel(sc,x+x1+dx,y-y1+dy,color);
                orpixel(sc,x-x1+dx,y-y1+dy,color);

                f = 0;
                if (y1 < yk)
                        break;
                if (delta < 0)
                {
                        sigma = 2*(delta+y1)-1;
                        if (sigma <= 0)
                        {
                                x1++;
                                delta += 2*x1+1;
                                f = 1;
                        }
                }
                else
                if (delta > 0)
                {
                        sigma = 2*(delta-x1)-1;
                        if (sigma > 0)
                        {
                                y1--;
                                delta += 1-2*y1;
                                f = 1;
                        }
                }
                if (!f)
                {
                        x1++;
                        y1--;
                        delta += 2*(x1-y1-1);
                }
        }
        while(1);
}



void oldbar(SDL_Surface*screen,int x1,int y1,int x2,int y2,Uint32 c){
    int x,y;
    if(x1>x2)
        swapint(x1,x2);
    if(y1>y2)
        swapint(y1,y2);
        
    for(x=x1;x<=x2;x++){
        for(y=y1;y<=y2;y++){
            putpixel(screen,x,y,c);
        }
    }

}
void bar(SDL_Surface*screen,int x1,int y1,int x2,int y2,Uint32 c){
    int x,y,w,dy;
    Uint32*p;
    if(x1>x2)
        swapint(x1,x2);
    if(y1>y2)
        swapint(y1,y2);

    if(x1<0)
        x1=0;
    if(y1<0)
        y1=0;
    if(y2>=screen->h)
        y2=screen->h-1;
    if(x2>=screen->w)
        x2=screen->w-1;
        

    p=((Uint32*)screen->pixels)+x1+y1*(screen->pitch/(screen->format->BytesPerPixel));

    dy=screen->pitch/(screen->format->BytesPerPixel) - (x2-x1+1);
    for(y=y1;y<=y2;y++,p+=dy){
        for(x=x1;x<=x2;x++,p++){
            *p=c;
        }
    }

}



void rainbowBar(SDL_Surface*screen,int x1,int y1,int x2,int y2){
    int x,y,r,g,b;
    Uint32 p;
    for(x=x1;x<=x2;x++){
        for(y=y1;y<=y2;y++){
            r=(x-x1)*255/(x2-x1);
            g=(y-y1)*255/(y2-y1);
            b=((y-y1)*(x-x1))*255/(y2-y1)/(x2-x1);
            
            rgb2pixel(r,g,b,&p);
            
            putpixel(screen,x,y,p);
        }
    }

}


void rectangle(SDL_Surface*screen,int x1,int y1,int x2,int y2,Uint32 c){
    int x,y;
     if(x1>x2)
        swapint(x1,x2);
    if(y1>y2)
        swapint(y1,y2);

    for(x=x1;x<=x2;x++){
         putpixel(screen,x,y1,c);
         putpixel(screen,x,y2,c);
        
    }   
    for(y=y1;y<=y2;y++){
         putpixel(screen,x1,y,c);
         putpixel(screen,x2,y,c);
    
    }

}






#endif
