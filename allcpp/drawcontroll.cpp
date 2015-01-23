#include<SDL/SDL.h>
#include"graphutil.cpp"
#include"koefs.cpp"
#include"colors.cpp"
#include"piano.cpp"
#include"editpannels.cpp"
#include"soundutil.cpp"
#include"stringid.cpp"

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
void rizeLoadDialog();
void rizeSaveDialog();
void rizePicDialog();
void drawSaveLoadButts(int x1,int y1,int x2,int y2,SDL_Surface*screen){
  // drawPrevPreset(x1,y1,(x1*2+x2)/3,y2,screen);
  // drawNextPreset((x1+x2*2)/3,y1,x2,y2,screen);
  int w,h;
  w=x2-x1;
  h=y2-y1;
   addButton(x1,y1,(x2+x1*2)/3,y2,1,rizeLoadDialog);
   rectangle(screen,x1,y1,(x2+x1*2)/3-1,y2,BLUE);
   circle(screen,(x1+(x2+x1*2)/3)/2,(y1+y2)/2,h/2,BLUE);

   addButton((x2+x1*2)/3,y1,(x1+x2*2)/3,y2,1,rizePicDialog);
   rectangle(screen,(x2+x1*2)/3,y1,(x1+x2*2)/3-1,y2,CYAN);
   
   bar(screen,(x2+x1*2)/3+w/9,y1+h/3,(x1+x2*2)/3-w/9,y2-h/3,CYAN);
      
   addButton((x1+x2*2)/3,y1,x2,y2,1,rizeSaveDialog);
   for(int i=0;i<fabs(y1-y2)/2;i+=5){
            rectangle(screen,(x1+x2*2)/3+i*w/h/3,y1+i,x2-i*w/h/3,y2-i,YELLOW);
   }    
   rectangle(screen,x1-1,y1-1,x2+1,y2+1,BORDERCOLOR);
    
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

struct playList*pls=NULL;
int plsn=0;
int curpls=0;
int curRabbit=-100;
int scrollLoadDialog=-100;// in pixels

void setCurRabbit(){
    curRabbit=butParam%pls[curpls].len;
//    curRabbit=0;
    
}

void setCurPL(){
    curpls=butParam%plsn;
    curRabbit=0;
    
}
int max(int a,int b){
    if(a>b)
        return a;
    return b;
}
int min(int a,int b){
    if(a<b)
        return a;
    return b;
}

void  rectangleSave(int bx1,int by1,int bx2,int by2,SDL_Surface*screen,int wx1,int wy1,int wx2,int wy2,Uint32 c){
    if(bx1>bx2){
        swap(bx1,bx2);
    }
    if(by1>by2){
        swap(by1,by2);
    }
    if(wy1>wy2){
        swap(wy1,wy2);
    }
    if(wx1>wx2){
        swap(wx1,wx2);
    }
    if(wy2<by1 || wx2<bx1 || wy1>by2 || wx1>bx2){
        return;
    }
    rectangle(screen,max(bx1,wx1),max(by1,wy1),min(bx2,wx2),min(by2,wy2),c);
}

void  barSave(int bx1,int by1,int bx2,int by2,SDL_Surface*screen,int wx1,int wy1,int wx2,int wy2,Uint32 c){
    if(bx1>bx2){
        swap(bx1,bx2);
    }
    if(by1>by2){
        swap(by1,by2);
    }
    if(wy1>wy2){
        swap(wy1,wy2);
    }
    if(wx1>wx2){
        swap(wx1,wx2);
    }
    if(wy2<by1 || wx2<bx1 || wy1>by2 || wx1>bx2){
        return;
    }
    bar(screen,max(bx1,wx1),max(by1,wy1),min(bx2,wx2),min(by2,wy2),c);
}



void   addRelizeButtonSave(int bx1,int by1,int bx2,int by2,int wx1,int wy1,int wx2,int wy2,int param,void(*func)()){
    if(bx1>bx2){
        swap(bx1,bx2);
    }
    if(by1>by2){
        swap(by1,by2);
    }
    if(wy1>wy2){
        swap(wy1,wy2);
    }
    if(wx1>wx2){
        swap(wx1,wx2);
    }
    if(wy2<by1 || wx2<bx1 || wy1>by2 || wx1>bx2){
        return;
    }
    addRelizeButton(max(bx1,wx1),max(by1,wy1),min(bx2,wx2),min(by2,wy2),param,func);
}

void drawBitmap(SDL_Surface*screen,char*pix,int pw,int ph,int x1,int y1,int x2,int y2){
    int h,w,x,y;
    w=x2-x1;
    h=y2-y1;
    if(pix==NULL){
        return;
    }
    for(x=0;x<w;x++){
        for(y=0;y<h;y++){
            Uint32 c;
            int xx,yy;
            xx=x*pw/w;
            yy=y*ph/h;            
            c=*((Uint32*)(pix+(xx+yy*pw)*4));
     //       c|=0x00ff00;
            putpixel(screen,x1+x,y1+y,c);
        }    
    }

}


void savePreview(){
    saveCurPreview(ssd[butParam],ssdw[butParam],ssdh[butParam]);
    doneDialog();
}
void drawSaveDialog(SDL_Surface*screen,int x1,int y1,int x2,int y2){
    int h,w,i;
    w=x2-x1;
    h=y2-y1;
    for(i=0;i<16;i++){
        int x,y;
        x=i/4;
        y=i%4;
        drawBitmap(screen,ssd[i],ssdw[i],ssdh[i],x1+x*w/4,y1+y*h/4,x1+(x+1)*w/4-1,y1+(y+1)*h/4-1);
        addButton(x1+x*w/4,y1+y*h/4,x1+(x+1)*w/4-1,y1+(y+1)*h/4-1,i,savePreview);
        
    }



}
void drawBitmapSave(char*pix,int pw,int ph,int bx1,int by1,int bx2,int by2,SDL_Surface*screen,int x1,int y1,int x2,int y2){
    int h,w,x,y;
    w=x2-x1;
    h=y2-y1;
    if(pix==NULL){
        return;
    }
    if(bx1>x2||bx2<x1||by1>y2||by2<y1)
        return;
    for(x=0;x<w;x++){
        for(y=0;y<h;y++){
            Uint32 c;
            int xx,yy;
            xx=x*pw/w;
            yy=y*ph/h;            
            c=*((Uint32*)(pix+(xx+yy*pw)*4));
     //       c|=0x00ff00;
            xx=x1+x;
            yy=y1+y;
            if(xx>=bx1&&xx<bx2&&yy>=by1&&yy<by2)
                putpixel(screen,xx,yy,c);
        }    
    }

}

void addPls(){
    addPlsTimeStamp();
    freePlayLists();
}
void drawLoadDialog(SDL_Surface*screen,int x1,int y1,int x2,int y2){
    int i,w,h,xi,yi,rh,rw,rows;
    rows=5;
    w=x2-x1;
    h=y2-y1;
    rw=w/rows;
    rh=3*rw/4;
    xi=0;yi=0;

    // curRabbit=-100;


    if(pls==NULL){
        pls=loadPlaylists(plsn);    
    }
    for(i=0;i<plsn+1;i++){
        int a,b,c,d;
        a=x1+w*i/(plsn+1);
        b=y1;
        c=x1+w*(i+1)/(plsn+1)-1;
        d=y1+h/5;
        if(i!=plsn){
            if(curpls!=i){
                rectangle(screen,a,b,c,d,BORDERCOLOR);
                addButton(a,b,c,d,i,setCurPL);
            
            }else{
                bar(screen,a,b,c,d,BORDERCOLOR);
            }
        }else{
                rectangle(screen,a,b,c,d,BORDERCOLOR);
                bar(screen,(a*2+c)/3,(b*2+d)/3,(c*2+a)/3,(d*2+b)/3,CYAN);
                
                addButton(a,b,c,d,i,addPls);
        
        
        }
    
    }
    y1=y1+h/5+1;
    if(curpls!=0){
        fprintf(stderr,"curpls:%d l=%d\n",curpls,pls[curpls].len);
    }
    for(i=0;i<pls[curpls].len;i++){
        int a,b,c,d;
        a=x1+xi*rw;
        b=y1+yi*rh-scrollLoadDialog;
        c=x1+(xi+1)*rw-1;
        d=y1+(yi+1)*rh-scrollLoadDialog-1;
        if(pls[curpls].rabbits!=NULL){
            if(curRabbit!=i){
                if(pls[curpls].rabbits[i].pic==NULL)
                    rectangleSave(x1,y1,x2,y2,screen,a,b,c,d,BORDERCOLOR);
                else        
                    drawBitmapSave(pls[curpls].rabbits[i].pic,pls[curpls].rabbits[i].w,pls[curpls].rabbits[i].h,x1,y1,x2,y2,screen,a,b,c,d);
    
                addRelizeButtonSave(x1,y1,x2,y2,a,b,c,d,i,setCurRabbit);
            
            }else{
                barSave(x1,y1,x2,y2,screen,a,b,c,d,BORDERCOLOR);
            }
        }
        xi++;
        if(xi>=rows){
            xi=0;
            yi++;
        }
    }
    if(scrollLoadDialog<0){
        scrollLoadDialog=0;//yi*rh-rh/2;
    
    }

    addEValue(x1,y1,x2,y2,1,0.5,0,yi*rh,&scrollLoadDialog);

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
void drawColorCorrectorPannelStack(SDL_Surface*screen,int x1,int y1,int x2,int y2);


double colorSeqSplash=0.;


void switchColorSeq(){
    if(colorSeqVar<8){
        colorSeqVar=8;
    }else if(colorSeqVar<9){
        colorSeqVar=9;
    }else{
        colorSeqVar=4;
    }
}

void switchLinDises(){
   int calcLin=getOpt("calcLin");

    if(calcLin){
        setOpt("calcLin",0);
    }else{
        setOpt("calcLin",1);
    }
}

void drawLinDisesSwitcher(SDL_Surface*screen,int x1,int y1,int x2,int y2){  
   int calcLin=getOpt("calcLin");

    if(calcLin){
        bar(screen,(x1*2+x2)/3,y1,(x1+x2*2)/3,y2,WHITE);
    }else{
        bar(screen,x1,(y1*2+y2)/3,x2,(y1+y2*2)/3,MAGENTA);
    }
        addButton(x1,y1,x2,y2,0,switchLinDises);
    

}

void drawColorSeqSwitcher(SDL_Surface*screen,int x1,int y1,int x2,int y2){  
    if(colorSeqVar<8){
        bar(screen,(x1*2+x2)/3,y1,(x1+x2*2)/3,y2,VIOLVET);
    }if(colorSeqVar==9){
        bar(screen,(x1*2+x2)/3,y1,(x1+x2*2)/3,y2,BLUE);
    }else{
        bar(screen,x1,(y1*2+y2)/3,x2,(y1+y2*2)/3,CYAN);
    }
        addButton(x1,y1,x2,y2,0,switchColorSeq);
    

}


void draw3Tone(SDL_Surface*screen,int x1,int y1,int x2,int y2,int n,    Uint32 c){
    double dk=pow(2.,1./12.);//554.36/523.25;
    
    int h=y2-y1;
    int w=x2-x1;
    int d1,d2;
    double k1,t1,t2,k2;
    double freq;
    double la,a;
    d1=getOpt("3Interval1",n);
    d2=getOpt("3Interval2",n);

    freq=20;
    k1=1;
    for(;d1>0;d1--){
        k1*=dk;
    }
    k2=1;
    for(;d2>0;d2--){
        k2*=dk;
    }
    
    a=0;
    t1=0;
    t2=0;
    double t=0;
    double lt=0;
//    fprintf(stderr,"n:%d ",n);
  //  fprintf(stderr,"d1:%d ",d1);
    //fprintf(stderr,"d2:%d\n",d2);
    
    for(double i=0;i<w;){
            //la=a;
            a=t-lt;
            i=t;
            drawLine(screen,x1+i-1,y1+a*h,x1+i,y1+a*h,c);
            
            if(t1+1./k1<t2+1./k2){
               t1+=1./k1;
               t=t1;
            }else{
                t2+=1./k2;
                t=t2;
            }
            
         while(t-lt>1){
                lt+=1;
                
         }

         
            
     }
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);
}

void frdraw3Tone(SDL_Surface*screen,int x1,int y1,int x2,int y2,int n,    Uint32 c){
    double dk=554.36/523.25;
    
    int h=y2-y1;
    int w=x2-x1;

    double k1,k2,t;
    double freq;
    double la,a;
    int d1,d2;
    d1=getOpt("3Interval1",n);
    d2=getOpt("3Interval2",n);

    freq=20;
    k1=1;
    for(;d1>0;d1--){
        k1*=dk;
    }
    k2=1;
    for(;d2>0;d2--){
        k2*=dk;
    }


    a=0;
    double stat[500];
    int st,i;
    for(i=0;i<w;i++)
        stat[i]=0;
    for(i=0;i<500;i++){
            t=i;
            t=4*t/w;
            a=(sin(t*freq)+sin(t*freq*k1)+sin(t*freq*k2));
            a=(fabs(a))/3;
            st=a*(w-1);
            if(st<0)
                st=0;
            if(st>=w)
                st=w-1;
            stat[st]+=fabs(sin(t*freq));
    }
    double max;
    max=0;
    for(i=0;i<w;i++){
       if(max<stat[i])
        max=stat[i];
    }

    for(i=0;i<w;i++){
        drawLine(screen,x1+i,y2,x1+i,y2-h*stat[i]/max,c);
    }
    
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);
}


