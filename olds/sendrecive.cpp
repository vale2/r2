#ifndef SENDRECIVEMOD
#define SENDRECIVEMOD
int lmapOq[OQS][OQS];



#ifdef IPSEND
    #define printf netprintf
    #define fprintf netfprintf
    #include"mynet.cpp"
#endif


#include"editpannels.cpp"
#include<stdio.h>
#include<string.h>
#include"soundutil.cpp"
#include"koefs.cpp"
#include"interfer.cpp"
#include"options.cpp"

double colorCorrector[CCORLEN]={0.5,0.5,0.5,0.5,0.5,0.5,0,0.5,0.5,0.5,0.5,0.5,0.5,};
double lcolorCorrector[CCORLEN];
int correctColorFlag=0;
int lcorrectColorFlag=-100;

int autoPifDeep=0;
extern int soundControllFlag;
int syntaxControll(char*p);
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



double lqsAll_ks[16*16];
double ldrawKoef[DRAWKOEFNUM];//PIF:pifDeep,pifNaked,pifColored,pifDWind,pifDScale,pifDAngle,double colorSpeedr,double colorSpeedg,double colorSpeedb,,pifRepeat,pifParity
double lmaxDrawKoef[DRAWKOEFNUM]={11,1.001,1.001,100,1000,7000,1000000,1000000,1000000,60.01,1.01};
double lminDrawKoef[DRAWKOEFNUM]={2,0,0,-100,-1000,-7000,0.0000001,0.0000001,0.0000001,1,0};
double lcolorStat[COLORSTATLEN];



double lcontrollKoef[DRAWKOEFNUM*KOEFNUM];
double lzeros[DRAWKOEFNUM];
double ldkoef[DRAWKOEFNUM];
double ldkoefacc[DRAWKOEFNUM];
double ldkoefaccperiod[DRAWKOEFNUM];
double lkoefascell[DRAWKOEFNUM];
double lkoefascellacc[DRAWKOEFNUM];
double lkoefascellamp[DRAWKOEFNUM];
double ldrawLatKoef[DRAWKOEFNUM];


double lsoundKoefs[KOEFNUM];
double laccspeed[KOEFNUM];
double llayerOpt[LAYEROPTS];

double lamplifierKoefLowValue=-1;
double lamplifierKoefHighValue=-1;
int lshowColorSeq=-1;
double lminColorSeqFreq=-1.;



/*
maxDrawKoef

minDrawKoef

controllKoef

zeros

dkoef

dkoefacc

dkoefaccperiod

koefascell

koefascellacc

koefascellamp
*/
int checkSpace(char a){
    if(a==' '||a==10||a==13)
        return 1;
    return 0;
}

int skeep(char*p){
    int a=0;
    while(*p&&checkSpace(*p)){
        a++;
        p++;
    }
    while(*p&&!checkSpace(*p)){
        a++;
        p++;
    }
    while(*p&&checkSpace(*p)){
        a++;
        p++;
    }
//    if(a>0)
    return a;
  //  return 0;

}

int readInt(char*p,int*r){
    int a=0;
    *r=0;
    while(*p&&checkSpace(*p)){
        a++;
        p++;
    }
    while(*p&&!checkSpace(*p)){
        if(*p>='0'&&*p<='9'){
            *r=*r*10+*p-'0';
        }else
            break;
        a++;
        p++;
    }
    while(*p&&checkSpace(*p)){
        a++;
        p++;
    }
//    if(a>0)
    return a;
  //  return 0;

}



