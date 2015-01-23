#include <SDL/SDL.h>
#include"graphutil.cpp"
#ifndef M_SENSE
#define M_SENSE
extern int colorSeqVar;

void drawLine(SDL_Surface *sc,int x1, int y1, int x2, int y2,int c);
int detectTone(double freq);
int detectOk(double freq);
double findCos(struct qs a);
void setQsMm(struct qs*r,int t,int oq,double value);
double getQsDis(struct qs*r,int t,int oq);
double getQsMm(struct qs*r,int t,int oq);
double getQsMm05(struct qs*r,int t,int oq);

double getQs(struct qs*r,int t,int oq);
#include"sens.cpp"

struct qs{
    double zeroFreq;
    char tones;
    char oqs;
    double* ks;
    int *dises;
    int *linDises;
    double *dlinDises;
    double *dlin3T;
    double *dis;
    double *mm;
    double *mm05;
    double *fade;
    struct sense*snsFade;    
    struct sense*dlinDisesSns[24];
    struct sense*sns;    
    struct sense *snsDis;    
    struct sense *snsMm;    
    struct sense *snsMm05;    

    int bufsize;
};


#include"cos.cpp"
#define DISES 13
int kosd[DISES]={0,12,7,5,3,4,8,9,6,2,10,1,11};
//double kosv[13]={1,1.4,0.93,0.87,0.82,0.81,0.79,0.75,0.71,0.68,0.65,0.4,0.34};
double kosv[DISES]={1.2,2,0.95,0.83,0.82,0.81,0.79,0.75,0.71,0.68,0.65,0.4,0.34};
void setQsDis(struct qs*r,int t,int oq,double value);


unsigned int getDisVectorT;
int myR(int min,int max){
    if(min>=max){
        return min;
    }
    return rand()%(max-min+1)-min;
}
void getDisVector(int dt,int max,double&dx,double&dy){
    dt=abs(dt)%12;
    switch (dt){
        case 0: dx=0;dy=0;break;//
        case 1: dx=myR(-max,max);dy=myR(-max,max);break;
        case 2: dx=myR(-max/2,max/2);dy=myR(-max/2,max/2);break;
        case 3: dx=myR(-max/8,max/8);dy=myR(-max/4,max/4);break;
        case 4: dx=myR(-max/3,max/3);dy=myR(-max/3,max/3);break;
        case 5: dx=myR(-max/4,max/4);dy=myR(-max/8,max/8);break;
        case 6: dx=myR(-max/2,max/2);dy=myR(-max/2,max/2);break;
        case 7: dx=myR(-max/8,max/8);dy=myR(-max/8,max/8);break;
        case 8: dx=myR(-max/2,max/2);dy=myR(-max/3,max/3);break;
        case 9: dx=myR(-max/3,max/3);dy=myR(-max/2,max/2);break;
        case 10: dx=myR(-max,max);dy=myR(-max/2,max/2);break;
        case 11: dx=myR(-max,max);dy=myR(-max,max);break;
        case 12: dx=getDisVectorT%2;dy=(getDisVectorT/2)%2;break;//
    }
    getDisVectorT++;
}
int  reallocQs(struct qs*q,int tones,int oq);
void QSmorph(struct qs*oldl,struct qs*newl,double d){
    int i,j;
    double*o,*n;
    reallocQs(oldl,newl->tones,newl->oqs);
    if(d<0.)
        d=0.;
    if(d>1.)
        d=1.;
    o=oldl->ks;
    n=newl->ks;
    
    if(d<0.0001){
        for(i=0;i<oldl->oqs;i++)
            for(j=0;j<oldl->tones;j++,o++,n++){
                *o=*n;

            }
        return;
    }    
    
    for(i=0;i<oldl->oqs;i++)
        for(j=0;j<oldl->tones;j++,o++,n++){
            *o=(*o)*d + (*n)*(1.-d);
        }



}

int comparedVolumes(double me,double him){
    double t;
    if(me<0.001||him<0.001)
        return 0;
    if(me>him){
        t=me;
        me=him;
        him=t;    
    }// now, me - smaller than him

    if(me*10>him)
        return 1;
    return 0;
}