void ldraw3Tone(SDL_Surface*screen,int x1,int y1,int x2,int y2,int n,    Uint32 c){
    double dk=554.36/523.25;
    
    int h=y2-y1;
    int w=x2-x1;
    int d1,d2;
    d1=getOpt("3Interval1",n);
    d2=getOpt("3Interval2",n);
    double k1,t,k2;
    double freq;
    double la,a;
    if(d1<=0||d2<=0)
        return;
    freq=20;
    k1=1;
    for(;d1>0;d1--){
        k1*=dk;
    }
    k2=1;
    for(;d2>0;d2--){
        k2*=dk;
    }
    a=0;
    for(int i=0;i<w;i++){
            t=i;
            t=4*t/w;
            la=a;
            a=sin(t*freq)+sin(t*freq*k1)+sin(t*freq*k2);
            drawLine(screen,x1+i-1,y1+h/2+la*h/4,x1+i,y1+h/2+a*h/4,c);
     }
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);
}


void frdrawInterval(SDL_Surface*screen,int x1,int y1,int x2,int y2,int d,    Uint32 c){
    double dk=554.36/523.25;
    
    int h=y2-y1;
    int w=x2-x1;

    double k,t;
    double freq;
    double la,a;

    freq=20;
    k=1;
    for(;d>0;d--){
        k*=dk;
    }
    a=0;
    double stat[1000];
    int st,i;
    for(i=0;i<w;i++)
        stat[i]=0;
    for(i=0;i<3000;i++){
            t=i;
            t=4*t/w;
            a=(sin(t*freq)+sin(t*freq*k));
            a=(2+a)/4;
            st=a*(w-1);
            if(st<0)
                st=0;
            if(st>=w)
                st=w-1;
            stat[st]=stat[st]+ fabs(sin(t*freq));
    }
    double max;
    max=0;
    for(i=0;i<w;i++){
       if(max<stat[i])
        max=stat[i];
    }

    for(i=0;i<w;i++){
        drawLine(screen,x1+i,y2,x1+i,y2-h*stat[i]/max,c);
    }
    
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);
}



