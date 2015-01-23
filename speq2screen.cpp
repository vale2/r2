#define SPEQTW 500
    double x[SPEQTW];
    double y[SPEQTW];
    double q[SPEQTW];
    double speqt[1000];
    double frk[1000];


double maxAmps[2048];
double*touch_freqs;
double* touch_amps;
double* touch_ks;
double* touch_vs;
double* touch_ph;
int touch_n;

struct speqPoint{
    double freq,k,v;
    int ns;
    double d[10];
};

void         putPixel(Uint32* ptr,int x,int  y, Uint32 c,int w,int h){
    ptr[x+y*w]=c;


}
Uint32         getPixel(Uint32* ptr,int x,int  y,int w,int h){
    return ptr[x+y*w];


}
    

void DrawInt(double *freqs,double *amps,double*ph,int n,double watchForward,int w,int h,Uint32 * ptr){
    int i,j;
    double r,a,d,k,v;
    double tt;
double t[1000];
double frk[1000];

    k=0;v=0;
    d=0;
    int wf,nextfr;
    double nextfrt,tmpfrt;  
    for(wf=0;wf+1<n&&freqs[0]/freqs[wf+1]<=watchForward;wf++){
        t[wf]=ph[wf+1];
        frk[wf]=freqs[wf+1]/freqs[0];
    }
    double yy=0;
    double lyy=0;
    double xx=0;
    double dy,koef;
    double dx=0;
    int xxcount=0;
    xx=0;
    yy=ph[0];
    for(i=0;xxcount<1000;i++){
        nextfr=0;
        nextfrt=t[0]+frk[0];
        for(j=0;j<wf;j++){
            if(nextfrt>t[j]+frk[j]){
                nextfrt=t[j]+frk[j];
                nextfr=j;  
            }
        }
        t[nextfr]+=frk[nextfr];
     //   q[i]=amps[nextfr+1] * (freqs[nextfr+1]/freqs[0]);
        yy+=frk[nextfr];
        while(yy>1){
            yy-=1.;
            xx+=0.001;
        }
        while(xx>1){
            xx-=1.;
            xxcount++;
//            SDL_Flip( sc );
  //         while(readKey()<0);

        }
        
        int mx,my;
        Uint32 c;
        mx=xx*w;
        my=yy*h;
        if(mx<w && my<h){
            c=getPixel(ptr,mx,  my,w,h);
            c=c&255;
//        if(c==0)
            if(c<255){
                c++;
                if(c+c/4<255){
                c=c+c/4;
                }else
                   c=255;
            }
        //if(c/2+)
            if(3*c/4+64<255)
                c=3*c/4+64;
            else 
                c=255;
            c=c|(c*256)|(c*256*256);
            putPixel(ptr, mx, my,c,w,h);
        }

                
    }    
    
    
}

void genTexInterval(double dfreq,Uint32*ptr,int w,int h){
    double freqs[10];
    double amps[10];
    double ph[10];
    freqs[0]=1;
    freqs[1]=dfreq;
    amps[0]=1;
    amps[1]=1;
    ph[0]=0.3;
    ph[1]=0.3;
    DrawInt(freqs,amps,ph,2,200,w,h,ptr); 
}

int intervalsTexLoad(double df,int w,int h,Uint32*ptr){
    char s[128];
    sprintf(s,"intervalsTex_%dx%d/%lf",w,h,df);
    FILE*f;
    f=fopen(s,"r");
    if(f!=NULL){
        fread(ptr,w*h,sizeof(Uint32),f);
        fclose(f);
        return 1;    
    }
    return 0;
}
#include<sys/stat.h>
int intervalsTexSave(double df,int w,int h,Uint32*ptr){
    char s[128];
    sprintf(s,"intervalsTex_%dx%d",w,h,df);
    mkdir(s,S_IREAD|S_IWRITE|S_IRWXU);    
    sprintf(s,"intervalsTex_%dx%d/%lf",w,h,df);
    FILE*f;
    f=fopen(s,"w");
    if(f!=NULL){
        fwrite(ptr,w*h,sizeof(Uint32),f);
        fclose(f);
        return 1;    
    }
    return 0;
}


