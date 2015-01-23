#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<SDL/SDL.h>
#include"graphutil.cpp"
int mixerh=0;
int mixerw=0;
int *mixerbuf=NULL;
int *mul_mixerw;

void closeRgbMixer(){
    if(mixerbuf!=NULL){
        free(mixerbuf);
    }
    if(mul_mixerw!=NULL)
        free(mul_mixerw);
}

int ks0[256];
int ks1[256];
int ks2[256];
int oldFade(SDL_Surface* source,int div);
int bpb=4;
int bpb1=1;
int bpb2=2;

void calcKs(double alpha,int w,int mul){
    
    
    int x,xm;
    int sinalpha,cosalpha;
    int sinalpha2,cosalpha2;
    int sinalpha3,cosalpha3;
    sinalpha=1024*sin(alpha)/255.;
    cosalpha=1024*cos(alpha)/255.;
    sinalpha2=1024*sin(alpha+2.0*M_PI/3.0)/255.;
    cosalpha2=1024*cos(alpha+2.0*M_PI/3.0)/255.;
    sinalpha3=1024*sin(alpha+4.0*M_PI/3.0)/255.;
    cosalpha3=1024*cos(alpha+4.0*M_PI/3.0)/255.;
    
    for(x=0,xm=0;x<256;x++,xm+=mul){
        ks0[x]=bpb*(
        
                       (
                         (int)
                            (
                              sinalpha*xm/1024
                            )
                       ) + 
                       (
                         (int)
                         (
                             (w+20)*
                             (
                                 (int)
                                 (
                                     cosalpha*xm/1024
                                 )
                             )
                         )
                         
                       ) 
                            
                   );    //red shift
        ks1[x]=bpb1+bpb*(
        
                        (
                          (int)
                          (
                             sinalpha2*xm/1024)
                          )+ 
                          (
                                (int)(20+w)*
                                    (
                                       (int)(
                                             cosalpha2*xm/1024
                                             )
                                       )
                    
                    
                          )
                    );   //green shift

        ks2[x]=bpb2+bpb*(
                         (
                            (int)
                                   (    
                                      sinalpha3*xm/1024
                                    )
                          )  +   
                          (
                              (int)
                              (20+w)*
                              (    (int)
                                  (
                                  cosalpha3*xm/1024)
                                  )
                              
                           )   
                              );   //blue shift
        
        
   }


}

void  addNoise(SDL_Surface* s,int counts,int value,int colored){
    int i;
    struct rgb c;
    i=(s->w*s->h)*counts/100;
    if(value>255)
        value = 255;
    if(!value)
        value=1;
    for(;i>0;i--){
        if(colored){
            c=*(((struct rgb*)(&(colorSeq2Buf[rand()%SEQLEN]))));
            c.r=c.r*value/256;
            c.g=c.g*value/256;
            c.b=c.b*value/256;
            
        }else{
            c.b=c.g=c.r=rand()%value;
        }
        plusPixel(s,rand()%s->w,rand()%s->h,*((Uint32*)(&c)));
    
    }
    
    
    


}


int smoothMask[10]={ 0, 2, 0,
                     2, 2, 1,
                     0, 1, 0,  4};
                     

int smooth(SDL_Surface* source,SDL_Surface* dest){
    int x,y,xx,yy,dd,r,g,b,i;
    Uint8 * s,*d;
    int bpp = source->format->BytesPerPixel;
    s=(((Uint8 *)source->pixels) +bpp + source->pitch);
    
    d=(((Uint8 *)dest->pixels) +bpp   +  dest->pitch);
    
    for(y=1;y<source->h-1;y++,s=(1+ ((Uint8 *)source->pixels) + (y) * source->pitch),d=( ((Uint8 *)dest->pixels) + (y) * dest->pitch +1 ))
        for(x=1;x<source->w-1;x++,s++,d++){
            r=0;g=0;b=0;
            for(yy=-1,dd=-dest->pitch-bpp,i=0;yy<2;yy++,dd+=dest->pitch-bpp*2)
                for(xx=-1;xx<2;xx++,dd+=bpp,i++){
                    r+=((int)  (((struct rgb*) (s+dd))->r  ))<<smoothMask[i];
                    g+=((int)  (((struct rgb*) (s+dd))->g  ))<<smoothMask[i];
                    b+=((int)  (((struct rgb*) (s+dd))->b  ))<<smoothMask[i];
                }
           r=r>>smoothMask[9];
           g=b>>smoothMask[9];
           g=b>>smoothMask[9];
           
           ((struct rgb*)d)->r=0;//r;
           ((struct rgb*)d)->g=g;
           ((struct rgb*)d)->b=b;
        }

    return 0;
}
void copySurface(SDL_Surface* source,SDL_Surface* dest){
   memcpy(dest->pixels,source->pixels,source->h*source->pitch);
 // memset(dest->pixels,0,source->h*source->pitch);  
}


