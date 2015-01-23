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
