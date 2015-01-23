#include<SDL/SDL.h>
#include"graphutil.cpp"
#include"colors.cpp"
extern double wind;

void  inline drawLines(SDL_Surface* sc,int x1,int y1,int x2,int y2,Uint32 pifColor, int repeat);
void  inline drawColoredLinesSeq2(SDL_Surface* sc,int x1,int y1,int x2,int y2, int repeat);
void  inline drawColoredLinesSeq2(SDL_Surface* sc,int x1,int y1,int x2,int y2, int repeat,int curDeep);
void  inline orDrawColoredLinesSeq2(SDL_Surface* sc,int x1,int y1,int x2,int y2, int repeat);
void  inline orDrawColoredLinesSeq2(SDL_Surface* sc,int x1,int y1,int x2,int y2, int repeat,int curDeep);
int axb[2048*2048];
int SQRT[1024*1024];
#include"star.cpp"
SDL_Surface* sc;
#include"fraqVertex.cpp"
double pifSoft=0;
double pifWight=0;
int pifColor=0;
int naked=0;
double pifagorWind;
double cospifagorWind;
extern int pifPosition;

int staticcolor=1;
double sound_rx=0;
double sound_ry=0;
#include"quickspeq.cpp"
extern struct qs qsAll;


#define PIFEPS 1.
#define NUMBER(a)   ((((a)+512)/1024))
//#define TOFIXED(a)  



int initPifFlag=0;


inline int TOFIXED(double a){
    return     (int)(a*1024.0);


}

Uint64 a,b;
int sig;

inline int MULT(int aa,int bb){
    
    
    return (aa*bb/1024);/*
    if(aa>0&&bb>0){
        sig=1;
        a=aa;
        b=bb;
    }else if(aa<0&&bb<0){
        sig=1;
        a=-aa;
        b=-bb;
    }else
    if(aa<0&&bb>0){
        sig=-1;
        a=-aa;
        b=bb;
    
    }else{
        sig=-1;
        a=aa;
        b=-bb;
    }
        return     sig*((int)(a*b/1024));
        */
//
}

#define INF 1e100;
double pMaxx=-INF;
double pMaxy=-INF;
double pMinx=INF;
double pMiny=INF;
double pscale;
//#define max(a,b) ((a)>(b))?(a):(b)
double MAXPIFTIMES=1000000.;
double piftimes=0.;
int sh,sw;
double maxl=1000.0;

void initPifTables(double w,double h){
    int i,j;
    /*double lpscale;
    lpscale=pscale;
    if(pMaxx>pMinx && pMiny<pMaxy){
        pscale=min(w/(pMaxx-pMinx),h/(pMaxy-pMiny))*2;        
    }else
        pscale=1;
   pscale=pscale*0.6+lpscale*0.4;
  */
  
   sh=h-1;
   sw=w-1;
   
 
    
    
    if(initPifFlag)
        return;
    
    for(i=0;i<2048;i++)
        for(j=0;j<2048;j++){
            axb[i+j*2048]=(i-725)*(j)/725;
        }
    for(i=0;i<1024*1024;i++){
        SQRT[i]=sqrt(i);
    }
    initPifFlag=1;
   
}
int cosAngleRepeat,sinAngleRepeat;
int sccx,sccy;


int ncircles=0;
int maxcircles=0;
char circleSeqPresent[360];

void inline circles(SDL_Surface* sc,int x,int y,int r,Uint32 Color,int repeat){
    int nx,ny;

    
    int i,j;
    if(circleSeqPresent[0])
    for(j=0;j<=ncircles;j++){
        circle(sc,x,y,r-r*j/(maxcircles+1),pifColor);
    
    }
    
    x=x-sccx;
    y=y-sccy;

    for(i=2;i<repeat;i++){
        nx=x*cosAngleRepeat/1024 - y*sinAngleRepeat/1024;
        ny=x*sinAngleRepeat/1024 + y*cosAngleRepeat/1024;  
        x=nx;
        y=ny;
        if(circleSeqPresent[i-1])
            for(j=0;j<=ncircles;j++)
                circle(sc,x+sccx,y+sccy,r-r*j/(maxcircles+1),pifColor);
     }
}
int numbers[20];
void zeroNumbers(){
    for(int i=0;i<20;i++){
        numbers[20]=0;
    }
}
int getNumberFromDeep(int deep){
    if(deep<20)
        return numbers[deep]++;
    return 0;
}