void spDrawInterval(SDL_Surface*screen,int x1,int y1,int x2,int y2,int d,    Uint32 c){
    double dk=pow(2.,1./12.);//554.36/523.25;
    
    int h=y2-y1;
    int w=x2-x1;

    double k,t;
    double freq;
    double la,a;

//    freq=20;
    k=1;
    int ddd=d;
    for(;d>0;d--){
        k*=dk;
    }
    a=0;
    //ph[d]+=M_PI/30000.;
    //t=ph[d];
   // while(t<0)
     //       t+=1;
    double b;
    t=0;
    b=0;//ph[d];
    double po[100];
    int i,j;
    for(i=0;i<100;i++)
        po[i]=0;
    double ad=1;
    for(i=0;i<3000;i++,t+=1/k){
            //la=a;
            while(t>1)
                t-=1;
//            while(b>1)
  //              b-=1;
            a=t;//sin(t);
           // drawLine(screen,x1+b*w,y1+a*h,x1+b*w,y1+a*h,c);
           int cell;
           cell=a*99;
           po[cell]+=ad;
           ad=ad*1.01;
          // for(j=0;j<100;j++)
          //    po[j]=0.999*po[j];
     }
     
    double max=0.0001;
    for(i=0;i<100;i++){
        if(max<po[i])
            max=po[i];
    }
    int col=0;
    for(i=0;i<100;i++){
        if(po[i]>max/2){
            col++;
        
        }
      
      
            drawLine(screen,x1+i*w/100,y2,x1+i*w/100,y2-po[i]/max*h,c);
        //else
          //  drawLine(screen,x1+i*w/100,y2,x1+i*w/100,y2-po[i]/max*h,WHITE);
        
    }
//    fprintf(stderr,"dis#%d:%d\n",ddd,col);
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);
}

double ph[13]={0,0,0,0,0,0,0,0,0,0,0,0,0};
void lindrawInterval(SDL_Surface*screen,int x1,int y1,int x2,int y2,int d,    Uint32 c){
    double dk=pow(2.,1./12.);//554.36/523.25;
    
    int h=y2-y1;
    int w=x2-x1;

    double k,t;
    double freq;
    double la,a;

//    freq=20;
    k=1;
    for(;d>0;d--){
        k*=dk;
    }
    a=0;
    //ph[d]+=M_PI/30000.;
    //t=ph[d];
   // while(t<0)
     //       t+=1;
    double b;
    b=0;//ph[d];
    while(t>1){
        t-=1;
    }
    t=0.3;
    for(int i=0;i<w;t+=1/k){
            //la=a;
            while(t>1){
                t-=1;
                i++;
                b+=1/(double)w;
            }
            while(b>1)
                b-=1;
            a=t;//sin(t);
            drawLine(screen,x1+b*w,y1+a*h,x1+b*w,y1+a*h,c);
            
     }
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);
}
int drawIntMetod=0;
void switchDrawIntMetod(){
    drawIntMetod=drawIntMetod+1;
    drawIntMetod=drawIntMetod%4;
}

void ldrawInterval(SDL_Surface*screen,int x1,int y1,int x2,int y2,int d,    Uint32 c){
    double dk=554.36/523.25;
    
    int h=y2-y1;
    int w=x2-x1;

    double k,t;
    double freq;
    double la,a;

    freq=20;
    k=1;
    for(;d>0;d--){
        k*=dk;
    }
    a=0;
    for(int i=0;i<w;i++){
            t=i;
            t=4*t/w;
            la=a;
     //       if(fabs(sin(t*freq))>0.000)
            a=(sin(t*freq)+sin(t*freq*k));
            drawLine(screen,x1+i-1,y1+h/2+la*h/4,x1+i,y1+h/2+a*h/4,c);
     }
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);
}

void drawInterval(SDL_Surface*screen,int x1,int y1,int x2,int y2,int d,    Uint32 c){
    
    if(drawIntMetod==0){
        spDrawInterval(screen,x1,y1,x2,y2,d,c);
    }else if(drawIntMetod==1){
        lindrawInterval(screen,x1,y1,x2,y2,d,c);
    
    }else if(drawIntMetod==2){
        frdrawInterval(screen,x1,y1,x2,y2,d,c);
    }else if(drawIntMetod==3){
        ldrawInterval(screen,x1,y1,x2,y2,d,c);
    }
}

Uint32 iColors[13]={WHITE,CYAN,CYAN,GREEN,BLUE,RED,RED,RED,BLUE,GREEN,CYAN,CYAN,MAGENTA};

void seq9ColorItemSetup(){
    int n=dialogParam;
    int ns[4];
    const char *s[4]={"iRed","iGreen","iBlue","iValue"};    
    Uint32 colors[4]={RED,GREEN,BLUE,WHITE};
    struct rgb c;
    c.b=255*getOpt("iRed",n);
    c.g=255*getOpt("iGreen",n);
    c.r=255*getOpt("iBlue",n);
    Uint32 cc;
    cc=*((Uint32*)&c);
    drawInterval(dSc,(dX2+dX1)/2,dY1,dX2,(dY2+dY1)/2,n,cc);

    ns[0]=ns[1]=ns[2]=ns[3]=n;

    drawOptStack(dSc,dX1,dY1,(dX2+dX1)/2,dY2,s,colors,ns,4);
    bar(dSc,(dX2+dX1)/2,dY1,dX2,(dY2+dY1)/2,0);
    

    bar(dSc,(dX2+dX1)/2,(dY2+dY1)/2,dX2,dY2,cc);
    
            
    
}

void drawSpiral(SDL_Surface*screen,int x1,int y1,int x2,int y2,int n,Uint32 c){
    double a1,a2,t,a;
    int w;
    w=x2-x1;
    a1=getOpt("iSpiralA1",n);
    a2=getOpt("iSpiralA2",n);
    t=getOpt("iSpiralT",n);
    if(t<0.0001)
        t=0.0001;
    if(a1<0.0001)
       a1=0.0001;
    if(a2<0.0001)
       a2=0.0001;

    int lx,ly,x,y;
    lx=-1000;
    ly=(y1+y2)/2;
    a=100;
    for(int i=0;i<128;i++){
        double dx,dy;
        dy=sin(i/12./(t*64/M_PI))/10/(a1);
        dx=cos(i/12./(t*64/M_PI))/10/(a2);
        x=x1 + i*w/128+dx*a;
        y=(y1+y2)/2+dy*a;
        if(lx>-100)
        drawLine(screen,lx,ly,x,y,c);
        lx=x;
        ly=y;    
    }

}
void seq9GeoItemSetup(){
    int n=dialogParam;
    int ns[4];
    
    const char *s[4]={"iSpiralA1","iSpiralA2","iSpiralT"};    
    Uint32 colors[4]={RED,GREEN,BLUE,WHITE};

    ns[0]=ns[1]=ns[2]=ns[3]=n;
    drawOptStack(dSc,dX1,dY1,(dX2+dX1)/2,dY2,s,colors,ns,3);
  
    bar(dSc,(dX2+dX1)/2,dY1,dX2,(dY2+dY1)/2,0);
    
    drawInterval(dSc,(dX2+dX1)/2,dY1,dX2,(dY2+dY1)/2,n,iColors[n]);
    drawSpiral(dSc,(dX2+dX1)/2,dY1,dX2,(dY2+dY1)/2,n,RED);
}