int oldFade(SDL_Surface* source,int div){
    int x,y;
    int back;
   double back_d;//,gray;
   back_d=getOpt("back");
   back=back_d*255;
   //gray=getOpt("background_value");
   // back=0;
    Uint8 d;
    struct rgb *p;
    
    if(div>20&&div!=255){
        div=10*(div/10); 
    }else if(div<20){
        div=2*(div/2);
    }
    
    if(div==255){
        SDL_FillRect(source,NULL, 0x000000);
        return 0;
    
    }
    d=div;
    p=(struct rgb *)( ((Uint8 *)source->pixels) );
    for(y=0;y<source->h;y++,p=(struct rgb *)( ((Uint8 *)source->pixels) + y * source->pitch))
        for(x=0;x<source->w;x++,p++){
            if(p->r>back+d){
                p->r-=d;
            }else if(p->r<back-d){
                p->r+=d;
            }else{
                p->r=back;            
            }
            
            if(p->g>back+d){
                p->g-=d;
            }else if(p->g<back-d){
                p->g+=d;
            }else{
                p->g=back;            
            }
            
            
            if(p->b>back+d){
                p->b-=d;
            }else if(p->b<back-d){
                p->b+=d;
            }else{
                p->b=back;            
            }
            if(p->o>0){
                p->o--;
            }        
        }
}

Uint32* fadeBufs[256][256];

Uint32 lastFadeBuf[256*256*256];
Uint32*fadeBuf;
int rgbMixer(SDL_Surface* source,SDL_Surface* filter,int mul,double alpha);
int controll(SDL_Surface *screen);
int prepareFade(struct SDL_Surface*screen,struct SDL_Surface*filter){
    int div,r,g,b,rr,gg,bb;
    int d;
    int back;
    back=255*getOpt("background_value");
    //setOpt background_value 0 0.5
    if(back<0)
        back=0;
    if(back>255)
        back=255;
    for(d=0;d<255;d++){
//        bar(screen,0,screen->h/3,screen->w*d/256,screen->h*2/3,WHITE);
//       SDL_FillRect(screen,NULL, 0x000000);
       oldFade(screen,10);
       drawPianoBar(screen,screen->w/3,screen->h/3,screen->w/3 + (d*screen->w/3)/255,2*screen->h/3,1+d/70);

       SDL_Flip( screen ); 
     // if(controll(screen)){
       //     break;
      // }       

        div=d;
        
        if(div>20){
            div=10*(div/10);
        }else if(div>10){
            div=2*(div/2);
        }
        if(fadeBufs[div][back]==NULL){
            fadeBufs[div][back]=(Uint32*)malloc(sizeof(Uint32)*256*256*256);
            if(fadeBufs[div][back]==NULL)
                return -1;        
            for(r=0;r<256;r++){
                if(r%64==0){
                    rgbMixer(screen,filter,10,r*M_PI/128.0);
                    SDL_Flip( screen );
                }
                for(g=0;g<256;g++){
                    for(b=0;b<256;b++){

                        if(r>back+div){
                            rr=r-div;
                        }else if(r<back-div){
                            rr=r+div;
                        }else{
                            rr=back;            
                        }
                        
                        if(g>back+div){
                            gg=g-div;
                        }else if(g<back-div){
                            gg=g+div;
                        }else{
                            gg=back;            
                        }
                        
                        if(b>back+div){
                            bb=b-div;
                        }else if(bb<back-div){
                            bb=b+div;
                        }else{
                            bb=back;            
                        }
                        fadeBufs[div][back][r+g*256+b*256*256]=rr+gg*256+bb*256*256; 
                    
                    }
                }
            }
        
        }
        
    
    }



}


