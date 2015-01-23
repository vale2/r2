#include"interfer.cpp"
char header[54];


struct layer*bmp2layer(const char*s){
    FILE*f;
    int i,x,y;
    unsigned short int *bpp;
    unsigned int *h,*w,*shift;
    unsigned char buf[3];
    unsigned int q;
    struct layer*r;
    f=fopen(s,"rb");
    if(f==NULL)
        return NULL;
    fread(header,54,1,f);
    shift=(unsigned int*)(header+10);
    w=(unsigned int*)(header+18);
    h=(unsigned int*)(header+22);
    bpp=(unsigned short int*)(header+28);
    r=makeLayer(*w,*h);
    if(header[0]!='B'||header[1]!='M'||*bpp!=24||r==NULL){
        fclose(f);
        return NULL;
    }
    for(i=0;i<*shift-54;i++){
        fread(buf,1,1,f);    
    }
    
    for(y=*h-1;y>=0;y--){
        for(x=0;x<*w;x++){
            fread(buf,3,1,f); 
            q=buf[0];
            q+=buf[1];
            q+=buf[2];
            q=q/3;
            r->p[x+y*(*w)]=q;
        }   
       for(;x%4!=0;x++)
            fread(buf,3,1,f); 
     
    }
    fclose(f);
    return r;   

}

void mySaveBMP(SDL_Surface* bitmap,char*name){
    FILE*f;
    char *buf;
    int x,y;
    f=fopen(name,"w");
    if(f==NULL)
        return;
    *((unsigned int*)(header+10))=54;
    *((unsigned int*)(header+18))=bitmap->w;
    *((unsigned int*)(header+22))=bitmap->h;
    *((unsigned short int*)(header+28))=24;
    header[0]='B';
    header[1]='M';
    fwrite(header,1,54,f);
    buf=(char*)bitmap->pixels;
    for(y=bitmap->h-1;y>=0;y--){
        for(x=0;x<bitmap->w;x++){
                fwrite(buf+x*3+y*bitmap->pitch,3,1,f);               
            }
        for(;x%4!=0;x++)
            fwrite(buf,3,1,f); 
 
    }  
    fclose(f);   
}

void mySaveBMP(char* bitmap,int w,int h,char*name){
    FILE*f;
    char *buf;
    int x,y;
    f=fopen(name,"w");
    if(f==NULL)
        return;
    *((unsigned int*)(header+0xa))=54;
    *((unsigned short int*)(header+0x12))=w;
    *((unsigned short int*)(header+0x14))=h;
    *((unsigned short int*)(header+0x18))=24;
 
    *((unsigned  int*)(header+2))=54+w*h*3;
    *((unsigned  int*)(header+6))=0;

    *((unsigned int*)(header+0xe))=12;
    *((unsigned short int*)(header+0x16))=1;


 
    header[0]='B';
    header[1]='M';
    fwrite(header,1,54,f);
    buf=(char*)bitmap;
    char zero=0;
    for(y=h-1;y>=0;y--){
        for(x=0;x<w;x++){
                fwrite(buf+x*4+y*w*4,3,1,f);               
            }
        x*=3;
        
        for(;x%4!=0;x++)
            fwrite(&zero,1,1,f); 
 
    }  
    fclose(f);   
}