void set3ToneInterval1(){
    int n,i;
    n=butParam/100;
    i=butParam%100;
    setOpt("3Interval1",n,i);
}
void set3ToneInterval2(){
    int n,i;
    n=butParam/100;
    i=butParam%100;
    setOpt("3Interval2",n,i);
}
void draw3ToneIntervalsSetup(SDL_Surface*screen,int x1,int y1,int x2,int y2,int n){
    int d1,d2,i,w,h;
    w=x2-x1;
    h=y2-y1;
    d1=getOpt("3Interval1",n);
    d2=getOpt("3Interval2",n);
    bar(screen,x1,y1,x2,y2,BLACK);
    if(d1==0){
        for(i=0;i<=12;i++){
            rectangle(screen,x1+i*w/12,y1,x1+(i+1)*w/12-1,y2,VERYGREEN);
            drawInterval(screen,x1+i*w/12,y1,x1+(i+1)*w/12-1,y2,i,GREEN);
            addButton(x1+i*w/12,y1,x1+(i+1)*w/12-1,y2,i+100*n,set3ToneInterval1);
        }   
    
    }else if(d2==0){
        for(i=0;i<=12;i++){
            if(i==d1){
                bar(screen,x1+i*w/12,y1,x1+(i+1)*w/12-1,y2,BLUE);
                addButton(x1+i*w/12,y1,x1+(i+1)*w/12-1,y2,100*n,set3ToneInterval1);

            }
            rectangle(screen,x1+i*w/12,y1,x1+(i+1)*w/12-1,y2,VERYGREEN);
            drawInterval(screen,x1+i*w/12,y1,x1+(i+1)*w/12-1,y2,i,GREEN);
            if(i>d1)
                addButton(x1+i*w/12,y1,x1+(i+1)*w/12-1,y2,i+100*n,set3ToneInterval2);
        }   
    }else{
        for(i=0;i<=12;i++){
            if(i==d1){
                bar(screen,x1+i*w/12,y1,x1+(i+1)*w/12-1,y2,BLUE);
                addButton(x1+i*w/12,y1,x1+(i+1)*w/12-1,y2,100*n,set3ToneInterval1);

            }
            if(i==d2){
                bar(screen,x1+i*w/12,y1,x1+(i+1)*w/12-1,y2,MAGENTA);
                addButton(x1+i*w/12,y1,x1+(i+1)*w/12-1,y2,100*n,set3ToneInterval2);
            }else if(i>d1){
            //    bar(screen,x1+i*w/12,y1,x1+(i+1)*w/12-1,y2,MAGENTA);
                addButton(x1+i*w/12,y1,x1+(i+1)*w/12-1,y2,i+100*n,set3ToneInterval2);
                
            }
            rectangle(screen,x1+i*w/12,y1,x1+(i+1)*w/12-1,y2,VERYGREEN);
            drawInterval(screen,x1+i*w/12,y1,x1+(i+1)*w/12-1,y2,i,GREEN);
        
        }   
    
    
    }


}
void seq9ColorItem3Setup(){
    int n=dialogParam;
    int ns[4];
    const char *s[4]={"3Red","3Green","3Blue","3Value"};    
    Uint32 colors[4]={RED,GREEN,BLUE,WHITE};
    struct rgb c;
    c.b=255*getOpt("3Red",n);
    c.g=255*getOpt("3Green",n);
    c.r=255*getOpt("3Blue",n);
    Uint32 cc;
    cc=*((Uint32*)&c);
    ns[0]=ns[1]=ns[2]=ns[3]=n;
    int y2=dY2;
    dY2=(dY2*8+dY1*2)/10;
 
    draw3ToneIntervalsSetup(dSc,dX1,dY2,dX2,y2,n);
    
    drawOptStack(dSc,dX1,dY1,(dX2+dX1)/2,dY2,s,colors,ns,4);
    bar(dSc,(dX2+dX1)/2,dY1,dX2,(dY2+dY1)/2,0);
    
    draw3Tone(dSc,(dX2+dX1)/2,dY1,dX2,(dY2+dY1)/2,n,iColors[n]);

    bar(dSc,(dX2+dX1)/2,(dY2+dY1)/2,dX2,dY2,cc);
    
            
    
}

void rizeSeq9ColorItemSetup(){
    addDialog(butParam,seq9ColorItemSetup);

}
void rizeSeq9GeoItemSetup(){
    addDialog(butParam,seq9GeoItemSetup);

}
void rizeSeq9ColorItem3Setup(){
    addDialog(butParam,seq9ColorItem3Setup);

}
void drawSeq9ColorSetupItem(SDL_Surface*screen,int x1,int y1,int x2,int y2,int n){
        struct rgb c;
        double v;
        int w,h;
        w=x2-x1;
        h=y2-y1;
        c.b=255*getOpt("iRed",n);
        c.g=255*getOpt("iGreen",n);
        c.r=255*getOpt("iBlue",n);
        v=getOpt("iStat",n);
        setOpt("iValue",n,getOpt("iValue",n));
        Uint32 cc;
        cc=*((Uint32*)&c);
        //bar(screen,x1,y1,x2,y2,cc);
        drawInterval(screen,x1,y1,x1+w*8/10,y2,n,cc);
        bar(screen,x1+w*9/10,y2-h*v,x2,y2,VERYGREEN);
        bar(screen,x1+w*8/10,y2-h*getOpt("iValue",n),x1+w*9/10,y2,WHITE);
        addRelizeButton(x1,y1,x2,y2,n,rizeSeq9ColorItemSetup);
        addEValue(x1,y1,x2,y2,getOptAdress("iValue",n));
}

void drawSeq9GeoSetupItem(SDL_Surface*screen,int x1,int y1,int x2,int y2,int n){
        int w,h;
        double a1,a2,t,v;
        w=x2-x1;
        h=y2-y1;
        a1=getOpt("iSpiralA1",n);
        a2=getOpt("iSpiralA2",n);
        t=getOpt("iSpiralT",n);
        v=getOpt("iStat",n);
       // setOpt("iValue",n,getOpt("iValue",n));
       // Uint32 cc;
      //  cc=*((Uint32*)&c);
        //bar(screen,x1,y1,x2,y2,cc);
        drawInterval(screen,x1,y1,x1+w*9/10,y2,n,VERYGREEN);
        drawSpiral(screen,x1,y1,x1+w*9/10,y2,n,RED);
      
        bar(screen,x1+w*9/10,y2-h*v,x2,y2,VERYGREEN);
      //  bar(screen,x1+w*8/10,y2-h*getOpt("iValue",n),x1+w*9/10,y2,WHITE);
        addButton(x1,y1,x2,y2,n,rizeSeq9GeoItemSetup);
        //addEValue(x1,y1,x2,y2,getOptAdress("iValue",n));
}

void drawSeq9ColorSetupItem3(SDL_Surface*screen,int x1,int y1,int x2,int y2,int n){
        struct rgb c;
        double v;
        int w,h;
        w=x2-x1;
        h=y2-y1;
        c.b=255*getOpt("3Red",n);
        c.g=255*getOpt("3Green",n);
        c.r=255*getOpt("3Blue",n);
        v=getOpt("3Stat",n);
        Uint32 cc;
        cc=*((Uint32*)&c);
        //bar(screen,x1,y1,x2,y2,cc);
        draw3Tone(screen,x1,y1,x1+w*8/10,y2,n,cc);
        bar(screen,x1+w*9/10,y2-h*v,x2,y2,VERYGREEN);
        bar(screen,x1+w*8/10,y2-h*getOpt("3Value",n),x1+w*9/10,y2,WHITE);

        addButton(x1,y1,x2,y2,n,rizeSeq9ColorItem3Setup);
}

