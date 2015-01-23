#include<SDL/SDL.h>
#include<math.h>
#include"graphutil.cpp"
#define MAXSTARN 360
//void  inline drawLines(SDL_Surface* sc,int x1,int y1,int x2,int y2,Uint32 pifColor, int repeat);
void  inline drawLines(SDL_Surface* sc,int x1,int y1,int x2,int y2,Uint32 pifColor, int repeat);

void  inline drawColoredLinesSeq2(SDL_Surface* sc,int x1,int y1,int x2,int y2, int repeat);
void  inline drawColoredLinesSeq2(SDL_Surface* sc,int x1,int y1,int x2,int y2, int repeat,int curDeep);
void  inline ordrawColoredLinesSeq2(SDL_Surface* sc,int x1,int y1,int x2,int y2, int repeat);
void  inline orDrawColoredLinesSeq2(SDL_Surface* sc,int x1,int y1,int x2,int y2, int repeat,int curDeep);
int fraqElPresent(int n,int d);

extern int axb[2048*2048];

struct star{
    int x1[MAXSTARN];
    int y1[MAXSTARN];
    int x2[MAXSTARN];
    int y2[MAXSTARN];
    int n;
} star1;

char starflags[MAXSTARN];
int starx[MAXSTARN];
int stary[MAXSTARN];

int buildStar(struct star*s,int n,int m,double a){
   int i,k,done,lk;
   char *flags=starflags;
   int *x=starx;
   int *y=stary;

   double nd;
   if(n<3){
        s->n=0;
        return -1;   
   } 
   if( m<1){
    m=1;
   
   }
   if(m*2>n){
       if(n%2 == 0){
           m=n/2;
       }else{
           m=(n-1)/2;
       }
   }
   nd=n;
   for(i=0;i<n;i++){
        flags[i]=0;
        x[i]= 725 + 512*sin(a)+512*cos(a);
        y[i]= 725 + 512*cos(a)-512*sin(a);
        a=a+2.*M_PI/nd;
   }

   k=0;
   done=0;
   lk=-1;
   s->n=0;
   while(done<n){
    if(lk!=-1){
        s->x1[s->n]=x[lk];
        s->y1[s->n]=y[lk];
        s->x2[s->n]=x[k];
        s->y2[s->n]=y[k];
        s->n++;
    }
    lk=k;
    flags[k]=1;
    k+=m;
    k%=n;
    done++;
    if(flags[k]){
        s->x1[s->n]=x[lk];
        s->y1[s->n]=y[lk];
        s->x2[s->n]=x[k];
        s->y2[s->n]=y[k];
        s->n++;
        lk=-1;
        while(done<n&&flags[k]){
            k++;
            k%=n;
        }
     }
   }
   
   return 0;
}

void drawStar(SDL_Surface*screen,struct star*s,int cx,int cy,int r,Uint32 c){
    int i;
    int *x1,*y1,*y2,*x2;
    for(i=0,x1=s->x1,y1=s->y1,x2=s->x2,y2=s->y2;i<s->n;i++,x1++,y1++,x2++,y2++){
        drawLine(screen,*x1*r/1024+cx,*y1*r/1024+cy,*x2*r/1024+cx,*y2*r/1024+cy,c);
    }
}


void drawStars(SDL_Surface*screen,struct star*s,int cx,int cy,int r,Uint32 c,int repeat){
    int i;
    int *x1,*y1,*y2,*x2;
    for(i=0,x1=s->x1,y1=s->y1,x2=s->x2,y2=s->y2;i<s->n;i++,x1++,y1++,x2++,y2++){
        drawLines(screen,axb[*x1+r*2048]+cx,axb[*y1+r*2048]+cy,axb[*x2+r*2048]+cx,axb[*y2+r*2048]+cy,c,repeat);
    }
}

//                        nTree
  //                      struct fraqVertex *p;
    //                    p=rePlace(int nRep,int nTree,int par,double x,double y,double soft);
/*
void drawStarsColorSeq(SDL_Surface*screen,struct star*s,int cx,int cy,int r,int repeat,int curDeep,int nTree,int parity){
    int i;
    int *x1,*y1,*y2,*x2;
//    struct fraqVertex *p;
    
    for(i=0,x1=s->x1,y1=s->y1,x2=s->x2,y2=s->y2;i<s->n;i++,x1++,y1++,x2++,y2++){
//        p=rePlace(i,int nTree,int par,double x,double y,double soft);
        drawColoredLinesSeq2(screen,axb[*x1+r*2048]+cx,axb[*y1+r*2048]+cy,axb[*x2+r*2048]+cx,axb[*y2+r*2048]+cy,repeat,curDeep);
    }
}
*/
#include"fraqVertex.cpp"
extern double pifSoft;
extern double pifWight;
extern int putPixelMetod;
extern int cosAngleRepeat,sinAngleRepeat;
extern int sccx,sccy;

double getStarSize(int deep,int n,int nmax);
#define MAXFAQDEEP 13
int starsNumber[MAXFAQDEEP];
int starsOnLevel[MAXFAQDEEP];
extern char circleSeqPresent[360];
void calcStarsNumber(int deep,int parity,int repeat){
  int i;
  int trees;
  trees=0;
  if(parity){
    parity=2;
  }else{
    parity=1;
  }
  for(i=0;i<repeat;i++){
    if(circleSeqPresent[i])
        trees++;
  }
  int pw;
  pw=1;
  for(i=0;i<deep;i++,pw=pw*2){
    starsNumber[i]=0;
    starsOnLevel[i]=trees*parity*pw;  
  }

}