double compareVolumesKoef(double me,double him){
    double t;
   // return 1-fabs(me-him);
    
    if(me>him){
        t=me;
        me=him;
        him=t;    
    }// now, me - smaller than him

    if(me<0.001||him<0.001)
        return 0.;
    if(me*100<him)
        return 0.;
    return 2/(him*him*him*him*him*him/me/me/me/me/me/me +me*me*me*me*me*me/him/him/him/him/him/him);
//    return 2/(him/me +me/him);



}
double linCompareVolumesKoef(double me,double him){
    double t;
    return 1-fabs(me-him);

}


double findDis(int di){
    di=abs(di);
    for(int i=0;i<DISES;i++){
        if(di==kosd[i])
            return kosv[i];
    }
    return 1;
}
double findNumDis(int di){
    di=abs(di);
    for(int i=0;i<DISES;i++){
        if(di==kosd[i])
            return i;
    }
    return -1;
}
double diss[DISES];
extern double layerOpt[15];
#define ALLTONES 12
double cds[OQS*ALLTONES][OQS*ALLTONES];
unsigned int cdsOk[OQS*ALLTONES][OQS*ALLTONES];

double linCds[OQS*ALLTONES][OQS*ALLTONES];
unsigned int linCdsOk[OQS*ALLTONES][OQS*ALLTONES];


unsigned int cdsOkflag=1;
#define MAJORS 3
#define MINORS 3
double maValues[MAJORS]={1,0.8,0.6};
double miValues[MINORS]={1,0.8,0.6};//,1.1,1.2};

int ma[MAJORS][2]={{4,3},{3,5},{5,4}};
int mi[MINORS][2]={{3,4},{4,5},{5,3}};//,{3,3},{4,4}};


double findCd(struct qs*q,int me,int him){
    double cd;
    if(cdsOk[me][him]!=cdsOkflag){
           cd=compareVolumesKoef(q->ks[me],q->ks[him]);                    
           cdsOk[me][him]=cdsOkflag;
           cdsOk[him][me]=cdsOkflag;
           cds[me][him]=cd;
           cds[him][me]=cd;
           return cd;                        
     }else{
          return cds[me][him];
    }
}
double findLinCd(struct qs*q,int me,int him){
    double cd;
    if(me<0||him<0||me>=q->oqs*q->tones||him>=q->oqs*q->tones)
        return 0;
    if(linCdsOk[me][him]!=cdsOkflag){
           cd=linCompareVolumesKoef(q->ks[me],q->ks[him]);                    
           linCdsOk[me][him]=cdsOkflag;
           linCdsOk[him][me]=cdsOkflag;
           linCds[me][him]=cd;
           linCds[him][me]=cd;
           return cd;                        
     }else{
          return linCds[me][him];
    }
}



double find3tone(struct qs*q,int me,int d1,int d2){
                  return findCd(q,me,me-d1)*findCd(q,me,me+d2)
                    +findCd(q,me,me-d2)*findCd(q,me,me-d2-d1)
                    +findCd(q,me,me+d1)*findCd(q,me,me+d1+d2);

}
double findLin3tone(struct qs*q,int me,int d1,int d2){
                  return 1-(1-findLinCd(q,me,me-d1))*(1-findLinCd(q,me,me+d2))
                    +1-(1-findLinCd(q,me,me-d2))*(1-findLinCd(q,me,me-d2-d1))
                    +1-(1-findLinCd(q,me,me+d1))*(1-findLinCd(q,me,me+d1+d2));

}
double findPureLin3tone(struct qs*q,int me,int d1,int d2){
                  if(d1==0||d1>=d2)
                    return 0.;
                  return (1-(1-findCd(q,me,me+d1))*(1-findCd(q,me,me+d2))*(1-findCd(q,me+d1,me+d2))
                         +
                        1-(1-findCd(q,me-d1,me-d1+d2))*(1-findCd(q,me,me-d1+d2))*(1-findCd(q,me-d1,me))
                         +
                        1-(1-findCd(q,me-d2,me))*(1-findCd(q,me-d2,me-d2+d1))*(1-findCd(q,me,me-d2+d1)))/3.
                         
                  
                  ;
                    
}

int               mmaiinit=0;
struct sense snsmma;
struct sense snsmmi;
double iStat[13];
double iStatd[13];
double i3Stat[13];
double i3Statd[13];

