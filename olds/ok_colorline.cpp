#include"graphutil.cpp"
#ifndef OQCOLORLINEMOD
#define OQCOLORLINEMOD
#define OQS 15
#define COLORLINELEN 256
#define COLORLINEMOD 255
#define mymin(a,b) (((a)>(b))?(b):(a))
int maxoqs=0;
void bar(SDL_Surface*screen,int x1,int y1,int x2,int y2,Uint32 c);
struct colorLine{
    
    double minFreq[OQS];
    double maxFreq[OQS];
    unsigned int seqno3[OQS];
    Uint32 oqColorline[OQS][COLORLINELEN];
    int oqColorlineDx[OQS][COLORLINELEN];
    int oqColorlineDy[OQS][COLORLINELEN];
            
    double oqColorlineWidth[OQS][COLORLINELEN];
    int colorSeq2BufNeedLine[OQS][COLORLINELEN];
    Uint32 orOqColorline[COLORLINELEN];
    unsigned int orseqno3;
    double oqColorlineSat[OQS];
    double oqColorlineVal[OQS];
    int mapOq[OQS][OQS];    
}*cl;
struct colorLine cl3,tcl;

inline Uint32 colorSeq3(int a){
    
    cl->seqno3[a]++;
    cl->seqno3[a]=COLORLINEMOD&(cl->seqno3[a]);
    return cl->oqColorline[a][cl->seqno3[a]];
}
void zeroSeqno3(){
    for(int i=0;i<OQS;i++){
        cl->seqno3[i]=0;
    }
}





void zeroOqColorLine(){
    int i;
    cl=&cl3;  

    for(i=0;i<OQS;i++){
            for(int j=0;j<OQS;j++)
                cl->mapOq[i][j]=0;
             
            cl->oqColorlineSat[i]=0;
            cl->oqColorlineVal[i]=0;

    }
    for(i=0;i<8;i++)
           cl->mapOq[i][i+1]=1;

    cl->mapOq[7][9]=1;
    cl->mapOq[0][0]=1;
    
    cl->oqColorlineSat[0]=0.7;
    cl->oqColorlineSat[1]=0.8;
    cl->oqColorlineSat[2]=0.9;
    cl->oqColorlineSat[3]=1;
    cl->oqColorlineSat[4]=1;
    cl->oqColorlineSat[5]=1;
    cl->oqColorlineSat[6]=1;
    cl->oqColorlineSat[7]=1;
    cl->oqColorlineSat[8]=1;
    cl->oqColorlineSat[9]=1;
    cl->oqColorlineSat[10]=1;


    cl->oqColorlineVal[0]=0.6;
    cl->oqColorlineVal[1]=0.7;
    cl->oqColorlineVal[2]=0.9;
    cl->oqColorlineVal[3]=1;
    cl->oqColorlineVal[4]=1;
    cl->oqColorlineVal[5]=1;
    cl->oqColorlineVal[6]=1;
    cl->oqColorlineVal[7]=1;
    cl->oqColorlineVal[8]=0.9;
    cl->oqColorlineVal[9]=0.6;
    cl->oqColorlineVal[10]=0.5;

}
int Find_Prev_Point(int pix, int TONES){
    return pix*TONES/(COLORLINELEN);
  
  /*  int frfrfr;
    int cur;
    cur = COLORLINELEN / TONES;
    if(pix*2*TONES<COLORLINELEN)
        return TONES-1;
    if(pix*TONES<COLORLINELEN)
        return 0;

    frfrfr = (COLORLINELEN+(pix-COLORLINELEN/(2*TONES)))%COLORLINELEN;//+COLORLINELEN/(2*TONES);
    frfrfr /= cur;
    return frfrfr;*/
}
double Find_Dist_Prev_Point(int pix, int TONES){
  
  return ((pix*TONES)%(COLORLINELEN))/((double) COLORLINELEN);
  /*  int frfrfr;
    int cur;
    if(pix*2*TONES<COLORLINELEN)
        return 1-pix/(((double)COLORLINELEN)/TONES);


    cur = COLORLINELEN / TONES;
    frfrfr = (COLORLINELEN+(pix-COLORLINELEN/(2*TONES)))%COLORLINELEN;//+COLORLINELEN/(2*TONES);
    frfrfr %= cur;
    return frfrfr / (double) cur;
*/
}

