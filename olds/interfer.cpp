#ifndef INTERFERMOD
#define INTERFERMOD

#include<math.h>

#include"graphutil.cpp"
#include"soundutil.cpp"
struct layer{
    unsigned char *p;
    Uint32 *p4b;
    int h,w;
    unsigned int upb,upe;
    unsigned int *obh;
    double oPart;
};
#include"forceLines.cpp"


unsigned char morphTable[256][256];
double  lastMorph=0;


unsigned int *qobh;
char*qfl;
int qow;
int qoh;
//int qle;

void genObh(unsigned int *obh,char* fl,int w,int h,int le){
    qfl=fl;
    qobh=obh;
    qow=w;
    qoh=h;
    //qle=le;
    

}
void  makeObh(unsigned int *obh,int w,int h,double part){
    int che=0;
    int cur=0;
    if(part<0.0001)
        part=0.0001;
    unsigned int alle,le,step;
    char*fl;
    fl=(char*)malloc(w*h);
    if(fl==NULL)
        return;
    memset(fl,0,w*h);
    alle=w*h;
    le=alle*part;
    
    //genObh(obh,fl,w,h,le);
    step=alle/part;
    while(che<alle){
        cur=cur%alle;
        if(!fl[cur]){
            obh[che]=cur;
            che++;
            fl[cur]=1;
            cur=cur+step;
        }else{
            cur++;
        }
    
    }
    free(fl);
    fprintf(stderr,"MAKEOBH\n");
}

void buildMorphTable(double d){
    int i,j;
    if(fabs(d-lastMorph)<0.0001)
        return;
    lastMorph=d;
    for(i=0;i<256;i++){
        for(j=0;j<256;j++){
            morphTable[i][j]=(i*(d)+j*(1.-d));
        }
    }

}


void morph(struct layer*oldl,struct layer*newl,double d){
    int i,j,jj;
    unsigned char*o,*n;
    Uint32 *o32;
    unsigned int *ob;
    unsigned int le;
    unsigned int alle;
    alle=newl->h*(unsigned int)newl->w;
    le=(newl->upe-newl->upb+alle)%alle;
    if(le==0)
        le=alle;
    
    o=oldl->p;//+newl->upb;
    n=newl->p;//+newl->upb;
    o32=oldl->p4b;//+newl->upb;
    ob=newl->obh+newl->upb;
    oldl->upb=newl->upb;
    oldl->upe=newl->upe;
//    fprintf(stderr,"upb/e:%d %d\n",(int)newl->upb,(int)newl->upe);
    if(d==0){
//        for(i=0;i<oldl->h;i++)
        if(le==alle){
            for(j=0;j<alle;j++,o++,n++,o32++){
                *o=*n;
                *o32=((Uint32)(*o))*256*256*256;
            }
        }else{
            for(j=0,jj=newl->upb;j<le&&jj<alle;j++/*,o++,n++,o32++*/,ob++,jj++){
                o[*ob]=n[*ob];
                o32[*ob]=((Uint32)(o[*ob]))*256*256*256;
            }
            o=oldl->p;
            n=newl->p;
            for(;j<le;j++/*,o++,n++,o32++*/,ob++){
                o[*ob]=n[*ob];
                o32[*ob]=((Uint32)(o[*ob]))*256*256*256;
            }
            
        }
        return;
    }    
    
    buildMorphTable(d);
//    for(i=0;i<oldl->h;i++)
  //      for(j=0;j<oldl->w;j++,o++,n++,o32++){
    //        *o=morphTable[*o][*n];
      //      *o32=((Uint32)(*o))*256*256*256;
        //}
      if(le==alle){
            for(j=0;j<alle;j++,o++,n++,o32++){
                *o=morphTable[*o][*n];
                *o32=((Uint32)(*o))*256*256*256;
            }
      }else{
        for(j=0,jj=newl->upb;j<le&&jj<alle;j++/*,o++,n++,o32++*/,jj++,ob++){
            o[*ob]=morphTable[o[*ob]][n[*ob]];
            o32[*ob]=((Uint32)(o[*ob]))*256*256*256;
        }
      
      
     // o=oldl->p;
     // n=newl->p;
     // o32=oldl->p4b;
         ob=newl->obh;
          for(;j<le;j++,o++,n++,o32++){
                *o=morphTable[*o][*n];
                *o32=((Uint32)(*o))*256*256*256;
          }

    }
}


struct layer*makeLayer(int w,int h,double part){
    struct layer *l;
    l=(struct layer*)malloc(sizeof(struct layer));
    if(l==NULL)
        return NULL;
    l->p=(unsigned char*)malloc(h*w);
    if(l->p == NULL){
        free(l);
        return NULL;
    
    }
    l->p4b=(Uint32*)malloc(h*w*4);
    if(l->p4b == NULL){
        free(l->p);
        free(l);
        return NULL;
    
    }
    l->obh=(unsigned int*)malloc(h*w*sizeof(unsigned int));
    if(l->obh==NULL){
        free(l->p);
        free(l->p4b);
        free(l);
        return NULL;
    }
    makeObh(l->obh,w,h,part);
    l->oPart=part;
    l->h=h;
    l->w=w;
    l->upe=0;
    l->upb=0;
    fprintf(stderr,"NULL LAYER\n");
    return l;
}
struct layer*makeLayer(int w,int h){
    return makeLayer(w,h,1);
}

void freeLayer(struct layer *p){
    if(p!=NULL){
        if(p->p!=NULL)
            free(p->p);
        if(p->p4b!=NULL)
            free(p->p4b);
        if(p->obh!=NULL)
            free(p->obh);
         free(p);
    }
}