double * getMasByName(char const*name){


 char tones;
 char oqs;

    if(!strcmp(name,"glOptKoefs"))
        return glOptKoefs;


    if(!strcmp(name,"glOpt"))
        return glOpt;


    if(!strcmp(name,"qsAll_ks"))
        return qsAll.ks;


    if(!strcmp(name,"colorStat"))
        return colorStat;


    if(!strcmp(name,"drawLatKoef"))
        return drawLatKoef;
    if(!strcmp(name,"colorCorrector"))
        return colorCorrector;


    if(!strcmp(name,"drawKoef"))
        return drawKoef;
    if(!strcmp(name,"maxDrawKoef"))
        return maxDrawKoef;

   if(!strcmp(name,"minDrawKoef"))
        return minDrawKoef;
   if(!strcmp(name,"controllKoef"))
        return controllKoef;
   if(!strcmp(name,"zeros"))
        return zeros;
   if(!strcmp(name,"dkoef"))
        return dkoef;
   if(!strcmp(name,"dkoefacc"))
        return dkoefacc;
   if(!strcmp(name,"dkoefaccperiod"))
        return dkoefaccperiod;
   if(!strcmp(name,"koefascell"))
        return koefascell;
   if(!strcmp(name,"koefascellamp"))
        return koefascellamp;
   if(!strcmp(name,"soundKoefs"))
        return soundKoefs;
   if(!strcmp(name,"accspeed"))
        return accspeed;
   if(!strcmp(name,"ascellValue"))
        return ascellValue;
   if(!strcmp(name,"layerOpt"))
        return layerOpt;




    return NULL;
}
double * getLMasByName(char const*name){
 char tones;
 char oqs;

   if(!strcmp(name,"glOptKoefs"))
        return lglOptKoefs;


   if(!strcmp(name,"glOpt"))
        return lglOpt;


    if(!strcmp(name,"qsAll_ks"))
        return lqsAll_ks;



    if(!strcmp(name,"colorStat"))
        return lcolorStat;


    if(!strcmp(name,"drawLatKoef"))
        return ldrawLatKoef;
    if(!strcmp(name,"colorCorrector"))
        return lcolorCorrector;


    if(!strcmp(name,"drawKoef"))
        return ldrawKoef;
    if(!strcmp(name,"maxDrawKoef"))
        return lmaxDrawKoef;

   if(!strcmp(name,"minDrawKoef"))
        return lminDrawKoef;
   if(!strcmp(name,"controllKoef"))
        return lcontrollKoef;
   if(!strcmp(name,"zeros"))
        return lzeros;
   if(!strcmp(name,"dkoef"))
        return ldkoef;
   if(!strcmp(name,"dkoefacc"))
        return ldkoefacc;
   if(!strcmp(name,"dkoefaccperiod"))
        return ldkoefaccperiod;
   if(!strcmp(name,"koefascell"))
        return lkoefascell;
   if(!strcmp(name,"koefascellamp"))
        return lkoefascellamp;
   if(!strcmp(name,"soundKoefs"))
        return lsoundKoefs;
   if(!strcmp(name,"accspeed"))
        return laccspeed;
   if(!strcmp(name,"ascellValue"))
        return lascellValue;
   if(!strcmp(name,"layerOpt"))
        return llayerOpt;
         

    return NULL;
}
int getMasSizeByName(char const*name){

    if(!strcmp(name,"glOptKoefs"))
        return GLOPTS*GLOPTKOEFS;


    if(!strcmp(name,"glOpt"))
        return GLOPTS;


    if(!strcmp(name,"qsAll_ks"))
        return (qsAll.tones)*((int)(qsAll.oqs));


    if(!strcmp(name,"colorStat"))
        return COLORSTATLEN;

    if(!strcmp(name,"drawLatKoef"))
        return DRAWKOEFNUM;

    if(!strcmp(name,"colorCorrector"))
        return CCORLEN;


    if(!strcmp(name,"drawKoef"))
        return DRAWKOEFNUM;
    if(!strcmp(name,"maxDrawKoef"))
        return DRAWKOEFNUM;

   if(!strcmp(name,"minDrawKoef"))
        return DRAWKOEFNUM;
   if(!strcmp(name,"controllKoef"))
        return DRAWKOEFNUM*KOEFNUM;
   if(!strcmp(name,"zeros"))
        return DRAWKOEFNUM;
   if(!strcmp(name,"dkoef"))
        return DRAWKOEFNUM;
   if(!strcmp(name,"dkoefacc"))
        return DRAWKOEFNUM;
   if(!strcmp(name,"dkoefaccperiod"))
        return DRAWKOEFNUM;
   if(!strcmp(name,"koefascell"))
        return DRAWKOEFNUM;
   if(!strcmp(name,"koefascellamp"))
        return DRAWKOEFNUM;
   if(!strcmp(name,"soundKoefs"))
        return KOEFNUM;
   if(!strcmp(name,"accspeed"))
        return KOEFNUM;
   if(!strcmp(name,"ascellValue")){
    return DRAWKOEFNUM;
   }
   if(!strcmp(name,"layerOpt")){
    return LAYEROPTS;
   }
   
   
    return 0;
}



int readMasValue(char const *name,int n,double v){
    double *m;
    double *lm;
    int size;
    m=getMasByName(name);
    lm=getLMasByName(name);
    size=getMasSizeByName(name);
    if(m!=NULL&&lm!=NULL&&n<size){
        m[n]=lm[n]=v;
        if(!strcmp(name,"soundKoefs")){
            archKoef(v,n);
        }
        return 0;
    }
    return -1;
}

