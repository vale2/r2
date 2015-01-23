#include<math.h>
#ifndef KOEFSMOD
#define KOEFSMOD
#define dEqEps 1e-10
#define dEq(a,b) ((fabs((a)-(b))<dEqEps)?1:0)


#define OCVCAMS 3
#define OCVPLYLISTS 6
#define KOEFNUM 11
#define DRAWKOEFNUM 18
double soundKoefs[KOEFNUM];
double drawKoef[DRAWKOEFNUM];
double ascellValue[DRAWKOEFNUM];
double lascellValue[DRAWKOEFNUM];
double drawLatKoef[DRAWKOEFNUM];





#include"timeutil.cpp"
#define HISLEN 1000
double hisKoef[HISLEN][KOEFNUM];

Uint32 hisKoefTime[HISLEN][KOEFNUM];
Uint32 hisCur[KOEFNUM];


void archKoef(double v,int n){
    hisKoef[hisCur[n]][n]=v;
    hisKoefTime[hisCur[n]][n]=GetTickCount();
    hisCur[n]++;
    hisCur[n]=hisCur[n]%HISLEN;

}
//PIF:
//pifDeep,pifNaked,pifColored,
//pifDWind,pifDScale,pifDAngle,
//empty(r),CircleSeqSym,CircleSeqN,
//,pifRepeat,pifParity,starValue,
//starAngle,starN,rScale,
//minDeep, SpirafTransform, MegaTransform
double accspeed[KOEFNUM]={1000,1000,1000,1000,1000,1000,1000,1000,1000,1000};

double maxDrawKoef[DRAWKOEFNUM]={10,3.001,1.001,100,10,7000,1000000,1,1,60.01,1.01,1.01,1000000,180,1,1};


double minDrawKoef[DRAWKOEFNUM]={2,0,0,-100,-1000,-7000,0.0000001,0.00,0.00,1,0,0,-1000000,3,0,0};


double controllKoef[DRAWKOEFNUM*KOEFNUM];
double zeros[DRAWKOEFNUM];
double dkoef[DRAWKOEFNUM];
double dkoefacc[DRAWKOEFNUM];
double dkoefaccperiod[DRAWKOEFNUM];
double koefascell[DRAWKOEFNUM];
double koefascellacc[DRAWKOEFNUM];
double koefascellamp[DRAWKOEFNUM];


double dkh[DRAWKOEFNUM];
void  drawKoefLatency(double *kf,double *lat){
    for(int i=0;i<DRAWKOEFNUM;i++){
        double a;
        a=lat[i];
        if(a<0.)
            a=0.;
        if(a>1.)
            a=1.;
        kf[i]=dkh[i]=dkh[i]*a+kf[i]*(1-a);
        
    }



}
#include"glopts.cpp"
extern int mode;
int setOpt(const char*name,double value);

void setZeroPifControllKoef(){
    int i,j;
    double *ck;
    ck=controllKoef;
//    printf("ZEROPIFSOUND!\n");
   mode=5;    
    
for(i=0;i<KOEFNUM;i++){
    accspeed[i]=1000;
zeroGlOpt();
}
setOpt("intervalRotSpeed",0.1);
double zeromaxDrawKoef[DRAWKOEFNUM]={10,3.001,1.001,100,10,7000,10000000,1000000,1 ,60.01,1.01,1.01,1000000,180,1,1,1,1};
double zerominDrawKoef[DRAWKOEFNUM]={2,0,0,-100,-1000,-7000,10000000.0,0.0000001,0.0000000,1,0,0,-1000000,3,0,0,0,0};
for(i=0;i<DRAWKOEFNUM;i++){
    maxDrawKoef[i]=zeromaxDrawKoef[i];
    minDrawKoef[i]=zerominDrawKoef[i];
    drawLatKoef[i]=0;
}    

    
    
    for(i=0;i<DRAWKOEFNUM;i++){
        dkoefacc[i]=0;
        zeros[i]=0;
        dkoef[i]=0;
        dkoefaccperiod[i]=10000000.;
        koefascell[i]=0;
        koefascellacc[i]=0;
        koefascellamp[i]=0;
        for(j=0;j<KOEFNUM;j++){
            ck[i*KOEFNUM+j]=0;
        
        }
    }
    
    //pifDeep
    ck[0*KOEFNUM+1]=7;
    ck[0*KOEFNUM+0]=7;
    ck[0*KOEFNUM+4]=11;
    //minDeep
//    ck[15*KOEFNUM+1]=7;
    ck[15*KOEFNUM+1]=7;
    maxDrawKoef[15]=10;
    minDrawKoef[15]=0;    
  //  ck[15*KOEFNUM+4]=11;
    
    
    
    
    //pifangle
    dkoef[5]=M_PI/10000;
    
    
    
    //pscale
    ck[4*KOEFNUM+6]=0.1;
    koefascell[4]=0.001;
    koefascellamp[4]=1/10.;
    //pwind
    ck[3*KOEFNUM+5]=0.1;
    koefascell[3]=1.0/100000000.;
    koefascellamp[3]=M_PI; 

    //starValue
    ck[11*KOEFNUM+4]=0.65;
    ck[11*KOEFNUM+2]=0.4;

    ck[11*KOEFNUM+1]=0.4;
    //starN
    zeros[13]=3;
    //starAngle
    ck[12*KOEFNUM+6]=1.;
    ck[12*KOEFNUM+5]=1.;
    
    
 //   koef[14]
   
    ck[14*KOEFNUM+0]=-1.;
  //  ck[14*KOEFNUM+2]=1.;
   
    zeros[14]=1.;
    minDrawKoef[14]=0;
    maxDrawKoef[14]=1;
    

//CircleSeq
    zeros[8]=0.;
    minDrawKoef[8]=0;
    maxDrawKoef[8]=1;

    
//    pifDeep=7.*melodyrithm*pifDeepRithm);
  //  if(pifDeep>7)
    //    pifDeep=7;
    //pifDeep=bassrithm*pifDeepBass;
    //if(pifDeep>7)
    //    pifDeep=7;
    
//    pifDeep=pifDeep+ cur*pifDeepCur;
  //  if(pifDeep>11)
    //    pifDeep=11;
    //if(pifDeep<2)
      //  pifDeep=2;

  //  if(ALLFRAQ){
  //      pifDeep=11;
    
  //  }
    //ds=bassrithm/10;
   // if(ds>maxds)
    //    maxds=ds;
   // sound_rx=rx*rxMax;
    //sound_ry=;

}
#endif
