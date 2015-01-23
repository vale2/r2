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