double presentEdge=0.4;
extern double fraqFilter;

int fraqElPresent(int n,int d){
    presentEdge=fraqFilter;
    if(presentEdge<0.01)
        return circleSeqPresent[n];
    double a;
    n=getNumberFromDeep(d);
    a=getQs(&qsAll,n % qsAll.tones,d);
    if(a>presentEdge)
        return 1;
    return 0;

}


void inline circlesColorSeq(SDL_Surface* sc,int x,int y,int r,int repeat,int deep,int nTree,int parity){
    int nx,ny;

    
    int i;
    int j;
    int n;
    struct fraqVertex *p;
   // int x,y;
   // x=cx;
   // y=cy;
    transformXY(x,y);    
   // cx=x;
   // cy=y;
    p=rePlace(0,nTree,parity,x,y,pifSoft,pifWight);
    x=p->x;
    y=p->y;
    
    
    
    
    
    n=0;
    if(fraqElPresent(n,deep))
        for(j=0;j<=ncircles;j++)
            circleColorSeq(sc,x,y,r-r*j/(maxcircles+1));
      
    
    x=x-sccx;
    y=y-sccy;

    for(i=2;i<repeat;i++){
        nx=x*cosAngleRepeat/1024 - y*sinAngleRepeat/1024;
        ny=x*sinAngleRepeat/1024 + y*cosAngleRepeat/1024;  
        x=nx;
        y=ny;
       // n=getNumberFromDeep(deep);
        if(fraqElPresent(i-1,deep))
            for(j=0;j<=ncircles;j++)
                circleColorSeq(sc,x+sccx,y+sccy,r-r*j/(maxcircles+1));


     }
}

void  inline drawLines(SDL_Surface* sc,int x1,int y1,int x2,int y2,Uint32 pifColor, int repeat){
    int nx1,ny1,nx2,ny2;

    
    int i;
    if(circleSeqPresent[0])
        drawLine(sc,x1,y1,x2,y2,pifColor);
      
    
    x1=x1-sccx;
    x2=x2-sccx;
    y1=y1-sccy;
    y2=y2-sccy;

 //   printf("repeat from lies:%d\n",repeat);
   // return;
    for(i=2;i<repeat;i++){
        nx1=x1*cosAngleRepeat/1024 - y1*sinAngleRepeat/1024;
        nx2=x2*cosAngleRepeat/1024 - y2*sinAngleRepeat/1024;    
        ny1=x1*sinAngleRepeat/1024 + y1*cosAngleRepeat/1024;
        ny2=x2*sinAngleRepeat/1024 + y2*cosAngleRepeat/1024;  
        x1=nx1;
        x2=nx2;
        y2=ny2;
        y1=ny1;
        if(circleSeqPresent[i-1])
            drawLine(sc,x1+sccx,y1+sccy,x2+sccx,y2+sccy,pifColor);
    }
       
}