void sendIStat(){
    double a;
    int i;
//    a=0;
  //  for(i=0;i<13;i++){
    //    if(a<iStat[i])
      //      a=iStat[i];
    //}
   // if(a<0.001)
        a=0.001;
    for(i=0;i<13;i++){
        if(iStatd[i]>=0.0001){
            setOpt("iStat",i,iStat[i]/iStatd[i]);
        }else{
            setOpt("iStat",i,0);
        }
        if(i3Statd[i]>=0.0001){
            setOpt("3Stat",i,i3Stat[i]/i3Statd[i]);
        }else{
            setOpt("3Stat",i,0);
        }
    }
}


int i3Tn=0;
int i3d1[13];
int i3d2[13];
void prepare3TOpts(){
    double i3Cr,i3Cg,i3Cb,i3v;
    for(int i=0;i<13;i++){
        i3d1[i]=getOpt("3Interval1",i);
        i3d2[i]=getOpt("3Interval2",i);
        i3Cr=getOpt("3Red",i);
        i3Cg=getOpt("3Green",i);
        i3Cb=getOpt("3Blue",i);
        i3v=getOpt("3Value",i);
        if(fabs(i3Cr)+fabs(i3Cb)+fabs(i3Cg)>0.001&&fabs(i3v)>0.001){
            i3Tn=i+1;
        }

    
    }

//    fprintf(stderr,"i3Tn=%d\n",i3Tn);
}
void calcQSDis(struct qs*q){
    int i,j,me,di,him;
//    double dx,dy;
    double dis,alld;
    double ipow;
    ipow=getOpt("intervalComparePow");
    cdsOkflag++;
    for(i=0;i<DISES;i++){
        diss[i]=0;
    
    }
    prepare3TOpts();
    if(!mmaiinit){
                    mmaiinit=1;
                    zeroSense(&(snsmma),"allMajors");
                    zeroSense(&(snsmmi),"allMinors");
                    snsmma.c.on=1;
                    snsmmi.c.on=1;
                    
                    
    }

  //  double alld;
    alld=0;
    
  //  for(i=0;i<q->oqs*q->tones;i++){
   //     for(j=0;j<q->oqs*q->tones;j++){
   //             cdsOk[i][j]=0;
   //     }
    
   // }
   // double disLevel;
   // disLevel=layerOpt[12];
//    if(disLevel<0.0001)
  //      disLevel=0.0001;
   for(i=0;i<13;i++){
        iStat[i]=0;
        iStatd[i]=0;
        i3Stat[i]=0;
        i3Statd[i]=0;

    }
    for(i=0;i<q->oqs;i++)
        for(j=0;j<q->tones;j++){
               dis=1;
                me=j+i*(q->tones);
                //dx=0.;
                //dy=0.;
                for(int iji=0;iji<i3Tn;iji++){
                    /*int i3Tn=0;
int i3d1[13];
int i3d2[13];*/
                    double i3=findPureLin3tone(q,me,i3d1[iji],i3d2[iji]);
                    q->dlin3T[me*13+iji]=i3;
                    
                    i3Stat[iji]+=i3*q->ks[me];
                    i3Statd[iji]+=q->ks[me];
                }
                
                for(di=-q->tones+1;di<=q->tones;di++){
                    him=me+di;
                    if(him>=0&&him<q->tones*q->tones){
                      double cd,fd,linCd;
                      cd=findCd(q,me,him);
                      linCd=findLinCd(q,me,him);

                      int a;      
                      a=findNumDis(di);
                      fd=findDis(di);
                      if(a>=0){
                            alld+=cd*q->ks[me];
                            diss[a]+=cd*q->ks[me];
                      }
                      //if(di!=0)
                      {
                        int ddi;
                        //if(di<0){
                             ddi=di+q->tones-1;
                      // }else{
                     //       ddi=di+q->tones-2;
                      // }
                        
                        q->dises[me*2*(q->tones)+ddi]=cd*1024;//*disLevel;      
                        q->linDises[me*2*(q->tones)+ddi]=linCd*1024;//*disLevel;      
                         if(colorSeqVar==9){

                            q->dlinDises[me*2*(q->tones)+ddi]=linCd;//senseValue(&(q->dlinDisesSns[ddi][me]),linCd);//*disLevel;      
                            double a;
                            a=cd*q->ks[me];
                            if(di==0||di==12){
                                a=a+a;
                            iStatd[abs(di)]+=q->ks[me];
                            }
                            iStat[abs(di)]+=a;
                            iStatd[abs(di)]+=q->ks[me];
                            
                        }
                      }
                      
                      dis=dis*(1-(1-fd)*cd);                    
                    }
   
   
                
                }

         //       if(dis>1.)
           //         dis=1.;
             //   if(dis<0.)
               //     dis=0.;
                setQsDis(q,j,i,dis);
                //q->dis[me]=dis;
               double mma,mmi;
               int k;
               mma=0;
               mmi=0;
               for(k=0;k<MAJORS;k++){
                    double a;
                    double b;
                    mma=mma+find3tone(q,me,ma[k][0],ma[k][1])*maValues[k];
               }
               for(k=0;k<MINORS;k++){
                    double a;
                    double b;
                    mmi=mmi+find3tone(q,me,mi[k][0],mi[k][1])*miValues[k];
                    
                    
               }
              // mma=senseValue(&(snsmma),mma);
              // mmi=senseValue(&(snsmmi),mmi);
               setQsMm(q,j,i,mma-mmi);
       
               /*if(mma>mmi){
                    setQsMm(q,j,i,mma);
               }else{
                    setQsMm(q,j,i,-mmi);
               }*/
                
        }
    for(i=0;i<DISES;i++){
            diss[i]=diss[i]/alld;
    }
    
                sendIStat();

}
double calcSumQSDis(struct qs*q){
    double r;
    int i,j;
    r=0;
    for(i=0;i<q->tones;i++){
        for(j=0;j<q->oqs;j++){
            r=r+getQsDis(q,i,j)*getQs(q,i,j);
        }

    }    
    return r;
}
double calcSumQSMm(struct qs*q){
    double r;
    int i,j;
    r=0;
    for(i=0;i<q->tones;i++){
        for(j=3;j<q->oqs;j++){
            r=r+(getQsMm05(q,i,j)-0.5 )*getQs(q,i,j);
        }

    }    
    return r;
}