int Find_Next_Point(int pix, int TONES){
  /*  int frfrfr;
    if(pix*2*TONES<COLORLINELEN)
        return 0;
    if(pix*TONES<COLORLINELEN)
        return 1;

    frfrfr = (Find_Prev_Point(pix, TONES)+1)%TONES;
    return frfrfr;
*/
    return (Find_Prev_Point(pix,TONES)+1)%TONES;

}




double minValue(double v,double l){
    v-=l;
    v/=(1.-l);
    if(v<0.)
        v=0.;
    if(v>1.)
      v=1.;
   return v;
}
#include"quickspeq.cpp"
#include"hsv.cpp"
void plog(const char*s){
    fprintf(stderr,"%s\n",(char*)s);
    fflush(stderr);


}

void zesizeColorLine(Uint32*d,Uint32*s,int div){
   int i;
    for(i=0;i<COLORLINELEN;i+=div,d++,s+=div){
        *d=*s;
    }


}


void zesizeColorLineDcoords(int*d,int*s,int div){
   int i;
    for(i=0;i<COLORLINELEN;i+=div,d++,s+=div){
        *d=*s;//(*s+*d*3)/4;
    }


}


void zesizeColorLineWidth(double*d,double*s,int div){
   int i;
    for(i=0;i<COLORLINELEN;i+=div,d++,s+=div){
        *d=*s;//(*s+*d*3)/4;
    }


}

int chance(double d){
    return 65536*d>rand()%65536;
}
void calcOrOqColorline(){
//    Uint32 oqColorline[OQS][COLORLINELEN];
  //  Uint32 orOqColorline[COLORLINELEN];
    cl->orseqno3=0;

    for(int j=0;j<COLORLINELEN;j++){
        cl->orOqColorline[j]=0;
        for(int i=0;i<OQS;i++){
            cl->orOqColorline[j]|=cl->oqColorline[i][j];
        }
     }
}

void getQsDisDxy(struct qs &a,int t,int oq,double&dx,double &dy){
    
}
extern double layerOpt[15];
unsigned int oqcp;


double lamp=-100;
int bis[256][32];

//double disMulKoef[13]={}
int mykosd[13]={0,12,7,5,3,4,8,9,6,2,10,1,11};
double disdx[13]={0,0,3,-3,-3,-5,5,5,-5,-10,10,10,-10};
double disdy[13]={0,0,3,3 ,-3,5,5,-5,-5,10,10,-10,10};
void initDisDxDy(double r){
    int i;
    for(i=0;i<13;i++){
        disdx[i]=r*i*cos(i*M_PI/6.5)/13;
        disdy[i]=r*i*sin(i*M_PI/6.5)/13;
    }
    


}


double mykosv[13][2]={{10,10},{7,8},{8,7},{6,8},{5,9},{6,5},{4,6},{6,3.5},{2.5,5.5},{5,1.3},{1.,4.3},{4.1,.9},
{0.1,0.11}};
double nbiko[13]={64/M_PI,32/M_PI,32/M_PI,24/M_PI,22/M_PI,18/M_PI,16/M_PI,9/M_PI,8/M_PI,7/M_PI,6/M_PI,5/M_PI,4/M_PI};
int findDisN(int di){
    di=abs(di);
    for(int i=0;i<DISES;i++){
        if(di==mykosd[i])
            return i;
    }
    return 0;
}


double oldcalcBi(int n,int interval,double amp,double ampAsc){
    double dk;
    dk=pow(554.36/523.25,interval);
    if(interval==0||interval==12)
        return 0;
    //return sin(2*n*M_PI*dk)*amp/10/(mykosv[findDisN(interval)][n%2]);
    return amp*(
    
    
    (n%2)*(sin((n/2)/12./nbiko[findDisN(interval)])/10/(mykosv[findDisN(interval)][n%2])*ampAsc  +  disdy[findDisN(interval)] /3)+
    
    (1-n%2)*(cos( (n/2)/12./nbiko[findDisN(interval)])/10/(mykosv[findDisN(interval)][n%2])*ampAsc+  disdx[findDisN(interval)]/3)
 
    )
 ;}
unsigned int countInterval[64];

int nprepareBi=0;
double lampAsc,lampZero;