struct layer*resizeLayer(struct layer*old,int w,int h,double part){
    struct layer *n;
    int x,y;
    if(old->w==w &&old->h==h){
        if(fabs(old->oPart-part)>0.00001){
            makeObh(old->obh,w,h,part);
            old->oPart=part;
        }
        return old;
    }

    if(old==NULL){
        return makeLayer(w,h,part);
    }
    n=makeLayer(w,h,part);
    if(n==NULL){
        freeLayer(old);
        return NULL;
    }
    for(y=0;y<h;y++)
        for(x=0;x<w;x++){
            n->p[x+y*w]=old->p[x*old->w/w + (y*old->h/h)*w];
        }
    freeLayer(old);
    return n;
}
struct layer*resizeLayer(struct layer*old,int w,int h){
    return resizeLayer(old,w,h,1);
}

#define SBUFSIZE 4096

unsigned int s1bufcur=0;
unsigned int s2bufcur=0;

short s1buf[SBUFSIZE];
short s2buf[SBUFSIZE];
unsigned int *interTable1=NULL;
unsigned int *interTable2=NULL;
int interTableH=0;
int interTableW=0;
double interTableMapSize=-1e100;
int ls1x;
int ls1y;
int ls2x;
int ls2y;
int buildInterTable(int w,int h,double mapSize,int s1x,int s1y,int s2x,int s2y){
    if(interTable1==NULL ||interTable2==NULL || interTableH!=h || interTableW!=w||fabs(mapSize-interTableMapSize)>0.00001||
     s1x!=ls1x || s1y!=ls1y || s2x!=ls2x || s2y!=ls2y
    
    ){
        ls1x=s1x;
        ls1y=s1y;
        ls2x=s2x;
        ls2y=s2y;
        if(interTable1!=NULL)
            free(interTable1);
        if(interTable2!=NULL)
            free(interTable2);
        interTable1=(unsigned int*)malloc(h*w*sizeof(unsigned int));
        if(interTable1==NULL){
            return -1;
        }
        interTable2=(unsigned int*)malloc(h*w*sizeof(unsigned int));
        if(interTable2==NULL){
            return -1;
        }
        interTableW=w;
        interTableH=h;
        interTableMapSize=mapSize;
        int x,y;
        double d,v;
        d=sqrt( (s1x-s2x)*(s1x-s2x) + (s1y-s2y)*(s1y-s2y));
        if(mapSize<0.001)
            mapSize=0.001;
        v=330.*d/mapSize;
        for(y=0;y<h;y++)
            for(x=0;x<w;x++){
                //SAMPLE_RATE
                double l,t;
                l=sqrt((x-s1x)*(x-s1x) + (y-s1y)*(y-s1y));
                t=l/v;
                
            
                interTable1[x+y*w]=t*SAMPLE_RATE;
                l=sqrt((x-s2x)*(x-s2x) + (y-s2y)*(y-s2y));
                t=l/v;
                interTable2[x+y*w]=  t*SAMPLE_RATE;
            }        
    
    }

    
    return 0;
}


int mulS=1024,t;
inline void putS1(int a){
    if(a*mulS>32767*1024||a*mulS<-32767*1024){
        if(a!=0)
            mulS=32767*1024/abs(a);
    
    }else{
        if(a!=0){
            t=32767*1024/abs(a);
            mulS=(499*mulS+t)/500;
         }
    }
    s1buf[s1bufcur]=a*mulS/1024;
    s1bufcur++;
    s1bufcur=s1bufcur&(SBUFSIZE-1);
}
inline void putS2(int  a){
    if(a*mulS>32767*1024||a*mulS<-32767*1024){
        if(a!=0)
            mulS=32767*1024/abs(a);
    
    }else{
        if(a!=0){
            t=32767*1024/abs(a);
            mulS=(499*mulS+t)/500;
        }
    }
    s2buf[s2bufcur]=a*mulS/1024;
    s2bufcur++;
    s2bufcur=s2bufcur&(SBUFSIZE-1);
}



inline int getS1(int d){
    int t;
    t=s1bufcur-d-1;
    while(t<0)
        t+=SBUFSIZE;
    t=t&(SBUFSIZE-1);
    return s1buf[t];
}
inline int getS2(int d){
    int t;
    t=s2bufcur-d-1;
    while(t<0)
        t+=SBUFSIZE;
    t=t&(SBUFSIZE-1);
    return s2buf[t];
}