void sendMas(char const *   name,FILE*f,int writeAll){
    double *m;
    double *lm;
    int size,i;
    m=getMasByName(name);
    lm=getLMasByName(name);
    size=getMasSizeByName(name);
    if(m!=NULL&&lm!=NULL){
//        printf("%s exist: %d\n",name,size);
        for(i=0;i<size;i++){
            if(fabs(m[i]-lm[i])>0.00000000001 || writeAll){
                fprintf(f,"SetMas %s %d %f\n",name,i,m[i]);
                lm[i]=m[i];            
            }
        
        }
    
    }

}
void sendMas(char const *   name){
    sendMas(name,stdout,0);
}



void sendAllMass(FILE*f,int writeAll,int notWriteZeros){
    sendMas("drawKoef",f,writeAll);
    sendMas("maxDrawKoef",f,writeAll);
    sendMas("minDrawKoef",f,writeAll);
    sendMas("controllKoef",f,writeAll);
    sendMas("zeros",f,writeAll);
    sendMas("dkoef",f,writeAll);
    sendMas("dkoefacc",f,writeAll);
    sendMas("dkoefaccperiod",f,writeAll);
    sendMas("koefascell",f,writeAll);
    sendMas("koefascellacc",f,writeAll);
    sendMas("koefascellamp",f,writeAll);
    sendMas("soundKoefs",f,writeAll);
    sendMas("accspeed",f,writeAll);
    sendMas("ascellValue",f,writeAll);
    sendMas("drawLatKoef",f,writeAll);
    sendMas("colorCorrector",f,writeAll);
    sendMas("colorStat",f,writeAll);
    if(getOpt("send_qsAll_ks")>0.5)
        sendMas("qsAll_ks",f,writeAll);

    sendMas("glOpt",f,writeAll);
    sendMas("glOptKoefs",f,writeAll);
    
    writeOpts(f,writeAll,notWriteZeros);
}
void sendAllMass(FILE*f,int writeAll){
    sendAllMass(f,writeAll,0);

}
void sendAllMass(){
    sendAllMass(stdout,0);

}


void copy2LMas(char const *name){
    double *lm,*m;
    int size,i;
    lm=getLMasByName(name);
    m=getMasByName(name);
    size=getMasSizeByName(name);
    if(lm!=NULL&&m!=NULL){
        for(i=0;i<size;i++){
            lm[i]=m[i];            
        }
    }
    //zeroLOpts();
}

void zeroLMas(char const *name){
    double *lm;
    int size,i;
    lm=getLMasByName(name);
    size=getMasSizeByName(name);
    if(lm!=NULL){
        for(i=0;i<size;i++){
            lm[i]=-1e100;            
        }
    }
    
}




inline void printABCDInt(unsigned int n,char*p){
    unsigned int a;
    char*s;
    s=p;
    a=n;
    if(a<0){
        *s='-';
        s++;
        a=-a;
    }    
    if(a==0){
        *s='a';
        s++;
    }
    while(a>0){
        *s=a%26+'a';
        s++;
        a=a/26;
    }
    *s=' ';
    s++;
    *s=0;
}
inline void printABCDUInt32(Uint32 n,char*p){
    Uint32 a;
    char*s;
    s=p;
    a=n;
    
    if(a==0){
        *s='a';
        s++;
    }
    while(a>0){
        *s=a%26+'a';
        s++;
        a=a/26;
    }
    *s=' ';
    s++;
    *s=0;
}
void sendSpector(int w){
    char tbuf[128];
    int i,k,j;
    double d;
    printf("setSpector %d ",w);
    double*a;
    int koef;
//    if(AFCaccAge<maxAFCaccAge){
        a=AFCacc;
  //      koef=AFCaccAge;
    //}else{
      //  a=sound_a;
        //koef=1;
    //}
    
    for(i=0,j=0;i<w;i++){
        d=0;
        for(k=0;j<(i+1)*Nmax/w;j++,k++){
            if(d<a[j]){
                d=a[j];
            }
            AFCacc[j]=0;
        }
        printABCDInt(d,tbuf);
        printf("%s",tbuf);
    }
    printf("\n");
    AFCaccAge=0;
    //maxAFCaccAge=1000;

}