#define INTERVALS 13
GLuint intervals[512][512];
char intervalsInit[512][512];


//#define texw 1024
//#define texh 768
//#define texw 400
//#define texh 300
#define texw 800
#define texh 600

Uint32 ibuf[texw*texh];

void getAllIntervals(){
 double * freqs;
 freqs=touch_freqs;
 int i,j;
 fprintf(stderr,"Generating %d textures\n",touch_n);

 for(i=0;i<touch_n;i++){
    if(fabs(freqs[i])<0.001 || freqs[i]>4000.)
        continue;
    for(j=i+1;j<touch_n;j++){
            int li,lj;
            int flag;
            flag=0;
            if(fabs(freqs[j])<0.001 || freqs[j]>4000.)
                    continue;
            if(freqs[j]>2*freqs[i])
                 break;
    
            for(li=0;li<=i;li++){
                if(fabs(freqs[i])<0.001 || freqs[i]>4000.)
                    continue;
                
                for(lj=0;lj<touch_n;lj++){
                    //if(fabs(freqs[lj])<0.001 || freqs[]>1000.)
                      //    continue;
                    for(int o=-11;o<11;o++){
                        if(intervalsInit[li][lj] && fabs(freqs[lj]/freqs[li] - freqs[j]/freqs[i] - o ) <0.0000000000001 ){
                            flag=1;
                            break;
                        }
                    }
                    if(flag)
                     break;
                }
                if(flag)
                 break;
            
            }
            if(!flag)
                   if(intervalsTexLoad(freqs[j]/freqs[i],texw,texh,ibuf)){
//                      fprintf(stderr,"(L)");
                      flag=2;
                   }
 
            if(flag==1){
                intervals[i][j]=intervals[li][lj];
                intervalsInit[i][j]=1;

            }else{
                if(flag==0){
                    genTexInterval(freqs[j]/freqs[i],ibuf,texw,texh);
                    intervalsTexSave(freqs[j]/freqs[i],texw,texh,ibuf);
                }
                glGenTextures(1,&( intervals[i][j]));
 
                glBindTexture(GL_TEXTURE_2D, intervals[i][j]);
                glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, texw,texh,
                0, GL_RGBA, GL_UNSIGNED_BYTE, ibuf);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            }
            intervalsInit[i][j]=1;
    }
    fprintf(stderr,"(%d)",i);
 }
 
    fprintf(stderr,"\n");

}