void  inline drawColoredLinesSeq2(SDL_Surface* sc,int x1,int y1,int x2,int y2, int repeat,int curDeep){
    int nx1,ny1,nx2,ny2;
    
    int i;
     int n;
    n=0;//getNumberFromDeep(curDeep);
//   if((x1<0&&x2<0)||(x1>sc->w&&x2>sc->w)||(y1<0&&y2<0)||(y1>sc->h&&y2>sc->h))
  //     return;
    if(fraqElPresent(n,curDeep))   
        drawColoredLineSeq2(sc,x1,y1,x2,y2);   
    x1=x1-sccx;
    x2=x2-sccx;
    y1=y1-sccy;
    y2=y2-sccy;
    
    for(i=2;i<repeat;i++){

        nx1=x1*cosAngleRepeat/1024 - y1*sinAngleRepeat/1024;
        nx2=x2*cosAngleRepeat/1024 - y2*sinAngleRepeat/1024;    
        
        
        ny1=x1*sinAngleRepeat/1024 + y1*cosAngleRepeat/1024;
        ny2=x2*sinAngleRepeat/1024 + y2*cosAngleRepeat/1024;    
        
        x1=nx1;
        x2=nx2;
        y2=ny2;
        y1=ny1;
         int n;
        //  n=getNumberFromDeep(curDeep);
    
        if( fraqElPresent(i-1,curDeep) )
            drawColoredLineSeq2(sc,x1+sccx,y1+sccy,x2+sccx,y2+sccy);
    }
       
}
void  inline orDrawColoredLinesSeq2(SDL_Surface* sc,int x1,int y1,int x2,int y2, int repeat,int curDeep){
    int nx1,ny1,nx2,ny2;
    
    int i;
     int n;
    n=0;//getNumberFromDeep(curDeep);
//   if((x1<0&&x2<0)||(x1>sc->w&&x2>sc->w)||(y1<0&&y2<0)||(y1>sc->h&&y2>sc->h))
  //     return;
    if(fraqElPresent(n,curDeep))   
        orDrawColoredLineSeq2(sc,x1,y1,x2,y2);   
    x1=x1-sccx;
    x2=x2-sccx;
    y1=y1-sccy;
    y2=y2-sccy;
    
    for(i=2;i<repeat;i++){

        nx1=x1*cosAngleRepeat/1024 - y1*sinAngleRepeat/1024;
        nx2=x2*cosAngleRepeat/1024 - y2*sinAngleRepeat/1024;    
        
        
        ny1=x1*sinAngleRepeat/1024 + y1*cosAngleRepeat/1024;
        ny2=x2*sinAngleRepeat/1024 + y2*cosAngleRepeat/1024;    
        
        x1=nx1;
        x2=nx2;
        y2=ny2;
        y1=ny1;
         int n;
        //  n=getNumberFromDeep(curDeep);
    
        if( fraqElPresent(i-1,curDeep) )
            orDrawColoredLineSeq2(sc,x1+sccx,y1+sccy,x2+sccx,y2+sccy);
    }
       
}

void  inline drawColoredLinesSeq2(SDL_Surface* sc,int x1,int y1,int x2,int y2, int repeat){
    drawColoredLinesSeq2(sc,x1,y1,x2,y2,repeat,0);
}
void  inline orDrawColoredLinesSeq2(SDL_Surface* sc,int x1,int y1,int x2,int y2, int repeat){
    orDrawColoredLinesSeq2(sc,x1,y1,x2,y2,repeat,0);
}

double rkoef=1.;
int rkoefInt=1.;

int minDeep=0;
int  colorDeep=0;
void zeroSeqno3();

