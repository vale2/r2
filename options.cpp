#ifdef IPSEND
/*    int setOpt(const char*name,unsigned int n,double value);
    int setOpt(const char*name,double value);
    double getOpt(struct adr a);
    double getOpt(const char*name);
*/
#include<stdio.h>

    #define printf netprintf
    #define fprintf netfprintf
    #include"mynet.cpp"

#else
#include<stdio.h>

#endif
#ifndef M_OPTIONS
#define M_OPTIONS


#include<string.h>
#include<stdlib.h>
//#include<stdio.h>
#include<math.h>
struct adr{
    int n,id;
};


char**optNames;
int optIds=0;
int optIdsBuf=0;
double**optValues;
double**loptValues;
int *optLens;
int reallocOptTable(){
    int newSize=0;
    char**n_optNames;
    double**n_optValues;
    double**n_loptValues;
    int *n_optLens;
    int i;
    if(optIdsBuf>100&&optIds<optIdsBuf/2){
        return 0;
    }

    if(optIdsBuf==0){
        newSize=128;
    }else{
        newSize=optIdsBuf*2;
    }
    n_optNames=(char**)malloc(newSize*(sizeof(char**)));
    if(n_optNames==NULL)
        return -1;
    n_optValues=(double**)malloc(newSize*(sizeof(double**)));
    if(n_optValues==NULL){
        free(n_optNames);
        return -1;
    }
    n_loptValues=(double**)malloc(newSize*(sizeof(double**)));
    if(n_loptValues==NULL){
        free(n_optNames);
        free(n_optValues);
        return -1;
    }
    n_optLens=(int*)malloc(newSize*(sizeof(int*)));
    if(n_optLens==NULL){
        free(n_optNames);
        free(n_optValues);
        free(n_loptValues);
        return -1;
    }
    for(i=0;i<optIds;i++){
        n_optNames[i]=optNames[i];
        n_optValues[i]=optValues[i];
        n_loptValues[i]=loptValues[i];
        n_optLens[i]=optLens[i];
        
    }
    for(;i<newSize;i++){
        n_optNames[i]=NULL;
        n_optValues[i]=NULL;
        n_loptValues[i]=NULL;
        n_optLens[i]=0;
        
    }
    if(optIdsBuf>0){
        free(optNames);
        free(optValues);
        free(loptValues);
        free(optLens);
    }
    optNames=n_optNames;
    optValues=n_optValues;
    loptValues=n_loptValues;
    optLens=n_optLens;
    optIdsBuf=newSize;
    return 0;
}



int getOptId(const char*name){
    char**p;
    int i;
    p=optNames;
    for(i=0;i<optIds;i++){
        if(!strcmp(name,p[i]))
            return i;
    }
    return -1;
}

struct adr getOptAdress(const char*name,unsigned int n){
    int id;
    struct adr r;
    r.id=-1;
    r.n=-1;
    
    id=getOptId(name);
    if(id<0)
        return r;
    if(n>=optLens[id])
        return r;
    r.id=id;
    r.n=n;
    return r;
}



struct adr getOptAdress(const char*name){
    return getOptAdress(name,0);
}



double getOpt(const char*name,unsigned int n){
    int id;
    id=getOptId(name);
    if(id<0)
        return 0.;
    if(n>=optLens[id])
        return 0.;
    return optValues[id][n];
}

double getOpt(const char*name){
    return getOpt(name,0);
}
#include"koefs.cpp"
extern double koefsAr16[KOEFNUM][16];

double getOptValue(const char*name){
    double r;
    int i;
    r=getOpt(name);
    for(i=0;i<KOEFNUM;i++){
        r+=getOpt(name,i+2)*soundKoefs[i];
    }
    return r;
}
void opts2koefsAr16(){
    int i,j;
    char s[128];
    for(i=0;i<1;i++){
        sprintf(s,"KoefAr16_%d",i);
        for(j=0;j<16;j++){
                koefsAr16[i][j]=getOpt(s,j);
        }
    }


}
double getOptValue(const char*name,int chanel){
    double r;
    int i;
    r=getOpt(name);
    for(i=0;i<KOEFNUM;i++){
        r+=getOpt(name,i+2)*soundKoefs[i];
    }
    if(chanel>=0&&chanel<16)
    for(i=0;i<KOEFNUM;i++){
        r+=getOpt(name,i+2+KOEFNUM)*koefsAr16[i][chanel];
    }

    return r;
}
double calcOpt(const char*name){
    double r;
    int i;
    r=getOpt(name);
    for(i=0;i<KOEFNUM;i++){
        r+=getOpt(name,i+2)*soundKoefs[i];
    }

    return r;
}
double calcOpt(const char*name,int chanel){
    double r;
    int i;
    r=getOpt(name);
    for(i=0;i<KOEFNUM;i++){
        r+=getOpt(name,i+2)*soundKoefs[i];
    }
    for(i=0;i<KOEFNUM;i++){
        r+=getOpt(name,i+2+KOEFNUM)*koefsAr16[i][chanel];
    }

    return r;
}