int seq9ColorSetupPage=0;
void modifySeq9ColorSetupPageSwitcher(){
    seq9ColorSetupPage=1-seq9ColorSetupPage;
}
void drawSeq9ColorSetupPageSwitcher(SDL_Surface*screen,int x1,int y1,int x2,int y2){
    int w;
    w=x2-x1;
    if(seq9ColorSetupPage==0)
        bar(screen,x1,y1,x1+w/2,y2,CYAN);
    else
        bar(screen,x1,y1,x1+w/2,y2,BLUE);

    addButton(x1,y1,x1+w/2,y2,0,modifySeq9ColorSetupPageSwitcher);


    bar(screen,x1+w/2,y1,x2,y2,MAGENTA);
    addButton(x1+w/2,y1,x2,y2,0,switchDrawIntMetod);

    

}
void seq9ColorSetup(){
    bar(dSc,dX1,dY1,dX2,dY2,0);
    int x,y,i,w,h;
            int a,b,c,d;
    int x2;
    x2=dX2;
    w=dX2-dX1;
    h=dY2-dY1;
    dX2=(dX2*8+dX1*2)/10;
   const  char *s[]={"intervalComparePow","intervalsMul","3tonesMul"};
//    int ns[]={0,0};
    Uint32 cs[]={WHITE,CYAN,BLUE};
    drawOptStack(dSc,dX2,dY1,x2,dY2-h/5,s,cs,3);


    drawSeq9ColorSetupPageSwitcher(dSc,dX2,dY2-h/5,x2,dY2);
    w=dX2-dX1;
    h=dY2-dY1;
    x=0;y=0;
    
    if(seq9ColorSetupPage==0){
        for(i=0;i<=12;i++){
            a=dX1+w*x/4;
            b=dY1+h*y/4;
            c=dX1+w*(x+1)/4;
            d=dY1+h*(y+1)/4;
            drawSeq9ColorSetupItem(dSc,a,b,c,d,i);
            x++;
            if(x>=4){
                x=0;y++;
            }
        }
    }else{
        for(i=0;i<=12;i++){
            a=dX1+w*x/4;
            b=dY1+h*y/4;
            c=dX1+w*(x+1)/4;
            d=dY1+h*(y+1)/4;
            drawSeq9ColorSetupItem3(dSc,a,b,c,d,i);
            x++;
            if(x>=4){
                x=0;y++;
            }
        }
    }

}
void rizeSeq9ColorSetup(){
    addDialog(0,seq9ColorSetup);

}


void seq9GeoSetup(){
    bar(dSc,dX1,dY1,dX2,dY2,0);
    int x,y,i,w,h;
    int a,b,c,d;
    int x2;
    x2=dX2;
    w=dX2-dX1;
    h=dY2-dY1;
    dX2=(dX2*8+dX1*2)/10;
    const  char *s[]={"ampZero","ampAsc","ampAmp"};
//    int ns[]={0,0};
    Uint32 cs[]={WHITE,CYAN,BLUE};
    drawOptStack(dSc,dX2,dY1,x2,dY2-h/5,s,cs,3);


   // drawSeq9ColorSetupPageSwitcher(dSc,dX2,dY2-h/5,x2,dY2);
    w=dX2-dX1;
    h=dY2-dY1;
    x=0;y=0;
    
    for(i=0;i<=12;i++){
            a=dX1+w*x/4;
            b=dY1+h*y/4;
            c=dX1+w*(x+1)/4;
            d=dY1+h*(y+1)/4;
            drawSeq9GeoSetupItem(dSc,a,b,c,d,i);
            x++;
            if(x>=4){
                x=0;y++;
            }
    }
}
void rizeSeq9GeoSetup(){
    addDialog(0,seq9GeoSetup);
}


void drawSeq9ColorSetupButton(SDL_Surface*screen,int x1,int y1,int x2,int y2){
    bar(screen,x1,y1,x2,y2,WHITE);
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);
    addButton(x1,y1,x2,y2,0,rizeSeq9ColorSetup);
}

void drawSeq9GeoSetupButton(SDL_Surface*screen,int x1,int y1,int x2,int y2){
    bar(screen,x1,y1,x2,y2,WHITE);
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);
    addButton(x1,y1,x2,y2,0,rizeSeq9GeoSetup);
}
void drawColorSeq(int x1,int y1,int x2,int y2,SDL_Surface*screen){
    int h,w,i,yr,yg,yb;
    int gx1,gx2,gy1,gy2,gw,gh;
    int minFreqX;
    w=x2-x1;
    h=y2-y1;
    
    gx1=x1+w/20;
    gx2=x2-w/20;
    gy2=y2-4*h/20;
    gy1=y1+h/3;
    
    gw=gx2-gx1;
    gh=gy2-gy1;
    
    Uint32 c;
    bar(screen,x1,y1,x2,y2,0);
    colorSeqSplash=drawSplash(screen,x1,y1,x2,y2,colorSeqSplash);
    
    //minFreqX = log(minColorSeqFreq+1)*gw/log(SAMPLE_RATE/2+1);
   // bar(screen,gx1+minFreqX-1,y2-h/40,gx1+minFreqX+1,y2,0xffffff);
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
   //drawOqColorLines(screen,gx1,gy1,gx2,gy2);
   
   
   drawSeq9GeoSetupButton(screen,x1+w/20,y1+h/20,x1+w/6,y1+h/3);
   
   drawColorCorrectorPannelStack(screen,x1+w/6,y1+h/20,(x1+x2)/2,y1+h/3);

   drawColorSeqSwitcher(screen,x1+w/20,y2-h/6,(x1+x2)/6,y2-h/20);
   
   if(colorSeqVar!=9){
        drawLinDisesSwitcher(screen,(x1+x2)/6,y2-h/6,2*(x1+x2)/6,y2-h/20);
   }else{
        drawSeq9ColorSetupButton(screen,(x1+x2)/6,y2-h/6,2*(x1+x2)/6,y2-h/20);
   
   }
   
   
   
   bar(screen,2*(x1+x2)/6,y2-h/6,(x1+x2)/2,y2-h/200,GRAY);
   
   addButton(2*(x1+x2)/6,y2-h/6,(x1+x2)/2,y2-h/200,0,rizeSpeakerControll);


   drawMapOq(screen,(x1+x2)/2,y1+h/20,x2-w/20,y1+h/3);
  // drawColorStat(screen,x1+w/20,y1+h/3,x2-w/20,y2-h/20);
   
   rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);
   //addButton(x1,y1,x2,y2,0,changeColorSeq);
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
      hsv_c.h=getOpt("soundKoefsColorH",i);
      hsv_c.s=getOpt("soundKoefsColorS",i);
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

void drawGLPannelKoefs(SDL_Surface*screen,int x1,int y1,int x2,int y2,int k){
    double values[GLOPTKOEFS];
    double *ev[GLOPTKOEFS];

    double controlls[GLOPTKOEFS];
    Uint32 colors[GLOPTKOEFS];
    int i,minusFlag,ttth,tttw,y;
    double max;
    int panel;
    int param;
    int noMaxDrawKoef=0;
    if(k<0){
        k=-k;
        noMaxDrawKoef=1;
        
    }
//    if(rizePannel ==0)
  //      addButton(x1,y1,x2,y2,k,rizeBarPannel);

    
    
    for(i=-1;i<KOEFNUM;i++){
        double t;
        if(i>=0){
            colors[i+1]=getSoundKoefsColor(i,0);
            t=soundKoefs[i]*glOptKoefs[k*GLOPTKOEFS+ i+1];
            values[1+i]=t;

        }else{
            colors[0]=0xffff00;
            values[0]=glOptKoefs[k*GLOPTKOEFS+ i+1];
            }
        controlls[1+i]=glOptKoefs[k*GLOPTKOEFS+ i+1];
        ev[1+i]=&(glOptKoefs[k*GLOPTKOEFS+ i+1]);
    }
    minusFlag=1;
    max=0.5;
    minusFlag++;
    if(max<0.0001){
        max=0.0001;
    }
    ttth=y2-y1;
    tttw=x2-x1;
    
    for(i=0;i<GLOPTKOEFS;i++){
        int a,b,c,d,dd,ay;

        y=values[i]/max*ttth*(18/20.)/(minusFlag);
        ay=controlls[i]/max*ttth*(18/20.)/(minusFlag);
        
        
        a=x1 +tttw/GLOPTKOEFS/20 +tttw/20+ i*tttw*(18./20)/GLOPTKOEFS;
        b=y1 -ttth/20.  +ttth/(minusFlag);
        c=x1 +tttw/20 -tttw/GLOPTKOEFS/20 +(i+1)*tttw*(18./20)/GLOPTKOEFS;
        d=y1 -ttth/20. -y +ttth/(minusFlag);
        dd=y1-ttth/20. -ay +ttth/(minusFlag);
        
        //printf("_ABCD:(%d-%d)(%d-%d)%d %d %d %d (%f)(%f)\n",x1,y1,x2,y2,a,b,c,d,values[i],max);
        
        bar(screen,a,b,c,d,colors[i]);
        rectangle(screen,a,b,c,dd,WHITE);
        if(rizePannel ==1)
            addEValue(a,y1+ttth/10-(minusFlag-1)*ttth/10,c,y2-ttth/10-(minusFlag-1)*ttth/10,0,max/1500,-100,100,ev[i]);
        
//        if(k==panel && i==param){
  //              rectangle(screen,a,b,c,dd,RED);

    //    }
    }
    y=1./max*ttth*(18/20.)/(minusFlag);
    y=y1 -ttth/20. -y +ttth/(minusFlag);
    rectangle(screen,x1+2,y,x2-2,y,WHITE);
   // if(k==panel){
     //   rectangle(screen,x1+1,y1+1,x2-1,y2-1,RED);
   // }
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
extern double colorCorrector[CCORLEN];
void modifyCorrectColorFlag(){
    correctColorFlag=!correctColorFlag;
}
void modifyMapOq(){
    cl->mapOq[butParam%OQS][butParam/OQS]=!cl->mapOq[butParam%OQS][butParam/OQS];
}


void drawColorStat(SDL_Surface*screen,int x1,int y1,int x2,int y2){
//colorStat COLORSTATLEN
    int i,w,h;
    Uint32 c;
    double a;
    w=x2-x1;
    h=y2-y1;
    bar(screen,x1,y1,x2,y2,0);
    if(rizePannel==0)
       addButton(x1,y1,x2,y2,0,rizeColorStat);

    
    for(i=0;i<18;i++){
        a=colorStat[i];
        if(a<0.)
            a=0.;
        if(a>1.)
            a=1.;
        c=(64+i*(128+64)/18);
        c=c|(c*256)|(c*256*256);
        bar(screen,x1+i*w/18/2,y2,x1+(i+1)*w/18/2 -1,y2-h*a,c);
    }
    for(i=18;i<36;i++){
        a=colorStat[i];
        if(a<0.)
            a=0.;
        if(a>1.)
            a=1.;
        c=((i-18)*128/18);
        c=(c+128)|((128-c)*256)|((c+128)*256*256);
        bar(screen,x1+i*w/18/2,y2,x1+(i+1)*w/18/2 -1,y2-h*a,c);
    }

    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);

}


