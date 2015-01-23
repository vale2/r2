
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