int  reallocQs(struct qs*q,int tones,int oq){
    if(q->ks==NULL){
        q->ks=(double*)malloc(tones*oq*sizeof(double));
        if(q->ks==NULL)
            return -1;
        memset(q->ks,0,tones*oq*sizeof(double));
    
        q->dis=(double*)malloc(tones*oq*sizeof(double));
        if(q->dis==NULL)
            return -1;
        q->mm=(double*)malloc(tones*oq*sizeof(double));
        if(q->mm==NULL)
            return -1;
        q->fade=(double*)malloc(tones*oq*sizeof(double));
        if(q->fade==NULL)
            return -1;

        q->mm05=(double*)malloc(tones*oq*sizeof(double));
        if(q->mm05==NULL)
            return -1;
    
        q->dises=(int*)malloc(2*tones*tones*oq*sizeof(int));
        if(q->dises==NULL)
            return -1;
        memset(q->dises,0,2*tones*tones*oq*sizeof(int));

        q->linDises=(int*)malloc(2*tones*tones*oq*sizeof(int));
        if(q->linDises==NULL)
            return -1;
        memset(q->linDises,0,2*tones*tones*oq*sizeof(int));

        q->dlinDises=(double*)malloc(2*tones*tones*oq*sizeof(double));
        if(q->dlinDises==NULL)
            return -1;
        memset(q->dlinDises,0,2*tones*tones*oq*sizeof(double));
        
        q->dlin3T=(double*)malloc(13*tones*oq*sizeof(double));
        if(q->dlin3T==NULL)
            return -1;
        memset(q->dlin3T,0,13*tones*oq*sizeof(double));
        
        
        for(int i=0;i<2*tones;i++){
            char s[128];
            sprintf(s,"dlinDisesSns_%d",i);
            q->dlinDisesSns[i]=makeSence(s,tones*oq);
        }

        q->sns=(struct sense*)malloc(tones*oq*sizeof(struct sense));
        if(q->sns==NULL)
            return -1;
        zeroSenses(q->sns,tones*oq,"qs");

        q->snsFade=(struct sense*)malloc(tones*oq*sizeof(struct sense));
        if(q->snsFade==NULL)
            return -1;
        zeroSenses(q->snsFade,tones*oq,"qsFade");
        
        q->snsMm=(struct sense*)malloc(tones*oq*sizeof(struct sense));
        if(q->snsMm==NULL)
            return -1;
        zeroSenses(q->snsMm,tones*oq,"qsMm");

        q->snsMm05=(struct sense*)malloc(tones*oq*sizeof(struct sense));
        if(q->snsMm05==NULL)
            return -1;
        zeroSenses05(q->snsMm05,tones*oq,"qsMm05");

        q->snsDis=(struct sense*)malloc(tones*oq*sizeof(struct sense));
        if(q->snsDis==NULL)
            return -1;
        zeroSenses(q->snsDis,tones*oq,"qsDis");


        q->tones=tones;
        q->oqs=oq;
        q->bufsize=oq*tones;
        return 0;
    }
    
    
    
    if(tones*oq>q->bufsize){
        if(q->ks!=NULL)
            free(q->ks);
        if(q->dis!=NULL)
            free(q->dis);
        if(q->mm!=NULL)
            free(q->mm);
        if(q->mm05!=NULL)
            free(q->mm05);
        if(q->fade!=NULL)
            free(q->fade);
        
        
        q->ks=(double*)malloc(tones*oq*sizeof(double));
        if(q->ks==NULL)
            return -1;
        memset(q->ks,0,tones*oq*sizeof(double));

        q->dis=(double*)malloc(tones*oq*sizeof(double));
        if(q->dis==NULL)
            return -1;
      
        q->mm=(double*)malloc(tones*oq*sizeof(double));
        if(q->mm==NULL)
            return -1;
      
        q->fade=(double*)malloc(tones*oq*sizeof(double));
        if(q->fade==NULL)
            return -1;

      
        q->mm05=(double*)malloc(tones*oq*sizeof(double));
        if(q->mm05==NULL)
            return -1;
      
      
        q->dises=(int*)malloc(2*tones*tones*oq*sizeof(int));
        if(q->dises==NULL)
            return -1;
        memset(q->dises,0,2*tones*tones*oq*sizeof(int));

        q->linDises=(int*)malloc(2*tones*tones*oq*sizeof(int));
        if(q->linDises==NULL)
            return -1;
        memset(q->linDises,0,2*tones*tones*oq*sizeof(int));

        q->dlinDises=(double*)malloc(2*tones*tones*oq*sizeof(double));
        if(q->dlinDises==NULL)
            return -1;
        memset(q->dlinDises,0,2*tones*tones*oq*sizeof(double));

        q->dlin3T=(double*)malloc(13*tones*oq*sizeof(double));
        if(q->dlin3T==NULL)
            return -1;
        memset(q->dlin3T,0,13*tones*oq*sizeof(double));


        for(int i=0;i<2*tones;i++){
            char s[128];
            sprintf(s,"dlinDisesSns_%d",i);
            q->dlinDisesSns[i]=makeSence(s,tones*oq);
        }


        if(q->sns!=NULL)
            free(q->sns);
        q->sns=(struct sense*)malloc(tones*oq*sizeof(struct sense));
        if(q->sns==NULL)
            return -1;
        zeroSenses(q->sns,tones*oq,"qs");

        if(q->snsMm!=NULL)
            free(q->snsMm);



        q->snsMm=(struct sense*)malloc(tones*oq*sizeof(struct sense));
        if(q->snsMm==NULL)
            return -1;
        zeroSenses(q->snsMm,tones*oq,"qsMm");

        if(q->snsFade!=NULL)
            free(q->snsFade);
            
        q->snsFade=(struct sense*)malloc(tones*oq*sizeof(struct sense));
        if(q->snsFade==NULL)
            return -1;
        zeroSenses(q->snsFade,tones*oq,"qsFade");



        if(q->snsMm05!=NULL)
            free(q->snsMm05);
        q->snsMm05=(struct sense*)malloc(tones*oq*sizeof(struct sense));
        if(q->snsMm05==NULL)
            return -1;
        zeroSenses05(q->snsMm05,tones*oq,"qsMm05");

        if(q->snsDis!=NULL)
            free(q->snsDis);
        q->snsDis=(struct sense*)malloc(tones*oq*sizeof(struct sense));
        if(q->snsDis==NULL)
            return -1;
        zeroSenses(q->snsDis,tones*oq,"qsDis");
        q->tones=tones;
        q->oqs=oq;
        q->bufsize=oq*tones;
        return 0;
    }
    q->tones=tones;
    q->oqs=oq;
    return 0;
}