void drawMapOq(SDL_Surface*screen,int x1,int y1,int x2,int y2){
    int i,j,h,w;
    int oqs;
    oqs=10;
    w=x2-x1;
    h=y2-y1;
    if(rizePannel==0)
        addButton(x1,y1,x2,y2,0,rizeMapOq);
     for(i=0;i<oqs;i++)
        for(j=0;j<oqs;j++){
            if(rizePannel)
                addButton(x1+i*w/oqs,y2-(j+1)*h/oqs+1,x1+(i+1)*w/oqs-1,y2-j*h/oqs,j+i*OQS,modifyMapOq);
            if(cl->mapOq[j][i]){
                bar(screen,x1+i*w/oqs,y2-j*h/oqs,x1+(i+1)*w/oqs-1,y2-(j+1)*h/oqs+1,WHITE);
              }else{
                if(rizePannel)
                    rectangle(screen,x1+i*w/oqs,y2-j*h/oqs,x1+(i+1)*w/oqs-1,y2-(j+1)*h/oqs+1,WHITE);
                else
                    bar(screen,x1+i*w/oqs,y2-j*h/oqs,x1+(i+1)*w/oqs-1,y2-(j+1)*h/oqs+1,GRAY);
                    
            }
     }


}
int centerSwitch;
void modifyCenterSwitch(){
    centerSwitch=butParam;
    if(centerSwitch==3){
   //    setOpt("monitor_allMajors",1);
 //      setOpt("monitor_allMinors",1);    
    }else{
     //  setOpt("monitor_allMajors",0.1);
     //  setOpt("monitor_allMinors",0.1);

    }
}
void drawCenterSwitcher(SDL_Surface*screen,int x1,int y1,int x2,int y2){
    int ax,bx,cx,dx;
    ax=(x1*4+x2)/5;
    bx=(x1*3+x2*2)/5;
    cx=(x1*2+x2*3)/5;
    dx=(x1+x2*4)/5;

    bar(screen,x1,y1,x2,y2,0);
    if(centerSwitch==0){
        bar(screen,x1,y1,ax,y2,VERYGREEN);
    }else{
        rectangle(screen,x1,y1,ax,y2,VERYGREEN);
               addButton(x1,y1,ax,y2,0,modifyCenterSwitch);
    }
    if(centerSwitch==1){
        bar(screen,ax,y1,bx,y2,VERYGREEN);
    }else{
        rectangle(screen,ax,y1,bx,y2,VERYGREEN);
               addButton(ax,y1,bx,y2,1,modifyCenterSwitch);
    }
    if(centerSwitch==2){
        bar(screen,bx,y1,cx,y2,VERYGREEN);
    }else{
        rectangle(screen,bx,y1,cx,y2,VERYGREEN);
               addButton(bx,y1,cx,y2,2,modifyCenterSwitch);
    }
    if(centerSwitch==3){
        bar(screen,cx,y1,x2,y2,VERYGREEN);
    }else{
        rectangle(screen,cx,y1,dx,y2,VERYGREEN);
        addButton(cx,y1,dx,y2,3,modifyCenterSwitch);
    }
    if(centerSwitch==4){
        bar(screen,cx,y1,x2,y2,VERYGREEN);
    }else{
        rectangle(screen,dx,y1,x2,y2,VERYGREEN);
        addButton(dx,y1,x2,y2,4,modifyCenterSwitch);
    }
    
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);
}

void drawBorders(SDL_Surface*screen,int x1,int y1,int x2,int y2,double *borders,double*counts,int n){
    double summ;
    summ=0.;
    int h,w,i;
    w=x2-x1;
    h=y2-y1;
    for(int i=0;i<n;i++){
        summ+=counts[i];
    }
    if(summ>0.000001){
        double lborder=0.;
        for(i=0;i<n;i++){
            Uint32 c;
            int myh;
            double p;
            myh=h*counts[i]/summ;
            lborder=borders[i];
            //c=RED;
            p=1000;
            if(borders[i]-lborder>0.00001){
                p=counts[i]/summ/(borders[i]-lborder);
            }
            if(p>1){
                p=1-1/(p);
                rgb2pixel(p*255,255,0,&c);
            }else{
                p=1-p;
                rgb2pixel(0,255,p*255,&c);
            }
            bar(screen,x1+ (int)(lborder*w),y1+h-myh,x1+ ((int)(borders[i]*w)),y1+h,c);
        }
    }
}

void drawMonitor(SDL_Surface*screen,int x1,int y1,int x2,int y2,const char*s){
    char name[256];
    double max,min,superMax,superMin,value,corOn,corSpeed;
    double corCounts[CORLEVEL];
    double corBorders[CORLEVEL];
    int x,y,h,w;
    x=(x1+9*x2) / (10);
    y=(y1+9*y2)/ (10);
    h=(8*(y2-y1))  /(10);
    w=(8*(x2-x1))  /(10);
    
    sprintf(name,"monitor_%s_min",s);
    min=getOpt(name);
    sprintf(name,"monitor_%s_max",s);
    max=getOpt(name);
    sprintf(name,"monitor_%s_value",s);
    value=getOpt(name);
    sprintf(name,"monitor_%s_superMin",s);
    superMin=getOpt(name);
    sprintf(name,"monitor_%s_superMax",s);
    superMax=getOpt(name);
    sprintf(name,"monitor_%s_cor_on",s);
    corOn=getOpt(name);
    sprintf(name,"monitor_%s_cor_speed",s);
    corSpeed=getOpt(s);
    for(int i=0;i<CORLEVEL;i++){
      sprintf(name,"monitor_%s_cor_counts_%d",s,i);
      corCounts[i]=getOpt(name);
      sprintf(name,"monitor_%s_cor_borders_%d",s,i);
      corBorders[i]=getOpt(name);
    }    

    bar(screen,x,y,x+w/10,y+h,BLUE);
    if(superMax-superMin>0.0000001){
        bar(screen,x,y+h-h*(max-superMin)/(superMax-superMin),x+w/10,y+h-h*(min-superMin)/(superMax-superMin),GREEN);
        int my;
        my=y+h-h*(value-superMin)/(superMax-superMin);
        bar(screen,x,my-1,x+w/10,my+1,YELLOW);
    }
    drawBorders(screen,x+2*w/10,y,x+w,y+h,corBorders,corCounts,CORLEVEL);

}
Uint32 NEG(Uint32 a){

    return a ^ 0xffffff;
}