unsigned char iFlag[1000];
unsigned char iGammas[1000][256];
unsigned char *iGamma;
void buildGammaTable(double gamma){
    int n;
    if(gamma<0.)
        gamma=0.;
    if(gamma>1.)
        gamma=1.;
        
    n=gamma*1000;
    if(n<0)
        n=0;
    if(n>=1000)
        n=999;
    if(iFlag[n] == 0){
        iFlag[n] = 1;
        for(int i=0;i<256;i++)
            iGammas[n][i]=255*pow(i/255.0,gamma*2);
    }
    
    iGamma=iGammas[n];

}
void interFer(struct layer*l,double mapsize,double part,double gamma){
    int x,y,i,j;
    int s1x,s1y,s2x,s2y;
    Uint32 a,d1,d2;
    unsigned char*out;
    Uint32 *out32;
    int w;
    int h;
    unsigned int le,alle;
    w=l->w;
    h=l->h;
    alle=w*h;
    le=alle*part;
    if(le>alle)
        le=alle;
    out=l->p;//+l->upe;
    out32=l->p4b;//+l->upe;
    s1x=w*getOpt("speaker1x");
    s1y=h*getOpt("speaker1y");
    s2x=w*getOpt("speaker2x");
    s2y=h*getOpt("speaker2y");
    buildInterTable(w,h,mapsize,s1x,s1y,s2x,s2y);
    buildGammaTable(gamma);
    //int i0,i1;
    //i0=0+pix*(1-value)/2;
    //i1=pix-pix*(1-value)/2;
            
    unsigned int c;
    unsigned int *dd1=interTable1;//+l->upe;
    unsigned int *dd2=interTable2;//+l->upe;
    unsigned int *ob;
    ob=l->obh+l->upe;
   // for(y=0;y<h;y++){
        for(x=l->upe,y=0;y<le;x++/*,out++,out32++,dd1++,dd2++*/,ob++,y++){
            if(x>=alle){
              //  dd1=interTable1;
              //  dd2=interTable2;
              //  out=l->p;
              //  out32=l->p4b;
              ob=l->obh;
              
                x=0;          
            }
            d1=dd1[*ob];
            d2=dd2[*ob];
            a=(getS1(d1)+getS2(d2))/2;
            a=a/256;
            a=128+a;
           // if(a>255){
           //     fprintf(stderr,"a:%d\n",a);
            
            //    a=255;
           // }
           // a=iGamma[a];
            a=iGamma[a&255];
            c=a;
            c=c*256*256*256;
            out[*ob]=a;
            out32[*ob]=c;
        }
   if(x>=alle){
    x=0;
   }
   l->upb=l->upe;
   l->upe=x;
//   fprintf(stderr,"x:%d\n",x);
    //}
}
void drawLayer(SDL_Surface *screen,struct layer*l,int x1,int y1,int x2,int y2){
    int x,y,w,h;
    unsigned int c;
//    int px,py,px1,px2,py1,py2;
    w=x2-x1;
    h=y2-y1;
    for(y=y1;y<y2;y++)
        for(x=x1;x<x2;x++){
            c=l->p[(x-x1)*l->w/w+((y-y1)*l->h/h)*l->w];
            putpixel(screen,x,y,c+c*256+c*256*256);          
        }

}

void drawMask(SDL_Surface *screen,struct layer*l,double value,int maxr,int maxg,int maxb){
    Uint32 *q;
    unsigned char*p;
    int w;
    int h;
    int x,y,i,j,x0,y0;
    int cw,ch,sw,sh;
    p=l->p;
    w=l->w;
    h=l->h;
    cw=value*screen->w/w;
    ch=value*screen->h/h;
    sw=(1-value)*screen->w/w/2;
    sh=(1-value)*screen->h/h/2;
    
    Uint32 c;
    //if(screen->w!=w||screen->h!=h)
    //    return;

    for(y=0;y<h;y++)
        for(x=0;x<w;x++,p++){
            int r,g,b;
            r=*p*maxr/255 ;
            g=*p*maxg/255 ;
            b=*p*maxb/255 ;
            
            c=r |((g)*256) | ((b)*256*256);
            x0=x*screen->w/w + sw;
            y0=y*screen->h/h + sh;
            for(j=0;j<ch;j++)
                for(i=0;i<cw;i++){
                    putpixel(screen,x0+i,y0+j,c);
                
                }
            
            
        
        }


}
void drawMask(SDL_Surface *screen,struct layer*l,double value,int maxl){
    drawMask(screen,l,value,maxl,maxl,maxl);

}
void mixBWSizedOr(SDL_Surface *screen,struct layer*l,double value,int middle,Uint32 color){
    Uint32 *q;
    unsigned char*p;
    int pitch;
    int w,i;
    int h;
    int x,y,j,x0,y0;
    int cw[256],ch[256],sw[256],sh[256];
    p=l->p;
    w=l->w;
    h=l->h;
    if(middle>=255)
        middle=254;
    for(i=0;i<256;i++){
        int ii;
        ii=i-middle;
        
        if(ii<0)
            ii=0;
        ii=ii*255/(255-middle);
        cw[i]=(ii)*value*screen->w/w/256;
        ch[i]=(ii)*value*screen->h/h/256;
        sw[i]=(256-ii*value)*screen->w/w/2/256;
        sh[i]=(256-ii*value)*screen->h/h/2/256;
    }
    Uint32 c;
    //if(screen->w!=w||screen->h!=h)
    //    return;
    q=(Uint32*)screen->pixels;
    pitch=screen->pitch/4;
    for(y=0;y<h;y++)
        for(x=0;x<w;x++,p++){
            int k;
            k=*p;
            
            //c=c |((c)*256) | ((c)*256*256);
            x0=x*screen->w/w + sw[k];
            y0=y*screen->h/h + sh[k];
            for(j=0;j<ch[k];j++)
                for(i=0;i<cw[k];i++){
                    int r,g,b;
            if(color)
               c=color;
            else
                c=colorSeq2();     

                    //c=q[(x0+i)+(y0+j)*pitch];
                             //getpixel(screen,x0+i,y0+j);
               //     pixel2rgb(c,r,g,b);
                              //rgb2pixel(g,r,b,&c);
                 //   c=(r+g+b)/3;
                   // c=c+c*256+c*256*256;
                  // c=c%256;
                  //  c=255+255*256+255*256*256;
                        q[(x0+i)+(y0+j)*pitch]|=c;
                    //else
                      //   q[(x0+i)+(y0+j)*pitch]=;   
               //     putpixel(screen,x0+i,y0+j,c);
                
                }
            
            
        
        }


}