unsigned int scanABCDInt(char*s){
    unsigned int r=0;
    int sign=1;
    while(*s&&checkSpace(*s))s++;
    if(*s=='-'){
        s++;
        sign=-1;
    }
    while(*s>='a'&&*s<='a'+25){
        r=r*26;
        r+=*s-'a';
        s++;
    }
    return r*sign;
}
Uint32 scanABCDUInt32(char*s){
    Uint32 r=0;
//    int sign=1;
    while(*s&&checkSpace(*s))s++;
    if(*s=='-'){
        s++;
        //sign=-1;
    }
    while(*s>='a'&&*s<='a'+25){
        r=r*26;
        r+=*s-'a';
        s++;
    }
    return r;
}
int reciveSpector(char*s){
    int w;
    char*p;
    int d;
    int len=0;;
    int l,i,j,k;
    p=s;
    
    sscanf(p,"%d",&w);
    len=skeep(p);
    p+=len;
    for(i=0,j=0;i<w;i++){
        d=scanABCDInt(p);
        l=skeep(p);
        p+=l;
        len+=l;
        for(k=0;j<(i+1)*Nmax/w;j++,k++){
            sound_a[j]=d;
        }
        if(*s==0)
            break;
        
    }
    
    

    return len;
}


    int    laddMelodyTorithm=-10;
        
        
    double    lMaxDanceFreq=-10;
    
   int     lsoundControllFlag=-1;
   int       lcolorSeqVar=-1;

int readSoundControllValue(char*name,char*value){
    
    if(!strcmp(name,"correctColorFlag")){
        sscanf(value,"%d",&correctColorFlag);
        lcorrectColorFlag=correctColorFlag;
        return 0;
    }
    

    if(!strcmp(name,"addMelodyTorithm")){
        sscanf(value,"%d",&addMelodyTorithm);
        laddMelodyTorithm=addMelodyTorithm;
        return 0;
    }
    if(!strcmp(name,"MaxDanceFreq")){
        sscanf(value,"%lf",&MaxDanceFreq);
        lMaxDanceFreq=MaxDanceFreq;
        return 0;
    }
    
    if(!strcmp(name,"soundControllFlag")){
        sscanf(value,"%d",&soundControllFlag);
        lsoundControllFlag=soundControllFlag;
        return 0;
    }
    if(!strcmp(name,"colorSeqVar")){
        sscanf(value,"%d",&colorSeqVar);
        colorSeqVar=colorSeqVar;
        return 0;
    }

    if(!strcmp(name,"amplifierKoefHighValue")){
        sscanf(value,"%lf",&amplifierKoefHighValue);
        lamplifierKoefHighValue=amplifierKoefHighValue;
        return 0;
    }
   if(!strcmp(name,"amplifierKoefLowValue")){
        sscanf(value,"%lf",&amplifierKoefLowValue);
        lamplifierKoefLowValue=amplifierKoefLowValue;
        return 0;
    }
   if(!strcmp(name,"showColorSeq")){
        sscanf(value,"%d",&showColorSeq);
        lshowColorSeq=showColorSeq;
        return 0;
    }
   if(!strcmp(name,"minColorSeqFreq")){
        sscanf(value,"%lf",&minColorSeqFreq);
        lminColorSeqFreq=minColorSeqFreq;
        return 0;
    }
 
 


    
    return 1;
}

int readColorSeq(char*p){
    int len,sk,k,t,i;
    sscanf(p,"%d ",&len);
    sk=skeep(p);
    p=p+sk;
    for(i=0;i<len;i++){
        sscanf(p,"%d",&t);
        if(i<SEQLEN){
            colorSeq2Buf[i]=t;
        }
        k=skeep(p);
        sk+=k;
        p+=k;
    }
    return sk;
}

     //writeColorSeq();
     
 
void writeIMas(FILE*f,unsigned int *p,int n){
    char tbuf[128];
    for(int i=0;i<n;i++,p++){
        printABCDInt(*p,tbuf);
        fprintf(f,"%s ",tbuf);
    }

}
void writeUIMas(FILE*f,Uint32 *p,int n){
    char tbuf[128];
    for(int i=0;i<n;i++,p++){
        printABCDUInt32(*p,tbuf);
        fprintf(f,"%s ",tbuf);
    }

}

int readIMas(char*s,unsigned int *p,int n){
    int sk=0;
    int t;
    for(int i=0;i<n;i++,p++){
        *p=scanABCDInt(s);
        t=skeep(s);
        sk+=t;
        s+=t;
    }
    return sk;
}
int readUIMas(char*s,Uint32 *p,int n){
    int sk=0;
    int t;
    for(int i=0;i<n;i++,p++){
        *p=scanABCDUInt32(s);
        t=skeep(s);
        sk+=t;
        s+=t;
    }
    return sk;
}