void drawOptStackRBKoefs(SDL_Surface*screen,int x1,int y1,int x2,int y2,char const**opts,Uint32*colors,int n){
    int i,h,w;
    h=y2-y1;
    w=x2-x1;
    double v;
    bar(screen,x1,y1,x2,y2,0);
    for(i=0;i<n;i++){
        double sk;
        v=getOpt(opts[i]);
        sk=getOptValue(opts[i]);
        if(v>=0.){
            bar(screen,x1+w*i/n,y2-h*v,x1+w*(i+1)/n,y2,colors[i]);
        }else{
            bar(screen,x1+w*i/n,y1,x1+w*(i+1)/n,y1-h*v,colors[i]);
        }

        if(sk>=0.){
            bar(screen,x1+w*i/n +w/n/2 -1 ,y2-h*sk,x1+w*i/n +w/n/2 +1,y2,NEG(colors[i]));
            bar(screen,x1+w*i/n +w/n/2  ,y2-h*sk,x1+w*(i)/n +w/n/2 ,y2,colors[i]);
        }else{
            bar(screen,x1+w*i/n +w/n/2 -1 ,y1,x1+w*i/n +w/n/2 +1,y1-h*sk,NEG(colors[i]));
            bar(screen,x1+w*i/n +w/n/2  ,y1,x1+w*i/n +w/n/2,y1-h*sk,(colors[i]));
        }


        rectangle(screen,x1+w*i/n,y1,x1+w*(i+1)/n,y2,BORDERCOLOR);


        setOpt(opts[i],getOpt(opts[i]));                        
//        addEValue(x1+w*i/n,y1,x1+w*(i+1)/n,y2,getOptAdress(opts[i]));
        if(v>0.001){
            addEValue(x1+w*i/n,y1,x1+w*(i+1)/n,y2,0.,1.,getOptAdress(opts[i]));
        }else if(v<-0.001){
            addEValue(x1+w*i/n,y1,x1+w*(i+1)/n,y2,-1.,0.,getOptAdress(opts[i]));
        }else {
            addEValue(x1+w*i/n,y1,x1+w*(i+1)/n,y2,-1.,1.,getOptAdress(opts[i]));
        }
        addRelizeButton(x1+w*i/n,y1,x1+w*(i+1)/n,y2,(char*)opts[i],rizeOptStackKoefs);

    }
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);

}

void zeroThisOpt(){
    setOpt(sbutParam,0.);
}
void drawOptStack(SDL_Surface*screen,int x1,int y1,int x2,int y2,char const**opts,Uint32*colors,int n){
    int i,h,w;
    h=y2-y1;
    w=x2-x1;
    double v;
    bar(screen,x1,y1,x2,y2,0);
    for(i=0;i<n;i++){
    
        double sk;
        v=getOpt(opts[i]);
//        sk=getOptValue(opts[i]);
        if(v>=0.){
            bar(screen,x1+w*i/n,y2-h*v,x1+w*(i+1)/n,y2,colors[i]);
        }else{
            bar(screen,x1+w*i/n,y1,x1+w*(i+1)/n,y1-h*v,colors[i]);
        }

  //      if(sk>=0.){
    //        bar(screen,x1+w*i/n +w/n/2 -1 ,y2-h*sk,x1+w*i/n +w/n/2 +1,y2,NEG(colors[i]));
      //      bar(screen,x1+w*i/n +w/n/2  ,y2-h*sk,x1+w*(i)/n +w/n/2 ,y2,colors[i]);
        //}else{
          //  bar(screen,x1+w*i/n +w/n/2 -1 ,y1,x1+w*i/n +w/n/2 +1,y1-h*sk,NEG(colors[i]));
            //bar(screen,x1+w*i/n +w/n/2  ,y1,x1+w*i/n +w/n/2,y1-h*sk,(colors[i]));
        //}


        rectangle(screen,x1+w*i/n,y1,x1+w*(i+1)/n,y2,BORDERCOLOR);


        setOpt(opts[i],getOpt(opts[i]));                        
//        addEValue(x1+w*i/n,y1,x1+w*(i+1)/n,y2,getOptAdress(opts[i]));
        if(v>0.001){
            addEValue(x1+w*i/n,y1,x1+w*(i+1)/n,y2,0.,1.,getOptAdress(opts[i]));
        }else if(v<-0.001){
            addEValue(x1+w*i/n,y1,x1+w*(i+1)/n,y2,-1.,0.,getOptAdress(opts[i]));
        }else {
            addEValue(x1+w*i/n,y1,x1+w*(i+1)/n,y2,-1.,1.,getOptAdress(opts[i]));
        }

        // fprintf(stderr,"THIS!\n");
    
        //bar(screen,x1+w*i/n,y2-h*v,x1+w*(i+1)/n,y2,colors[i]);
       // rectangle(screen,x1+w*i/n,y1,x1+w*(i+1)/n,y2,BORDERCOLOR);
       // setOpt(opts[i],getOpt(opts[i]));                        
        //addEValue(x1+w*i/n,y1,x1+w*(i+1)/n,y2,getOptAdress(opts[i]));
        addRelizeButton(x1+w*i/n,y1,x1+w*(i+1)/n,y2,(char*)opts[i],zeroThisOpt);

    }
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);

}    
void drawOptStack(SDL_Surface*screen,int x1,int y1,int x2,int y2,char const**opts,Uint32*colors,int* optsn ,int n){
    int i,h,w;
    h=y2-y1;
    w=x2-x1;
    double v;
    bar(screen,x1,y1,x2,y2,0);
    for(i=0;i<n;i++){
        
        
        
        
        setOpt(opts[i],optsn[i],getOpt(opts[i],optsn[i]));                        
        v=getOpt(opts[i],optsn[i]);
          if(v>=0.){
            bar(screen,x1+w*i/n,y2-h*v,x1+w*(i+1)/n,y2,colors[i]);
        }else{
            bar(screen,x1+w*i/n,y1,x1+w*(i+1)/n,y1-h*v,colors[i]);
        }

  //      if(sk>=0.){
    //        bar(screen,x1+w*i/n +w/n/2 -1 ,y2-h*sk,x1+w*i/n +w/n/2 +1,y2,NEG(colors[i]));
      //      bar(screen,x1+w*i/n +w/n/2  ,y2-h*sk,x1+w*(i)/n +w/n/2 ,y2,colors[i]);
        //}else{
          //  bar(screen,x1+w*i/n +w/n/2 -1 ,y1,x1+w*i/n +w/n/2 +1,y1-h*sk,NEG(colors[i]));
            //bar(screen,x1+w*i/n +w/n/2  ,y1,x1+w*i/n +w/n/2,y1-h*sk,(colors[i]));
        //}


        rectangle(screen,x1+w*i/n,y1,x1+w*(i+1)/n,y2,BORDERCOLOR);


//        setOpt(opts[i],getOpt(opts[i]));                        
//        addEValue(x1+w*i/n,y1,x1+w*(i+1)/n,y2,getOptAdress(opts[i]));
        if(v>0.001){
            addEValue(x1+w*i/n,y1,x1+w*(i+1)/n,y2,0.,1.,getOptAdress(opts[i],optsn[i]));
        }else if(v<-0.001){
            addEValue(x1+w*i/n,y1,x1+w*(i+1)/n,y2,-1.,0.,getOptAdress(opts[i],optsn[i]));
        }else {
            addEValue(x1+w*i/n,y1,x1+w*(i+1)/n,y2,-1.,1.,getOptAdress(opts[i],optsn[i]));
        }
        
        
        //bar(screen,x1+w*i/n,y2-h*v,x1+w*(i+1)/n,y2,colors[i]);
        //rectangle(screen,x1+w*i/n,y1,x1+w*(i+1)/n,y2,BORDERCOLOR);

//        addEValue(x1+w*i/n,y1,x1+w*(i+1)/n,y2,getOptAdress(opts[i],optsn[i]));
     //   fprintf(stderr,"optsn[%d]=%d\n",i,optsn[i]);
    }
    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);

}