void mixBWSized(SDL_Surface *screen,struct layer*l,double value,int middle,Uint32 color){
    Uint32 *q;
    unsigned char*p;
    int pitch;
    int w,i;
    int h;
    int x,y,j,x0,y0;
    int cw[256],ch[256],sw[256],sh[256];
    p=l->p;
    w=l->w;
    h=l->h;
    for(i=0;i<256;i++){
        int ii;
        ii=i-middle;
        if(ii<0)
            ii=0;
        cw[i]=(ii)*value*screen->w/w/256;
        ch[i]=(ii)*value*screen->h/h/256;
        sw[i]=(256-ii*value)*screen->w/w/2/256;
        sh[i]=(256-ii*value)*screen->h/h/2/256;
    }
    Uint32 c;
    //if(screen->w!=w||screen->h!=h)
    //    return;
    q=(Uint32*)screen->pixels;
    pitch=screen->pitch/4;
    for(y=0;y<h;y++)
        for(x=0;x<w;x++,p++){
            int k;
            k=*p;
            
            //c=c |((c)*256) | ((c)*256*256);
            x0=x*screen->w/w + sw[k];
            y0=y*screen->h/h + sh[k];
            for(j=0;j<ch[k];j++)
                for(i=0;i<cw[k];i++){
                    int r,g,b;
            if(color)
               c=color;
            else
                c=colorSeq2();     

                    //c=q[(x0+i)+(y0+j)*pitch];
                             //getpixel(screen,x0+i,y0+j);
               //     pixel2rgb(c,r,g,b);
                              //rgb2pixel(g,r,b,&c);
                 //   c=(r+g+b)/3;
                   // c=c+c*256+c*256*256;
                  // c=c%256;
                  //  c=255+255*256+255*256*256;
                        q[(x0+i)+(y0+j)*pitch]=c;
                    //else
                      //   q[(x0+i)+(y0+j)*pitch]=;   
               //     putpixel(screen,x0+i,y0+j,c);
                
                }
            
            
        
        }


}
#ifdef GLBILD

#include"mygl.h"

inline void zeroone(double &a){
    if(a<0.)
        a=0.;
    if(a>1.)
        a=1.;

}
/*
inline void transform(double sp,double me,double &x,double&y){
    double r,a;
    x-=0.5;
    y-=0.5;
    r=x*x+y*y;
    a=atan2(y,x)+r*sp*M_PI;
    r=pow(r,1-me);
    x=cos(a)*r+0.5;
    y=sin(a)*r+0.5;
}*/
void mixBWSizedOrGLOp_Fast(struct layer*l,double value,int middle,Uint32 color,int tex,int screenW,int screenH,double op){
    glBindTexture(GL_TEXTURE_2D, tmpt);
    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, GLW, GLH, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);





  glBindTexture(GL_TEXTURE_2D, tex);
  glColor4f(1.0f,1.0f,1.0f,1);
  glBegin(GL_TRIANGLE_STRIP);
       glTexCoord2f (0,0); glVertex2f (0.0,GLH);
       glTexCoord2f (0,1); glVertex2f (0.0,0);
       glTexCoord2f (1,0); glVertex2f (0+GLW,GLH );
       glTexCoord2f (1,1); glVertex2f (0+GLW,0);
  glEnd();
     
    
  glBindTexture(GL_TEXTURE_2D, itex);


  glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, l->w, l->h,
            0, GL_RGBA, GL_UNSIGNED_BYTE, l->p4b);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

  glBlendFunc(GL_ZERO,GL_SRC_ALPHA);

  glBindTexture(GL_TEXTURE_2D, itex);
  glColor4f(1.0f,1.0f,1.0f,1);
  glBegin(GL_TRIANGLE_STRIP);
       glTexCoord2f (0,0); glVertex2f (0.0,GLH);
       glTexCoord2f (0,1); glVertex2f (0.0,0);
       glTexCoord2f (1,0); glVertex2f (0+GLW,GLH );
       glTexCoord2f (1,1); glVertex2f (0+GLW,0);
  glEnd();


  glBindTexture(GL_TEXTURE_2D, tmp2t);
  glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, GLW, GLH, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




  glBlendFunc(GL_SRC_ALPHA,GL_ONE);




        glBindTexture(GL_TEXTURE_2D, tmpt);
        glColor4f(1,1,1,1);
        glBegin(GL_TRIANGLE_STRIP);
                glTexCoord2f (0.0,1.0); glVertex2f (0.0,0.0);
                glTexCoord2f (0.0,0.0); glVertex2f (0.0,0+GLH);
                glTexCoord2f (1.0,1.0); glVertex2f (0+GLW,0.0);
                glTexCoord2f (1.0,0.0); glVertex2f (0+GLW,GLH);
  
       glEnd();

        glBindTexture(GL_TEXTURE_2D, tmp2t);
        glColor4f(1,1,1,op);
        glBegin(GL_TRIANGLE_STRIP);
                glTexCoord2f (0.0,1.0); glVertex2f (0.0,0.0);
                glTexCoord2f (0.0,0.0); glVertex2f (0.0,0+GLH);
                glTexCoord2f (1.0,1.0); glVertex2f (0+GLW,0.0);
                glTexCoord2f (1.0,0.0); glVertex2f (0+GLW,GLH);
  
       glEnd();

}