int lastdiv=-1;
int fadeReady=0;
int r0=0;
int pblurtime=0;
int lastpnlur=0;
void orblur(SDL_Surface* source,int div){
    int y,x,pit,d;
    Uint32*q;
    pit=source->pitch/4;
//    pblurtime&=3;
    d=0;
    div=255-div;
    if (div<0)
        div=0;
    if(div>=255)
        return;
    if(pblurtime*4>=div){
        pblurtime-=div/4;
        lastpnlur++;
        if(lastpnlur%4==1)
            d=1;
        else
        if(lastpnlur%4==1)
            d=-1;
        else
        if(lastpnlur%4==2)
            d=pit;
        else
        if(lastpnlur%4==3){
            pblurtime=0;
            d=-pit;
        }
        if(d>0)
            for(y=1,q=(Uint32*)source->pixels    +  y*pit  +1;y<source->h-1;y++,q=(Uint32*)(source->pixels) + y * pit)
               for(x=1;x<source->w-1;x++,q++){
                    *q|=*(q+d);               
               }
        else if(d<0){
            for(y=source->h-2,q=(Uint32*)source->pixels    +  y*pit  + source->w-2;y>0;y--,q=(Uint32*)(source->pixels) + (y) * pit + source->w-2)
                for(x=source->w-2;x>0;x--,q--){
                    *q|=*(q+d);               
                 }
        }
    }else
     pblurtime++;
    
}
int laskBack=-1;
int fade(SDL_Surface* source,int div){
    int x,y;
    int r,g,b,rr,gg,bb;
    Uint32*q;
    Uint8 d;
    int back;
    back=255*getOpt("back");
    if(back<0)
        back=0;
    if(back>255)
        back=255;
    //back=0;
    if(div==255){
        SDL_FillRect(source,NULL, back|back*256|back*256*256);
        return 0;
    
    }
    if(div>60){
        div=10*(div/10);
        
    }else if(div>10){
        div=2*(div/2);
    }
    back=32*(back/32);


    d=div;
    
    if(lastdiv!=div || lastdiv==-1 ||laskBack!=back){
        lastdiv=div;
        laskBack=back;
        if(fadeBufs[div][back]==NULL){
               fadeBuf=lastFadeBuf;                
               fadeReady=0;
               r0=0;
         }else{
            fadeReady=1;
            fadeBuf=fadeBufs[div][back];
         
         }
    }
    
    if(fadeReady==0){
        for(r=r0;r<256&&r<r0+8;r++)
            for(g=0;g<256;g++)
                for(b=0;b<256;b++){
                       if(r>back+div){
                            rr=r-div;
                        }else if(r<back-div){
                            rr=r+div;
                        }else{
                            rr=back;            
                        }
                        
                        if(g>back+div){
                            gg=g-div;
                        }else if(g<back-div){
                            gg=g+div;
                        }else{
                            gg=back;            
                        }
                        
                        if(b>back+div){
                            bb=b-div;
                        }else if(bb<back-div){
                            bb=b+div;
                        }else{
                            bb=back;            
                        }

                  fadeBuf[r+g*256+b*256*256]=rr+gg*256+bb*256*256; 
        }
        r0=r;
        if(r0==256){
            fadeReady=1;
            fadeBufs[div][back]=(Uint32*)malloc(sizeof(Uint32)*256*256*256);
            
            if(fadeBufs[div][back]!=NULL){
                memcpy(fadeBufs[div][back],fadeBuf,sizeof(Uint32)*256*256*256);
            }
        
        
            /*FILE*f;
            char s[128];
            sprintf(s,"cache/fade_%d",div);
            f=fopen(s,"wb");
            if(f!=NULL){
                int l;
                fwrite(fadeBuf,256*256*256*sizeof(Uint32),1,f);
                fclose(f);
            }*/
        }
    }
    if(fadeReady){
        for(y=0,q=(Uint32*)source->pixels;y<source->h;y++,q=(Uint32*)( ((Uint8 *)source->pixels) + y * source->pitch))
            for(x=0;x<source->w;x++,q++){
      //          Uint32 qq;
    //            qq=(((Uint32)*q) & 255*(unsigned int)256*256*256);
        //        if(qq)
                    *q=/*(qq-256*256*256)|*/fadeBuf[(*q)&(255|(255*256)|(255*256*256))];
          //      else{
            //        *q=fadeBuf[(*q)&(255|(255*256)|(255*256*256))];
                    
                
              //  }
            }
    }else{
        oldFade(source,div);
    
        //SDL_FillRect(source,NULL, 0x000000);
    
    }
}