void prepareBi(struct qs &a,double amp){
    amp=2*amp;
    int i;
    //
    nprepareBi++;
    for(i=0;i<64;i++)
        countInterval[i]=((int)(nprepareBi*0.2))%128;
    double ampAsc,ampZero;
    
    ampAsc=2.*getOpt("ampAsc");
    ampZero=2.*getOpt("ampZero");
    if(fabs(lamp-amp)>0.0001 || fabs(ampZero-lampZero)>0.000001 || fabs(ampAsc-lampAsc)>0.000001){
        int n,dt,interval;
        lamp=amp;
        lampAsc=ampAsc;
        lampZero=ampZero;

        initDisDxDy(3*amp/50*ampZero);
        for(n=0;n<256;n++){
            for(dt=0;dt<a.tones*2;dt++){
              int interval;
              interval=dt-(a.tones-1);
               bis[n][dt]=1024*oldcalcBi(n,interval,amp,ampAsc);
            }
        }
    }

}
inline int calcBi(int n,int interval){
    return bis[n][interval];
}   
void calcDxDy(struct qs &a,int me,double &dx,double &dy,double myVolume){
                int dt,mt2;
                int fdx,fdy;
                fdx=0;
                fdy=0;
                dx=0;dy=0;
                mt2=me*2*(a.tones);
                for(dt=0;dt<a.tones*2;dt++){
                    int interval;
                        interval=dt-(a.tones-1);
                    if(me+interval>=0&&me+interval<a.oqs*a.tones){
                        int n;
                        n=countInterval[dt]++;
                        countInterval[dt]%=128;
                        fdx+=a.dises[mt2+interval]*calcBi(n*2,dt)*myVolume/1024;
                        fdy+=a.dises[mt2+interval]*calcBi(n*2+1,dt)*myVolume/(1024);
                    }
                }
                dx=fdx/1024.0;
                dy=fdy/1024.0;
                
}

void correctColor(struct hsv_colour &c);
void calcLinDxDy(struct qs &a,int me,double &dx,double &dy,double myVolume){
                int dt,mt2;
                int fdx,fdy;
                fdx=0;
                fdy=0;
                dx=0;dy=0;
                mt2=me*2*(a.tones);
                for(dt=0;dt<a.tones*2;dt++){
                    int interval;
                        interval=dt-(a.tones-1);
                    if(me+interval>=0&&me+interval<a.oqs*a.tones){
                        int n;
                        n=countInterval[dt]++;
                        countInterval[dt]%=128;
                        fdx+=a.linDises[mt2+interval]*calcBi(n*2,dt)*myVolume/1024;
                        fdy+=a.linDises[mt2+interval]*calcBi(n*2+1,dt)*myVolume/(1024);
                    }
                }
                dx=fdx/1024.0;
                dy=fdy/1024.0;
                
}
//#define min(a,b) (((a)>(b))?(b):(a))
//#define CCORLEN 7
extern double colorCorrector[CCORLEN];
double resizeCon(double v){
    return v*v*4;

}
double resizeBri(double v){
    return (v-0.5)*2;
}
double resizeGam(double v){
    return v*v*4;

}

double correct(double v,double b,double c,double g){
    double r;
    b=resizeBri(b);
    c=resizeCon(c);
    g=resizeGam(g);
    
    r=pow((v-0.5)*c +0.5 +b,g);
    if(r>1.)
        return 1.;
    if(r<0.)
        return 0.;
    return r;
}
double oldcolor[CCORLEN];
int  buildCorrectorTable(double*values,double*oldvalues,double*table){
    int rebuild=0;
    int i;
    double a;
    for(i=0;i<3;i++){
        if(fabs(values[i]-oldvalues[i])>0.0001){
            rebuild=1;
        }
    }
    if(rebuild){
    //    fprintf(stderr,"rebuild\n");
        for(i=0;i<3;i++){
            oldvalues[i]=values[i];
            
        }

        for(i=0;i<3000;i++){
            a=(i-1000)/1000.;
            table[i]=correct(a,values[0],values[1],values[2]);
        }
    }
    return rebuild;
}

double lightTable[3000];
double   satTable[3000];

double   tempTable[3000];
double   moodTable[3000];
unsigned int correctorTablesNum=1;
unsigned int rgbTableNum[256][256][256];
struct rgb rgbTable[256][256][256];
inline struct rgb rgbCorrector(struct rgb c){
    //unsigned char o;
    struct rgb r;
    struct hsv_colour hsv_c; 
    struct rgb_colour rgb_c;
  //  struct tmv tmv_c;    

    //o=c.o;
    if(rgbTableNum[c.r][c.g][c.b]==correctorTablesNum){
       r=rgbTable[c.r][c.g][c.b];
      // r.o=o;
       return r;
    }else{
         hsv_c=rgb2hsv(c);
         correctColor(hsv_c);
         hsv2rgb(&hsv_c,&rgb_c);
         r=rgb_colour2rgb(&rgb_c);
         rgbTable[c.r][c.g][c.b]=r;
         rgbTableNum[c.r][c.g][c.b]=correctorTablesNum;
         return r;
    }
}
void buildCorrectorTables(){
    int a;
    a=buildCorrectorTable(colorCorrector,oldcolor,lightTable)
    +buildCorrectorTable(colorCorrector+3,oldcolor+3,satTable)

    +buildCorrectorTable(colorCorrector+7,oldcolor+7,tempTable)
    +buildCorrectorTable(colorCorrector+10,oldcolor+10,moodTable);
    if(a){
       // fprintf(stderr,"Color Corrector Rebuilded\n");
        correctorTablesNum++;
    }
}

