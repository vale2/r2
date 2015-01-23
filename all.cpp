#include<math.h>
#include<stdlib.h>
#include <SDL/SDL.h>
#include "graphutil.cpp"
#include"colors.cpp"
#define MAX4D 500
#define METEORS 100
//#define SHOWLINES 10000000
#define RADIUS4D 1000
#define RESTART4d 40000
#define G4D 10
#define G4D_M 0.1
#define MIND4D 10
#define sign_(a)  ((a)>=0.0?1:-1) 
#define abs_(a)  ( ((a)>=0.0) ? (a) : (-(a))   ) 
#define EPS 0.001
#define LINE 10
#define FOV (M_PI/3)
struct p4d{
    double x,y,z,w;
} ;
struct mp4d{
    double x,y,z,w,dx,dy,dz,dw;
};

struct p4d stars4d[MAX4D];
struct mp4d meteors[METEORS];
int near[MAX4D][3];
int scx[MAX4D];
int scy[MAX4D];

double cx,cy,cz,cw;
double cdx,cdy,cdz,cdw;
//double ca1,ca2,ca3,ca4;



void init4d(){
    int i,j,k,n;
    double r,rr,x,y,z,w,a1,a2,a3,xx,yy,zz,ww,a,b,c,d,e,f,g,h,l,m,u,o,p,q,s,t;
    
     for(i=0;i<METEORS;i++){
             r=rand()%RADIUS4D;
             a1=(rand()%RADIUS4D)*M_PI*2.0/RADIUS4D;
             a2=(rand()%RADIUS4D)*M_PI*2.0/RADIUS4D;
             a3=(rand()%RADIUS4D)*M_PI*2.0/RADIUS4D;
             meteors[i].x=r*cos(a1)*sin(a2)*sin(a3);
             meteors[i].y=r*sin(a1)*sin(a2)*sin(a3);
             meteors[i].z=        r*cos(a2)*sin(a3);
             meteors[i].w=                r*cos(a3);
             meteors[i].dx=r*cos(a1)*sin(a2)*sin(a3)/100000.0;
             meteors[i].dy=r*sin(a1)*sin(a2)*sin(a3)/100000.0;
             meteors[i].dz=        r*cos(a2)*sin(a3)/100000.0;
             meteors[i].dw=                r*cos(a3)/100000.0;
    }
    if(!(rand()%2)){
    
        for(i=0;i<MAX4D;i++){
            r=rand()%RADIUS4D;
            a1=(rand()%RADIUS4D)*M_PI*2.0/RADIUS4D;
            a2=(rand()%RADIUS4D)*M_PI*2.0/RADIUS4D;
            a3=(rand()%RADIUS4D)*M_PI*2.0/RADIUS4D;
            stars4d[i].x=r*cos(a1)*sin(a2)*sin(a3);
            stars4d[i].y=r*sin(a1)*sin(a2)*sin(a3);
            stars4d[i].z=        r*cos(a2)*sin(a3);
            stars4d[i].w=                r*cos(a3);
        }
    
    }else{
        a=(rand()%1000000)/10000000.0;
        b=(rand()%1000000)/10000000.0;
        c=(rand()%1000000)/10000000.0;
        d=(rand()%1000000)/10000000.0;
        e=(rand()%1000000)/10000000.0;
        f=(rand()%1000000)/10000000.0;
        g=(rand()%1000000)/10000000.0;
        h=(rand()%1000000)/10000000.0;
        l=(rand()%1000000)/10000000.0;
        m=(rand()%1000000)/10000000.0;
        u=(rand()%1000000)/10000000.0;
        o=(rand()%1000000)/10000000.0;
        p=(rand()%1000000)/10000000.0;
        q=(rand()%1000000)/10000000.0;
        s=(rand()%1000000)/10000000.0;
        t=(rand()%1000000)/10000000.0;
        for(i=0;i<MAX4D;i++){
            xx=rand()%(RADIUS4D*2)-RADIUS4D;
            yy=rand()%(RADIUS4D*2)-RADIUS4D;
            zz=l*cos(a*xx*xx)+b*sin(m*xx)+u*sin(c*yy*yy)+o*cos(d*yy);
            ww=p*cos(e*xx*xx)+q*sin(f*xx)+s*cos(g*yy*yy)+t*sin(h*yy);
            
            
            
            r=rand()%RADIUS4D;
            r=r*r/RADIUS4D*r/RADIUS4D;
            a1=(rand()%RADIUS4D)*M_PI*2.0/RADIUS4D;
            a2=(rand()%RADIUS4D)*M_PI*2.0/RADIUS4D;
            a3=(rand()%RADIUS4D)*M_PI*2.0/RADIUS4D;
            stars4d[i].x=xx+r*cos(a1)*sin(a2)*sin(a3);
            stars4d[i].y=yy+r*sin(a1)*sin(a2)*sin(a3);
            stars4d[i].z=zz+        r*cos(a2)*sin(a3);
            stars4d[i].w=ww+                r*cos(a3);
        }
    
    
    
    }
    
    for(i=0;i<MAX4D;i++){
        rr=-100;        
        for(j=0;j<3;j++){
            n=-1;
            for(k=0;k<MAX4D;k++){
                if(k==i || j>0 && k==near[i][0] || j==2 && k==near[i][1])
                    continue;
                x=stars4d[i].x-stars4d[k].x;
                y=stars4d[i].y-stars4d[k].y;
                z=stars4d[i].z-stars4d[k].z;
                w=stars4d[i].w-stars4d[k].w;
                r=x*x+y*y+z*z+w*w;
                if(rr<0.0 || rr>r){
                    n=k;
                    rr=r;
                }
            
            }
            near[i][j]=n;     
        
        }
    }
    
    
    
    cx=rand()%RADIUS4D;
    cy=rand()%RADIUS4D;
    cz=rand()%RADIUS4D;
    cw=rand()%RADIUS4D;
    cdx=((double)(rand()%RADIUS4D)) / RADIUS4D -0.5;
    cdy=((double)(rand()%RADIUS4D)) / RADIUS4D -0.5;
    cdz=((double)(rand()%RADIUS4D)) / RADIUS4D -0.5;
    cdw=((double)(rand()%RADIUS4D)) / RADIUS4D -0.5;
}

void close4d(){


}
void move4d(){
    double ccdx,ccdy,ccdz,ccdw;
    int i,j;
    ccdx=0;ccdy=0;ccdz=0;ccdw=0;
    for(i=0;i<METEORS;i++){
        ccdx=0;ccdy=0;ccdz=0;ccdw=0;
            for(j=0;j<MAX4D;j++){
                if(abs_((meteors[i].x-stars4d[j].x))>MIND4D   )
                    ccdx-=sign_(meteors[i].x-stars4d[j].x)*G4D/(meteors[i].x-stars4d[j].x) / (meteors[i].x-stars4d[j].x);
                if(abs_(meteors[i].y-stars4d[j].y)>MIND4D)
                    ccdy-=sign_(meteors[i].y-stars4d[j].y)*G4D/(meteors[i].y-stars4d[j].y) / (meteors[i].y-stars4d[j].y);
                if(abs_(meteors[i].z-stars4d[j].z)>MIND4D)
                    ccdz-=sign_(meteors[i].z-stars4d[j].z)*G4D/(meteors[i].z-stars4d[j].z) / (meteors[i].z-stars4d[j].z);
                if(abs_(meteors[i].w-stars4d[j].w)>MIND4D)
                    ccdw-=sign_(meteors[i].w-stars4d[j].w)*G4D/(meteors[i].w-stars4d[j].w) / (meteors[i].w-stars4d[j].w);    
            } 
            for(j=0;j<METEORS;j++){
                if(i==j)
                    continue;
                if(abs_((meteors[i].x-meteors[j].x))>MIND4D   )
                    ccdx-=sign_(meteors[i].x-meteors[j].x)*G4D_M/(meteors[i].x-meteors[j].x) / (meteors[i].x-meteors[j].x);
                if(abs_(meteors[i].y-stars4d[j].y)>MIND4D)
                    ccdy-=sign_(meteors[i].y-meteors[j].y)*G4D_M/(meteors[i].y-meteors[j].y) / (meteors[i].y-meteors[j].y);
                if(abs_(meteors[i].z-stars4d[j].z)>MIND4D)
                    ccdz-=sign_(meteors[i].z-meteors[j].z)*G4D_M/(meteors[i].z-meteors[j].z) / (meteors[i].z-meteors[j].z);
                if(abs_(meteors[i].w-meteors[j].w)>MIND4D)
                    ccdw-=sign_(meteors[i].w-meteors[j].w)*G4D_M/(meteors[i].w-meteors[j].w) / (meteors[i].w-meteors[j].w);    
                    
                    
            }   
        meteors[i].dx+=ccdx/(double)(MAX4D+METEORS);
        meteors[i].dy+=ccdy/(double)(MAX4D+METEORS);
        meteors[i].dz+=ccdz/(double)(MAX4D+METEORS);
        meteors[i].dw+=ccdw/(double)(MAX4D+METEORS);
        meteors[i].x+=meteors[i].dx;
        meteors[i].y+=meteors[i].dy;
        meteors[i].z+=meteors[i].dz;
        meteors[i].w+=meteors[i].dw;
    }
        ccdx=0;ccdy=0;ccdz=0;ccdw=0;
    for(i=0;i<MAX4D;i++){ 
        if(   abs_((cx-stars4d[i].x))>MIND4D   )
            ccdx-=sign_(cx-stars4d[i].x)*G4D/(cx-stars4d[i].x) / (cx-stars4d[i].x);
        if(abs_(cy-stars4d[i].y)>MIND4D)
            ccdy-=sign_(cy-stars4d[i].y)*G4D/(cy-stars4d[i].y) / (cy-stars4d[i].y);
        if(abs_(cz-stars4d[i].z)>MIND4D)
            ccdz-=sign_(cz-stars4d[i].z)*G4D/(cz-stars4d[i].z) / (cz-stars4d[i].z);
        if(abs_(cw-stars4d[i].w)>MIND4D)
            ccdw-=sign_(cw-stars4d[i].w)*G4D/(cw-stars4d[i].w) / (cw-stars4d[i].w);
    }
    cdx+=ccdx/(double)MAX4D;
    cdy+=ccdy/(double)MAX4D;
    cdz+=ccdz/(double)MAX4D;
    cdw+=ccdw/(double)MAX4D;
    cx+=cdx;
    cy+=cdy;
    cz+=cdz;
    cw+=cdw;       
    //printf("radius:%lf\n",sqrt(cx*cx+cy*cy+cz*cz+cw*cw));
    if(RADIUS4D*4.<sqrt(cx*cx+cy*cy+cz*cz+cw*cw) || (!(rand()%RESTART4d)))
        init4d();     
}


void draw4d(SDL_Surface* screen){
 //   SDL_FillRect(screen,NULL, 0x000000);
   // screen->w;
 //  screen->h;
   int i,j,k,a,b;
   double dx,dy,dz,dw,xx1,yy1,zz1,ww1,xx2,yy2,zz2,ww2,r,x,y;
    r=sqrt(cy*cy+cx*cx+cz*cz+cw*cw);
    xx1=cy/r;
    yy1=-cx/r;
    zz1=cw/r;
    ww1=-cz/r;
    xx2=cz/r;
    yy2=cw/r;
    zz2=-cy/r;
    ww2=-cx/r;
           
           
    
    for(i=0;i<METEORS;i++){ 
          x=meteors[i].x*xx1+meteors[i].y*yy1+meteors[i].z*zz1+meteors[i].w*ww1;
          y=meteors[i].x*xx2+meteors[i].y*yy2+meteors[i].z*zz2+meteors[i].w*ww2;
          dx=cx-meteors[i].x;
          dy=cy-meteors[i].y;
          dz=cz-meteors[i].z;
          dw=cw-meteors[i].w;
          r=sqrt(dx*dx+dy*dy+dz*dz+dw*dw);
          if(r<EPS)
            r=EPS;
          x/=r*r/1000000./3.;
          y/=r*r/1000000./4.;
          x+=screen->w/2;
          y+=screen->h/2;
          scx[i]=x;
          scy[i]=y;
          if(x>0&&x<screen->w && y>0 && y<screen->h)
            putpixel(screen,x,y,VERYGREEN);
        
        
    
    }

   
    for(i=0;i<MAX4D;i++){ 
    //    put4dpixel(screen,stars4d[i].x,stars4d[i].y,stars4d[i].z,stars4d[i].w,100);    
     //     rr=sqrt(stars4d[i].x*stars4d[i].x + stars4d[i].y*stars4d[i].y + stars4d[i].z*stars4d[i].z +stars4d[i].w*stars4d[i].w);
          x=stars4d[i].x*xx1+stars4d[i].y*yy1+stars4d[i].z*zz1+stars4d[i].w*ww1;
          y=stars4d[i].x*xx2+stars4d[i].y*yy2+stars4d[i].z*zz2+stars4d[i].w*ww2;
          dx=cx-stars4d[i].x;
          dy=cy-stars4d[i].y;
          dz=cz-stars4d[i].z;
          dw=cw-stars4d[i].w;
          r=sqrt(dx*dx+dy*dy+dz*dz+dw*dw);
          if(r<EPS)
            r=EPS;
          x/=r*r/1000000./3.;
          y/=r*r/1000000./4.;
          x+=screen->w/2;
          y+=screen->h/2;
          scx[i]=x;
          scy[i]=y;
          if(x>0&&x<screen->w && y>0 && y<screen->h)
            putpixel(screen,x,y,WHITE);
        
        
    
    }
    
        for(i=0;i<MAX4D;i++){
            dx=cx-stars4d[i].x;
            dy=cy-stars4d[i].y;
            dz=cz-stars4d[i].z;
            dw=cw-stars4d[i].w;
            r=sqrt(dx*dx+dy*dy+dz*dz+dw*dw); 
            if(r<RADIUS4D*2)
                continue;
        for(j=0;j<3;j++){
            if(near[i][j]==-1)
                continue;
            dx=cx-stars4d[near[i][j]].x;
            dy=cy-stars4d[near[i][j]].y;
            dz=cz-stars4d[near[i][j]].z;
            dw=cw-stars4d[near[i][j]].w;
            r=sqrt(dx*dx+dy*dy+dz*dz+dw*dw); 
            if(r<RADIUS4D*2)
                continue;
            
            drawLine(screen,scx[i],scy[i],scx[near[i][j]],scy[near[i][j]],GRAY);
            setPixel(screen,scx[i],scy[i],WHITE);
            setPixel(screen,scx[near[i][j]],scy[near[i][j]],WHITE);
        
        }
    }
  //	SDL_Flip( screen ); 
   // putpixel(screen,x,y,0);        
      
    

}
#define IPSEND
#define REVERCERGB
#include"/home/7/r2/ungl/_controll.cpp"
int main( int argc, char* args[]){ 
    addServer("192.168.211.165",8000,8001);
    addServer("10.42.0.1",8000,8001);
    addServer("192.168.44.113",8000,8001);
    addServer("192.168.0.48",8000,8001);
    addServer("192.168.43.6956cvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv ",8000,8001);

    FILE*f;
    char name[128];
    int a,b;
    f=fopen("hosts.lst","r");
    if(f!=NULL){
        while(!feof(f)){
            fscanf(f,"%s %d %d",name,&a,&b);
            addServer(name,a,b);
        }
        fclose(f);
    }
    while(myConnect());
    return controll_main(argc,args);
    myDisconnect();
}
#include"koefs.cpp"
#define GARMONY 10
struct asc{
    int n;
    double t[GARMONY];
    double a[GARMONY];
    double z[GARMONY];
    double f[GARMONY];
}ascellator[DRAWKOEFNUM];

void zeroAsc(){
    int i;
    for(i=0;i<DRAWKOEFNUM;i++)
        ascellator[i].n=0;

}
void setAscellator(int n,double t,double a,double z,double f){

   ascellator[n].t[0]=t;
   ascellator[n].a[0]=a;
      ascellator[n].z[0]=z;
   ascellator[n].f[0]=f;
   ascellator[n].n=1;

}
void addAscellator(int n,double t,double a,double z,double f){
   if(ascellator[n].n<GARMONY){
        ascellator[n].t[ascellator[n].n]=t;
        ascellator[n].a[ascellator[n].n]=a;
        ascellator[n].z[ascellator[n].n]=z;
        ascellator[n].f[ascellator[n].n]=f;
        ascellator[n].n++;
   }
}
double ascell(int n,double t){
    double r;
    int i;
    r=0.;
 //  printf("Calc asc# %d :\n",n);
    for(i=0;i<ascellator[n].n;i++){
        r+=ascellator[n].z[i]+ascellator[n].a[i]*sin((ascellator[n].f[i]+t/ascellator[n].t[i]));
   //     printf("%lf %lf %lf %lf\n",ascellator[n].t[i],ascellator[n].a[i],ascellator[n].z[i],ascellator[n].f[i]);
    }
   // fflush(stdout);
    return r;

}

#include <SDL/SDL.h>
#include <math.h>
#include"colors.cpp"
#include"graphutil.cpp"


#define MAXBARS 1024
#define TURN2NORM 50
#define TURN2UNNORM 70
#define TURNGRAY 50
#define TURNPARTBAR 30
#define TURNALL 300
#define NORMALCENTER 300
#define NORMALSPEED 3000
#define NORMALWiDTH 295
#define REDONE 1000


long bartime;
char bars[MAXBARS][MAXBARS];
unsigned int bw;
unsigned int bh;
unsigned int nbw;
unsigned int scrw;
unsigned int scrh;
int barcolor;
void initbarcode(SDL_Surface* screen){
    int i;
    int j;
    bartime=0;
    nbw=300;
    barcolor=WHITE;
    scrw=screen->w;
    scrh=screen->h;
    bw=5;
    bh=bw*scrh/scrw;
    for(i=0;i<MAXBARS;i++){
        for(j=0;j<MAXBARS;j++){
            bars[i][j]=rand()%2;
        }
    }
}

void checkBars(){
    int i,j;
    int ii,jj;
    int summ,all;
    for(i=0;i<bw;i++)
        for(j=0;j<bh;j++){
            summ=0;
            all=0;
            for(ii=i*MAXBARS/bw;ii<(i+1)*MAXBARS/bw;ii++){
                for(jj=j*MAXBARS/bh;jj<(j+1)*MAXBARS/bh;jj++){
                    if(bars[ii][jj])
                        summ++;
                     all++;
                }
            
            }
            if(all!=0){
                summ=(summ+all/2-rand()%2)/all;
                if(summ)
                    summ=1;
            }else{
                summ=1;
            }
            for(ii=i*MAXBARS/bw;ii<(i+1)*MAXBARS/bw;ii++){
                for(jj=j*MAXBARS/bh;jj<(j+1)*MAXBARS/bh;jj++){
                    bars[ii][jj]=summ;
                }
            
            }
        }

}


void inverse(int x,int y){
    int i,j,mi,mj;
    i=x*MAXBARS/bw;

    mi=(x+1)*MAXBARS/bw;
    mj=(y+1)*MAXBARS/bh;
    
    for(;i<mi;i++)
        for(j=y*MAXBARS/bh;j<mj;j++){
            bars[i][j]=!bars[i][j];
        
        }
}
void makered(int x,int y){
    int i,j,mi,mj;
    i=x*MAXBARS/bw;

    mi=(x+1)*MAXBARS/bw;
    mj=(y+1)*MAXBARS/bh;
    
    for(;i<mi;i++)
        for(j=y*MAXBARS/bh;j<mj;j++){
            bars[i][j]=2;
        
        }
}

void inversePartBar(int x1,int y1,int hh){
    int x,y,cx,cy,h,i;
    cx=(x1*2+hh)/2;
    cy=(y1*2+hh)/2;
    inverse(cx,cy);
    for(h=2;h<=hh/2;h+=2){
        inverse(cx+h,cy);
        inverse(cx-h,cy);
        inverse(cx,cy+h);
        inverse(cx,cy-h);
        inverse(cx+h,cy+h);
        inverse(cx+h,cy-h);
        inverse(cx-h,cy-h);
        inverse(cx-h,cy+h);

        for(i=1;i<h;i++){
            inverse(cx+h,cy+i);
            inverse(cx+h,cy-i);
            inverse(cx-h,cy+i);
            inverse(cx-h,cy-i);
            inverse(cx+i,cy+h);
            inverse(cx-i,cy+h);
            inverse(cx+i,cy-h);
            inverse(cx-i,cy-h);
           
        }  
    }     


}
void movebarcode(){
    int x,y,h;
    if(!(rand()%50))
    bartime++;
    nbw=NORMALCENTER-NORMALWiDTH*sin(bartime*3.14*2/NORMALSPEED);
   // printf("%d\n",nbw);


    if(!(rand()%TURN2NORM)){
        if(bw>nbw && (bw-1)*scrh/scrw>1){
            bw--;            
        }
        if(bw<nbw && (bw+1)*scrh/scrw<MAXBARS - 1){
            bw++;            
        }
        bh=bw*scrh/scrw;
        //printf("turn2norm:%d %d\n",bw,bh);
        //fflush(stdout);
        checkBars();
    }
    if(!(rand()%TURN2UNNORM)){
        if(bw>nbw && bw < MAXBARS -1 && (bw+1)*scrh/scrw<MAXBARS - 1){
            bw++;            
        }
        if(bw<nbw && bw > 2 && (bw-1)*scrh/scrw>1){
            bw--;            
        }
        bh=bw*scrh/scrw;
       // printf("turn2unnorm:%d %d\n",bw,bh);
       // fflush(stdout);
        checkBars();
    }
    //printf("check!\n");
    //fflush(stdout);
    
    if((!(rand()%TURNGRAY))){
        x=rand()%bw;
        y=rand()%bh;
        inverse(x,y);
    }
    if(!(rand()%TURNPARTBAR)){
        x=rand()%bw;
        y=rand()%bh;
        h=4 *( rand()%(((bh/5)+1)));
        if(x+h>=bw)
            h=bw-1-x;
        if(y+h>=bh)
            h=bh-1-y;
        inversePartBar(x,y,h);
        
    
    }
    if(!(rand()%TURNALL)){
        for(x=0;x<bw;x++)
            for(y=0;y<bh;y++)
                inverse(x,y);    
    
    }
    
    
    if(!(rand()%REDONE)){
        x=rand()%bw;
        y=rand()%bh;        
        makered(x,y);  
    
    
    }
}
void closebarcode(){

}

void drawBar(SDL_Surface* screen,int x1,int y1,int x2,int y2,int color){
    int x,y;
    for(x=x1;x<=x2;x++)
        for(y=y1;y<=y2;y++){
            putpixel(screen,x,y,color);
        }

}
void drawbarcode(SDL_Surface* screen){
    int i,j;
    
    for(i=0;i<bw;i++){
        for(j=0;j<bh;j++){
            if(bars[i*MAXBARS/bw][j*MAXBARS/bh])
                drawBar(screen,i*screen->w/bw,j*screen->h/bh,(i+1)*screen->w/bw-1,(j+1)*screen->h/bh-1,bars[i*MAXBARS/bw][j*MAXBARS/bh]==1?barcolor:VERYRED);        
        }
    
    }
    
    
    
    
    

}
#ifndef COLORSMOD
#define COLORMOD
#define GRAY 0x10101010

#ifndef REVERCERGB

    #define YELLOW 0xaf9000
    #define WHITE 0xffffffff
//#define DARKRED   0x600505
    #define VERYRED   0xff0505
    #define GREEN   0x005000
    #define VERYGREEN   0x00ff00
    #define BLACK 0x0
    #define BORDERCOLOR 0x107000
    #define RED 0xff0000
    #define MAGENTA 0x00ffff
//#define GREEN 0x00ff00
    #define BLUE 0xff
    #define DARKRED 0x700000
    #define DARKGREEN 0x007000
    #define DARKBLUE 0x70




    #define DARKGRAY 0x707070
    #define BROWN 0x00a0a0

#else
    #define MAGENTA 0xffff00

    #define BROWN 0xa0a000

    #define YELLOW 0x0090af
    #define WHITE 0xffffffff
//#define DARKRED   0x600505
    #define VERYRED   0x0505ff
    #define GREEN   0x005000
    #define VERYGREEN   0x00ff00
    #define BLACK 0x0
    #define BORDERCOLOR 0x007010
    #define RED 0x0000ff
//#define GREEN 0x00ff00
    #define BLUE 0xff0000
    #define DARKRED 0x000070
    #define DARKGREEN 0x007000
    #define DARKBLUE 0x700000
    #define DARKGRAY 0x707070


#endif
#endif

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



    


int mode=5;
int pageScreen=0;
#include"colors.cpp"

Uint32 frames=0;
int slowWork=0;
void takeItEasy(){
   struct timespec tw = {0,03};
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
            if(keys[CTRL]){
                char*p;
                p=saveNext();
            }else{
                loadNext();
            }
        
        }
    
    if(keys[KEY_F11]==2){
            if(!keys[CTRL]){
                loadPrev();
            }else{
                saveCurrent();
            }
        
        }
    
    
    
    for(int i=0;i<10;i++){
        if(keys[i+KEY_F1]==2){
            char name[32];
            sprintf(name,"quick_%d.r2",i+1);
            if(keys[CTRL]){
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
int syntaxControll(char*p){
    char term[128];
    char buf[128];
    int t1,i,t2;
    char s1[128];
    char s2[128];
    double t,a,z,f;
   // printf("SyntaxControll:%s\n",p);
    lastRecive= GetTickCount();
    while(*p){
        term[0]=0;
        sscanf(p,"%s",term);
        p+=skeep(p);
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
    drawSpiralTransform(screen->w/3,0,6*screen->w/13,screen->h/6,screen);
    drawMegaTransform(screen->w/3,screen->h/6+1,6*screen->w/13,screen->h/3,screen);
    
    drawOSDButts(11*screen->w/13,screen->h/4,screen->w-1,screen->h/3,screen);
    
    
    
    
    //drawPifNaked(0,2*screen->h/3,screen->w/10,screen->h-1,screen);
    //drawPifColored(screen->w/10,2*screen->h/3,2*screen->w/10,screen->h-1,screen);
    //drawPifPosition(2*screen->w/11,screen->h/3,3*screen->w/11,2*screen->h/3,screen);
    //drawPifSigns(4*screen->w/10,2*screen->h/3,7*screen->w/10,screen->h-1,screen);
  
  
  
  
    drawInput(screen,0,0.4,0.25,0.6);  
    drawRithm(screen,screen->w/4,screen->h*0.4,0.75*screen->w,screen->h*0.6,rithm);
    
    drawOutput(screen,0.75,0.4,1,0.6);  

    drawFade(6*screen->w/13,0,7*screen->w/13-1,screen->h/6,screen);
    drawOrblur(7*screen->w/13,0,8*screen->w/13-1,screen->h/6,screen);
    
    
    
    drawMaskFilter(6*screen->w/13,screen->h/6+1,8*screen->w/13-1,screen->h/3,screen);
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
int controll(){
    SDL_Event event;
    char buf[BUFSIZE+1]="";
    int datasize;
    int msgid,size;

    recive();
    #ifdef IPSEND

    if(connectflag && GetTickCount() - lastRecive >1000 ){
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
                if(clickMouse(event.button.x,event.button.y)){
                    addDrop(event.button.x,event.button.y);
                
                }
                
                selectEValue(event.button.x,event.button.y);
                break;
            case SDL_MOUSEMOTION:
                modifySelected(event.motion.x,event.motion.y);
                if(event.motion.state)
                    sclickMouse(event.motion.x,event.motion.y);
            break;
            case SDL_MOUSEBUTTONUP:
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
    
    printf("\nconnect\n");
    while(!connectflag){
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
      printf("\ndisconnect\nEOF:%c",EOF);
      fflush(stdout);
      sleep(1);
      for(int i=0;i<100;i++){
          controll();      
      }
     // sleep(1);
      return 0;
}


#define IPSEND
#include"/home/7/r2/ungl/_controll.cpp"
int main( int argc, char* args[]){ 
  //  addServer("192.168.211.165",8000,8001);
 //   addServer("127.0.0.1",8000,8001);
 //   addServer("10.42.0.1",8000,8001);
//    addServer("192.168.44.113",8000,8001);
//    addServer("192.168.0.48",8000,8001);

    FILE*f;
    char name[128];
    int a,b;
    f=fopen("hosts.lst","r");
    if(f!=NULL){
        while(!feof(f)){
            b=-1;
            fscanf(f,"%s %d %d",name,&a,&b);
//            a=8000;b=8001;
            fprintf(stderr,"server: <%s>,%d ",name,a);
            fprintf(stderr," %d\n",b);
            addServer(name,a,b);
        }
        fclose(f);
    }
    int r;
    while(myConnect());
    r= controll_main(argc,args);
    myDisconnect();
    return r;
}
#ifndef COSMOD
#define COSMOD
#include<math.h>
#include<stdlib.h>
#include"quickspeq.cpp"

int good[12] = {1, 2, 10, 11, 5, 6, 8, 9, 7, 4, 3, 0};

int find_(int num){
  int i;
  for (i = 0; i < 12; i++){
    if (good[i] == num)
      return(i);
  }
  //return(-100500);
}
double getQualInterval( int a, int b ){
  int period;
  period = abs((a % 12) - (b % 12));
  return(find_(period) / 12.);
}



double findCos(struct qs a){
  int i; int j;
  double r=7    ;
  for (i = 0; i < a.tones *(int)a.oqs; i++){
    for (j = i + 1; j < a.tones *(int)a.oqs; j++){
      r+=a.ks[i]*a.ks[j]   *getQualInterval(i,j);
      //printf("gqi: %lf \n", getQualInterval(i,j));
      
    }
  }
  return r;
}
#endif
#include<SDL/SDL.h>
#include"graphutil.cpp"
#include"koefs.cpp"
#include"colors.cpp"
#include"piano.cpp"
#include"editpannels.cpp"
#include"soundutil.cpp"


extern double hearingVolume;
extern double amplifierKoef;
extern double amplifierKoefHighValue;
extern double amplifierKoefLowValue;
extern int faded;
extern int rgbMixerDepth;
extern int rgbMixerDepthAuto;
extern int noiseC;
extern int noiseV;
extern int noiseColor;
extern double pifColorSpeedr;
extern double pifColorSpeedg;
extern double pifColorSpeedb;
extern int pifDeep;
extern int pifNaked;
extern int pifColored;
extern double pifDWind;
extern double pifDScale;
extern double pifDAngle;


extern int pifPosition;

extern int showColorSeq;




Uint32 findDrawKoefColor(int k,double old);
Uint32 findDrawKoefColor(int k);
Uint32 getSoundKoefsColor(int i,double old);
#define SPASHSPEED 0.9
double drawSplash(SDL_Surface*screen,int x1,int y1,int x2,int y2,double splash){
    Uint32 color;
    color=splash*255;
    color=color + color*256+color*256*256;
//    if(color)
        bar(screen,x1,y1,x2,y2,color);
    return splash*SPASHSPEED;
}


void drawPannelStack(SDL_Surface*screen,int x1,int y1,int x2,int y2,int k);
void    drawNoise(int sx,int sy,int ex,int ey,SDL_Surface*screen){
    int i,x1,x2,y1,y2,x,y,a,yy;
    Uint32 p;
    x1=sx;
    x2=sx+(ex-sx)/3;
    
    y1=sy+(ey-sy)*(99-noiseC)/100;
    y2=ey;
    if(y1<0)
        y1=0;
    for(i=0;i<noiseC*x2*(y2-y1)/100;i++){
        putpixel(screen,x1+rand()%(x2-x1),y1+rand()%(y2-y1),0xffffff);   
    
    }
   
    
    x1=sx+(ex-sx)/3;
    x2=sx+2*(ex-sx)/3;
    y1=sy;
    y2=ey;
    for(y=y1;y<y2;y++)
        for(x=x1;x<x2;x++){
            a=((y2-y)*255/(y2-y1)<noiseV)?(rand()%(noiseV+1)):(0);
            rgb2pixel(a,a,a,&p);
            putpixel(screen,x,y,p);
        
        }   
        
    
    
    x1=(sx+2*(ex-sx))/3;
    x2=ex;
    y1=sy;
    y2=ey/2;
    if(noiseColor)
        yy=(2*y1+y2)/3;
    else
        yy=(y1+2*y2)/3;
        
    
    
   /*  for(i=0;i<3*(x2-x1)*(yy-y1)/100;i++){
            //if(noiseColor){
                rgb2pixel(rand()%(noiseV+1),rand()%(noiseV+1),rand()%(noiseV+1),&p);
            
           // putpixel(screen,x1+rand()%(x2-x1),y1+rand()%(yy-y1),p);
        
        }  
     for(i=0;i<3*(x2-x1)*(y2-yy)/100;i++){
                a=rand()%noiseV;
                rgb2pixel(a,a,a,&p);
           
            putpixel(screen,x1+rand()%(x2-x1),yy+rand()%(y2-yy),p);
        
        }  
     
     */
     
    


    rectangle(screen,sx,sy,ex,ey,BORDERCOLOR);
}
double loadPrevSplash;
double loadNextSplash;
void loadPreset();
void drawPrevPreset(int x1,int y1,int x2,int y2,SDL_Surface*screen){
    loadPrevSplash=drawSplash(screen,x1,y1,x2,y2,loadPrevSplash);

    bar(screen,x1,y1,(x1*9+x2)/10,y2,WHITE);    
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);
    addButton(x1,y1,x2,y2,0,loadPreset);

}



void drawNextPreset(int x1,int y1,int x2,int y2,SDL_Surface*screen){
    loadNextSplash=drawSplash(screen,x1,y1,x2,y2,loadNextSplash);
    bar(screen,(x2*9+x1)/10,y1,x2,y2,WHITE);    
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);
    addButton(x1,y1,x2,y2,1,loadPreset);

}
void drawSaveLoadButts(int x1,int y1,int x2,int y2,SDL_Surface*screen){
   drawPrevPreset(x1,y1,(x1*2+x2)/3,y2,screen);
   drawNextPreset((x1+x2*2)/3,y1,x2,y2,screen);
   //addButton(x1,y1,x2,y2,1,loadPreset);
   rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);
    
}
void rizeOSD();
void  drawOSDButts(int x1,int y1,int x2,int y2,SDL_Surface*screen){
    bar(screen,(x2*9+x1)/10,y1,x2,y2,WHITE);    
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);
    
    addButton(x1,y1,x2,y2,1,rizeOSD);


    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);
}


void drawPiano(int x1,int y1,int x2,int y2,SDL_Surface*screen){
    if(rgbMixerDepth!=11){
        drawPianoBarScale(screen,x1,y1,(x1*3+x2)/4-2,y2,5,80);
        drawPianoBarScale(screen,(x2*3+x1)/4+2,y1,x2,y2,1,80);
//        rectangle(screen,(x2*3+x1)/4+2,y1,x2,y2,DARKGRAY);
        drawPianoBar(screen,(x1*3+x2)/4,(y1*2+y2)/3 ,x1+   (x2-x1)/4 + ((x2-x1)/2-15)*rgbMixerDepth/10  +15   ,(y1+y2*2 )/3,rgbMixerDepth/2+1);



//        drawPianoBarScale(screen,x1,y1,x1+(x2-x1)*rgbMixerDepth/10,y2,5,80);
        addEValue(x1,y1,x2,y2,1,0.01,0,10,&rgbMixerDepth);
    
    }else{
        drawPianoBarScale(screen,x1,y1,(x1*3+x2)/4-2,y2,1,80);
        drawPianoBarScale(screen,(x2*3+x1)/4+2,y1,x2,y2,5,80);
        drawPianoBar(screen,(x1*3+x2)/4,(y1*2+y2)/3 ,x1+   (x2-x1)/4 + ((x2-x1)/2-15)*rgbMixerDepth/10  +15   ,(y1+y2*2 )/3,rgbMixerDepth/2+1);

    }    
        rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);
}




void drawOrblur(int x1,int y1,int x2,int y2,SDL_Surface*screen){
   int x,y;
   unsigned int reverceRGB;
   #ifdef REVERCERGB
       reverceRGB=256;
   #else   
       reverceRGB=256;
   #endif
   double dorblurd;
   if(orblurd>240){
       dorblurd=0.02;
   }else {
       dorblurd=0.3;
   }
  addEValue(x1,y1,x2,y2,1,dorblurd,0,255,&orblurd);
   if(orblurd>240){
   
     for(y=y1;y<y2;y++){
        for(x=x1;x<(x2+x1)/2;x++){
            putpixel(screen,x,y,(y-y1)*255/(y2-y1) * reverceRGB);
    
        }
      }
      for(y=y1;y<y2;y++){
        for(x=(x2+x1)/2;x<x2;x++){
            if((x-(x2+x1)/2)*15<(orblurd-240)*(x2-(x2+x1)/2))
            putpixel(screen,x,y,(y-y1)*255/(y2-y1) *reverceRGB);
    
        }
      }


   }else{
   
   for(y=y1;y<y2;y++){
        for(x=x1;x<(x2+x1)/2;x++){
            if((x-x1)*240<orblurd*(((x2+x1)/2-x1)))
            putpixel(screen,x,y,(y-y1)*255/(y2-y1) * reverceRGB);
    
        }
      }
   }
   
   
   //x1=2*screen->w/13;
   // x2=3*screen->w/13;
   // y1=0;
   // y2=screen->h/3;
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);
}



void drawFade(int x1,int y1,int x2,int y2,SDL_Surface*screen){
   int x,y;
   unsigned int reverceRGB;
   #ifdef REVERCERGB
       reverceRGB=256*256;
   #else   
       reverceRGB=1;
   #endif
   double dfaded;
   if(faded<20){
       dfaded=0.02;
   }else {
       dfaded=0.3;
   }
  addEValue(x1,y1,x2,y2,1,dfaded,0,255,&faded);
   if(faded>20){
   
     for(y=y1;y<y2;y++){
        for(x=x1;x<(x2+x1)/2;x++){
            putpixel(screen,x,y,(y-y1)*255/(y2-y1) * reverceRGB);
    
        }
      }
      for(y=y1;y<y2;y++){
        for(x=(x2+x1)/2;x<x2;x++){
            if((x-(x2+x1)/2)*235<(faded-20)*(x2-(x2+x1)/2))
            putpixel(screen,x,y,(y-y1)*255/(y2-y1) *reverceRGB);
    
        }
      }


   }else{
   
   for(y=y1;y<y2;y++){
        for(x=x1;x<(x2+x1)/2;x++){
            if((x-x1)*20<faded*(((x2+x1)/2-x1)))
            putpixel(screen,x,y,(y-y1)*255/(y2-y1) * reverceRGB);
    
        }
      }
   }
   
   
   //x1=2*screen->w/13;
   // x2=3*screen->w/13;
   // y1=0;
   // y2=screen->h/3;
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);
}
#define MAXCOLORSPEED 50



int findSpeed(double s){
       int i;
       for(i=0;s>0.002;i++,s/=1.27);
       return i;

}



#define MAXWINDSPEED 25
#define MAXSCALESPEED 17
#define MAXANGLESPEED 27
int findWindSpeed(double s){
       int i;
       for(i=0;s>0.0000002;i++,s/=1.27);
       return i;

}
int findScaleSpeed(double s){
       int i;
       for(i=0;s>0.2;i++,s/=1.27);
       return i;

}
int findAngleSpeed(double s){
       int i;
       for(i=0;s>0.0001;i++,s/=1.27);
       return i;

}



void drawColorSpeed(int x1,int y1,int x2,int y2,SDL_Surface*screen){
    int xx1,xx2,yy1,yy2,x,y,a;
    Uint32 p;

    xx1=x1;
    xx2=x1+(x2-x1)/3;
    yy1=y1;
    yy2=y2;
// 0.002 ..200
    a=findSpeed(pifColorSpeedr);
    for(y=yy1;y<yy2;y++)
        for(x=xx1;x<xx2;x++){
            p=(((yy2-y)*MAXCOLORSPEED / (yy2-yy1)   )<(a))?(RED):(0);
            
            putpixel(screen,x,y,p);
        
        }   




    xx1=x1+(x2-x1)/3;
    xx2=x1+2*(x2-x1)/3;
    yy1=y1;
    yy2=y2;
    a=findSpeed(pifColorSpeedg);
    for(y=yy1;y<yy2;y++)
        for(x=xx1;x<xx2;x++){
            p=((yy2-y)*MAXCOLORSPEED/(yy2-yy1)<a)?(GREEN):(0);
            
            putpixel(screen,x,y,p);
        
        }   
    xx1=x1+2*(x2-x1)/3;
    xx2=x2;
    yy1=y1;
    yy2=y2;
    
    a=findSpeed(pifColorSpeedb);
    for(y=yy1;y<yy2;y++)
        for(x=xx1;x<xx2;x++){
            p=((yy2-y)*MAXCOLORSPEED/(yy2-yy1)<a)?(BLUE):(0);
            
            putpixel(screen,x,y,p);
        
        }   


    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);
}
#define min(a,b) ((a)<(b)?(a):(b))


void drawSinglePif(SDL_Surface*screen,int x1,int y1,int x2,int y2,double wind,Uint32 color){
    int cx,cy,w;
    cx=(x1+x2)/2;
    cy=(y1+y2)/2;
    w=min((x2-x1)/2,(y2-y1)/2);
    
    drawLine(screen,cx,cy,cx+cos(wind)*w,cy-sin(wind)*w,color);
    
    

    
}

void drawValuedSector(SDL_Surface*screen,int x1,int y1,int x2,int y2,double min,double max,double value,Uint32 colormin,Uint32 colormax,Uint32 colorvalue){
    int i;
    for(i=0;i<201;i++){
        drawSinglePif(screen,x1,y1,x2,y2,(min*(200-i)+max*(i))/200,(colormin));
    }


    drawSinglePif(screen,x1,y1,x2,y2,value,colorvalue);
}

void rizeAnglePannel();
int rizePannel;
void drawAnglePannelStack(SDL_Surface*screen,int x1,int y1,int x2,int y2,int k){
    int cells,lines;
    double values[ROWS];
    double controlls[ROWS];
    Uint32 colors[ROWS];
    double *ev[ROWS];
    int i,minusFlag,ttth,tttw,y,j,c,l;
    double max;
    int panel;
    int param;
    int noMaxDrawKoef=0;
    int w,maxw;
    cells=ROWS;
    lines=1;
    maxw=(x2-x1)/ROWS;
    if(rizePannel ==0)
        addButton(x1,y1,x2,y2,k,rizeAnglePannel);

    
    for(i=1;i<=ROWS;i++){
        c=i;
        l=(ROWS+c-1)/c;
        w=min((x2-x1)/c,(y2-y1)/l);
        if(w>maxw){
            maxw=w;
            lines=l;
            cells=c;
        }
    
    }
    w=maxw;
    if(lines<=0 || cells<=0){
        cells=ROWS;
        lines=1;
    }
    
    if(k<0){
        k=-k;
        noMaxDrawKoef=1;
        
    }
    
    panel=panel_no[curEditPannel];
    param=curEditParam;
    values[0]=drawKoef[k];
    ev[0]=NULL;
    controlls[0]=0;//maxDrawKoef[k];
    colors[0]=findDrawKoefColor(k);
    values[1]=zeros[k];
    ev[1]=zeros+k;
    colors[1]=WHITE;
    controlls[1]=zeros[k];
    
    values[2]=drawLatKoef[k];
    ev[2]=drawLatKoef+k;
    colors[2]=0xffff00;
    controlls[2]=drawLatKoef[k];

    
    for(i=0;i<KOEFNUM;i++){
        double t;
        colors[PREGDOEFS+i]=getSoundKoefsColor(i,0);
        t=soundKoefs[i]*controllKoef[k*KOEFNUM+i];
        values[PREGDOEFS+i]=t;
        ev[PREGDOEFS+i]=&(controllKoef[k*KOEFNUM+i]);
        controlls[PREGDOEFS+i]=controllKoef[k*KOEFNUM+i];
    
    }
    max=0.;
    for(i=0;i<ROWS;i++){
        //if(controlls[i]<0.0){
         //   minusFlag=1;
       // }
        if(fabs(controlls[i])>max){
            max=fabs(controlls[i]);
        }
    
    }
    minusFlag++;
    if(max<0.0001){
        max=0.0001;
    }
    maxPannelValue[k]=M_PI/10.;//max;

    ttth=y2-y1;
    tttw=x2-x1;
    
    for(i=0;i<ROWS;i++){
        int x,y;
        x=i%cells;
        y=i/cells;
        x=x1+(x2-x1)*x/cells;
        y=y1+(y2-y1)*y/lines;
        
//        values[i];
  //      controlls[i];
        
        
        drawValuedSector(screen,x,y,x+w,y+w,0,controlls[i],values[i],colors[i],colors[i],WHITE);
        if(rizePannel ==1)
            addEValue(x,y,x+w,y+w,0,M_PI/1000.,-2*M_PI,2*M_PI,ev[i]);
                
        
        if(k==panel && i==param){
                circle(screen,x+w/2,y+w/2,w/2,RED);

        }
    }
    if(k==panel){
        rectangle(screen,x1+1,y1+1,x2-1,y2-1,RED);
    }

    


}
#include<math.h>
#include"pifmousecontroll.cpp"



double colorSeqSplash=0.;
void drawColorSeq(int x1,int y1,int x2,int y2,SDL_Surface*screen){
    int h,w,i,yr,yg,yb;
    int gx1,gx2,gy1,gy2,gw,gh;
    int minFreqX;
    w=x2-x1;
    h=y2-y1;
    
    gx1=x1+w/20;
    gx2=x2-w/20;
    gy2=y2-4*h/20;
    gy1=y1+h/20;
    
    gw=gx2-gx1;
    gh=gy2-gy1;
    
    Uint32 c;
    bar(screen,x1,y1,x2,y2,0);
    colorSeqSplash=drawSplash(screen,x1,y1,x2,y2,colorSeqSplash);
    minFreqX = log(minColorSeqFreq+1)*gw/log(SAMPLE_RATE/2+1);
    bar(screen,gx1+minFreqX-1,y2-h/40,gx1+minFreqX+1,y2,0xffffff);
    /*
    if(showColorSeq){
        for(i=0;i<gw;i++){
            c=colorSeq2Buf[i*SEQLEN/gw];
            drawLine(screen,gx1+i,y2-h/20,gx1+i,y2-3*h/20,c);
            pixel2rgb(c,yr,yg,yb);
            yr=gy2-yr*gh/255;
            yg=gy2-yg*gh/255;
            yb=gy2-yb*gh/255;
            putpixel(screen,gx1+i,yr,getpixel(screen,gx1+i,yr)|RED);
            putpixel(screen,gx1+i,yg,getpixel(screen,gx1+i,yg)|VERYGREEN);        
            putpixel(screen,gx1+i,yb,getpixel(screen,gx1+i,yb)|BLUE);
    
        }
    }
*/
   drawOqColorLines(screen,gx1,gy1,gx2,gy2);
   rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);
   addButton(x1,y1,x2,y2,0,changeColorSeq);
}


void drawWind(int x1,int y1,int x2,int y2,SDL_Surface*screen){
    double minWind;
    double maxWind;
    int x,i;
    maxWind=minWind=zeros[3]+dkoefacc[3]+ascellValue[3];
    
    for(i=0;i<KOEFNUM;i++){
        maxWind=maxWind+controllKoef[3*KOEFNUM+i];
       // minWind=minWind-controllKoef[3*KOEFNUM+i];
    }    
    
    x=(x1*2+x2)/3;
    if(minWind<minDrawKoef[3]){
        minWind=minDrawKoef[3];
    }
    if(maxWind>maxDrawKoef[3]){
        maxWind=maxDrawKoef[3];
    }
    
    
///   drawSinglePif(screen,x1,y1,x,y2,minWind,BLUE);
//   drawSinglePif(screen,x1,y1,x,y2,maxWind,BLUE);   
//   drawSinglePif(screen,x1,y1,x,y2,drawKoef[3],WHITE);    
    drawValuedSector(screen,x1,y1,x,y2,minWind,maxWind,drawKoef[3],BLUE,BLUE,WHITE);

   drawAnglePannelStack(screen,x,y1,x2,y2,3);
   
   
   rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);

}
void  drawCircleSeq(int x1,int y1,int x2,int y2,SDL_Surface*screen){
    drawPannelStack(screen,x1,y1,x2,y2,8);
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);				
}
void  drawCircleSeqSymm(int x1,int y1,int x2,int y2,SDL_Surface*screen){
    drawPannelStack(screen,x1,y1,x2,y2,7);
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);				
}

void drawPifAngle(int x1,int y1,int x2,int y2,SDL_Surface*screen){
    double minWind;
    double maxWind;
    int x,i;
    maxWind=minWind=zeros[5]+dkoefacc[5]+ascellValue[5];
    
    for(i=0;i<KOEFNUM;i++){
        maxWind=maxWind+controllKoef[5*KOEFNUM+i];
       // minWind=minWind-controllKoef[3*KOEFNUM+i];
    }    
    
    x=(x1*2+x2)/3;
    if(minWind<minDrawKoef[5]){
        minWind=minDrawKoef[5];
    }
    if(maxWind>maxDrawKoef[5]){
        maxWind=maxDrawKoef[5];
    }
    
    
///   drawSinglePif(screen,x1,y1,x,y2,minWind,BLUE);
//   drawSinglePif(screen,x1,y1,x,y2,maxWind,BLUE);   
//   drawSinglePif(screen,x1,y1,x,y2,drawKoef[3],WHITE);    
    drawValuedSector(screen,x1,y1,x,(y2+y1)/2,minWind,maxWind,drawKoef[5],BLUE,BLUE,WHITE);

 
   drawAnglePannelStack(screen,x,y1,x2,y2,5);
   
   
   rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);

}


void drawMoveSpeed(int x1,int y1,int x2,int y2,SDL_Surface*screen){
    int xx1,xx2,yy1,yy2,x,y,a;
    Uint32 p;

    xx1=x1;
    xx2=x1+(x2-x1)/3;
    yy1=y1;
    yy2=y2;
// 0.002 ..200

// pifDWind;
// pifDScale;
// pifDAngle;

    a=findWindSpeed(fabs(pifDWind));
    for(y=yy1;y<yy2;y++)
        for(x=xx1;x<xx2;x++){
            p=(((yy2-y)*MAXWINDSPEED / (yy2-yy1)   )<(a))?((128+(int) ( sin(y*0.55)*127)) +  (128+ (int)  (sin(y*.502)*127))*256 +  (128+ (int)  (sin(y*.401)*127))*256*256  ):(0);
            
            putpixel(screen,x,y,p);
        
        }   




    xx1=x1+(x2-x1)/3;
    xx2=x1+2*(x2-x1)/3;
    yy1=y1;
    yy2=y2;
    a=findScaleSpeed(fabs(pifDScale));
    for(y=yy1;y<yy2;y++)
        for(x=xx1;x<xx2;x++){
            p=((yy2-y)*MAXSCALESPEED/(yy2-yy1)<a)?((128+(int) ( sin(y*0.403)*127)) +  (128+ (int)  (sin(y*.502)*127))*256 +  (128+ (int)  (sin(y*.301)*127))*256*256  ):(0);
            
            putpixel(screen,x,y,p);
        
        }   
    xx1=x1+2*(x2-x1)/3;
    xx2=x2;
    yy1=y1;
    yy2=y2;
    
    a=findAngleSpeed(fabs(pifDAngle));
    for(y=yy1;y<yy2;y++)
        for(x=xx1;x<xx2;x++){
            p=((yy2-y)*MAXANGLESPEED/(yy2-yy1)<a)?((128+(int) ( sin(y*0.5)*127)) +  (128+ (int)  (sin(y*.602)*127))*256 +  (128+ (int)  (sin(y*.501)*127))*256*256  ):(0);
            
            putpixel(screen,x,y,p);
        
        }   


    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);
}


void drawFraq(int x1,int y1,int x2,int y2,int deep,SDL_Surface*screen,Uint32 color){
    int xx1,xx2,yy1,yy2,xx,yy;
    
    if(deep==0)
        return;
        
    xx=(x2-x1)/3;
    yy=(y2-y1)/3;
    xx1=(x1+x1+x1+x2)/4;
    xx2=(x1+x2+x2+x2)/4;
    yy1=(y1+y1+y1+y2)/4;
    yy2=(y1+y2+y2+y2)/4;
    
    
    drawLine(screen,x1,y1,x2,y2,color);
    
    if(x1==x2){
        drawFraq(x1-yy,yy1,x1+yy,yy1,deep-1,screen,color);
        drawFraq(x1-yy,yy2,x1+yy,yy2,deep-1,screen,color);
    }else{
        drawFraq(xx1,y1-xx,xx1,y1+xx,deep-1,screen,color);
        drawFraq(xx2,y1-xx,xx2,y1+xx,deep-1,screen,color);
    }
 

}


Uint32 getSoundKoefsColor(int i,double old){
    struct rgb c;
    struct hsv_colour hsv_c; 
    struct rgb_colour rgb_c;
  
    
    
    
    
       hsv_c.v=(1-old);
       hsv_c.h=((double)i)/KOEFNUM;
       hsv_c.s=(1-old);
       hsv2rgb(&hsv_c,&rgb_c);
       c=rgb_colour2rgb(&rgb_c);
      return *((Uint32*)&c);
}



Uint32 findDrawKoefColor(int k,double old){
    
    int i,j;
    double v;
    double summ,r,g,b;
    //struct rgb c[KOEFNUM];
    struct rgb c;
    Uint32 p;
    summ=0.;
    r=0.;
    g=0.;
    b=0.;
    for(j=0;j<KOEFNUM;j++){
        
        p=getSoundKoefsColor(j,old);
        c=*((struct rgb*)(&p));
        
        v=soundKoefs[j]*controllKoef[k*KOEFNUM+j];
        summ=summ+v;
        r=r+c.r*v;
        g=g+c.g*v;
        b=b+c.b*v;
    }
    
    r=r/summ;
    g=g/summ;
    b=b/summ;
    if(r<0.)
        r=0.;
    if(r>255.)
        r=255.;
    if(g<0.)
        g=0.;
    if(g>255.)
        g=255.;
    if(b<0.)
        b=0.;
    if(b>255.)
        b=255.;
            
    c.r=r;
    c.g=g;
    c.b=b;
    return *((Uint32*)(&c));
}

Uint32 findDrawKoefColor(int k){
    return  findDrawKoefColor(k,0);
}
double modPi(double a){
    while(a>M_PI*2){
        a=a-M_PI*2;
    }
    while(a<0.){
        a=a+M_PI*2;
    }
    
    return a;


}
void drawPannelStack(SDL_Surface*screen,int x1,int y1,int x2,int y2,int k){
    double values[ROWS];
    double *ev[ROWS];

    double controlls[ROWS];
    Uint32 colors[ROWS];
    int i,minusFlag,ttth,tttw,y;
    double max;
    int panel;
    int param;
    int noMaxDrawKoef=0;
    if(k<0){
        k=-k;
        noMaxDrawKoef=1;
        
    }
    if(rizePannel ==0)
        addButton(x1,y1,x2,y2,k,rizeBarPannel);

    
    
    panel=panel_no[curEditPannel];
    param=curEditParam;
    values[0]=noMaxDrawKoef?modPi(drawKoef[k]):drawKoef[k];
    ev[0]=maxDrawKoef+k;
    controlls[0]=noMaxDrawKoef?(2*M_PI):maxDrawKoef[k];
    colors[0]=findDrawKoefColor(k);
    values[1]=noMaxDrawKoef?modPi(zeros[k]):zeros[k];
    ev[1]=zeros+k;
    colors[1]=WHITE;
    controlls[1]=zeros[k];
    
    
    values[2]=drawLatKoef[k];
    colors[2]=0xffff00;
    controlls[2]=drawLatKoef[k];
    ev[2]=drawLatKoef+k;
    for(i=0;i<KOEFNUM;i++){
        double t;
        colors[PREGDOEFS+i]=getSoundKoefsColor(i,0);
        t=soundKoefs[i]*controllKoef[k*KOEFNUM+i];
        values[PREGDOEFS+i]=noMaxDrawKoef?modPi(t):t;
        controlls[PREGDOEFS+i]=controllKoef[k*KOEFNUM+i];
        ev[PREGDOEFS+i]=&(controllKoef[k*KOEFNUM+i]);
    }
    minusFlag=0;
    max=0.;
    for(i=0;i<ROWS;i++){
        if(controlls[i]<0.0){
            minusFlag=1;
        }
        if(fabs(controlls[i])>max){
            max=fabs(controlls[i]);
        }
    
    }
    minusFlag++;
    if(max<0.0001){
        max=0.0001;
    }
    maxPannelValue[k]=max;
    //printf("max:")
    //minusFlag=0;
    //minusFlag=minusFlag/minusFlag;
    //printf("%d %d -> %d %d : %d %d\n",x1,y1,x2,y2,tttw,ttth);
    ttth=y2-y1;
    tttw=x2-x1;
    
    for(i=0;i<ROWS;i++){
        int a,b,c,d,dd,ay;

        y=values[i]/max*ttth*(18/20.)/(minusFlag);
        ay=controlls[i]/max*ttth*(18/20.)/(minusFlag);
        
        
        a=x1 +tttw/ROWS/20 +tttw/20+ i*tttw*(18./20)/ROWS;
        b=y1 -ttth/20.  +ttth/(minusFlag);
        c=x1 +tttw/20 -tttw/ROWS/20 +(i+1)*tttw*(18./20)/ROWS;
        d=y1 -ttth/20. -y +ttth/(minusFlag);
        dd=y1-ttth/20. -ay +ttth/(minusFlag);
        
        //printf("_ABCD:(%d-%d)(%d-%d)%d %d %d %d (%f)(%f)\n",x1,y1,x2,y2,a,b,c,d,values[i],max);
        
        bar(screen,a,b,c,d,colors[i]);
        rectangle(screen,a,b,c,dd,WHITE);
        if(rizePannel ==1)
            addEValue(a,y1+ttth/10-(minusFlag-1)*ttth/10,c,y2-ttth/10-(minusFlag-1)*ttth/10,0,max/1500,-100,100,ev[i]);
        
        if(k==panel && i==param){
                rectangle(screen,a,b,c,dd,RED);

        }
    }
    y=1./max*ttth*(18/20.)/(minusFlag);
    y=y1 -ttth/20. -y +ttth/(minusFlag);
    rectangle(screen,x1+2,y,x2-2,y,WHITE);
    if(k==panel){
        rectangle(screen,x1+1,y1+1,x2-1,y2-1,RED);
    }
}


int smalstack[10];
int stackp=0;
void mypush(char a){
    if(stackp<=9)
        smalstack[stackp++]=a;
}
int mypop(){
    if(stackp>0)
        return smalstack[--stackp];
    return -100;
}
void printfStack(){
    int i;
    fprintf(stderr,"STACK:");
    
    for(i=0;i<stackp;i++)
       fprintf(stderr,"%d ",smalstack[i]);
 fprintf(stderr,";\n");
   
}
void drawFilterPannelStack(SDL_Surface*screen,int x1,int y1,int x2,int y2,int k){
    const char *order="ss2f3s2ff1ss2fs2ff";
    double values[LAYEROPTS];
    double controlls[LAYEROPTS];
   // Uint32 colors[LAYEROPTS];
    int i,ttth,tttw;
    double max;
    int panel;
    int param;
    double *ev[LAYEROPTS];
    Uint32 colors[LAYEROPTS]={GREEN,GREEN/2,0,0,0,RED,RED/2,YELLOW,YELLOW/2,MAGENTA,MAGENTA/2};
    
    panel=panel_no[curEditPannel];
    if(rizePannel ==0)
        addButton(x1,y1,x2,y2,k,rizeFilterPannel);


//    panel=pannels[k];
    param=curEditParam%LAYEROPTS;
    max=1.;
    if(max<0.0001){
        max=0.0001;
    }
    tttw=x2-x1;
    
    int deep=0;
    int mindeepy=screen->h;
    int a,sx,fx,y;

    //fprintf(stderr,"-----------------\n");
    
    for(i=0;*order;order++){
        if(*order=='s'){
            mypush(i);
            deep++;
            //fprintf(stderr,"push %d\n",i);
          //  printfStack();
        }
        if(*order>='1'&&*order<='9'){
            i+=(*order)-'0';
        //    fprintf(stderr,"add %d\n",((*order)-'0'));
      //      fprintf(stderr,"now i is %d \n",i);

        }
        if(*order=='f'){
    //        printfStack();
            a=mypop();
//            fprintf(stderr,"pop %d\n",a);
  //          fprintf(stderr,"draw it to %d\n",i);
            

            sx=x1+tttw/LAYEROPTS/20 +tttw/20 +a*tttw*(18./20)/LAYEROPTS;
            fx=x1 +tttw/20 -tttw/LAYEROPTS/20 +(i)*tttw*(18./20)/LAYEROPTS;
            y=y2-5-deep*15;
            bar(screen,sx,y-5,fx,y,BORDERCOLOR);
            if(mindeepy>y-1){
                mindeepy=y-1;
            }
            deep--;
        }
    
    }
    
    ttth=mindeepy-y1;

    for(i=0;i<LAYEROPTS;i++){
        int a,b,c,d,dd,ay;
        y=layerOpt[i]/max*ttth*(18/20.);
        ev[i]=layerOpt+i;
        
        a=x1 +tttw/LAYEROPTS/20 +tttw/20+ i*tttw*(18./20)/LAYEROPTS;
        b=y1 -ttth/20.  +ttth;
        c=x1 +tttw/20 -tttw/LAYEROPTS/20 +(i+1)*tttw*(18./20)/LAYEROPTS;
        d=y1 -ttth/20. -y +ttth;
       // dd=y1-ttth/20. -ay +ttth/(minusFlag);
        
        
        bar(screen,a,b,c,d,colors[i]);
        rectangle(screen,a,b,c,d,WHITE);
        if(rizePannel ==1)
            addEValue(a,y1,c,y2,0,0.001,0,1,ev[i]);
       // rectangle(screen,a,y1,c,y2,BLUE);
        if(k==panel && i==param){
                rectangle(screen,a,b,c,d,RED);

        }
    }
    y=1./max*ttth*(18/20.);
    y=y1 -ttth/20. -y +ttth;
    rectangle(screen,x1+2,y,x2-2,y,WHITE);
    if(k==panel){
        rectangle(screen,x1+1,y1+1,x2-1,y2-1,RED);
    }
}

void drawMaskFilter(int x1,int y1,int x2,int y2,SDL_Surface*screen){
    drawFilterPannelStack(screen,x1,y1,x2,y2,-1);

}


void drawFraqDeep(SDL_Surface*screen,int x1,int y1,int x2,int y2,int pifDeep,Uint32 color){
 if((x2-x1)/2>y2-y1){
        drawFraq((x1+x1+x1+x2)/4,y1,(x2+x1+x1+x1)/4,y2,(pifDeep<8)?pifDeep:8,screen,color);
        drawFraq((x1+x2+x2+x2)/4,y1,(x2+x2+x2+x1)/4,y2,(pifDeep-8>0)?(pifDeep-8):0,screen,color);
    }else{
        drawFraq(x1,(y1+y2)/2,(x1+x2)/2,(y1+y2)/2,(pifDeep<8)?pifDeep:8,screen,color);
        drawFraq((x1+x2)/2,(y1+y2)/2,x2,(y1+y2)/2,(pifDeep-8>0)?(pifDeep-8):0,screen,color);
    }

}


void reverceAutoPifDeep(){
    autoPifDeep=!autoPifDeep;

}
void  drawPifDeep(int x1,int y1,int x2,int y2,SDL_Surface*screen){
    int y,x;
    y=(y2+y1)/2;
    x=(x2+x1)/2;
    
    addButton(x,y1,x2,y2,0,reverceAutoPifDeep);

    drawFraqDeep(screen,x,y1,x2,y2,maxDrawKoef[0],BLUE);
    drawFraqDeep(screen,x,y1,x2,y2,drawKoef[0],VERYGREEN);
    drawFraqDeep(screen,x,y1,x2,y2,minDrawKoef[0],RED);
    drawFraqDeep(screen,x,y1,x2,y2,zeros[0],WHITE);
         
    if(!autoPifDeep){    
        drawPannelStack(screen,x1,y1,x,y,15);
        drawPannelStack(screen,x1,y,x,y2,0);
    }
 
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);				
 
 }
 

void  drawPifScale(int x1,int y1,int x2,int y2,SDL_Surface*screen){
    int y,x;
//    y=(y2+y1)/2;
  //  x=(x2+x1)/2;
    
    
/*  drawFraqDeep(screen,x,y1,x2,y2,maxDrawKoef[0],BLUE);
    drawFraqDeep(screen,x,y1,x2,y2,drawKoef[0],VERYGREEN);
    drawFraqDeep(screen,x,y1,x2,y2,minDrawKoef[0],RED);
    drawFraqDeep(screen,x,y1,x2,y2,zeros[0],WHITE);
  */       

    //drawPannelStack(screen,x1,y1,x,y,15);

    drawPannelStack(screen,x1,y1,x2,y2,4);
    
 
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);				
 
}


void  drawSpiralTransform(int x1,int y1,int x2,int y2,SDL_Surface*screen){
    int y,x;
//    y=(y2+y1)/2;
  //  x=(x2+x1)/2;
    
    
/*  drawFraqDeep(screen,x,y1,x2,y2,maxDrawKoef[0],BLUE);
    drawFraqDeep(screen,x,y1,x2,y2,drawKoef[0],VERYGREEN);
    drawFraqDeep(screen,x,y1,x2,y2,minDrawKoef[0],RED);
    drawFraqDeep(screen,x,y1,x2,y2,zeros[0],WHITE);
  */       

    //drawPannelStack(screen,x1,y1,x,y,15);

    drawPannelStack(screen,x1,y1,x2,y2,16);
    
 
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);				
 
}

void  drawMegaTransform(int x1,int y1,int x2,int y2,SDL_Surface*screen){
    int y,x;
//    y=(y2+y1)/2;
  //  x=(x2+x1)/2;
    
    
/*  drawFraqDeep(screen,x,y1,x2,y2,maxDrawKoef[0],BLUE);
    drawFraqDeep(screen,x,y1,x2,y2,drawKoef[0],VERYGREEN);
    drawFraqDeep(screen,x,y1,x2,y2,minDrawKoef[0],RED);
    drawFraqDeep(screen,x,y1,x2,y2,zeros[0],WHITE);
  */       

    //drawPannelStack(screen,x1,y1,x,y,15);

    drawPannelStack(screen,x1,y1,x2,y2,17);
    
 
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);				
 
}




void  drawSubFraqScale(int x1,int y1,int x2,int y2,SDL_Surface*screen){
    int y,x;
    drawPannelStack(screen,x1,y1,x2,y2,14);
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);				
}

void  drawSubFraqN(int x1,int y1,int x2,int y2,SDL_Surface*screen){
    int y,x;
    drawPannelStack(screen,x1,y1,x2,y2,13);
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);				
}
void  drawSubFraqValue(int x1,int y1,int x2,int y2,SDL_Surface*screen){
    int y,x;
    drawPannelStack(screen,x1,y1,x2,y2,11);
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);				
}
void  drawSubFraqAngle(int x1,int y1,int x2,int y2,SDL_Surface*screen){
       drawAnglePannelStack(screen,x1,y1,x2,y2,12);
       rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);
}


void drawSubFraqControll(int x1,int y1,int x2,int y2,SDL_Surface*screen){
    int y,x;
    y=(y2+y1)/2;
    x=(x2+x1)/2;
    drawSubFraqScale(x1,y,x,y2,screen);
    drawSubFraqN(x,y1,x2,y,screen);
    drawSubFraqValue(x,y,x2,y2,screen);
    drawSubFraqAngle(x1,y1,x,y,screen);
}
void drawPifNaked(int x1,int y1,int x2,int y2,SDL_Surface*screen){
     Uint32 c1,c2;
     if(pifNaked){
        c1=GREEN;
        c2=BLUE;
        rectangle(screen,(x1*2+x2)/3,(y1*2+y2)/3,(x2*2+x1)/3,(y2*2+y1)/3,c2);
        drawLine(screen,(x1+x2)/2,(y1+y2)/2,(x1+x2)/2,(y2*5+y1)/6,c1);     
        drawLine(screen,(x1+x2)/2,(y1+y2)/2,(x1*5+x2)/6,(y1*5+y2)/6,c1);     
        drawLine(screen,(x1+x2)/2,(y1+y2)/2,(x2*5+x1)/6,(y1*5+y2)/6,c1);     
        
     }else{
        c2=GREEN;
        c1=BLUE;

        drawLine(screen,(x1+x2)/2,(y1+y2)/2,(x1+x2)/2,(y2*2+y1)/3,c1);     
        drawLine(screen,(x1+x2)/2,(y1+y2)/2,(x1*2+x2)/3,(y1*2+y2)/3,c1);     
        drawLine(screen,(x1+x2)/2,(y1+y2)/2,(x2*2+x1)/3,(y1*2+y2)/3,c1);     

        rectangle(screen,(x1*3+x2)/4,(y1*3+y2)/4,(x2*3+x1)/4,(y2*3+y1)/4,c2);


    }
    
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);				
}



void drawPifColored(int x1,int y1,int x2,int y2,SDL_Surface*screen){
    int fx1,fx2,fy1,fy2;
    int bx1,bx2,by1,by2;
    int ay1,ay2;
    ay1=y1;
    ay2=y2;
    y1=(ay1*4+ay2)/5;
    y2=(ay1+ay2*4)/5;
    
    fx1=(x1*5+x2)/6;
    fx2=(x1+x2*3)/4;
    fy1=(y1*5+y2)/6;
    fy2=(y1+y2*3)/4;         
    bx1=(x1*3+x2)/4;
    bx2=(x1+x2*5)/6;
    by1=(y1*3+y2)/4;
    by2=(y1+y2*5)/6;
    if(!pifColored){
        bar(screen,(bx1*2+bx2)/3,(2*by1+by2)/3,(bx1+2*bx2)/3,(by1+by2*2)/3,DARKGRAY);
        
        bar(screen,fx1,fy1,(fx1+fx2)/2,(fy1+fy2)/2,RED);
        bar(screen,(fx1+fx2)/2-3,fy1+3,fx2-3,(fy1+fy2)/2+3,GREEN);
        bar(screen,fx1+4,(fy1+fy2)/2-5,(fx1+fx2)/2+4,fy2-5,BLUE);
        
        //rainbowBar(screen,fx1,fy1,fx2,fy2);
    }else{
        bar(screen,(bx1+bx2)/2-7,by1+2,bx2-7,(by2+by1)/2+2,DARKRED);
        bar(screen,(bx1+bx2)/2-4,(by1+by2)/2-8,bx2-4,by2-8,DARKGREEN);
        bar(screen,bx1+4,(by1+by2)/2+1,(bx1+bx2)/2+4,by2-1,DARKBLUE);


        //rainbowBar(screen,bx1,by1,bx2,by2);
        bar(screen,(bx1*4+bx2)/5,(4*by1+by2)/5,(bx1+4*bx2)/5,(by1+by2*4)/5,WHITE);
    }
    
    rectangle(screen,x1,ay1,x2,ay2,BORDERCOLOR);		
}


void drawPifPosition(int x1,int y1,int x2,int y2,SDL_Surface*screen){
     int xx1,yy1,xx2,yy2,cx,cy;
     double cosa,sina;
     cosa=cos(frames/700.);
     sina=sin(frames/700.);
     
     
     bar(screen,x1,y1,x2,y2,0);
     cx=(x1+x2)/2;
     cy=(y1+y2)/2;
     xx1=(x1*2+x2)/3-cx;
     xx2=(x1+x2*2)/3-cx;
     yy1=(y1*2+y2)/3-cy;
     yy2=(y1+y2*2)/3-cy;
     
     
     
     if(pifPosition){
          drawLine(screen,cx+xx1*cosa+yy2*sina,cy+yy2*cosa-xx1*sina,cx+xx2*cosa+yy2*sina,cy+yy2*cosa-xx2*sina,BLUE);
          drawLine(screen,cx+xx1*cosa+yy1*sina,cy+yy1*cosa-xx1*sina,cx+xx2*cosa+yy1*sina,cy+yy1*cosa-xx2*sina,BLUE);
          
          drawLine(screen,cx+yy1*sina,cy+yy1*cosa,cx-2*sina,cy+2*cosa,BLUE);
          drawLine(screen,cx+yy2*sina,cy+yy2*cosa,cx+2*sina,cy-2*cosa,BLUE);
          
     }else{
          drawLine(screen,cx+yy1*sina,cy+yy1*cosa,cx-2*sina,cy+2*cosa,BLUE);
          drawLine(screen,cx+yy2*sina,cy+yy2*cosa,cx+2*sina,cy-2*cosa,BLUE);


          drawLine(screen,cx+xx1*cosa+2*sina,cy+2*cosa+xx1*sina,cx+xx2*cosa-2*sina,cy+2,BLUE);
          drawLine(screen,cx+xx1*cosa-2*sina,cy-2*cosa+xx1*sina,cx+xx2*cosa+2*sina,cy-2,BLUE);
          
     
     }
     rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);

}
void drawPifSigns(int x1,int y1,int x2,int y2,SDL_Surface*screen){
    int w,s,a,i,cx,x,y;
    int dw;
    int ds;
    int da;
    if(pifDWind>0.0){
        w=1;
        dw=0;
    }else{
        w=-1;
        dw=0;//(x2-x1)/3/3;
    }
    if(pifDScale>0.0){
        s=1;
        ds=0;
    }else{
        s=-1;
        ds=0;//(y2-y1)/3/3;
    }
    if(pifDAngle>0.0){
        a=1;
        da=0;
    }else{
        a=-1;
        da=0;//-365;
    }
    cx=(x1+(x1*2+x2)/3)/2;

    for(i=0;i<(x2-x1)/3/3;i++){
        putpixel(screen,cx+i,(y1+y2)/2,(128+127*sin((w*i+dw+frames)/10))*256 );
        putpixel(screen,cx-i,(y1+y2)/2,(128+127*sin((w*i+dw+frames)/10))*256 );
    }
    
    cx=(x1+3*x2)/4;
    for(i=0;i<365;i++){
        //cx=(x1+(x1*2+x2)/3)/2;
        
        //putpixel(screen,cx,(y1+y2)/2+i,(128+127*sin((s*i+frames)/10))*256 );
        putpixel(screen,cx+2*(x2-x1)/18*cos(i*M_PI/128),(y1+y2)/2+2*(x2-x1)/18*sin(i*M_PI/128),(128+127*sin((a*i+da+frames)/10))*256 );
    
    }

    cx=(x1+x2)/2;
    for(i=0;i<(y2-y1)/3/3;i++){
        //cx=(x1+(x1*2+x2)/3)/2;
        
        putpixel(screen,cx,(y1+y2)/2+i,(128+127*sin((s*i+ds+frames)/10))*256 );
        putpixel(screen,cx,(y1+y2)/2-i,(128+127*sin((s*i+ds+frames)/10))*256 );
    
    }

  
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);
    
} 


#define VALUECOLOR 0x00ff00
void drawValueLabel(SDL_Surface*screen,double x,double y,double w,double h,double scale,double value){
    int a,b,my,i;
    double s1,s2;
    
    
    s1=value;
    s2=value;
    if(value>1/32.){
        for(a=0;s1<0.99;s1=s1*2.,a++);
        for(b=0;s2>1.11;s2=s2*2.,b++);
    }else{
        a=0;
        b=0;
    }
    my=y+h-value/scale*h;
    
    bar(screen,x,my,x+w,my,VERYGREEN);
    
    for(i=0;i<a;i++){
        bar(screen,x,my+i*2,x+w,my+i*2,VERYGREEN);
        bar(screen,x,my+i*2+1,x+w,my+i*2+1,RED);
    }
    for(i=0;i<b;i++){
        bar(screen,x,my+i*2,x+w,my+i*2,VERYGREEN);
        bar(screen,x,my+i*2+1,x+w,my+i*2+1,BLUE);
    }
    
        
    
    


}
#define M_PICOLOR 0xffffff

void drawsector(SDL_Surface*screen,double x,double y,double r,double angle,Uint32 color){
double a;
    for(a=0.;a<angle;a=a+M_PI/360.){
            drawLine(screen,x,y,x+r*cos(angle),y+r*sin(angle),color);

    }


}

void drawM_PI(SDL_Surface*screen,double x,double y,double w,double h,double scale){
    double a;
    a=M_PI*2.;
    while(a>M_PI/60.){
        if(a<scale*1.1 && a/scale>0.2){
            drawsector(screen,x+w/2,y+h-h*a/scale,2*w/3,a,M_PICOLOR);
        
        }
        a=a/2.;
    }
 
}

void  drawValue(SDL_Surface*screen,double x,double y,double w,double h,double value,double myscale,Uint32 color){
    double scale=1.;
    if(myscale<0.0){
        if(value>1/32.){
            while(value>scale)
                scale=scale*2.;
            while(value*2.<scale)
                scale=scale/2.;
        }else{
            scale=1/16.;
        }
    
    }else{
        scale=myscale;
    }
    bar(screen,x,y+h - value*h/scale -h/40. ,x+w,y+h-value*h/scale + h/40.,color);
    
  //  drawValueLabel(screen,x,y,h,w,scale,scale);
  //  drawValueLabel(screen,x,y,h,w,scale,scale/2);
  //  drawM_PI(screen,x,y,h,w,scale);
    
        


}



#define HISTORYLEN 10
double soundKoefsHistory[HISTORYLEN][KOEFNUM];
#define DRAWHISTORYLEN 10

double drawKoefHistory[DRAWHISTORYLEN][DRAWKOEFNUM];


void    drawInput(SDL_Surface*screen,double x1,double y1,double x2,double y2){
    double h,w;
    Uint32 color;
    int i,j;
    x1=x1*screen->w;
    y1=y1*screen->h;
    x2=x2*screen->w;
    y2=y2*screen->h;
    h=y2-y1;
    w=x2-x1;
    
    bar(screen,x1,y1,x2,y2,0);
    for(j=HISTORYLEN-1;j>0;j--){
        for(i=0;i<KOEFNUM;i++)
            soundKoefsHistory[j][i]=soundKoefsHistory[j-1][i];
    
    }
    
    
    for(i=0;i<KOEFNUM;i++){
        soundKoefsHistory[0][i]=soundKoefs[i];
        for(j=HISTORYLEN-1;j>=0;j--){
            color=getSoundKoefsColor(i,j/(double)HISTORYLEN);
            drawValue(screen,x1+0.1*w +i*0.8*w/KOEFNUM,y1+h*0.1,0.8*w/KOEFNUM,h*0.8,soundKoefsHistory[j][i],1,color);
        }
    
    }
    
    
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);

}  
double drawKoefScale[DRAWKOEFNUM];
void    drawOutput(SDL_Surface*screen,double x1,double y1,double x2,double y2){

    double h,w;
    Uint32 color;
    int i,j;
    x1*=screen->w;
    y1*=screen->h;
    x2*=screen->w;
    y2*=screen->h;
    h=y2-y1;
    w=x2-x1;
    
    bar(screen,x1,y1,x2,y2,0);
    for(j=DRAWHISTORYLEN-1;j>0;j--){
        for(i=0;i<DRAWKOEFNUM;i++)
            drawKoefHistory[j][i]=drawKoefHistory[j-1][i];
    
    }
    
    
    for(i=0;i<DRAWKOEFNUM;i++){
        drawKoefHistory[0][i]=drawKoef[i];
        if(drawKoefScale[i]<fabs(drawKoef[i])){
            drawKoefScale[i]=fabs(drawKoef[i]);
            
        }else{
            drawKoefScale[i]=(99*drawKoefScale[i]+drawKoef[i])/100;
        
        }
        
        if(fabs(drawKoefScale[i])<0.001){
            drawKoefScale[i]=0.001;
        }
        for(j=DRAWHISTORYLEN-1;j>=0;j--){
            color=findDrawKoefColor(i,j/(double)DRAWHISTORYLEN);
            drawValue(screen,x1+0.1*w +i*0.8*w/DRAWKOEFNUM,y1+h*0.1,0.8*w/DRAWKOEFNUM,h*0.8,drawKoefHistory[j][i]/drawKoefScale[i],1,color);
        }
    
    }
    
    
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);



}  



#include<SDL/SDL.h>
#include"graphutil.cpp"
#include"colors.cpp"

#ifndef DRAWCURRENTMOD
#define DRAWCURRENTMOD


extern double hearingVolume;
extern double amplifierKoef;
extern double amplifierKoefHighValue;
extern double amplifierKoefLowValue;
extern int currentFps;
extern Uint32 frames;



int drawAddaptiveVolumeFlag=0;
double drawAddaptiveVolumeValue=100;
void addEValue(int x1,int y1,int x2,int y2,int type,double d,double min,double max,void*ptr);
#include"mousecontroll.cpp"
void drawCurrent(SDL_Surface* screen){
    double addaptive=1.;
    double hscale=screen->h/768.;
/*    if(drawAddaptiveVolumeFlag ){
        
        addaptive=drawAddaptiveVolumeValue;
    
    }*/
    double d;
    d=-amplifierKoef/400.;
    if(d>-0.001)
        d=-0.001;
    
    addEValue(screen->w-300,0,screen->w-1,55*hscale,0,d,1,124,&amplifierKoefHighValue);
//    addEValue(x1,y1,x2,y2,1,dfaded,0,255,&faded);
//    fprintf(stderr,"%lf\n",amplifierKoefHighValue);;
    drawSqr(screen,screen->w-300,0,screen->w-1,25*hscale,VERYGREEN);
    drawSqr(screen,screen->w-300,10*hscale,screen->w-300+hearingVolume*300*addaptive,15*hscale,VERYGREEN);
    drawSqr(screen,screen->w-300,5*hscale,screen->w-300+300/amplifierKoef*addaptive,20*hscale,VERYGREEN);

    bar(screen,screen->w-300+300/amplifierKoefHighValue*addaptive -2 ,11*hscale,
    screen->w-300+300/amplifierKoefHighValue*addaptive +2 ,14*hscale,
    YELLOW);

    bar(screen,
    screen->w-300+300/amplifierKoefLowValue*addaptive -2 ,11*hscale,
    screen->w-300+300/amplifierKoefLowValue*addaptive +2 ,14*hscale,
    
    
    BROWN);
    
    
    
    
    
    drawSqr(screen,screen->w-300,30*hscale,screen->w-1,55*hscale,VERYGREEN);

    drawSqr(screen,screen->w-300,35*hscale,screen->w-300+currentFps*300/60,50*hscale,(currentFps>25)?VERYGREEN:((currentFps>15)?YELLOW:RED));
    
    drawSqr(screen,screen->w-300+(25)*300/60,30*hscale,screen->w-300+(25)*300/60,55*hscale,VERYGREEN);
    






}
#endif
#include "SDL/SDL.h"
//#include "SDL_opengl.h"
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
//#include "mynet.cpp"
#include "mynet.hpp"




//#include "HttpGet.h"

//"http://192.168.7.222/index.html"




/////////////////////////////////////////////////////////////////////





struct rgb{
Uint8 r,g,b,o; 
};
#define sign(a) (((a)>=0)?1:-1)


struct rgb hsv2rgb(int h,double s,double v){// h =0.. 360  s=0..1  v=0..1
    int h1;
    double x,c,m,r,g,b;    
    struct rgb res;
    c=v*s;
    h1=h / 60;
    x=c*(1-abs((h1%2) - 1));    
    switch (h1){
        case 0:r=c ; g=x ; b=0 ;break;
        case 1:r=x ; g=c ; b=0 ;break;
        case 2:r=0 ; g=c ; b=x ;break;
        case 3:r=0 ; g=x ; b=c ;break;
        case 4:r=x ; g=0 ; b=c ;break;
        case 5:r=c ; g=0 ; b=x ;break;
    }
    m=v-c;
    r+=m;
    g+=m;
    b+=m;
    res.r=r*255;
    res.g=g*255;
    res.b=b*255;
    return res;
}


unsigned int  inline getPixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    if(x<0||x>=surface->w || y<0 || y>=surface->h)
        return 0;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    unsigned int *q;
    q=(unsigned int*)p;
    return *q;
}
void inline putPixel(SDL_Surface *s, int x, int y, Uint32 pixel)
{
    int bpp = s->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    if(x<0||x>=s->w || y<0 || y>=s->h)
        return;
    
    Uint8 *p = (Uint8 *)s->pixels + y * s->pitch + x * bpp;
    *(Uint32 *)p = pixel;
    
}
void drawLine(SDL_Surface *sc,int x1, int y1, int x2, int y2,int c) {
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
    
    putPixel(sc, x2, y2, c);
    while(x1 != x2 || y1 != y2) {
        putPixel(sc,x1, y1,c);
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
int mx,my,mflag;

int readKey(){
   SDL_Event event;
   char buf[128];
   if(SDL_PollEvent(&event)){
        if(event.type ==  SDL_MOUSEBUTTONDOWN){
            mx=event.button.x;
            my=event.button.y;
            mflag=1;
            
            sprintf(buf,"Pressed %d %d\n",mx,my);
            mySend(buf);
            
            
        }
        if(event.type ==  SDL_MOUSEMOTION){
            if(event.motion.state & SDL_BUTTON(1)){
                mx=event.motion.x;
                my=event.motion.y;
                mflag=1;
            }
        }

        
        
        
        if(event.type == SDL_KEYDOWN) {
            return -1;
            return event.key.keysym.scancode;
        
        }
   
   }     
   return -1;
}
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
SDL_Surface* makeScreen() { 
     int H,W;
     SDL_Surface* screen = NULL;
     const SDL_VideoInfo* myPointer;
     SDL_putenv((char*)"SDL_VIDEO_WINDOW_POS=0,0");
     SDL_Init( SDL_INIT_EVERYTHING ); 
     myPointer = SDL_GetVideoInfo();
     W=myPointer->current_w;
     H=myPointer->current_h;
     screen = SDL_SetVideoMode(W , H, 32, SDL_HWSURFACE | SDL_NOFRAME | SDL_DOUBLEBUF); 
     if(screen==NULL){
        //printf("Cant create filter surface\n");
        return NULL;
     }
    
     SDL_ShowCursor(0);
    return screen;
}

SDL_Surface *cloneScreen(SDL_Surface *screen){
    const SDL_PixelFormat& fmt = *(screen->format);
  return SDL_CreateRGBSurface(screen->flags,screen->w,screen->h,
                  fmt.BitsPerPixel,
                  fmt.Rmask,fmt.Gmask,fmt.Bmask,fmt.Amask );




}




inline void circle(SDL_Surface* sc, int x, int y, int r,Uint32 color){
        int x1,y1,yk = 0;
        int sigma,delta,f;

        x1 = 0;
        y1 = r;
        delta = 2*(1-r);

        do
        {
                putPixel(sc,x+x1,y+y1,color);
                putPixel(sc,x-x1,y+y1,color);
                putPixel(sc,x+x1,y-y1,color);
                putPixel(sc,x-x1,y-y1,color);

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

int fade(SDL_Surface* source,int div){
    int x,y;
    Uint8 d;
    struct rgb *p;
    if(div==255){
        SDL_FillRect(source,NULL, 0x000000);
        return 0;
    
    }
    d=div;
    p=(struct rgb *)( ((Uint8 *)source->pixels) );
    for(y=0;y<source->h;y++,p=(struct rgb *)( ((Uint8 *)source->pixels) + y * source->pitch))
        for(x=0;x<source->w;x++,p++){
            if(p->r>d){
                p->r-=d;
            }else{
                p->r=0;            
            }
            if(p->g>d){
                p->g-=d;
            }else{
                p->g=0;            
            }
            if(p->b>d){
                p->b-=d;
            }else{
                p->b=0;            
            }
        
        }


}

#define WHITE 0xffffff
#define PINK 0xffA0A0
#define BLUE 0x4040ff
#define MAXDROPS 1000
struct drop{
    int x,y,r,death,startDeath;
    
}rain[MAXDROPS];




void addDrop(SDL_Surface*screen,double d){
    int i;
    if(mflag){
            for(i = 0;i<MAXDROPS;i++){
                    if (rain[i].r == -1){
                        rain[i].x = mx;
                        rain[i].y = my;
                        rain[i].death = 60 + rand()%150;
                        rain[i].startDeath=rain[i].death;
        //                return;
                        mflag=0;
                        break;
                    }
            }
   
    }
    return;
    //0..1 
    while(d>0.5){
        if(rand()%2){
                for(i = 0;i<MAXDROPS;i++){
                    if (rain[i].r == -1){
                        rain[i].x = rand()%screen->w;
                        rain[i].y = rand()%screen->h;
                        rain[i].death = 60 + rand()%150;
                        rain[i].startDeath=rain[i].death;
        //                return;
                        break;
                    }
            }
   
        }
        d=d-0.5;
    }
    if(d>0.000001){
        if(0==rand()%((int)(1./d))){
          for(i = 0;i<MAXDROPS;i++){
               if (rain[i].r == -1){
                   rain[i].x = rand()%screen->w;
                    rain[i].y = rand()%screen->h;
                    rain[i].death = 60 + rand()%150;
                    rain[i].startDeath=rain[i].death;
                    break;
                 }
            }
        }
    }
}

void makeMove(){
    int i;
    for(i=0;i<MAXDROPS;i++){
        if (rain[i].death>0){
            rain[i].death--;
            rain[i].r = rain[i].r +2;;
            if (rain[i].death == 0)
                rain[i].r = -1;
        }
    } 
}

void drawDrops(SDL_Surface*screen){
    int i;
    for(i = 0;i<MAXDROPS;i++){
        Uint32 c;
        if(rain[i].r != -1){
        
            c = rain[i].death*(0x0000ff)/rain[i].startDeath;
            circle(screen,rain[i].x,rain[i].y,rain[i].r,c);
        }
    }
}

int main(int argc, char *argv[]){
    SDL_Surface*screen;
    screen = makeScreen();
    if (screen == NULL){
        printf("Can't init screen\n");
        return 1;
    }
    SDL_FillRect(screen,NULL, 0x000000);
    
    while(myConnect("192.168.0.48",8000,8001));
    
    
    int i;
    for(i = 0;i < MAXDROPS; i++){
       rain[i].r=-1;      
    }
    double a;
    a=0.;
    while(readKey() < 0){
        makeMove();
        drawDrops(screen);
        SDL_Flip( screen ); 
        fade(screen,10);
//        addDrop(screen,sin(a)*30.+30.);
        addDrop(screen,(sin(a)+1.)/5.);
                      
        a=a+M_PI/180;
        
        checkRecvData();
    }
    SDL_Quit(); 
    return 0;
}

///kat-kuz@hotmail.com
#ifndef EDITPANNELSMOD
#define EDITPANNELSMOD
#include"koefs.cpp"
#define PREGDOEFS 3
#define ROWS (PREGDOEFS+(KOEFNUM))
double maxPannelValue[DRAWKOEFNUM];
#define PANNELS 14

int curEditPannel=0;
int curEditParam=0;
#define LAYEROPTS 14
double layerOpt[LAYEROPTS]={0.4,0.1,0,0,0,0.1,0.1,0,0,0.1,0,0,1,0};
int panel_no[PANNELS]={16,17,-1,14,12,11,13,0,15,3,4,8,7,5};

#endif 
/*
    Fast Fourier Transformation
    ====================================================
    Coded by Miroslav Voinarovsky, 2002
    This source is freeware.
*/
#include "fft.h"

// This array contains values from 0 to 255 with reverse bit order
static unsigned char reverse256[]= {
    0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0,
    0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0,
    0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8,
    0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8,
    0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4,
    0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4,
    0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC,
    0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC,
    0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2,
    0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2,
    0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA,
    0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA,
    0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6,
    0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6,
    0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE,
    0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE,
    0x01, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1,
    0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1,
    0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9,
    0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9,
    0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5,
    0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5,
    0x0D, 0x8D, 0x4D, 0xCD, 0x2D, 0xAD, 0x6D, 0xED,
    0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD,
    0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3,
    0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3,
    0x0B, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB,
    0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB,
    0x07, 0x87, 0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7,
    0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7,
    0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF,
    0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF,
};

//This is minimized version of type 'complex'. All operations is inline
static long double temp;
inline void operator+=(ShortComplex &x, const Complex &y)        { x.re += (double)y.re; x.im += (double)y.im; }
inline void operator-=(ShortComplex &x, const Complex &y)        { x.re -= (double)y.re; x.im -= (double)y.im; }
inline void operator*=(Complex &x,        const Complex &y)        { temp = x.re; x.re = temp * y.re - x.im * y.im; x.im = temp * y.im + x.im * y.re; }
inline void operator*=(Complex &x,        const ShortComplex &y)    { temp = x.re; x.re = temp * y.re - x.im * y.im; x.im = temp * y.im + x.im * y.re; }
inline void operator/=(ShortComplex &x, double div)                { x.re /= div; x.im /= div; }

//This is array exp(-2*pi*j/2^n) for n= 1,...,32
//exp(-2*pi*j/2^n) = Complex( cos(2*pi/2^n), -sin(2*pi/2^n) )
static Complex W2n[32]={
    {-1.00000000000000000000000000000000,  0.00000000000000000000000000000000}, // W2 calculator (copy/paste) : po, ps
    { 0.00000000000000000000000000000000, -1.00000000000000000000000000000000}, // W4: p/2=o, p/2=s
    { 0.70710678118654752440084436210485, -0.70710678118654752440084436210485}, // W8: p/4=o, p/4=s
    { 0.92387953251128675612818318939679, -0.38268343236508977172845998403040}, // p/8=o, p/8=s
    { 0.98078528040323044912618223613424, -0.19509032201612826784828486847702}, // p/16=
    { 0.99518472667219688624483695310948, -9.80171403295606019941955638886e-2}, // p/32=
    { 0.99879545620517239271477160475910, -4.90676743274180142549549769426e-2}, // p/64=
    { 0.99969881869620422011576564966617, -2.45412285229122880317345294592e-2}, // p/128=
    { 0.99992470183914454092164649119638, -1.22715382857199260794082619510e-2}, // p/256=
    { 0.99998117528260114265699043772857, -6.13588464915447535964023459037e-3}, // p/(2y9)=
    { 0.99999529380957617151158012570012, -3.06795676296597627014536549091e-3}, // p/(2y10)=
    { 0.99999882345170190992902571017153, -1.53398018628476561230369715026e-3}, // p/(2y11)=
    { 0.99999970586288221916022821773877, -7.66990318742704526938568357948e-4}, // p/(2y12)=
    { 0.99999992646571785114473148070739, -3.83495187571395589072461681181e-4}, // p/(2y13)=
    { 0.99999998161642929380834691540291, -1.91747597310703307439909561989e-4}, // p/(2y14)=
    { 0.99999999540410731289097193313961, -9.58737990959773458705172109764e-5}, // p/(2y15)=
    { 0.99999999885102682756267330779455, -4.79368996030668845490039904946e-5}, // p/(2y16)=
    { 0.99999999971275670684941397221864, -2.39684498084182187291865771650e-5}, // p/(2y17)=
    { 0.99999999992818917670977509588385, -1.19842249050697064215215615969e-5}, // p/(2y18)=
    { 0.99999999998204729417728262414778, -5.99211245264242784287971180889e-6}, // p/(2y19)=
    { 0.99999999999551182354431058417300, -2.99605622633466075045481280835e-6}, // p/(2y20)=
    { 0.99999999999887795588607701655175, -1.49802811316901122885427884615e-6}, // p/(2y21)=
    { 0.99999999999971948897151921479472, -7.49014056584715721130498566730e-7}, // p/(2y22)=
    { 0.99999999999992987224287980123973, -3.74507028292384123903169179084e-7}, // p/(2y23)=
    { 0.99999999999998246806071995015625, -1.87253514146195344868824576593e-7}, // p/(2y24)=
    { 0.99999999999999561701517998752946, -9.36267570730980827990672866808e-8}, // p/(2y25)=
    { 0.99999999999999890425379499688176, -4.68133785365490926951155181385e-8}, // p/(2y26)=
    { 0.99999999999999972606344874922040, -2.34066892682745527595054934190e-8}, // p/(2y27)=
    { 0.99999999999999993151586218730510, -1.17033446341372771812462135032e-8}, // p/(2y28)=
    { 0.99999999999999998287896554682627, -5.85167231706863869080979010083e-9}, // p/(2y29)=
    { 0.99999999999999999571974138670657, -2.92583615853431935792823046906e-9}, // p/(2y30)=
    { 0.99999999999999999892993534667664, -1.46291807926715968052953216186e-9}, // p/(2y31)=
};

/*
  x: x - array of items
  T: 1 << T = 2 power T - number of items in array
  complement: false - normal (direct) transformation, true - reverse transformation
*/
void fft(ShortComplex *x, int T, bool complement)
{
    unsigned int I, J, Nmax, N, Nd2, k, m, mpNd2, Skew;
    unsigned char *Ic = (unsigned char*) &I;
    unsigned char *Jc = (unsigned char*) &J;
    ShortComplex S;
    ShortComplex *Wstore, *Warray;
    Complex WN, W, Temp, *pWN;

    Nmax = 1 << T;

    //first interchanging
    for(I = 1; I < Nmax - 1; I++)
    {
        Jc[0] = reverse256[Ic[3]];
        Jc[1] = reverse256[Ic[2]];
        Jc[2] = reverse256[Ic[1]];
        Jc[3] = reverse256[Ic[0]];
        J >>= (32 - T);
        if (I < J)
        {
            S = x[I];
            x[I] = x[J];
            x[J] = S;
        }
    }

    //rotation multiplier array allocation
    Wstore = new ShortComplex[Nmax / 2];
    Wstore[0].re = 1.0;
    Wstore[0].im = 0.0;

    //main loop
    for(N = 2, Nd2 = 1, pWN = W2n, Skew = Nmax >> 1; N <= Nmax; Nd2 = N, N += N, pWN++, Skew >>= 1)
    {
        //WN = W(1, N) = exp(-2*pi*j/N)
       	WN= *pWN; 
        if (complement)
            WN.im = -WN.im;
        for(Warray = Wstore, k = 0; k < Nd2; k++, Warray += Skew)
        {
            if (k & 1)
            {
                W *= WN;
                *Warray = W;
            }
            else
                W = *Warray;

            for(m = k; m < Nmax; m += N)
            {
                mpNd2 = m + Nd2;
                Temp = W;
                Temp *= x[mpNd2];
                x[mpNd2] = x[m];
                x[mpNd2] -= Temp;
                x[m] += Temp;
            }
        }
    }

    delete [] Wstore;

    if (complement)
    {
        for( I = 0; I < Nmax; I++ )
            x[I] /= Nmax;
    }
}
#ifndef FRAQVERTEXMOD
#define FRAQVERTEXMOD
struct fraqVertex{
   double x,y,dx,dy;
   int ok;
}pVer[60][2][8192];

void zeroFraqVertex(){
    int i,j;
    for(i=0;i<60;i++)
        for(j=0;j<8192;j++){
            pVer[i][0][j].ok=0;
            pVer[i][1][j].ok=0;
            pVer[i][0][j].dx=0;
            pVer[i][1][j].dx=0;
            pVer[i][0][j].dy=0;
            pVer[i][1][j].dy=0;
        }

}
struct fraqVertex a_replace;
struct fraqVertex *rePlace(int nRep,int nTree,int par,double x,double y,double soft,double weight){
    
    struct fraqVertex *p;
    a_replace.ok=0;
    if(soft>1.)
        soft=1.;
    if(nRep>=0&&nRep<60&&nTree>=0&&nTree<8192&&par>=0&&par<2){
        p=&(pVer[nRep][par][nTree]);
    }else{
        p=&a_replace;
    }
    if(p->ok){
       /* if(soft<0.00001){
            p->x=x;
            p->y=y;            
        }else*/
        if(weight<0.001){
            p->x=x*(1.-soft)+p->x*soft;
            p->y=y*(1.-soft)+p->y*soft;
        }else{
            double dx,dy;
            weight=fabs(weight);
            if(weight>1.)
                weight=1.;
            dx=(x-p->x)/2;
            dy=(y-p->y)/2;
            p->dx=p->dx*(1-soft);
            p->dy=p->dy*(1-soft);
            
            p->dx+=dx*(1-weight);
            p->dy+=dy*(1-weight);
            p->x+=p->dx;
            p->y+=p->dy;
            
        }
    }else{
        p->x=x;
        p->y=y;
        p->ok=1;
    }
    return p;
}

#endif
#define MAXPARTICLES 3000
struct  particle{
    double x,y,dx,dy;
} ps[MAXPARTICLES];

void layer2particles(SDL_Surface*sc,struct layer*l,double g,double co,double v0,double k){
    int n,i,x,y,dx,dy,a,v,b;
    double kx,ky,f;
    kx=(l->w)/((double)sc->w);
    ky=(l->h)/((double)sc->h);
    
    n=co*MAXPARTICLES;
    if(n>MAXPARTICLES){
        n=MAXPARTICLES;
    }
    for(i=0;i<n;i++){
        x=round(ps[i].x *kx);
        y=round(ps[i].y *ky);
        b=x+y*l->w;
        for(dx=-1;dx<=1;dx++){
            for(dy=-1;dy<=1;dy++){
                if(!dx && !dy || x+dx<0 || x+dx>=l->w|| y+dy<0 || y+dy>=l->h || x<0 || x>=l->w|| y<0 || y>=l->h)
                    continue;
                a=x+dx+(y+dy)*l->w;
                ps[i].dx+=dx*(l->p[a]-l->p[b])*g;
                ps[i].dy+=dy*(l->p[a]-l->p[b])*g;
            }
        }
//        ps[i].dx+=(rand()%1001 - 500)/10000.;
  //      ps[i].dy+=(rand()%1001 - 500)/10000.;
        ps[i].x+=ps[i].dx;
        ps[i].y+=ps[i].dy;
        ps[i].dy*=k;
        ps[i].dx*=k;
        
        x=ps[i].x;
        y=ps[i].y;
        if( x>=0&&x<sc->w && y>=0 && y<sc->h && fabs(ps[i].dx)+fabs(ps[i].dy)>0.2){
            //circle(sc,sc->w/2,sc->h/2,10,WHITE);
            circle(sc,x,y,2,WHITE);

//            putpixel(sc,x,y,WHITE);
        }else{
            ps[i].x=rand()%sc->w;
            ps[i].y=rand()%sc->h;
            f=(rand()%1000)/500.*M_PI;
            v=v0*(rand()%1000)/1000.;
            ps[i].dx=v*cos(f);
            ps[i].dy=v*sin(f);            
        }        
    
    }

}


#ifndef GRAPHUTILMOD
#define GRAPHUTILMOD
#include"SDL/SDL.h"
double spiral=0.0;
double mega=0.0;
#include"filters/SPIRAL.cpp"
#include"filters/nosound.cpp"
#include"hsv.cpp"
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

Uint32 *_colorSeq2Buf;
int* _colorSeq2BufDy;
int* _colorSeq2BufDx;
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

void prepareSeqNo2(int deep){
    seqno2=cl->seqno3[deep];
    _colorSeq2Buf=cl->oqColorline[deep];
    _colorSeq2BufDx=cl->oqColorlineDx[deep];
    _colorSeq2BufDy=cl->oqColorlineDy[deep];


}
void prepareDefSeqNo2(){
//    seqno2=cl->seqno3[deep];
    _colorSeq2Buf=colorSeq2Buf;
    _colorSeq2BufDx=colorSeq2BufDx;
    _colorSeq2BufDy=colorSeq2BufDy;

}

void prepareOrSeqNo2(){
    seqno2=cl->orseqno3;
    _colorSeq2Buf=cl->orOqColorline;
    _colorSeq2BufDx=colorSeq2BufDx;
    _colorSeq2BufDy=colorSeq2BufDy;

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
void inline putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel){
    if(x<0||x>=surface->w||y<0||y>=surface->h)
        return;
    *((Uint32 *)surface->pixels + putPixelBufy[y] + x) = pixel;
}
void inline orpixel(SDL_Surface *surface, int x, int y, Uint32 pixel){
    if(x<0||x>=surface->w||y<0||y>=surface->h)
        return;
    *((Uint32 *)surface->pixels + putPixelBufy[y] + x) |= pixel;
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
    
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    //
    int error = deltaX - deltaY;
    //
    int dx,dy;
    colorDxy(dx,dy);
    orpixel(sc, x2+dx, y2+dy, colorSeq2());
    while(x1 != x2 || y1 != y2) {
        colorDxy(dx,dy);
    
        orpixel(sc,x1+dx, y1+dy,colorSeq2());
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
        {       color=colorSeq2();
                orpixel(sc,x+x1,y+y1,color);
                orpixel(sc,x-x1,y+y1,color);
                orpixel(sc,x+x1,y-y1,color);
                orpixel(sc,x-x1,y-y1,color);

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
//#define M_PI 3.1415926
#include"SDL/SDL.h"
#include<math.h>

#include"colors.cpp"
#include"graphutil.cpp"

#define HS 5.0 
#define HSS 6.0
#define LEAFSIZE 50

#define LEAFGROW 10
#define DISAPIRE 400


#define STARTGROW 9
#define FORK 50
#define LEAF 5
#define GROW 2

#define BARRY 1
#define BARRYSIZE 5
#define GROWCLUSTER 2
#define CLUSTEREND 5
#define CLUSTER  200
#define SHAKE 50


#define VISUAL1X 35.0
#define VISUAL1Y 50.0
#define TIMEDEVIDE1X 10.0
#define SUMTIMEDEVIDE1X 30.0
#define TIMEDEVIDE1Y 10.0
#define SUMTIMEDEVIDE1Y 100.0
#define CHECKNEWSPROUT 100

#define NEWSPROUT   5
 
#define BERRYBURST 50000
#define BURSTTIME    1000
#define BURSTMINTIME 100
#define BURSTSIZE 200
#define GRAVITY 0.6
#define SWING .3
#define SWINGPERIOD 20
#define WINDCHANGE 1000
#define MAXWIND   2.0




#define CHILDTIMESTEP .3



#define TIMEDEVIDE2X 10.0
#define SUMTIMEDEVIDE2X 15.0
#define TIMEDEVIDE2Y 4.0
#define SUMTIMEDEVIDE2Y 10.0
#define VISUAL2X 25.0
#define VISUAL2Y 5.0
#define FADE 100 
double h_time;

double wind=0;
struct grow{
   unsigned int id;
   int weight;
   int fade;
   double x1,y1,x2,y2,a,da,dda,ph,r;//x1,y1,x2,y2 -координаты начала и конца, a - текущее изменения угла роста, ph - возраст
   int state;// 0 - росток, 1 - палочка, 2 - гроздь, 3 - листик, 4 - ягодка 
   int burst;
struct grow*next;
}*root;
unsigned int growid;


#define hashSize  1000
unsigned int fade(unsigned int color,unsigned int fade){
    unsigned int r,g,b;
    if(fade==0)
        return color;
    r=color & 255;
    g=(color / 256) & 255; 
    b=(color / 256 / 256) &255;
    if(fade>FADE)
        fade=FADE;
    r=r*(FADE-fade)/FADE;
    g=g*(FADE-fade)/FADE;
    b=b*(FADE-fade)/FADE;
    return r |  (g*256)  | (b*256*256);
 }
int hash(int id){
    return id % hashSize;
}
struct hash{
    int id;
    int flag;
    int count;
    int minweight;
    struct hash*next;

} *table[hashSize];



void zerroTable(){
    int i;
    for(i=0;i<hashSize;i++){
        table[i]=NULL;
    }
}
void freeTable(){
    int i;
    for(i=0;i<hashSize;i++){
        if(table[i]!=NULL){
            free(table[i]);        
            table[i]=NULL;
        }
    }
    
}

int getHashFlag(int id){
    int h;
    struct hash*p;
    h=hash(id);
    p=table[h];
    while(p){
        if(p->id==id)
            return p->flag;
        p=p->next;
    }
    
    return 0;
}

int getHashMinWeight(int id){
    int h;
    struct hash*p;
    h=hash(id);
    p=table[h];
    while(p){
        if(p->id==id)
            return p->minweight;
        p=p->next;
    }
    
    return 0;
}
int getHashCount(int id){
    int h;
    struct hash*p;
    h=hash(id);
    p=table[h];
    while(p){
        if(p->id==id)
            return p->count;
        p=p->next;
    }
    
    return 0;
}

void setHashFlag(int id,int flag){
    int h;
    struct hash*p;
    h=hash(id);
    p=table[h];
    while(p){
        if(p->id==id){
            p->flag=flag;
            return;
        }
        p=p->next;
    }
    p=(struct hash*)malloc(sizeof(struct hash));
    if(p!=NULL){
        p->id=id;
        p->flag=flag;
        p->count=0;
        p->minweight=0;
        p->next=table[h];
        table[h]=p;
    }else{
        printf("Memory error\n");    
    
    }
}

void countHash(int id,int weight){
    int h;
    struct hash*p;
    h=hash(id);
    p=table[h];
    while(p){
        if(p->id==id){
            if(p->minweight > weight){
                p->minweight=weight;
            }
            p->count++;
            return;
        }
        p=p->next;
    }
    p=(struct hash*)malloc(sizeof(struct hash));
    if(p!=NULL){
        p->id=id;
        p->flag=0;
        p->count=1;
        p->minweight=weight;
        p->next=table[h];
        table[h]=p;
    }else{
        printf("Memory error\n");    
    
    }
}


char *space;
unsigned int *sumspace;

int h_h,h_w;

void h_line(SDL_Surface *sc,int x1, int y1, int x2, int y2,int c){
      drawLine(sc,x1,y1,x2,y2,c);
}
void setSpacePixel(int x,int y){
    if(x>=0 && x< h_w && y>=0 && y<h_w )
        space[x+y*h_w]=1;
}


double xvisual(struct grow *p){
    return cos((p->ph+h_time/TIMEDEVIDE1X)/SUMTIMEDEVIDE1X)*VISUAL1X+cos((p->ph+h_time/TIMEDEVIDE2X)/SUMTIMEDEVIDE2X)*VISUAL2X;

}
double yvisual(struct grow *p){
    return sin((p->ph+h_time/TIMEDEVIDE1Y)/SUMTIMEDEVIDE1Y)*VISUAL1Y+sin((p->ph+h_time/TIMEDEVIDE2Y)/SUMTIMEDEVIDE2Y)*VISUAL2Y;

}


int getSpacePixel(int x,int y){
    return space[x+y*h_w];
}
int check_h_spaceLine(int x1,int y1,int x2,int y2){
    x1/=5;
    x2/=5;
    y1/=5;
    y2/=5;
    if(x1<0)
        return 1;
    if(x1>=h_w)
        return 1;
        
    if(x2<0)
     return 1;
    if(x2>=h_w)
        return 1;
        
    if(y1<0)
    return 1;
    if(y1>=h_h)
        return 1;
        
    if(y2<0)
     return 1;
    if(y2>=h_h)
        return 1;
        
    
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    //
    int error = deltaX - deltaY;
    //
    if(getSpacePixel(x2, y2))
        return 1;
    while(x1 != x2 || y1 != y2) {
        if(getSpacePixel(x1, y1))
            return 1;
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
    return 0;
}

int checkSpace(struct grow*p){
    if(p->state == 3){ // ЛИСТ
        double dx,dy;
        int l;
        dx=p->x2-p->x1;
        dy=p->y2-p->y1;
        l=sqrt(dx*dx+dy*dy) +0.9;
        if(p->x1 < 5+l || p->x1 > h_w * 5 -5 -l
                            ||
           p->y1 < 5+l || p->y1 > h_h * 5 -5 -l
           ||
           p->x2 < 5+l || p->x2 > h_w * 5 -5 -l
                ||
                           p->y2 < 5+l || p->y2 > h_h * 5 -5 -l
        
         )
         return 1;
    
    }

    if(check_h_spaceLine(p->x2+ cos(p->a)*HS,p->y2 + sin(p->a)*HS,p->x2 + cos(p->a)*HSS,p->y2 + sin(p->a)*HSS))
        return 0;
    return 1;

 
}
int check_h_spaceCircle(int x2,int y2,int r){

    int x,y,rr;
    x2=(x2+2)/5;
    y2=(y2+2)/5;
    r=(r+2)/5;
    for(x=x2-r;x<=x2+r;x++)
        for(y=y2-r;y<=y2+r;y++){
        rr=((x-x2)*(x-x2)+(y-y2)*(y-y2));
            if(rr<=r*r){
                if(x>=0&&x<h_w&&y>=0&&y<h_h)
                    if(getSpacePixel(x,y)){
                        return 1;
                    
                    }            
            }
        
        }
        return 0;

}
void h_spaceCircle(int x2,int y2,int r){

    int x,y,rr;
    x2=(x2+2)/5;
    y2=(y2+2)/5;
    r=(r+2)/5;
    for(x=x2-r;x<=x2+r;x++)
        for(y=y2-r;y<=y2+r;y++){
        rr=sqrt((x-x2)*(x-x2)+(y-y2)*(y-y2));
            if(rr<=r){
                if(x>=0&&x<h_w&&y>=0&&y<h_h)
                    setSpacePixel(x,y);
            }
        
        }
        
}



int checkBerrySpace(struct grow*p){       
   
    if(check_h_spaceCircle(p->x1+xvisual(p),p->y1+yvisual(p),p->r))
        return 0;
    return 1;

 
}
void h_spaceLine(int x1,int y1,int x2,int y2){
    x1/=5;
    x2/=5;
    y1/=5;
    y2/=5;
    if(x1<0)
     x1=0;
    if(x1>=h_w)
        x1=h_w-1;
        
    if(x2<0)
     x2=0;
    if(x2>=h_w)
        x2=h_w-1;
        
    if(y1<0)
     y1=0;
    if(y1>=h_h)
        y1=h_h-1;
        
    if(y2<0)
     y2=0;
    if(y2>=h_h)
        y2=h_h-1;
        
    
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    //
    int error = deltaX - deltaY;
    //
    setSpacePixel(x2, y2);
    while(x1 != x2 || y1 != y2) {
        setSpacePixel(x1, y1);
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


void   drawSprout(SDL_Surface *screen,struct grow *p){
    h_line(screen,p->x1+xvisual(p),p->y1+yvisual(p),p->x2+xvisual(p),p->y2+yvisual(p),WHITE);
    h_spaceLine(p->x1,p->y1,p->x2,p->y2);
}

void   drawStick(SDL_Surface *screen,struct grow *p){
    int weight,i;
    weight=p->weight - getHashMinWeight(p->id);
    if(weight<0)
        weight=0;
    
    weight=log(weight*4);

    if(weight<1)
        weight=1;
    
    
    h_line(screen,p->x1+xvisual(p) ,p->y1+yvisual(p)   ,p->x2+xvisual(p)  ,p->y2+yvisual(p) ,fade(YELLOW,p->fade));
    
     h_line(screen,p->x1+xvisual(p) + weight*(p->id & 1) ,p->y1+yvisual(p)  + weight*(1 - p->id & 1),p->x2+xvisual(p) + weight*( p->id & 1),p->y2+yvisual(p)+ weight*(1 - p->id & 1),fade(YELLOW,p->fade));
    for(i=0;i<weight;i++){
       // h_line(screen,p->x1+xvisual(p) + i*(p->id & 1) ,p->y1+yvisual(p)  + i*(1 - p->id & 1),p->x2+xvisual(p) + i*( p->id & 1),p->y2+yvisual(p)+ i*(1 - p->id & 1),fade(YELLOW,p->fade));
        
        h_spaceLine(p->x1 +  i*(p->id & 1),p->y1+ i*(1 - p->id & 1),p->x2 + i*(p->id & 1),p->y2+ i*(1 - p->id & 1));
    }
}




void putLeaf(SDL_Surface *screen,int x1,int y1,int x2,int y2,int myfade){  
        int i,dx,dy,xx,yy;
        double a,cosa,sina,d;
        dx=x2 - x1;
        dy=y2 - y1;
        a=atan2(dy,dx);
        a-=M_PI/2;
        cosa=cos(a);
        sina=sin(a);
        
        for(i=0;i<LEAFSIZE;i++){
            xx=x1+dx*i/LEAFSIZE;
            yy=y1+dy*i/LEAFSIZE;
            if(i<LEAFSIZE/2)
              d=sqrt(i);
            else
              d=sqrt(LEAFSIZE-i);
           
           
            h_line(screen,xx,yy,xx+cosa*d,yy+sina*d,fade(GREEN,myfade));
        }
}

void putLeaf2(SDL_Surface *screen,double x1,double y1,double x2,double y2,int myfade){  
        int i,LS;
        double dx,dy,xx,yy;
        double a,cosa,sina,d,h1,h2,t,ls;
        //return ;
        dx=x2 - x1;
        dy=y2 - y1;
        a=atan2(dy,dx);
        ls=sqrt(dx*dx+dy*dy);
        LS=ls+1;
        a-=M_PI/2;
        cosa=cos(a);
        sina=sin(a);
        
        for(i=0;i<LS*1;i++){
            xx=x1+dx*i/1.0/ls;
            yy=y1+dy*i/1.0/ls;
            
            t = i*3.14*3.14/ls/1.0;
            h1 = sin(sqrt(t)) * ls/3.0;
            h2 = -sin(sqrt(2.0*t))/(1.0 + t*2) * ls/3.0;
           
           setPixel(screen,xx+h2*cosa,yy+h2*sina,fade(GREEN,myfade));
           setPixel(screen,xx+h1*cosa,yy+h1*sina,fade(GREEN,myfade));
           
          // h_line(screen,xx+h2*cosa,yy+h2*sina,xx+h1*cosa,yy+h1*sina,fade(GREEN,myfade));
        }
}



void   drawLeaf(SDL_Surface *screen,struct grow *p){
   
    putLeaf2(screen,p->x1+xvisual(p),p->y1+yvisual(p),p->x2+xvisual(p),p->y2+yvisual(p),p->fade);
    
   
   
    h_spaceLine(p->x1,p->y1,p->x2,p->y2);
}

void h_Circle(SDL_Surface *screen,int x2,int y2,int r,int c){

    int x,y,rr;
    r*=r;
    for(x=x2-r;x<=x2+r;x++)
        for(y=y2-r;y<=y2+r;y++){
        rr=((x-x2)*(x-x2)+(y-y2)*(y-y2));
            if(rr <=r){
                if(x>=0&&x<screen->w&&y>=0&&y<screen->h && viewPixel(screen,x,y) == 0  )
                    putpixel(screen,x,y, c);            
            }
        
        }

}

void   drawBerry(SDL_Surface *screen,struct grow *p){
    int dr;
    dr=0;
   
    if(p->burst>0){
        dr=SHAKE*fabs(sin(sqrt(p->burst)))/ sqrt(sqrt(p->burst));
    }
    
    h_Circle(screen,p->x1+xvisual(p),p->y1+yvisual(p),p->r+dr,fade(RED,p->fade));
    
   // if(check_h_spaceCircle(p->x1+xvisual(p),p->y1+yvisual(p),p->r+dr) && p->burst<1.0){
     //   p->burst=200;  
    
   // }
    h_spaceCircle(p->x1+xvisual(p),p->y1+yvisual(p),p->r+dr);
    //h_spaceCircle(p->x1,p->y1,p->x2,p->y2);
}

void   drawBurst(SDL_Surface *screen,struct grow *p){
    if(p->r>4)
        h_Circle(screen,p->x1+xvisual(p),p->y1+yvisual(p),p->r,fade(WHITE,p->fade));
    
}

unsigned int inline getR(unsigned int c){
    return c&255;
}
unsigned int inline getG(unsigned int c){
    return (c/256)&255;
}
unsigned int inline getB(unsigned int c){
    return (c/256/256)&255;
}
unsigned int inline getC(unsigned int r,unsigned int g,unsigned int b){
    if(r>255)
        r=255;
    if(g>=255)
        g=255;
    if(b>255)
        b=255;
    return r | (g*256) | (b*256*256);

}



void   	smooth(SDL_Surface* screen ){
    //int rdx,rdy,gdx,gdy
    int x,y,i,j,a;
    unsigned int c,r,g,b;
    unsigned int *p;
    int bpp = screen->format->BytesPerPixel;
    int pitch = screen->pitch/bpp;
    int matrix[9]={ 1,2,1,
                       2,4,2,
                       1,2,1};//16
    for(y=1,p=((unsigned int *)screen->pixels)+pitch;y<screen->h-1;y++,p+=pitch - screen->w+1)
        for(x=1,p++;x<screen->w-1;x++,p++)
        {
            r=0;
            g=0;
            b=0;
            for(i=-1,a=0;i<=1;i++)
                for(j=-1;j<=1;j++,a++){
                    c=*(p+i+j*pitch);
                    r+=getR(c)*matrix[a];    
                    g+=getG(c)*matrix[a];    
                    b+=getB(c)*matrix[a];    
                }
            r/=16;
            g/=16;
            b/=16;
            c=getC(r,g,b);
            *p=c;
        
        }



}




void drawHohloma(SDL_Surface* screen){

    struct grow *p;
    
 //   SDL_FillRect(screen,NULL, 0x000000); 
    
    if(space!=NULL)
     memset(space,0,h_h*h_w);
    h_time+=1;
    for(p=root;p!=NULL;p=p->next){
        if(p->state==0){
            drawSprout(screen,p);
        }
        if(p->state==1){
            drawStick(screen,p);
        }
        if(p->state==3){
            drawLeaf(screen,p);
        }
        if(p->state==4){
            drawBerry(screen,p);
            
        }
        if(p->state==5){
            drawBurst(screen,p);
        }
    }    
  	
 
  	//postProcess( screen );
  //	printf("Hello\n");
	//fflush(stdout);

  //	SDL_GL_SwapBuffers();
  	//SDL_Flip( screen ); 
  	//SDL_UpdateRect(screen, 0, 0, 0, 0)  ;
}


int checkSumSpace(int x, int y){
    int s,i,j;
    s=0;
    for(i=x-3;i<x+4;i++){
        for(j=y-3;j<y+4;j++){
            if(i>=0&&i<h_w&&j>=0&&j<h_h){
                s+=sumspace[i+j*h_w];
            }
        }
    }

    return s;
}
void     checkPostBurst(){
    grow *tmp,*p,*parrent;
    while(root != NULL && root->state==5 && root->r < 5){
        p=root->next;
       // printf("free root %d\n",root->id);
        free(root);
        root=p;
   }
   parrent=root;
   while(parrent!=NULL && parrent->next != NULL){
        if(parrent->next->state==5 && parrent->next->r < 5){
           // printf("free %d\n",parrent->next->id);
            tmp=parrent->next->next;
            free(parrent->next);
            parrent->next=tmp;
            
        }else{
            parrent = parrent->next;
        }
    }
}
void     distructBurst(int x,int y,double r){
    grow *tmp,*p,*parrent;
    while(root != NULL && root->state!=5 && (root->x1-x)*(root->x1-x)+ (root->y1-y)*(root->y1-y)<r*r){
        p=root->next;
       // printf("free root %d\n",root->id);
        free(root);
        root=p;
   }
   parrent=root;
   while(parrent!=NULL && parrent->next != NULL){
        if(parrent->next->state!=5 && parrent->next->state!=5 && (parrent->next->x1-x)*(parrent->next->x1-x)+ (parrent->next->y1-y)*(parrent->next->y1-y)<r*r){
           // printf("free %d\n",parrent->next->id);
            tmp=parrent->next->next;
            free(parrent->next);
            parrent->next=tmp;
            
        }else{
            parrent = parrent->next;
        }
    }
}

void burst(int x,int y,double ph){
   struct grow*p,*newroot,*pnext;
   double r;
   p=(struct grow*)malloc(sizeof(struct grow));
   if(p!=NULL){
       p->x1=x;
       p->y1=y;
       p->ph=ph;
       r=rand()%BURSTSIZE;
       p->r=r;
       p->ph=ph;
       p->state=5;//ВЗРЫВ
       p->next=root;
       p->id=0;
       p->weight=0;
       p->fade=0;
       root=p;
                     
   }
/*   newroot=NULL;
   for(p=root;p!=NULL;p=pnext){
        if(p->state!=5 && (p->x1-x)*(p->x1-x)+ (p->y1-y)*(p->y1-y)<r*r){
            pnext=p->next;
            free(p);
        }else{
            pnext=p->next;
            p->next=newroot;
            newroot=p;        
        }
   
   }
   root=newroot;
 */  
     distructBurst(x,y,r);
}


/*

void     checkPostBurst(grow ** p){
grow *tmp;  
   // return;
    while(*p != NULL){
        if((*p)->state==5 && (*p)->r < 5){
            tmp=(*p)->next;
            (*p)->state=6;
            free(*p);
            *p=tmp;
        }else{
            p = & ((*p)->next);
        }
    }
}


*/

void moveHohloma(){
    struct grow *addon,*p,*q,*newroot,*pnext;
    int forksign,x,y,s,sm,sx,sy;
    addon=NULL;
    freeTable();
    for(x=0;x<h_w;x++){
        for(y=0;y<h_h;y++){
            if(!getSpacePixel(x,y)){
                if(!(rand()%NEWSPROUT)){
                    sumspace[x+y*h_w]++;    
                }        
            }else{
                sumspace[x+y*h_w]=0;
            
            }
        }
    }
    
    
    if(!(rand()%CHECKNEWSPROUT)){
       
        sm=-32000;
        for(x=0;x<h_w;x++){
            for(y=0;y<h_h;y++){
                s=checkSumSpace(x,y);
                if(s>sm){
                    sm=s;
                    sx=x;
                    sy=y;
                }
        
            }
        }
        if(sm>0){
             p=(struct grow*)malloc(sizeof(struct grow));
             if(p!=NULL){
                 double a,da,dda;
                 a=((rand()%1000)/1000.0)*2.0*M_PI;
                 da=((rand()%1000)/50000.0)*M_PI;
                 dda=((rand()%1000)/2500000.0)*2.0*M_PI;
                 p->id=growid++;
                 p->x1=sx*5+2;
                 p->y1=sy*5+2;
                 p->x2=sx*5+2+cos(a)*HS;
                 p->y2=sy*5+2+sin(a)*HS;
                 p->a=a;
                 p->da=da;
                 p->dda=dda;
                 p->ph=0;
                 p->burst=0;
                 p->state=0;
                 p->weight=0;
                 p->fade=0;
        
        
                 p->next=root;
                 root=p;
                if(sumspace!=NULL)
                    memset(sumspace,0,h_h*h_w*sizeof(unsigned int));  
                 
              }        
        
        }
    }
    
  // newroot=NULL;
  int minid= -1 ;
   for(p=root;p!=NULL;p=p->next){
        if(minid==-1 || minid> p->id){
            minid=p->id;
        }
        countHash(p->id,p->weight);
        if(p->state==0){//Росток
            setHashFlag(p->id,2);        
        }
        
        
    /*    if(p->state==5 && p->r < 5){
            pnext=p->next;
            free(p);
        }else{
            pnext=p->next;
            p->next=newroot;
            newroot=p;        
        }
   */
   }
  
  if(!(rand()%DISAPIRE)){
    if(minid!=-1){
        for(p=root;p!=NULL;p=p->next){
            if(p->id == minid){
                p->burst=-1;   
            
            }
        }
    
    }  
  
  
  }
  
  //root=newroot;
   
    checkPostBurst();
    
    
    
   
   
    for(p=root;p!=NULL;p=p->next){
        if(p->state!=5 && (getHashFlag(p->id)!=2/* &&  (growid -  p->id > 10  || growid < p->id) */ ) && getHashCount(p->id)<150){
            p->burst=-1;

        }
        if(p->burst==-1){
            //p->y1+=GRAVITY;
            //p->y2+=GRAVITY;
            p->fade++;
           //p->x1+=wind+SWING*cos((p->ph+h_time)/SWINGPERIOD);
           //p->x2+=wind+SWING*cos((p->ph+h_time)/SWINGPERIOD);
           if(p->fade>=FADE||p->y1>h_h*5 && p->y2 > h_h*5){
            p->state=5;
            p->r=3;
        } 
        }
        
        
        
        if(p->state==5){//Взрыв
            p->r=p->r*0.8;
            
        }
        
        if(p->state==3){//ЛИСТ
            double dx,dy,sz,a,x2,y2;
            if(!(rand()%LEAFGROW)){
                dx = p->x2 - p->x1;
                dy = p->y2 - p->y1;
                sz = sqrt(dx*dx + dy* dy);
                if(sz>0.1){
                    a=atan2(dy,dx);
                    if(sz < LEAFSIZE){
                        sz*=1.04;
                        x2=p->x2;
                        y2=p->y2;
                        p->x2=p->x1+sz*cos(a);
                        p->y2=p->y1+sz*sin(a);               
                        if(!checkSpace(p)){
                            p->x2=x2;
                            p->y2=y2;
                        }
                    }
                }
            }
        }
        
        if(p->state==4){//Ягода
            if(p->burst>1){
                p->burst--;
            }else if(p->burst==1){
                    burst(p->x1,p->y1,p->ph);
                    break;            
            
            }else if(!(rand()%BERRYBURST)){
                p->burst=BURSTMINTIME+rand()%BURSTTIME;
                printf("BERRYBURST %d\n",p->burst);
            
            }
            
        
        }
        if(p->state==2){///Гроздь
          if(!(rand()%GROWCLUSTER)){
                p->state=1;
                if((rand()%CLUSTEREND)){
                    q=(struct grow*)malloc(sizeof(struct grow));/// растём линейно
                    if(q==NULL)
                       continue;
                    q->id=p->id;
                    q->x1=p->x2;
                    q->y1=p->y2;
                    q->a=p->a+p->da;
                    q->da=p->da+p->dda;
                    q->dda=p->dda;
                    q->burst=0;
                    q->x2=q->x1+cos(q->a)*HS;
                    q->y2=q->y1+sin(q->a)*HS;
                    q->ph=p->ph+CHILDTIMESTEP;
                    q->state=2;
                    q->weight=p->weight-1;
                    q->next=addon;
                    q->fade=p->fade;
                    if(checkSpace(q)){
                          addon=q;            
                    }else{
                        free(q);            
                    }  
                 }
                 if(!(rand()%BARRY)){
                    q=(struct grow*)malloc(sizeof(struct grow));/// Ягодка
                    if(q==NULL)
                        continue;
                    q->id=p->id;
                    forksign=1-2*(rand()%2); //1 или -1;
                    q->a=p->a+M_PI/2.0*forksign;
                    q->x1=p->x2+cos(q->a)*BARRYSIZE;
                    q->y1=p->y2+sin(q->a)*BARRYSIZE;

                    q->da=forksign*p->da;
                    q->r=BARRYSIZE;
                    q->burst=0;
                    q->ph=p->ph+CHILDTIMESTEP;
                    q->state=4;
                    q->next=addon;
                    q->weight=p->weight-1;
                    q->fade=p->fade;
                    if(checkBerrySpace(q)){
                        addon=q;            
                    }else{
                        free(q);            
                    }    
                 }
                 
                
                 
                 
          
          }          
        
        }
        
        if(p->state==0){// Росток
            if(!(rand()%GROW)){
                p->state=1;
                q=(struct grow*)malloc(sizeof(struct grow));/// растём линейно
                if(q==NULL)
                    continue;
                q->id=p->id;;
                q->x1=p->x2;
                q->y1=p->y2;
                q->a=p->a+p->da;
                q->da=p->da+p->dda;
                q->dda=p->dda;
                q->burst=0;
                q->x2=q->x1+cos(q->a)*HS;
                q->y2=q->y1+sin(q->a)*HS;
                q->ph=p->ph+CHILDTIMESTEP;
                q->state=0;
                q->weight=p->weight-1;
                q->next=addon;
                q->fade=p->fade;
                if(checkSpace(q)){
                        addon=q;            
                }else{
                    free(q);            
                }
                if(!(rand()%CLUSTER)){
                    q=(struct grow*)malloc(sizeof(struct grow));/// порождаем ветку
                    if(q==NULL)
                        continue;
                    q->id=p->id;;
                    forksign=1-2*(rand()%2); //1 или -1;
                    q->x1=p->x2;
                    q->y1=p->y2;
                    q->a=p->a+M_PI/6.0*forksign;
                    q->da=forksign*p->da;
                    q->dda=((rand()%1000)/2500000.0)*2.0*M_PI;
                    q->x2=q->x1+cos(q->a)*HS;
                    q->y2=q->y1+sin(q->a)*HS;
                    q->ph=p->ph+CHILDTIMESTEP;
                    q->state=2;
                    q->burst=0;
                    q->weight=p->weight-1;
                    q->next=addon;
                    q->fade=p->fade;
                    if(checkSpace(q)){
                        addon=q;            
                    }else{
                        free(q);   
                                 
                    }    
                
                }
                
                if(!(rand()%FORK)){
                    q=(struct grow*)malloc(sizeof(struct grow));/// порождаем ветку
                    if(q==NULL)
                        continue;
                    q->id=p->id;
                    forksign=1-2*(rand()%2); //1 или -1;
                    q->x1=p->x2;
                    q->y1=p->y2;
                    q->a=p->a+M_PI/6.0*forksign;
                    q->da=forksign*p->da;
                    q->dda=((rand()%1000)/2500000.0)*2.0*M_PI;
                    q->x2=q->x1+cos(q->a)*HS;
                    q->y2=q->y1+sin(q->a)*HS;
                    q->ph=p->ph+CHILDTIMESTEP;
                    q->state=0;
                    q->burst=0;
                    q->weight=p->weight-1;
                    q->next=addon;
                    q->fade=p->fade;
                    if(checkSpace(q)){
                        addon=q;            
                    }else{
                        free(q);   
                                 
                    }    
                
                }
                if(!(rand()%LEAF)){
                    double sz;
                    q=(struct grow*)malloc(sizeof(struct grow));/// порождаем ветку
                    if(q==NULL)
                        continue;
                    q->id=p->id;;
                    forksign=1-2*(rand()%2); //1 или -1;
                    q->x1=p->x2;
                    q->y1=p->y2;
                    q->a=p->a+M_PI/6.0*forksign;
                    q->da=forksign*p->da;
                    
                    sz=0.3;//((rand()%100 )/100.0) +.1;
                    q->x2=q->x1+cos(q->a)*LEAFSIZE * sz;
                    q->y2=q->y1+sin(q->a)*LEAFSIZE * sz;
                    q->ph=p->ph+CHILDTIMESTEP;
                    q->state=3;
                    q->burst=0;
                    q->weight=p->weight-1;
                    q->next=addon;
                    q->fade=p->fade;
                    if(checkSpace(q)){
                        addon=q;            
                    }else{
                        free(q);            
                    }    
                
                }
                
            }
        
        }
    }
    if(root!=NULL){
        for(p=root;p->next!=NULL;p=p->next);
        p->next=addon;    
    }else{
        root=addon;    
    }
}
void zeroHohloma(SDL_Surface* screen){
    int x,y,i;
    double a,da,dda;
    struct grow*p;
    wind=(rand()%1000)*MAXWIND*2/1000.0 - MAXWIND;
    for(x=0;x<screen->w;x++){
        for(y=0;y<screen->h;y++){
            putpixel(screen,x,y,0);        
        }
    
    }
    root=NULL;
   
    for(i=0;i<STARTGROW;i++){
        p=(struct grow*)malloc(sizeof(struct grow));
        if(p==NULL)
            continue;
        
        x=rand()%(screen->w);
        y=rand()%(screen->h);
        a=((rand()%1000)/1000.0)*2.0*M_PI;
        da=((rand()%1000)/50000.0)*M_PI;
        dda=((rand()%1000)/2500000.0)*2.0*M_PI;
        p->id=growid++;
        p->x1=x;
        p->y1=y;
        p->x2=x+cos(a)*HS;
        p->y2=y+sin(a)*HS;
        p->a=a;
        p->da=da;
        p->dda=dda;
        p->ph=0;
        p->state=0;
        p->burst=0;
        p->weight=0;
        p->fade=0;
        p->next=root;
        root=p;
    }
    h_w=(screen->w)/5;
    h_h=(screen->h)/5;
    space=(char*)malloc(h_h*h_w*sizeof(char));
    sumspace=(unsigned int*)malloc(h_h*h_w*sizeof(unsigned int));
   
    
    if(space!=NULL)
        memset(space,0,h_h*h_w);
    if(sumspace!=NULL)
        memset(sumspace,0,h_h*h_w*sizeof(unsigned int));  
    
}
void closeHohloma(){
    struct grow*p,*q;
    p=root;
    while(p!=NULL){
        q=p->next;
        free(p);
        p=q;    
    }
    if(space!=NULL){
        free(space);
    }
     if(sumspace!=NULL){
        free(sumspace);
    }

}
#ifndef HSVMOD
#define HSVMOD

#ifdef REVERCERGB
struct rgb{
    Uint8 b,g,r,o; 
};
#else
struct rgb{
    Uint8 r,g,b,o; 
};
#endif

struct hsv_colour{
    float s,h,v;

};
struct rgb_colour{
    float r,g,b;
}; 

struct rgb hsv2rgb(int h,double s,double v){// h =0.. 360  s=0..1  v=0..1
    int h1;
    double x,c,m,r,g,b;    
    struct rgb res;
    c=v*s;
    h1=h / 60;
    x=c*(1-abs((h1%2) - 1));    
    switch (h1){
        case 0:r=c ; g=x ; b=0 ;break;
        case 1:r=x ; g=c ; b=0 ;break;
        case 2:r=0 ; g=c ; b=x ;break;
        case 3:r=0 ; g=x ; b=c ;break;
        case 4:r=x ; g=0 ; b=c ;break;
        case 5:r=c ; g=0 ; b=x ;break;
    }
    m=v-c;
    r+=m;
    g+=m;
    b+=m;
    res.r=r*255;
    res.g=g*255;
    res.b=b*255;
    return res;
}


struct rgb rgb_colour2rgb(rgb_colour*rgb){
    struct rgb c;
    c.r=rgb->r*255.;
    c.g=rgb->g*255.;
    c.b=rgb->b*255.;
    return c;
}


int hsv2rgb( struct hsv_colour *hsv, struct rgb_colour *rgb ) {
   /*
    * Purpose:
    * Convert HSV values to RGB values
    * All values are in the range [0.0 .. 1.0]
    */
   float S, H, V, F, M, N, K;
   int   I;
   
   S = hsv->s;  /* Saturation */
   H = hsv->h;  /* Hue */
   V = hsv->v;  /* value or brightness */
   
   if ( S == 0.0 ) {
      /* 
       * Achromatic case, set level of grey 
       */
      rgb->r = V;
      rgb->g = V;
      rgb->b = V;
   } else {
      /* 
       * Determine levels of primary colours. 
       */
      if (H >= 1.0) {
         H = 0.0;
      } else {
         H = H * 6;
      } /* end if */
      I = (int) H;   /* should be in the range 0..5 */
      F = H - I;     /* fractional part */

      M = V * (1 - S);
      N = V * (1 - S * F);
      K = V * (1 - S * (1 - F));

      if (I == 0) { rgb->r = V; rgb->g = K; rgb->b = M; }
      if (I == 1) { rgb->r = N; rgb->g = V; rgb->b = M; }
      if (I == 2) { rgb->r = M; rgb->g = V; rgb->b = K; }
      if (I == 3) { rgb->r = M; rgb->g = N; rgb->b = V; }
      if (I == 4) { rgb->r = K; rgb->g = M; rgb->b = V; }
      if (I == 5) { rgb->r = V; rgb->g = M; rgb->b = N; }
   } /* end if */

   return 0;
} /* end function hsv2rgb */



 typedef struct {
    double r;       // percent
    double g;       // percent
    double b;       // percent
} rgb_percent;

    typedef struct {
    double h;       // angle in degrees
    double s;       // percent
    double v;       // percent
} hsv_degrees_percent;

    static hsv_degrees_percent      rgb2hsv(rgb_percent in);
    static rgb_percent      hsv2rgb(hsv_degrees_percent in);

hsv_degrees_percent rgb2hsv(rgb_percent in)
{
    hsv_degrees_percent          out;
    double      min, max, delta;

    min = in.r < in.g ? in.r : in.g;
    min = min  < in.b ? min  : in.b;

    max = in.r > in.g ? in.r : in.g;
    max = max  > in.b ? max  : in.b;

    out.v = max;                                // v
    delta = max - min;
    if( max > 0.0 ) {
        out.s = (delta / max);                  // s
    } else {
        // r = g = b = 0                        // s = 0, v is undefined
        out.s = 0.0;
        out.h = NAN;                            // its now undefined
        return out;
    }
    if( in.r >= max )                           // > is bogus, just keeps compilor happy
        out.h = ( in.g - in.b ) / delta;        // between yellow & magenta
    else
    if( in.g >= max )
        out.h = 2.0 + ( in.b - in.r ) / delta;  // between cyan & yellow
    else
        out.h = 4.0 + ( in.r - in.g ) / delta;  // between magenta & cyan

    out.h *= 60.0;                              // degrees

    if( out.h < 0.0 )
        out.h += 360.0;

    return out;
}


rgb_percent hsv2rgb(hsv_degrees_percent in)
{
    double      hh, p, q, t, ff;
    long        i;
    rgb_percent      out;

    if(in.s <= 0.0) {       // < is bogus, just shuts up warnings
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
    hh = in.h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));

    switch(i) {
    case 0:
        out.r = in.v;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = in.v;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = in.v;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = in.v;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = in.v;
        break;
    case 5:
    default:
        out.r = in.v;
        out.g = p;
        out.b = q;
        break;
    }
    return out;     
}

struct rgb rgb_percent2rgb(rgb_percent rgb){
    struct rgb c;
    c.r=rgb.r*2.55;
    c.g=rgb.g*2.55;
    c.b=rgb.b*2.55;
    return c;
}

#endif
#ifndef INTERFERMOD
#define INTERFERMOD

#include<math.h>

#include"graphutil.cpp"
#include"soundutil.cpp"

struct layer{
    unsigned char *p;
    int h,w;
};


unsigned char morphTable[256][256];
int lastMorph=0;


void buildMorphTable(int d){
    int i,j;
    if(d==lastMorph)
        return;
    lastMorph=d;
    for(i=0;i<256;i++){
        for(j=0;j<256;j++){
            morphTable[i][j]=(i*(d)+j)/(d+1);
        }
    }

}

void morph(struct layer*oldl,struct layer*newl,int d){
    int i,j;
    unsigned char*o,*n;
    o=oldl->p;
    n=newl->p;
    if(d==0){
        for(i=0;i<oldl->h;i++)
            for(j=0;j<oldl->w;j++,o++,n++){
                *o=*n;

            }
        return;
    }    
    
    buildMorphTable(d);
    for(i=0;i<oldl->h;i++)
        for(j=0;j<oldl->w;j++,o++,n++){
            *o=morphTable[*o][*n];
        }



}


struct layer*makeLayer(int w,int h){
    struct layer *l;
    l=(struct layer*)malloc(sizeof(struct layer));
    if(l==NULL)
        return NULL;
    l->p=(unsigned char*)malloc(h*w);
    if(l->p == NULL){
        free(l);
        return NULL;
    
    }
    l->h=h;
    l->w=w;
    return l;
}
void freeLayer(struct layer *p){
    if(p!=NULL){
        if(p->p!=NULL)
            free(p->p);
         free(p);
    }
}


struct layer*resizeLayer(struct layer*old,int w,int h){
    struct layer *n;
    int x,y;
    if(old==NULL){
        return makeLayer(w,h);
    }
    n=makeLayer(w,h);
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
int buildInterTable(int w,int h,double mapSize,int s1x,int s1y,int s2x,int s2y){
    if(interTable1==NULL ||interTable2==NULL || interTableH!=h || interTableW!=w||fabs(mapSize-interTableMapSize)>0.00001){
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



int getS1(int d){
    int t;
    t=s1bufcur-d-1;
    while(t<0)
        t+=SBUFSIZE;
    t=t&(SBUFSIZE-1);
    return s1buf[t];
}
int getS2(int d){
    int t;
    t=s2bufcur-d-1;
    while(t<0)
        t+=SBUFSIZE;
    t=t&(SBUFSIZE-1);
    return s2buf[t];
}



void interFer(struct layer*l,double mapsize){
    int x,y,i,j;
    int s1x,s1y,s2x,s2y;
    Uint32 a,d1,d2;
    unsigned char*out;
    int w;
    int h;
    out=l->p;
    w=l->w;
    h=l->h;
    
    s1x=0;
    s1y=h/2;
    s2x=w-1;
    s2y=h/2;
    buildInterTable(w,h,mapsize,s1x,s1y,s2x,s2y);
    //int i0,i1;
    //i0=0+pix*(1-value)/2;
    //i1=pix-pix*(1-value)/2;
            
    for(y=0;y<h;y++){
        for(x=0;x<w;x++){
            d1=interTable1[x+ (y)*w];
            d2=interTable2[x+ (y)*w];
            a=(getS1(d1)+getS2(d2))/2;
            a=a/256;
            out[(x)+(y)*w]=128+a;
        }
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


#endif
#include<math.h>
#ifndef KOEFSMOD
#define KOEFSMOD
#define dEqEps 1e-10
#define dEq(a,b) ((fabs((a)-(b))<dEqEps)?1:0)



#define KOEFNUM 10
#define DRAWKOEFNUM 18
double soundKoefs[KOEFNUM];
double drawKoef[DRAWKOEFNUM];
double ascellValue[DRAWKOEFNUM];
double lascellValue[DRAWKOEFNUM];
double drawLatKoef[DRAWKOEFNUM];


//PIF:
//pifDeep,pifNaked,pifColored,
//pifDWind,pifDScale,pifDAngle,
//empty(r),CircleSeqSym,CircleSeqN,
//,pifRepeat,pifParity,starValue,
//starAngle,starN,rScale,
//minDeep, SpirafTransform, MegaTransform
double accspeed[KOEFNUM]={1000,1000,1000,1000,1000,1000,1000,1000,1000,1000};

double maxDrawKoef[DRAWKOEFNUM]={10,3.001,1.001,100,10,7000,1000000,1,1,60.01,1.01,1.01,1000000,180,1,1};


double minDrawKoef[DRAWKOEFNUM]={2,0,0,-100,-1000,-7000,0.0000001,0.00,0.00,1,0,0,-1000000,3,0,0};


double controllKoef[DRAWKOEFNUM*KOEFNUM];
double zeros[DRAWKOEFNUM];
double dkoef[DRAWKOEFNUM];
double dkoefacc[DRAWKOEFNUM];
double dkoefaccperiod[DRAWKOEFNUM];
double koefascell[DRAWKOEFNUM];
double koefascellacc[DRAWKOEFNUM];
double koefascellamp[DRAWKOEFNUM];


double dkh[DRAWKOEFNUM];
void  drawKoefLatency(double *kf,double *lat){
    for(int i=0;i<DRAWKOEFNUM;i++){
        double a;
        a=lat[i];
        if(a<0.)
            a=0.;
        if(a>1.)
            a=1.;
        kf[i]=dkh[i]=dkh[i]*a+kf[i]*(1-a);
        
    }



}

void setZeroPifControllKoef(){
    int i,j;
    double *ck;
    ck=controllKoef;
//    printf("ZEROPIFSOUND!\n");
    
    
for(i=0;i<KOEFNUM;i++){
    accspeed[i]=1000;
}

double zeromaxDrawKoef[DRAWKOEFNUM]={10,3.001,1.001,100,10,7000,10000000,1000000,1 ,60.01,1.01,1.01,1000000,180,1,1,1,1};
double zerominDrawKoef[DRAWKOEFNUM]={2,0,0,-100,-1000,-7000,10000000.0,0.0000001,0.0000000,1,0,0,-1000000,3,0,0,0,0};
for(i=0;i<DRAWKOEFNUM;i++){
    maxDrawKoef[i]=zeromaxDrawKoef[i];
    minDrawKoef[i]=zerominDrawKoef[i];
    drawLatKoef[i]=0;
}    

    
    
    for(i=0;i<DRAWKOEFNUM;i++){
        dkoefacc[i]=0;
        zeros[i]=0;
        dkoef[i]=0;
        dkoefaccperiod[i]=10000000.;
        koefascell[i]=0;
        koefascellacc[i]=0;
        koefascellamp[i]=0;
        for(j=0;j<KOEFNUM;j++){
            ck[i*KOEFNUM+j]=0;
        
        }
    }
    
    //pifDeep
    ck[0*KOEFNUM+1]=7;
    ck[0*KOEFNUM+0]=7;
    ck[0*KOEFNUM+4]=11;
    //minDeep
//    ck[15*KOEFNUM+1]=7;
    ck[15*KOEFNUM+1]=7;
    maxDrawKoef[15]=10;
    minDrawKoef[15]=0;    
  //  ck[15*KOEFNUM+4]=11;
    
    
    
    
    //pifangle
    dkoef[5]=M_PI/10000;
    
    
    
    //pscale
    ck[4*KOEFNUM+6]=0.1;
    koefascell[4]=0.001;
    koefascellamp[4]=1/10.;
    //pwind
    ck[3*KOEFNUM+5]=0.1;
    koefascell[3]=1.0/100000000.;
    koefascellamp[3]=M_PI; 

    //starValue
    ck[11*KOEFNUM+4]=0.65;
    ck[11*KOEFNUM+2]=0.4;

    ck[11*KOEFNUM+1]=0.4;
    //starN
    zeros[13]=3;
    //starAngle
    ck[12*KOEFNUM+6]=1.;
    ck[12*KOEFNUM+5]=1.;
    
    
 //   koef[14]
   
    ck[14*KOEFNUM+0]=-1.;
  //  ck[14*KOEFNUM+2]=1.;
   
    zeros[14]=1.;
    minDrawKoef[14]=0;
    maxDrawKoef[14]=1;
    

//CircleSeq
    zeros[8]=0.;
    minDrawKoef[8]=0;
    maxDrawKoef[8]=1;

    
//    pifDeep=7.*melodyrithm*pifDeepRithm);
  //  if(pifDeep>7)
    //    pifDeep=7;
    //pifDeep=bassrithm*pifDeepBass;
    //if(pifDeep>7)
    //    pifDeep=7;
    
//    pifDeep=pifDeep+ cur*pifDeepCur;
  //  if(pifDeep>11)
    //    pifDeep=11;
    //if(pifDeep<2)
      //  pifDeep=2;

  //  if(ALLFRAQ){
  //      pifDeep=11;
    
  //  }
    //ds=bassrithm/10;
   // if(ds>maxds)
    //    maxds=ds;
   // sound_rx=rx*rxMax;
    //sound_ry=;

}
#endif
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<SDL/SDL.h>
#include"graphutil.cpp"
int mixerh=0;
int mixerw=0;
int *mixerbuf=NULL;
int *mul_mixerw;

void closeRgbMixer(){
    if(mixerbuf!=NULL){
        free(mixerbuf);
    }
    if(mul_mixerw!=NULL)
        free(mul_mixerw);
}

int ks0[256];
int ks1[256];
int ks2[256];
int oldFade(SDL_Surface* source,int div);
int bpb=4;
int bpb1=1;
int bpb2=2;

void calcKs(double alpha,int w,int mul){
    
    
    int x,xm;
    int sinalpha,cosalpha;
    int sinalpha2,cosalpha2;
    int sinalpha3,cosalpha3;
    sinalpha=1024*sin(alpha)/255.;
    cosalpha=1024*cos(alpha)/255.;
    sinalpha2=1024*sin(alpha+2.0*M_PI/3.0)/255.;
    cosalpha2=1024*cos(alpha+2.0*M_PI/3.0)/255.;
    sinalpha3=1024*sin(alpha+4.0*M_PI/3.0)/255.;
    cosalpha3=1024*cos(alpha+4.0*M_PI/3.0)/255.;
    
    for(x=0,xm=0;x<256;x++,xm+=mul){
        ks0[x]=bpb*(
        
                       (
                         (int)
                            (
                              sinalpha*xm/1024
                            )
                       ) + 
                       (
                         (int)
                         (
                             (w+20)*
                             (
                                 (int)
                                 (
                                     cosalpha*xm/1024
                                 )
                             )
                         )
                         
                       ) 
                            
                   );    //red shift
        ks1[x]=bpb1+bpb*(
        
                        (
                          (int)
                          (
                             sinalpha2*xm/1024)
                          )+ 
                          (
                                (int)(20+w)*
                                    (
                                       (int)(
                                             cosalpha2*xm/1024
                                             )
                                       )
                    
                    
                          )
                    );   //green shift

        ks2[x]=bpb2+bpb*(
                         (
                            (int)
                                   (    
                                      sinalpha3*xm/1024
                                    )
                          )  +   
                          (
                              (int)
                              (20+w)*
                              (    (int)
                                  (
                                  cosalpha3*xm/1024)
                                  )
                              
                           )   
                              );   //blue shift
        
        
   }


}

void  addNoise(SDL_Surface* s,int counts,int value,int colored){
    int i;
    struct rgb c;
    i=(s->w*s->h)*counts/100;
    if(value>255)
        value = 255;
    if(!value)
        value=1;
    for(;i>0;i--){
        if(colored){
            c=*(((struct rgb*)(&(colorSeq2Buf[rand()%SEQLEN]))));
            c.r=c.r*value/256;
            c.g=c.g*value/256;
            c.b=c.b*value/256;
            
        }else{
            c.b=c.g=c.r=rand()%value;
        }
        plusPixel(s,rand()%s->w,rand()%s->h,*((Uint32*)(&c)));
    
    }
    
    
    


}


int smoothMask[10]={ 0, 2, 0,
                     2, 2, 1,
                     0, 1, 0,  4};
                     

int smooth(SDL_Surface* source,SDL_Surface* dest){
    int x,y,xx,yy,dd,r,g,b,i;
    Uint8 * s,*d;
    int bpp = source->format->BytesPerPixel;
    s=(((Uint8 *)source->pixels) +bpp + source->pitch);
    
    d=(((Uint8 *)dest->pixels) +bpp   +  dest->pitch);
    
    for(y=1;y<source->h-1;y++,s=(1+ ((Uint8 *)source->pixels) + (y) * source->pitch),d=( ((Uint8 *)dest->pixels) + (y) * dest->pitch +1 ))
        for(x=1;x<source->w-1;x++,s++,d++){
            r=0;g=0;b=0;
            for(yy=-1,dd=-dest->pitch-bpp,i=0;yy<2;yy++,dd+=dest->pitch-bpp*2)
                for(xx=-1;xx<2;xx++,dd+=bpp,i++){
                    r+=((int)  (((struct rgb*) (s+dd))->r  ))<<smoothMask[i];
                    g+=((int)  (((struct rgb*) (s+dd))->g  ))<<smoothMask[i];
                    b+=((int)  (((struct rgb*) (s+dd))->b  ))<<smoothMask[i];
                }
           r=r>>smoothMask[9];
           g=b>>smoothMask[9];
           g=b>>smoothMask[9];
           
           ((struct rgb*)d)->r=0;//r;
           ((struct rgb*)d)->g=g;
           ((struct rgb*)d)->b=b;
        }

    return 0;
}
void copySurface(SDL_Surface* source,SDL_Surface* dest){
   memcpy(dest->pixels,source->pixels,source->h*source->pitch);
 // memset(dest->pixels,0,source->h*source->pitch);  
}


int oldFade(SDL_Surface* source,int div){
    int x,y;
    Uint8 d;
    struct rgb *p;
    if(div>20&&div!=255){
        div=10*(div/10); 
    }else if(div<20){
        div=2*(div/2);
    }
    
    if(div==255){
        SDL_FillRect(source,NULL, 0x000000);
        return 0;
    
    }
    d=div;
    p=(struct rgb *)( ((Uint8 *)source->pixels) );
    for(y=0;y<source->h;y++,p=(struct rgb *)( ((Uint8 *)source->pixels) + y * source->pitch))
        for(x=0;x<source->w;x++,p++){
            if(p->r>d){
                p->r-=d;
            }else{
                p->r=0;            
            }
            if(p->g>d){
                p->g-=d;
            }else{
                p->g=0;            
            }
            if(p->b>d){
                p->b-=d;
            }else{
                p->b=0;            
            }
        
        }


}

Uint32* fadeBufs[256];

Uint32 lastFadeBuf[256*256*256];
Uint32*fadeBuf;
int rgbMixer(SDL_Surface* source,SDL_Surface* filter,int mul,double alpha);
int controll(SDL_Surface *screen);
int prepareFade(struct SDL_Surface*screen,struct SDL_Surface*filter){
    int div,r,g,b,rr,gg,bb;
    int d;
    for(d=0;d<255;d++){
//        bar(screen,0,screen->h/3,screen->w*d/256,screen->h*2/3,WHITE);
//       SDL_FillRect(screen,NULL, 0x000000);
       oldFade(screen,10);
       drawPianoBar(screen,screen->w/3,screen->h/3,screen->w/3 + (d*screen->w/3)/255,2*screen->h/3,1+d/70);

       SDL_Flip( screen ); 
      if(controll(screen)){
            break;
       }       

        div=d;
        
        if(div>20){
            div=10*(div/10);
        }else if(div>10){
            div=2*(div/2);
        }
        if(fadeBufs[div]==NULL){
            fadeBufs[div]=(Uint32*)malloc(sizeof(Uint32)*256*256*256);
            if(fadeBufs[div]==NULL)
                return -1;        
            for(r=0;r<256;r++){
                if(r%64==0){
                    rgbMixer(screen,filter,10,r*M_PI/128.0);
                    SDL_Flip( screen );
                }
                for(g=0;g<256;g++){
                    for(b=0;b<256;b++){
                        
                         if(r>div){
                             rr=r-div;
                         }else{
                             rr=0;            
                         }
                         if(g>div){
                             gg=g-div;
                         }else{
                             gg=0;            
                         }
                         if(b>div){
                             bb=b-div;
                         }else{
                             bb=0;            
                         }
                         fadeBufs[div][r+g*256+b*256*256]=rr+gg*256+bb*256*256; 
                    
                    }
                }
            }
        
        }
        
    
    }



}


int lastdiv=-1;
int fadeReady=0;
int r0=0;
int pblurtime=0;
int lastpnlur=0;
void orblur(SDL_Surface* source,int div){
    int y,x,pit,d;
    Uint32*q;
    pit=source->pitch/4;
//    pblurtime&=3;
    d=0;
    div=255-div;
    if (div<0)
        div=0;
    if(div>=255)
        return;
    if(pblurtime*4>=div){
        pblurtime-=div/4;
        lastpnlur++;
        if(lastpnlur%4==1)
            d=1;
        else
        if(lastpnlur%4==1)
            d=-1;
        else
        if(lastpnlur%4==2)
            d=pit;
        else
        if(lastpnlur%4==3){
            pblurtime=0;
            d=-pit;
        }
        if(d>0)
            for(y=1,q=(Uint32*)source->pixels    +  y*pit  +1;y<source->h-1;y++,q=(Uint32*)(source->pixels) + y * pit)
               for(x=1;x<source->w-1;x++,q++){
                    *q|=*(q+d);               
               }
        else if(d<0){
            for(y=source->h-2,q=(Uint32*)source->pixels    +  y*pit  + source->w-2;y>0;y--,q=(Uint32*)(source->pixels) + (y) * pit + source->w-2)
                for(x=source->w-2;x>0;x--,q--){
                    *q|=*(q+d);               
                 }
        }
    }else
     pblurtime++;
    
}

int fade(SDL_Surface* source,int div){
    int x,y;
    Uint32 r,g,b,rr,gg,bb;
    Uint32*q;
    Uint8 d;
    if(div==255){
        SDL_FillRect(source,NULL, 0x000000);
        return 0;
    
    }
    if(div>60){
        div=10*(div/10);
        
    }else if(div>10){
        div=2*(div/2);
    }
    
    d=div;
    
    if(lastdiv!=div || lastdiv==-1){
        lastdiv=div;
        if(fadeBufs[div]==NULL){
               fadeBuf=lastFadeBuf;                
               fadeReady=0;
               r0=0;
         }else{
            fadeReady=1;
            fadeBuf=fadeBufs[div];
         
         }
    }
    
    if(fadeReady==0){
        for(r=r0;r<256&&r<r0+8;r++)
            for(g=0;g<256;g++)
                for(b=0;b<256;b++){
                   if(r>d){
                        rr=r-d;
                   }else{
                        rr=0;            
                   }
                   if(g>d){
                        gg=g-d;
                   }else{
                        gg=0;            
                   }
                   if(b>d){
                        bb=b-d;
                   }else{
                        bb=0;            
                   }
                  fadeBuf[r+g*256+b*256*256]=rr+gg*256+bb*256*256; 
        }
        r0=r;
        if(r0==256){
            fadeReady=1;
            fadeBufs[div]=(Uint32*)malloc(sizeof(Uint32)*256*256*256);
            
            if(fadeBufs[div]!=NULL){
                memcpy(fadeBufs[div],fadeBuf,sizeof(Uint32)*256*256*256);
            }
        
        
            /*FILE*f;
            char s[128];
            sprintf(s,"cache/fade_%d",div);
            f=fopen(s,"wb");
            if(f!=NULL){
                int l;
                fwrite(fadeBuf,256*256*256*sizeof(Uint32),1,f);
                fclose(f);
            }*/
        }
    }
    if(fadeReady){
        for(y=0,q=(Uint32*)source->pixels;y<source->h;y++,q=(Uint32*)( ((Uint8 *)source->pixels) + y * source->pitch))
            for(x=0;x<source->w;x++,q++){
                *q=fadeBuf[(*q)&(255|(255*256)|(255*256*256))];
            }
    }else{
        oldFade(source,div);
    
        //SDL_FillRect(source,NULL, 0x000000);
    
    }
}

/*
*/

int initFade(SDL_Surface* source){
//    for(int i=0;i<256;i++){
  //      fade(source,i);    
    //}
    return 0;
}

void closeFades(){
   for(int i=0;i<256;i++){
        if(fadeBufs[i]!=NULL)
            free(fadeBufs[i]);
    }
    

}




inline char*getScreenPointer(SDL_Surface* source,int x,int y){
    return (char*)( ((Uint8 *)source->pixels) + y * source->pitch + x * source->format->BytesPerPixel);

}


char swapchart;
inline void swapchar(char &a,char &b){
    swapt=a;
    a=b;    
    b=swapt;
}

int moveNoise(SDL_Surface* source,int div,int count){
    int d,c,l,x,y,i;
    int bpp=source->format->BytesPerPixel;
    char *p,*q;
    d=div;
    if(div<=0)
        return 0;
   // p=getScreenPointer(source,div,div);
    for(i=source->h*source->w*count/100;i>=0;i--){
        x=rand()%(source->w-2*div)+div;
        y=rand()%(source->h-2*div)+div;
        p=getScreenPointer(source,x,y);
        c=rand()%3;
        l=(rand()%(2*div+1) - div)*bpp + (rand()%(2*div+1) - div)*source->pitch;
        swapchar(*(p+c),*(p+l+c)); 
    }
    
/*    for(y=div;y<source->h - div ;y++,p=getScreenPointer(source,div,y))
        for(x=div;x<source->w-div;x++,p+=bpp){
          if(rand()%100>count)
            continue;
           c=rand()%3;
           l=rand()%(2*div+1) - div + (rand()%(2*div+1) - div)*source->pitch;
           swapchar(*(p+c),*(p+l+c));              
        }

*/
}

int rgbMixerStep=0;
int rgbMixer(SDL_Surface* source,SDL_Surface* filter,int mul,double alpha){
    int x,y;
    int bpp = source->format->BytesPerPixel;
    int r,g,b,fr,fg,fb,dx,dy;
    SDL_Surface *f,*s,*d;
    int *bu;
    int xshift;
    int yshift;
    
    #define RGBDIV 2
    int xstep=RGBDIV;
    int ystep=RGBDIV;
    xshift=rgbMixerStep&(RGBDIV-1);
    yshift=(rgbMixerStep/RGBDIV)&(RGBDIV-1);
    rgbMixerStep++;
    
  //  printf("mixer start\n");
   // fflush(stdout);
   
    if(mul<=0)
        return 0;
    if(mul>10)
        mul=10;
    if(source->w!=filter->w || source->h!=filter->h){
        if(mixerh!=-1){
           printf("Cant rgbMix, becouse screens are different\n");
           mixerh=-1;           
        }
        return -1;
    }
    if(mixerh!=filter->h || mixerw!=filter->w){

        if(mixerbuf!=NULL){
            free(mixerbuf);        
        }
        
        mixerbuf=(int*)malloc((filter->h+20)*(filter->w+20)*sizeof(int)*4);
        if(mixerbuf==NULL){
             printf("Cant rgbMix, becouse out of memory\n");
            return -2;
        }
        memset(mixerbuf,0,(20+mixerh)*(20+mixerw)*4*sizeof(int));  
        mixerh=filter->h;
        mixerw=filter->w;
       
    }
    //memset(mixerbuf,0,(20+mixerh)*(20+mixerw)*4*sizeof(int));
    
   // bu=mixerbuf+(20+mixerw)*4*sizeof(int));
    calcKs(alpha,filter->w,mul);
   // printf("mixer started\n");
    //fflush(stdout);
    for(y=yshift;y<mixerh;y+=ystep){

        Uint32 *s =(Uint32 *)( (Uint8 *)source->pixels + y * source->pitch);
        Uint32 *f =(Uint32 *)( (Uint8 *)filter->pixels + y * filter->pitch);
        bu=mixerbuf+(((y+10)*(mixerw+20))+10)*4;
        s+=xshift;
        f+=xshift;
        bu+=4*xshift;
        for(x=mixerw-1-xshift;x>0;x-=xstep,bu+=4*xstep,f+=xstep,s+=xstep){
            if(!(*s) || !(*f)){
                continue;
            }
            pixel2rgb(*s,r,g,b);
            pixel2rgb(*f,fr,fg,fb);
            
            *s=0;
            bu[ks0[fr]]+=r;
            bu[ks1[fg]]+=g;
            bu[ks2[fb]]+=b;
            
        }
    }
    //printf("mixer half\n");
    //fflush(stdout);

    for(y=yshift;y<mixerh;y+=ystep){
        
        Uint32 *d =(Uint32*)( (Uint8 *)source->pixels + y * source->pitch);
        bu=mixerbuf+(((y+10)*(mixerw+20))+10)*4;
        d+=xshift;
        bu+=4*xshift;


        for(x=mixerw-1-xshift;x>0;x-=xstep,bu+=xstep*4,d+=xstep){
            if(!(*bu | *(bu+1) | *(bu+2)))
                continue;
            pixel2rgb(*d,r,g,b);
            r+=*bu;
            g+=*(bu+1);
            b+=*(bu+2);
            *bu=0;
            *(bu+1)=0;
            *(bu+2)=0;
      //      *((Uint32*)bu)=0;            
                        
            if(r & (65535-255))
                r=255;           
            if(g& (65535-255))
                g=255;
            if(b& (65535-255))
                b=255;
            rgb2pixel(r,g,b,d);    
        }
    }
 //   printf("mixer finish\n");
   // fflush(stdout);
    return 0;
}
int orrgbMixer(SDL_Surface* source,SDL_Surface* filter,int mul,double alpha){
    int x,y;
    int bpp = source->format->BytesPerPixel;
    int r,g,b,fr,fg,fb,dx,dy;
    SDL_Surface *s,*d;
    int *bu;
    int xshift;
    int yshift;
    
    #define RGBDIV 2
    int xstep=RGBDIV;
    int ystep=RGBDIV;
    xshift=rgbMixerStep&(RGBDIV-1);
    yshift=(rgbMixerStep/RGBDIV)&(RGBDIV-1);
    rgbMixerStep++;
    
  //  printf("mixer start\n");
   // fflush(stdout);
   
    if(mul<=0)
        return 0;
    if(mul>10)
        mul=10;
    if(source->w!=filter->w || source->h!=filter->h){
        if(mixerh!=-1){
           printf("Cant rgbMix, becouse screens are different\n");
           mixerh=-1;           
        }
        return -1;
    }
    bpb=1;
    bpb1=0;
    bpb2=0;

    calcKs(alpha,filter->w,mul);
    Uint32*q,*f;
    int pit;
    pit=source->pitch/4;
    Uint32 c;
    int dd=1;
    for(y=20,q=(Uint32*)source->pixels +  y*pit  +20,f=(Uint32*)filter->pixels    +  y*pit  +20;y<filter->h-20
    ;y++,q=(Uint32*)(source->pixels) + y * pit+20,f=(Uint32*)(filter->pixels) + y * pit+20)
         for(x=20;x<source->w-20;x+=dd,q+=dd,f+=dd){
//                    pixel2rgb(*f,r,g,b);
                  pixel2rgb(*f,fr,fg,fb);
                  c=*q;
                  *q=0;
                  q[ks0[fr]]|=(c)&255;
                  q[ks1[fg]]|=(c)&(255)*256;
                  q[ks2[fb]]|=(c)&(255)*256*256;;
                  dd=1+rand()%3;
               }
        

    return 0;
}





#ifndef MOUSECONTOLLMOD
#define MOUSECONTOLLMOD
#include"colors.cpp"
#define MAXDROPS 128
struct drop{
    int x,y;
    double r;
}drops[MAXDROPS];
//int ndrops=0;

void addDrop(int x,int y){
    int i;
    for(i=0;i<MAXDROPS;i++){
        if(drops[i].r<=0.){
            drops[i].x=x;
            drops[i].y=y;
            drops[i].r=15;   
            return;
        }
    }
}
void showDrops(SDL_Surface* screen){
    int i;
    for(i=0;i<MAXDROPS;i++){
        if(drops[i].r>0){
            circle(screen,drops[i].x,drops[i].y,drops[i].r,GREEN);
            drops[i].r*=2.3;   
            if(drops[i].r>screen->w)
                drops[i].r=-1;
        }
    }


}




#define MAXEVALUES 1024
struct eValue{
    int x1,y1,x2,y2,x,y,mx,my;
    int type;
    double d;
    void *ptr;
    double last;    
    double min,max;
}eValues[MAXEVALUES],selectedEValue;
int neValues=0;
void clearEvalues(){
    neValues=0;
}
void addEValue(int x1,int y1,int x2,int y2,int type,double d,double min,double max,void*ptr){
    if (neValues > MAXEVALUES)
        return;
    eValues[neValues].x1=x1;
    eValues[neValues].y1=y1;
    eValues[neValues].x2=x2;
    eValues[neValues].y2=y2;
    eValues[neValues].d=d;        
    eValues[neValues].min=min;        
    eValues[neValues].max=max;        

    eValues[neValues].ptr=ptr;
    eValues[neValues].type=type;
    neValues++;
}
int selectEValue(int x,int y){
   int i;
    for(i=neValues-1;i>=0;i--){
        if(x>=eValues[i].x1 && x<=eValues[i].x2
            &&
            y>=eValues[i].y1 && y<=eValues[i].y2
            &&eValues[i].ptr!=NULL
        ){
            selectedEValue=eValues[i];
            selectedEValue.x=x;
            selectedEValue.y=y;
            if(selectedEValue.type==0){
                selectedEValue.last=*((double*)selectedEValue.ptr);
            }
            else{
                selectedEValue.last=*((int*)selectedEValue.ptr);
            }
            return 1;
        }
    }
    selectedEValue.ptr=NULL;
    return 0;
}
void markSelectedValue(SDL_Surface* screen){
    if(selectedEValue.ptr!=NULL){
        rectangle(screen,selectedEValue.x1,selectedEValue.y1,selectedEValue.x2,selectedEValue.y2,RED);
        drawLine(screen,selectedEValue.x,selectedEValue.y,selectedEValue.mx,selectedEValue.y,WHITE);
        drawLine(screen,selectedEValue.mx,selectedEValue.y,selectedEValue.mx,selectedEValue.my,WHITE);
        
    }

}
void relizeSelectedValue(){
    selectedEValue.ptr=NULL;
}
void modifySelected(int x,int y){
    if(selectedEValue.ptr!=NULL){
        double d;
        selectedEValue.mx=x;
        selectedEValue.my=y;
        d=selectedEValue.last  + ((x-selectedEValue.x)+(selectedEValue.y-y))*selectedEValue.d;
        if(d>selectedEValue.max)
                d=selectedEValue.max;
        if(d<selectedEValue.min)
                d=selectedEValue.min;
        
        if(selectedEValue.type==0){
            double*v;
            v=(double*)selectedEValue.ptr;
            *v=d;                
            
        }
        else{
            int*v;
            v=(int*)selectedEValue.ptr;
            *v=d;
        }            
    }
}

void clearButtons();
void addButton(int x1,int y1,int x2,int y2,int param,void(*handler)());
#define MAXDIALOGS 128
struct dialog{
    void (*drawDialog)();
    void (*doneDialog)();
    int param;
}dialogs[MAXDIALOGS];
int ndialogs=0;
int dialogParam=0;
int dX1;
int dY1;
int dX2;
int dY2;
SDL_Surface* dSc;

//    (butParam,editAngle);
void addDialog(int param,void(*draw)(),void(*done)()){
    if (ndialogs > MAXDIALOGS)
        return;
    dialogs[ndialogs].drawDialog=draw;
    dialogs[ndialogs].doneDialog=done;
    dialogs[ndialogs].param=param;
    ndialogs++;
}
void addDialog(int param,void(*draw)()){
    addDialog(param,draw,NULL);
}

void doneDialog(){
    if(ndialogs>0){
       ndialogs--;
       if(dialogs[ndialogs].doneDialog!=NULL)
           (dialogs[ndialogs].doneDialog)();

    }

}
void showDialog(SDL_Surface* screen){
    if(ndialogs>0){
        clearButtons();
        clearEvalues();
        dialogParam=dialogs[ndialogs-1].param;
        dX1=screen->w/10;
        dX2=8*screen->w/10;
        dY1=screen->h/10;
        dY2=8*screen->h/10;       
        dSc=screen;
        (*dialogs[ndialogs-1].drawDialog)();
        bar(screen,dX2,dY2,screen->w,screen->h,VERYGREEN);
        addButton(dX2,dY2,screen->w,screen->h,0,doneDialog);        
    }

}


#define MAXBUTTS 20240
struct butt{
    int x1,y1,x2,y2;
    int param;
    int type;
    void(*handler)();
    
}butts[MAXBUTTS];
int nbutts=0;
int butParam;


void clearButtons(){
    nbutts=0;

}
void addButton(int x1,int y1,int x2,int y2,int param,void(*handler)()){
    if (nbutts >= MAXBUTTS)
        return;
    butts[nbutts].x1=x1;
    butts[nbutts].y1=y1;
    butts[nbutts].x2=x2;
    butts[nbutts].y2=y2;
    butts[nbutts].type=1;
    butts[nbutts].handler=handler;
    butts[nbutts].param=param;
    nbutts++;
}
void addSButton(int x1,int y1,int x2,int y2,int param,void(*handler)()){
    if (nbutts >= MAXBUTTS)
        return;
    butts[nbutts].x1=x1;
    butts[nbutts].y1=y1;
    butts[nbutts].x2=x2;
    butts[nbutts].y2=y2;
    butts[nbutts].type=2;
    butts[nbutts].handler=handler;
    butts[nbutts].param=param;
    nbutts++;
}

int clickMouse(int x,int y){
    int i;
    for(i=nbutts-1;i>=0;i--){
        if((butts[i].type&1) &&  x>=butts[i].x1 && x<=butts[i].x2
            &&
            y>=butts[i].y1 && y<=butts[i].y2
        ){
            butParam=butts[i].param;
            (*butts[i].handler)();
            return 1;
        }
    }
    return 0;
}
int sclickMouse(int x,int y){
    int i;
    for(i=nbutts-1;i>=0;i--){
        if((butts[i].type&2) &&  x>=butts[i].x1 && x<=butts[i].x2
            &&
            y>=butts[i].y1 && y<=butts[i].y2
        ){
            butParam=butts[i].param;
            (*butts[i].handler)();
            return 1;
        }
    }
    return 0;
}
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#include <android/log.h>
#include <errno.h>
#ifndef MYNET

#define MYNET
int netstatus=0;


struct  myhost{
    char name[128];
    int inport,outport;
}hosts[1024];
int nhost=0;
int lhost=0;
void myDisconnect();
void mySend(const char*s);
void addServer(const char*name,int inport,int outport){
    strcpy(hosts[nhost].name,name);
    hosts[nhost].inport=inport;
    hosts[nhost].outport=outport;
    nhost++;
}


int inSoc=-1;
int outSoc=-1;
extern Uint32  lastRecive;
int myConnect(){
    int sock=socket(PF_INET,SOCK_STREAM,0);
    struct sockaddr_in peerAddr;
    int ret;
    char*server=hosts[lhost].name;
    int inport=hosts[lhost].inport;
    int outport=hosts[lhost].outport;
    int valopt; 
    long arg; 
    fd_set myset; 
    struct timeval tv; 
    socklen_t lon; 
    
    
    lhost++;
    lhost=lhost%nhost;
    
    peerAddr.sin_family=AF_INET;
    peerAddr.sin_port=htons(inport);
    peerAddr.sin_addr.s_addr=inet_addr(server);
   
    fcntl(sock, F_SETFL, fcntl(sock, F_GETFL) | O_NONBLOCK);
   
    ret=connect(sock,(struct sockaddr *)&peerAddr,sizeof(peerAddr));
    if (ret != 0) { 
         if (errno == EINPROGRESS) { 
            tv.tv_sec = 1; 
            tv.tv_usec = 0; 
            FD_ZERO(&myset); 
            FD_SET(sock, &myset); 
            if (select(sock+1, NULL, &myset, NULL, &tv) > 0) { 
               lon = sizeof(int); 
               getsockopt(sock, SOL_SOCKET, SO_ERROR, (void*)(&valopt), &lon); 
               if (valopt) { 
                  //fprintf(stderr, "Error in connection() %d - %s\n", valopt, strerror(valopt)); 
                  //exit(0); 
                  perror("connect failed");
                  close(sock);
                  outSoc=-1;
                  inSoc=-1;
                  return -1;
               } 
            } 
            else { 
                  perror("connect failed");
                  close(sock);
                  outSoc=-1;
                  inSoc=-1;
                  return -1;
            } 
         } 
         else { 
                  perror("connect failed");
                  close(sock);
                  outSoc=-1;
                  inSoc=-1;
                  return -1;
         } 
    } 
    
    
    
    inSoc=sock;
 
    sock=socket(PF_INET,SOCK_STREAM,0);
    fcntl(sock, F_SETFL, fcntl(sock, F_GETFL) | O_NONBLOCK);

    peerAddr.sin_family=AF_INET;
    peerAddr.sin_port=htons(outport);
    peerAddr.sin_addr.s_addr=inet_addr(server);
    ret=connect(sock,(struct sockaddr *)&peerAddr,sizeof(peerAddr));
    if (ret != 0) { 
         if (errno == EINPROGRESS) { 
            tv.tv_sec = 1; 
            tv.tv_usec = 0; 
            FD_ZERO(&myset); 
            FD_SET(sock, &myset); 
            if (select(sock+1, NULL, &myset, NULL, &tv) > 0) { 
               lon = sizeof(int); 
               getsockopt(sock, SOL_SOCKET, SO_ERROR, (void*)(&valopt), &lon); 
               if (valopt) { 
                  //fprintf(stderr, "Error in connection() %d - %s\n", valopt, strerror(valopt)); 
                  //exit(0); 
                  perror("connect failed");
                  close(sock);
                  outSoc=-1;
                 // inSoc=-1;
                  myDisconnect();
                  return -1;
               } 
            } 
            else { 
                  perror("connect failed");
                  close(sock);
                  outSoc=-1;
                  //inSoc=-1;
                  myDisconnect();
                  return -1;
            } 
         } 
         else { 
                  perror("connect failed");
                  close(sock);
                  outSoc=-1;
                  //inSoc=-1;
                  myDisconnect();
                  return -1;
         } 
    } 
        
//    fcntl(sock, F_SETFL, fcntl(sock, F_GETFL) | O_NONBLOCK);
    outSoc=sock;
    netstatus=1;
    lastRecive= GetTickCount();
    mySend("\nconnect\n");
    return 0;
}
extern  int connectflag;
void myDisconnect(){
    connectflag=0;
    if(inSoc!=-1){
        shutdown(inSoc,SHUT_RDWR);
        close(inSoc);
        inSoc=-1;
    }
    if(outSoc!=-1){
        shutdown(outSoc,SHUT_RDWR);
        close(outSoc);
        outSoc=-1;
    }
    netstatus=0;
}

int errCount=0;

void  mabyReconnect(){
    errCount++;
    if(errCount>1000){
          myDisconnect();
          
          myConnect();
          errCount=0;
    }
}
void   itIsOk(){
    errCount=0;

}

void mySend(const char*s){
     if(outSoc==-1){
//        mabyReconnect();
          myDisconnect();
          myConnect();

        return;
     }
     
     if(send(outSoc,s,strlen(s),0) == -1){
 //      mabyReconnect();
       
       //   myDisconnect();
       //   myConnect();
     }
    else{
         //  itIsOk();

    }
}

void mySyntax(char*s){
    char buf[2048];
    sprintf(buf,"recived:[%s]\n",s);
    mySend(buf);
}


#define RECVBUFSIZE 65536
char recvBuf[RECVBUFSIZE];
int recvBufCur;
int syntaxControll(char*p);
int checkRecvData(){
    int r=0;
    int rv=0;
    //int errno;
     if(inSoc==-1){
        //mabyReconnect();
          myDisconnect();
          myConnect();
         return 0;
     }

    while(recvBufCur<RECVBUFSIZE-1 &&  (rv=recv(inSoc,recvBuf+recvBufCur,1,0)) >0){
        if(recvBuf[recvBufCur]=='\n'){
            recvBuf[recvBufCur]=0;
           // mySyntax(recvBuf);
            syntaxControll(recvBuf);
            recvBufCur=0;
            continue;
            r=1;
        }
        recvBufCur++;
    }
    if(recvBufCur>=RECVBUFSIZE-1){
        recvBufCur=0;
    }
 //   int errno;
   // errno=sock_errno();
    if(rv==-1 && errno!=EAGAIN && errno!=EWOULDBLOCK){
          //mabyReconnect();
          myDisconnect();
          myConnect();
    }else{
        //itIsOk();
    }
    return r;
}
int getnetc(){
    char a;
    int r;
    r=recv(inSoc,&a,1,0);
    if(r==0)
        return -1;
    return a;
}

int netprintf(const char*s){
    mySend(s);
    return strlen(s);
}

char sendBuf[RECVBUFSIZE];

int netprintf(const char*s,int a){
    sprintf(sendBuf,s,a);
    mySend(sendBuf);
    return strlen(sendBuf);
}
int netprintf(const char*s,double a){
    sprintf(sendBuf,s,a);
    mySend(sendBuf);
    return strlen(sendBuf);
}

int netprintf(const char*s,char*a,int b,double c){
    sprintf(sendBuf,s,a,b,c);
    mySend(sendBuf);
    return strlen(sendBuf);
}
int netprintf(const char*s,double b,double c){
    sprintf(sendBuf,s,b,c);
    mySend(sendBuf);
    return strlen(sendBuf);
}

int netprintf(const char*s,char*a){
    sprintf(sendBuf,s,a);
    mySend(sendBuf);
    return strlen(sendBuf);
}




int netfprintf(FILE*f,const char*s){
    if(f==stdout){
        mySend(s);
    }else{
        fwrite(s,strlen(s),1,f);
    }
    return strlen(s);
}


int netfprintf(FILE*f,const char*s,int a){
    sprintf(sendBuf,s,a);
    if(f==stdout){
        mySend(sendBuf);
    }else{
        fwrite(sendBuf,strlen(sendBuf),1,f);
    
    }
    return strlen(sendBuf);
}
int netfprintf(FILE*f,const char*s,Uint32 a){
    sprintf(sendBuf,s,a);
    if(f==stdout){
        mySend(sendBuf);
    }else{
        fwrite(sendBuf,strlen(sendBuf),1,f);
    
    }
    return strlen(sendBuf);
}
int netfprintf(FILE*f,const char*s,double a){
    sprintf(sendBuf,s,a);
    if(f==stdout){
        mySend(sendBuf);
    }else{
        fwrite(sendBuf,strlen(sendBuf),1,f);
    
    }
    return strlen(sendBuf);
}

int netfprintf(FILE*f,const char*s,const char*a,int b,double c){
    sprintf(sendBuf,s,a,b,c);
    if(f==stdout){
        mySend(sendBuf);
    }else{
        fwrite(sendBuf,strlen(sendBuf),1,f);
    
    }
    return strlen(sendBuf);
}
int netfprintf(FILE*f,const char*s,const char*a,int b){
    sprintf(sendBuf,s,a,b);
    if(f==stdout){
        mySend(sendBuf);
    }else{
        fwrite(sendBuf,strlen(sendBuf),1,f);
    
    }
    return strlen(sendBuf);
}
int netfprintf(FILE*f,const char*s,const char*a,const char*b){
    sprintf(sendBuf,s,a,b);
    if(f==stdout){
        mySend(sendBuf);
    }else{
        fwrite(sendBuf,strlen(sendBuf),1,f);
    
    }
    return strlen(sendBuf);
}
int netfprintf(FILE*f,const char*s,double b,double c){
    sprintf(sendBuf,s,b,c);
    if(f==stdout){
        mySend(sendBuf);
    }else{
        fwrite(sendBuf,strlen(sendBuf),1,f);
    
    }
    return strlen(sendBuf);
}

int netfprintf(FILE*f,const char*s,char*a){
    sprintf(sendBuf,s,a);
    if(f==stdout){
        mySend(sendBuf);
    }else{
        fwrite(sendBuf,strlen(sendBuf),1,f);
    
    }
    return strlen(sendBuf);
}




#endif
#include"graphutil.cpp"
#ifndef OQCOLORLINEMOD
#define OQCOLORLINEMOD
#define OQS 15
#define COLORLINELEN 256
#define COLORLINEMOD 255
int maxoqs=0;
void bar(SDL_Surface*screen,int x1,int y1,int x2,int y2,Uint32 c);
struct colorLine{
    unsigned int seqno3[OQS];
    Uint32 oqColorline[OQS][COLORLINELEN];
    int oqColorlineDx[OQS][COLORLINELEN];
    int oqColorlineDy[OQS][COLORLINELEN];
    Uint32 orOqColorline[COLORLINELEN];
    unsigned int orseqno3;
    double oqColorlineSat[OQS];
    double oqColorlineVal[OQS];
    int mapOq[OQS][OQS];    
}*cl;
struct colorLine cl3,tcl;

inline Uint32 colorSeq3(int a){
    
    cl->seqno3[a]++;
    cl->seqno3[a]=COLORLINEMOD&(cl->seqno3[a]);
    return cl->oqColorline[a][cl->seqno3[a]];
}
void zeroSeqno3(){
    for(int i=0;i<OQS;i++){
        cl->seqno3[i]=0;
    }
}





void zeroOqColorLine(){
    int i;
    cl=&cl3;  

    for(i=0;i<OQS;i++){
            for(int j=0;j<OQS;j++)
                cl->mapOq[i][j]=0;
             
            cl->oqColorlineSat[i]=0;
            cl->oqColorlineVal[i]=0;

    }
    for(i=0;i<8;i++)
           cl->mapOq[i][i+1]=1;

    cl->mapOq[7][9]=1;
    cl->mapOq[0][0]=1;
    
    cl->oqColorlineSat[0]=0.7;
    cl->oqColorlineSat[1]=0.8;
    cl->oqColorlineSat[2]=0.9;
    cl->oqColorlineSat[3]=1;
    cl->oqColorlineSat[4]=1;
    cl->oqColorlineSat[5]=1;
    cl->oqColorlineSat[6]=1;
    cl->oqColorlineSat[7]=1;
    cl->oqColorlineSat[8]=1;
    cl->oqColorlineSat[9]=1;
    cl->oqColorlineSat[10]=1;


    cl->oqColorlineVal[0]=0.6;
    cl->oqColorlineVal[1]=0.7;
    cl->oqColorlineVal[2]=0.9;
    cl->oqColorlineVal[3]=1;
    cl->oqColorlineVal[4]=1;
    cl->oqColorlineVal[5]=1;
    cl->oqColorlineVal[6]=1;
    cl->oqColorlineVal[7]=1;
    cl->oqColorlineVal[8]=0.9;
    cl->oqColorlineVal[9]=0.6;
    cl->oqColorlineVal[10]=0.5;

}
int Find_Prev_Point(int pix, int TONES){
    int frfrfr;
    int cur;
    cur = COLORLINELEN / TONES;
    frfrfr = (COLORLINELEN+(pix-COLORLINELEN/(2*TONES)))%COLORLINELEN+COLORLINELEN/(2*TONES);
    frfrfr /= cur;
    return frfrfr;
}
double Find_Dist_Prev_Point(int pix, int TONES){
    int frfrfr;
    int cur;
    cur = COLORLINELEN / TONES;
    frfrfr = (COLORLINELEN+(pix-COLORLINELEN/(2*TONES)))%COLORLINELEN+COLORLINELEN/(2*TONES);
    frfrfr %= cur;
    return frfrfr / (double) cur;
}

int Find_Next_Point(int pix, int TONES){
    int frfrfr;
    frfrfr = (Find_Prev_Point(pix, TONES)+1)%TONES;
    return frfrfr;
}




double minValue(double v,double l){
    v-=l;
    v/=(1.-l);
    if(v<0.)
        v=0.;
    if(v>1.)
      v=1.;
   return v;
}
#include"quickspeq.cpp"
#include"hsv.cpp"
void plog(const char*s){
    fprintf(stderr,"%s\n",s);
    fflush(stderr);


}

void zesizeColorLine(Uint32*d,Uint32*s,int div){
   int i;
    for(i=0;i<COLORLINELEN;i+=div,d++,s+=div){
        *d=*s;
    }


}


void zesizeColorLineDcoords(int*d,int*s,int div){
   int i;
    for(i=0;i<COLORLINELEN;i+=div,d++,s+=div){
        *d=*s;
    }


}


int chance(double d){
    return 65536*d>rand()%65536;
}
void calcOrOqColorline(){
//    Uint32 oqColorline[OQS][COLORLINELEN];
  //  Uint32 orOqColorline[COLORLINELEN];
    cl->orseqno3=0;

    for(int j=0;j<COLORLINELEN;j++){
        cl->orOqColorline[j]=0;
        for(int i=0;i<OQS;i++){
            cl->orOqColorline[j]|=cl->oqColorline[i][j];
        }
     }
}

void getQsDisDxy(struct qs &a,int t,int oq,double&dx,double &dy){
    
}
extern double layerOpt[14];
void calcOqColorline(struct qs &a){
    double v;
    int i,j;
    struct rgb c;
    struct hsv_colour hsv_c; 
    struct rgb_colour rgb_c;
    
    int skeep;
    maxoqs=a.oqs;
   // plog("calcOqColorline");
    for(j=0;j<maxoqs;j++){
 //       oqColorline[j]=
        skeep=0;
        for(i=0;i<COLORLINELEN;i++){
            int next,prev,ii;
            double d,dxn,dyn,dxp,dyp,dx,dy;
            ii=(i*(j/2+1))%COLORLINELEN;
            prev=Find_Prev_Point(ii,a.tones);
            next=Find_Next_Point(ii,a.tones);
            d=Find_Dist_Prev_Point(ii,a.tones);     

            hsv_c.h=ii/(double)COLORLINELEN;
            double q,w,dq,dw,dis;
            q=getQs(&a,next,j);
            w=getQs(&a,prev,j);
            
            getQsDisDxy(a,next,j,dxn,dyn);
            getQsDisDxy(a,prev,j,dxp,dxp);
            
            dq=getQsDis(&a,next,j);
            dw=getQsDis(&a,prev,j);

           // dx=dxn*d+dxp*(1-d);
           // dy=dyn*d+dyp*(1-d);

            
//            q=minValue(q,0.3);
  //          w=minValue(w,0.3);
            
            dis=dq*d+dw*(1-d);
            double disl0;
            disl0=(0.4+0.6*dis);
    //        if(!chance(dis)){
      //          hsv_c.h+=0.5;
        //        if(hsv_c.h>=1.)
          //          hsv_c.h-=1.;
            
            //}
            if(chance(sqrt(sqrt(sqrt(sqrt(sqrt((1-dis)))))))){
                hsv_c.s=disl0*cl->oqColorlineSat[j];
                hsv_c.v=(dis/2+0.5)*(q*d+w*(1-d))*cl->oqColorlineVal[j];
            }else{
                hsv_c.s=cl->oqColorlineSat[j];
                hsv_c.v=(q*d+w*(1-d))*cl->oqColorlineVal[j];
            }
            
           double cdis;
            dx=0;
            dy=0;

           if(layerOpt[12]>0.0001){
               cdis=(dis-(1-layerOpt[12]))/(layerOpt[12]);
           
                if(cdis<1.){
                   dx=(rand()%31-15)*(1-cdis)*layerOpt[13];
                   dy=(rand()%31-15)*(1-cdis)*layerOpt[13];
                }
            }
            hsv2rgb(&hsv_c,&rgb_c);
            c=rgb_colour2rgb(&rgb_c);
          //  if(chance(sqrt(sqrt(sqrt(sqrt(sqrt((1-dis)))))))){
            //    skeep=3;
          //  }
            
            if(skeep==0){
               tcl.oqColorline[j][i]=*((Uint32*)(&c));
               tcl.oqColorlineDx[j][i]=dx;
               tcl.oqColorlineDy[j][i]=dy;

           } else{
                skeep--;
                tcl.oqColorline[j][i]=rand()%(256*256)+(rand()%256)*256*256;                
            }
        }
    
    }
    int resizedoqs=0;
    int oqpresent;
    int oqInFraq[OQS];
    for(i=0;i<OQS;i++){
        oqpresent=0;
        oqInFraq[i]=0;
            for(j=0;j<OQS;j++){
                if(cl->mapOq[i][j]){
                    oqpresent=1;
                    oqInFraq[i]++;
                }
            }
            if(oqpresent)
             resizedoqs++;
    }
    maxoqs=resizedoqs;
    int oqcount;
    for(i=0;i<OQS;i++){
            oqcount=0;
            for(j=0;j<OQS;j++){
                if(cl->mapOq[i][j]){
                    zesizeColorLine(cl->oqColorline[i] + oqcount*COLORLINELEN/oqInFraq[i],tcl.oqColorline[j],oqInFraq[i]);
                    zesizeColorLineDcoords(cl->oqColorlineDx[i] + oqcount*COLORLINELEN/oqInFraq[i],tcl.oqColorlineDx[j],oqInFraq[i]);
                    zesizeColorLineDcoords(cl->oqColorlineDy[i] + oqcount*COLORLINELEN/oqInFraq[i],tcl.oqColorlineDy[j],oqInFraq[i]);
                    oqcount++;
                }
            }
    
    }    
    calcOrOqColorline();
}    

void drawOqColorLines(SDL_Surface*screen,int x1,int y1,int x2,int y2){
    int i,j,w,h;
    w=abs(x2-x1);
    h=abs(y2-y1);
    if(x2<x1)
        x1=x2;  
    if(y2<y1)
        y1=y2;  
    
    
    for(i=0;i<maxoqs;i++){
        for(j=0;j<COLORLINELEN;j++){           
            bar(screen,x1+j*w/COLORLINELEN,y1+i*h/(maxoqs+1),x1+(j+1)*w/COLORLINELEN-1,y1+(i+1)*h/(maxoqs+1),cl->oqColorline[maxoqs-1-i][j]);    
        
        }
    }
    for(j=0;j<COLORLINELEN;j++){           
            bar(screen,x1+j*w/COLORLINELEN,y1+i*h/(maxoqs+1),x1+(j+1)*w/COLORLINELEN-1,y1+(i+1)*h/(maxoqs+1),cl->orOqColorline[j]);    
        
        }
    

}
void drawOqColorLines(SDL_Surface*screen){
    drawOqColorLines(screen,0,0,screen->w-1,screen->h-1);
}
#endif
#ifndef PIANOMOD
#define PIANOMOD
#include<SDL/SDL.h>
#include"graphutil.cpp"
int koefx1[4]={3,3,1,1};
int koefx2[4]={1,1,3,3};

int koefy1[4]={1,3,3,1};
int koefy2[4]={3,1,1,3};

int k2x1[4][3]={
                {2,0,0},
                {2,0,0},
                {1,1,0},//1
                {1,1,0}//1
                };
int k2y1[4][3]={
                {1, 1, 0},
                {2, 0, 0},
                {2, 0, 0},
                {1, 1, 0}//1
                };
int k2x2[4][3]={
                {1, 1, 0},
                {1, 1, 0},
                {0, 2, 0},
                {0, 2, 0}
                };
int k2y2[4][3]={
                {0, 2, 0},
                {1, 1, 0},
                {1, 1, 0},
                {0, 2, 0}
                };

int kdir[4]={-1,1,1,-1};
int ktype[4]={0,0,0,2};



SDL_Surface* pianoScreen=NULL;
Uint32(*colorSeq)() = NULL;
int lPianoX=0;
int lPianoY=0;
//int pianoColor=0;
int seqno=0;

void beginPiano(SDL_Surface* screen,Uint32(*cs)()){
     pianoScreen=screen;
     colorSeq=cs;
     lPianoX=-1;
     seqno=0;
     lPianoY=-1;
     //pianoColor=c;
}
void addPianoPoint(int x,int y){
    int i,j;
    if(lPianoX!=-1){
        drawColoredLine(pianoScreen,lPianoX,lPianoY,x,y,colorSeq);
      //  SDL_Flip( pianoScreen ); 
        //delay(100);
//        for(j=0;j<1000;j++)
  //      for(i=0;i<10000;i++)
    //    {}
    }
    lPianoX=x;
    lPianoY=y;
}

void qPiano(int x1,int y1,int x2,int y2,int type,int dir,int deep){
    int x;
    int y;
    int k,i;
    if(deep>0){
           for(k=(dir>0)?0:4,i=0;  (dir>0 && k<4) ||( dir<0 && k>=1);k+=sign(dir),i++){
                
                qPiano(   (k2x1[(k+type)%4][0]*x1 + k2x1[(k+type)%4][1]*x2 + k2x1[(k+type)%4][2])/2,
                        (k2y1[(k+type)%4][0]*y1 + k2y1[(k+type)%4][1]*y2 + k2y1[(k+type)%4][2])/2,
                        (k2x2[(k+type)%4][0]*x1 + k2x2[(k+type)%4][1]*x2 + k2x2[(k+type)%4][2])/2,
                        (k2y2[(k+type)%4][0]*y1 + k2y2[(k+type)%4][1]*y2 + k2y2[(k+type)%4][2])/2
                        
                        ,type+ktype[i],dir*kdir[i],deep-1);
            }
    
    
        /*if(dir>0){
            
            qPiano(x1,(y1+y2+1)/2,(x1+x2)/2,y2,type+1,-dir,deep-1);   //1
            qPiano(x1,y1,(x1+x2)/2,(y1+y2)/2,type,dir,deep-1);       //2
            qPiano((x1+x2+1)/2,y1,x2,(y1+y2)/2,type,dir,deep-1);     //3
            qPiano((x1+x2+1)/2,(y1+y2+1)/2,x2,y2,type+3,-dir,deep-1);//4
        }else{
            qPiano(x1,(y1+y2+1)/2,(x1+x2)/2,y2,type+3,-dir,deep-1);   //1
            qPiano((x1+x2+1)/2,(y1+y2+1)/2,x2,y2,type+1,-dir,deep-1);//4
            qPiano((x1+x2+1)/2,y1,x2,(y1+y2)/2,type,dir,deep-1);     //3
            qPiano(x1,y1,(x1+x2)/2,(y1+y2)/2,type,dir,deep-1);       //2
            
        }
    */
    }else{
         for(k=(dir>0)?0:4; (dir>0 && k<4) ||( dir<0 && k>=1);k+=sign(dir)){
             x=(  x1*koefx1[(k+type)%4]    +x2*koefx2[(k+type)%4]    )/4;
             y=(  y1*koefy1[(k+type)%4]    +y2*koefy2[(k+type)%4])/4;
             addPianoPoint(x,y);
         }        
        
    }
}

Uint32 colorSeq1Buf[4096];
int colorSeq1BufReady=0;
void initColorSeq1(){
    int i;
    if(!colorSeq1BufReady){
        colorSeq1BufReady=1;
        for(i=0;i<4094;i++){
            struct rgb a;
            a.r=255*sin(i*M_PI/100);
            a.g=255*sin(i*M_PI/80);
            a.b=255*sin(i*M_PI/120);        
            colorSeq1Buf[i]=*((Uint32*)&a );
        }
    }

}
//#define SEQLEN 262144
//#define SEQMOD2 262143
//#define SEQLEN 8192
//#define SEQMOD2 8191


//Sint64 colorSeq2Len=-1;



Uint32 colorSeq1(){
    seqno++;
    return colorSeq1Buf[seqno&4095];
}

void drawPiano(SDL_Surface* screen,int deep){
   initColorSeq1();
    beginPiano(screen,colorSeq1);
   // qPiano(rand()%4,rand()%4,screen->w-1-rand()%4,screen->h-1-rand()%4,0,1,6);
 qPiano(0,0,screen->w-1,screen->h-1,0,1,deep);
}
void drawPianoBar(SDL_Surface* screen,int x1,int y1,int x2,int y2,int deep){
   initColorSeq1();
    beginPiano(screen,colorSeq1);
   // qPiano(rand()%4,rand()%4,screen->w-1-rand()%4,screen->h-1-rand()%4,0,1,6);
 qPiano(x1,y1,x2,y2,0,1,deep);
}

void drawPianoBarScale(SDL_Surface* screen,int x1,int y1,int x2,int y2,int deep,int scale){
   initColorSeq1();
    beginPiano(screen,colorSeq1);
   // qPiano(rand()%4,rand()%4,screen->w-1-rand()%4,screen->h-1-rand()%4,0,1,6);
 qPiano((x1*(scale)+x2*(100-scale))/100,(y1*scale+y2*(100-scale))/100,(x2*(scale)+x1*(100-scale))/100,(y2*scale+y1*(100-scale))/100,0,1,deep);
}
#endif
#include<SDL/SDL.h>
#include"graphutil.cpp"
#include"colors.cpp"
extern double wind;

void  inline drawLines(SDL_Surface* sc,int x1,int y1,int x2,int y2,Uint32 pifColor, int repeat);
void  inline drawColoredLinesSeq2(SDL_Surface* sc,int x1,int y1,int x2,int y2, int repeat);
void  inline drawColoredLinesSeq2(SDL_Surface* sc,int x1,int y1,int x2,int y2, int repeat,int curDeep);
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
#define max(a,b) ((a)>(b))?(a):(b)
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


void inline circlesColorSeq(SDL_Surface* sc,int x,int y,int r,int repeat,int deep){
    int nx,ny;

    
    int i;
    int j;
    int n;
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
void  inline drawColoredLinesSeq2(SDL_Surface* sc,int x1,int y1,int x2,int y2, int repeat){
    drawColoredLinesSeq2(sc,x1,y1,x2,y2,repeat,0);
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
                    circlesColorSeq(sc,(x1+x2+x1+x+x2+x)/4,(y1+y2+y1+y+y2+y)/4,r,repeat,curDeep);
                    if(parity){
                        circlesColorSeq(sc,sw-(x1+x2+x1+x+x2+x)/4,sh-(y1+y2+y1+y+y2+y)/4,r,repeat,curDeep);
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
#define eqEPS 0.0000000001
#define notEq(a,b) ((fabs((a)-(b))>eqEPS)?1:0)

#define SHIFT 50
#define CTRL  37
#define ALT   64
#define BACKSPACE 22
#include"koefs.cpp"
extern short int keys[256];
extern int mode;
extern int soundControllFlag;
extern int pifPosition;


/*
double pifColorSpeedr=0.01;
double pifColorSpeedg=0.11;
double pifColorSpeedb=1.11;
*/



double nextRational(double r){
       int a,b;
       double rr,ans;
       //char s[128]="Next Rational: 1\n";
       ans=5.;
       for(b=1;b<60;b++){
        for(a=0;a<=b && a<b ;a++){
            rr=((double)a)/b;
            if(notEq(r,rr) && rr>r && rr<ans){
                ans=rr;
                //sprintf(s,"Next Rational: %d/%d\n",a,b);
            }
        }
       
       }
      //  printf("%s",s);
    return ans;
}

double previusRational(double r){
       int a,b;
       double rr,ans;
       //char s[128]="Prev Rational: 0\n";
       ans=0;
       for(b=1;b<60;b++){
        for(a=0;a<=b && a<b ;a++){
            rr=((double)a)/b;
            if(notEq(r,rr) && rr<r && rr>ans){
        //        sprintf(s,"Prev Rational: %d/%d\n",a,b);
                ans=rr;
            }
        }
       
       }
      // printf("%s",s);
    return ans;
}


void pifKeyboardControll(){
    double*ck;
    ck=controllKoef;
    if(mode!=5)
        return;
   // if(keys[96]==2){
   //     ALLFRAQ=!ALLFRAQ;
   // }
    /*
    
    ck[0*KOEFNUM+1]=7;
    ck[0*KOEFNUM+0]=7;
    ck[0*KOEFNUM+4]=11;
    
    //pifangle
    dkoef[5]=M_PI/10000;
    
    
    
    //pscale
    ck[4*KOEFNUM+6]=10;
    koefascell[4]=1./10.0;
    
    //pwind
    ck[3*KOEFNUM+5]=10;
    koefascell[3]=1./10.0;
    
    
    */
    
   
    
    
    if(keys[64]){//alt
        if(keys[55] == 2){
            ck[0*KOEFNUM+0]=ck[0*KOEFNUM+0]*1.1;            
        }
    
        if(keys[54] == 2){
            ck[0*KOEFNUM+0]=ck[0*KOEFNUM+0]/1.1;            
        }    
        if(keys[46]){
                zeros[3]=zeros[3]+0.03;
             }                              // l
        if(keys[59]){

                zeros[3]=zeros[3]-0.03;
            }                               // ,
         if(keys[47]){

                zeros[4]=zeros[4]+0.03;
         }                             // ;
         if(keys[60]){

                zeros[4]=zeros[4]-0.03;
          }                           
        
        
    }
     if(keys[50]){//shift
      /*  if(keys[55] == 2){
            ck[0*KOEFNUM+1]=ck[0*KOEFNUM+1]*1.1;            
        }
    
        if(keys[54] == 2){
            ck[0*KOEFNUM+1]=ck[0*KOEFNUM+1]/1.1;            
        } 
        */
        if(keys[46]){
                ck[3*KOEFNUM+5]=ck[3*KOEFNUM+5]*1.1;
             }                              // l
        if(keys[59]){

                ck[3*KOEFNUM+5]=ck[3*KOEFNUM+5]/1.1;
            }                               // ,
         if(keys[47]){

                ck[4*KOEFNUM+6]=ck[4*KOEFNUM+6]*1.1;
         }                             // ;
         if(keys[60]){

                ck[4*KOEFNUM+6]=ck[4*KOEFNUM+6]/1.1;
          }         
        
        
           
    }
    if(keys[37]){//ctrl
        if(keys[55] == 2){
            ck[0*KOEFNUM+4]=ck[0*KOEFNUM+4]*1.1;            
        }
    
        if(keys[54] == 2){
            ck[0*KOEFNUM+4]=ck[0*KOEFNUM+4]/1.1;            
        }    

                          



    }
    
    if(keys[45]==2){
        zeros[9]=zeros[9]+1.;   //k
     }
    if(keys[44]==2){  //j
        if(zeros[9]>1.001)
            zeros[9]=zeros[9]-1.;   
     }
     if(keys[30]==2){  //j
        int pifParity;
        pifParity=zeros[10];
        pifParity=pifParity++;
        pifParity=pifParity&1;
        zeros[10]=pifParity;
        
        //printf("pifParity: %d\n",pifParity);

     }
     
     
    if(keys[23]==2){
        soundControllFlag=!soundControllFlag;   
     }
    if(keys[110]){
            setZeroPifControllKoef();   
    }
    if(keys[52] == 2){
            int z;
            z=zeros[1];
            z++;
            z=z%4;
            zeros[1]=z;
            //printf("naked! %f\n",zeros[1]);

     }                          // z
     if(keys[53] == 2){
        int z;
        z=zeros[2];
        if(z)
         zeros[2]=0.;
         else
         zeros[2]=1.;
            
      }                      // x
      if(keys[40] == 2){
        pifPosition=!pifPosition;
      }  //d
      if(keys[54] == 2){//c
            int z;
            if(keys[37]){//ctrl
                if(zeros[15]>0.9999)
                    zeros[15]=zeros[15]-1.;
                
            }else
            if(!keys[50]){///!SHUFT
            
                z=zeros[0];
                if(z)
                     zeros[0]=z-1;
           }else{//SHIFT
              
               z=maxDrawKoef[0];
                if(z>2)
                     maxDrawKoef[0]=z-1;
           
           }
       }                        
       
       
       if(keys[55] == 2){//v
            int z;
            if(keys[37]){//ctrl
                if(zeros[15]<9)
                    zeros[15]=zeros[15]+1.;
                
            }else
            if(!keys[50]){///!SHUFT
                z=zeros[0];
                if(z<16)
                     zeros[0]=z+1;
            }else{///SHIFT
                z=maxDrawKoef[0];
                if(z<16)
                     maxDrawKoef[0]=z+1;
            
            }

        }
        
        
        
        
        
        if(keys[46]&&keys[CTRL]){

                koefascell[3]*=1.1;
             }                              // l
        if(keys[59]&&keys[CTRL]){

                koefascell[3]/=1.1;
            }                               // ,
         if(keys[47]&&keys[CTRL]){

                koefascell[4]*=1.1;
         }                             // ;
         if(keys[60]&&keys[CTRL]){

                koefascell[4]/=1.1;
          }                             // .
          if(keys[48]){
            //if(mode==5)
               if(keys[64]){//alt
                    if(keys[48]==2){
                        dkoef[5]=nextRational(dkoef[5]/M_PI/2.)*M_PI*2.;
                    }
                }else if(keys[50])
                    dkoef[5]*=1.0001;
                else 
                    dkoef[5]*=1.1;
          }                            // '
          if(keys[61]){
                if(keys[64]){
                    if(keys[61]==2){
                        dkoef[5]=previusRational(dkoef[5]/M_PI/2.)*M_PI*2.;
                    }
                 }else if(keys[50]){
                    dkoef[5]/=1.0001;
                 }else
                    dkoef[5]/=1.1;
                
           }                             // /
           if(keys[56]==2){

                   dkoef[3]*=-1;
           }                              // b
           if(keys[57]==2){

                dkoef[4]*=-1;
            }                              // n
            if(keys[58]==2){

                    dkoef[5]*=-1;
            }                              // m
            if(keys[27]){

                    zeros[6]*=1.1;
            }                              // r
            if(keys[41]){

                    zeros[6]/=1.1;
             }                              // f
             if(keys[28]){

                    zeros[7]*=1.1;
             }                              // g
             if(keys[42]){

                    zeros[7]/=1.1;
             }                              // f
             if(keys[29]){

                    zeros[8]*=1.1;
             }                              // g
             if(keys[43]){

                    zeros[8]/=1.1;
             }

    if(keys[112]){
       if(!keys[64]){//!ALT{
          if(zeros[13] < 180. && keys[112] == 2)
            zeros[13]=zeros[13]+1.;
        }else{
           ck[12*KOEFNUM+6]=ck[12*KOEFNUM+6]*1.01;
           ck[12*KOEFNUM+5]=ck[12*KOEFNUM+5]*1.01;;
        }
    }
    if(keys[117]){
        if(!keys[64]){//!ALT{
            if(zeros[13] > 3.01 && keys[117] == 2)
                zeros[13]=zeros[13]-1.;
        }else{
           ck[12*KOEFNUM+6]=ck[12*KOEFNUM+6]/1.01;
           ck[12*KOEFNUM+5]=ck[12*KOEFNUM+5]/1.01;;
        }
    }


}

extern int butParam;
extern double colorSeqSplash;
extern double loadPrevSplash;
extern double loadNextSplash;
void changeColorSeq(){
            colorSeqVar++;
            colorSeqVar=colorSeqVar%4;
            colorSeq2BufReady=0;
            colorSeqSplash=1.;
}

void loadPreset(){
    if (butParam==0){
        loadPrev();
        loadPrevSplash=1;
    }
    if (butParam==1){
        loadNext();
        loadNextSplash=1;
    }

}

extern int dialogParam;
extern int dX1;
extern int dY1;
extern int dX2;
extern int dY2;
extern SDL_Surface* dSc;
void pifRepeatMod(){
    if(butParam==0){
        if(zeros[9]>0)
            zeros[9]=zeros[9]-1.;
    }
    if(butParam==1){
        pifPosition=!pifPosition;
    }
    if(butParam==2){
        int pifParity;
        pifParity=zeros[10];
        pifParity=pifParity++;
        pifParity=pifParity&1;
        zeros[10]=pifParity;
    }
    if(butParam==3){
        if(zeros[9]<60)
            zeros[9]=zeros[9]+1.;
    }
    
    

}
void editAngle(){
    bar(dSc,dX1,dY1,dX2,dY2,0);
    int sx1;
    sx1=dX1;
    if(dialogParam==5){
        sx1=(dX1*9+dX2)/10;
        addButton(dX1,dY1,sx1,(dY1*3+dY2)/4,0,pifRepeatMod);
        rectangle(dSc,dX1,dY1,sx1,(dY1*3+dY2)/4,BORDERCOLOR);

        addButton(dX1,(dY1*3+dY2)/4,sx1,(dY1*2+dY2*2)/4,1,pifRepeatMod);
        rectangle(dSc,dX1,(dY1*3+dY2)/4,sx1,(dY1*2+dY2*2)/4,BORDERCOLOR);

        addButton(dX1,(dY1*2+dY2*2)/4,sx1,(dY1+dY2*3)/4,2,pifRepeatMod);
        rectangle(dSc,dX1,(dY1*2+dY2*2)/4,sx1,(dY1+dY2*3)/4,BORDERCOLOR);

        addButton(dX1,(dY1+dY2*3)/4,sx1,(dY2),3,pifRepeatMod);
        rectangle(dSc,dX1,(dY1+dY2*3)/4,sx1,(dY2),BORDERCOLOR);
    
    }
    rizePannel=1;
    drawAnglePannelStack(dSc,sx1,dY1,dX2,dY2,dialogParam);
    rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);
    
    
}
void editBar(){
 
    bar(dSc,dX1,dY1,dX2,dY2,0);
    rizePannel=1;
    drawPannelStack(dSc,dX1,dY1,dX2,dY2,dialogParam);
    rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);
    
    
}
void drawFilterPannelStack(SDL_Surface*screen,int x1,int y1,int x2,int y2,int k);
void editFilter(){
 
    bar(dSc,dX1,dY1,dX2,dY2,0);
    rizePannel=1;
    drawFilterPannelStack(dSc,dX1,dY1,dX2,dY2,dialogParam);
    rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);
    
    
}

void rizeAnglePannel(){
    addDialog(butParam,editAngle);
}
void rizeBarPannel(){
    addDialog(butParam,editBar);
}
void rizeFilterPannel(){
    addDialog(butParam,editFilter);
}



struct layer*OSDtauch=NULL;
#define OSDh 90
#define OSDw 120
void markOSDTauch(){
    int a;
    a=OSDtauch->p[butParam];
    a=a+80;
    if(a>255)
        a=255;
    OSDtauch->p[butParam]=a;
    
}

void OSDDone(){
    printf("osd ");
    sendLayer(OSDtauch,stdout);    
//    while(1);
}
void OSDCreate(){
    int i,j;
    bar(dSc,dX1,dY1,dX2,dY2,0);
    for(i=0;i<OSDh;i++)
        for(j=0;j<OSDw;j++){
            int x1,y1,x2,y2,mx,my;
            double m;
            x1=(dX1*(OSDw-j) + dX2*(j) )/ (OSDw);
            y1=(dY1*(OSDh-i) + dY2*(i) )/ (OSDh);

            x2=(dX1*(OSDw-j-1) + dX2*(j+1) )/ (OSDw) -1;
            y2=(dY1*(OSDh-i-1) + dY2*(i+1) )/ (OSDh) -1;
            addSButton(x1 ,y1,x2,y2,j+i*OSDw,markOSDTauch);
            m=1 - OSDtauch->p[i*OSDw+j]/255.;
            mx=(dX2-dX1)/OSDw * m/2;
            
            my=(dY2-dY1)/OSDh * m/2;
            
            rectangle(dSc,x1+mx,y1+my,x2-mx,y2-my,WHITE);
        }
        
 
 
    rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);
}

void rizeOSD(){
    if(OSDtauch == NULL){
        OSDtauch=makeLayer(OSDw,OSDh);
    }
    if(OSDtauch!=NULL){
        int i,j;
        for(i=0;i<OSDh;i++)
            for(j=0;j<OSDw;j++){
                OSDtauch->p[i*OSDw+j]=0;
            }
        
        addDialog(0,OSDCreate,OSDDone);
    }
}
#include <SDL/SDL.h>
#include"graphutil.cpp"
#ifndef M_SENSE
#define M_SENSE
void drawLine(SDL_Surface *sc,int x1, int y1, int x2, int y2,int c);
int detectTone(double freq);
int detectOk(double freq);
double findCos(struct qs a);

#include"sens.cpp"

struct qs{
    char tones;
    char oqs;
    double* ks;
    double *dises;
    double *dis;
    struct sense*sns;    
    int bufsize;
};


#include"cos.cpp"
#define DISES 13
int kosd[DISES]={0,12,7,5,3,4,8,9,6,2,10,1,11};
//double kosv[13]={1,1.4,0.93,0.87,0.82,0.81,0.79,0.75,0.71,0.68,0.65,0.4,0.34};
double kosv[DISES]={2,2,0.95,0.83,0.82,0.81,0.79,0.75,0.71,0.68,0.65,0.4,0.34};


unsigned int getDisVectorT;
int myR(int min,int max){
    if(min>=max){
        return min;
    }
    return rand()%(max-min+1)-min;
}
void getDisVector(int dt,int max,double&dx,double&dy){
    dt=abs(dt)%12;
    switch (dt){
        case 0: dx=0;dy=0;break;//
        case 1: dx=myR(-max,max);dy=myR(-max,max);break;
        case 2: dx=myR(-max/2,max/2);dy=myR(-max/2,max/2);break;
        case 3: dx=myR(-max/8,max/8);dy=myR(-max/4,max/4);break;
        case 4: dx=myR(-max/3,max/3);dy=myR(-max/3,max/3);break;
        case 5: dx=myR(-max/4,max/4);dy=myR(-max/8,max/8);break;
        case 6: dx=myR(-max/2,max/2);dy=myR(-max/2,max/2);break;
        case 7: dx=myR(-max/8,max/8);dy=myR(-max/8,max/8);break;
        case 8: dx=myR(-max/2,max/2);dy=myR(-max/3,max/3);break;
        case 9: dx=myR(-max/3,max/3);dy=myR(-max/2,max/2);break;
        case 10: dx=myR(-max,max);dy=myR(-max/2,max/2);break;
        case 11: dx=myR(-max,max);dy=myR(-max,max);break;
        case 12: dx=getDisVectorT%2;dy=(getDisVectorT/2)%2;break;//
    }
    getDisVectorT++;
}
int  reallocQs(struct qs*q,int tones,int oq);
void QSmorph(struct qs*oldl,struct qs*newl,double d){
    int i,j;
    double*o,*n;
    reallocQs(oldl,newl->tones,newl->oqs);
    if(d<0.)
        d=0.;
    if(d>1.)
        d=1.;
    o=oldl->ks;
    n=newl->ks;
    
    if(d<0.0001){
        for(i=0;i<oldl->oqs;i++)
            for(j=0;j<oldl->tones;j++,o++,n++){
                *o=*n;

            }
        return;
    }    
    
    for(i=0;i<oldl->oqs;i++)
        for(j=0;j<oldl->tones;j++,o++,n++){
            *o=(*o)*d + (*n)*(1.-d);
        }



}

int comparedVolumes(double me,double him){
    double t;
    if(me<0.001||him<0.001)
        return 0;
    if(me>him){
        t=me;
        me=him;
        him=t;    
    }// now, me - smaller than him

    if(me*10>him)
        return 1;
    return 0;
}


double compareVolumesKoef(double me,double him){
    double t;
    if(me>him){
        t=me;
        me=him;
        him=t;    
    }// now, me - smaller than him

    if(me<0.001||him<0.001)
        return 0.;
    if(me*10<him)
        return 0.;
    return 2/(him*him*him*him*him*him/me/me/me/me/me/me +me*me*me*me*me*me/him/him/him/him/him/him);



}


double findDis(int di){
    di=abs(di);
    for(int i=0;i<DISES;i++){
        if(di==kosd[i])
            return kosv[i];
    }
    return 1;
}
double findNumDis(int di){
    di=abs(di);
    for(int i=0;i<DISES;i++){
        if(di==kosd[i])
            return i;
    }
    return -1;
}
double diss[DISES];
void calcQSDis(struct qs*q){
    int i,j,me,di,him;
//    double dx,dy;
    double dis,alld;
    for(i=0;i<DISES;i++){
        diss[i]=0;
    
    }
  //  double alld;
    alld=0;
    
    for(i=0;i<q->oqs;i++)
        for(j=0;j<q->tones;j++){
               dis=0.5;
                me=j+i*(q->tones);
                //dx=0.;
                //dy=0.;
                for(di=-11;di<=12;di++){
                    him=me+di;
                    if(him>=0){
                      double cd;
                      cd=compareVolumesKoef(q->ks[me],q->ks[him]);                    
                      int a;      
                      a=findNumDis(di);
                      
                      if(a>=0){
                            alld+=cd*q->ks[me];
                            diss[a]+=cd*q->ks[me];
                      }

                      
                      dis=dis*(1-(1-findDis(di))*cd);                    
                    }
                
                }
                if(dis>1.)
                    dis=1.;
                if(dis<0.)
                    dis=0.;
                q->dis[me]=dis;
        }
    for(i=0;i<DISES;i++){
        
            diss[i]=diss[i]/alld;
    }


}

int  reallocQs(struct qs*q,int tones,int oq){
    if(q->ks==NULL){
        q->ks=(double*)malloc(tones*oq*sizeof(double));
        if(q->ks==NULL)
            return -1;
        memset(q->ks,0,tones*oq*sizeof(double));
    
        q->dis=(double*)malloc(tones*oq*sizeof(double));
        if(q->dis==NULL)
            return -1;
    
        q->dises=(double*)malloc(2*tones*tones*oq*sizeof(double));
        if(q->dises==NULL)
            return -1;
    


        q->sns=(struct sense*)malloc(tones*oq*sizeof(struct sense));
        if(q->sns==NULL)
            return -1;
        zeroSenses(q->sns,tones*oq);
        q->tones=tones;
        q->oqs=oq;
        q->bufsize=oq*tones;
        return 0;
    }
    if(tones*oq>q->bufsize){
        if(q->ks!=NULL)
            free(q->ks);
        if(q->dis!=NULL)
            free(q->dis);
        q->ks=(double*)malloc(tones*oq*sizeof(double));
        if(q->ks==NULL)
            return -1;
        memset(q->ks,0,tones*oq*sizeof(double));

        q->dis=(double*)malloc(tones*oq*sizeof(double));
        if(q->dis==NULL)
            return -1;
        q->dises=(double*)malloc(2*tones*tones*oq*sizeof(double));
        if(q->dises==NULL)
            return -1;


        if(q->sns!=NULL)
            free(q->sns);
        q->sns=(struct sense*)malloc(tones*oq*sizeof(struct sense));
        if(q->sns==NULL)
            return -1;
        zeroSenses(q->sns,tones*oq);
        q->tones=tones;
        q->oqs=oq;
        q->bufsize=oq*tones;
        return 0;
    }
    q->tones=tones;
    q->oqs=oq;
    return 0;
}

void setQs(struct qs*r,int t,int oq,double value){
    int adr;
    if(t>=r->tones || oq>=r->oqs ||t<0||oq<0)
        return;
    
    adr=t+oq*(r->tones);
 //   soft
    r->ks[adr]=senseValue(&(r->sns[adr]),value);
}

void setQs(struct qs*r,int t,int oq,double value,double soft){
    int adr;
    if(t>=r->tones || oq>=r->oqs ||t<0||oq<0)
        return;
    
    adr=t+oq*(r->tones);
 //   soft
    r->sns[adr].soft=soft;
    r->ks[adr]=senseValue(&(r->sns[adr]),value);
}

void a2tq(int a,int *t,int *q,int tones,double soft){
    *q=0;
    while(a<0){
        *q=(*q)-1;
        a=a+tones;    
    }
    *t=a%tones;
    *q=*q+a/tones;
}

double qs_a[20480];
double qs_fr[20480];


void speq2qs(double*sound_a,double*freqs,int n,int tones,int minoq,int maxoq,struct qs*r,double soft){
    int i;
    double summ,skipValue;
    int col,t,oq,startSkip;
    int lt,loq;
    
    for(i=0;i<n;i++){
   //     fprintf(stderr,"(freq=%3.1f amp=%3.1f)",freqs[i],sound_a[i]);
    
    }
    //fprintf(stderr,"\n\n\n\n");
    //fflush(stderr);
    lt=-1;
    loq=-1;
    tones=12;//QBUG
    startSkip=minoq*tones-1;
    skipValue=0.;
    reallocQs(r,tones,maxoq-minoq+1);
    col=0;
    summ=0;
    for(i=0;i<n;i++){
        if(freqs[i]<0.001)
            continue;
        t=detectTone(freqs[i]);          
        oq=detectOk(freqs[i]);
        if(t==lt&&oq==loq){
            summ=summ+sound_a[i];
            col++;        
        }else{
            if(lt!=-1 && col!=0){
                if(loq>=minoq&&loq<=maxoq){
                    int la,a;
                    double v;
                    v=summ/col;
                    la=lt+loq*tones;
              //      if(startSkip!=-1000){
                //           for(int i=startSkip;i<startSkip-1/*la*/;i++){
                  //          int tt,qq;
                    //        a2tq(i,&tt,&qq,tones);
                      //      setQs(r,tt,qq-minoq,((la-i)*skipValue +  (i-startSkip)*v)/(la-startSkip+1));
                        //}
                    
                 //   }
                    
                    //a=t+oq*tones;
                    if(a-la>1){
                        startSkip=la+1;
                        skipValue=v;
                    }else{
                        startSkip=-1000;
                    }
                    //r->sns[]soft
                    setQs(r,lt,loq-minoq,v,soft);
                
                
                
                }
            }
            col=1;
            summ=sound_a[i];
            lt=t;
            loq=oq;
        }
    }
    
    if(lt!=-1 && col!=0){
        if(loq>=minoq&&loq<=maxoq){
                double v;
                int la;
                v=summ/col;
                la=lt+loq*tones;
  //              if(startSkip!=-1000){
//                    for(int i=startSkip;i<startSkip-1/*la*/;i++){
      //                  int tt,qq;
    //                    a2tq(i,&tt,&qq,tones);
        //                setQs(r,tt,qq-minoq,((la-i)*skipValue +  (i-startSkip)*v)/(la-startSkip+1));
          //          }
                
            //    }
    
        
              setQs(r,lt,loq-minoq,v,soft);
        }
    }
}
void speq2qs(double*sound_a,double*freqs,double*b_sound_a,double*b_freqs,int n,int tones,int minoq,int maxoq,struct qs*r,double soft){
    int i;
    double summ,skipValue;
    int col,t,oq,startSkip;
    int lt,loq;
    
    int c1,c2,c;
    c1=0;c2=0;c=0;
    double bl=1080;
//    fprintf(stderr,"speq2qs\n");
  //  fflush(stderr);
    
    while(b_freqs[c2]<bl){
        //if(b_freqs[c2]<b_freqs[c1]){
            qs_a[c]=b_sound_a[c2];
            qs_fr[c]=b_freqs[c2];
            c2++;
            c++;
       // }else{
         //   qs_a[c]=sound_a[c1];
           // qs_fr[c]=freqs[c1];
           // c1++;
           // c++;
       // }
    }
    while(freqs[c1]<bl && c1<n){
        c1++;
    }

    while(c1<n){
        qs_a[c]=sound_a[c1];
        qs_fr[c]=freqs[c1];
        c1++;
        c++;
    }    
    
    n=c;
    sound_a=qs_a;
    freqs=qs_fr;
    speq2qs(qs_a,qs_fr,c,tones,minoq,maxoq,r,soft);
}
void speq2qs(double*sound_a,double*freqs,double*b_sound_a,double*b_freqs,double*c_sound_a,double*c_freqs,int n,int tones,int minoq,int maxoq,struct qs*r,double soft){
    int i;
    double summ,skipValue;
    int col,t,oq,startSkip;
    int lt,loq;
    
    int c1,c2,c,c3;
    c1=0;c2=0;c=0;c3=0;
    double bl=1080;
    double cl=1000/8;
//    fprintf(stderr,"speq2qs\n");
  //  fflush(stderr);
    while(c_freqs[c3]<cl){
            qs_a[c]=c_sound_a[c3];
            qs_fr[c]=c_freqs[c3];
            c3++;
            c++;
    }
    while(freqs[c2]<cl && c2<n){
        c2++;
    }
    while(b_freqs[c2]<bl){
            qs_a[c]=b_sound_a[c2];
            qs_fr[c]=b_freqs[c2];
            c2++;
            c++;
    }
    while(freqs[c1]<bl && c1<n){
        c1++;
    }

    while(c1<n){
        qs_a[c]=sound_a[c1];
        qs_fr[c]=freqs[c1];
        c1++;
        c++;
    }    
    
    n=c;
    sound_a=qs_a;
    freqs=qs_fr;
    speq2qs(qs_a,qs_fr,c,tones,minoq,maxoq,r,soft);
}
void speq2qs(double*sound_a,double*freqs,double*b_sound_a,double*b_freqs,double*c_sound_a,double*c_freqs,double*d_sound_a,double*d_freqs,int n,int tones,int minoq,int maxoq,struct qs*r,double soft){
    int i;
    double summ,skipValue;
    int col,t,oq,startSkip;
    int lt,loq;
    
    int c1,c2,c,c3,c4;
    c1=0;c2=0;c=0;c3=0,c4=0;
    double bl=1080;
    double cl=1100/4;
    double dl=1100/8;
//    fprintf(stderr,"speq2qs\n");
  //  fflush(stderr);
    while(d_freqs[c4]<dl){
            qs_a[c]=d_sound_a[c4];
            qs_fr[c]=d_freqs[c4];
            c4++;
            c++;
    }
    while(freqs[c2]<cl && c2<n){
        c2++;
    }
    
    while(c_freqs[c3]<cl){
            qs_a[c]=c_sound_a[c3];
            qs_fr[c]=c_freqs[c3];
            c3++;
            c++;
    }
    while(freqs[c2]<cl && c2<n){
        c2++;
    }
    while(b_freqs[c2]<bl){
            qs_a[c]=b_sound_a[c2];
            qs_fr[c]=b_freqs[c2];
            c2++;
            c++;
    }
    while(freqs[c1]<bl && c1<n){
        c1++;
    }

    while(c1<n){
        qs_a[c]=sound_a[c1];
        qs_fr[c]=freqs[c1];
        c1++;
        c++;
    }    
    
    n=c;
    sound_a=qs_a;
    freqs=qs_fr;
    speq2qs(qs_a,qs_fr,c,tones,minoq,maxoq,r,soft);
}



double getQs(struct qs*r,int t,int oq){
    int adr;
    if(t>=r->tones || oq>=r->oqs)
        return 0.;
    
    adr=t+oq*(r->tones);
    return r->ks[adr];
}
double getQsDis(struct qs*r,int t,int oq){
    int adr;
    if(t>=r->tones || oq>=r->oqs)
        return 0.;
    
    adr=t+oq*(r->tones);
    return r->dis[adr];
}
#include"cos.cpp"
#include"colors.cpp"
struct sense css;    
int zero=1;
void truncNotImportant(struct qs *s,double d){
    int i,j;
    for(j=0;j<s->oqs;j++)
        for(i=0;i<s->tones;i++){
            double a,b;
            int adr;
            adr=i+j*(s->tones);
            a=s->ks[adr];
            b=a-d;
            if(b<0.)
                b=0.;
            if(d<1.){
                b=b/(1.-d);
            }else{
                b=0;
            }
            s->ks[adr]=b;
        
        }
}
void drawQs(SDL_Surface*screen,int x1,int y1,int x2,int y2,struct qs *s){
    int i,j,w,h;
    Uint32 c;
    double t;
    if(zero){
        zero=0;
        zeroSense(&css);
    
    }
    t=findCos(*s);
    t=senseValue(&css,t);
      
    
    w=(x2-x1)/s->tones;
    h=(y2-y1)/s->oqs;
//    printf("COS:%f\n",t);
    drawLine(screen,x2,y1 + (1- t)*(y2-y1),x2,y2, WHITE);    

    for(j=0;j<s->oqs;j++)
        for(i=0;i<s->tones;i++){
            double a,b;
            a=getQs(s,i,j);
           // b=a-d;
           // if(b<0.)
            //    b=0.;
           // b=b/(1-d);
            c=a*255;
            c=c|c*256|c*256*256;
            
           // if(a>=d)
                bar(screen,x1+w*i +w/3,y2-h*(j+1) +h/3,x1+w*(i+1)-w/3,y2-h*(j)-h/3,c);    
        }
}

void drawQsDis(SDL_Surface*screen,int x1,int y1,int x2,int y2){
    int i,h,w;
    double alld=0;
    h=abs(y1-y2);
    w=abs(x1-x2);
    for(i=0;i<DISES;i++){
        double a;
        a=diss[i];
        bar(screen,x1+i*w/DISES,y1+(1-a)*h,x1+(i+1)*w/DISES,y2,GRAY);
    
    }
}


#endif

void speq2qs(double*sound_a,double*freqs,int n,int tones,int minoq,int maxoq,struct qs*r);


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
   Uint32 getSoundKoefsColor(int i,double old){return 0;}
//#include "SDL_opengl.h"
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <time.h> 
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
#define min(x,y)  (((x)>(y))?(y):(x))
#include "graphutil.cpp"
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

//#include "filters/nosound.cpp"
//int SVIDanswer(const char*p);
void drawStars(SDL_Surface* screen){
    putpixel(screen,rand() % (screen->w),rand() % (screen->h),rand()); 
    SDL_Flip( screen ); 
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
    if(!connected)
        return;
    if(GetTickCount()-lastRecive>200){
        return;
    }      
    if(connected && showColorSeq){
//        writeColorSeq();
        writeColorSeq3();
    }

    sendAllMass(stdout,writeAll);
    sendSoundRawData();
    writeSoundControllValue(stdout,writeAll);
    writeVolume();
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
void draw(SDL_Surface* screen,SDL_Surface* filter,double*sk){
  // SDL_FillRect(screen,NULL, 0x000000);
 //  SDL_FillRect(filter,NULL, 0x000000);
//    plog("rabbit draw");

    if(mask==NULL){
        mask=makeLayer(layerOpt[5]*screen->w,layerOpt[6]*screen->h);
        if(mask==NULL)
            return;
        mask2=makeLayer(layerOpt[5]*screen->w,layerOpt[6]*screen->h);
        if(mask2==NULL)
            return;
        llh=layerOpt[6]*screen->h;
        llw=layerOpt[5]*screen->w;
    }
    if(llh!=layerOpt[6]*screen->h|| llw!=layerOpt[5]*screen->w){
         mask=resizeLayer(mask,layerOpt[5]*screen->w,layerOpt[6]*screen->h);
         if(mask==NULL)
            return;
         mask2=resizeLayer(mask2,layerOpt[5]*screen->w,layerOpt[6]*screen->h);
         if(mask2==NULL)
            return;
       
    
    }  
    if(mode!=6 && mode!=7){
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
    interFer(mask,layerOpt[7]*100);
    morph(mask2,mask,1);
    switch (mode){
        case 1: drawSnake(screen); break;   
        case 2:drawHohloma(screen); break;      
        case 3:draw4d(screen); break;
        case 4:drawbarcode(screen); break;
//pifDeep,pifNaked,pifColored,pifDWind,pifDScale,pifDAngle,pifColorSpeedr,pifColorSpeedg,pifColorSpeedb,pifRepeat,pifParity        
        case 5: 
        
        
        pifSoundControll(sk,zeros,dkoef,controllKoef,drawKoef,maxDrawKoef,minDrawKoef);
        drawKoefLatency(drawKoef,drawLatKoef);
//        drawMask(screen,mask2,0.2);
      //  fprintf(stderr,"drawPif!\n");
       // fflush(stderr);
        extern double pifSoft;
        pifSoft=layerOpt[10];
        pifWight=layerOpt[11];
        drawPifagor(screen,drawKoef);
       // fprintf(stderr,"drawPif ok!\n");
       // fflush(stderr);
        //prepareDefSeqNo2();
        //SeqNo2
        prepareOrSeqNo2();
        mixBWSizedOr(screen,mask2,layerOpt[0],layerOpt[1]*255,((int)(layerOpt[2]*255))  +256*((int)(layerOpt[3]*255)) + 256*256*((int)(layerOpt[4]*255)));
      
        // drawMask(screen,mask2,0.6,127);
       // mulMix(screen,mask,1);
        if(osd!=NULL){
//            mixBWSized(screen,osd,1,0,0);
              layer2particles(screen,osd,0.006,0.1,0.1,0.9);

        }
        break;
        
        case 6: drawSound(screen);break;
        
        case 7:
        
        
        drawMask(screen,mask2,0.7,0,255,0);
        
        
         break;
        case 8:
            int d;
          d=(screen->w-screen->h);            
            drawQs(screen,d,0,screen->w,screen->h-1,&qsAll);
     
     
     ////       calcOqColorline(qsAll);
     //       drawOqColorLines(screen);
            
            drawQsDis(screen,0,0,d,d);   
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
    
    holdFPS(30);  
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
        SDL_Flip( screen ); 
    //}
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
int syntaxControll(char*p){
    char term[128];
    char buf[128];
    int t1,i,t2;
    char s1[128];
    char s2[128];
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
           printf("noise:%d %d %d\n",noiseC,noiseV,noiseColor);
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



/*
double pifDeepBass=1/700.;
double pifDeepRithm=1/500;
double pifDeepCur=14./((N + 1) / 2);

double rxMax=1./100.;
double ryMax=1./100.;
*/

#include"pifkeyboardcontroll.cpp"
#include"soundkeyboardcontroll.cpp"
#include"saveload.cpp"
int keyboardControll(){
    int i;
    if(keys[KEY_ESC]){
        return 1;
    
    }
    
    if(keys[KEY_F12]==2){
            if(keys[CTRL]){
                char*p;
                p=saveNext();
            }else{
                loadNext();
            }
        
        }
    
    if(keys[KEY_F11]==2){
            if(!keys[CTRL]){
                loadPrev();
            }else{
                saveCurrent();
            }
        
        }
    
    
    
    for(int i=0;i<10;i++){
        if(keys[i+KEY_F1]==2){
            char name[32];
            sprintf(name,"quick_%d.r2",i+1);
            if(keys[CTRL]){
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
    
    pifKeyboardControll();
    soundKeyboardControll();
    for(i=0;i<256;i++)
        if(keys[i])
            keys[i]=1;
    return 0;
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
    srand (time(NULL));
    SDL_putenv((char*)"SDL_VIDEO_WINDOW_POS=0,0");
    initStdIn();
    for(i=1;i<argc;i++){
        printf("Catch:%s\n",args[i]);
        if(!strcmp(args[i],"-window") && i+1<argc){
            windowXRes=-1;
            windowYRes=-1;
            i++;
            sscanf(args[i],"%dx%d",&windowXRes,&windowYRes);
            if(windowXRes > 0 && windowYRes > 0 ){
                windowflag=1;  
     
            }
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
        printf("cant init sound\n");
        fflush (stdout);
    }
     
     
     zeroAsc();
     myPointer = SDL_GetVideoInfo();
     W=myPointer->current_w;
     H=myPointer->current_h;
     
     if(windowflag){
        W=windowXRes;
        H=windowYRes;
     }        
        
     screen = SDL_SetVideoMode(W , H, 32, SDL_HWSURFACE |  ((windowflag&&(!doumode))&&(!noframe)?0:SDL_NOFRAME) | SDL_DOUBLEBUF/*|SDL_GL_DOUBLEBUFFER |SDL_OPENGL */); 
   
   
     if(doumode){
        char tmps[128];
        sprintf(tmps,"SDL_VIDEO_WINDOW_POS=%d,%d",windowXRes,0);
        SDL_putenv(tmps);
        controllscreen = SDL_SetVideoMode(window2XRes , window2YRes, 32, SDL_HWSURFACE |  ((windowflag&&(!doumode))?0:SDL_NOFRAME) | SDL_DOUBLEBUF/*|SDL_GL_DOUBLEBUFFER |SDL_OPENGL */); 
        if(controllscreen==NULL)
            printf("Cant init controll screen\n");
     }
     preparePutPixel(screen);
//     outputScreen=cloneScreen(screen);
     screenW=screen->w;
     screenH=screen->h;
     diag=sqrt(screenH*screenH+screenW*screenW);
     
     
     filter=cloneScreen(screen);
//    initFade(screen);
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

 load_rabbit("current.r2");
     
     while(flag){
        //printf("draw\n");
        //fflush(stdout);
      //  plog("rabbit loop");

        calcSound(soundKoefs);
        
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
        if(controll(screen)){
            break;
        }       
      // printf("%lf\n",pifColorSpeedr); 
     }
     

     
      //Quit SDL 
      printf("Saving current\n");fflush(stdout);
      save_rabbit("current.r2");
      printf("Closing sound\n");fflush(stdout);
      closeSound();
      printf("Closing rgbmixer\n");fflush(stdout);
      closeRgbMixer();
      printf("Closing fades\n");fflush(stdout);
      closeFades();
      printf("Closing SDL\n");fflush(stdout);
      SDL_Quit();
      printf("All correct!\n");fflush(stdout);
      printf("%c",EOF); 
      return 0;
}
#include<stdio.h>
#include<string.h>

#include"sendrecive.cpp"
char currentFile[128];
extern double hearingVolume;
extern double amplifierKoef;
extern double amplifierKoefHighValue;
extern double amplifierKoefLowValue;
extern int faded;
extern int rgbMixerDepth;
extern int rgbMixerDepthAuto;
extern int noiseC;
extern int noiseV;
extern int noiseColor;
extern double pifColorSpeedr;
extern double pifColorSpeedg;
extern double pifColorSpeedb;
extern int pifDeep;
extern int pifNaked;
extern int pifColored;
extern double pifDWind;
extern double pifDScale;
extern double pifDAngle;
extern int pifPosition;
extern int showColorSeq;


void zeroFilters(){
    orblurd=0;
    faded=50;
    rgbMixerDepth=0;
    
    for(int i=0;i<LAYEROPTS;i++)
        layerOpt[i]=0.;
}


int save_rabbit(const char*name){
    FILE*f;
    char s[128];
    sprintf(s,"saves/%s",name);
    f=fopen(s,"w");
    if(f==NULL){
        return -1;
    }
    sendAllMass(f,1);
    writeSoundControllValue(f,1);
    sendFilters(f,1);
    fclose(f);
    zeroLValues();   
    strcpy(currentFile,name);
    return 0;
}

void saveCurrent(){
   save_rabbit(currentFile);    
}




char loadBuf[1024];
int load_rabbit(const char*name){
    FILE*f;
    char s[128];
    sprintf(s,"saves/%s",name);
    f=fopen(s,"r");
    if(f==NULL){
        return -1;
    }
    setZeroPifControllKoef();  
    zeroOqColorLine();
    zeroFilters();
    while(!feof(f)){
        fgets(loadBuf,1024,f);
//        syntaxControll
        syntaxControll(loadBuf);
    }
    zeroLValues();   
    fclose(f);
    strcpy(currentFile,name);
    return 0;
}

char nameReturn[128];
char*saveNext(){
    for(int n=0;n<1024;n++){
        FILE*f;
        sprintf(nameReturn,"saves/quick_%d.r2",n);

        f=fopen(nameReturn,"r");
        if(f==NULL){
            f=fopen(nameReturn,"w");
            if(f!=NULL){
                fclose(f);
                sprintf(nameReturn,"quick_%d.r2",n);
                if(!save_rabbit(nameReturn)){
                    return nameReturn;
                }
            }
            
        }
        fclose(f);
    }
    return NULL;
}

char*loadNext(){
    int n;
    sscanf(currentFile,"quick_%d.r2",&n);
    n++;
    if(n<0||n>=1024)
        n=0;
    for(;n<1024;n++){
        FILE*f;
        sprintf(nameReturn,"saves/quick_%d.r2",n);
        f=fopen(nameReturn,"r");
        if(f!=NULL){
            fclose(f);
            sprintf(nameReturn,"quick_%d.r2",n);
            if(!load_rabbit(nameReturn))
                return nameReturn;
        }
   }
   return NULL;
}

char*loadPrev(){
    int n;
    sscanf(currentFile,"quick_%d.r2",&n);
    n--;
    if(n<0||n>=1024)
        n=1023;
    for(;n>0;n--){
        FILE*f;
        sprintf(nameReturn,"saves/quick_%d.r2",n);
        f=fopen(nameReturn,"r");
        if(f!=NULL){
            fclose(f);
            sprintf(nameReturn,"quick_%d.r2",n);
            if(!load_rabbit(nameReturn))
                return nameReturn;
        }
   }
   return NULL;
}


#ifndef SENDRECIVEMOD
#define SENDRECIVEMOD





#ifdef IPSEND
    #define printf netprintf
    #define fprintf netfprintf
    #include"mynet.cpp"
#endif


#include"editpannels.cpp"
#include<stdio.h>
#include<string.h>
#include"soundutil.cpp"
#include"koefs.cpp"
#include"interfer.cpp"
int autoPifDeep=0;
extern int soundControllFlag;
int syntaxControll(char*p);
extern double hearingVolume;
extern double amplifierKoef;
extern double amplifierKoefHighValue;
extern double amplifierKoefLowValue;
extern int faded;
extern int rgbMixerDepth;
extern int rgbMixerDepthAuto;
extern int noiseC;
extern int noiseV;
extern int noiseColor;
extern double pifColorSpeedr;
extern double pifColorSpeedg;
extern double pifColorSpeedb;
extern int pifDeep;
extern int pifNaked;
extern int pifColored;
extern double pifDWind;
extern double pifDScale;
extern double pifDAngle;
extern int pifPosition;
extern int showColorSeq;



double ldrawKoef[DRAWKOEFNUM];//PIF:pifDeep,pifNaked,pifColored,pifDWind,pifDScale,pifDAngle,double colorSpeedr,double colorSpeedg,double colorSpeedb,,pifRepeat,pifParity
double lmaxDrawKoef[DRAWKOEFNUM]={11,1.001,1.001,100,1000,7000,1000000,1000000,1000000,60.01,1.01};
double lminDrawKoef[DRAWKOEFNUM]={2,0,0,-100,-1000,-7000,0.0000001,0.0000001,0.0000001,1,0};


double lcontrollKoef[DRAWKOEFNUM*KOEFNUM];
double lzeros[DRAWKOEFNUM];
double ldkoef[DRAWKOEFNUM];
double ldkoefacc[DRAWKOEFNUM];
double ldkoefaccperiod[DRAWKOEFNUM];
double lkoefascell[DRAWKOEFNUM];
double lkoefascellacc[DRAWKOEFNUM];
double lkoefascellamp[DRAWKOEFNUM];
double ldrawLatKoef[DRAWKOEFNUM];


double lsoundKoefs[KOEFNUM];
double laccspeed[KOEFNUM];
double llayerOpt[LAYEROPTS];

double lamplifierKoefLowValue=-1;
double lamplifierKoefHighValue=-1;
int lshowColorSeq=-1;
double lminColorSeqFreq=-1.;
/*
maxDrawKoef

minDrawKoef

controllKoef

zeros

dkoef

dkoefacc

dkoefaccperiod

koefascell

koefascellacc

koefascellamp
*/
int checkSpace(char a){
    if(a==' '||a==10||a==13)
        return 1;
    return 0;
}

int skeep(char*p){
    int a=0;
    while(*p&&checkSpace(*p)){
        a++;
        p++;
    }
    while(*p&&!checkSpace(*p)){
        a++;
        p++;
    }
    while(*p&&checkSpace(*p)){
        a++;
        p++;
    }
//    if(a>0)
    return a;
  //  return 0;

}

int readInt(char*p,int*r){
    int a=0;
    *r=0;
    while(*p&&checkSpace(*p)){
        a++;
        p++;
    }
    while(*p&&!checkSpace(*p)){
        if(*p>='0'&&*p<='9'){
            *r=*r*10+*p-'0';
        }else
            break;
        a++;
        p++;
    }
    while(*p&&checkSpace(*p)){
        a++;
        p++;
    }
//    if(a>0)
    return a;
  //  return 0;

}



double * getMasByName(char const*name){

    if(!strcmp(name,"drawLatKoef"))
        return drawLatKoef;


    if(!strcmp(name,"drawKoef"))
        return drawKoef;
    if(!strcmp(name,"maxDrawKoef"))
        return maxDrawKoef;

   if(!strcmp(name,"minDrawKoef"))
        return minDrawKoef;
   if(!strcmp(name,"controllKoef"))
        return controllKoef;
   if(!strcmp(name,"zeros"))
        return zeros;
   if(!strcmp(name,"dkoef"))
        return dkoef;
   if(!strcmp(name,"dkoefacc"))
        return dkoefacc;
   if(!strcmp(name,"dkoefaccperiod"))
        return dkoefaccperiod;
   if(!strcmp(name,"koefascell"))
        return koefascell;
   if(!strcmp(name,"koefascellamp"))
        return koefascellamp;
   if(!strcmp(name,"soundKoefs"))
        return soundKoefs;
   if(!strcmp(name,"accspeed"))
        return accspeed;
   if(!strcmp(name,"ascellValue"))
        return ascellValue;
   if(!strcmp(name,"layerOpt"))
        return layerOpt;




    return NULL;
}
double * getLMasByName(char const*name){
    if(!strcmp(name,"drawLatKoef"))
        return ldrawLatKoef;


    if(!strcmp(name,"drawKoef"))
        return ldrawKoef;
    if(!strcmp(name,"maxDrawKoef"))
        return lmaxDrawKoef;

   if(!strcmp(name,"minDrawKoef"))
        return lminDrawKoef;
   if(!strcmp(name,"controllKoef"))
        return lcontrollKoef;
   if(!strcmp(name,"zeros"))
        return lzeros;
   if(!strcmp(name,"dkoef"))
        return ldkoef;
   if(!strcmp(name,"dkoefacc"))
        return ldkoefacc;
   if(!strcmp(name,"dkoefaccperiod"))
        return ldkoefaccperiod;
   if(!strcmp(name,"koefascell"))
        return lkoefascell;
   if(!strcmp(name,"koefascellamp"))
        return lkoefascellamp;
   if(!strcmp(name,"soundKoefs"))
        return lsoundKoefs;
   if(!strcmp(name,"accspeed"))
        return laccspeed;
   if(!strcmp(name,"ascellValue"))
        return lascellValue;
   if(!strcmp(name,"layerOpt"))
        return llayerOpt;
         

    return NULL;
}
int getMasSizeByName(char const*name){
    if(!strcmp(name,"drawLatKoef"))
        return DRAWKOEFNUM;

    if(!strcmp(name,"drawKoef"))
        return DRAWKOEFNUM;
    if(!strcmp(name,"maxDrawKoef"))
        return DRAWKOEFNUM;

   if(!strcmp(name,"minDrawKoef"))
        return DRAWKOEFNUM;
   if(!strcmp(name,"controllKoef"))
        return DRAWKOEFNUM*KOEFNUM;
   if(!strcmp(name,"zeros"))
        return DRAWKOEFNUM;
   if(!strcmp(name,"dkoef"))
        return DRAWKOEFNUM;
   if(!strcmp(name,"dkoefacc"))
        return DRAWKOEFNUM;
   if(!strcmp(name,"dkoefaccperiod"))
        return DRAWKOEFNUM;
   if(!strcmp(name,"koefascell"))
        return DRAWKOEFNUM;
   if(!strcmp(name,"koefascellamp"))
        return DRAWKOEFNUM;
   if(!strcmp(name,"soundKoefs"))
        return KOEFNUM;
   if(!strcmp(name,"accspeed"))
        return KOEFNUM;
   if(!strcmp(name,"ascellValue")){
    return DRAWKOEFNUM;
   }
   if(!strcmp(name,"layerOpt")){
    return LAYEROPTS;
   }
   
   
    return 0;
}



int readMasValue(char const *name,int n,double v){
    double *m;
    double *lm;
    int size;
    m=getMasByName(name);
    lm=getLMasByName(name);
    size=getMasSizeByName(name);
    if(m!=NULL&&lm!=NULL&&n<size){
        m[n]=lm[n]=v;
        return 0;
    }
    return -1;
}

void sendMas(char const *   name,FILE*f,int writeAll){
    double *m;
    double *lm;
    int size,i;
    m=getMasByName(name);
    lm=getLMasByName(name);
    size=getMasSizeByName(name);
    if(m!=NULL&&lm!=NULL){
//        printf("%s exist: %d\n",name,size);
        for(i=0;i<size;i++){
            if(fabs(m[i]-lm[i])>0.00000000001 || writeAll){
                fprintf(f,"SetMas %s %d %f\n",name,i,m[i]);
                lm[i]=m[i];            
            }
        
        }
    
    }

}
void sendMas(char const *   name){
    sendMas(name,stdout,0);
}


void sendAllMass(FILE*f,int writeAll){
    sendMas("drawKoef",f,writeAll);
    sendMas("maxDrawKoef",f,writeAll);
    sendMas("minDrawKoef",f,writeAll);
    sendMas("controllKoef",f,writeAll);
    sendMas("zeros",f,writeAll);
    sendMas("dkoef",f,writeAll);
    sendMas("dkoefacc",f,writeAll);
    sendMas("dkoefaccperiod",f,writeAll);
    sendMas("koefascell",f,writeAll);
    sendMas("koefascellacc",f,writeAll);
    sendMas("koefascellamp",f,writeAll);
    sendMas("soundKoefs",f,writeAll);
    sendMas("accspeed",f,writeAll);
    sendMas("ascellValue",f,writeAll);
    sendMas("drawLatKoef",f,writeAll);

}
void sendAllMass(){
    sendAllMass(stdout,0);

}

void zeroLMas(char const *name){
    double *lm;
    int size,i;
    lm=getLMasByName(name);
    size=getMasSizeByName(name);
    if(lm!=NULL){
        for(i=0;i<size;i++){
            lm[i]=-1e100;            
        }
    }
}




inline void printABCDInt(unsigned int n,char*p){
    unsigned int a;
    char*s;
    s=p;
    a=n;
    if(a<0){
        *s='-';
        s++;
        a=-a;
    }    
    if(a==0){
        *s='a';
        s++;
    }
    while(a>0){
        *s=a%26+'a';
        s++;
        a=a/26;
    }
    *s=' ';
    s++;
    *s=0;
}
inline void printABCDUInt32(Uint32 n,char*p){
    Uint32 a;
    char*s;
    s=p;
    a=n;
    
    if(a==0){
        *s='a';
        s++;
    }
    while(a>0){
        *s=a%26+'a';
        s++;
        a=a/26;
    }
    *s=' ';
    s++;
    *s=0;
}
void sendSpector(int w){
    char tbuf[128];
    int i,k,j;
    double d;
    printf("setSpector %d ",w);
    double*a;
    int koef;
//    if(AFCaccAge<maxAFCaccAge){
        a=AFCacc;
  //      koef=AFCaccAge;
    //}else{
      //  a=sound_a;
        //koef=1;
    //}
    
    for(i=0,j=0;i<w;i++){
        d=0;
        for(k=0;j<(i+1)*Nmax/w;j++,k++){
            if(d<a[j]){
                d=a[j];
            }
            AFCacc[j]=0;
        }
        printABCDInt(d,tbuf);
        printf("%s",tbuf);
    }
    printf("\n");
    AFCaccAge=0;
    //maxAFCaccAge=1000;

}

unsigned int scanABCDInt(char*s){
    unsigned int r=0;
    int sign=1;
    while(*s&&checkSpace(*s))s++;
    if(*s=='-'){
        s++;
        sign=-1;
    }
    while(*s>='a'&&*s<='a'+25){
        r=r*26;
        r+=*s-'a';
        s++;
    }
    return r*sign;
}
Uint32 scanABCDUInt32(char*s){
    Uint32 r=0;
//    int sign=1;
    while(*s&&checkSpace(*s))s++;
    if(*s=='-'){
        s++;
        //sign=-1;
    }
    while(*s>='a'&&*s<='a'+25){
        r=r*26;
        r+=*s-'a';
        s++;
    }
    return r;
}
int reciveSpector(char*s){
    int w;
    char*p;
    int d;
    int len=0;;
    int l,i,j,k;
    p=s;
    
    sscanf(p,"%d",&w);
    len=skeep(p);
    p+=len;
    for(i=0,j=0;i<w;i++){
        d=scanABCDInt(p);
        l=skeep(p);
        p+=l;
        len+=l;
        for(k=0;j<(i+1)*Nmax/w;j++,k++){
            sound_a[j]=d;
        }
        if(*s==0)
            break;
        
    }
    
    

    return len;
}


    int    laddMelodyTorithm=-10;
        
        
    double    lMaxDanceFreq=-10;
    
   int     lsoundControllFlag=-1;
   int       lcolorSeqVar=-1;

int readSoundControllValue(char*name,char*value){


    if(!strcmp(name,"addMelodyTorithm")){
        sscanf(value,"%d",&addMelodyTorithm);
        laddMelodyTorithm=addMelodyTorithm;
        return 0;
    }
    if(!strcmp(name,"MaxDanceFreq")){
        sscanf(value,"%lf",&MaxDanceFreq);
        lMaxDanceFreq=MaxDanceFreq;
        return 0;
    }
    
    if(!strcmp(name,"soundControllFlag")){
        sscanf(value,"%d",&soundControllFlag);
        lsoundControllFlag=soundControllFlag;
        return 0;
    }
    if(!strcmp(name,"colorSeqVar")){
        sscanf(value,"%d",&colorSeqVar);
        colorSeqVar=colorSeqVar;
        return 0;
    }

    if(!strcmp(name,"amplifierKoefHighValue")){
        sscanf(value,"%lf",&amplifierKoefHighValue);
        lamplifierKoefHighValue=amplifierKoefHighValue;
        return 0;
    }
   if(!strcmp(name,"amplifierKoefLowValue")){
        sscanf(value,"%lf",&amplifierKoefLowValue);
        lamplifierKoefLowValue=amplifierKoefLowValue;
        return 0;
    }
   if(!strcmp(name,"showColorSeq")){
        sscanf(value,"%d",&showColorSeq);
        lshowColorSeq=showColorSeq;
        return 0;
    }
   if(!strcmp(name,"minColorSeqFreq")){
        sscanf(value,"%lf",&minColorSeqFreq);
        lminColorSeqFreq=minColorSeqFreq;
        return 0;
    }
 
 


    
    return 1;
}

int readColorSeq(char*p){
    int len,sk,k,t,i;
    sscanf(p,"%d ",&len);
    sk=skeep(p);
    p=p+sk;
    for(i=0;i<len;i++){
        sscanf(p,"%d",&t);
        if(i<SEQLEN){
            colorSeq2Buf[i]=t;
        }
        k=skeep(p);
        sk+=k;
        p+=k;
    }
    return sk;
}

     //writeColorSeq();
     
 
void writeIMas(FILE*f,unsigned int *p,int n){
    char tbuf[128];
    for(int i=0;i<n;i++,p++){
        printABCDInt(*p,tbuf);
        fprintf(f,"%s ",tbuf);
    }

}
void writeUIMas(FILE*f,Uint32 *p,int n){
    char tbuf[128];
    for(int i=0;i<n;i++,p++){
        printABCDUInt32(*p,tbuf);
        fprintf(f,"%s ",tbuf);
    }

}

int readIMas(char*s,unsigned int *p,int n){
    int sk=0;
    int t;
    for(int i=0;i<n;i++,p++){
        *p=scanABCDInt(s);
        t=skeep(s);
        sk+=t;
        s+=t;
    }
    return sk;
}
int readUIMas(char*s,Uint32 *p,int n){
    int sk=0;
    int t;
    for(int i=0;i<n;i++,p++){
        *p=scanABCDUInt32(s);
        t=skeep(s);
        sk+=t;
        s+=t;
    }
    return sk;
}

void writeDMas(FILE*f,double *p,int n){
    for(int i=0;i<n;i++,p++)
        fprintf(f,"%lf ",*p);

}
int readDMas(char*s,double *p,int n){
    int sk=0;
    int t;
    for(int i=0;i<n;i++,p++){
        sscanf(s,"%lf",p);
        t=skeep(s);
        sk+=t;
        s+=t;
    }
    return sk;
}

/*
    unsigned int seqno3[OQS];
    Uint32 oqColorline[OQS][COLORLINELEN];
    Uint32 orOqColorline[COLORLINELEN];
    unsigned int orseqno3;
    double oqColorlineSat[OQS];
    double oqColorlineVal[OQS];
    int mapOq[OQS][OQS];    


*/
    int aa,bb;
   
int readColorSeq3(char*pp){
    int sk=0;
    int t;
    char s[128];
    char*p;
    char *p2;
    p=pp;
    sscanf(p,"%s",s);
    sk=skeep(p);
    p+=sk;
//    fprintf(stderr,"readColorSeq3 (%s)",s);
  //  fprintf(stderr," %s\n",p);
    
    //fflush(stderr);
    p2=p;
    if(!strcmp(s,"seqno3")){
        sscanf(p,"%d ",&aa);
      //  fprintf(stderr,"[seqno3] <%d> ",aa);
        //fprintf(stderr,"%s\n ",p);
        //fflush(stderr);

        t=skeep(p);

        sk+=t;
        p+=t;

//        t=readIMas(p,(int*)cl->seqno3,a);
        sk+=t;
        p+=t;
    }
    
    if(!strcmp(s,"oqColorline")){
        //sscanf(p,"%d ",&a);
//        t=readInt(p,&aa);;
  //      t+=readInt(p+t,&bb);
        aa=scanABCDInt(p);
        t=skeep(p);
        bb=scanABCDInt(p+t);
        t+=skeep(p+t);

    
        //skeep(p);
//        sk+=t;
  //      p+=t;
        //sscanf(p+t,"%d ",&b);
        //char bbb[128];
       // sprintf(bbb,"%d %d",aa,bb);
      
        //fprintf(stderr,"--oqColorline-- %s ",bbb);
          
       // fprintf(stderr,"%s\n ",p);
       // fflush(stderr);

        
        
        sk+=t;
        p+=t;
       // Uint32 cc;
     //   cc=rand()%256+(rand()%256)*256+256*(rand()%256);
   //     for(int i=0;i<bb;i++)
         //   cl->oqColorline[aa][i]=cc;
        t=readUIMas(p,cl->oqColorline[aa],bb);
        sk+=t;
        p+=t;

    }
    if(!strcmp(s,"mapOq")){
//        sscanf(p,"%d",&a);
  //      t=skeep(p);
       // sk+=t;
       // p+=t;
    //    sscanf(p+t,"%d",&b);
        aa=0;bb=0;
        aa=scanABCDInt(p);
        t=skeep(p);
        bb=scanABCDInt(p+t);
        t+=skeep(p+t);
        char bbb[128];
        sprintf(bbb,"%d %d",aa,bb);
      
       // fprintf(stderr,"--mapOq-- %s ",bbb);
       // fprintf(stderr,"%s\n ",p);

       // fflush(stderr);
        
        t+=skeep(p);
        sk+=t;
        p+=t;
        t=readIMas(p,(unsigned int*)cl->mapOq[aa],bb);
        sk+=t;
        p+=t;
    }
    
    if(!strcmp(s,"orOqColorline")){
        sscanf(p,"%d",&aa);
        t=skeep(p);
        sk+=t;
        p+=t;
     //   fprintf(stderr,"[orOqColorline] %d\n",aa);
       // fflush(stderr);
        t=readIMas(p,(unsigned int*)cl->orOqColorline,aa);
        sk+=t;
        p+=t;
    }
    if(!strcmp(s,"orseqno3")){
        sscanf(p,"%d",&(cl->orseqno3));
        t=skeep(p);
        sk+=t;
        p+=t;
        //fprintf(stderr,"[orseqno3] %d\n",cl->orseqno3);
        //fflush(stderr);
    }
    
    if(!strcmp(s,"oqColorlineSat")){
        sscanf(p,"%d",&aa);
        t=skeep(p);
        sk+=t;
        p+=t;
        //fprintf(stderr,"[oqColorlineSat] %d\n",aa);
        //fflush(stderr);
        //t=readDMas(p,cl->oqColorlineSat,a);
        sk+=t;
        p+=t;
    }
    if(!strcmp(s,"oqColorlineVal")){
        sscanf(p,"%d",&aa);
        t=skeep(p);
        sk+=t;
        p+=t;
       // fprintf(stderr,"[oqColorlineVal] %d\n",aa);
       // fflush(stderr);
        //t=readDMas(p,cl->oqColorlineVal,a);
        sk+=t;
        p+=t;
    }
    if(!strcmp(s,"maxoqs")){
        sscanf(p,"%d",&(maxoqs));
        t=skeep(p);
        sk+=t;
        p+=t;
        //fprintf(stderr,"[orseqno3] %d\n",maxoqs);
        //fflush(stderr);
    }
    
//    fprintf(f,"setColorSeq3 maxoqs %d\n",);
    return sk;
}
int wcs3i=0;
void writeColorSeq3(FILE*f){
    fprintf(f,"\n");
     fprintf(f,"setColorSeq3 seqno3 %d ",OQS);
    writeIMas(f,(unsigned int*)cl->seqno3,OQS);    
    fprintf(f,"\n");
    
   // for(int i=0;i<OQS;i++)
    {
        if(wcs3i<0||wcs3i>=maxoqs)
            wcs3i=0;
        char b1[128];
        char b2[128];
     //   wcs3i=i;
        printABCDInt(wcs3i,b1);
        printABCDInt(COLORLINELEN,b2);        
//        i,COLORLINELEN
        //fprintf(f,"setColorSeq3 oqColorline %s %s ",b1,b2);
        //writeUIMas(f,cl->oqColorline[wcs3i],COLORLINELEN);    
        //fprintf(f,"\n");
//        printABCDInt(i,b1);
        printABCDInt(OQS,b2);        

        
        fprintf(f,"setColorSeq3 mapOq %s %s ",b1,b2);
        writeIMas(f,(unsigned int*)cl->mapOq[wcs3i],OQS);    
        fprintf(f,"\n");
        wcs3i++;
    }
    fprintf(f,"setColorSeq3 orOqColorline %d ",COLORLINELEN);
    writeUIMas(f,cl->orOqColorline,COLORLINELEN);    
    fprintf(f,"\n");

    fprintf(f,"setColorSeq3 orseqno3 %d\n",cl->orseqno3);
    fprintf(f,"setColorSeq3 maxoqs %d\n",maxoqs);


    fprintf(f,"setColorSeq3 oqColorlineSat %d ",OQS);
    writeDMas(f,cl->oqColorlineSat,OQS);    
    fprintf(f,"\n");

    fprintf(f,"setColorSeq3 oqColorlineVal %d ",OQS);
    writeDMas(f,cl->oqColorlineVal,OQS);    
    fprintf(f,"\n");

    
}
void writeColorSeq3(){
    writeColorSeq3(stdout);
}







void writeColorSeq(FILE*f){
    fprintf(f,"setColorSeq %d ",SEQLEN);
    for(int i=0;i<SEQLEN;i++){
        fprintf(f,"%d ",colorSeq2Buf[i]);
    }
    fprintf(f,"\n");
}
void writeColorSeq(){
    writeColorSeq(stdout);
}

void writeVolume(FILE*f,int writeAll){
    if(!dEq(lamplifierKoefLowValue,amplifierKoefLowValue) || writeAll){
        fprintf(f,"set amplifierKoefLowValue %f\n",amplifierKoefLowValue);
        lamplifierKoefLowValue=amplifierKoefLowValue;
    
    }
    if(!dEq(lamplifierKoefHighValue,amplifierKoefHighValue) || writeAll){
        fprintf(f,"set amplifierKoefHighValue %f\n",amplifierKoefHighValue);
        lamplifierKoefHighValue=amplifierKoefHighValue;
    }
    


}
void writeVolume(){
    writeVolume(stdout,0);
}


int writeSoundControllValue(FILE*f,int writeAll){

    if(!dEq(lminColorSeqFreq,minColorSeqFreq) || writeAll){
        fprintf(f,"set minColorSeqFreq %f\n",minColorSeqFreq);
        lminColorSeqFreq=minColorSeqFreq;
    
    }
    
    
    
    if(lshowColorSeq!=showColorSeq || writeAll){
        fprintf(f,"set showColorSeq %d\n",showColorSeq);
        lshowColorSeq=showColorSeq;
    }


    
    if(laddMelodyTorithm!=addMelodyTorithm || writeAll){
        fprintf(f,"set addMelodyTorithm %d\n",addMelodyTorithm);
        laddMelodyTorithm=addMelodyTorithm;
    
    }
    if(!dEq(lMaxDanceFreq,MaxDanceFreq) || writeAll){
        fprintf(f,"set MaxDanceFreq %f\n",MaxDanceFreq);
        lMaxDanceFreq=MaxDanceFreq;
    
    }
    if(lsoundControllFlag!=soundControllFlag || writeAll){
        fprintf(f,"set soundControllFlag %d\n",soundControllFlag);
        lsoundControllFlag=soundControllFlag;
    }
    if(lcolorSeqVar!=colorSeqVar || writeAll){
        fprintf(f,"set colorSeqVar %d\n",colorSeqVar);
        lcolorSeqVar=colorSeqVar;
    }


}

int writeSoundControllValue(){
    return writeSoundControllValue(stdout,0);
}
int writeSoundControllValue(int writeAll){
    return writeSoundControllValue(stdout,writeAll);
}

int    lnoiseColor=-100;
int    lnoiseV=-100;
int    lnoiseC=-100;
int    lrgbMixerDepth=-100;
int    lfaded=-100;
int lorblurd=-100;
double lpifColorSpeedb=-100.;
double lpifColorSpeedg=-100.;
double lpifColorSpeedr=-100.;
int lautoPifDeep=-10;
void sendFilters(FILE*f,int writeAll){
    
    if(autoPifDeep!=lautoPifDeep || writeAll){
        fprintf(f,"set autoPifDeep %d\n",autoPifDeep);
    
        lautoPifDeep   = autoPifDeep ;
    }
    
    
    if(faded!=lfaded || writeAll){
        fprintf(f,"set faded %d\n",faded);
    
        lfaded   = faded ;
    }
    if(orblurd!=lorblurd || writeAll){
        fprintf(f,"set orblurd %d\n",orblurd);
    
        lorblurd   = orblurd ;
    }
    if(rgbMixerDepth!=lrgbMixerDepth || writeAll){
        fprintf(f,"set rgbMixerDepth %d\n",rgbMixerDepth);
         lrgbMixerDepth  =rgbMixerDepth  ;
    }
    if(noiseC!=lnoiseC || writeAll){
        fprintf(f,"set noiseC %d\n",noiseC);
         lnoiseC  = noiseC ;
    }
    if(noiseV!=lnoiseV || writeAll){
        fprintf(f,"set noiseV %d\n",noiseV);
         lnoiseV  =  noiseV;
    }
    if(noiseColor!=lnoiseColor || writeAll){
        fprintf(f,"set noiseColor %d\n",noiseColor);
         lnoiseColor  = noiseColor ;
    }

   if(!dEq(pifColorSpeedr,lpifColorSpeedr) || writeAll){
        fprintf(f,"set pifColorSpeedr %lf\n",pifColorSpeedr);
         lpifColorSpeedr  = pifColorSpeedr ;
    }
    if(!dEq(pifColorSpeedg,lpifColorSpeedg) || writeAll){
        fprintf(f,"set pifColorSpeedg %lf\n",pifColorSpeedg);
        lpifColorSpeedg   = pifColorSpeedg ;
    }
    if(!dEq(pifColorSpeedb,lpifColorSpeedb) || writeAll){
        fprintf(f,"set pifColorSpeedb %lf\n",pifColorSpeedb);
        lpifColorSpeedb   =pifColorSpeedb  ;
    }

    sendMas("layerOpt",f,writeAll);
    
    
    
    
 

}
void sendFilters(){
     sendFilters(stdout,0);

}




void zeroLValues(){
    zeroLMas("drawKoef");
    zeroLMas("maxDrawKoef");
    zeroLMas("minDrawKoef");
    zeroLMas("controllKoef");
    zeroLMas("zeros");
    zeroLMas("dkoef");
    zeroLMas("dkoefacc");
    zeroLMas("dkoefaccperiod");
    zeroLMas("koefascell");
    zeroLMas("koefascellacc");
    zeroLMas("koefascellamp");
    zeroLMas("soundKoefs");
    zeroLMas("accspeed");
    zeroLMas("ascellValue");
    zeroLMas("layerOpt");
    zeroLMas("drawLatKoef");

        lminColorSeqFreq=-1e100;
        lshowColorSeq=-10000;
        lamplifierKoefLowValue=-1e100;
        lamplifierKoefHighValue=-1e100;
        laddMelodyTorithm=-10000;
        lMaxDanceFreq=-1e100;
        lsoundControllFlag=-10000;
        lcolorSeqVar=-10000;
        
        lfaded   = -100 ;
        lrgbMixerDepth  =-100  ;
        lnoiseC  = -100 ;
        lnoiseV  =  -100;
        lnoiseColor  = -100 ;
        lpifColorSpeedr  = -1e100 ;
        lpifColorSpeedg   = -1e100 ;
        lpifColorSpeedb   =-1e100  ;
    
}


struct layer*recvLayer(struct layer*l,char *p){
    int w,h,i,j,t;
    sscanf(p,"%d",&w);
    p+=skeep(p);
    sscanf(p,"%d",&h);
    p+=skeep(p);
    l=resizeLayer(l,w,h);
    if(l==NULL)
        return NULL;
    for(i=0;i<h && *p;i++){
        for(j=0;j<w && *p;j++){
            sscanf(p,"%d",&t);
            p+=skeep(p);
            if(t<0)
                t=0;
            if(t>255)
                t=255;
            l->p[j+i*w]=t;      
        }
    
    }
    return l;
}
void sendLayer(struct layer*l,FILE*f){
    int w,h,t,i,j;
    w=l->w;
    h=l->h;
    
    fprintf(f,"%d ",w);
    fprintf(f,"%d ",h);
    
    for(i=0;i<h;i++){
        for(j=0;j<w;j++){
            t=l->p[j+i*w];
            fprintf(f,"%d ",t);      
        }
    }
    fprintf(f,"\n");      
}




#endif
#define MIND 0.00000001
#define LATE 1000
#define SOFT 0
struct sense{
    double min,max,lat,mind;
    double soft;
    double last;

};


void zeroSense(struct sense*s){
    s->mind=MIND;
    s->min=0;
    s->last=0;
    s->max=s->mind;
    s->lat=LATE;
    s->soft=SOFT;
}
void zeroSenses(struct sense*s,int n){
    for(int i=0;i<n;i++){
        zeroSense(s+i);
    }
}
double senseValue(struct sense*s,double v){
       v=v*(1-s->soft)+s->last*(s->soft);
       s->last=v;
       if(s->max<v){
            s->max=v;        
        }
        if(s->min>v){
            s->min=v;        
        }
        s->max=(s->max*s->lat+v)/(s->lat+1);

        s->min=(s->min*s->lat+v)/(s->lat+1);
        if(s->max - s->min<s->mind){
            s->max=s->min+s->mind;
        }
        return  (v-s->min)/(s->max-s->min);
}

#include<stdio.h>
#include<SDL/SDL.h>
#include"hsv.cpp"



#define APPLES 10
#define SNAKES 1000

double G,L,M,SNL,K,C;

struct snake{
    double  x[SNAKES];
    double  y[SNAKES];
    Uint32 color[SNAKES];
    double dx[SNAKES];
    double dy[SNAKES];
    double m[SNAKES];
    double r[SNAKES];
    double applex[APPLES];
    double appley[APPLES];
    double appledx[APPLES];
    double appledy[APPLES];
    double applem[APPLES];
    double appler[APPLES];
};



void zeroSnake(){
    int i,x,y;
    
    struct snake*sn;
    sn=(struct snake*)modeData;
    if(sn==NULL)
        return;
    x=rand()%W;    
    y=rand()%H;    
    for(i=0;i<SNAKES;i++){
        sn->x[i]=x;
        sn->y[i]=y;
        sn->color[i]=    (!(rand()%3))?255:
        
        
                     (!(rand()%2)  ?  (255<<8) : (255<<16));
        sn->dx[i]=0;//((rand()%200)/100.0 - 1.0);
        sn->dy[i]=0;//((rand()%200)/100.0 - 1.0);
        sn->m[i]=0.2;
        sn->r[i]=15;
    } 
    sn->m[0]=(10);
    sn->dx[0]=((rand()%200)/100.0 - 1.0);
    sn->dy[0]=((rand()%200)/100.0 - 1.0);
    for(i=0;i<APPLES;i++){
        sn->applex[i]=rand()%W;
        sn->appley[i]=rand()%H;
        sn->appledx[i]=((rand()%200)/100.0 - 1.0)/10;
        sn->appledy[i]=((rand()%200)/100.0 - 1.0)/10;
        sn->applem[i]=(rand()%5+5); //* ( 2*(rand()%2) -1);
        sn->appler[i]=sn->applem[i]*sn->applem[i];

    }
}

void drawSnake(SDL_Surface* screen){
    int i,x,y;    
    struct snake*sn;
    sn=(struct snake*)modeData;
    if(sn==NULL)
        return;
        
        

    
    
    
    for(i=0;i<APPLES;i++){
        int cc;
        cc=sn->appler[i]*sn->appler[i];
        for(x=-102;x<=102;x++)
            for(y=-102;y<=102;y++){
                int c;
                c=x*x+y*y;
                if(c<cc){
                    if(sn->applex[i]+x>=0 && sn->applex[i]+x<W
                    &&
                       sn->appley[i]+y>=0 && sn->appley[i]+y<H
                    ){
                        addpixel(screen,sn->applex[i]+x,sn->appley[i]+y,(cc-c)*255/cc,255);
                    
                    }
                
                                
                
                }   
            
            }
    
    }
    
    for(i=1;i<SNAKES;i++){
        drawLine(screen,sn->x[i],sn->y[i],sn->x[i-1],sn->y[i-1],sn->color[i]);
        
    
    }
    drawSplashes (screen);

  	
}
int moves=0;
void moveSnake(){
    int i,j;    
    double rr,f,dx,dy,a,a1,sp1,a2,sp2;
    struct snake*sn;
    Uint32*p;
    struct rgb myrgb;
    sn=(struct snake*)modeData;
    if(sn==NULL)
        return;
    moves++;    
    myrgb=hsv2rgb(((int)((sin(moves/450.0)+1.0)*2.0))*359,(sin(moves/250.0)+1.0)/2.0,(sin(moves/100.0)+2.0)/3.0);
    p=(Uint32*)&myrgb;
    sn->color[0]=*p;    
    for(i=0;i<APPLES;i++){
        for(j=0;j<i;j++){
            
                dx=sn->applex[i] - sn->applex[j];
                dy=sn->appley[i] - sn->appley[j];
                rr=dx*dx+dy*dy;
                if(rr>=0.000001){
                    if(rr<(sn->appler[i]+sn->appler[j])*(sn->appler[i]+sn->appler[j])){
                        
                        f=G*sn->applem[i]*sn->applem[j]/rr;
                        a=atan2(dy,dx);
                        sn->appledx[i]+=cos(a)*f/sn->applem[i];
                        sn->appledy[i]+=sin(a)*f/sn->applem[i];
                        
                        sn->appledx[j]-=cos(a)*f/sn->applem[j];
                        sn->appledy[j]-=sin(a)*f/sn->applem[j];
                        
                
                    }else{
                    
                        f=G*sn->applem[i]*sn->applem[j]/rr;
                        a=atan2(dy,dx);
                        sn->appledx[i]-=cos(a)*f/sn->applem[i];
                        sn->appledy[i]-=sin(a)*f/sn->applem[i];
                        
                        sn->appledx[j]+=cos(a)*f/sn->applem[j];
                        sn->appledy[j]+=sin(a)*f/sn->applem[j];
                        
                        
                    }
                }
            
                
        }    
        sn->appledx[i]*=1-L;
        sn->appledy[i]*=1-L; 
        sn->appledy[i]+=G*M;
        
        
        
   }
   for(i=SNAKES-1;i>0;i--){
    sn->dx[i]=sn->x[i-1]-sn->x[i];
    sn->dy[i]=sn->y[i-1]-sn->y[i];
    sn->color[i]=sn->color[i-1]; 
   
   }
   if(!(rand()%100))
       for(i=1;i<SNAKES-1;i++){
         sn->y[i]=(sn->y[i] + sn->y[i-1] +sn->y[i+1])/3.0;
         sn->x[i]=(sn->x[i] + sn->x[i-1] +sn->x[i+1])/3.0;
     
   

        }
   
   for(i=0;i<SNAKES;i++){
        
        /*dx=sn->x[i]-sn->x[i+1];
        dy=sn->y[i]-sn->y[i+1];
        rr=sqrt(dx*dx+dy*dy));
        if(1){
            f=K*(rr-SNL);
            a=atan2(dy,dx);
          //  printf("%d\n",(int)(f*100));
            sn->dx[i]+=f*cos(a)/sn->m[i];
            sn->dy[i]+=f*sin(a)/sn->m[i];
            sn->dx[i+1]-=f*cos(a)/sn->m[i+1];
            sn->dy[i+1]-=f*sin(a)/sn->m[i+1];
                
        }*/
        
        
        for(j=0;j<APPLES;j++){
                dx=sn->x[i] - sn->applex[j];
                dy=sn->y[i] - sn->appley[j];
                rr=dx*dx+dy*dy;
                if(rr>=0.000001){
                    if(rr<(sn->r[i]+sn->appler[j])*(sn->r[i]+sn->appler[j])){
                        
                        f=G*sn->m[i]*sn->applem[j]/rr;
                        a=atan2(dy,dx);
                        sn->dx[i]+=cos(a)*f/sn->m[i];
                        sn->dy[i]+=sin(a)*f/sn->m[i];
                        
                        sn->appledx[j]-=cos(a)*f/sn->applem[j];
                        sn->appledy[j]-=sin(a)*f/sn->applem[j];
                        
                
                    }else{
                    
                        f=G*sn->m[i]*sn->applem[j]/rr;
                        a=atan2(dy,dx);
                        sn->dx[i]-=cos(a)*f/sn->m[i];
                        sn->dy[i]-=sin(a)*f/sn->m[i];
                        
                        sn->appledx[j]+=cos(a)*f/sn->applem[j];
                        sn->appledy[j]+=sin(a)*f/sn->applem[j];
                        
                        
                    }
                }   
        
        }
  
        sn->dx[i]*=1-L;
        sn->dy[i]*=1-L; 
        sn->dy[i]+=G*M;
        if(sn->dx[i]>C){
            sn->dx[i]=C;
        }
        if(sn->dy[i]>C){
            sn->dy[i]=C;
        }
        if(sn->dx[i]<-C){
            sn->dx[i]=-C;
        }
        if(sn->dy[i]<-C){
            sn->dy[i]=-C;
        }  
   }
   
    for(i=0;i<SNAKES;i++){
         sn->x[i]+=sn->dx[i];
         sn->y[i]+=sn->dy[i];
         if(sn->x[i]<sn->r[i]){
            sn->dx[i]=fabs(sn->dx[i]);
    
         }
         if(sn->y[i]<sn->r[i]){
            sn->dy[i]=fabs(sn->dy[i]);
    
         }
         if(sn->x[i]>W-sn->r[i]){
            sn->dx[i]=-fabs(sn->dx[i]);
    
         }
         if(sn->y[i]>H-sn->r[i]){
             sn->dy[i]=-fabs(sn->dy[i]);
    
         }  
    
    } 
    
    
    
    
    
    
    for(i=0;i<APPLES;i++){
        
        sn->applex[i]+=sn->appledx[i];
        sn->appley[i]+=sn->appledy[i];
        if(sn->applex[i]<sn->appler[i]){
            sn->appledx[i]=fabs(sn->appledx[i]);
        
        }
        if(sn->appley[i]<sn->appler[i]){
            sn->appledy[i]=fabs(sn->appledy[i]);
    
        }
        if(sn->applex[i]>W-sn->appler[i]){
            sn->appledx[i]=-fabs(sn->appledx[i]);
    
        }
        if(sn->appley[i]>H-sn->appler[i]){
            sn->appledy[i]=-fabs(sn->appledy[i]);
    
        }
        if(sn->appledx[i]>C){
            sn->appledx[i]=C;
        }
        if(sn->appledy[i]>C){
            sn->appledy[i]=C;
        }
        if(sn->appledx[i]<-C){
            sn->appledx[i]=-C;
        }
        if(sn->appledy[i]<-C){
            sn->appledy[i]=-C;
        } 

    }
}

int checkLokalSnake(){
   int i;
   double r;
   double xx,yy,dx,dy;
    struct snake*sn;
    sn=(struct snake*)modeData;
    if(sn==NULL)
        return 0;
   
   r=0;
   xx=0;
   yy=0;
   dx=0;
   dy=0;
   for(i=0;i<SNAKES;i++){
        xx+=sn->x[i];
        yy+=sn->y[i];
   }
   xx/=SNAKES;
   yy/=SNAKES;
   for(i=0;i<SNAKES;i++){
        dx+=abs(sn->x[i]-xx);
        dy+=abs(sn->y[i]-yy);
   }
   
   dx/=SNAKES;
   dy/=SNAKES;
   if(dx+dy<30){
        return 1;
   } 
    return 0;
}

extern short int keys[256];
#include"soundutil.cpp"

#define SHIFT 50
#define CTRL  37
#define ALT   64
#define BACKSPACE 22
#define KEY_R 27
#define KEY_F 41
#define KEY_T 28
#define KEY_G 42
#define KEY_Y 29
#define KEY_H 43
extern double pifColorSpeedr;
extern double pifColorSpeedg;
extern double pifColorSpeedb;
extern int showColorSeq;




void soundKeyboardControll(){
     if(keys[KEY_R]){
        pifColorSpeedr*=1.03;
        
     }
     if(keys[KEY_F]){
        pifColorSpeedr/=1.03;
        
     }
     if(keys[KEY_T]){
        pifColorSpeedg*=1.03;
        
     }
     if(keys[KEY_G]){
        pifColorSpeedg/=1.03;
        
     }
     if(keys[KEY_Y]){
        pifColorSpeedb*=1.03;
        
     }
     if(keys[KEY_H]){
        pifColorSpeedb/=1.03;
        
     }



    if(keys[66]==2){
        if(!keys[CTRL]){
            colorSeqVar++;
            colorSeqVar=colorSeqVar%4;
            colorSeq2BufReady=0;
        }else{
            showColorSeq=!showColorSeq;
        
        }
    }
    
    if(keys[49]==2){
            addMelodyTorithm++;
            addMelodyTorithm=addMelodyTorithm&1;
    }
    if(keys[20]==2){
        if(keys[CTRL] && keys[SHIFT]){
            minColorSeqFreq=minColorSeqFreq/1.1;
    
        }else
        if(keys[CTRL]){
            MaxDanceFreq=MaxDanceFreq/2;
        }else if(keys[SHIFT]){
             amplifierKoefHighValue=amplifierKoefHighValue*1.1;
        }else if(keys[ALT]){
             amplifierKoefLowValue=amplifierKoefLowValue*1.1;
        }
    }
    if(keys[21]==2){
        if(keys[CTRL] && keys[SHIFT]){
            minColorSeqFreq=minColorSeqFreq*1.1;
    
        }else
        if(keys[CTRL]){
             MaxDanceFreq=MaxDanceFreq*2;
        }else if(keys[SHIFT]){
             amplifierKoefHighValue=amplifierKoefHighValue/1.1;
        }else if(keys[ALT]){
             amplifierKoefLowValue=amplifierKoefLowValue/1.1;
        }

    }
    if(keys[BACKSPACE]==2){
        drawAddaptiveVolumeFlag=!drawAddaptiveVolumeFlag;
       // printf("drawAddaptiveVolumeFlag changed %d\n",drawAddaptiveVolumeFlag);
    }
    

}

#ifndef SOUNDUILMOD
#define SOUNDUILMOD
#include"quickspeq.cpp"
#include"drawcurrent.cpp"
Uint32 GetTickCount(void);
//int keys[256];
int ALLFRAQ=0; 
int colorSeqVar=0;
double minColorSeqFreq=1.;
 #include <stdio.h>
 #include <stdlib.h>
   #ifdef RECORDSOUND

 #include "portaudio.h"
#endif
// #include "sdlutils.cpp"
 #include "fft.cpp"
// #include "timeutil.cpp"
 
 
 /* #define SAMPLE_RATE (17932) // Test failure to open with this value. */
 #define SAMPLE_RATE (44100)
 #define FRAMES_PER_BUFFER (1024)
 #define NUM_SECONDS (1)

 /* #define DITHER_FLAG (paDitherOff) */
 #define DITHER_FLAG (0)
 
 #define WRITE_TO_FILE (0)
 
 /* Select sample format. */
 /*#if 1
 #define PA_SAMPLE_TYPE paFloat32
 typedef float SAMPLE;
 #define SAMPLE_SILENCE (0.0f)
 #define PRINTF_S_FORMAT "%.8f"
 #elif 1*/
 #define PA_SAMPLE_TYPE paInt16
 typedef short SAMPLE;
 #define SAMPLE_SILENCE (0)
 #define PRINTF_S_FORMAT "%d"
 /*#elif 0
 #define PA_SAMPLE_TYPE paInt8
 typedef char SAMPLE;
 #define SAMPLE_SILENCE (0)
 #define PRINTF_S_FORMAT "%d"
 #else
 #define PA_SAMPLE_TYPE paUInt8
 typedef unsigned char SAMPLE;
 #define SAMPLE_SILENCE (128)
 #define PRINTF_S_FORMAT "%d"
 #endif
 */
 
 //double notes[12]={523.25, 554.36 ,587.33, 622.25 ,659.26, 698.46, 739.99 ,783.99,830.61 ,880.00, 932.32 ,987.77};
 //int colors[12]={1,1,1,1,256,256,256,256,256*256,256*256,256*256,256*256}; //0 - blue, 1 - red, 2 - green
 
 //int colors[12]={1,1,1,1,256*256,256*256,256*256,256*256,256,256,256,256}; //0 - blue, 1 - red, 2 - green


  ////
//  #define N 8192
 // #define K 13
 // #define N 1024
  #define N 1024
  #define NK 10
  ShortComplex sound_arr[N];
  double sound_a[N];
  double sound_fi[N];
  double sound_freq[N];  

  ShortComplex b2_sound_arr[N];
  ShortComplex b_sound_arr[N];
  double b_sound_a[N];
  double b_sound_fi[N];
  double b_sound_freq[N];  
  int b_k=2;
  int b_cur=0;

  ShortComplex c2_sound_arr[N];
  ShortComplex c_sound_arr[N];
  double c_sound_a[N];
  double c_sound_fi[N];
  double c_sound_freq[N];  

  int c_k=8;
  int c_cur=0;


  ShortComplex d2_sound_arr[N];
  ShortComplex d_sound_arr[N];
  double d_sound_a[N];
  double d_sound_fi[N];
  double d_sound_freq[N];  
  int d_k=32;
  int d_cur=0;


 
 typedef struct{
  int begin; /* Index into sample array. */
  int end;
  int len;
  char lostData;
  SAMPLE *buff1;
  SAMPLE *buff2;

 }  soundData;

struct nota{
    short int ok;
    signed char tone;
    int volume;
    double freq;
  //  double*freqs;
  //  double*amps;
   // int col;
};
struct nota getNota(int k);
 
 /* This routine will be called by the PortAudio engine when audio is needed.
 ** It may be called at interrupt level on some machines so don't do anything
 ** that could mess up the system like calling malloc() or free().
 */
 
 #define TONEEPS 0.001
 int detectTone(double freq){
    double c1=523.25;
    double ton;
    double d=554.36/523.25;
   int i;
    while(freq<c1){
        c1=c1/2.;
    }
    while(freq>c1*2){
        c1=c1*2.;
    }
   freq=freq/c1;
   for(i=0;freq/d-1>TONEEPS;freq=freq/d,i++);
   if(i>11)
    i=11;
   return i;
  
 }
 
 int detectOk(double freq){
    double c1=523.25;
  //  double ton;
//    double d=554.36/523.25;
   int i=1;
    while(freq<c1){
        c1=c1/2.;
        i--;
    }
    while(freq>c1*2){
        c1=c1*2.;
        i++;
    }
 
   return i;
  }
 
 
 /*
 int findColor(int o){
    double ak=1./512;
    double k,kk;
    int n,nn;
    double f;
    f=sound_freq[o];
    n=0;
    nn=0;
    kk=10;
    
    do{
        k=fabs(1.-f/(ak*notes[n]));
        if(k<kk){
            nn=n;
            kk=k;
        }
        n++;
        if(n>=12){
            n=0;
            ak=ak*2.;
        }
            
    
    
    }while(ak<64.);
    
    
 
    return nn;
 
 
 }*/
 int findDeep(double*a,int n,int w,double findEps,int minok,int lastvalue){
    int i,r,k,m,j,rr;
    double sum,max;
    max=0;
    r=lastvalue;
    r=-1;
    rr=0;
    for(i=n;i>0;i--){
        k=0;
        sum=0;
        if(getNota(i).ok>=minok){
            rr=i;
        
        }
        for(j=-w;j<=w;j++){
            if(i+j>=0&&i+j<n && getNota(i+j).ok>=minok && a[i+j]>findEps){
              m=w+1-abs(j);
              sum+=a[i+j]*m*m;
              k++;
            }
            sum/=k;
            if(max<sum){
                r=i;
                max=sum;
            
            }
        
        }
    
    }
    if(r<0){
        r=rr;
    }
     
    return r;
 }
 
 
 #ifdef RECORDSOUND
 
 
 static int recordCallback( const void *inputBuffer, void *outputBuffer,
  unsigned long framesPerBuffer,
  const PaStreamCallbackTimeInfo* timeInfo,
  PaStreamCallbackFlags statusFlags,
  void *userData ){
      soundData *data = (soundData*)userData;
      const SAMPLE *rptr = (const SAMPLE*)inputBuffer;
      SAMPLE *wptr1 = data->buff1 + data->end;
      SAMPLE *wptr2 = data->buff2 + data->end;

      long framesToCalc;
      long i;
      unsigned long framesLeft = data->len - data->end + data->begin-1;
 
      (void) outputBuffer; /* Prevent unused variable warnings. */
      (void) timeInfo;
      (void) statusFlags;
      (void) userData;

      if( framesLeft < framesPerBuffer ){
          framesToCalc = framesLeft;
          data->lostData=1;
          //printf("LOST!!!\n");
          //fflush(stdout);
      }else{
          framesToCalc = framesPerBuffer;
      }
 
      if( inputBuffer == NULL ){
          for( i=0; i<framesToCalc; i++ , data->end++){
              if( data->end == data->len){
                data->end =0;
                wptr1=data->buff1;
                wptr2=data->buff2;
                
              }
              *wptr1++ = SAMPLE_SILENCE;
              *wptr2++ = SAMPLE_SILENCE;
              
          }
      }else{
          for( i=0; i<framesToCalc; i++ ,data->end++){
              if( data->end == data->len){
                data->end =0;
                wptr1=data->buff1;
                wptr2=data->buff2;
              }
              *wptr1++ = *rptr++;
              *wptr2++ = *rptr++;
               
          }
      }

      return paContinue;
}
#endif
int findMedian(double*a,int n,double eps){
    double r,d;
    int i;
    r=0;d=0;
    for(i=0;i<n;i++){
        if(*a>eps){
            d=d+*a/1000.;
            r=r+*a*i/1000.;
        }
        a++; 
    }
    return r/d;
}

double MaxDanceFreq=20;

void  findNMax(double*a,double*freq,int n, int*out,int col,double eps){
    int i,j,r,flag,k;
    double max;    
    for(i=0;i<col;i++){
        max=-1;
        r=0;
        for(j=0;j<n;j++){
            if(max<a[j]&&a[j]>eps&&freq[j]<MaxDanceFreq){
                flag=1;
                for(k=0;k<i;k++){
                    if(out[k]==j){
                        flag=0;
                        break;
                    }
                }
                if(flag){
                    max=a[j];
                    r=j;
                }
                
            
            }
        }
        out[i]=r;    
        //printf("found:%d ",r);
    }
    //printf("\n");

}

/*



void findNMaxC(double*a,int n, int c,int*out,int col,double eps,int *cr1,int*cr2,int dist,double filter){
    int i,j,r,flag,k;
    double max;    
    for(i=0;i<col;i++){
        max=-1;
        r=-1;
        for(j=0;j<n;j++){
            if(sound_freq[j]>filter&&max<a[j]&&a[j]>eps && colors[findColor(j)]==c){
                flag=1;
                for(k=0;k<i;k++){
                    if(abs(out[k]-j)<dist){
                        flag=0;
                        break;
                    }
                }
                for(k=0;k<col;k++){
                    if(abs(cr1[k]-j)<dist||abs(cr2[k]-j)<dist){
                        flag=0;
                        break;
                    }
                }
                if(flag){
                    max=a[j];
                    r=j;
                }
                
            
            }
        }
        if(r>0.)
            out[i]=r;    
    }

}

*/
/*
void findNMaxC(double*a,int n, int c,int*out,int col,double eps,int *cr1,int*cr2,int dist){
    int i,j,r,flag,k;
    double max;    
    for(i=0;i<col;i++){
        max=-1;
        r=0;
        for(j=0;j<n;j++){
            if(max<a[j]&&a[j]>eps && colors[findColor(j)]==c){
                flag=1;
                for(k=0;k<i;k++){
                    if(abs(out[k]-j)<dist){
                        flag=0;
                        break;
                    }
                }
                for(k=0;k<col;k++){
                    if(abs(cr1[k]-j)<dist||abs(cr2[k]-j)<dist){
                        flag=0;
                        break;
                    }
                }
                if(flag){
                    max=a[j];
                    r=j;
                }
                
            
            }
        }
        out[i]=r;    
    }

}*/
 #include <cmath>
 double rx=0;
 double ry=0;
 double rxy=0;
 /*
void drawRithm(SDL_Surface*screen,double*a,double*fi,double*freq,int n){
    double r[2];
    double norm[2];
    int i;
    double t;
    r[0]=0;
    r[1]=0;
    norm[0]=0;
    norm[1]=0;
    t=GetTickCount()/1000.;
    for(i=0;i<n;i++){
        if(freq[i]>0.00001 && !std::isnan( a[i]) && !std::isnan( freq[i]) && !std::isnan( fi[i])){
            r[i%2]+=a[i]*sin(freq[i]*t+fi[i]);
            norm[i%2]+=a[i];
        }
    
    }
    if(fabs(norm[0])>0.0000001)
        r[0]=r[0]*100/norm[0];
    if(fabs(norm[1])>0.0000001)
        r[1]=r[1]*100/norm[1];
    
    //printf("rythm:%f\n",r);
    ry+=r[0];
    rx+=r[1];
    ry=ry*0.4;
    rx=rx*0.4;
    drawSqr(screen,screen->w-110+rx,screen->h/2+ry-10,screen->w-90+rx,screen->h/2+ry+10,WHITE);


}
*/
int addMelodyTorithm=0;
void calcRithm(double*a,double*fi,double*freq,double*la,double*lfi,double*lfreq,int n,int Tc,int T,double t0,double lt0){
    
    double r[3];
    double norm[3];
    char calced[3];
    char lcalced[3];
    double lr[3];
    double lnorm[3];

    int i;
    double t;
    for(i=0;i<3;i++){
        r[i]=0;
        norm[i]=0;
        lr[i]=0;
        lnorm[i]=0;
        calced[i]=0;
        lcalced[i]=0;
    }    
    
    t=GetTickCount()/1000.;
    for(i=0;i<n;i++){
        if(freq[i]>0.00001 && freq[i]<MaxDanceFreq && !std::isnan( a[i]) && !std::isnan( freq[i]) && !std::isnan( fi[i])){
            r[i%2]+=a[i]*sin(freq[i]*(t-t0)+fi[i]);
            norm[i%2]+=a[i];
            calced[i%2]=1;
            r[2]+=a[i]*sin(freq[i]*(t-t0)+fi[i]);
            norm[2]+=a[i];
            calced[2]=1;
        }
        if(lfreq[i]>0.00001 &&lfreq[i]<MaxDanceFreq && !std::isnan( la[i]) && !std::isnan( lfreq[i]) && !std::isnan( lfi[i])){
            lr[i%2]+=la[i]*sin(lfreq[i]*(t-lt0)+lfi[i]);
            lnorm[i%2]+=la[i];
            lcalced[i%2]=1;
            lr[2]+=la[i]*sin(lfreq[i]*(t-lt0)+lfi[i]);
            lnorm[2]+=la[i];
            lcalced[2]=1;
        }
    
    }
    for(i=0;i<3;i++){
        if(calced[i]){
            if(fabs(norm[i])>0.0000001){
                r[i]=r[i]*1000/norm[i];
            }
        }else{
            r[i]=-1000;
        }
        if(lcalced[i]){
            if(fabs(lnorm[i])>0.0000001)
                lr[i]=lr[i]*1000/lnorm[i];
        }else{
            lr[i]=-1000;
        }
    }
    //printf("rythm:%f\n",r);
    ry =(r[0]*Tc+lr[0]*(T-Tc))/T;
    rx =(r[1]*Tc+lr[1]*(T-Tc))/T;
    rxy=(r[2]*Tc+lr[2]*(T-Tc))/T;
    
   // ry=ry*0.4;
   // rx=rx*0.4;
    //drawSqr(screen,screen->w-110+rx,screen->h/2+ry-10,screen->w-90+rx,screen->h/2+ry+10,WHITE);


}


double findRithm(double * a,int n,double eps,double minfreq,double maxfreq){
    double r;
    int i;
    r=0;
    for(i=1;i<n;i++){
        if(sound_freq[i]>minfreq && sound_freq[i]>maxfreq)
            break;
        if(a[i]>eps && sound_freq[i]>minfreq && sound_freq[i]<maxfreq)
            r=r+a[i];
    
    }
    return r;


}


  int cur=0,target;
  int mcur=0,mtarget;
  #define RITHMLEN 256
  #define RITHMK 8
  #define BASSPASS 120.
  #define MELODYPASS 1500.
  #define ALLPASS 44000.
  
  #define RITHMEPS 1.
  //double rithm[RITHMLEN];
  ShortComplex rithm[RITHMLEN];
  double rithma[RITHMLEN];
  double rithmfi[RITHMLEN];
  double rithmfreq[RITHMLEN];
  
  #define KO 1
  int reds[KO];
  int greens[KO];
  int blues[KO];
  #define RO 500        
  int rithms[RO];
  double ra[RO];
  double rfi[RO];
  double rfreq[RO];
  double lra[RO];
  double lrfi[RO];
  double lrfreq[RO];
         
  
  
  
  
  int rithmp=0;
  
 
 #ifdef RECORDSOUND
 
  PaError err = paNoError;
  PaStreamParameters inputParameters;
  PaStream* stream;
  soundData data;
#endif
  int totalFrames;
  int numSamples;
  int numBytes;


int initSound(){
  int i;
  #ifdef RECORDSOUND
  data.len = totalFrames = NUM_SECONDS * SAMPLE_RATE; /* Record for a few seconds. */
  data.begin = 0;
  data.end = 0;
  data.lostData=0;
  numSamples = totalFrames;
  
  numBytes = numSamples * sizeof(SAMPLE);
  data.buff1 = (SAMPLE *) malloc( numBytes ); /* From now on, recordedSamples is initialised. */
  data.buff2 = (SAMPLE *) malloc( numBytes ); /* From now on, recordedSamples is initialised. */
  if( data.buff1 == NULL || data.buff2 == NULL ){
    printf("Could not allocate record array.\n");
    fflush(stdout);
    return -1;
  }

  for( i=0; i<numSamples; i++){ 
    data.buff1[i] = 0;
    data.buff2[i] = 0;

  }
 
  err = Pa_Initialize();
  if( err != paNoError ){
    return -2;
  
  } 
  inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
  if (inputParameters.device == paNoDevice) {
    fprintf(stderr,"Error: No default input device.\n");
    return -3;
  }
  inputParameters.channelCount = 2; 
  inputParameters.sampleFormat = PA_SAMPLE_TYPE;
 // inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency;
   inputParameters.suggestedLatency = 0.0001;
  inputParameters.hostApiSpecificStreamInfo = NULL;
   printf("lat:%f\n",inputParameters.suggestedLatency);
  /* Record some audio. -------------------------------------------- */
  err = Pa_OpenStream(&stream,&inputParameters, NULL, /* &outputParameters, */  SAMPLE_RATE,  FRAMES_PER_BUFFER,  paClipOff, /* we won't output out of range samples so don't bother clipping them */
  recordCallback,
  &data );
  if( err != paNoError ) {
    printf("Error while opening stream\n");
    return -4;
  
  }
 
  err = Pa_StartStream( stream );
  if( err != paNoError ){
      printf("Error while starting stream\n");
      return -5;
  }
//int x,y;
 // x=0;
 
  //int j;
 /* show1=(int*)malloc(screen->w*(sizeof(int)));
  show2=(int*)malloc(screen->w*(sizeof(int)));
  if(show1==NULL || show2==NULL){
    return -10;
  }*/
  
  
  ////
  
    #endif
    return 0;
}


#define NOTES 3
#define MAINNOTES 2
#define MAXMAINOK 3
#define MINMAINOK 0

struct nota notes[NOTES];
int foundNotes=0;
int Nmax= (N + 1) / 2;
int foundMainNotes=0;


struct nota getNota(int k){
    struct nota r;
    r.freq=sound_freq[k];
    r.volume=sound_a[k]*100.;
    if(r.volume>65535)
        r.volume=65535;
    r.ok=detectOk(r.freq);
    r.tone=detectTone(r.freq);
    
    return r;

}



int NoteTableOk=0;
double freqs[12][(N+1)/2];
double amps[12][(N+1)/2];
int facols[12];

void calcNoteTable(){
    if(NoteTableOk)
        return;
    NoteTableOk=1;
    /*for(int i=0;i<NOTES;i++){
        notes[i].freqs=(double*)malloc(sizeof(double)*Nmax);
        notes[i].amps=(double*)malloc(sizeof(double)*Nmax);
        if(notes[i].freqs==NULL || notes[i].amps==NULL){
            printf("MEMo\n");
            fflush(stdout);
        
        }
    }*/
    printf("MEMo ok!\n");
    fflush(stdout);

}



void showCollectedNotes(SDL_Surface*screen,struct nota n){
  int x;
  struct rgb c;
  Uint32 p;
  struct hsv_colour hsv_c; 
  struct rgb_colour rgb_c;
  double v;
  v=(n.volume)*2;
  if(v>65535){
    v=65535;
  }
//  x=n.freq/sound_freq[Nmax-1]*screen->w;
  hsv_c.v=0.99;
  hsv_c.h=n.tone/12.;
  hsv_c.s=v/65536.0;
  hsv2rgb(&hsv_c,&rgb_c);
  c=rgb_colour2rgb(&rgb_c);
  rgb2pixel(c.r,c.g,c.b,&p);

//  drawSqr(screen,x-3,screen->h/2-3,x+3,screen->h/2+3,p);
  
  x=n.tone*30;
  
  bar(screen,x,40,x+29,70,p);
  
  
    


}


void showNota(SDL_Surface*screen,struct nota n){
/*    n.volume;
    n.tone
    n.ak
    n.freq
  */
  int x;
  struct rgb c;
  Uint32 p;
  struct hsv_colour hsv_c; 
  struct rgb_colour rgb_c;
  double v;
  v=(n.volume);
  if(v>65535){
    v=65535;
  }
  x=n.freq/sound_freq[Nmax-1]*screen->w;
  hsv_c.v=0.99;
  hsv_c.h=n.tone/12.;
  hsv_c.s=v/65536.0;
  hsv2rgb(&hsv_c,&rgb_c);
  c=rgb_colour2rgb(&rgb_c);
  rgb2pixel(c.r,c.g,c.b,&p);

  drawSqr(screen,x-3,screen->h/2-3,x+3,screen->h/2+3,p);
  
  x=n.tone*30;
  
  bar(screen,x,0,x+29,30,p);
  
  
    
}
double noteCollector[12];
int noteBusy[12];

void findNotes(int volumeEps){
    int i,j,flag,k;
    struct nota n,m;
    ///Main notes;
    double max;
    calcNoteTable();
    for(i=0;i<12;i++){
        noteCollector[i]=0;
        noteBusy[i]=0;
    }    
    
    foundNotes=0;
    for(i=0;i<MAINNOTES;i++){
        m.volume=0;
        
        for(j=0;j<Nmax;j++){
            n=getNota(j);
            if(n.ok>MAXMAINOK)
                break;
            if(n.ok<MINMAINOK)
                continue;
            if(n.volume>m.volume && n.volume>volumeEps){
                flag=1;
                for(k=0;k<foundNotes;k++){
                    if(notes[k].tone==n.tone){
                        flag=0;
                        break;
                    }
                }
                if(flag){
                    m=n;
                }
                
            
            }
        
        }
        if(m.volume!=0){
          notes[foundNotes++]=m; 
          noteBusy[m.tone]=1;
         // printf("Nota %d: %d, %d:%d\n",foundNotes,m.ok,m.tone,m.volume);
        }   
    }
    foundMainNotes=foundNotes;
    ///Collector
    

    double allcol=0;
    for(j=0;j<Nmax;j++){
         n=getNota(j);
         if(n.ok<=MINMAINOK)
                continue;
        if(n.volume<=volumeEps)
            continue;
        allcol=allcol+sound_a[j];
        noteCollector[n.tone]=noteCollector[n.tone]+sound_a[j];
    }

    for(i=foundMainNotes;i<NOTES;i++){
        max=-1;
        for(j=0;j<12;j++){
            if(max<noteCollector[j] && !noteBusy[j] ){
                max=noteCollector[j];
                k=j;            
            }
        
        }
        if(max>allcol/11 && 100000*max/Nmax > volumeEps ){
           
           notes[foundNotes].tone=k;
           notes[foundNotes].volume=10000*max/Nmax;
           if(notes[foundNotes].volume>65535)
             notes[foundNotes].volume=65535;
           
         //  printf("Collected Nota %d: %d:%d\n",foundNotes,k,notes[foundNotes].volume);
           
           
           
           foundNotes++; 
           
           //printf("foundNotes:%d\n",foundNotes);
           // fflush(stdout);           
           noteBusy[k]=1;
        }
    }
           //printf("foundNotes:%d\n",foundNotes);
            //fflush(stdout);           
    
    
   // return;
    for(i=0;i<12;i++){
        facols[i]=0;
    }
     for(i=0;i<Nmax;i++){
        n=getNota(i);
        if(noteBusy[n.tone]!=-1 && n.volume>volumeEps){
            k=n.tone;
            freqs[k][facols[k]]=n.freq;
            amps[k][facols[k]]=n.volume/65536.;
            facols[k]++;
            //printf("col:%d\n",facols[k]);
            //fflush(stdout);
            
            
            
        }
        
        
        
    }
    
    
    
}



int sound_k=0;
int b_sound_k=0;
int c_sound_k=0;
int d_sound_k=0;
double bassrithm=0.;
double allrithm=0.;
double melodyrithm=0;
int deepWidth=20;

int seqAccR[SEQLEN];
int seqAccG[SEQLEN];
int seqAccB[SEQLEN];

struct rgb fvc[N];
char lfvc[N];
char cfvc=1;

struct rgb freqValue2Color(int k){
       double value,sat,tone;
       Uint32 p;
       struct rgb c;
       struct hsv_colour hsv_c; 
       struct rgb_colour rgb_c;
       if(lfvc[k] == cfvc){
            return fvc[k];
       }
       value=sound_a[k]/7-20;//-50;
       sat=(detectOk(sound_freq[k])+30)*5;
       if(value<0.)
        value=0.;
       if(sat<0.)
        sat=0.;
        if(sat>99.)
            sat=99.;
       if(value>99.)
            value=99.;
       tone=detectTone(sound_freq[k]);
      
       hsv_c.v=value/100.;
       hsv_c.h=tone/12;
       hsv_c.s=sat/100.;
       hsv2rgb(&hsv_c,&rgb_c);
 
       c= rgb_colour2rgb(&rgb_c);
       lfvc[k]=cfvc;
       fvc[k]=c;
       

 
       return c;
}

void calcSoundColorSeqByAFCMixingGamma(double minFreq,double maxFreqm,double mixDist,double cvr,double cvg,double cvb){
    double r,g,b,a,lr,lg,lb,rr,gg,bb;
    struct rgb c;
    int k,i,n,ln,n0;
    ln=-1;
    n0=0;
    cfvc++;
    lr=0;lg=0;lb=0;
    for(k=0;k<Nmax;k++){
       if(sound_freq[k]*mixDist<minFreq)
            continue;
       r=0;g=0;b=0;a=0;
       for(i=k;sound_freq[i]>sound_freq[k]/mixDist && i>0;i--){
           c=freqValue2Color(i);
           r=r+((double)c.r)/sound_freq[i]*(sound_freq[i]-sound_freq[k]/mixDist);
           g=g+((double)c.g)/sound_freq[i]*(sound_freq[i]-sound_freq[k]/mixDist);
           b=b+((double)c.b)/sound_freq[i]*(sound_freq[i]-sound_freq[k]/mixDist);
           a=a+(sound_freq[i]-sound_freq[k]/mixDist)/sound_freq[i];
       
       }
       for(i=k+1;sound_freq[i]<sound_freq[k]*mixDist && i<Nmax;i++){
           c=freqValue2Color(i);
           r=r+((double)c.r)/sound_freq[i] *(sound_freq[k]*mixDist-sound_freq[i]);
           g=g+((double)c.g)/sound_freq[i]*(sound_freq[k]*mixDist-sound_freq[i]);
           b=b+((double)c.b)/sound_freq[i]*(sound_freq[k]*mixDist-sound_freq[i]);
           a=a+(sound_freq[k]*mixDist-sound_freq[i])/sound_freq[i] ;
       
       }
       r=r/a;
       g=g/a;
       b=b/a;
       //n=log(k)/log(Nmax)*SEQLEN;
       //n=k*SEQLEN/Nmax;
       n=log(k)/log(Nmax)*(SEQLEN);
       if(ln==-1){
        n0=n;
        ln=0;
        lr=r;
        lg=g;
        lb=b;
        continue;
       }else{
       // n=n-n0;
       }
       if(n==ln){
          lr=r/2+lr/2;
          lg=g/2+lg/2;
          lb=b/2+lb/2;
          
       
       }else{
           if(n-ln>6*5){
                n=ln+6*5;
            
            }
     
     
           for(i=ln;i<=n && i<SEQLEN;i++){
               rr=((r*(i-ln)   +  lr*(n-i))/(n-ln))*cvr;
               gg=((g*(i-ln)   +  lg*(n-i))/(n-ln))*cvg;
               bb=((b*(i-ln)   +  lb*(n-i))/(n-ln))*cvb;
               if(rr>255)
                rr=255;
               if(gg>255)
               gg=255;
               if(bb>255)
                bb=255;
               c.r=rr;
               c.g=gg;
               c.b=bb;
               
               colorSeq2Buf[i]=*((Uint32*)&c );
            }
           lr=r;
           lg=g;
           lb=b;
           ln=n;
      }     
    }
    
}




void calcSoundColorSeqByAFC(){
    double sat; 
    double value,tone;
    int k,i;
    Uint32 p;
    struct rgb c;
    struct hsv_colour hsv_c; 
    struct rgb_colour rgb_c;
//sound_a,sound_fi,sound_freq
    for(i=0;i<SEQLEN;i++){
        seqAccR[i]=0;
        seqAccG[i]=0;
        seqAccB[i]=0;
        
    
    }
    i=0;
    int li;
    for(k=1;k<Nmax;k++){
        //continue;
       value=sound_a[k]/7-20;//-50;
       sat=(detectOk(sound_freq[k])+30)*5;
       if(value<0.)
        value=0.;
       if(sat<0.)
        sat=0.;
        if(sat>99.)
            sat=99.;
       if(value>99.)
            value=99.;
       tone=detectTone(sound_freq[k]);
      
       hsv_c.v=value/100.;
       hsv_c.h=tone/12;
       hsv_c.s=sat/100.;
       hsv2rgb(&hsv_c,&rgb_c);
       c=rgb_colour2rgb(&rgb_c);
       li=i;
       i=log(k)/log(Nmax)*SEQLEN*5;//k*SEQLEN/Nmax;
       if(i-li>6*5){
            i=li+6*5;
       }
       //i=(k+2)/(Nmax+2)*5*SEQLEN;
       if(li!=i){
        int i0,ii;
        i0=(li+i)/2;
        ii=(i-li) ;
       
        for(;li<i;li++){
            if(sound_freq[k]>minColorSeqFreq){
       
                seqAccR[li%SEQLEN]+=c.r*(ii-2*abs(li-i0))/ii;
                seqAccG[li%SEQLEN]+=c.g*(ii-2*abs(li-i0))/ii;
                seqAccB[li%SEQLEN]+=c.b*(ii-2*abs(li-i0))/ii;
            }
        }
       }
       else{
           if(sound_freq[k]>minColorSeqFreq){
               seqAccR[i%SEQLEN]+=c.r;
               seqAccG[i%SEQLEN]+=c.g;
               seqAccB[i%SEQLEN]+=c.b;
           }       
       
       }


//       colorSeq2Buf[k*SEQLEN/Nmax]=*((Uint32*)&c );
    }
    for(i=0;i<SEQLEN;i++){

       if(seqAccR[i]>255){
            seqAccR[i]=255;       
       }
       if(seqAccG[i]>255){
            seqAccG[i]=255;       
       }
       if(seqAccB[i]>255){
            seqAccB[i]=255;       
       }
       
       c.r=seqAccR[i];
       c.g=seqAccG[i];
       c.b=seqAccB[i];


       colorSeq2Buf[i]=*((Uint32*)&c );
    }
    
}




/*
void calcSoundColorSeqByAFC(){
    double sat; 
    double value,tone;
    int k,i;
    Uint32 p;
    struct rgb c;
    struct hsv_colour hsv_c; 
    struct rgb_colour rgb_c;
//sound_a,sound_fi,sound_freq
    for(i=0;i<SEQLEN;i++){
        seqAccR[i]=0;
        seqAccG[i]=0;
        seqAccB[i]=0;
        
    
    }
    i=0;
    int li;
    for(k=1;k<Nmax;k++){
       if(sound_freq[k]<minColorSeqFreq)
        continue;
       value=sound_a[k]/7-20;//-50;
       sat=(detectOk(sound_freq[k])+30)*5;
       if(value<0.)
        value=0.;
       if(sat<0.)
        sat=0.;
        if(sat>99.)
            sat=99.;
       if(value>99.)
            value=99.;
       tone=detectTone(sound_freq[k]);
      
       hsv_c.v=value/100.;
       hsv_c.h=tone/12;
       hsv_c.s=sat/100.;
       hsv2rgb(&hsv_c,&rgb_c);
       c=rgb_colour2rgb(&rgb_c);
       li=i;
       i=log(k+2)/log(Nmax+2)*5*SEQLEN;//k*SEQLEN/Nmax;
       if(li!=i){
        int i0,ii;
        i0=(li+i)/2;
        ii=(i-li) ;
        for(;li<i;li++){
           seqAccR[li%SEQLEN]+=c.r*(ii-2*abs(li-i0))/ii;
           seqAccG[li%SEQLEN]+=c.g*(ii-2*abs(li-i0))/ii;
           seqAccB[li%SEQLEN]+=c.b*(ii-2*abs(li-i0))/ii;
        }
       }
       else{
           seqAccR[i%SEQLEN]+=c.r;
           seqAccG[i%SEQLEN]+=c.g;
           seqAccB[i%SEQLEN]+=c.b;
       
       
       }


//       colorSeq2Buf[k*SEQLEN/Nmax]=*((Uint32*)&c );
    }
    for(i=0;i<SEQLEN;i++){

       if(seqAccR[i]>255){
            seqAccR[i]=255;       
       }
       if(seqAccG[i]>255){
            seqAccG[i]=255;       
       }
       if(seqAccB[i]>255){
            seqAccB[i]=255;       
       }
       
       c.r=seqAccR[i];
       c.g=seqAccG[i];
       c.b=seqAccB[i];


       colorSeq2Buf[i]=*((Uint32*)&c );
    }
    
}


*/

void calcSoundColorSeqByNotes(){
    double r,g,b,a,s;
    int t,i,k,j;
    double tr[NOTES];
    double tg[NOTES];
    double tb[NOTES];
    struct rgb c;
    Uint32 p;
    struct hsv_colour hsv_c; 
    struct rgb_colour rgb_c;
    
    for(i=0;i<foundNotes;i++){
            t=notes[i].tone;
            hsv_c.v=0.99;
            hsv_c.h=t/12.;
            hsv_c.s=0.99;
            hsv2rgb(&hsv_c,&rgb_c);
            c=rgb_colour2rgb(&rgb_c);
            tr[t]=c.r/255.;          
            tg[t]=c.g/255.;          
            tb[t]=c.b/255.;          
            //printf("%f %f %f\n",tr[t],tg[t],tb[t]);
    }
    
     //printf("foundNotes:%d\n",foundNotes);
            
    
    for(i=0;i<SEQLEN;i++){
            r=0;g=0;b=0;a=0;
           for(j=0;j<foundNotes;j++){
                t=notes[j].tone;
                //printf("facols[t]:%d\n",facols[t]);
                for(k=0;k<facols[t];k++){
                    double f;
                    
                    f=freqs[t][k];
                    f=log(f);
                    if(f<0.001)
                        f=0.001;
                    //f=1;
                    //printf("f[%d]:%f %f",k,f,amps[t][k]);
                    s=(cos(i*f/SEQLEN*2*M_PI)+1)*amps[t][k];
                    r=r+ tr[t]*s;
                    g=g+ tg[t]*s;
                    b=b+ tb[t]*s;
                    a=a+s;
                }                    
            //    printf("\n");
            
            }
            
            

            
            
            c.r=255*r/a;
            c.g=255*g/a;
            c.b=255*b/a;        
            
            colorSeq2Buf[i]=*((Uint32*)&c );
        }

}
double rt0=0;
double lrt0=0;
double nrt0=0;
int ryly1[RITHMLEN];
int ryly2[RITHMLEN];
int ryly[RITHMLEN];
int lrithmp=0;
double b_amplifierKoef;
void calcOqColorline(struct qs& a);
    Uint32 getSoundKoefsColor(int i,double old);

void drawRithm(SDL_Surface* sc,int _x1,int _y1,int _x2,int _y2,ShortComplex* r){
        double max=-1e10;
        double min=1e10;
        int h,h0,x,y,w,i,y1;
        h=_y2-_y1;
        w=_x2-_x1;  
        h0=_y1;  
        if(rithmp<0||rithmp>=RITHMLEN)
            return;
        for(i=0;i<rithmp;i++){
            if(r[i].re>max){
                max=r[i].re;
            }
            if(r[i].re<min){
                min=r[i].re;
            }
        }
        if(fabs(max-min)<0.00001){
              min=max-0.00001;
        }
        int minr,maxr;
        minr=1000;
        maxr=-1000;
        
        int y2;         
        
        lrithmp=rithmp;

        x=_x1+rithmp*w/RITHMLEN;
        y1=h0 + h -  (rx+100)*h/(200) ;
        y= h0 + h - (ry+100)*h/200;
        y2=h0 + h -  (rx+ry+200)*h/(400) ;
        
        for(i=lrithmp;i<=rithmp;i++){
            ryly1[i]=y1;
            ryly2[i]=y2;
            ryly[i]=y;
        }
        if(lrithmp>rithmp)
            lrithmp=0;

    for(i=0;i<rithmp;i++){
            if(minr>ryly[i])
                minr=ryly[i];
            if(maxr<ryly[i])
                maxr=ryly[i];
            if(minr>ryly1[i])
                minr=ryly1[i];
            if(maxr<ryly1[i])
                maxr=ryly1[i];
            if(minr>ryly2[i])
                minr=ryly2[i];
            if(maxr<ryly2[i])
                maxr=ryly2[i];
        }        
        if (maxr==minr)
            maxr=minr+1;
    

        for(i=0;i<rithmp;i++){
                x=_x1+i*w/RITHMLEN;
                y=h0 + h -  (r[i].re-min)*h/(max-min);
                drawLine(sc,x,h+h0,x,y,0x00ff00);
              //  rectangle(sc,x-2,y-2,x+2,y+2,0x0ff00);
               orpixel(sc,x,_y1+h*(ryly[i]-minr)/(maxr-minr),getSoundKoefsColor(7,0));
                orpixel(sc,x,_y1+h*(ryly1[i]-minr)/(maxr-minr),getSoundKoefsColor(6,0));
               orpixel(sc,x,_y1+h*(ryly2[i]-minr)/(maxr-minr),getSoundKoefsColor(5,0));

        }
     
     

        rectangle(sc,x-1,_y1+h*(y-minr)/(maxr-minr)-1,x+1,_y1+h*(y-minr)/(maxr-minr)+1,getSoundKoefsColor(7,0));
        rectangle(sc,x-2,_y1+h*(y1-minr)/(maxr-minr)-2,x+2,_y1+h*(y1-minr)/(maxr-minr)+2,getSoundKoefsColor(6,0));
        rectangle(sc,x-3,_y1+h*(y2-minr)/(maxr-minr)-3,x+3,_y1+h*(y2-minr)/(maxr-minr)+3,getSoundKoefsColor(5,0));
            

        double graphTime;
        graphTime=(double)N*RITHMLEN/SAMPLE_RATE;
        double label;
        if(MaxDanceFreq>0.00001 && MaxDanceFreq <1000.)
            for(label=0;label<graphTime;label=label+2./MaxDanceFreq){
                int x;
                x=_x1 +  label*w/graphTime;
                rectangle(sc,x,h0 + h -h/3,x,h0 + h,0x00ff20);    
                rectangle(sc,x,h0 ,x,h0 + h/3 ,0x00ff20);    
        
            }
        rectangle(sc,_x1,_y1,_x2,_y2,BORDERCOLOR);
        addEValue(_x1,_y1,_x2,_y2,0,MaxDanceFreq/1000+0.0000001,0,100,&MaxDanceFreq);
        
}    
void drawRithm(SDL_Surface* sc,ShortComplex* r){
   drawRithm(sc,sc->w-101,100,sc->w-1,200,r);

//   y1=100

        //y2=200;
//        x1=
     

} 

double AFCacc[(N + 1) / 2];
int AFCaccAge=0;
int maxAFCaccAge=1000;
inline void putS2(int a);
inline void putS1(int a);

struct qs qsAll;
struct qs _qsAll;

void abcdSPEQ(int&b_cur,int&b_k,double&b_sum,ShortComplex*sound_arr,int sound_k,int&b_sound_k,ShortComplex*b_sound_arr,ShortComplex*b2_sound_arr,
double*b_sound_a,double* b_sound_freq,int&b_ready
){
    int i;
    if(b_cur<b_k){
                b_sum=b_sum+sound_arr[sound_k].re;      
                b_cur++;
            }else{
                if(b_sound_k<N){
                    b_sound_arr[b_sound_k].re=b_sum;
                    b2_sound_arr[b_sound_k].re=b_sum;
                    
                    b_sound_arr[b_sound_k].im=0.;
                    b_sound_k++;
                    b_cur=0;
                    b_sum=0;

                }else{
///////////////////////
                   //b_sound_k=0;
//                   fprintf(stderr,"b_fft\n");
  //                 fflush(stderr);

                    double maxValue;
                    maxValue=0;
                   maxValue=0;
        for(i=0;i<N;i++){
            if(maxValue<fabs(b_sound_arr[i].re))
                maxValue=fabs(b_sound_arr[i].re);
        }  
        maxValue=maxValue/b_k;
        hearingVolume=maxValue/65556;
        if(maxValue<700)
            maxValue=700;

        if(hearingVolume< 0.00000001){
            hearingVolume=0.00000001;
        }
        
        if(drawAddaptiveVolumeValue>65535./maxValue){
            drawAddaptiveVolumeValue=65535./maxValue;
        }else{
            drawAddaptiveVolumeValue= (99*drawAddaptiveVolumeValue+ 65535./maxValue)/100;
        }
//        if(amplifierKoef<1.)
  //          amplifierKoef=1;
            
            
        if(amplifierKoef>65535/maxValue)
            amplifierKoef=65535/maxValue;
        else{
            amplifierKoef=(amplifierKoef*9999+65535/maxValue)/10000;
        
            if(amplifierKoef<amplifierKoefHighValue)
                 amplifierKoef=amplifierKoefHighValue;
            
            
            if(amplifierKoef>amplifierKoefLowValue)
                 amplifierKoef=amplifierKoefLowValue;
        
        
        
        }
              for(i=0;i<N;i++){
                b_sound_arr[i].re=b_sound_arr[i].re*amplifierKoef;
                }  
        
      
        
                    #define sound_EPS 1000. 
      
                    fft(b_sound_arr, NK, false);
        
                    Nmax= (N + 1) / 2;
        
                    for(i=0;i<Nmax;i++){
                        b_sound_a[i]=sqrt(b_sound_arr[i].re*b_sound_arr[i].re + b_sound_arr[i].im*b_sound_arr[i].im)*N;
            
                      //  if(b_sound_a[i]<sound_EPS){
                      //      b_sound_a[i]=0.;
                      //  }
            
                      //  if(b_sound_freq[i]>BASSPASS)
                        //    b_sound_a[i]=b_sound_a[i]/10000.*sqrt(i);
                       // else
                             b_sound_a[i]=b_sound_a[i];
           
            
          //  sound_a[i]=sound_a[i]/10000.*sqrt(i);
            
            
            
            
                        b_ready=1;
                        //b_sound_fi[i]=atan2(b_sound_arr[i].im, b_sound_arr[i].re);
                        //b_sound_fi[i]+= M_PI/2.;
                       // if (b_sound_fi[i] > M_PI)
                        //    b_sound_fi[i]-= 2.*M_PI;
                        b_sound_freq[i]= (SAMPLE_RATE *(double) i) / N/b_k;
                        //printf("freqq:%f \n",sound_freq[i]);
                    }
                    int shift;
                    shift=N/b_k;
                    for(int i=0;i<N-shift;i++){
                        b_sound_arr[i].re=0;
                        b_sound_arr[i].im=0;
                    }
                    for(int i=0;i<N-shift;i++){
                            b_sound_arr[i].re=b2_sound_arr[i+shift].re;
                            b2_sound_arr[i].re=b2_sound_arr[i+shift].re;
                            b_sound_arr[i].im=0;
                    }
                    b_sound_k=N-shift;
                    b_cur=0;
                    b_sum=0;

/////////////////////////////////////                    
                }
            }
}



int b_ready=0;
int c_ready=0;
int d_ready=0;
extern double layerOpt[14];

 
 #ifdef RECORDSOUND
 double b_sum=0.;
 double c_sum=0.;
 double d_sum=0.;
int calcSound(double*koefs){
    int i;
    
  //  if( (err = Pa_IsStreamActive( stream ) ) != 1){
  //      return -1;
  //  }
     
   // Pa_Sleep(10);
   // printf("Actual latencity:%f\n",Pa_GetStreamInfo(stream)->inputLatency);
    int soundLoop;
    soundLoop=0;
    while(data.begin!=data.end){
    if(soundLoop>3)
        break;
    soundLoop++;
    /*
    
  ShortComplex b_sound_arr[N];
  double b_sound_a[N];
  double b_sound_fi[N];
  double b_sound_freq[N];  
  int b_k=8;
  int b_cur=0;
    
    */
    
    for(;sound_k<N&&data.begin!=data.end;sound_k++,data.begin++,data.begin%=data.len){
            putS2(data.buff1[data.begin]);
            putS1(data.buff2[data.begin]);

            sound_arr[sound_k].re= (data.buff1[data.begin]+(double)data.buff2[data.begin]);
            sound_arr[sound_k].im= 0.0;
            abcdSPEQ(b_cur,b_k,b_sum,sound_arr,sound_k,b_sound_k,b_sound_arr,b2_sound_arr,b_sound_a,b_sound_freq,b_ready);       
            abcdSPEQ(c_cur,c_k,c_sum,sound_arr,sound_k,c_sound_k,c_sound_arr,c2_sound_arr,c_sound_a,c_sound_freq,c_ready);       
            abcdSPEQ(d_cur,d_k,d_sum,sound_arr,sound_k,d_sound_k,d_sound_arr,d2_sound_arr,d_sound_a,d_sound_freq,d_ready);       
            
    
    }
    //return 0;
   double maxValue;
    if(sound_k==N){
      //   printf("hi!\n");
    //    fflush(stdout);
        maxValue=0;
        for(i=0;i<N;i++){
            if(maxValue<fabs(sound_arr[i].re))
                maxValue=fabs(sound_arr[i].re);
        }  
        hearingVolume=maxValue/65556;
        if(maxValue<700)
            maxValue=700;

        if(hearingVolume< 0.00000001){
            hearingVolume=0.00000001;
        }
        
        if(drawAddaptiveVolumeValue>65535./maxValue){
            drawAddaptiveVolumeValue=65535./maxValue;
        }else{
            drawAddaptiveVolumeValue= (99*drawAddaptiveVolumeValue+ 65535./maxValue)/100;
        }
//        if(amplifierKoef<1.)
  //          amplifierKoef=1;
            
            
        if(amplifierKoef>65535/maxValue)
            amplifierKoef=65535/maxValue;
        else{
            amplifierKoef=(amplifierKoef*9999+65535/maxValue)/10000;
        
            if(amplifierKoef<amplifierKoefHighValue)
                 amplifierKoef=amplifierKoefHighValue;
            
            
            if(amplifierKoef>amplifierKoefLowValue)
                 amplifierKoef=amplifierKoefLowValue;
        
        
        
        }
        //printf("maxValue: %f\n",maxValue);
        for(i=0;i<N;i++){
            sound_arr[i].re=sound_arr[i].re*amplifierKoef;
        }  
        
        
        
        #define sound_EPS 1000. 
      
        fft(sound_arr, NK, false);
        
        Nmax= (N + 1) / 2;
        
        for(i=0;i<Nmax;i++){
            sound_a[i]=sqrt(sound_arr[i].re*sound_arr[i].re + sound_arr[i].im*sound_arr[i].im);///N;
            
            if(sound_a[i]<sound_EPS){
                sound_a[i]=0.;
            }
            
            if(sound_freq[i]>BASSPASS)
                sound_a[i]=sound_a[i]/10000.*sqrt(i);
            else
                 sound_a[i]=sound_a[i]/20000.;
           
            
          //  sound_a[i]=sound_a[i]/10000.*sqrt(i);
           // if(AFCacc[i]<sound_a[i])
          //      AFCacc[i]=sound_a[i];
          //  AFCaccAge++;

            
            
            
            
           // sound_fi[i]=atan2(sound_arr[i].im, sound_arr[i].re);
           // sound_fi[i]+= M_PI/2.;
           // if (sound_fi[i] > M_PI)
           //     sound_fi[i]-= 2.*M_PI;
            sound_freq[i]= (SAMPLE_RATE *(double) i) / N;
            //printf("freqq:%f \n",sound_freq[i]);
        }
//        double*sound_a,double*freqs,int n,int tones,int minoq,int maxoq,struct qs*r
        if(b_ready&&c_ready&&d_ready){
            speq2qs(sound_a,sound_freq,b_sound_a,b_sound_freq,c_sound_a,c_sound_freq,d_sound_a,d_sound_freq,Nmax,12,-3,6,&qsAll,layerOpt[8]);    
        //    QSmorph(&qsAll,&_qsAll,layerOpt[8]);
            truncNotImportant(&qsAll,layerOpt[9]);
            calcQSDis(&qsAll);
        }
        else if(b_ready){
        //    speq2qs(sound_a,sound_freq,b_sound_a,b_sound_freq,Nmax,12,-3,6,&_qsAll);    
          //  QSmorph(&qsAll,&_qsAll,layerOpt[8]);
            //calcQSDis(&qsAll);
        }else{
            //speq2qs(sound_a,sound_freq,Nmax,12,-3,6,&_qsAll);    
            //QSmorph(&qsAll,&_qsAll,layerOpt[8]);
            //calcQSDis(&qsAll);

        
        }
        //printf("\n");
       // SDL_FillRect(screen,NULL, 0x000000);
        
       //showAmp(screen,a,fi,freq,Nmax);

        double findEps=200.;
        double findRithmEps=2.;
        
        target=findDeep(sound_a,Nmax,Nmax/deepWidth,findEps,MAXMAINOK,cur);
        
        
        cur=(target);//+2*cur)/3;
        
       // findNotes(30000);                   
        
        
        
        mtarget=findMedian(sound_a,Nmax,findEps);
        mcur=mtarget;//+19*mcur)/20;
        melodyrithm=findRithm(sound_a,Nmax,findEps,BASSPASS,MELODYPASS);;

        bassrithm=findRithm(sound_a,Nmax,findEps,0,BASSPASS);        
        rithm[rithmp].re=bassrithm+(addMelodyTorithm?melodyrithm:0);
        
        allrithm=findRithm(sound_a,Nmax,findEps,MELODYPASS,ALLPASS);
        
        
        rithm[rithmp++].im=0;
        
        
        if(rithmp==RITHMLEN){
           lrt0=rt0;
           rt0=nrt0;
           nrt0=GetTickCount()/1000.;

            rithmp=0;
            fft(rithm, RITHMK, false);
            int rithmNmax= (RITHMLEN + 1) / 2;
            for(i=0;i<rithmNmax;i++){
                rithma[i]=2*sqrt(rithm[i].re*rithm[i].re + rithm[i].im*rithm[i].im)/N;
                if(rithma[i]<RITHMEPS){
                    rithma[i]=0.;
                }
                //rithma[i]=rithma[i]/10000.*sqrt(i);
                rithmfi[i]=atan2(rithm[i].im, rithm[i].re);
                rithmfi[i]+= M_PI/2.;
                if (rithmfi[i] > M_PI)
                    rithmfi[i]-= 2.*M_PI;
                rithmfreq[i]= (SAMPLE_RATE *(double) i)/N / RITHMLEN;
            //  printf("%f ",freq[i]);
            }
            findNMax(rithma,rithmfreq,rithmNmax,rithms,RO,findRithmEps);
            for(i=0;i<RO;i++){
                lra[i]=ra[i];
                lrfi[i]=rfi[i];
                lrfreq[i]=rfreq[i];
            }

            for(i=0;i<RO;i++){
                ra[i]=rithma[rithms[i]];
                rfi[i]=rithmfi[rithms[i]];
                rfreq[i]=rithmfreq[rithms[i]];
                
            }
            
        
        }

        //drawRithm(screen,ra,rfi,rfreq,RO);

            
 
        
        //SDL_Flip( screen );
        sound_k=0;
        //break;
    }
     
    if(data.lostData){
         printf("Lost data!\n");
        data.lostData=0;
    }
     //fflush(stdout);
  //   SDL_Flip( screen ); 
  //}
    }
    calcRithm(ra,rfi,rfreq,lra,lrfi,lrfreq,RO,rithmp,RITHMLEN,rt0,lrt0);

    
    if(soundControllFlag){
        koefs[0]=bassrithm;
        koefs[1]=melodyrithm;
        koefs[2]=allrithm;
        koefs[3]=mtarget;
        koefs[4]=target;
        koefs[5]=rx;
        koefs[6]=ry;
        koefs[7]=rxy;
        calcOqColorline(qsAll);
     //   if(colorSeqVar==0)
     //       initColorSeq2(pifColorSpeedr,pifColorSpeedg,pifColorSpeedb);
      //  else if(colorSeqVar==1)
       //     calcSoundColorSeqByNotes();
       // else if(colorSeqVar==2){
      //      calcSoundColorSeqByAFC();
        
      //  }else if(colorSeqVar==3){
       //     calcSoundColorSeqByAFCMixingGamma(30,48000,2,2,1.3,2);
       // }
        //printf("calcsoundSeq\n");
    }
    
    return 0;
}

#endif

int closeSound(){
//  if( err < 0 ) {
  //      printf("Error!\n");
    //    return -6;
    
 // }
  #ifdef RECORDSOUND

  err = Pa_CloseStream( stream );
  if( err != paNoError ){
  
        return -7;
  }
  //SDL_Quit(); 
  Pa_Terminate();
  if( data.buff1 ) /* Sure it is NULL or valid. */
      free( data.buff1 );
  if( data.buff2 ) /* Sure it is NULL or valid. */
      free( data.buff2 );
  /*if(show1!=NULL)
    free(show1);
  if(show2!=NULL)
    free(show2);*/
 #endif
  return 0;




}



void showAmp(SDL_Surface* screen,double*a,double*fi,double *freq,int n){
    int x,k,y,c2;
    struct rgb c;
    double tone,volume;
    double value;
//    struct hsv_colour hsv; 
  //  struct rgb_colour rgb;
    Uint32 p;
//    hsv_degrees_percent hsv;
  //  rgb_percent rgb;
    
    struct hsv_colour hsv_c; 
    struct rgb_colour rgb_c;
    
    
    
    //printf("n:%d\n",n);
    
    for(x=0;x<screen->w;x++){
        k=x*n/screen->w;
        y=screen->h-a[k]/3.-1;
        
       volume=a[k]/3.;
       value=a[k]/7.;
        if(volume>99.)
            volume=99.;
       if(value>99.)
            value=99.;
       // volume=1;
       tone=detectTone(freq[k]);
       
      /* hsv.v=value;
       hsv.h=tone*360/12;
       hsv.s=volume;
       rgb=hsv2rgb(hsv);
       c=(rgb_percent2rgb(rgb));
      */
       hsv_c.v=value/100.;
       hsv_c.h=tone/12;
       hsv_c.s=volume/100.;
       hsv2rgb(&hsv_c,&rgb_c);
       c=rgb_colour2rgb(&rgb_c);
       
       rgb2pixel(c.r,c.g,c.b,&p);
       // if(x%10==0)
       //     printf("n, k, freq, tone:%d, %d, %f, %f\n",n,k,freq[k],tone);
       // c=hsv2rgb(tone*360./12.,volume,1);
        
        
        //if(a[k]>10){
        //    putPixel(screen,x,y,GREEN);
        
        
        drawLine(screen,x,y,x,screen->h-1,p);
        //}
    
    }
   // printf("!\n");
 //   fflush(stdout);


}

void drawLabel(SDL_Surface* screen,int x,int w,Uint32 c){
     drawSqr(screen,x-w,screen->h/2-w,x+w,screen->h/2+w,c);
     


}
void drawHLabel(SDL_Surface* screen,int x,int y,int w,Uint32 c){
     drawSqr(screen,screen->w-x-w,screen->h/2+y-w,screen->w-x+w,screen->h/2+y+w,c);
}



void drawSound(SDL_Surface* screen){
      int i,x;
      
       SDL_FillRect(screen,NULL, 0x000000);
       drawCurrent(screen);
       
       showAmp(screen,sound_a,sound_fi,sound_freq,Nmax);    
//       for(x=0;x<Nmax;x++){
  //          if(getNota(x).ok==cur)
    //            break;
      // }
       drawLabel(screen,cur*screen->w/Nmax,screen->w/deepWidth,WHITE);
        
        
        
        for(i=0;i<foundMainNotes;i++){
            showNota(screen,notes[i]);
        }
        for(i=foundMainNotes;i<foundNotes;i++){
            showCollectedNotes(screen,notes[i]);
        }
        
        
        drawLabel(screen,mcur*screen->w/Nmax,6,WHITE);
        drawHLabel(screen,100,bassrithm/10.,6,WHITE);

        drawHLabel(screen,200,melodyrithm/100.,6,WHITE);

        //drawRithm(screen,ra,rfi,rfreq,RO);
        drawSqr(screen,screen->w-110+rx,screen->h/2+ry-10,screen->w-90+rx,screen->h/2+ry+10,WHITE);
        drawRithm(screen,rithm);
}


int lastrgbMixerAuto=-1;



inline int calcColor(int*seq,double t,int n){
    double r;
    double norm;
    
    int i;
    r=0;
    norm=0;
    for(i=0;i<n;i++){        
        if(sound_freq[seq[i]]>0.00001 && !std::isnan( sound_a[seq[i]]) && !std::isnan( sound_freq[seq[i]]) && !std::isnan( sound_fi[seq[i]])){
            r+=sound_a[seq[i]]*sin(t/sound_freq[seq[i]]+sound_fi[seq[i]]);
            //printf("freq:%f\n",sound_freq[seq[i]]);
            norm+=sound_a[seq[i]];
        }
    
    }
    if(fabs(norm)>0.0000001)
        return (r)*256/norm;
    return 0;
}


void calcColorSound(){
    int i;
    double c;
    c=(double)SEQLEN/20.;
    for(i=0;i<SEQLEN;i++){
            struct rgb a;
            int r,g,b;
            *((Uint32*)&a )=colorSeq2Buf[i];
            r=a.r;
            g=a.g;
            b=a.b;
            r+=calcColor(reds,(double)i / c,KO)/2;
            g+=calcColor(greens,(double)i /c,KO)/2;
            b+=calcColor(blues,(double)i /c,KO)/2;        
            if(r<0)
                r=0;
            if(r>255)
                r=255;
            if(g<0)
                g=0;
            if(g>255)
                g=255;
            if(b<0)
                b=0;
            if(b>255)
                b=255;
                
            a.r=r;
            a.g=g;
            a.b=b;
           
            colorSeq2Buf[i]=*((Uint32*)&a );
    }
}



int syncllrithmp=0;
void syncSoundData(){
     if(syncllrithmp<rithmp){
         for(int i=syncllrithmp;i<=rithmp;i++)
              rithm[i].re=bassrithm+(addMelodyTorithm?melodyrithm:0);
        syncllrithmp=rithmp;
     }else if(syncllrithmp>rithmp){
         for(int i=0;i<RITHMLEN;i++)
              rithm[i].re=0;
      
       syncllrithmp=rithmp;
     }        

       Nmax= (N + 1) / 2;
        
        for(int i=0;i<Nmax;i++){
            sound_freq[i]= (SAMPLE_RATE *(double) i) / N;

        }
        cur=target;
        mcur=mtarget;
}
#endif
#include<SDL/SDL.h>
#include<math.h>
#include"graphutil.cpp"
#define MAXSTARN 360
void  inline drawLines(SDL_Surface* sc,int x1,int y1,int x2,int y2,Uint32 pifColor, int repeat);
void  inline drawColoredLinesSeq2(SDL_Surface* sc,int x1,int y1,int x2,int y2, int repeat);
void  inline drawColoredLinesSeq2(SDL_Surface* sc,int x1,int y1,int x2,int y2, int repeat,int curDeep);
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

void drawStarsColorSeq(SDL_Surface*screen,struct star*s,int cx,int cy,int r,int repeat,int curDeep,int nTree,int parity){
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
    for(i=0,x1=s->x1,y1=s->y1,x2=s->x2,y2=s->y2;i<s->n;i++,x1++,y1++,x2++,y2++){
        drawColoredLinesSeq2(screen,axb[*x1+r*2048]+cx,axb[*y1+r*2048]+cy,axb[*x2+r*2048]+cx,axb[*y2+r*2048]+cy,repeat,curDeep);
    }
}

#include<stdio.h>
#define SIMPLES 6
int simple[SIMPLES]={2,3,5,7,11,13};
int findSyms(int l){
    if(l==1 || l==0)
        return 0;
    int r=0;
    for(int i=0;i<SIMPLES;i++){
        if(l%simple[i] == 0){
            r=findSyms(l/simple[i])+1;
            break;
        }
        
    }
    return r;
        
}


int _2(int a){
    int r,i;
    for(i=0,r=1;i<a;i++,r*=2);
    return r;
}

int findFree(int i0,int l,int s){
    //int r;
   // if(l==1||l==0)
     //   return 0;
    
    if(s==0){
        if(l>0)
            return _2(l)-1;
        else 
            return 0;
    }
    int r=0;
    for(int i=i0;i<SIMPLES;i++){
        if(l%simple[i] == 0){
            r+=findFree(i,l/simple[i],s-1);
            
        }
        
    }
    return r;
        
}


unsigned int grayencode(unsigned int g) {
    return g ^ (g >> 1);
}

int generateSym(int i0,char*m,int s,int n,int l){
    char mm[360];
    int a,i;
    if(s==0){
        if(n>=_2(l)){
            return _2(l)-1; 
        }
        a=1;
        for(i=0;i<l;i++,a=a*2){
            if(n&a){
                m[i]=1;
            }else{
                m[i]=0;
            }
        }
        return 0;
    }
    
    int r=0;
    int rr=0;
    for(i=i0;i<SIMPLES;i++){
        if(l%simple[i] == 0){
            int j,k;
            int ll=l/simple[i];
            r=generateSym(i,mm,s-1,n-rr,ll);
            if(r==0){
                for(j=0;j<ll;j++){
                   for(k=0;k<simple[i];k++){
                       m[k*ll+j]=mm[j];    
                   }
            
                }
                return 0;
            }else{
                rr+=r;
                continue;
            }
        }
        
    }
    return rr;
}

void gcs(char*m,double s,double n,int l){
    int ms;
    int ss;
    int mn;
    int nn;
    ms=findSyms(l);
    ss=ms*s;
    mn=findFree(0,l,ss);
 
 
    nn=(mn-1)*n;
    if(nn == 0){
        nn=mn-1;
    }
    if(nn==0 || generateSym(0,m,ss,nn,l)!=0){
        for(int i=0;i<l;i++)
            m[i]=1;
    
    }
    
    //nn=grayencode(nn);   

}
 #include <SDL/SDL.h> 

 #include <sys/time.h> 
extern short int keys[256]; 
 int timeSynk=0;
  Uint32 lastFpsTime=0;
  Uint32 nextFpsTime;
  int currentFps=0;
 void timeKeyboardControll(){
    if(keys[119]==2){
        timeSynk=!timeSynk;
    
    }
 
 
 }
 
 
 Uint32 GetTickCount(void){
    struct timeval t;
    gettimeofday( &t, NULL );
    return ((t.tv_sec) * 1000) + (t.tv_usec / 1000);
}

Uint32 zeroTime=0;
inline int tekeFps(){
    if(/*!timeSynk || */currentFps==0 || currentFps==-1)
        return 30;
    
    return currentFps; 
}
Uint32 myTimer(){
    Uint32 r,t;
    if(!timeSynk)
        return 1000/tekeFps();
    if(zeroTime==0){
        zeroTime=lastFpsTime;//GetTickCount();
    }

    t = lastFpsTime;//GetTickCount();
    r=t-zeroTime;
    zeroTime=t;
    return r;
}


double dcurrentFps=30;

void holdFPS(Uint32 fps){
    Uint32 t;
     
    if(lastFpsTime==0){
        lastFpsTime=GetTickCount();
    }
    
    nextFpsTime=lastFpsTime+1000/fps;
    
    do{
        t=GetTickCount();
    }while( (t-lastFpsTime)*fps<1000 &&   t>lastFpsTime && timeSynk);
    

    
    if(t-lastFpsTime!=0){
        dcurrentFps=(dcurrentFps*39. + 1000/(t-lastFpsTime))/40;
        
        currentFps=dcurrentFps;   
    }else{
        currentFps=-1;
    
    }
    if(0 && nextFpsTime+1000/fps>t){///Если за накопилась ошибка длинной в 1 кадр, отключаем на следующий щаг 
        lastFpsTime=nextFpsTime;
    }else{
        lastFpsTime=t;
    
    }
    

}
#include<SDL/SDL.h>
#include"graphutil.cpp"
void wavesLine(SDL_Surface *screen, int x1,int y1,int x2,int y2,int h,int w,int scrw,int scrh,int color){
    x1 = (scrw) * x1 / w  + screen->w/2 - scrw/2;
    y1 = (scrh) * y1 / h+ screen->h/2 - scrh/2;
    x2 = (scrw) * x2 / w+ screen->w/2 - scrw/2;
    y2 = (scrh) * y2 / h+ screen->h/2 - scrh/2;
    drawLine(screen, x1, y1, x2, y2, color);
}

int drawWaves(SDL_Surface*screen,int scrw,int scrh,int w,int h,int color){

    int x, y, dx, dy;
    int visible;
    int flag1 = 2;
    int x0 = 0;
    int y0 = 0;
    
      
  

    x = 0;
    y = 0;
    dx = -1;
    dy = -1;



     while(1){
         if (flag1 == 1){
             wavesLine(screen, x,y, x + dx, y + dy, h, w,scrw,scrh,color);
         }
         
         if ((x == w) || (x == 0)){
             //invert(screen, x0, y0, x, y, h, w);
             dx = -dx;
             x0 = x;
             y0 = y;
                         
         }
         
         if ((y == h) || (y == 0)){
             //invert(screen, x0, y0, x, y, h, w);
             dy = -dy;
             x0 = x;
             y0 = y;
         }         
         x += dx;
         y += dy;
         flag1=3-flag1;
         if ((x % w == 0) && (y % h == 0)){

             dx = 0;
             dy = 0;
            break;
         }
     }
    }
