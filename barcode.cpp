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
