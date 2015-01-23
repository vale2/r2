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
