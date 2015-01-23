void *__gxx_personality_v0;
int msgid;

#include "SDL/SDL.h"
//#include "SDL_opengl.h"
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#define WHITE 0xffffff
#define BLUE 0x0000ff
#define GREEN 0x00ff00
#define RED 0xff0000


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

int readKey(){
   SDL_Event event;
   if(SDL_PollEvent(&event)){
        if(event.type == SDL_KEYDOWN) {
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
SDL_Surface *cloneScreen(SDL_Surface *screen){
    const SDL_PixelFormat& fmt = *(screen->format);
  return SDL_CreateRGBSurface(screen->flags,screen->w,screen->h,
                  fmt.BitsPerPixel,
                  fmt.Rmask,fmt.Gmask,fmt.Bmask,fmt.Amask );




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
     screen = SDL_SetVideoMode(W , H, 32, SDL_HWSURFACE |  SDL_NOFRAME | SDL_DOUBLEBUF); 
     if(screen==NULL){
        //printf("Cant create filter surface\n");
        return NULL;
     }
    
     SDL_ShowCursor(0);
    return screen;
}