int correctOpt(struct adr a){
    if(a.id<0 || a.id>=optIds)
        return 0;
    if(a.n>=optLens[a.id])
        return 0;
    return 1;
}

double getOpt(struct adr a){
//    int id;
  //  int n;
    //id=adr.id;
   // n=
    if(a.id<0 || a.id>=optIds)
        return 0.;
    if(a.n>=optLens[a.id])
        return 0.;
    return optValues[a.id][a.n];
}

int createOptId(const char*name){
    if(optIds>=optIdsBuf){
        if(reallocOptTable()){
            return -1;
        }
        if(optIds>=optIdsBuf)
            return -1;
    }
    optNames[optIds]=(char*)malloc(strlen(name)+1);
    if(optNames[optIds]==NULL)
        return -1;
    strcpy(optNames[optIds],name);
    optLens[optIds]=0;
    optValues[optIds]=NULL;
    loptValues[optIds]=NULL;
    optIds++;
    return optIds-1;    
}

int reallocOptValues(int id,int newSize){
    double*n_optValues;
    double*n_loptValues;
    int i;
    n_optValues=(double*)malloc(newSize*sizeof(double));
    if(n_optValues==NULL)
        return -1;
    n_loptValues=(double*)malloc(newSize*sizeof(double));
    if(n_loptValues==NULL){
        free(n_optValues);
        return -1;
    }
    for(i=0;i<optLens[id];i++){
        n_optValues[i]=optValues[id][i];
        n_loptValues[i]=loptValues[id][i];
    
    }
    for(;i<newSize;i++){
        n_optValues[i]=0.;
        n_loptValues[i]=0.;
    
    }

    optLens[id]=newSize;
    if(optLens[id]!=0){
        free(optValues[id]);    
        free(loptValues[id]);    
  
    }
    optValues[id]=n_optValues;
    loptValues[id]=n_loptValues;
    return 0;
}
int setOptFromClient(const char*name,unsigned int n,double value){
    int id;
    id=getOptId(name);
    if(id<0){
        id=createOptId(name);
        if(id<0){
            return -1;
        }
    }
    if(n>=optLens[id]){
        if(reallocOptValues(id,2*n+1) ){
            return -1;
        }
        if(n>=optLens[id])
            return -1;
    }
    optValues[id][n]=value;
    loptValues[id][n]=value;
    return 0;
}

int setOpt(const char*name,unsigned int n,double value){
    int id;
    id=getOptId(name);
    if(id<0){
        id=createOptId(name);
        if(id<0){
            return -1;
        }
    }
    if(n>=optLens[id]){
        if(reallocOptValues(id,2*n+1) ){
            return -1;
        }
        if(n>=optLens[id])
            return -1;
    }
    optValues[id][n]=value;
    return 0;
}
int setLOpt(const char*name,unsigned int n,double value){
    int id;
    id=getOptId(name);
    if(id<0){
        id=createOptId(name);
        if(id<0){
            return -1;
        }
    }
    if(n>=optLens[id]){
        if(reallocOptValues(id,2*n+1) ){
            return -1;
        }
        if(n>=optLens[id])
            return -1;
    }
    loptValues[id][n]=value;
    return 0;
}


int setOpt(const char*name,double value){
   return setOpt(name,0,value);
}
int setOpt(struct adr a,double value){
   if(a.id<0 || a.id>=optIds)
        return -1;
    if(a.n>=optLens[a.id])
        return -1;
    optValues[a.id][a.n]=value;
    return 0;
}

int lastSend=-1;
#define CRITSEND 100
void writeOpts(FILE*f,int writeAll,int notWriteZeros){
    int i,j;
    int sended=0;
    i=0;
    if(lastSend>=-1){
        i=lastSend+1;
    }
    for(;i<optIds;i++){
        for(j=0;j<optLens[i];j++){
            if(writeAll||fabs(loptValues[i][j]-optValues[i][j])>0.0000000000001){
                if(!notWriteZeros||fabs(optValues[i][j])>0.0000000001){
                    fprintf(f,"setOpt %s %d %f\n",optNames[i],j,optValues[i][j]);
//                    fprintf(stderr,"sdterr:setOpt %s %d %f\n",optNames[i],j,optValues[i][j]);
                  
                   // loptValues[i][j]=optValues[i][j];
                    sended++;
                }
            }
        }
        if(sended>CRITSEND){
          //  lastSend=i;
           // return;
        }

    }
    lastSend=-1;

}
void writeOpts(FILE*f,int writeAll){
    writeOpts(f,writeAll,0);
}