int eqq(double ddf,int _12int){
    double et;
    et=pow(2,_12int/12.);
    if(fabs(ddf-et)<0.00001)
        return 1;
    return 0;

}
int IrraFraqInit;
void showIrraFraq(GLuint tex){
  double q1,q2;
  int i,j;
 double * freqs;
 double ops[30];
 GLuint texs[30];
 double ph[30];
 double  d[30];
 for(i=0;i<30;i++){
    ops[i]=0.;
 }
 
 freqs=touch_freqs;

  if(!IrraFraqInit){
        IrraFraqInit=1;
        getAllIntervals();
  }
 glClearColor(0,0,0,1);
            
 glEnable(GL_BLEND);
 glEnable(GL_TEXTURE_2D);
 glClearColor(0,0,0,1);
 double texzoom;
 texzoom=2;
 glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  int k=0;
  int ok;
  int minok;
  minok=log(freqs[1])/log(2);
  double okx,oky,okw,okh;
  okw=GLW;///3;
  okh=GLH;///3;
 for(i=0;i<touch_n;i++){
    if(fabs(freqs[i])<0.001)
        continue;
    q1=touch_amps[i]/maxAmps[i];
    
//    if(q1<0.1)
  //     continue;
    ok=log(freqs[i])/log(2)-minok;
    okx=0;//(ok%3) *GLW/3.;
    oky=0;//(ok/3) *GLH/3.;
    
    for(j=i+1;j<touch_n;j++){
        if(freqs[j]>2*freqs[i])
            break;
        q2=touch_amps[j]/maxAmps[j];
//        if((q1*q2)/freqs[i]*10<0.02)
  //             continue;
        double ddf;
        ddf=freqs[j]/freqs[i];
        if(eqq(ddf,12),eqq(ddf,7),eqq(ddf,5))
            continue;
        if(intervalsInit[i][j]){
           double dph;
            double op;
            op=10*(q1+q2)/freqs[i];
             int ii;
             for(ii=0;ii<30;ii++){
                if(ops[ii]<op){
                    int jj;
                    for(jj=29;jj>ii;jj--){
                        ops[jj]=ops[jj-1];
                        texs[jj]=texs[jj-1];
                        ph[jj]=ph[jj-1];
                        d[jj]=d[jj-1];
                    }
                    d[ii]=log(freqs[j]/freqs[i])/log(2);
                    ops[ii]=op;
                    texs[ii]=intervals[i][j];
                    ph[ii]=0;//
                    (touch_ph[i]-touch_ph[j])/M_PI/2.;
                    break;
                }
             }  
            
            
            

            
        }
    }
 }    



 for(i=0;i<30;i++){
//           dph=;
           k++;
           if(ops[i]>0.0001){
                glBindTexture(GL_TEXTURE_2D,texs[i] );
                 glColor4f(1.0f,1.0f,1.0f,ops[i]);
                  glBegin(GL_TRIANGLE_STRIP);
                  glTexCoord2f (0.5-0.5/texzoom,0.5-0.5/texzoom+ph[i]); glVertex2f (okx,oky+okh);
                  glTexCoord2f (0.5-0.5/texzoom,0.5+0.5/texzoom+ph[i]); glVertex2f (okx,oky);
                  glTexCoord2f (0.5+0.5/texzoom,0.5-0.5/texzoom+ph[i]); glVertex2f (okx+okw,oky+okh);
                  glTexCoord2f (0.5+0.5/texzoom,0.5+0.5/texzoom+ph[i]); glVertex2f (okx+okw,oky);
                 glEnd();
               fprintf(stderr,"%lf :",d[i]);
             //  fprintf(stderr,"%lf :",ops[i]);

             }

 }

    fprintf(stderr,"\n");
    saveGlScreen2Tex(tex);

}


struct speqPoint viewFreq(double *freqs,double *amps,double*ph,int n,double rmax,double watchForward){
    int i,j;
    double r,a,d,k,v;
    double tt;
    k=0;v=0;
    d=0;
//    double le[SPEQTW];
  //  double x,y;
    //for(i=0;i<SPEQTW;i++){
      //  le[i]=0;
    //} 
    int wf,nextfr;
    double nextfrt,tmpfrt;  
    struct speqPoint res;
    res.freq=freqs[0];
    res.k=0;
    res.v=0;
    if(freqs[0]<0.001)
        return res;
    for(wf=0;wf+1<n&&freqs[0]/freqs[wf+1]<=watchForward;wf++){
        speqt[wf]=ph[wf+1];
//        frk[wf]=0;
        frk[wf]=freqs[wf+1]/freqs[0];
//         printf("frk[%d]=%lf\n",wf,frk[wf]);
    }
    if(wf==0)
        return res; 
    double yy=0;
    double lyy=0;
    double xx=0;
    for(i=0;i<SPEQTW&&xx<200.;i++){
        //nextPoint(freqs,amps,n,watchForward,x[i],y[i],q[i]);
//        nextfr=-1;
        nextfr=0;
        nextfrt=speqt[0]+frk[0];
        for(j=1;j<wf;j++){
            if(nextfrt>speqt[j]+frk[j]){
                nextfrt=speqt[j]+frk[j];
                nextfr=j;  
            }
        }
        speqt[nextfr]+=frk[nextfr];
        q[i]=amps[nextfr+1];
        yy=speqt[nextfr];
        
        while(yy-lyy>=1.){
            lyy+=1;
          //  xx+=1;
        }
        
        y[i]=yy-lyy;
        xx=x[i]=yy/100.;
 //       putPixel(sc, x[i]*scw,  y[i]*sch,0xFFFFFF);

 //      printf("%lf %lf\n",x[i],y[i]);
        for(j=i-1;j>=0;j--){
            if(x[i]-x[j]>rmax)
                break; 
            
            double dy,koef;
           // if(y)
            dy=(y[i]-y[j]);
            
            
            r=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
         //  r=sqrt(r);
            if(r>rmax*rmax)
                continue;
            //            r=r*r;
           // a=atan2(y[i]-y[j],x[i]-x[j]);
            
            koef=q[i]*q[j]/r;//(x[i]-x[j]);
            k+=fabs(dy)/(x[i]-x[j])*koef;
            v+=atan2(dy,x[i]-x[j])*koef;
            d+=koef;
        }        
    }    
    
    
    res.k=k/d;
    res.v=v/d;
    return res;
}