void writeDMas(FILE*f,double *p,int n){
    for(int i=0;i<n;i++,p++)
        fprintf(f,"%lf ",*p);

}
int readDMas(char*s,double *p,int n){
    int sk=0;
    int t;
    for(int i=0;i<n;i++,p++){
        sscanf(s,"%lf",p);
        t=skeep(s);
        sk+=t;
        s+=t;
    }
    return sk;
}

/*
    unsigned int seqno3[OQS];
    Uint32 oqColorline[OQS][COLORLINELEN];
    Uint32 orOqColorline[COLORLINELEN];
    unsigned int orseqno3;
    double oqColorlineSat[OQS];
    double oqColorlineVal[OQS];
    int mapOq[OQS][OQS];    


*/
    int aa,bb;
   
int readColorSeq3(char*pp){
    int sk=0;
    int t;
    char s[128];
    char*p;
    char *p2;
    p=pp;
    sscanf(p,"%s",s);
    sk=skeep(p);
    p+=sk;
//    fprintf(stderr,"readColorSeq3 (%s)",s);
  //  fprintf(stderr," %s\n",p);
    
    //fflush(stderr);
    p2=p;
//                        fprintf(f,"setColorSeq3 mapOq %d %d %d\n",i,j,cl->mapOq[i][j]);
  //                  lmapOq[i][j]=cl->mapOq[i][j];
    if(!strcmp(s,"mapOq")){
        sscanf(p,"%d",&aa);
        t=skeep(p);
        sk+=t;
        p+=t;
        sscanf(p,"%d",&bb);
        t=skeep(p);
        sk+=t;
        p+=t;
        sscanf(p,"%d",&(cl->mapOq[aa][bb]));
        t=skeep(p);
        sk+=t;
        p+=t;
        lmapOq[aa][bb]=cl->mapOq[aa][bb];
    }
    
    if(!strcmp(s,"seqno3")){
        sscanf(p,"%d ",&aa);
      //  fprintf(stderr,"[seqno3] <%d> ",aa);
        //fprintf(stderr,"%s\n ",p);
        //fflush(stderr);

        t=skeep(p);

        sk+=t;
        p+=t;

//        t=readIMas(p,(int*)cl->seqno3,a);
        sk+=t;
        p+=t;
    }
    
    if(!strcmp(s,"oqColorline")){
        //sscanf(p,"%d ",&a);
//        t=readInt(p,&aa);;
  //      t+=readInt(p+t,&bb);
        aa=scanABCDInt(p);
        t=skeep(p);
        bb=scanABCDInt(p+t);
        t+=skeep(p+t);

    
        //skeep(p);
//        sk+=t;
  //      p+=t;
        //sscanf(p+t,"%d ",&b);
        //char bbb[128];
       // sprintf(bbb,"%d %d",aa,bb);
      
        //fprintf(stderr,"--oqColorline-- %s ",bbb);
          
       // fprintf(stderr,"%s\n ",p);
       // fflush(stderr);

        
        
        sk+=t;
        p+=t;
       // Uint32 cc;
     //   cc=rand()%256+(rand()%256)*256+256*(rand()%256);
   //     for(int i=0;i<bb;i++)
         //   cl->oqColorline[aa][i]=cc;
        t=readUIMas(p,cl->oqColorline[aa],bb);
        sk+=t;
        p+=t;

    }
    
    if(!strcmp(s,"orOqColorline")){
        sscanf(p,"%d",&aa);
        t=skeep(p);
        sk+=t;
        p+=t;
     //   fprintf(stderr,"[orOqColorline] %d\n",aa);
       // fflush(stderr);
        t=readIMas(p,(unsigned int*)cl->orOqColorline,aa);
        sk+=t;
        p+=t;
    }
    if(!strcmp(s,"orseqno3")){
        sscanf(p,"%d",&(cl->orseqno3));
        t=skeep(p);
        sk+=t;
        p+=t;
        //fprintf(stderr,"[orseqno3] %d\n",cl->orseqno3);
        //fflush(stderr);
    }
    
    if(!strcmp(s,"oqColorlineSat")){
        sscanf(p,"%d",&aa);
        t=skeep(p);
        sk+=t;
        p+=t;
        //fprintf(stderr,"[oqColorlineSat] %d\n",aa);
        //fflush(stderr);
        //t=readDMas(p,cl->oqColorlineSat,a);
        sk+=t;
        p+=t;
    }
    if(!strcmp(s,"oqColorlineVal")){
        sscanf(p,"%d",&aa);
        t=skeep(p);
        sk+=t;
        p+=t;
       // fprintf(stderr,"[oqColorlineVal] %d\n",aa);
       // fflush(stderr);
        //t=readDMas(p,cl->oqColorlineVal,a);
        sk+=t;
        p+=t;
    }
    if(!strcmp(s,"maxoqs")){
        sscanf(p,"%d",&(maxoqs));
        t=skeep(p);
        sk+=t;
        p+=t;
        //fprintf(stderr,"[orseqno3] %d\n",maxoqs);
        //fflush(stderr);
    }
    
//    fprintf(f,"setColorSeq3 maxoqs %d\n",);
    return sk;
}