void zeroCalcOpt(const char*name,double a){
    int i;
    setOpt(name,a);
    setOpt(name,1,0);
    for(i=0;i<KOEFNUM;i++){
        setOpt(name,i+2,0);
    }


}
void zeroCalcOpt(const char*s){
    zeroCalcOpt(s,0);
}
const char* multiTh(int th,const char*s,char *rBuf);
int findDisN(int di);
void zeroSpiral(){
double _mykosv[13][2]={{10,10},{7,8},{8,7},{6,8},{5,9},{6,5},{4,6},{6,3.5},{2.5,5.5},{5,1.3},{1.,4.3},{4.1,.9},{0.1,0.11}};
double _nbiko[13]={64/M_PI,32/M_PI,32/M_PI,24/M_PI,22/M_PI,18/M_PI,16/M_PI,9/M_PI,8/M_PI,7/M_PI,6/M_PI,5/M_PI,4/M_PI};
   for(int i=0;i<13;i++){
        double a1,a2,t;
        int n;
//        sprintf(s,)
        n=findDisN(i);
     
        a1=_mykosv[n][0]/10.;
        a2=_mykosv[n][1]/10.;
        t=_nbiko[n]*M_PI/64.;
        setOpt("iSpiralA1",i,a1);
        setOpt("iSpiralA2",i,a2);
        setOpt("iSpiralT",i,t);
  }



}
void zeroSoundKoefsColor();



void zerospiralDisRenumber(){
    int i;
    int spiralDisRenumber[13]={0,12,7,5,3,4,8,9,6,2,10,1,11};
    double spiralDisKoef[13]={1,1,1,1,1,1,0.7,0.7,0.6,0.6,0.6,0.6,0.6};
    for(i=0;i<13;i++){
        setOpt("spiralDisRenumber",i,spiralDisRenumber[i]);
        setOpt("spiralDisKoef",i,spiralDisKoef[i]);
    }

}


void zeroSoundKoefsTypes(){
    
    setOpt("freqKoefStart",0,0);
    setOpt("freqKoefFin",0,0.1);
    setOpt("typeKoef",0,0);//EQ
    
    setOpt("freqKoefStart",1,0.1);
    setOpt("freqKoefFin",1,0.6);
    setOpt("typeKoef",1,0);//EQ
    
    setOpt("freqKoefStart",2,0.6);
    setOpt("freqKoefFin",2,1);
    setOpt("typeKoef",2,0); ///EQ
    
    setOpt("freqKoefStart",3,0);
    setOpt("freqKoefFin",3,1);
    setOpt("typeKoef",3,1); ///FADES

    setOpt("freqKoefStart",4,0);
    setOpt("freqKoefFin",4,1);
    setOpt("typeKoef",4,2); ///ULTRAHIGH


    setOpt("freqKoefStart",5,0);
    setOpt("freqKoefFin",5,1);
    setOpt("typeKoef",5,3); ///RITHM
    setOpt("koefRithmChose",5,0); ///RITHM

    setOpt("freqKoefStart",6,0);
    setOpt("freqKoefFin",6,1);
    setOpt("typeKoef",6,3); ///RITHM
    setOpt("koefRithmChose",6,0); ///RITHM

    setOpt("freqKoefStart",7,0);
    setOpt("freqKoefFin",7,1);
    setOpt("typeKoef",7,3); ///RITHM
    setOpt("koefRithmChose",7,0); ///RITHM

    setOpt("freqKoefStart",8,0);
    setOpt("freqKoefFin",8,1);
    setOpt("typeKoef",8,4); ///DISES

    setOpt("freqKoefStart",9,0);
    setOpt("freqKoefFin",9,1);
    setOpt("typeKoef",9,5); ///MM
    
    setOpt("freqKoefStart",10,0);
    setOpt("freqKoefFin",10,1);
    setOpt("typeKoef",10,6); ///LIGHTBACK


}
extern    double lspeedSpeqUp;
extern    double lspeedSpeqDown;
extern    double lspeedSizeUp;
extern    double lspeedSizeDown;
extern    double lspeedFadeUp;
extern    double lspeedFadeDown;