void mixBWSizedOrGL_Transform_Op_Fast(struct layer*l,double value,int middle,Uint32 color,int tex,int screenW,int screenH,
double ax,double ay,
double bx,double by,double op//,double spiral,double mega//,
//double cx,double cy,
//double dx,double dy
){
    glBindTexture(GL_TEXTURE_2D, tmpt);
    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, GLW, GLH, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);





  glBindTexture(GL_TEXTURE_2D, tex);
  glColor4f(1.0f,1.0f,1.0f,1);
  glBegin(GL_TRIANGLE_STRIP);
       glTexCoord2f (ax,ay); glVertex2f (0.0,GLH);
       glTexCoord2f (ax,by); glVertex2f (0.0,0);
       glTexCoord2f (bx,ay); glVertex2f (0+GLW,GLH );
       glTexCoord2f (bx,by); glVertex2f (0+GLW,0);
  glEnd();
     
    
  glBindTexture(GL_TEXTURE_2D, itex);


  glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, l->w, l->h,
            0, GL_RGBA, GL_UNSIGNED_BYTE, l->p4b);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

  glBlendFunc(GL_ZERO,GL_SRC_ALPHA);

  glBindTexture(GL_TEXTURE_2D, itex);
  glColor4f(1.0f,1.0f,1.0f,1);
  glBegin(GL_TRIANGLE_STRIP);
       glTexCoord2f (0,0); glVertex2f (0.0,GLH);
       glTexCoord2f (0,1); glVertex2f (0.0,0);
       glTexCoord2f (1,0); glVertex2f (0+GLW,GLH );
       glTexCoord2f (1,1); glVertex2f (0+GLW,0);
  glEnd();


  glBindTexture(GL_TEXTURE_2D, tmp2t);
  glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, GLW, GLH, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




  glBlendFunc(GL_SRC_ALPHA,GL_ONE);




        glBindTexture(GL_TEXTURE_2D, tmpt);
        glColor4f(1,1,1,1);
        glBegin(GL_TRIANGLE_STRIP);
                glTexCoord2f (0.0,1.0); glVertex2f (0.0,0.0);
                glTexCoord2f (0.0,0.0); glVertex2f (0.0,0+GLH);
                glTexCoord2f (1.0,1.0); glVertex2f (0+GLW,0.0);
                glTexCoord2f (1.0,0.0); glVertex2f (0+GLW,GLH);
  
       glEnd();

        glBindTexture(GL_TEXTURE_2D, tmp2t);
        glColor4f(1,1,1,op);
        glBegin(GL_TRIANGLE_STRIP);
                glTexCoord2f (0.0,1.0); glVertex2f (0.0,0.0);
                glTexCoord2f (0.0,0.0); glVertex2f (0.0,0+GLH);
                glTexCoord2f (1.0,1.0); glVertex2f (0+GLW,0.0);
                glTexCoord2f (1.0,0.0); glVertex2f (0+GLW,GLH);
  
       glEnd();

}
void mixBWSizedOrGL_Transform_Op(struct layer*l,double value,int middle,Uint32 color,int tex,int screenW,int screenH,
double bx,double ay,
double ax,double by,double op//,double spiral,double mega//,
//double cx,double cy,
//double dx,double dy
){
    Uint32 *q;
    unsigned char*p;
    int pitch;
    int w,i;
    int h;
    int x,y,j,x0,y0;
    int cw[256],ch[256],sw[256],sh[256];
    p=l->p;
    w=l->w;
    h=l->h;
    if(tex>=0)
       glEnable(GL_TEXTURE_2D);
   
    
    if(middle>=255)
        middle=254;
    int a_middle;
    a_middle=middle;
   // if(a_middle<=0)
     //   a_middle=0;
    for(i=0;i<256;i++){
        int ii;
        ii=i-middle;
        
        if(ii<0)
            ii=0;
        ii=ii*255/(255-a_middle);
        cw[i]=(ii)*value*screenW/w/256;
        ch[i]=(ii)*value*screenH/h/256;
        sw[i]=(256-ii*value)*screenW/w/2/256;
        sh[i]=(256-ii*value)*screenH/h/2/256;
    }
    Uint32 c;
    for(y=0;y<h;y++)
        for(x=0;x<w;x++,p++){
            int k,x1,y1,k1,k2,k3,k4;
            k1=l->p[x+y*w];
            k2=l->p[(x+1)%w+y*w];
            k3=l->p[(x)+((y+1)%h)*w];
            k4=l->p[(x+1)%w+((y+1)%h)*w];
            
            
            double a,b,c,d;
            k=*p;
            x0=x*screenW/w; //+ sw[k];
            y0=y*screenH/h; //+ sh[k];
            
              x1=(x+1)*screenW/w;//+cw[k];
              y1=(y+1)*screenH/h;//+ch[k];
           //fprintf(stderr,"%d %d ",x0,y0);
           //fprintf(stderr,"%d %d\n",x1,y1);
           if(x1<=x0|y1<=y0)
            continue;
          if(x0<0)
            x0=0;
          if(y0<0)
            y0=0;
          if(y1>screenH)
            y1=screenH;
          if(x1>screenW)
            x1=screenW;

          glBegin(GL_TRIANGLE_STRIP);
                    a=x0/(double)screenW;
                    b=y0/(double)screenH;
                    c=x1/(double)screenW;
                    d=y1/(double)screenH;
                    double cx1,cy1,cx2,cy2,cx3,cy3,cx4,cy4;
                    cx1=a*ax+(1-a)*bx;
                    
                    cy1=d*ay+(1-d)*by;
                    cx2=a*ax+(1-a)*bx;
                    cy2=b*ay+(1-b)*by;
                    cx3=c*ax+(1-c)*bx;
                    cy3=d*ay+(1-d)*by;
                    cx4=c*ax+(1-c)*bx;
                    cy4=b*ay+(1-b)*by;
                    
                    
             //       transform(spiral,mega,cx1,cy1);
               //     transform(spiral,mega,cx2,cy2);
                 //   transform(spiral,mega,cx3,cy3);
                   // transform(spiral,mega,cx4,cy4);

                    zeroone(cx1);
                    zeroone(cy1);
                                        
                    zeroone(cx2);
                    zeroone(cy2);
                                        
                    zeroone(cx3);
                    zeroone(cy3);
                                        
                    zeroone(cx4);
                    zeroone(cy4);
                    glColor4f(1.0f,1.0f,1.0f,op*k3/256);
                                        
                    if(tex>=0)
                        glTexCoord2f (cx1,cy1);
                     else{
                       c=colorSeq2();
                              if(color)
                               c=color;
                       glColor4bv((const GLbyte*)&c);
                    }
                    glVertex2f (x0,y1);

                    glColor4f(1.0f,1.0f,1.0f,op*k1/256);

                    if(tex>=0)
                        glTexCoord2f (cx2,cy2);
                     else{
                       c=colorSeq2();
                               if(color)
                               c=color;
                       glColor4bv((const GLbyte*)&c);
                    }
                    
                    glVertex2f (x0,y0);
                    glColor4f(1.0f,1.0f,1.0f,op*k4/256);

                    if(tex>=0)
                        glTexCoord2f (cx3,cy3);
                     else{
                       c=colorSeq2();
                           if(color)
                           c=color;
                       glColor4bv((const GLbyte*)&c);
                    }
                    
                    glVertex2f (x1,y1);

                    glColor4f(1.0f,1.0f,1.0f,op*k2/256);

                    if(tex>=0)
                        glTexCoord2f (cx4,cy4);
                    else{
                       c=colorSeq2();
                       if(color)
                           c=color;
                       glColor4bv((const GLbyte*)&c);
                    }
                    
                    glVertex2f (x1,y0);
  
           glEnd();
                        
            
        
        }


}
void mixBWSizedOrGL_Transform(struct layer*l,double value,int middle,Uint32 color,int tex,int screenW,int screenH,
double bx,double ay,
double ax,double by//,
//double cx,double cy,
//double dx,double dy
){
    Uint32 *q;
    unsigned char*p;
    int pitch;
    int w,i;
    int h;
    int x,y,j,x0,y0;
    int cw[256],ch[256],sw[256],sh[256];
    p=l->p;
    w=l->w;
    h=l->h;
    if(tex>=0)
       glEnable(GL_TEXTURE_2D);
   
    
    if(middle>=255)
        middle=254;
    int a_middle;
    a_middle=middle;
   // if(a_middle<=0)
     //   a_middle=0;
    for(i=0;i<256;i++){
        int ii;
        ii=i-middle;
        
        if(ii<0)
            ii=0;
        ii=ii*255/(255-a_middle);
        cw[i]=(ii)*value*screenW/w/256;
        ch[i]=(ii)*value*screenH/h/256;
        sw[i]=(256-ii*value)*screenW/w/2/256;
        sh[i]=(256-ii*value)*screenH/h/2/256;
    }
    Uint32 c;
    for(y=0;y<h;y++)
        for(x=0;x<w;x++,p++){
            int k,x1,y1;
            double a,b,c,d;
            k=*p;
            x0=x*screenW/w + sw[k];
            y0=y*screenH/h + sh[k];
            
              x1=x0+cw[k];
              y1=y0+ch[k];
           //fprintf(stderr,"%d %d ",x0,y0);
           //fprintf(stderr,"%d %d\n",x1,y1);
           if(x1<=x0|y1<=y0)
            continue;
          if(x0<0)
            x0=0;
          if(y0<0)
            y0=0;
          if(y1>screenH)
            y1=screenH;
          if(x1>screenW)
            x1=screenW;
            
          glBegin(GL_TRIANGLE_STRIP);
                    a=x0/(double)screenW;
                    b=y0/(double)screenH;
                    c=x1/(double)screenW;
                    d=y1/(double)screenH;
                    double cx1,cy1,cx2,cy2,cx3,cy3,cx4,cy4;
                    cx1=a*ax+(1-a)*bx;
                    cy1=d*ay+(1-d)*by;
                    cx2=a*ax+(1-a)*bx;
                    cy2=b*ay+(1-b)*by;
                    cx3=c*ax+(1-c)*bx;
                    cy3=d*ay+(1-d)*by;
                    cx4=c*ax+(1-c)*bx;
                    cy4=b*ay+(1-b)*by;
                    zeroone(cx1);
                    zeroone(cy1);
                                        
                    zeroone(cx2);
                    zeroone(cy2);
                                        
                    zeroone(cx3);
                    zeroone(cy3);
                                        
                    zeroone(cx4);
                    zeroone(cy4);
                                        
                    if(tex>=0)
                        glTexCoord2f (cx1,cy1);
                     else{
                       c=colorSeq2();
                              if(color)
                               c=color;
                       glColor4bv((const GLbyte*)&c);
                    }
                    glVertex2f (x0,y1);
                    if(tex>=0)
                        glTexCoord2f (cx2,cy2);
                     else{
                       c=colorSeq2();
                               if(color)
                               c=color;
                       glColor4bv((const GLbyte*)&c);
                    }
                    
                    glVertex2f (x0,y0);
                    if(tex>=0)
                        glTexCoord2f (cx3,cy3);
                     else{
                       c=colorSeq2();
                           if(color)
                           c=color;
                       glColor4bv((const GLbyte*)&c);
                    }
                    
                    glVertex2f (x1,y1);
                    if(tex>=0)
                        glTexCoord2f (cx4,cy4);
                    else{
                       c=colorSeq2();
                       if(color)
                           c=color;
                       glColor4bv((const GLbyte*)&c);
                    }
                    
                    glVertex2f (x1,y0);
  
           glEnd();
                        
            
        
        }


}
void mixBWSizedOrGL(struct layer*l,double value,int middle,Uint32 color,int tex,int screenW,int screenH){
    Uint32 *q;
    unsigned char*p;
    int pitch;
    int w,i;
    int h;
    int x,y,j,x0,y0;
    int cw[256],ch[256],sw[256],sh[256];
    p=l->p;
    w=l->w;
    h=l->h;
    if(tex>=0)
       glEnable(GL_TEXTURE_2D);
   
    
    if(middle>=255)
        middle=254;
    for(i=0;i<256;i++){
        int ii;
        ii=i-middle;
        
        if(ii<0)
            ii=0;
        ii=ii*255/(255-middle);
        cw[i]=(ii)*value*screenW/w/256;
        ch[i]=(ii)*value*screenH/h/256;
        sw[i]=(256-ii*value)*screenW/w/2/256;
        sh[i]=(256-ii*value)*screenH/h/2/256;
    }
    Uint32 c;
    for(y=0;y<h;y++)
        for(x=0;x<w;x++,p++){
            int k,x1,y1;
            k=*p;
            x0=x*screenW/w + sw[k];
            y0=y*screenH/h + sh[k];
            
              x1=x0+cw[k];
              y1=y0+ch[k];
           //fprintf(stderr,"%d %d ",x0,y0);
           //fprintf(stderr,"%d %d\n",x1,y1);
           if(x1<=x0|y1<=y0)
            continue;
          if(x0<0)
            x0=0;
          if(y0<0)
            y0=0;
          if(y1>screenH)
            y1=screenH;
          if(x1>screenW)
            x1=screenW;
            
          glBegin(GL_TRIANGLE_STRIP);
                    
                    if(tex>=0)
                        glTexCoord2f (x0/(double)screenW,1-y1/(double)screenH);
                     else{
                       c=colorSeq2();
                              if(color)
                               c=color;
                       glColor4bv((const GLbyte*)&c);
                    }
                    glVertex2f (x0,y1);
                    if(tex>=0)
                        glTexCoord2f (x0/(double)screenW,1-y0/(double)screenH);
                     else{
                       c=colorSeq2();
                               if(color)
                               c=color;
                       glColor4bv((const GLbyte*)&c);
                    }
                    
                    glVertex2f (x0,y0);
                    if(tex>=0)
                        glTexCoord2f (x1/(double)screenW,1-y1 /(double)screenH);
                     else{
                       c=colorSeq2();
                           if(color)
                           c=color;
                       glColor4bv((const GLbyte*)&c);
                    }
                    
                    glVertex2f (x1,y1);
                    if(tex>=0)
                        glTexCoord2f (x1/(double)screenW,1-y0/(double)screenH );
                    else{
                       c=colorSeq2();
                       if(color)
                           c=color;
                       glColor4bv((const GLbyte*)&c);
                    }
                    
                    glVertex2f (x1,y0);
  
           glEnd();
                        
            
        
        }


}
void mixBWSizedOrGLOp(struct layer*l,double value,int middle,Uint32 color,int tex,int screenW,int screenH,double op){
    Uint32 *q;
    unsigned char*p;
    int pitch;
    int w,i;
    int h;
    int x,y,j,x0,y0;
    int cw[256],ch[256],sw[256],sh[256];
    p=l->p;
    w=l->w;
    h=l->h;
    if(tex>=0)
       glEnable(GL_TEXTURE_2D);
   
    
    if(middle>=255)
        middle=254;
    /*for(i=0;i<256;i++){
        int ii;
        ii=i-middle;
        
        if(ii<0)
            ii=0;
        ii=ii*255/(255-middle);
        cw[i]=(ii)*value*screenW/w/256;
        ch[i]=(ii)*value*screenH/h/256;
        sw[i]=(256-ii*value)*screenW/w/2/256;
        sh[i]=(256-ii*value)*screenH/h/2/256;
    }*/
    Uint32 c;
    for(y=0;y<h;y++)
        for(x=0;x<w;x++,p++){
            int k,x1,y1,k1,k2,k3,k4,sens ;
            k1=l->p[x+y*w];
            k2=l->p[(x+1)%w+y*w];
            k3=l->p[(x)+((y+1)%h)*w];
            k4=l->p[(x+1)%w+((y+1)%h)*w];

            k=*p;
            x0=x*screenW/w; //+ sw[k];
            y0=y*screenH/h; //+ sh[k];
            
              x1=(x+1)*screenW/w;//+cw[k];
              y1=(y+1)*screenH/h;///+ch[k];
           //fprintf(stderr,"%d %d ",x0,y0);
           //fprintf(stderr,"%d %d\n",x1,y1);
           if(x1<=x0|y1<=y0)
            continue;
          if(x0<0)
            x0=0;
          if(y0<0)
            y0=0;
          if(y1>screenH)
            y1=screenH;
          if(x1>screenW)
            x1=screenW;
//          glColor4f(1.0f,1.0f,1.0f,op*k/256);
           glColor4f(1.0f,1.0f,1.0f,op*k3/256);

          glBegin(GL_TRIANGLE_STRIP);
                    
                    if(tex>=0)
                        glTexCoord2f (x0/(double)screenW,1-y1/(double)screenH);
                     else{
                       c=colorSeq2();
                              if(color)
                               c=color;
                       glColor4bv((const GLbyte*)&c);
                    }
                    glVertex2f (x0,y1);
           glColor4f(1.0f,1.0f,1.0f,op*k1/256);

                    if(tex>=0)
  
                        glTexCoord2f (x0/(double)screenW,1-y0/(double)screenH);
                     else{
                       c=colorSeq2();
                               if(color)
                               c=color;
                       glColor4bv((const GLbyte*)&c);
                    }
                    
                    glVertex2f (x0,y0);
           glColor4f(1.0f,1.0f,1.0f,op*k4/256);

                    if(tex>=0)
                        glTexCoord2f (x1/(double)screenW,1-y1 /(double)screenH);
                     else{
                       c=colorSeq2();
                           if(color)
                           c=color;
                       glColor4bv((const GLbyte*)&c);
                    }
                    
                    glVertex2f (x1,y1);
                    glColor4f(1.0f,1.0f,1.0f,op*k2/256);

                    if(tex>=0)
                        glTexCoord2f (x1/(double)screenW,1-y0/(double)screenH );
                    else{
                       c=colorSeq2();
                       if(color)
                           c=color;
                       glColor4bv((const GLbyte*)&c);
                    }
                    
                    glVertex2f (x1,y0);
  
           glEnd();
                        
            
        
        }


}

