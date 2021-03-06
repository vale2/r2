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


void refreshAll(){
    printf("\nwriteAllValues\n");

}
Uint32 startRecTime;

void recVideoButt(){
    if(getOpt("recVideo")>0.5){
        setOpt("recVideo",0);
    }else{
       setOpt("recVideo",1);
       startRecTime=GetTickCount();
    }

}
void  drawRecButton(SDL_Surface* screen,int x1,int y1,int x2,int y2){
    if(getOpt("recVideo")>0.5 && ((GetTickCount()-startRecTime)/1000 )%2 == 0){
        bar(screen,x1,y1,x2,y2,RED);
    }else{
        rectangle(screen,x1,y1,x2,y2,RED);
    }
        addButton(x1,y1,x2,y2,0,recVideoButt);

}

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
    
    
    drawRecButton(screen,screen->w-380,0,screen->w-310,55*hscale);
    addEValue(screen->w-300,0,screen->w-1,55*hscale,0,d,1,124,&amplifierKoefHighValue);
    addRelizeButton(screen->w-300,0,screen->w-1,55*hscale,0,refreshAll);
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

    drawSqr(screen,screen->w-300,35*hscale,screen->w-300+currentFps*300/60,50*hscale,(currentFps>25)?VERYGREEN:((currentFps>15)?VERYYELLOW:RED));
    
    drawSqr(screen,screen->w-300+(25)*300/60,30*hscale,screen->w-300+(25)*300/60,55*hscale,VERYGREEN);

    drawSqr(screen,screen->w-300+(25)*300/60,30*hscale,screen->w-300+(15)*300/60,55*hscale,VERYGREEN);
    






}
#endif