int wcs3i=0;
void writeColorSeq3(FILE*f){
    fprintf(f,"\n");
    fprintf(f,"setColorSeq3 seqno3 %d ",OQS);
    writeIMas(f,(unsigned int*)cl->seqno3,OQS);    
    fprintf(f,"\n");
   // writeColorLineMap(f);
    
   // for(int i=0;i<OQS;i++)
    {
        if(wcs3i<0||wcs3i>=maxoqs)
            wcs3i=0;
        char b1[128];
        char b2[128];
     //   wcs3i=i;
        printABCDInt(wcs3i,b1);
        printABCDInt(COLORLINELEN,b2);        
//        i,COLORLINELEN
        //fprintf(f,"setColorSeq3 oqColorline %s %s ",b1,b2);
        //writeUIMas(f,cl->oqColorline[wcs3i],COLORLINELEN);    
        //fprintf(f,"\n");
//        printABCDInt(i,b1);
        printABCDInt(OQS,b2);        

        
//        fprintf(f,"setColorSeq3 mapOq %s %s ",b1,b2);
  //      writeIMas(f,(unsigned int*)cl->mapOq[wcs3i],OQS);    
    //    fprintf(f,"\n");
        wcs3i++;
    }
   // fprintf(f,"setColorSeq3 orOqColorline %d ",COLORLINELEN);
   // writeUIMas(f,cl->orOqColorline,COLORLINELEN);    
   // fprintf(f,"\n");

   // fprintf(f,"setColorSeq3 orseqno3 %d\n",cl->orseqno3);
   // fprintf(f,"setColorSeq3 maxoqs %d\n",maxoqs);


//    fprintf(f,"setColorSeq3 oqColorlineSat %d ",OQS);
  //  writeDMas(f,cl->oqColorlineSat,OQS);    
    //fprintf(f,"\n");

    //fprintf(f,"setColorSeq3 oqColorlineVal %d ",OQS);
    //writeDMas(f,cl->oqColorlineVal,OQS);    
    //fprintf(f,"\n");

    
}
void writeColorSeq3(){
    writeColorSeq3(stdout);
}







void writeColorSeq(FILE*f){
    fprintf(f,"setColorSeq %d ",SEQLEN);
    for(int i=0;i<SEQLEN;i++){
        fprintf(f,"%d ",(int)colorSeq2Buf[i]);
    }
    fprintf(f,"\n");
}
void writeColorSeq(){
    writeColorSeq(stdout);
}

void writeVolume(FILE*f,int writeAll){
    if(!dEq(lamplifierKoefLowValue,amplifierKoefLowValue) || writeAll){
        fprintf(f,"set amplifierKoefLowValue %f\n",amplifierKoefLowValue);
        lamplifierKoefLowValue=amplifierKoefLowValue;
    
    }
    if(!dEq(lamplifierKoefHighValue,amplifierKoefHighValue) || writeAll){
        fprintf(f,"set amplifierKoefHighValue %f\n",amplifierKoefHighValue);
        lamplifierKoefHighValue=amplifierKoefHighValue;
    }
    


}
void writeVolume(){
    writeVolume(stdout,0);
}


int writeSoundControllValue(FILE*f,int writeAll){
    
    if(correctColorFlag!=lcorrectColorFlag || writeAll){
        fprintf(f,"set correctColorFlag %d\n",correctColorFlag);
        lcorrectColorFlag=correctColorFlag;
    
    }

    if(!dEq(lminColorSeqFreq,minColorSeqFreq) || writeAll){
        fprintf(f,"set minColorSeqFreq %f\n",minColorSeqFreq);
        lminColorSeqFreq=minColorSeqFreq;
    
    }
    
    
    
    if(lshowColorSeq!=showColorSeq || writeAll){
        fprintf(f,"set showColorSeq %d\n",showColorSeq);
        lshowColorSeq=showColorSeq;
    }


    
    if(laddMelodyTorithm!=addMelodyTorithm || writeAll){
        fprintf(f,"set addMelodyTorithm %d\n",addMelodyTorithm);
        laddMelodyTorithm=addMelodyTorithm;
    
    }
    if(!dEq(lMaxDanceFreq,MaxDanceFreq) || writeAll){
        fprintf(f,"set MaxDanceFreq %f\n",MaxDanceFreq);
        lMaxDanceFreq=MaxDanceFreq;
    
    }
    if(lsoundControllFlag!=soundControllFlag || writeAll){
        fprintf(f,"set soundControllFlag %d\n",soundControllFlag);
        lsoundControllFlag=soundControllFlag;
    }
    if(lcolorSeqVar!=colorSeqVar || writeAll){
        fprintf(f,"set colorSeqVar %d\n",colorSeqVar);
        lcolorSeqVar=colorSeqVar;
    }


}