void setQs(struct qs*r,int t,int oq,double value){
    int adr;
    if(t>=r->tones || oq>=r->oqs ||t<0||oq<0)
        return;
    
    adr=t+oq*(r->tones);
 //   soft
    //r->sns[adr].c.on=1;

    r->ks[adr]=senseValue(&(r->sns[adr]),value);
}


void setQsDis(struct qs*r,int t,int oq,double value){
    int adr;
    if(t>=r->tones || oq>=r->oqs ||t<0||oq<0)
        return;
    
    adr=t+oq*(r->tones);
 //   soft
    r->snsDis[adr].c.on=1;

    r->dis[adr]=senseValue(&(r->snsDis[adr]),value);
}
void setQsMm(struct qs*r,int t,int oq,double value){
    int adr;
    if(t>=r->tones || oq>=r->oqs ||t<0||oq<0)
        return;
    
    adr=t+oq*(r->tones);
 //   soft
   r->snsMm[adr].c.on=1;
   r->snsMm05[adr].c.on=1;
   r->mm[adr]=senseValue(&(r->snsMm[adr]),value);
   r->mm05[adr]=senseValue(&(r->snsMm05[adr]),value);

}

/*
void setQsDis(struct qs*r,int t,int oq,double value,double soft){
    int adr;
    if(t>=r->tones || oq>=r->oqs ||t<0||oq<0)
        return;
    
    adr=t+oq*(r->tones);
 //   soft
    r->snsDis[adr].soft=soft;
    r->snsDis[adr].c.on=1;
    r->dis[adr]=senseValue(&(r->snsDis[adr]),value);
}

*/