void  touchInt(double d,double&k,double&v){
    double freqs[10];
    double amps[10];
    double ph[10];
    freqs[0]=1;
    freqs[1]=1*d;
    amps[0]=1;
    amps[1]=1;
    ph[0]=0.3;
    ph[1]=0.3;
    struct speqPoint r;
    r=viewFreq(freqs,amps,ph,2,0.3,2.0001); 
    k=r.k;
    v=r.v;
}
int initTouchSpeq=0;
double  touchDk[2048][2048];
double  touchDv[2048][2048];
double maxV[2048];
double maxK[2048];
double minV[2048];
double maxA[2048];
void touchSpeq(double *freqs,double*amps,double*ks,double*vs,double* ph,int n){
    int i,j;
    
    if(!initTouchSpeq){
        initTouchSpeq=1;
        fprintf(stderr,"start initTouchSpeq whis %d freqs\n",n);
        fflush(stderr);
        FILE*f;
        f=fopen("TouchSpeq.txt","r");
        if(f==NULL){
            f=fopen("TouchSpeq.txt","w");
            for(i=0;i<n;i++){
                fprintf(stderr,".");
            //    fflush(stderr);
                maxAmps[i]=0;
                maxV[i]=0.1;
                minV[i]=-0.1;
                maxA[i]=0;
                if(freqs[i]<0.00000001)
                    continue;
                for(j=i;j<n && freqs[j]/freqs[i]<=2.0001;j++){
                    touchInt(freqs[j]/freqs[i],touchDk[i][j],touchDv[i][j]);
                    fprintf(f,"%lf ",touchDk[i][j]);
                    fprintf(f,"%lf\n",touchDv[i][j]);
                    
                }
        
            }       
            fclose(f);
        }else{
            for(i=0;i<n;i++){
                fprintf(stderr,".");
                //fflush(stderr);
                maxAmps[i]=0;
                maxV[i]=0.1;
                minV[i]=-0.1;
                maxA[i]=0;
                if(freqs[i]<0.00000001)
                    continue;
                for(j=i;j<n && freqs[j]/freqs[i]<=2.0001;j++){
                  //  touchInt(freqs[j]/freqs[i],touchDk[i][j],touchDv[i][j]);
                    fscanf(f,"%lf",&(touchDk[i][j]));
                    fscanf(f,"%lf",&(touchDv[i][j]));
                    
                }
        
            }       
        
            fclose(f);
        
        }
    
    }
   // fprintf(stderr,"initTouchSpeq!\n");
   // fflush(stderr);
    double vp,vm,k;
    for(i=0;i<n;i++){
        maxAmps[i]=0.9999*maxAmps[i];
        maxAmps[i]=0.9999*maxAmps[i];
  //      maxK[i]=0.9999*maxK[i];
//        maxV[i]=0.9999*maxV[i];
    //    minV[i]=0.9999*minV[i];
                
        if(amps[i]>maxAmps[i])
            maxAmps[i]=amps[i];            
    }
    //fprintf(stderr,"maxAmps!\n");
    //fflush(stderr);

    for(i=0;i<n;i++){
       if(freqs[i]<0.00000001)
            continue;
        vp=0;
        vm=0;
        k=0;
  //      fprintf(stderr,"tauch loop %d!\n",i);
//        fflush(stderr);

        for(j=i;j<n && freqs[j]/freqs[i]<=2.0001;j++){
            if(touchDv[i][j]>0)
                vp+=touchDv[i][j]*amps[j]/maxAmps[j];
            else
               vm+=touchDv[i][j]*amps[j]/maxAmps[j];

            k+=touchDk[i][j]*amps[j]/maxAmps[j];
        }
        if(vp>maxV[i]){
            maxV[i]=vp;
        }
        if(vm<minV[i]){
            minV[i]=vm;
        }
        if(k>maxK[i]){
            maxK[i]=k;
        }
        ks[i]=k/maxK[i];

//        if(v>0)
        vs[i]=0.5+vp/maxV[i]/2. - vm/minV[i]/2;
  //      else{
    //        vs[i]=0.5-v/minV[i]/2.;
//        }
    }       
    touch_freqs=freqs;
    touch_amps=amps;
    touch_vs=vs;
    touch_ks=ks;
    touch_ph=ph;
    
    touch_n=n;
}

