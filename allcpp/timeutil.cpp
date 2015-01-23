#ifndef TIMEMOD
#define TIMEMOD
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

Uint32 fpstimes[100];
void holdFPS(Uint32 fps){
    Uint32 t;
    for(int i=99;i>0;i--)
        fpstimes[i]=fpstimes[i-1];
    fpstimes[0]=GetTickCount();
    currentFps=1./((fpstimes[0]-fpstimes[99])/100000.);
 /*    
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
    
*/
}
#endif