extern int correctColorFlag;
//#include"sendrecive.cpp"
//#define COLORSTATLEN 36


#define COLORSTATLEN (16+2+16+2+16+2+16+2)
double colorStat[COLORSTATLEN];
int colorStatInt[COLORSTATLEN];

    //colorStat COLORSTATLEN
    #define max(a,b) (((a)>(b))?(a):(b))
void colorStatInt2Double(){
    int i;
    int s;
    s=0;
    for(i=0;i<18;i++){
        s=max(s,colorStatInt[i]);
    }
    if(s!=0){
        for(i=0;i<18;i++){
            colorStat[i]=colorStatInt[i]/(double)s;
            colorStatInt[i]=0;
        }
    }
    s=0;
    for(i=18;i<36;i++){
        s=max(s,colorStatInt[i]);
    }
    if(s!=0){
        for(i=18;i<36;i++){
            colorStat[i]=colorStatInt[i]/(double)s;
            colorStatInt[i]=0;
        }
    }
    
}
#include"tmv.cpp"
void correctColor(struct hsv_colour &c){
    int v;
    int s;

    //    return;
    v=(c.v+1)*1000.;
    if(v<0)
        v=0;
    if(v>=3000)
        v=2999;
    c.v=lightTable[v];
    if(c.v<0.00000001){
        colorStatInt[0]++;
    }else if(c.v>0.99999999){
        colorStatInt[17]++;
    }else{
        v=c.v*16+1;
        colorStatInt[v]++;
    }
    
    s=(c.s+1)*1000.;
    if(s<0)
        s=0;
    if(s>=3000)
        s=2999;
    c.s=satTable[s];
    if(c.s<0.00000001){
        colorStatInt[18]++;
    }else if(c.s>0.99999999){
        colorStatInt[35]++;
    }else{
        s=c.s*16+1+18;
        colorStatInt[s]++;
    }
    
        
    
    c.h=c.h+colorCorrector[6];
    if(c.h<0.)
        c.h=0.;
    while(c.h>=1.)
        c.h=c.h-1.;

}

void correctColor(struct tmv &c){
    int t;
    int m;

    //    return;
    t=(c.t+1)*1000.;
    if(t<0)
        t=0;
    if(t>=3000)
        t=2999;
    c.t=tempTable[t];
    if(c.t<0.00000001){
        colorStatInt[36+0]++;
    }else if(c.t>0.99999999){
        colorStatInt[36+17]++;
    }else{
        t=c.t*16+1;
        colorStatInt[36+t]++;
    }
    
    m=(c.m+1)*1000.;
    if(m<0)
        m=0;
    if(m>=3000)
        m=2999;
    c.m=moodTable[m];
    if(c.m<0.00000001){
        colorStatInt[36+18]++;
    }else if(c.m>0.99999999){
        colorStatInt[36+35]++;
    }else{
        m=c.m*16+1+18;
        colorStatInt[36+m]++;
    }
    
        
    /*
    c.h=c.h+colorCorrector[6];
    if(c.h<0.)
        c.h=0.;
    while(c.h>=1.)
        c.h=c.h-1.;
*/
}




char CLZerroed[OQS];
char oqPresent[OQS];
int startOqcl=-1;
int finOqcl;

#include"tmv.cpp"
extern int colorSeqVar;
void calcNeedLine(){
    for(int i=0;i<OQS;i++){
        int ldx,ldy;
        ldx=0;
        ldy=0;
        for(int j=0;j<COLORLINELEN;j++){
            int dx,dy;
            dx=cl->oqColorlineDx[i][j];
            dy=cl->oqColorlineDy[i][j];
            if(abs(ldx-dx)+abs(ldy-dy)>2){
                cl->colorSeq2BufNeedLine[i][j]=1;            
            }else{
                cl->colorSeq2BufNeedLine[i][j]=0;
            }
            ldx=dx;
            ldy=dy;
        }
    
    }
    
}