extern GLuint vct;
char upsideBuf[4*1000*1000];

void *upsideDown(char*p,int w,int h){
    if(h*w>1000*1000)
        return (void*)p;
    for(int y=0;y<h;y++){
        memcpy(upsideBuf+4*w*(h-1-y),p+4*w*y,w*4);
    }
    return upsideBuf;
}
void mixBWSizedOrGL(struct layer*l,double value,double middle,char*img,int imgw,int imgh,double alpha,int screenW,int screenH){
    
      glBindTexture(GL_TEXTURE_2D, vct);
        if(img!=NULL){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgw, imgh,
            0, GL_BGR, GL_UNSIGNED_BYTE, upsideDown(img,imgw, imgh));
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }        

//        glBindTexture(GL_TEXTURE_2D, sct);
        if(alpha>0.000001){
           glEnable(GL_BLEND);
           glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA/*GL_ONE*/);

           glColor4f(1.0f,1.0f,1.0f,alpha);
            mixBWSizedOrGL(l,value,-256+2*256*middle,0,vct,screenW,screenH);
        }
}
void mixBWSizedOrGL_tex(struct layer*l,double value,double middle,GLuint tex,double alpha,int screenW,int screenH){
    
     // glBindTexture(GL_TEXTURE_2D, tex);
        if(alpha>0.000001){
           glEnable(GL_BLEND);
           glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA/*GL_ONE*/);

           glColor4f(1.0f,1.0f,1.0f,alpha);
           mixBWSizedOrGL(l,value,middle*255,0,tex,screenW,screenH);
        }
}
#endif