double specX[1000];
double specY[1000];
double specZ[1000];
struct rgb specC[1000];

void drawSpec(GLuint tex,double r,double a1,double a2,double fov,double pwks,double minfreq,double maxfreq,double pwksr,double showType){
    //fprintf(stderr,"start showIrraFraq\n");
    showIrraFraq(tex);
    return;
    
    
    
    
    
    
    
    
    
    int i;
    double cx,cy,cz;
    double hx,hy,hz;
    double *freqs;
    double*amps;
    double*ks;
    double*vs;
    
    
    
    freqs=touch_freqs;
    amps=touch_amps;
    ks=touch_ks;
    vs=touch_ks;
    int n=touch_n;
    cx=r*cos(a1);
    cy=r*sin(a1)*cos(a2);
    cz=r*sin(a1)*sin(a2);
    glDisable(GL_TEXTURE_2D);
    

    hx=r*cos(a1+M_PI/2);
    hy=r*sin(a1+M_PI/2)*cos(a2+M_PI);
    hz=r*sin(a1+M_PI/2)*sin(a2+M_PI);

    
//    saveGlScreen();
 //   glBindTexture(GL_TEXTURE_2D, tmpt);
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov,(double)GLW/GLH,0.1,1000);

  glClearColor(0,0,0,1);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
//  camz=cz;
//  camx=cx;
//  camy=cy;
 // platesN=0;
  gluLookAt(cx,cy,cz ,0,0,0, hx,hy,hz);
  //glDisable(GL_BLEND);
 
  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPointSize(2.0);