void blurCDXY(){
    int fdx,fdy;
    for(int i=0;i<OQS;i++){
        int ldx,ldy;
        ldx=cl->oqColorlineDx[i][COLORLINELEN-1];
        ldy=cl->oqColorlineDy[i][COLORLINELEN-1];
        
        fdx=cl->oqColorlineDx[i][0];
        fdy=cl->oqColorlineDy[i][0];
        
        for(int j=0;j<COLORLINELEN-1;j++){
            int ndx,ndy;
            ndx=(cl->oqColorlineDx[i][j+1]+ldx)/2;
            ndy=(cl->oqColorlineDy[i][j+1]+ldy)/2;
                      

            ldx=cl->oqColorlineDx[i][j];
            ldy=cl->oqColorlineDy[i][j];
                      
            cl->oqColorlineDx[i][j]=ndx;
            cl->oqColorlineDy[i][j]=ndy;
            
            
            
        }
        cl->oqColorlineDx[i][COLORLINELEN-1]=(ldx+fdx)/2;
        cl->oqColorlineDy[i][COLORLINELEN-1]=(ldy+fdy)/2;
    }
}


inline double calcLW(struct qs &a,int me,double myVolume){
    return 1-a.fade[me];
}


double iCr[13];
double iCg[13];
double iCb[13];
double iv[13];



double i3Cr[13];
double i3Cg[13];
double i3Cb[13];
double i3v[13];
int i3n=13;
double igray;
double iMul=0;
double i3Mul=0;

void prepareICRGB(){
    iMul=getOpt("intervalsMul");
    i3Mul=getOpt("3tonesMul");
    for(int i=0;i<13;i++){
        iv[i]=getOpt("iValue",i)*iMul;
        iCr[i]=getOpt("iRed",i)*iv[i];
        iCg[i]=getOpt("iGreen",i)*iv[i];
        iCb[i]=getOpt("iBlue",i)*iv[i];
        
    }

    for(int i=0;i<13;i++){
        i3v[i]=getOpt("3Value",i)*i3Mul;
    
        i3Cr[i]=getOpt("3Red",i)*i3v[i];
        i3Cg[i]=getOpt("3Green",i)*i3v[i];
        i3Cb[i]=getOpt("3Blue",i)*i3v[i];
        if(fabs(i3Cr[i])+fabs(i3Cb[i])+fabs(i3Cg[i])>0.001&&fabs(i3v[i])>0.001){
            i3n=i+1;
        }
    }
    igray=getOpt("gray");

}

struct rgb calcIColor(double*ik,double*i3k,double v){
    double r,g,b;
    int rr,gg,bb,i;
    struct rgb c;
    r=0;g=0;b=0;
      double d=0;

    if (v>=1.)
        v=1.;
    if(v<0.)
        v=0.;
    for(i=0;i<=12;i++){
//        iStat[i]+=v*ik[i];
        d+=ik[i]*iv[i];
        r=r+iCr[i]*ik[i];
        g=g+iCg[i]*ik[i];
        b=b+iCb[i]*ik[i];
    }
    for(i=0;i<i3n;i++){
        d+=i3k[i]*i3v[i];
        r=r+i3Cr[i]*i3k[i];
        g=g+i3Cg[i]*i3k[i];
        b=b+i3Cb[i]*i3k[i];
    }
    
//    d=sqrt(r*r+g*g+b*b);
    double maxRGB=mmax(r,mmax(g,b))+0.0000001;
    double sat = (maxRGB - mmin(r,mmin(g,b)))/maxRGB;
    
    if(d>0){
        v=v*255*((1-sat)*(1-igray) + sat)/d;
        c.b=v*r;
        c.g=v*g;
        c.r=v*b;       
    }else{
        c.r=0;
        c.g=0;
        c.b=0;
    }
//    if(rr>bb||rr>gg){
  //      fprintf(stderr,"rr >bb gg, %d %d %d\n",rr,gg,bb);
   // }
   /* if(rr>255)
        rr=255;
    if(gg>255)
        gg=255;
    if(bb>255)
        bb=255;*/
    return c;

}