void QPif(double x1,double y1,double x2,double y2,int deep,int parity,int repeat,int curDeep,int nTree){
    double x,xx,yy,xx1,xx2,yy1,yy2;
    double y;
    double a,l,ll1,ll2;
    
    if((fabs(x1-x2)<PIFEPS && fabs(y1-y2)<PIFEPS) || deep==0)
        return;
//    colorDeep=curDeep;
    prepareSeqNo2(curDeep);
  /*  if(x1<pMinx)
        pMinx=x1;
    if(x2<pMinx)
        pMinx=x2;
    if(x1>pMaxx)
        pMaxx=x1;
    if(x2>pMaxx)
        pMaxx=x2;
    if(y1<pMiny)
        pMiny=y1;
    if(y2<pMiny)
        pMiny=y2;
    if(y1>pMaxy)
        pMaxy=y1;
    if(y2>pMaxy)
        pMaxy=y2;
    */    
    x=x2-x1;
    y=y2-y1;
    
   // a=ATAN2[NUMBER(y)+256][NUMBER(x)+256];
     a=atan2(y,x);
     l=sqrt((x*x)+(y*y));
    ll1=l*cospifagorWind;
    x=cos(a -M_PI/2)*l;
    y=sin(a -M_PI/2)*l;
    
    
    
    xx1=x1+x;
    yy1=y1+y;
    xx2=x2+x;
    yy2=y2+y;
    
  //  pifagorWind=M_PI/4;
    xx=cos(a-pifagorWind)*ll1;
    yy=sin(a-pifagorWind)*ll1;
    
    if(deep<=minDeep){
        if(naked==0){
//        printf("naked0\n");         

            if(l<maxl){
                if(staticcolor){  
                    drawLines(sc,(x2),(y2),(x2+x),(y2+y),pifColor,repeat);
                    drawLines(sc,(x1),(y1),(x1+x),(y1+y),pifColor,repeat);
                    drawLines(sc,(x1+x),(y1+y),(x2+x),(y2+y),pifColor,repeat);
                    drawLines(sc,(x1),(y1),(x2),(y2),pifColor,repeat);
                    if(parity){
                        drawLines(sc,sw-(x2),sh-(y2),sw-(x2+x),sh-(y2+y),pifColor,repeat);
                        drawLines(sc,sw-(x1),sh-(y1),sw-(x1+x),sh-(y1+y),pifColor,repeat);
                        drawLines(sc,sw-(x1+x),sh-(y1+y),sw-(x2+x),sh-(y2+y),pifColor,repeat);
                        drawLines(sc,sw-(x1),sh-(y1),sw-(x2),sh-(y2),pifColor,repeat);
                    }
    
                }else{
                    drawColoredLinesSeq2(sc,(x2),(y2),(x2+x),(y2+y),repeat,curDeep);
                    drawColoredLinesSeq2(sc,(x1),(y1),(x1+x),(y1+y),repeat,curDeep);
                    drawColoredLinesSeq2(sc,(x1+x),(y1+y),(x2+x),(y2+y),repeat,curDeep);
                    drawColoredLinesSeq2(sc,(x1),(y1),(x2),(y2),repeat,curDeep);
        
                    if(parity){
                        drawColoredLinesSeq2(sc,sw-(x2),sh-(y2),sw-(x2+x),sh-(y2+y),repeat,curDeep);
                        drawColoredLinesSeq2(sc,sw-(x1),sh-(y1),sw-(x1+x),sh-(y1+y),repeat,curDeep);
                        drawColoredLinesSeq2(sc,sw-(x1+x),sh-(y1+y),sw-(x2+x),sh-(y2+y),repeat,curDeep);
                        drawColoredLinesSeq2(sc,sw-(x1),sh-(y1),sw-(x2),sh-(y2),repeat,curDeep);
                    }
    
          
                }
            }
        }else if(naked==1){
                    double tl,tx,ty;
                    tx=(x1+x2)/2  -  (x1+x+x2+x)/2;
                    ty=(y1+y2)/2  - (y1+y+y2+y)/2 ;
//            printf("naked1\n");         
                     
                     if(tx*tx+ty*ty<maxl*maxl){
                        if(!staticcolor){
                             drawColoredLinesSeq2(sc,(x1+x2)/2,(y1+y2)/2,(x1+x+x2+x)/2,(y1+y+y2+y)/2,repeat,curDeep);
                             drawColoredLinesSeq2(sc,(x1+x+x2+x)/2,(y1+y+y2+y)/2,(xx1+xx1+xx)/2,(yy1+yy1+yy)/2,repeat,curDeep);
                             drawColoredLinesSeq2(sc,(x1+x+x2+x)/2,(y1+y+y2+y)/2,(xx1+xx+xx2)/2,(yy1+yy+yy2)/2,repeat,curDeep);
                     
                     
                            if(parity){
                                 drawColoredLinesSeq2(sc,sw-(x1+x2)/2,sh-(y1+y2)/2,sw-(x1+x+x2+x)/2,sh-(y1+y+y2+y)/2,repeat,curDeep);
                                 drawColoredLinesSeq2(sc,sw-(x1+x+x2+x)/2,sh-(y1+y+y2+y)/2,sw-(xx1+xx1+xx)/2,sh-(yy1+yy1+yy)/2,repeat,curDeep);
                                 drawColoredLinesSeq2(sc,sw-(x1+x+x2+x)/2,sh-(y1+y+y2+y)/2,sw-(xx1+xx+xx2)/2,sh-(yy1+yy+yy2)/2,repeat,curDeep);
                            }
                        }else{
                             drawLines(sc,(x1+x2)/2,(y1+y2)/2,(x1+x+x2+x)/2,(y1+y+y2+y)/2,pifColor,repeat);
                             drawLines(sc,(x1+x+x2+x)/2,(y1+y+y2+y)/2,(xx1+xx1+xx)/2,(yy1+yy1+yy)/2,pifColor,repeat);
                             drawLines(sc,(x1+x+x2+x)/2,(y1+y+y2+y)/2,(xx1+xx+xx2)/2,(yy1+yy+yy2)/2,pifColor,repeat);
                             if(parity){
                           
                                drawLines(sc,sw-(x1+x2)/2,sh-(y1+y2)/2,sw-(x1+x+x2+x)/2,sh-(y1+y+y2+y)/2,pifColor,repeat);
                                drawLines(sc,sw-(x1+x+x2+x)/2,sh-(y1+y+y2+y)/2,sw-(xx1+xx1+xx)/2,sh-(yy1+yy1+yy)/2,pifColor,repeat);
                                drawLines(sc,sw-(x1+x+x2+x)/2,sh-(y1+y+y2+y)/2,sw-(xx1+xx+xx2)/2,sh-(yy1+yy+yy2)/2,pifColor,repeat);
                            }                  
                                           
                        }
                     
                     }             
//                     drawColoredLine(sc,(x1+x+x2+x)/2,(y1),(x1+x),(y1+y),colorSeq2);
                   
                   
        //            drawColoredLine(sc,(x1),(y1),(x1+x),(y1+y),colorSeq2);
          //          drawColoredLine(sc,(x1+x),(y1+y),(x2+x),(y2+y),colorSeq2);
            //        drawColoredLine(sc,(x1),(y1),(x2),(y2),colorSeq2);
        
        
        
        }else if(naked==2) {
        //    printf("naked2\n");
                double r;
                r=sqrt(x*x+y*y)/2 * rkoef;
                if(staticcolor){  
                    circles(sc,(x1+x2+x1+x+x2+x)/4,(y1+y2+y1+y+y2+y)/4,r,pifColor,repeat);
                    if(parity){
                        circles(sc,sw-(x1+x2+x1+x+x2+x)/4,sh-(y1+y2+y1+y+y2+y)/4,r,pifColor,repeat);
                    }
    
                }else{
                    circlesColorSeq(sc,(x1+x2+x1+x+x2+x)/4,(y1+y2+y1+y+y2+y)/4,r,repeat,curDeep,nTree,0);
                    if(parity){
                        circlesColorSeq(sc,sw-(x1+x2+x1+x+x2+x)/4,sh-(y1+y2+y1+y+y2+y)/4,r,repeat,curDeep,nTree,1);
                    }
                }
        
        }else {
        //    printf("naked3\n");
              int sq;
              sq=x*x+y*y;
//               double r;
  //             r=sqrt(x*x+y*y)/2 * rkoef;
    
              if(sq<1024*1024 && sq>=0){
                 sq=rkoefInt*SQRT[sq]/2/1024;   
                  if(staticcolor){  
                        drawStars(sc,&star1,(x1+x2+x1+x+x2+x)/4,(y1+y2+y1+y+y2+y)/4,sq,pifColor,repeat);
                        if(parity){
                            drawStars(sc,&star1,sw-(x1+x2+x1+x+x2+x)/4,sh-(y1+y2+y1+y+y2+y)/4,sq,pifColor,repeat);
                        }
    
                    }else{

                        drawStarsColorSeq(sc,&star1,(x1+x2+x1+x+x2+x)/4,(y1+y2+y1+y+y2+y)/4,sq,repeat,curDeep,nTree,0);
                        if(parity){
                            drawStarsColorSeq(sc,&star1,sw-(x1+x2+x1+x+x2+x)/4,sh-(y1+y2+y1+y+y2+y)/4,sq,repeat,curDeep,nTree,1);
                        }
                    }
                }
        
        }
    }
    //SDL_Flip( sc ); 
    //sleep(1);
    
    QPif(xx1,yy1,xx1+xx,yy1+yy,deep-1,parity,repeat,curDeep+1,nTree*2);
    
    
   // x=cos(M_PI-(a-pifagorWind))*ll2;
   // y=sin(M_PI-(a-pifagorWind))*ll2;
    QPif(xx1+xx,yy1+yy,xx2,yy2,deep-1,parity,repeat,curDeep+1,nTree*2+1);
  // QPif(x2+y,y2-x,x2,y2,deep-1);    
    
    //(x1,y1)
    //(x2,y1)
    
   // drawSqr(sc,x1,y1,x2,y2,pifColor);
    
//    printf("%d %d %d %d\n",(int)x1,(int)y1,(int)x2,(int)y2);

}
double rational(double r,int*ra,int*rb){
       int a,b;
       double rr,ans;
       //char s[128]="Next Rational: 1\n";
       ans=5.;
       for(b=1;b<60;b++){
        for(a=0;a<60 ;a++){
            rr=((double)a)/b;
            if(fabs(r-rr)>0.000001 && rr>r && rr<ans){
                ans=rr;
                *ra=a;
                *rb=b;
   //             sprintf(s,"Next Rational: %d/%d\n",a,b);
            }
        }
       
       }
     //  printf("%s",s);
    return ans;
}