int writeSoundControllValue(){
    return writeSoundControllValue(stdout,0);
}
int writeSoundControllValue(int writeAll){
    return writeSoundControllValue(stdout,writeAll);
}

int    lnoiseColor=-100;
int    lnoiseV=-100;
int    lnoiseC=-100;
int    lrgbMixerDepth=-100;
int    lfaded=-100;
int    lmode=-100;
extern int mode;

int lorblurd=-100;
double lpifColorSpeedb=-100.;
double lpifColorSpeedg=-100.;
double lpifColorSpeedr=-100.;
int lautoPifDeep=-10;

void writeColorLineMap(FILE*f,int writeAll){
   int i,j;
    for(i=0;i<OQS;i++)
        for(j=0;j<OQS;j++){
                if(lmapOq[i][j]!=cl->mapOq[i][j] || writeAll){
                    fprintf(f,"setColorSeq3 mapOq %d %d %d\n",i,j,cl->mapOq[i][j]);
                    lmapOq[i][j]=cl->mapOq[i][j];
                }
        }
}
void sendFilters(FILE*f,int writeAll){
    writeColorLineMap(f,writeAll);
    if(autoPifDeep!=lautoPifDeep || writeAll){
        fprintf(f,"set autoPifDeep %d\n",autoPifDeep);
    
        lautoPifDeep   = autoPifDeep ;
    }
    
    
    if(faded!=lfaded || writeAll){
        fprintf(f,"set faded %d\n",faded);
        lfaded   = faded ;
    }
    if(mode!=lmode || writeAll){
        fprintf(f,"setmode %d\n",mode);
        lmode   = mode ;
    }

    if(orblurd!=lorblurd || writeAll){
        fprintf(f,"set orblurd %d\n",orblurd);
    
        lorblurd   = orblurd ;
    }
    if(rgbMixerDepth!=lrgbMixerDepth || writeAll){
        fprintf(f,"set rgbMixerDepth %d\n",rgbMixerDepth);
         lrgbMixerDepth  =rgbMixerDepth  ;
    }
    if(noiseC!=lnoiseC || writeAll){
        fprintf(f,"set noiseC %d\n",noiseC);
         lnoiseC  = noiseC ;
    }
    if(noiseV!=lnoiseV || writeAll){
        fprintf(f,"set noiseV %d\n",noiseV);
         lnoiseV  =  noiseV;
    }
    if(noiseColor!=lnoiseColor || writeAll){
        fprintf(f,"set noiseColor %d\n",noiseColor);
         lnoiseColor  = noiseColor ;
    }

   if(!dEq(pifColorSpeedr,lpifColorSpeedr) || writeAll){
        fprintf(f,"set pifColorSpeedr %lf\n",pifColorSpeedr);
         lpifColorSpeedr  = pifColorSpeedr ;
    }
    if(!dEq(pifColorSpeedg,lpifColorSpeedg) || writeAll){
        fprintf(f,"set pifColorSpeedg %lf\n",pifColorSpeedg);
        lpifColorSpeedg   = pifColorSpeedg ;
    }
    if(!dEq(pifColorSpeedb,lpifColorSpeedb) || writeAll){
        fprintf(f,"set pifColorSpeedb %lf\n",pifColorSpeedb);
        lpifColorSpeedb   =pifColorSpeedb  ;
    }

    sendMas("layerOpt",f,writeAll);
    
    
    
    
 

}
void sendFilters(){
     sendFilters(stdout,0);

}

void zeroLColorLineMap(){
    int i,j;
    for(i=0;i<OQS;i++)
        for(j=0;j<OQS;j++){
                lmapOq[i][j]=-100;
        }
}