double getMaxLineWidth();
inline double getDLD(struct qs &a,int t,int ok,int dis){

 if(dis==0)
    return 2*a.dlinDises[(t+ok*a.tones)*2*a.tones+11];
 if(dis==12)
    return 2*a.dlinDises[(t+ok*a.tones)*2*a.tones+23];
 
    return a.dlinDises[(t+ok*a.tones)*2*a.tones + 11 - dis] + a.dlinDises[(t+ok*a.tones)*2*a.tones + 11 + dis] ;
 
 
 
 
// +fabs(a.dlinDises[np2D(next)+11-i]))

}
inline double getDLD3(struct qs &a,int t,int ok,int dis){
    return a.dlin3T[(t+ok*a.tones)*13+dis];
}
void calcOqColorline(struct qs &a){
    double v;
    int i,j;
    struct rgb c;
    struct hsv_colour hsv_c; 
    struct rgb_colour rgb_c;
    struct tmv tmv_c;    
    int skeep;
    maxoqs=a.oqs;
   // plog("PrepBi");
   double back,gray;
   back=getOpt("back");
   gray=layerOpt[14]=getOpt("gray");
   int calcLin=getOpt("calcLin");
   double lwZero,lwMax,lopmin,lopmax,lwbmin,lwbmax;
             
   double wm=getMaxLineWidth();
   if(colorSeqVar==9){
       prepareICRGB(); 
   }
   lopmin=getOpt("lopmin");
   lopmax=getOpt("lopmax");
   lwZero=getOpt("lwZero")*wm;
   lwMax=getOpt("lwMax")*wm;
   lwbmin=getOpt("lwbmin");
   lwbmax=getOpt("lwbmax");
/*   fprintf(stderr,"lopmin %f ",lopmin);
   fprintf(stderr,"lopmax %f ",lopmax);
   fprintf(stderr,"lwZero %f ",lwZero);
   fprintf(stderr,"lwMax %f \n",lwMax);*/
   
   if(lwZero<0.000000001){
     lwZero=0.000000001;
      setOpt("lwZero",lwZero/wm);
   }
   if(lwMax<0.000000001){
        lwMax=0.000000001;
        setOpt("lwMax",lwMax/wm);

    }
   
/*    if(lwMax<lwZero){
        lwMax=lwZero;
        setOpt("lwMax",lwMax/wm);

    }*/
    /*
    if(lopmax<lopmin){
        lopmax=lopmin;
        setOpt("lopmax",lopmax);

    }*/
   
    prepareBi(a,layerOpt[12]*screenW/30);
    if(correctColorFlag)
        buildCorrectorTables();
   
    //plog("ok");
    double d,dnx,dny,dpx,dpy,dx,dy;
    dx=0;
    dy=0;
    for(j=0;j<maxoqs;j++){
 //       oqColorline[j]=
        skeep=0;
        int next,prev,ii;
         tcl.minFreq[j]=a.zeroFreq*pow(2,j);
         tcl.maxFreq[j]=a.zeroFreq*pow(2,(j+11./12));

        for(i=0;i<COLORLINELEN;i++,oqcp++){
            ii=(i*(j/2+1));
            if(ii>=COLORLINELEN)
                break;
            prev=Find_Prev_Point(ii,a.tones);
            next=Find_Next_Point(ii,a.tones);
            d=Find_Dist_Prev_Point(ii,a.tones);     

            double q,w,dq,dw,mq,mw,dis;
            q=getQs(&a,next,j);
            w=getQs(&a,prev,j);
            
            //getQsDisDxy(a,next,j,dnx,dny,q*1024);
            //getQsDisDxy(a,prev,j,dpx,dpy,w*1024);
            
            dq=getQsDis(&a,next,j);
            dw=getQsDis(&a,prev,j);
            mq=getQsMm05(&a,next,j);
            mw=getQsMm05(&a,prev,j);

            if(layerOpt[12]>0.001){
                if(calcLin){
                    calcLinDxDy(a,prev,dpx,dpy,q);
                    calcLinDxDy(a,next,dnx,dny,w);
                }else{
                
                    calcDxDy(a,prev,dpx,dpy,q);
                    calcDxDy(a,next,dnx,dny,w);
                
                }
                
                
                dx=dnx*d+dpx*(1-d);
                dy=dny*d+dpy*(1-d);
            }
            double lWidth,dplw,dnlw,lwpercent;
            if(1){
                    dplw=calcLW(a,prev,q);
                    dnlw=calcLW(a,next,w);
                    lwpercent=(dnlw*d+dplw*(1-d));
                
                lWidth=lwZero+(lwMax-lwZero)*lwpercent;
            
            }
            
            
            
//            q=minValue(q,0.3);
  //          w=minValue(w,0.3);
            
            dis=dq*d+dw*(1-d);
            double disl01,disl02;
            double dl1,dl2;
            dl1=layerOpt[13];
            dl2=layerOpt[14];
            
            disl01=(1-dl1+(dl1)*dis);
            disl02=(1-dl2+(dl2)*dis);
            
    //        if(!chance(dis)){
      //          hsv_c.h+=0.5;
        //        if(hsv_c.h>=1.)
          //          hsv_c.h-=1.;
            
            //}
           // if(chance(sqrt(sqrt(sqrt(sqrt(sqrt((1-dis)))))))){
          if(colorSeqVar<8){
                hsv_c.h=ii/(double)COLORLINELEN;
                hsv_c.s=disl01*cl->oqColorlineSat[j];
                hsv_c.v=disl02*(q*d+w*(1-d))*cl->oqColorlineVal[j];
           
           }else if(colorSeqVar==9){
//                prepareICRGB
                double ikoefs[13];
                double i3koefs[13];
                
                for(int i=0;i<=12;i++){
                    ikoefs[i]=getDLD(a,next,j,i)*d+getDLD(a,next,j,i)*(1-d);
                    i3koefs[i]=getDLD3(a,next,j,i)*d+getDLD3(a,next,j,i)*(1-d);
                    
                    
//                    (fabs(a.dlinDises[np2D(next)+i+11])+fabs(a.dlinDises[np2D(next)+11-i]))*d+(fabs(a.dlinDises[np2D(prev)+i+11])+fabs(a.dlinDises[np2D(prev)+11-i]))*(1.-d);
                }
                c=calcIColor(ikoefs,i3koefs,(q*d+w*(1-d)));
               // c.o=0;
           }else{
                tmv_c.t=dis;
                tmv_c.m=mq*d+mw*(1-d);
                tmv_c.v=(q*d+w*(1-d))*(lwbmin+(lwbmax-lwbmin)*lwpercent);
                if(correctColorFlag)
                    correctColor(tmv_c);
                hsv_c=tmv2hsv(tmv_c,gray,back);

           }
           // }else{
               // hsv_c.s=cl->oqColorlineSat[j];
             //   hsv_c.v=(q*d+w*(1-d))*cl->oqColorlineVal[j];
           // }
            
           double cdis;
           /*
           if(layerOpt[12]>0.0001){
               cdis=(dis)/(layerOpt[12]);
           
                if(cdis<1.){
                   dx=(rand()%31-15)*(1-cdis)*layerOpt[13];
                   dy=(rand()%31-15)*(1-cdis)*layerOpt[13];
                }
                
            }*/
            if(colorSeqVar!=9){
                //    fprintf(stderr,"CORRECTION\n");
                    if(correctColorFlag)
                        correctColor(hsv_c);
           
                    hsv2rgb(&hsv_c,&rgb_c);
                    c=rgb_colour2rgb(&rgb_c);
                 // c=r_rgb_colour2rgb(&rgb_c);
          
            }else{
                  if(correctColorFlag){
                        c=rgbCorrector(c);

                    }
                 // c=r_rgb_colour2rgb(&rgb_c);
            //c.o=(lopmin+(lwpercent)*(lopmax-lopmin));

            
            }
            c.o=(lopmin+(lwpercent)*(lopmax-lopmin));
            
          //  if(chance(sqrt(sqrt(sqrt(sqrt(sqrt((1-dis)))))))){
            //    skeep=3;
          //  }
            
//            if(skeep==0){
               tcl.oqColorline[j][i]=*((Uint32*)(&c));
               tcl.oqColorlineDx[j][i]=dx;
               tcl.oqColorlineDy[j][i]=dy;
               tcl.oqColorlineWidth[j][i]=lWidth;

  //         } else{
    //            skeep--;
      //          tcl.oqColorline[j][i]=rand()%(256*256)+(rand()%256)*256*256;                
        //    }
        }
        int empty;
        int l0;
        l0=ii;
        empty=COLORLINELEN-i;
        while(i<COLORLINELEN){
            memcpy(tcl.oqColorline[j]+i,tcl.oqColorline[j],mymin(l0,empty)*sizeof(Uint32));
            memcpy(tcl.oqColorlineDx[j]+i,tcl.oqColorlineDx[j],mymin(l0,empty)*sizeof(int));
            memcpy(tcl.oqColorlineDy[j]+i,tcl.oqColorlineDy[j],mymin(l0,empty)*sizeof(int));
            
            
            memcpy(tcl.oqColorlineWidth[j]+i,tcl.oqColorlineWidth[j],mymin(l0,empty)*sizeof(double));
            
            
            i+=l0;
            empty-=l0;
        }
    }
    int resizedoqs=0;
    int oqpresent;
    int oqInFraq[OQS];
    startOqcl=-1;
    //finOqcl;
    
    for(i=0;i<OQS;i++){
        oqpresent=0;
        oqInFraq[i]=0;
            for(j=0;j<OQS;j++){
                if(cl->mapOq[i][j]){
                    oqpresent=1;
                    oqInFraq[i]++;
                }
            }
            if(oqpresent){
              if(startOqcl<0)
                startOqcl=i;
              oqPresent[i]=1;
              finOqcl=i;
              resizedoqs++;
            }else{
              oqPresent[i]=0;
            
            }
    }
    maxoqs=finOqcl-startOqcl+1;
    int oqcount;
    for(i=0;i<OQS;i++){
            oqcount=0;
        //    oqPresent[i]=0;
            if(!CLZerroed[i]){
                memset(cl->oqColorline[i],0,COLORLINELEN*sizeof(Uint32));
                CLZerroed[i]=1;
            }
            char flag;
            flag=0;
            for(j=0;j<OQS;j++){
                if(cl->mapOq[i][j]){
                    //oqPresent[i]=1;
                    if(!flag){
                        cl->minFreq[i]=tcl.minFreq[j];
                    }
                    cl->maxFreq[i]=tcl.maxFreq[j];

                    flag=1;
                    CLZerroed[i]=0;
                    zesizeColorLine(cl->oqColorline[i] + oqcount*COLORLINELEN/oqInFraq[i],tcl.oqColorline[j],oqInFraq[i]);
                    zesizeColorLineDcoords(cl->oqColorlineDx[i] + oqcount*COLORLINELEN/oqInFraq[i],tcl.oqColorlineDx[j],oqInFraq[i]);
                    zesizeColorLineDcoords(cl->oqColorlineDy[i] + oqcount*COLORLINELEN/oqInFraq[i],tcl.oqColorlineDy[j],oqInFraq[i]);

                    zesizeColorLineWidth(cl->oqColorlineWidth[i] + oqcount*COLORLINELEN/oqInFraq[i],tcl.oqColorlineWidth[j],oqInFraq[i]);

                    oqcount++;
                }
            }
    
    }   
    for(int k=0;k<5;k++)
        blurCDXY(); 
    calcNeedLine();
    calcOrOqColorline();
    colorStatInt2Double();
}    
void prepareSeqNo2(int deep);
inline void orDrawColoredLineSeq2(SDL_Surface *sc,int x1, int y1, int x2, int y2);
void drawOqColorLines(SDL_Surface*screen,int x1,int y1,int x2,int y2){
    int w,h,i,n,a;
    w=x2-x1;
    h=y2-y1;
    n=0;a=0;
   for(i=0;i<OQS;i++){
    if(oqPresent[i])
        n++;
   }
   if(n)
    for(i=0;i<OQS;i++){
        if(oqPresent[i]){
            prepareSeqNo2(i);
            orDrawColoredLineSeq2(screen,(a+1)*w/(n+2) +w/(n+2)/2,(y1+y2)/2-128,(a+1)*w/(n+2) +w/(n+2)/2,(y1+y2)/2+127);    
            a++;
        }
    }

}
void _drawOqColorLines(SDL_Surface*screen,int x1,int y1,int x2,int y2){
    int i,j,w,h;
    w=abs(x2-x1);
    h=abs(y2-y1);
    if(x2<x1)
        x1=x2;  
    if(y2<y1)
        y1=y2;  
    
    int ii=0;;
    for(i=0;i<OQS;i++){
        if(oqPresent[i]){
            for(j=0;j<COLORLINELEN;j++){           
                bar(screen,x1+j*w/COLORLINELEN,y1+(maxoqs-ii-1)*h/(maxoqs+1),x1+(j+1)*w/COLORLINELEN-1,y1+((maxoqs-ii))*h/(maxoqs+1),cl->oqColorline[ii][j]);    
            }
            ii++;
        }
    }
    for(j=0;j<COLORLINELEN;j++){           
            bar(screen,x1+j*w/COLORLINELEN,y1+i*h/(maxoqs+1),x1+(j+1)*w/COLORLINELEN-1,y1+(i+1)*h/(maxoqs+1),cl->orOqColorline[j]);    
        
        }
    

}
void drawOqColorLines(SDL_Surface*screen){
    drawOqColorLines(screen,0,0,screen->w-1,screen->h-1);
}
#endif