void zeroSnsSpeedsMass(){
 lspeedSpeqUp=-100;
 lspeedSpeqDown=-100;
 lspeedSizeUp=-100;
 lspeedSizeDown=-100;
 lspeedFadeUp=-100;
 lspeedFadeDown=-100;

}
void zeroOpts(){
    zeroSnsSpeedsMass();
    zeroSpiral();
    zerospiralDisRenumber();
    zeroSoundKoefsColor();
    zeroSoundKoefsTypes();
    setOpt("quickSpeqAmpGamma",1);
    setOpt("soundSpeq_lowFreqBri",1);
    setOpt("soundSpeq_highFreqBri",1);
    
    setOpt("recSplitTime",300);
    setOpt("recVideo",0);
    setOpt("intervalsMul",0);
    setOpt("3tonesMul",0);
        setOpt("iValue",0.1);
        setOpt("iRed",0.5);
        setOpt("iGreen",0.5);
        setOpt("iBlue",0.5);

    for(int i=1;i<13;i++){
        setOpt("iValue",i,0);
        setOpt("iRed",i,0);
        setOpt("iGreen",i,0);
        setOpt("iBlue",i,0);
        setOpt("3Value",i,0);
        setOpt("3Red",i,0);
        setOpt("3Green",i,0);
        setOpt("3Blue",i,0);
        
    }
    
    
    
    setOptFromClient("gray",0,0.5);
    setOpt("speedSpeqUp",0,0.);
    setOpt("speedSpeqDown",0,0.);
    setOpt("speedSizeUp",0,0.);
    setOpt("speedSizeDown",0,0.8);    
    setOpt("ampAsc",0.5);
    setOpt("ampZero",0.5);
    setOpt("lopmin",0);
    setOpt("lopmax",0);
    setOpt("lwZero",0);
    setOpt("lwMax",0);
    setOpt("lwbmin",1);
    setOpt("lwbmax",1);        
    setOpt("intervalComparePow",1);
    
    setOpt("speedKoefUp",3,0.9);
    setOpt("speedkoefDown",3,0.9);
    setOpt("correctorKoef",3,1);

    setOpt("speedKoefUp",8,0.9);
    setOpt("speedkoefDown",8,0.9);
    setOpt("correctorKoef",8,1);

    setOpt("speedKoefUp",9,0.9);
    setOpt("speedkoefDown",9,0.9);
    setOpt("correctorKoef",9,1);


setOpt("pifInterSize1",0);
setOpt("pifInterSize2",0);
setOpt("pifInterSize3",0);

setOpt("pifInterOp4",1);
setOpt("pifInterOp4_q",0);

setOpt("pifInterSize4",0);


setOpt("pifInterOp1",0);
setOpt("pifInterOp1_q",1);
setOpt("pifInterOp2",0);
setOpt("pifInterOp2_q",1);
setOpt("pifInterOp3",0);
setOpt("pifInterOp3_q",1);

    setOpt("speaker1x",0);
    setOpt("speaker1y",0.5);
    setOpt("speaker2x",1);
    setOpt("speaker2y",0.5);

    


    
    zeroCalcOpt("spiral1");
    zeroCalcOpt("mega1");
    zeroCalcOpt("spiral2");
    zeroCalcOpt("mega2");
    
    char rb[128];
    for(int i=0;i<3;i++){
        setOpt(multiTh(i,"OVCLoopBegin",rb),0);
        setOpt(multiTh(i,"OVCLoopEnd",rb),1);
        zeroCalcOpt(multiTh(i,"videoZoom",rb),0.5);
        zeroCalcOpt(multiTh(i,"videoAspect",rb),0.5);
        zeroCalcOpt(multiTh(i,"videoPosX",rb),0.5);
        zeroCalcOpt(multiTh(i,"videoPosY",rb),0.5);
        zeroCalcOpt(multiTh(i,"OVCLoopEnd",rb),1);
        zeroCalcOpt(multiTh(i,"videoSpeed",rb),1);
    
    }
    
    zeroCalcOpt("interferMorphSpeed",0.5);
    zeroCalcOpt("interferGamma",0.5);
    setOpt("hardFrameDrop",1);
    setOpt("interferPart",1);

 //   setOpt("videoZoom",0.5);
   // setOpt("videoAspect",0.5);
  //  setOpt("videoPosX",0.5);
  //  setOpt("videoPosY",0.5);
   // setOpt("OVCLoopEnd",1);
 //   setOpt("videoSpeed",1);

}

void copy2LOpts(){
    int i,j;
    for(i=0;i<optIds;i++){
        for(j=0;j<optLens[i];j++){
            loptValues[i][j]=optValues[i][j];
            
        }
    }


}
void zeroLOpts(){
    int i,j;
    for(i=0;i<optIds;i++){
        for(j=0;j<optLens[i];j++){
            loptValues[i][j]=-1e100;
            
        }
    }


}

void freeOpts(){
    int i;
    for(i=0;i<optIds;i++){
        if(optLens[i]>0){
            free(optValues[i]);    
            free(loptValues[i]);    
        }
        free(optNames[i]);    
    }
    if(optIds>0){
        free(optNames);    
        free(optValues);    
        free(loptValues);    
        free(optLens);    
    }
    optIds=0;
    optIdsBuf=0;

}



#endif