/*
*/

int initFade(SDL_Surface* source){
//    for(int i=0;i<256;i++){
  //      fade(source,i);    
    //}
   for(int i=0;i<256;i++)
   for(int j=0;j<256;j++){
        fadeBufs[i][j]=NULL;
    }
    
    return 0;
}

void closeFades(){
   
   for(int i=0;i<256;i++)
   for(int j=0;j<256;j++){
        if(fadeBufs[i][j]!=NULL)
            free(fadeBufs[i][j]);
    }
    

}




inline char*getScreenPointer(SDL_Surface* source,int x,int y){
    return (char*)( ((Uint8 *)source->pixels) + y * source->pitch + x * source->format->BytesPerPixel);

}


char swapchart;
inline void swapchar(char &a,char &b){
    swapt=a;
    a=b;    
    b=swapt;
}

int moveNoise(SDL_Surface* source,int div,int count){
    int d,c,l,x,y,i;
    int bpp=source->format->BytesPerPixel;
    char *p,*q;
    d=div;
    if(div<=0)
        return 0;
   // p=getScreenPointer(source,div,div);
    for(i=source->h*source->w*count/100;i>=0;i--){
        x=rand()%(source->w-2*div)+div;
        y=rand()%(source->h-2*div)+div;
        p=getScreenPointer(source,x,y);
        c=rand()%3;
        l=(rand()%(2*div+1) - div)*bpp + (rand()%(2*div+1) - div)*source->pitch;
        swapchar(*(p+c),*(p+l+c)); 
    }
    
/*    for(y=div;y<source->h - div ;y++,p=getScreenPointer(source,div,y))
        for(x=div;x<source->w-div;x++,p+=bpp){
          if(rand()%100>count)
            continue;
           c=rand()%3;
           l=rand()%(2*div+1) - div + (rand()%(2*div+1) - div)*source->pitch;
           swapchar(*(p+c),*(p+l+c));              
        }

*/
}