void drawColorCorrectorPannelStack(SDL_Surface*screen,int x1,int ay1,int x2,int y2){
    const char *order="s3fs3fs1fss3fs3ff";
    double values[CCORLEN];
    double controlls[CCORLEN];
    int y1;
   // Uint32 colors[LAYEROPTS];
    int i,ttth,tttw;
    double max;
    int panel;
    int param;
    int rx1;
    double *ev[CCORLEN];
    Uint32 colors[CCORLEN]={WHITE,GRAY,BLUE,WHITE,GRAY,BLUE,VIOLVET,WHITE,GRAY,BLUE,WHITE,GRAY,BLUE,};
    y1=ay1;
    if(rizePannel ==0)
        addButton(x1,y1,x2,y2,0,rizeColorCorrectorPannel);
    else{
        drawColorStat(screen,x1,y1,x2,(y1*4+y2)/5);
        y1=(ay1*4+y2)/5;
           
        rx1=x1;
        x1=(x1*9+x2)/10;
        if(correctColorFlag){
            bar(screen,rx1,(y1*9+y2)/10,x1,(y1*3+y2)/4,GREEN);        
        }else{
            rectangle(screen,rx1,(y1*9+y2)/10,x1,(y1*3+y2)/4,GREEN);        
        }
        addButton(rx1,(y1*9+y2)/10,x1,(y1*3+y2)/4,0,modifyCorrectColorFlag);

    }
    
    max=1.;
    tttw=x2-x1;
    int deep=0;
    int mindeepy=screen->h;
    int a,sx,fx,y;
    for(i=0;*order;order++){
        if(*order=='s'){
            mypush(i);
            deep++;
        }
        if(*order>='1'&&*order<='9'){
            i+=(*order)-'0';
        }
        if(*order=='f'){
            a=mypop();
            sx=x1+tttw/CCORLEN/20 +tttw/20 +a*tttw*(18./20)/CCORLEN;
            fx=x1 +tttw/20 -tttw/CCORLEN/20 +(i)*tttw*(18./20)/CCORLEN;
            y=y2-5-deep*15;
            bar(screen,sx,y-5,fx,y,BORDERCOLOR);
            if(mindeepy>y-1){
                mindeepy=y-1;
            }
            deep--;
        }
    
    }
    
    ttth=mindeepy-y1;

    for(i=0;i<CCORLEN;i++){
        int a,b,c,d,dd,ay;
        y=colorCorrector[i]/max*ttth*(18/20.);
        ev[i]=colorCorrector+i;
        
        a=x1 +tttw/CCORLEN/20 +tttw/20+ i*tttw*(18./20)/CCORLEN;
        b=y1 -ttth/20.  +ttth;
        c=x1 +tttw/20 -tttw/CCORLEN/20 +(i+1)*tttw*(18./20)/CCORLEN;
        d=y1 -ttth/20. -y +ttth;
       // dd=y1-ttth/20. -ay +ttth/(minusFlag);
        
        
        bar(screen,a,b,c,d,colors[i]);
        rectangle(screen,a,b,c,d,WHITE);
        if(rizePannel ==1)
            addEValue(a,y1,c,y2,0,0.001,0,1,ev[i]);
       // rectangle(screen,a,y1,c,y2,BLUE);
//        if(k==panel && i==param){
  //              rectangle(screen,a,b,c,d,RED);

    //    }
    }
    y=.5/max*ttth*(18/20.);
    y=y1 -ttth/20. -y +ttth;
    rectangle(screen,x1+2,y,x2-2,y,WHITE);
   // if(k==panel){
     //   rectangle(screen,x1+1,y1+1,x2-1,y2-1,RED);
   // }
}




void drawGLPannelStack(SDL_Surface*screen,int x1,int ay1,int x2,int y2){
    const char *order="ss2ffss2fs1fs2fs1ffss1f5f";
    double values[GLOPTS];
    double controlls[GLOPTS];
    int y1;
   // Uint32 colors[LAYEROPTS];
    int i,ttth,tttw;
    double max;
    int panel;
    int param;
    int rx1;
    double *ev[GLOPTS];
    Uint32 colors[GLOPTS]={WHITE,GRAY,BLUE,WHITE,BROWN,RED,MAGENTA,CYAN,WHITE,BLUE,GREEN,RED,YELLOW,YELLOW};
    y1=ay1;
    if(rizePannel ==0)
        addButton(x1,y1,x2,y2,0,rizeGLPannel);
    
    max=1.;
    tttw=x2-x1;
    int deep=0;
    int mindeepy=screen->h;
    int a,sx,fx,y;
    for(i=0;*order;order++){
        if(*order=='s'){
            mypush(i);
            deep++;
        }
        if(*order>='1'&&*order<='9'){
            i+=(*order)-'0';
        }
        if(*order=='f'){
            a=mypop();
            sx=x1+tttw/GLOPTS/20 +tttw/20 +a*tttw*(18./20)/GLOPTS;
            fx=x1 +tttw/20 -tttw/GLOPTS/20 +(i)*tttw*(18./20)/GLOPTS;
            y=y2-5-deep*15;
            bar(screen,sx,y-5,fx,y,BORDERCOLOR);
            if(mindeepy>y-1){
                mindeepy=y-1;
            }
            deep--;
        }
    
    }
    
    ttth=mindeepy-y1;

    for(i=0;i<GLOPTS;i++){
        int a,b,c,d,dd,ay;
        y=glOpt[i]/max*ttth*(18/20.);
        ev[i]=glOpt+i;
        
        a=x1 +tttw/GLOPTS/20 +tttw/20+ i*tttw*(18./20)/GLOPTS;
        b=y1 -ttth/20.  +ttth;
        c=x1 +tttw/20 -tttw/GLOPTS/20 +(i+1)*tttw*(18./20)/GLOPTS;
        d=y1 -ttth/20. -y +ttth;
       // dd=y1-ttth/20. -ay +ttth/(minusFlag);
        
        
        bar(screen,a,b,c,d,colors[i]);
        rectangle(screen,a,b,c,d,WHITE);
        if(rizePannel ==1){
            addEValue(a,y1,c,y2,0,0.001,0,1,ev[i]);
            addRelizeButton(a,y1,c,y2,i,rizeGLPannelKoefs);
    
       } 
       // rectangle(screen,a,y1,c,y2,BLUE);
//        if(k==panel && i==param){
  //              rectangle(screen,a,b,c,d,RED);

    //    }
    }
    y=.5/max*ttth*(18/20.);
    y=y1 -ttth/20. -y +ttth;
    rectangle(screen,x1+2,y,x2-2,y,WHITE);
   // if(k==panel){
     //   rectangle(screen,x1+1,y1+1,x2-1,y2-1,RED);
   // }
}


void drawFilterPannelStack(SDL_Surface*screen,int x1,int y1,int x2,int y2,int k){
    const char *order="ss2f3s3ffs2fs2fs3f";
    double values[LAYEROPTS];
    double controlls[LAYEROPTS];
   // Uint32 colors[LAYEROPTS];
    int i,ttth,tttw;
    double max;
    int panel;
    int param;
    double *ev[LAYEROPTS];
    Uint32 colors[LAYEROPTS]={GREEN,GREEN/2,0,0,0,RED,RED/2,YELLOW,YELLOW/2,MAGENTA,MAGENTA/2,0x505050,YELLOW,0xff00ff,0xffffff};
    
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