/*
unsigned int _2(unsigned int a){
    unsigned int r;
    r=1;
    while(a){
        r=r*2;
        a--;
    }
    return r;
}

*/
/*
double rational(double r,int*ra,int *rb){
       int a,b;
       double rr,ans;
       //char s[128]="Next Rational: 1\n";
       ans=-500.;
       for(b=1;b<10;b++){
        for(a=0; a<b;a++){
            rr=((double)a)/b;
            if( fabs((rr-r)) <fabs((ans-r))){
                ans=rr;
                *ra=a;
                *rb=b;
                //sprintf(s,"Next Rational: %d/%d\n",a,b);
            }
        }
       
       }
      //  printf("%s",s);
    return ans;
}
*/

#include"symmetry.cpp"

int piflparity=-1;
int piflrepeat=-1;



double pifAngle=0;
#include"colors.cpp"
void drawPifagor(SDL_Surface* screen,double *koef){
int deep=koef[0];
int n=koef[1];
int color=koef[2];
double dwind=koef[3];
double dpscale=koef[4];
double dpangle=koef[5];
double colorSpeedr=koef[6];
double colorSpeedg=koef[7];
double colorSpeedb=koef[8];
int repeat=koef[9];
int parity=koef[10];
double starValue=koef[11];
double starAngle=koef[12];
int starn=koef[13];
double spiral=koef[16];
double mega=koef[17];
    zeroNumbers();
    setSpiral(spiral);
    setMega(mega);
    


//double xshift=koef[14];
//double yshift=starAngle=koef[15];
  //  printf("deep:%d\nscale %f\n",deep,dpscale);
//    yshift=yshift*dpscale;
//    xshift=xshift*dpscale;
    rkoef=koef[14];
   
    
    
    rkoefInt=rkoef*1024;
    double circleSeq;
    circleSeq=koef[8];
    double circleSeqSymm;
    circleSeqSymm=koef[7];
    
    if(circleSeq>0.0000001){
        //unsigned int bit;
       // int len,b,c,i;
        if(circleSeq<0.)
            circleSeq=0.;
        if(circleSeq>1.)
            circleSeq=1.;
        if(circleSeqSymm<0.)
            circleSeqSymm=0.;
        if(circleSeqSymm>1.)
            circleSeqSymm=1.;
        gcs(circleSeqPresent,circleSeqSymm,circleSeq,repeat);

       
       // generateCircleSeq(circleSeqPresent,circleSeq,repeat);
        
       
       // b=((unsigned int)circleSeq/*_2(repeat)*/);
      //  bit=1;
      //  c=grayencode(b);
//        printf("%d %d :",b,c);
        
     //   for(i=0;i<16;i++,bit=bit*2){
     //       if(b&bit){
      //          len=i;
       //     }
  //          printf("(%d,%d)",b&bit,c&bit);
      //  }
    //    printf("\n");
      //  if(len!=0){
       //     for(i=0,bit=1;i<repeat;i++,bit=bit*2){
        //        if(i%len==0){
         //           bit=1;
          //      }
           //     if(c&bit)
         //          circleSeqPresent[i]=1;
            //    else
             //      circleSeqPresent[i]=0;
           // }
      //   }else{
       //     for(i=0,bit=1;i<repeat;i++,bit=bit*2){
        //           circleSeqPresent[i]=1;
         //   }         
       //  }
    
    }else{
        for(int i=0;i<repeat;i++){
            circleSeqPresent[i]=1;
        }
    
    }
    
//    printf("koef 14:%lf(%lf)(%lf)\n",rkoef,zeros[14],controllKoef[14*KOEFNUM+0]);
    
    sc=screen;
    pifColor=WHITE;
    naked=n;
   initPifTables(sc->w,sc->h);
  
  
  
   if(naked == 3){
      if(starn<3)
        naked=2;
      else
        buildStar(&star1,starn,starn*starValue/2.+0.5,starAngle);
   
   }
   if(naked == 2){
     ncircles=ceil((starn-3)*starValue);
     maxcircles=(starn-3);
   
   
   }
   
   // printf("n:%d\n",naked);
//    if(color==0){
    //    initColorSeq2(colorSpeedr,colorSpeedg,colorSpeedb);    
  //  }
    parity=parity&1;
    if(parity!=piflparity || repeat!=piflrepeat){
        piflparity=parity;
        piflrepeat=repeat;
        zeroFraqVertex(); 
    }
    staticcolor=color;
    //printf("Pifa:%lf\n",wind);
    //fflush(stdout);
    //initColorSeq1();
    wind=dwind;
    while(wind>M_PI*2)
        wind-=M_PI*2;
    while(wind<0.0)
        wind+=M_PI*2;
    //    printf("staticcolor: %d\n",staticcolor);
   // if(wind>M_PI&&wind<M_PI+M_PI/100)
     //   return;    
   //if(wind<M_PI&&wind>M_PI-M_PI/100)
     //   return; 
    //wind=-9*M_PI/20;
    
    maxl=sc->w*100./1366.;
    
    
    
    
    pscale=dpscale;//ascell(1,piftimes)/10.0 +sound_ry; 
//    double dt;
  //  dt=dt+1;//=myTimer()/((double)tekeFps());
    
    //piftimes+=dt*dpscale;
   // if(fabs(piftimes)>(MAXPIFTIMES))
    //    piftimes=0.;
    
    pifagorWind=wind;//ascell(2,wind)+sound_rx;
    //wind+=dt*dwind;
    
    pifAngle=dpangle;
    
    //if(fabs(pifAngle)>MAXPIFTIMES)
    //    pifAngle=0.;

   
    
    
    seqno2=0;
    zeroSeqno3();
   // if(!(rand()%500)){
    //    naked=!naked;
    //}
    cospifagorWind=cos(pifagorWind);
    
    double x1,y1,x2,y2;
   // for(int i=0;i<repeat+1-parity;i++){
        double angle;
        angle=pifAngle;//+ (2*M_PI*(1+parity))*i/repeat;
        if(pifPosition==1){//Начальное положение снизу по центру, вращается в зависимости от piFAngle вокруг центра экрана

        
            x1=sc->w/2 +((sc->w/2-(sc->w/15)*pscale) - sc->w/2)*cos(angle) + ((sc->h-1 - sc->h/2)*sin(angle));
            y1=sc->h/2 + ((sc->h-1)-sc->h/2)*cos(angle)   -  ((sc->w/2-(sc->w/15)*pscale) - sc->w/2)*sin(angle);
            x2=sc->w/2 +((sc->w/2+(sc->w/15)*pscale) - sc->w/2)*cos(angle) + ((sc->h-1 - sc->h/2)*sin(angle));
            y2=sc->h/2 + ((sc->h-1)-sc->h/2)*cos(angle)   -  ((sc->w/2+(sc->w/15)*pscale) - sc->w/2)*sin(angle);
        }else{// в центре экрана, врашается.
            maxl=100000000.;
           
            x1=sc->w/2 -(sc->w/30)*pscale*cos(angle);
            y1=sc->h/2 -(sc->w/30)*pscale*sin(angle);;
            x2=sc->w/2 +(sc->w/30)*pscale*cos(angle);
            y2=sc->h/2 +(sc->w/30)*pscale*sin(angle);
    
        }
   // pifAngle+=;
   
        cosAngleRepeat=1024*cos((2*M_PI*(1+parity))/repeat);
        sinAngleRepeat=1024*sin((2*M_PI*(1+parity))/repeat);
        sccx=screen->w/2;
        sccy=screen->h/2;

//    printf("naked: %d\n",naked);
    
        
        minDeep=koef[15];
        minDeep=deep-minDeep;
        
        
        calcStarsNumber(deep,parity,repeat+1-parity);       
        
        QPif(x1,y1,x2,y2,deep,parity,repeat+1-parity,0,1);
   // }
    //colorSeq2Len=seqno2;
  //  printf("%lld\n",colorSeq2Len);
//    QPif((sc->w/2-(sc->w/15)*pscale,(sc->h-1),(sc->w/2+(sc->w/15)*pscale),(sc->h-1),deep);
    //QPif(  sc->w-1,  sc->h/2-(sc->w/15)*pscale,sc->w-1,sc->h+(sc->h/15)*pscale,deep);

   // QPif((sc->w/2+(sc->w/15)*pscale),0,(sc->w/2-(sc->w/15)*pscale),0,deep);
    //QPif(0,sc->h/2+(sc->h/15)*pscale,0,sc->h-(sc->h/15)*pscale,deep);
   

    //printf("wind:%d deg\n",(int)(wind*180./M_PI));   
    setSpiral(0);
    setMega(0);


}