int rgbMixerStep=0;
int rgbMixer(SDL_Surface* source,SDL_Surface* filter,int mul,double alpha){
    int x,y;
    int bpp = source->format->BytesPerPixel;
    int r,g,b,fr,fg,fb,dx,dy;
    SDL_Surface *f,*s,*d;
    int *bu;
    int xshift;
    int yshift;
    
    #define RGBDIV 2
    int xstep=RGBDIV;
    int ystep=RGBDIV;
    xshift=rgbMixerStep&(RGBDIV-1);
    yshift=(rgbMixerStep/RGBDIV)&(RGBDIV-1);
    rgbMixerStep++;
    
  //  printf("mixer start\n");
   // fflush(stdout);
   
    if(mul<=0)
        return 0;
    if(mul>10)
        mul=10;
    if(source->w!=filter->w || source->h!=filter->h){
        if(mixerh!=-1){
           printf("Cant rgbMix, becouse screens are different\n");
           mixerh=-1;           
        }
        return -1;
    }
    if(mixerh!=filter->h || mixerw!=filter->w){

        if(mixerbuf!=NULL){
            free(mixerbuf);        
        }
        
        mixerbuf=(int*)malloc((filter->h+20)*(filter->w+20)*sizeof(int)*4);
        if(mixerbuf==NULL){
             printf("Cant rgbMix, becouse out of memory\n");
            return -2;
        }
        memset(mixerbuf,0,(20+mixerh)*(20+mixerw)*4*sizeof(int));  
        mixerh=filter->h;
        mixerw=filter->w;
       
    }
    //memset(mixerbuf,0,(20+mixerh)*(20+mixerw)*4*sizeof(int));
    
   // bu=mixerbuf+(20+mixerw)*4*sizeof(int));
    calcKs(alpha,filter->w,mul);
   // printf("mixer started\n");
    //fflush(stdout);
    for(y=yshift;y<mixerh;y+=ystep){

        Uint32 *s =(Uint32 *)( (Uint8 *)source->pixels + y * source->pitch);
        Uint32 *f =(Uint32 *)( (Uint8 *)filter->pixels + y * filter->pitch);
        bu=mixerbuf+(((y+10)*(mixerw+20))+10)*4;
        s+=xshift;
        f+=xshift;
        bu+=4*xshift;
        for(x=mixerw-1-xshift;x>0;x-=xstep,bu+=4*xstep,f+=xstep,s+=xstep){
            if(!(*s) || !(*f)){
                continue;
            }
            pixel2rgb(*s,r,g,b);
            pixel2rgb(*f,fr,fg,fb);
            
            *s=0;
            bu[ks0[fr]]+=r;
            bu[ks1[fg]]+=g;
            bu[ks2[fb]]+=b;
            
        }
    }
    //printf("mixer half\n");
    //fflush(stdout);

    for(y=yshift;y<mixerh;y+=ystep){
        
        Uint32 *d =(Uint32*)( (Uint8 *)source->pixels + y * source->pitch);
        bu=mixerbuf+(((y+10)*(mixerw+20))+10)*4;
        d+=xshift;
        bu+=4*xshift;


        for(x=mixerw-1-xshift;x>0;x-=xstep,bu+=xstep*4,d+=xstep){
            if(!(*bu | *(bu+1) | *(bu+2)))
                continue;
            pixel2rgb(*d,r,g,b);
            r+=*bu;
            g+=*(bu+1);
            b+=*(bu+2);
            *bu=0;
            *(bu+1)=0;
            *(bu+2)=0;
      //      *((Uint32*)bu)=0;            
                        
            if(r & (65535-255))
                r=255;           
            if(g& (65535-255))
                g=255;
            if(b& (65535-255))
                b=255;
            rgb2pixel(r,g,b,d);    
        }
    }
 //   printf("mixer finish\n");
   // fflush(stdout);
    return 0;
}
int orrgbMixer(SDL_Surface* source,SDL_Surface* filter,int mul,double alpha){
    int x,y;
    int bpp = source->format->BytesPerPixel;
    int r,g,b,fr,fg,fb,dx,dy;
    SDL_Surface *s,*d;
    int *bu;
    int xshift;
    int yshift;
    
    #define RGBDIV 2
    int xstep=RGBDIV;
    int ystep=RGBDIV;
    xshift=rgbMixerStep&(RGBDIV-1);
    yshift=(rgbMixerStep/RGBDIV)&(RGBDIV-1);
    rgbMixerStep++;
    
  //  printf("mixer start\n");
   // fflush(stdout);
   
    if(mul<=0)
        return 0;
    if(mul>10)
        mul=10;
    if(source->w!=filter->w || source->h!=filter->h){
        if(mixerh!=-1){
           printf("Cant rgbMix, becouse screens are different\n");
           mixerh=-1;           
        }
        return -1;
    }
    bpb=1;
    bpb1=0;
    bpb2=0;

    calcKs(alpha,filter->w,mul);
    Uint32*q,*f;
    int pit;
    pit=source->pitch/4;
    Uint32 c;
    int dd=1;
    for(y=20,q=(Uint32*)source->pixels +  y*pit  +20,f=(Uint32*)filter->pixels    +  y*pit  +20;y<filter->h-20
    ;y++,q=(Uint32*)(source->pixels) + y * pit+20,f=(Uint32*)(filter->pixels) + y * pit+20)
         for(x=20;x<source->w-20;x+=dd,q+=dd,f+=dd){
//                    pixel2rgb(*f,r,g,b);
                  pixel2rgb(*f,fr,fg,fb);
                  c=*q;
                  *q=0;
                  q[ks0[fr]]|=(c)&255;
                  q[ks1[fg]]|=(c)&(255)*256;
                  q[ks2[fb]]|=(c)&(255)*256*256;;
                  dd=1+rand()%3;
               }
        

    return 0;
}