extern int drawGLZ;
extern double minDistance;
extern double maxDistance;
extern int GLLINE;
void drawStarColorSeq(SDL_Surface*screen,struct star*s,int cx,int cy,int r,int curDeep,int nTree,int parity){
    int i;
    int *x1,*y1,*y2,*x2;
    //fprintf(stderr,"drawStarColoredSeq!\n");
    if(!drawGLZ){
    
        r=r *(2*getStarSize(curDeep,starsNumber[curDeep],starsOnLevel[curDeep]));
        starsNumber[curDeep]++;
        if(GLLINE){
                for(i=0,x1=s->x1,y1=s->y1,x2=s->x2,y2=s->y2;i<s->n;i++,x1++,y1++,x2++,y2++){
                    GLColoredLineSeq2(axb[*x1+r*2048]+cx,axb[*y1+r*2048]+cy,axb[*x2+r*2048]+cx,axb[*y2+r*2048]+cy);
                }
        }else{
            if(putPixelMetod==0)
                for(i=0,x1=s->x1,y1=s->y1,x2=s->x2,y2=s->y2;i<s->n;i++,x1++,y1++,x2++,y2++){
//                    posColorLine(-1,-1,i,s->n)
                    drawColoredLineSeq2(screen,axb[*x1+r*2048]+cx,axb[*y1+r*2048]+cy,axb[*x2+r*2048]+cx,axb[*y2+r*2048]+cy);
                }
            else{
                for(i=0,x1=s->x1,y1=s->y1,x2=s->x2,y2=s->y2;i<s->n;i++,x1++,y1++,x2++,y2++){
                    orDrawColoredLineSeq2(screen,axb[*x1+r*2048]+cx,axb[*y1+r*2048]+cy,axb[*x2+r*2048]+cx,axb[*y2+r*2048]+cy);
                }
            }
        }
    }else{
        double z;
        z=-minDistance - maxDistance*getStarSize(curDeep,starsNumber[curDeep],starsOnLevel[curDeep]);
        starsNumber[curDeep]++;
        for(i=0,x1=s->x1,y1=s->y1,x2=s->x2,y2=s->y2;i<s->n;i++,x1++,y1++,x2++,y2++){
                drawGlZColoredLineSeq2(*x1+cx,*y1+cy,*x2+cx,*y2+cy,0);
        }
     
    
    }

}

void drawStarsColorSeq(SDL_Surface*screen,struct star*s,int cx,int cy,int r,int repeat,int curDeep,int nTree,int parity){
    int i;
    //int *x1,*y1,*y2,*x2;
        //fprintf(stderr,"!!!!!11111!\n");

    struct fraqVertex *p;
    int x,y;
    int nx1,ny1;
    
    x=cx;
    y=cy;
    transformXY(x,y);    
    cx=x;
    cy=y;
    p=rePlace(0,nTree,parity,cx,cy,pifSoft,pifWight);
    cx=p->x;
    cy=p->y;
    if(fraqElPresent(0,curDeep)){
        posColorLine(starsNumber[curDeep],starsOnLevel[curDeep]);
  
        drawStarColorSeq(screen,s,cx,cy,r,curDeep,nTree,parity);
    }
//    int nx1,ny1;
  //      x1=x1-sccx;

    int x1=cx-sccx;
    int y1=cy-sccx;
      for(i=2;i<repeat;i++){
        nx1=x1*cosAngleRepeat/1024 - y1*sinAngleRepeat/1024;
        ny1=x1*sinAngleRepeat/1024 + y1*cosAngleRepeat/1024;
        x1=nx1;
        y1=ny1;
        // int n;
        //  n=getNumberFromDeep(curDeep);
    
       // if( fraqElPresent(i-1,curDeep) )
//         drawColoredLineSeq2(sc,,,x2+sccx,y2+sccy);
        if(fraqElPresent(i-1,curDeep)){
            posColorLine(starsNumber[curDeep],starsOnLevel[curDeep]);
            drawStarColorSeq(screen,s,x1+sccx,y1+sccy,r,curDeep,nTree,parity);
        }
    }
  
    
}




void _drawStarsColorSeq(SDL_Surface*screen,struct star*s,int cx,int cy,int r,int repeat,int curDeep,int nTree,int parity){
    int i;
    int *x1,*y1,*y2,*x2;
    struct fraqVertex *p;
    int x,y;
    x=cx;
    y=cy;
    transformXY(x,y);    
    cx=x;
    cy=y;
    p=rePlace(0,nTree,parity,cx,cy,pifSoft,pifWight);
    cx=p->x;
    cy=p->y;
    if(putPixelMetod==0)
        for(i=0,x1=s->x1,y1=s->y1,x2=s->x2,y2=s->y2;i<s->n;i++,x1++,y1++,x2++,y2++){
            drawColoredLinesSeq2(screen,axb[*x1+r*2048]+cx,axb[*y1+r*2048]+cy,axb[*x2+r*2048]+cx,axb[*y2+r*2048]+cy,repeat,curDeep);
        }
    else{
        for(i=0,x1=s->x1,y1=s->y1,x2=s->x2,y2=s->y2;i<s->n;i++,x1++,y1++,x2++,y2++){
            orDrawColoredLinesSeq2(screen,axb[*x1+r*2048]+cx,axb[*y1+r*2048]+cy,axb[*x2+r*2048]+cx,axb[*y2+r*2048]+cy,repeat,curDeep);
        }
    }
}