void copy2lvalues(){
    copy2LMas("drawKoef");
    copy2LMas("maxDrawKoef");
    copy2LMas("minDrawKoef");
    copy2LMas("controllKoef");
    copy2LMas("zeros");
    copy2LMas("dkoef");
    copy2LMas("dkoefacc");
    copy2LMas("dkoefaccperiod");
    copy2LMas("koefascell");
    copy2LMas("koefascellacc");
    copy2LMas("koefascellamp");
    copy2LMas("soundKoefs");
    copy2LMas("accspeed");
    copy2LMas("ascellValue");
    copy2LMas("layerOpt");
    copy2LMas("drawLatKoef");
    copy2LMas("colorCorrector");
    copy2LMas("colorStat");
    copy2LMas("qsAll_ks");
 //   copy2LColorLineMap();
    copy2LMas("glOpt");
    copy2LMas("glOptKoefs");





        lcorrectColorFlag=correctColorFlag;
        lminColorSeqFreq=minColorSeqFreq;
        lshowColorSeq=showColorSeq;
        lamplifierKoefLowValue=amplifierKoefLowValue;
        lamplifierKoefHighValue=amplifierKoefHighValue;
        laddMelodyTorithm=addMelodyTorithm;
        lMaxDanceFreq=MaxDanceFreq;
        lsoundControllFlag=soundControllFlag;
        lcolorSeqVar=colorSeqVar;
        lcorrectColorFlag=correctColorFlag;
   
        lfaded   = faded ;
        lmode=mode;
        lorblurd = orblurd;
        lrgbMixerDepth  =rgbMixerDepth  ;
        lnoiseC  = noiseC ;
        lnoiseV  =  noiseV;
        lnoiseColor  = noiseColor ;
        lpifColorSpeedr  = pifColorSpeedr ;
        lpifColorSpeedg   = pifColorSpeedg ;
        lpifColorSpeedb   =pifColorSpeedb  ;
        copy2LOpts();
    


}
void zeroLValues(){
    zeroLMas("drawKoef");
    zeroLMas("maxDrawKoef");
    zeroLMas("minDrawKoef");
    zeroLMas("controllKoef");
    zeroLMas("zeros");
    zeroLMas("dkoef");
    zeroLMas("dkoefacc");
    zeroLMas("dkoefaccperiod");
    zeroLMas("koefascell");
    zeroLMas("koefascellacc");
    zeroLMas("koefascellamp");
    zeroLMas("soundKoefs");
    zeroLMas("accspeed");
    zeroLMas("ascellValue");
    zeroLMas("layerOpt");
    zeroLMas("drawLatKoef");
    zeroLMas("colorCorrector");
    zeroLMas("colorStat");
    zeroLMas("qsAll_ks");
    zeroLColorLineMap();
    zeroLMas("glOpt");
    zeroLMas("glOptKoefs");





        lcorrectColorFlag=-100;
        lminColorSeqFreq=-1e100;
        lshowColorSeq=-10000;
        lamplifierKoefLowValue=-1e100;
        lamplifierKoefHighValue=-1e100;
        laddMelodyTorithm=-10000;
        lMaxDanceFreq=-1e100;
        lsoundControllFlag=-10000;
        lcolorSeqVar=-10000;
        lcorrectColorFlag=-100;
   
        lfaded   = -100 ;
        lmode=-100;
        lorblurd = -100;
        lrgbMixerDepth  =-100  ;
        lnoiseC  = -100 ;
        lnoiseV  =  -100;
        lnoiseColor  = -100 ;
        lpifColorSpeedr  = -1e100 ;
        lpifColorSpeedg   = -1e100 ;
        lpifColorSpeedb   =-1e100  ;
    
        zeroLOpts();
}


struct layer*recvLayer(struct layer*l,char *p){
    int w,h,i,j,t;
    sscanf(p,"%d",&w);
    p+=skeep(p);
    sscanf(p,"%d",&h);
    p+=skeep(p);
    l=resizeLayer(l,w,h);
    if(l==NULL)
        return NULL;
    for(i=0;i<h && *p;i++){
        for(j=0;j<w && *p;j++){
            sscanf(p,"%d",&t);
            p+=skeep(p);
            if(t<0)
                t=0;
            if(t>255)
                t=255;
            l->p[j+i*w]=t;      
        }
    
    }
    return l;
}
void sendLayer(struct layer*l,FILE*f){
    int w,h,t,i,j;
    w=l->w;
    h=l->h;
    
    fprintf(f,"%d ",w);
    fprintf(f,"%d ",h);
    
    for(i=0;i<h;i++){
        for(j=0;j<w;j++){
            t=l->p[j+i*w];
            fprintf(f,"%d ",t);      
        }
    }
    fprintf(f,"\n");      
}




#endif