//  glBegin(GL_LINES);

  double maxfr;
        struct rgb c;

  maxfr=log(freqs[n-1])/log(2.);
 /*       c.r=255;
        c.b=0;
        c.g=255;
        c.o=255;
        glColor4ubv((const GLubyte*)&c);
        glVertex3f (-0.1,-0.1,-0.1);
        c.r=255;
        c.b=255;
        c.g=0;
        c.o=255;
        glColor4ubv((const GLubyte*)&c);
        glVertex3f (0.1,0.1,0.1);
  */
  double allv=0;
  for(i=0;i<n;i++){
    allv+=vs[i];
  }
  double curv=0;
  int ii=0;
  int prev=0;
  double nx,ny,llx,lly;
  double x,y;
  x=-1000;
  y=0;
  llx=-1000;lly=-10;
  if(showType<0.5){
     glBegin(GL_LINE_STRIP);

      for(i=0;i<n;i++){
            double z,mr;
            double fr,alpha;
            double warm,grbl;
            if(freqs[i]<0.00001){
                specX[i]=-100000;
                continue;
            }
            fr=log(freqs[i])/log(2.);///maxfr;
            double fff;
            fff=fr/maxfr;
            if(fff< minfreq || fff>maxfreq){
                  specX[i]=-100000;
           
                continue;
            }
            alpha=fr;
            while(alpha>1.)
                alpha-=1.;
            alpha*=2*M_PI;
           
            
            fr=(fr/maxfr)-0.8;
            z=fr;//(vs[i]-0.5)/10;//curv/allv-0.5;
            z=z*3;
            mr=1-pow(ks[i],pwksr);
           // x=cos(alpha)*mr;
           // y=sin(alpha)*mr;
            ny=vs[i]*3;
            nx=(ks[i]-amps[i]/maxAmps[i])*3;
            if(x>-500){
               y=(y*i+ny)/(i+1);
               x=(x*i+nx)/(i+1);
            }else{
                if(llx>-500){
                    x=(llx*999+nx)/1000;
                    y=(lly*999+ny)/1000;
                }else{
                    x=nx;
                    y=ny;
                
                }
                llx=x;
                lly=y;
                
            }
            warm=1-pow(ks[i],pwks);
            curv+=vs[i];
            grbl=vs[i];
            c.r=255*(1-grbl)*(1-warm);//;BLUE!!
            c.b=255*warm;////RED!!!
            c.g=255*(grbl)*(1-warm);
            if(correctColorFlag){
                c=rgbCorrector(c);
            }
            c.o=255*log(1+amps[i]/maxAmps[i])/log(2.);
//            c.o=255*amps[i]/maxAmps[i];
    
//            if(prev){
                glColor4ubv((const GLubyte*)&c);
                glVertex3f (x,y,z);
  //          }
    
            specC[i]=c;
            specX[i]=x;
            specY[i]=y;
            specZ[i]=z;
            while(0&& freqs[ii]*2<freqs[i]){
                if(specX[ii]>-1000){
                    glColor4ubv((const GLubyte*)&c);
                    glVertex3f (x,y,z);
             
                   glColor4ubv((const GLubyte*)&specC[ii]);
                   glVertex3f (specX[ii],specY[ii],specZ[ii]);
    
                }
                ii++;
            
            }
        //    glColor4ubv((const GLubyte*)&c);
      //  glVertex3f (x,y,z);
                prev=1;
            
        
/*        fprintf(stderr,"(%lf ",x);
        fprintf(stderr,"%lf ",y);
        fprintf(stderr,"%lf)",z);
        fprintf(stderr,"%d ",c.r);
        fprintf(stderr,"%d ",c.g);
        fprintf(stderr,"%d ",c.b);
        fprintf(stderr,"%d\n",c.o);
*/
        }   
        glEnd();
    }else{
        double ax,ay,bx,by,cy,cx;;
        ax=-100;
        bx=-100;
        cx=-100;
     glBegin(GL_LINES);

      for(i=0;i<n;i++){
            double x,y,z,mr;
            double fr,alpha;
            double warm,grbl;
            if(freqs[i]<0.00001){
                specX[i]=-100000;
                continue;
            }
            fr=log(freqs[i])/log(2.);///maxfr;
            double fff;
            fff=fr/maxfr;
            if(fff< minfreq || fff>maxfreq){
                  specX[i]=-100000;
           
                continue;
            }
            z=(fr/maxfr)-0.8;
            if(ax>-50){
                glColor3f(1,0,0);

                glVertex3f (ax,ay,0);
                glVertex3f (fr*4,ks[i],0);
            }
            ax=fr*4;
            ay=ks[i];
            if(bx>-50){

                glVertex3f (bx,by,0);
                glVertex3f (fr*4,ks[i]+1.5,0);
            }
            bx=fr*4;

            by=ks[i];
            if(cx>-50){
                glVertex3f (cx,cy,0);
                glVertex3f (fr*4,amps[i]/maxAmps[i]+3,0);
            }
            cx=fr*4;
            cy=amps[i]/maxAmps[i]+3;
            
        }   
        glEnd();
    
    }
    saveGlScreen2Tex(tex);
    glPopMatrix();
    glPopAttrib();

}