void a2tq(int a,int *t,int *q,int tones,double soft){
    *q=0;
    while(a<0){
        *q=(*q)-1;
        a=a+tones;    
    }
    *t=a%tones;
    *q=*q+a/tones;
}

double qs_a[20480];
double qs_fr[20480];

void detectOkToneLike(double freq,int&ok,int&tone,double&like);
double getToneFreq(int oq,int t);
void speq2qs(double*sound_a,double*freqs,int n,int tones,int minoq,int maxoq,struct qs*r){
    int i;
    double summ,skipValue;
    int col,t,oq,startSkip;
    int lt,loq;
    double like;
    r->zeroFreq=getToneFreq(minoq,0);
    for(i=0;i<n;i++){
   //     fprintf(stderr,"(freq=%3.1f amp=%3.1f)",freqs[i],sound_a[i]);
    
    }
    //fprintf(stderr,"\n\n\n\n");
    //fflush(stderr);
    lt=-1;
    loq=-1;
    tones=12;//QBUG
    startSkip=minoq*tones-1;
    skipValue=0.;
    reallocQs(r,tones,maxoq-minoq+1);
    col=0;
    summ=0;
    like=1.;
    double mlike=10.;
    for(i=0;i<n;i++){
        if(freqs[i]<0.001)
            continue;
    //    t=detectTone(freqs[i]);          
  //      oq=detectOk(freqs[i]);
//        like=detectOk(freqs[i]);
          detectOkToneLike(freqs[i],oq,t,like);
        if(t==lt&&oq==loq){
            summ+=sound_a[i]/like;
            col++;
            if(like<mlike){
                //col=1;        
                mlike=like;
            }
        }else{
            mlike=like;
            if(lt!=-1 && col!=0){
                if(loq>=minoq&&loq<=maxoq){
                    int la,a;
                    double v;
                    v=summ;///col;
                    la=lt+loq*tones;
              //      if(startSkip!=-1000){
                //           for(int i=startSkip;i<startSkip-1/*la*/;i++){
                  //          int tt,qq;
                    //        a2tq(i,&tt,&qq,tones);
                      //      setQs(r,tt,qq-minoq,((la-i)*skipValue +  (i-startSkip)*v)/(la-startSkip+1));
                        //}
                    
                 //   }
                    
                    //a=t+oq*tones;
                    if(a-la>1){
                        startSkip=la+1;
                        skipValue=v;
                    }else{
                        startSkip=-1000;
                    }
                    //r->sns[]soft
                    setQs(r,lt,loq-minoq,v);
                
                
                
                }
            }
            col=1;
            summ=sound_a[i];
            lt=t;
            loq=oq;
        }
    }
    
    if(lt!=-1 && col!=0){
        if(loq>=minoq&&loq<=maxoq){
                double v;
                int la;
                v=summ/col;
                la=lt+loq*tones;
  //              if(startSkip!=-1000){
//                    for(int i=startSkip;i<startSkip-1/*la*/;i++){
      //                  int tt,qq;
    //                    a2tq(i,&tt,&qq,tones);
        //                setQs(r,tt,qq-minoq,((la-i)*skipValue +  (i-startSkip)*v)/(la-startSkip+1));
          //          }
                
            //    }
    
        
              setQs(r,lt,loq-minoq,v);
        }
    }
    nearbySenses(r->sns,r->oqs*(int)r->tones,1./12.);

    nearbySenses(r->snsMm,r->oqs*(int)r->tones,1./12.);
    nearbySenses(r->snsMm05,r->oqs*(int)r->tones,1./12.);
    nearbySenses(r->snsDis,r->oqs*(int)r->tones,1./12.);
  //  for(int i=0;i<24;i++){
        
//        nearbySenses(r->dlinDisesSns[i],r->oqs*(int)r->tones,1./12.);

    //}
}
void speq2qs(double*sound_a,double*freqs,double*b_sound_a,double*b_freqs,int n,int tones,int minoq,int maxoq,struct qs*r){
    int i;
    double summ,skipValue;
    int col,t,oq,startSkip;
    int lt,loq;
    
    int c1,c2,c;
    c1=0;c2=0;c=0;
    double bl=1080;
//    fprintf(stderr,"speq2qs\n");
  //  fflush(stderr);
    
    while(b_freqs[c2]<bl){
        //if(b_freqs[c2]<b_freqs[c1]){
            qs_a[c]=b_sound_a[c2];
            qs_fr[c]=b_freqs[c2];
            c2++;
            c++;
       // }else{
         //   qs_a[c]=sound_a[c1];
           // qs_fr[c]=freqs[c1];
           // c1++;
           // c++;
       // }
    }
    while(freqs[c1]<bl && c1<n){
        c1++;
    }

    while(c1<n){
        qs_a[c]=sound_a[c1];
        qs_fr[c]=freqs[c1];
        c1++;
        c++;
    }    
    
    n=c;
    sound_a=qs_a;
    freqs=qs_fr;
    speq2qs(qs_a,qs_fr,c,tones,minoq,maxoq,r);
}
void speq2qs(double*sound_a,double*freqs,double*b_sound_a,double*b_freqs,double*c_sound_a,double*c_freqs,int n,int tones,int minoq,int maxoq,struct qs*r){
    int i;
    double summ,skipValue;
    int col,t,oq,startSkip;
    int lt,loq;
    
    int c1,c2,c,c3;
    c1=0;c2=0;c=0;c3=0;
    double bl=1080;
    double cl=1000/8;
//    fprintf(stderr,"speq2qs\n");
  //  fflush(stderr);
    while(c_freqs[c3]<cl){
            qs_a[c]=c_sound_a[c3];
            qs_fr[c]=c_freqs[c3];
            c3++;
            c++;
    }
    while(freqs[c2]<cl && c2<n){
        c2++;
    }
    while(b_freqs[c2]<bl){
            qs_a[c]=b_sound_a[c2];
            qs_fr[c]=b_freqs[c2];
            c2++;
            c++;
    }
    while(freqs[c1]<bl && c1<n){
        c1++;
    }

    while(c1<n){
        qs_a[c]=sound_a[c1];
        qs_fr[c]=freqs[c1];
        c1++;
        c++;
    }    
    
    n=c;
    sound_a=qs_a;
    freqs=qs_fr;
    speq2qs(qs_a,qs_fr,c,tones,minoq,maxoq,r);
}
void speq2qs(double*sound_a,double*freqs,double*b_sound_a,double*b_freqs,double*c_sound_a,double*c_freqs,double*d_sound_a,double*d_freqs,int n,int tones,int minoq,int maxoq,struct qs*r){
    int i;
    double summ,skipValue;
    int col,t,oq,startSkip;
    int lt,loq;
    
    int c1,c2,c,c3,c4;
    c1=0;c2=0;c=0;c3=0,c4=0;
    double bl=1300;
    double cl=625;
    double dl=210.;
//    fprintf(stderr,"speq2qs\n");
  //  fflush(stderr);
    while(d_freqs[c4]<dl){
            qs_a[c]=d_sound_a[c4];
            qs_fr[c]=d_freqs[c4];
            c4++;
            c++;
    }
    while(c_freqs[c3]<dl && c3<n){
        c3++;
    }
    
    while(c_freqs[c3]<cl){
            qs_a[c]=c_sound_a[c3];
            qs_fr[c]=c_freqs[c3];
            c3++;
            c++;
    }
    while(b_freqs[c2]<cl && c2<n){
        c2++;
    }
    while(b_freqs[c2]<bl){
            qs_a[c]=b_sound_a[c2];
            qs_fr[c]=b_freqs[c2];
            c2++;
            c++;
    }
    while(freqs[c1]<bl && c1<n){
        c1++;
    }

    while(c1<n){
        qs_a[c]=sound_a[c1];
        qs_fr[c]=freqs[c1];
        c1++;
        c++;
    }    
    
    n=c;
    sound_a=qs_a;
    freqs=qs_fr;
//    fprintf(stderr,"\n\n\n\nfreqs start=============================\n");

  //  for(i=0;i<c-1;i++){
   //     fprintf(stderr,"%3.2f( %3.2f )\n",qs_fr[i],qs_fr[i+1]/qs_fr[i]);
    
   // }
    //fprintf(stderr,"freqs end=============================\n\n\n\n");
    
    speq2qs(qs_a,qs_fr,c,tones,minoq,maxoq,r);
}



