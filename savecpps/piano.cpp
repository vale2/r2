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