Uint32 *mulBuf=NULL;

int initMulBuf=0;
void buildMulTable(){
    int r,g,b,i,rr,gg,bb,ll;
    Uint32 c1,c2,c3,cc1,cc2,cc3;
    if(initMulBuf)
        return;
    if(mulBuf==NULL){
        mulBuf=(Uint32*)malloc(256*256*256*16*sizeof(Uint32));
        if(mulBuf==NULL)
            return;
    
    }
    for(i=0;i<16;i++)
    for(r=0;r<256;r++){
        for(g=0;g<256;g++){
            for(b=0;b<256;b++){
                c1=r|g*256|b*256*256;
                ll=(r+g+b)/3;
                rr=(r*i+ll*(15-i))/15;
                gg=(g*i+ll*(15-i))/15;
                bb=(b*i+ll*(15-i))/15;
                
                cc1=(rr) | (gg) *256 | (bb) *256*256;
                
                
                mulBuf[c1*16+i]=cc1;   
            }
        }    
    }
    
    initMulBuf=1;
}
int s2lx[2048];
int s2ly[2048];
int inits2l=0;
void mulMixAllScreen(SDL_Surface *screen,struct layer*l){
    int x,y,xx,yy,d;
    Uint32*q;
    if(!inits2l){
        for(x=0;x<2048;x++){
            s2lx[x]=x*l->w/screen->w;
            s2ly[x]=(x*l->h/screen->h) * l->w;
        }
        inits2l=1;
    }

       for(y=0,q=(Uint32*)screen->pixels;y<screen->h;y++,q=(Uint32*)( ((Uint8 *)screen->pixels) + y * screen->pitch))
            for(x=0;x<screen->w;x++,q++){
                xx=s2lx[x];
                yy=s2ly[y];
                d=l->p[xx+yy];
            
                *q=mulBuf[((*q)&(255|(255*256)|(255*256*256)))*16+d];
            }




}
void mulMix(SDL_Surface *screen,struct layer*l,double value){
    Uint32 *q;
    unsigned char*p;
    int w;
    int h;
    int x,y,i,j,x0,y0;
    int cw,ch,sw,sh;
    p=l->p;
    w=l->w;
    h=l->h;
    cw=value*screen->w/w;
    ch=value*screen->h/h;
    sw=(1-value)*screen->w/w/2;
    sh=(1-value)*screen->h/h/2;
    
    Uint32 c;
    //if(screen->w!=w||screen->h!=h)
    //    return;
    buildMulTable();
    if(fabs(value-1.)<0.0001){
        mulMixAllScreen(screen,l);
        return;
    }
    for(y=0;y<h;y++)
        for(x=0;x<w;x++,p++){
            //c=*p |(((unsigned int)*p)*256) | (((unsigned int)*p)*256*256);
            x0=x*screen->w/w + sw;
            y0=y*screen->h/h + sh;
            for(j=0;j<ch;j++)
                for(i=0;i<cw;i++){
                    c=getpixel(screen,x0+i,y0+j);
                    //x0=x0/0;
    
                    //c=mulBuf[c&(255|(255*256)|(255*256*256))][(*p)/16];
                    if( *p>100){
                        c= ((c&255) + ((c/256)&255) + ((c/256/256)&255))/3;
                        c= c|(c*256)|(c*256*256);
                    }
                    //c=0;
                    putpixel(screen,x0+i,y0+j,c);
                
                }
            
            
        
        }


}

struct layer* copyLayer(struct layer*l){
    struct layer*r;
    int i;
    if(l==NULL)
        return NULL;
    r=makeLayer(l->w,l->h);
    if(r==NULL)
        return NULL;
    if(l->p!=NULL){
        for(i=0;i<l->w*l->h;i++){
            r->p[i]=l->p[i];
        }
    
    }else{
       for(i=0;i<l->w*l->h;i++){
            r->p[i]=0;
        }
    
    }
    return r;
}

#endif