double getQs(struct qs*r,int t,int oq){
    int adr;
    //if(t==r->tones){
    //    return 1.;
   // } 
    if(oq<0 || t<0||t>=r->tones || oq>=r->oqs)
        return 0.;
    
    adr=t+oq*(r->tones);
    return r->ks[adr];
}
double getQsDis(struct qs*r,int t,int oq){
    int adr;
    if(t>=r->tones || oq>=r->oqs)
        return 0.;
    
    adr=t+oq*(r->tones);
    return r->dis[adr];
}
double getQsMm(struct qs*r,int t,int oq){
    int adr;
    if(t>=r->tones || oq>=r->oqs)
        return 0.;
    
    adr=t+oq*(r->tones);
    return r->mm[adr];
}
double getQsMm05(struct qs*r,int t,int oq){
    int adr;
    if(t>=r->tones || oq>=r->oqs)
        return 0.;
    
    adr=t+oq*(r->tones);
    return r->mm05[adr];
}

#include"cos.cpp"
#include"colors.cpp"
struct sense css;    
int zero=1;
void truncNotImportant(struct qs *s,double d){
    int i,j;
    for(j=0;j<s->oqs;j++)
        for(i=0;i<s->tones;i++){
            double a,b;
            int adr;
            adr=i+j*(s->tones);
            a=s->ks[adr];
            b=a-d;
            if(b<0.)
                b=0.;
            if(d<1.){
                b=b/(1.-d);
            }else{
                b=0;
            }
            s->ks[adr]=b;
        
        }
}
void drawQs(SDL_Surface*screen,int x1,int y1,int x2,int y2,struct qs *s){
    int i,j,w,h;
    Uint32 c;
    double t;
  //  if(zero){
    //    zero=0;
     //   zeroSense(&css);
    
  //  }
    //t=findCos(*s);
   // t=senseValue(&css,t);
      
    
    w=(x2-x1)/s->tones;
    h=(y2-y1)/s->oqs;
//    printf("COS:%f\n",t);
   // drawLine(screen,x2,y1 + (1- t)*(y2-y1),x2,y2, WHITE);    
    for(j=0;j<s->oqs;j++)
        for(i=0;i<s->tones;i++){
            double a,b;
            a=getQs(s,i,j);
           // b=a-d;
           // if(b<0.)
            //    b=0.;
           // b=b/(1-d);
     //       if(a>=0.&&a<=1.){
                c=a*255;
                c=c|c*256|c*256*256;
            
               // if(a>=d)
                bar(screen,x1+w*i +w/3,y2-h*(j+1) +h/3,x1+w*(i+1)-w/3,y2-h*(j)-h/3,c);    
       //     }
        }
}

void drawQsDis(SDL_Surface*screen,int x1,int y1,int x2,int y2){
    int i,h,w;
    double alld=0;
    h=abs(y1-y2);
    w=abs(x1-x2);
    for(i=0;i<DISES;i++){
        double a;
        a=diss[i];
        bar(screen,x1+i*w/DISES,y1+(1-a)*h,x1+(i+1)*w/DISES,y2,GRAY);
    
    }
}


#endif

void speq2qs(double*sound_a,double*freqs,int n,int tones,int minoq,int maxoq,struct qs*r);

