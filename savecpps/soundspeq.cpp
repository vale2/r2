#ifdef GLBILD
#include "mygl.h"
#define NGAR 6
#define MAXTONEHEIGHT 1500


void freqInGarLowHiKoef(int cur,int gr,double*freqs,double*amps,double*sumAmps,int n,double*low,double*hi,double*koefsLo,double*koefsHi,int*ampNum,int&koefnum);


void plate(double x1,double y1,double z1,struct rgb c1,
double x2,double y2,double z2,struct rgb c2,
double x3,double y3,double z3,struct rgb c3,
double x4,double y4,double z4,struct rgb c4);
void plate(double x1,double y1,double z1,struct rgb c1,
double x2,double y2,double z2,struct rgb c2,
double x3,double y3,double z3,struct rgb c3);
void plate(double x1,double y1,double z1,struct rgb c1,
double x2,double y2,double z2,struct rgb c2);
struct soundSpeq{
    int initKos;
    
    double spUp;
    double spDown;
    double *maxAmps;
    double *maxKos;
    double *minKos;
    double *freqs;
    double *amps;
    double *neamps;
    double *sumAmps;
    double *maxGar;
    double *kos;
    double *mam;
    double *gar;
    double *garHi;
    double *maxGarHi;
    double *fade;

    double**findKosKoef;
    int **findKosNum;
    int *findKosN;


    double**findGarKoefLo;
    double**findGarKoefHi;
    int **findGarNum;
    int *findGarN;

    int n;    
}ssp1;
void ssp2frafr(struct soundSpeq & ssp);
void playMyPlay();



double gz2mel(double gz){

    return 100* (13*atan(0.76*gz/1000)+3.5*atan((gz/7500)*(gz/7500)));///https://ru.wikipedia.org/wiki/%D0%91%D0%B0%D1%80%D0%BA_%28%D0%B2%D1%8B%D1%81%D0%BE%D1%82%D0%B0_%D0%B7%D0%B2%D1%83%D0%BA%D0%B0%29
    
    ////////////


    if(gz<20)
        return 0;
    if(gz<50)
        return (gz-20)/30*1000/6.;
    if(gz<200){
        return 1000/6.+ ((gz-50)/150*(1000/4.-1000/6.));  
    }
    if(gz<500){
        return 1000/4. +  (gz-200)/300. * (1000*0.55 - 1000/4.);
    
    }
    if(gz<1000){
        return 1000*0.55 +  (gz-500)/500. * (1000*0.45);
    
    }
    if(gz<2000){
       return 1000 +  (gz-1000)/1000. * (1000*0.47);
    }
    if(gz<5000){
       return 1000*1.47 +  (gz-2000)/3000. * (1000*(2.2-1.47));
    }
    if(gz<10000){
       return 1000*2.2 +  (gz-5000)/5000. * (3000-2200);
    }
    return 3000 +  (gz-10000)/10000. * (800);
}

double mel2gz(double mel){


    double l,r;
    double m,v;
    l=0;
    r=44000;
    while(r-l>(l+r)/200.){
        m=(l+r)/2;
        v=gz2mel(m);
        
        if(v>mel){
            r=m;
        }else{
            l=m;
        }    
    }
    return (l+r)/2;
}

double crw[2000];
double critWidth(double freq){
    int n;
    n=freq/45000*2000;
    if(crw[n]<0.1){
    
        double a,l,r,w;
        a=gz2mel(freq);
        l=mel2gz(a-50);
        r=mel2gz(a+50);
       
      // if(r<10000){
       
        w=r-l;
      // }else{
      //    w=1000000;
       //} 
        crw[n]=w;
        return w;
    }
    return crw[n];

}
double dis(double step,double width){
    step/=width;
    if(step<0.2*0.44)
        return step/(0.2*0.44)*0.6;
    if(step<0.2*3./5.)
        return 0.6+ (step-0.2*0.44)/(0.2*3./5.-0.2*0.44)*0.2;
    
    if(step<0.225)
        return 0.8+ (step-0.2*3./5.)/(0.225-0.2*3./5.)*0.2;
    
    if(step<0.4)
        return 1- (step-0.225)/(0.4-0.225)*0.25;

    if(step<0.6)
        return 1-0.25 - (step-0.4)/(0.2)*0.4;
            
    if(step<0.8)
        return 1-0.65 - (step-0.6)/(0.2)*0.23;
    if(step<1.)
        return 1-0.88 - (step-0.8)/(0.2)*0.1;

    if(step<1.2)
        return 1-0.98 - (step-1.0)/(0.2)*0.02;
    
    return 0;    
    
    
}
double findKos(double*freqs,double*amps,int n,int ii){
    double r,myfreq,w,step;
    double *freqsii,*ampsii;
    r=0;
    int i,col;
    col=0;
    freqsii=freqs;
    ampsii=amps;
    freqsii--;
    ampsii--;
    myfreq=freqs[0];
    freqs++;
    amps++;
    for(i=1;i<n;i++,freqs++,amps++){
        w=critWidth((myfreq+*freqs)/2);
        step=*freqs-myfreq;
        r+=dis(step,w)* *amps;
        col++;
        if(step>w*1.2)
            break;
    }
    for(i=1;i<ii;i++,freqsii--,ampsii--){
        w=critWidth((myfreq+*freqsii)/2);
        step=myfreq-*freqsii;
        r+=dis(step,w)* *ampsii;
        col++;
        if(step>w*1.2)
            break;
    }
    if(col!=0)
        return -r/col;
    else
        return 0;

}
double calcfindKosKoefs(struct soundSpeq &ssp1,int n){
    double r=0.;
    double rd=0.;
    int i;
    for(i=0;i<ssp1.findKosN[n];i++){
        r+=ssp1.findKosKoef[n][i]*ssp1.amps[ssp1.findKosNum[n][i]];
        rd+=ssp1.amps[ssp1.findKosNum[n][i]];
    
    }
    if(rd>0.0001)
        return r*ssp1.findKosN[n]/rd;
    return 0;;
/*
        ssp.findKosKoef=(double*)malloc(num*sizeof(double));
        ssp.findKosNum=(int*)malloc(num*sizeof(int));
        ssp.findKosN=num;

*/
}

void calcFreqInGar(struct soundSpeq &ssp,int n,int gr,double &rrll,double &rrhh){
    double rl=0.,rh=0;
    int i;
    int nu,l,r;
    
    for(i=0;i<ssp.findGarN[n*NGAR+gr];i++){
             nu=ssp.findGarNum[n*NGAR+gr][i];
             if(nu>=0){
                rl+=ssp.findGarKoefLo[n*NGAR+gr][i]*ssp.amps[nu];
                rh+=ssp.findGarKoefHi[n*NGAR+gr][i]*ssp.amps[nu];
                   
             
             }else{
              // fprintf(stderr,"nu:%d ",nu);
               //   ampNum[koefnum]=-r1*n-l0-1;
                  nu++;
                  nu=-nu;
                  r=(nu)/ssp.n;
                  l=nu%ssp.n;
                //  fprintf(stderr,"(%d %d)\n",l,r);

                  rl+=(ssp.sumAmps[r]-ssp.sumAmps[l])*ssp.findGarKoefLo[n*NGAR+gr][i];
                  rh+=(ssp.sumAmps[r]-ssp.sumAmps[l])*ssp.findGarKoefHi[n*NGAR+gr][i];
                  
             }
             
    }
   rrll=rl;
   rrhh=rh;
///    return r;
/*
        ssp.findKosKoef=(double*)malloc(num*sizeof(double));
        ssp.findKosNum=(int*)malloc(num*sizeof(int));
        ssp.findKosN=num;

*/
}
double findKosKoefs(double*freqs,double*amps,int n,int ii,double*koefs,int *ampNum,int &nkoefs){
    double r,myfreq,w,step, ko;
    double *freqsii,*ampsii;
    r=0;
    int i,col;
    col=0;
    freqsii=freqs;
    ampsii=amps;
    freqsii--;
    ampsii--;
    myfreq=freqs[0];
    freqs++;
    amps++;
    nkoefs=0;
    for(i=1;i<n;i++,freqs++,amps++){
        w=critWidth((myfreq+*freqs)/2);
        step=*freqs-myfreq;
        ko=dis(step,w);
        if(fabs(ko)>0.000001){
            koefs[nkoefs]=ko;
            ampNum[nkoefs]=i+ii;
            nkoefs++;
        }
        
        
        r+=ko * *amps;
        col++;
        if(step>w*1.2)
            break;
    }
    for(i=1;i<ii;i++,freqsii--,ampsii--){
        w=critWidth((myfreq+*freqsii)/2);
        step=myfreq-*freqsii;

        ko=dis(step,w);
        if(fabs(ko)>0.000001){
            koefs[nkoefs]=ko;
            ampNum[nkoefs]=ii-i;
            nkoefs++;

        }
        r+=ko* *ampsii;
        col++;
        if(step>w*1.2)
            break;
    }
    
    if(col!=0){
     //   fprintf(stderr,"%d\n",nkoefs);
        for(i=0;i<nkoefs;i++){
            koefs[i]/=-col;
        }

        return -r/col;
    }
    else
        return 0;

}

void initSsp(struct soundSpeq & ssp,int n){
    fprintf(stderr,"initSsp:%d freqs\n",n);
    ssp.initKos=0;
    ssp.spUp=0;
    ssp.spDown=0;
    ssp.amps=(double*)malloc(n*sizeof(double));
    ssp.neamps=(double*)malloc(n*sizeof(double));


    ssp.sumAmps=(double*)malloc(n*sizeof(double));
    
    ssp.maxAmps=(double*)malloc(n*sizeof(double));
    ssp.freqs=(double*)malloc(n*sizeof(double));;
    ssp.kos=(double*)malloc(n*sizeof(double));;
    ssp.mam=(double*)malloc(NGAR*n*sizeof(double));;

    ssp.maxKos=(double*)malloc(n*sizeof(double));;
    ssp.minKos=(double*)malloc(n*sizeof(double));;

    ssp.fade=(double*)malloc(n*sizeof(double));

    ssp.gar=(double*)malloc(NGAR*n*sizeof(double));
    ssp.maxGar=(double*)malloc(NGAR*n*sizeof(double));
    ssp.garHi=(double*)malloc(NGAR*n*sizeof(double));
    ssp.maxGarHi=(double*)malloc(NGAR*n*sizeof(double));
    
    ssp.findKosKoef=(double**)malloc(n*sizeof(double*));
    ssp.findKosNum=(int**)malloc(n*sizeof(int*));

    ssp.findKosN=(int*)malloc(n*sizeof(int));


    ssp.findGarKoefLo=(double**)malloc(NGAR*n*sizeof(double*));
    ssp.findGarKoefHi=(double**)malloc(NGAR*n*sizeof(double*));

    ssp.findGarNum=(int**)malloc(NGAR*n*sizeof(int*));

    ssp.findGarN=(int*)malloc(NGAR*n*sizeof(int));



    ssp.n=n;
    int  i;
    for(i=0;i<n;i++){
        ssp.maxKos[i]=0;
        ssp.minKos[i]=-0.7;
        ssp.maxAmps[i]=0.1;
        for(int j=0;j<NGAR;j++){
            ssp.maxGar[i*NGAR+j]=0.1;
            ssp.maxGarHi[i*NGAR+j]=0.1;

        }
        
    }

    
    
}


void initFreqInGar(struct soundSpeq & ssp){
    double koefsLo[4096];
    double koefsHi[4096];
    int koefnum[4096];
    int num;
   for(i=0;i<ssp.n;i++){
       for(int j=0;j<NGAR;j++){
            if(ssp.freqs[i]/(j+1)<MAXTONEHEIGHT  && ssp.freqs[i]/(j+1)>20) {
                double gr,gr2;
                freqInGarLowHiKoef(i,j,ssp.freqs,ssp.amps,ssp.sumAmps,ssp.n,&gr,&gr2,koefsLo,koefsHi,koefnum,num);

                ssp.findGarKoefLo[i*NGAR+j]=(double*)malloc(num*sizeof(double));
                ssp.findGarKoefHi[i*NGAR+j]=(double*)malloc(num*sizeof(double));
                
                ssp.findGarNum[i*NGAR+j]=(int*)malloc(num*sizeof(int));
                ssp.findGarN[i*NGAR+j]=num;
                
                memcpy(ssp.findGarKoefLo[i*NGAR+j],koefsLo,num*sizeof(double));
                memcpy(ssp.findGarKoefHi[i*NGAR+j],koefsHi,num*sizeof(double));

                memcpy(ssp.findGarNum[i*NGAR+j],koefnum,num*sizeof(int));
          
             
             
            
            
    
          
            }
        }
    }


}
void initFindKos(struct soundSpeq & ssp){
    double koefs[ssp.n];
    int koefnum[ssp.n];
    int num;
    for(i=0;i<ssp.n;i++){
        findKosKoefs(ssp.freqs+i,ssp.amps+i,ssp.n-i,i,koefs,koefnum,num);
        ssp.findKosKoef[i]=(double*)malloc(num*sizeof(double));
        ssp.findKosNum[i]=(int*)malloc(num*sizeof(int));
        ssp.findKosN[i]=num;
        memcpy(ssp.findKosKoef[i],koefs,num*sizeof(double));
        memcpy(ssp.findKosNum[i],koefnum,num*sizeof(int));
        
    }


}

int findLowHighfreqpri=0;
void findLowHighfreq(double freq,double*freqs,int n,int&ll,int&rr){
    int l,r,m;
    l=0;
    r=n-1;
    while(r>l+1){
         m=(l+r)/2;
    //    if(findLowHighfreqpri)
      //      fprintf(stderr,"((%lf %lf))\n",freqs[m],freq);

         if(freqs[m]>freq){
            r=m;
         }else{
            l=m;
         }
    }
//    if(findLowHighfreqpri)
  //      fprintf(stderr,"((%d %d))\n",r,l);
    rr=r;
    ll=l;
}
double interFreqAmp(double freq,double *freqs,double*amps,int n){
    int r,l;
//    l=findLowfreq(freq,freqs,n);
  //  r=findHifreq(freq,freqs,n);
    findLowHighfreq(freq,freqs,n,l,r);
    return (amps[l]*(freq-freqs[l]) + amps[r]*(freqs[r]-freq))/(freqs[r]-freqs[l]);
}

double interFreqKosAve(double freq1,double freq2,double *freqs,double*amps,double*kos,int n){
    int r0,l0,r1,l1,i;
    findLowHighfreq(freq1,freqs,n,l0,r0);
    findLowHighfreq(freq1,freqs,n,l1,r1);
    double res,dd;
    res=0;
    dd=0;
    if(r1-l0>0){
        for(i=l0;i<r1;i++){
                res+=kos[i]*amps[i];
                dd+=amps[i];
        }
        if(dd>0.000001){
            return res/(dd);
        }else
            return 0;
    }else{
        return 0;
    
    }
}

double interFreqAmpMax(double freq1,double freq2,double *freqs,double*amps,int n){
    int r0,l0,r1,l1,i;
    findLowHighfreq(freq1,freqs,n,l0,r0);
    findLowHighfreq(freq1,freqs,n,l1,r1);
    double res;
    res=0;
    for(i=l0;i<r1;i++)
        if(res<amps[i])
            res=amps[i];
    return res;
}
double interFreqAmpSum(double freq1,double freq2,double *freqs,double*sumAmps,int n){
    int r0,l0,r1,l1,i;
    findLowHighfreq(freq1,freqs,n,l0,r0);
    findLowHighfreq(freq1,freqs,n,l1,r1);
//    double res;
  //  res=0;
//    for(i=l0;i<r1;i++)
  //      if(res<amps[i])
    //        res=amps[i];
//    if(r1!=l0)
    return sumAmps[r1]-sumAmps[l0];
}
double interFreqAmpSumAve(double freq1,double freq2,double *freqs,double*sumAmps,int n){
    int r0,l0,r1,l1,i;
    findLowHighfreq(freq1,freqs,n,l0,r0);
    findLowHighfreq(freq2,freqs,n,l1,r1);
//    double res;
  //  res=0;
//    for(i=l0;i<r1;i++)
  //      if(res<amps[i])
    //        res=amps[i];
    if(r1>l0)
        return (sumAmps[r1]-sumAmps[l0])/(r1-l0);
     return 0;
}

void freqInGarLowHi(int cur,int gr,double*freqs,double*amps,double*sumAmps,int n,double*low,double*hi){
    double rl,rh;
    double fr,fr0,fr1;
    int i;
    rl=0;
    rh=0;
    *low=rl;
    *hi=rh;

    if(cur==0){
        return;
    }
    if(cur==n-1){
        return;
    }
    fr=freqs[cur]/(gr+1);
    fr0=(freqs[cur-1]+freqs[cur])/2/(gr+1);
    fr1=(freqs[cur]+freqs[cur+1])/2/(gr+1);
    double v;
    
    for(i=0;i<gr;i++){
        v=interFreqAmp(fr*(i+1),freqs,amps,n);
        rh+=v*(i+1)/NGAR;
        rl+=v*(NGAR-i)/NGAR;
    
    }
    rh+=amps[cur]*(gr+1)/NGAR;
    rl+=amps[cur]*(NGAR-gr)/NGAR;
    for(i=gr+1;i<NGAR;i++){
        v=interFreqAmpSumAve(fr0*(i+1),fr1*(i+1),freqs,sumAmps,n);
        rh+=v*(i+1)/NGAR;
        rl+=v*(NGAR-i)/NGAR;
    }
    int r0,l0,r1,l1;
   // findLowHighfreq(fr0,freqs,n,l0,r0);
  //  findLowHighfreq(fr1*NGAR,freqs,n,l1,r1);
   // double rd;
   // rd=sumAmps[r1]-sumAmps[l0];
    //if(rd>0.001){
     //   rh=rh/rd;
     //   rl=rh/rd;
    
   // }else{
   //     rh=0;
   //     rl=0;
   // }
    *low=rl;
    *hi=rh;
    
}
void freqInGarLowHiKoef(int cur,int gr,double*freqs,double*amps,double*sumAmps,int n,double*low,double*hi,double*koefsLo,double*koefsHi,int*ampNum,int&koefnum){
    double rl,rh;
    double fr,fr0,fr1;
    int i;
    rl=0;
    rh=0;
    *low=rl;
    *hi=rh;
    koefnum=0;
    if(cur==0){
        return;
    }
    if(cur==n-1){
        return;
    }
//    fprintf(stderr,"freqs[cur] = %lf\n",freqs[cur]);
    
    fr=freqs[cur]/(gr+1);
    fr0=(freqs[cur-1]+freqs[cur])/2/(gr+1);
    fr1=(freqs[cur]+freqs[cur+1])/2/(gr+1);
  //  fprintf(stderr,"fr0 = %lf fr1=%lf \n",fr0,fr1);

    double v;
    
    for(i=0;i<gr;i++){
        int r,l;
        double freq;
        freq=fr*(i+1);
        findLowHighfreq(freq,freqs,n,l,r);
        ampNum[koefnum]=l;
        koefsLo[koefnum]=((freq-freqs[l])/(freqs[r]-freqs[l]))*(NGAR-i)/NGAR;
//        koefsLo[koefnum]=((freq-freqs[l])/(freqs[r]-freqs[l]))/NGAR;
        koefsHi[koefnum]=((freq-freqs[l])/(freqs[r]-freqs[l]))*(i+1)/NGAR;
        koefnum++;
        ampNum[koefnum]=r;
  //      koefsLo[koefnum]=((freqs[r]-freq)/(freqs[r]-freqs[l]))*(NGAR-i)/NGAR;
        koefsLo[koefnum]=((freqs[r]-freq)/(freqs[r]-freqs[l]))/NGAR;
        koefsHi[koefnum]=((freqs[r]-freq)/(freqs[r]-freqs[l]))*(i+1)/NGAR;
        koefnum++;
        
//        l , (freq-freqs[l])/(freqs[r]-freqs[l]); 
 //       r, freqs[r]-freq))/(freqs[r]-freqs[l]);
//        
        
    
  //      v=interFreqAmp(,freqs,amps,n,);
    //    rh+=v*(i+1)/NGAR;
      //  rl+=v;
    
    }
    ampNum[koefnum]=cur;
//    koefsLo[koefnum]=(NGAR-gr)/NGAR;
    koefsLo[koefnum]=1./NGAR;//(NGAR-gr)/NGAR;
    koefsHi[koefnum]=(gr+1)/NGAR;
    koefnum++;
    
    
    for(i=gr+1;i<NGAR;i++){
        int r0,l0,r1,l1;
//        double freq1;
  //      freq1=fr*(i+1);
//findLowHighfreqpri=1;
      //  fprintf(stderr,"[%lf %lf]\n",fr0*(i+1),fr1*(i+1));
    //fprintf(stderr,"fr0 = %lf fr1=%lf \n",fr0,fr1);
  //  fprintf(stderr,"i = %d \n",i);

        findLowHighfreq(fr0*(i+1),freqs,n,l0,r0);
        findLowHighfreq(fr1*(i+1),freqs,n,l1,r1);
//findLowHighfreqpri=0;

        if(r1>l0){
    //        fprintf(stderr,"%d %d\n",r1,l0);
      //      fprintf(stderr,"%lf %lf\n",fr0,fr1);
            ampNum[koefnum]=-r1*n-l0-1;
//            koefsLo[koefnum]=(NGAR-i)/(r1-l0)/NGAR;
            koefsLo[koefnum]=1./(r1-l0)/NGAR;
            koefsHi[koefnum]=(i+1)/(r1-l0)/NGAR;
            koefnum++;
        }
    }
}

double freqInGarHi(int cur,int gr,double*freqs,double*amps,double*sumAmps,int n){
    double r;
    double fr,fr0,fr1;
        int i;
    r=0;    
    if(cur==0)
        return 0;
    if(cur==n-1)
        return 0;
    fr=freqs[cur]/(gr+1);
    fr0=(freqs[cur-1]+freqs[cur])/2/(gr+1);
    fr1=(freqs[cur]+freqs[cur+1])/2/(gr+1);
    
    for(i=0;i<gr;i++){
        r+=interFreqAmp(fr*(i+1),freqs,amps,n)*(i+1)/NGAR;
    
    }
    r+=amps[cur]*(gr+1)/NGAR;
    for(i=gr+1;i<NGAR;i++){
        r+=interFreqAmpSum(fr0*(i+1),fr1*(i+1),freqs,sumAmps,n)*(i+1)/NGAR;
    }
    int r0,l0,r1,l1;
    findLowHighfreq(fr0,freqs,n,l0,r0);
    findLowHighfreq(fr1*NGAR,freqs,n,l1,r1);
    double rd;
    rd=sumAmps[r1]-sumAmps[l0];
    if(rd>0.001){
        r=r/rd;
    
    }else
        r=0;
    
    return r;
}
double freqInGar(int cur,int gr,double*freqs,double*amps,double*sumAmps,int n){
    double r;
    double fr,fr0,fr1;
    int i;
    r=0;
    if(cur==0)
        return 0;
    if(cur==n-1)
        return 0;
    fr=freqs[cur]/(gr+1);
    fr0=(freqs[cur-1]+freqs[cur])/2/(gr+1);
    fr1=(freqs[cur]+freqs[cur+1])/2/(gr+1);
    
    for(i=0;i<gr;i++){
        r+=interFreqAmp(fr*(i+1),freqs,amps,n)*(NGAR-i)/NGAR;
    
    }
    r+=amps[cur]*(NGAR-gr)/NGAR;
    for(i=gr+1;i<NGAR;i++){
        r+=interFreqAmpSum(fr0*(i+1),fr1*(i+1),freqs,sumAmps,n)*(NGAR-i)/NGAR;
    }
    int r0,l0,r1,l1;
    findLowHighfreq(fr0,freqs,n,l0,r0);
    findLowHighfreq(fr1*NGAR,freqs,n,l1,r1);
    double rd;
    rd=sumAmps[r1]-sumAmps[l0];
    if(rd>0.001){
        r=r/rd;
    
    }else
        r=0;
    
    return r;
}
double oldFreqInGar(int cur,int gr,double*freqs,double*amps,int n){
    double r;
    double fr,fr0,fr1;
    int i;
    
    if(cur==0)
        return 0;
    if(cur==n-1)
        return 0;
    fr=freqs[cur]/(gr+1);
    fr0=(freqs[cur-1]+freqs[cur])/2/(gr+1);
    fr1=(freqs[cur]+freqs[cur+1])/2/(gr+1);
    
    for(i=0;i<gr;i++){
        r+=interFreqAmp(fr*(i+1),freqs,amps,n)*(NGAR-i)/NGAR;
    
    }
    
    for(i=gr+1;i<NGAR;i++){
        r+=interFreqAmpMax(fr0*(i+1),fr1*(i+1),freqs,amps,n)*(NGAR-i)/NGAR;
    }
    return r/(NGAR-1);
}
double findMam(int cur,int gr,double*freqs,double*amps,double *kos,int n){
    double r;
    double fr,fr0,fr1;
    int i;
    if(cur==0)
        return 0;
    if(cur==n-1)
        return 0;
    fr=freqs[cur]/(gr+1);
    fr0=(freqs[cur-1]+freqs[cur])/2/(gr+1);
    fr1=(freqs[cur]+freqs[cur+1])/2/(gr+1);
    
   return  amps[i] *(kos[i]/2-interFreqKosAve(fr0*(gr+2),fr1*(gr+2),freqs,amps,kos,n)/2)+0.5;
    

}
#define MINFREQ 64
#define MAXFREQ 10000
//double 


double myPow[9000];
double myPowGamma=0.;
double mpow[512][1024];
int mpowinit=0;
double mypow(double v,double p){
    return mpow[(int)(v*511.)][(int)(p*1023./3)];

}

void init_my_pow(double gamma){
    int i;
    if(fabs(myPowGamma-gamma)>0.000001){
        myPowGamma=gamma;
        for(i=0;i<9000;i++){
            myPow[i]=pow(i/4096.,gamma);
        }
    
    }
    if(mpowinit)
        return;
    mpowinit=1;
    int j;
    for(i=0;i<512;i++)
        for(j=0;j<1024;j++){
            mpow[i][j]=pow(i/511.,j*3./1023.);
        }

}
double my_pow(double a){
    if(a>2)
        return 2;
    return myPow[(int)(a*4096)];
}
void calcSoundSpeq(struct soundSpeq & ssp,double*amps,double*freqs,int n){
    int my_n=0;
    int i;
    double lfreq=0;
    double lamp;
    FILE*f;
    double spup,spdown,ampGamma;
    spup=getOpt("speedSpeqUp");
    spdown=getOpt("speedSpeqDown");
    ampGamma=getOpt("quickSpeqAmpGamma");
    init_my_pow(ampGamma);

    double neAmpSpeedUp=getOpt("neAmpSpeedUp");
    double neAmpSpeedDown=getOpt("neAmpSpeedDown");

    

    if(ssp.n==0){
        my_n=0;
        double lfreq,w;
        lfreq=0;
        f=fopen("ssp_freqs.txt","w");
        for(i=0;i<n;i++){
           if(freqs[i]<MINFREQ)
             continue;

            if(freqs[i]>MAXFREQ)
                break;
            w=critWidth((freqs[i]+lfreq)/2);
            
            if(freqs[i]-lfreq>w*0.02 && w<1000000-100){
                my_n++;
                if(f!=NULL){
                    fprintf(f,"freq=%lf ",freqs[i]);
                    fprintf(f,"w=%lf \n",w);
                
                }
                lfreq=freqs[i];
                
            }
            
        }
        initSsp(ssp,my_n);    
        if(f!=NULL)
            fclose(f);
    }
    my_n=0;
    double w;
    lfreq=0;
    double sumfreq=0;
    double freqnum=0;
    double my_amp=0;
    double calc_my_amp=0;
    double sumAmp=0;
    for(i=0;i<n;i++){
       if(freqs[i]<MINFREQ)
          continue;
        if(freqs[i]>MAXFREQ)
           break;
       
       if(my_n>=ssp.n)
            break;
       if(amps[i]>calc_my_amp){
            calc_my_amp=amps[i];
       }
       sumfreq+=freqs[i];
       freqnum+=1;

       w=critWidth((freqs[i]+lfreq)/2);
       if(freqs[i]-lfreq>w*0.02 && w<1000000-100){
            if(ssp.maxAmps[i]>0.001)
                ssp.maxAmps[i]*=0.9999;
            
            lfreq=freqs[i];
            ssp.freqs[my_n]=freqs[i];//sumfreq/freqnum;
            sumfreq=0;
            freqnum=0;
            
            my_amp=calc_my_amp;
            
            
            calc_my_amp=0;
            double newAmp,oldAmp,saveNewAmp;
            oldAmp=ssp.amps[my_n]*ssp.maxAmps[my_n];
            //newAmp=my_pow(my_amp/ssp.maxAmps[my_n])*ssp.maxAmps[my_n];
            newAmp=pow(my_amp/ssp.maxAmps[my_n],ampGamma)*ssp.maxAmps[my_n];
            
            saveNewAmp=newAmp;
            if(newAmp>oldAmp){
                newAmp=oldAmp*(spup)+newAmp*(1-spup);
            }else{
                newAmp=oldAmp*(spdown)+newAmp*(1-spdown);
            }
            if(ssp.maxAmps[my_n]<newAmp){
                ssp.maxAmps[my_n]=newAmp;
            }
            lamp=ssp.amps[my_n];
            
            ssp.amps[my_n]=newAmp/ssp.maxAmps[my_n];
            
          //  neAmpSpeedDown neAmpSpeedUp
            double nneamp;
            nneamp=(saveNewAmp-newAmp)/ssp.maxAmps[my_n];
            if(nneamp>ssp.neamps[my_n]){
                ssp.neamps[my_n]=ssp.neamps[my_n]*neAmpSpeedUp+nneamp*(1-neAmpSpeedUp);
            }else{
                ssp.neamps[my_n]=ssp.neamps[my_n]*neAmpSpeedDown+nneamp*(1-neAmpSpeedDown);
            }
            
            my_amp=ssp.amps[my_n];
            sumAmp+=ssp.amps[my_n];
            ssp.sumAmps[my_n]=sumAmp;
            if(my_amp>0.0001&&lamp>my_amp){
                ssp.fade[my_n]=my_amp/lamp;
            }
            
            else if(lamp>0.0001&&lamp<my_amp){
                ssp.fade[my_n]=lamp/my_amp;
            }            
            else
                ssp.fade[my_n]=0;
        
           my_n++;
       }
    }
    if(ssp.initKos==0){
        ssp.initKos=1;
        initFindKos(ssp);
        initFreqInGar(ssp);
    }
    
    for(i=0;i<ssp.n;i++){
        double kos;
        kos=calcfindKosKoefs(ssp,i);
        ssp.minKos[i]=ssp.minKos[i]*0.9999+ssp.maxKos[i]*0.0001;
        ssp.maxKos[i]=ssp.maxKos[i]*0.9999+ssp.minKos[i]*0.0001;
        
        if(ssp.maxKos[i]-ssp.minKos[i]<0.0001){
           ssp.maxKos[i]=ssp.minKos[i]+0.0001;
        }
        if(ssp.minKos[i]>kos){
            ssp.minKos[i]=kos;
        }
        if(ssp.maxKos[i]<kos){
            ssp.maxKos[i]=kos;
        }
        ssp.kos[i]=(kos-ssp.minKos[i])/(ssp.maxKos[i]-ssp.minKos[i]);
    }
    
    for(i=0;i<ssp.n;i++){
       for(int j=0;j<NGAR;j++){
            if(ssp.freqs[i]/(j+1)<MAXTONEHEIGHT  && ssp.freqs[i]/(j+1)>20) {
                double gr,gr2;
             //   freqInGarLowHi(i,j,ssp.freqs,ssp.amps,ssp.sumAmps,ssp.n,&gr,&gr2);
               calcFreqInGar(ssp,i,j,gr,gr2);
               
                if(gr>ssp.maxGar[i*NGAR+j]){
                    ssp.maxGar[i*NGAR+j]=gr;
                }
                ssp.gar[i*NGAR+j]=gr/ssp.maxGar[i*NGAR+j];
//                gr=freqInGarHi(i,j,ssp.freqs,ssp.amps,ssp.sumAmps,ssp.n);
                gr=gr2;
                if(gr>ssp.maxGarHi[i*NGAR+j]){
                    ssp.maxGarHi[i*NGAR+j]=gr;
                }
                ssp.garHi[i*NGAR+j]=gr/ssp.maxGarHi[i*NGAR+j];
                
                ssp.mam[i*NGAR+j]=findMam(i,j,ssp.freqs,ssp.amps,ssp.kos,ssp.n);
                
            }else{
                ssp.gar[i*NGAR+j]=0;
                ssp.garHi[i*NGAR+j]=0;
                ssp.mam[i*NGAR+j]=0.5;
            }
        }
    }
}


#include"my_glut32.cpp"
struct snoxel{
    double x,y,z;
    struct rgb c;
    struct rgb cp;
    struct rgb cpp;
 
    int gar;
    double freq;
    int  nfreq;
    double ps;
    double baseFreq;
    double baseCroma;   
}snoxels[5000];
int snoxelGar[1000][NGAR];
double cosChroma[3000];
double getCosChroma(double freq){
    int n;
    n=freq/45000*6000;
    if(n<0||n>3000)
        return 0;
    if(cosChroma[n]<0.1){
        double c1;
        c1=523.25;
        while(freq>=2*c1)
             freq/=2.;
        while(freq<c1)
            freq*=2;
        freq/=c1;
        cosChroma[n]=cos(2*M_PI*log(freq)/log(2.));
    }
    return cosChroma[n];   
}


double sinChroma[3000];
double getSinChroma(double freq){
    int n;
    n=freq/45000*6000;
    if(n<0||n>3000)
        return 0;
    if(sinChroma[n]<0.1){
        double c1;
        c1=523.25;
        while(freq>=2*c1)
             freq/=2.;
        while(freq<c1)
            freq*=2;
        freq/=c1;
        sinChroma[n]=sin(2*M_PI*log(freq)/log(2.));
    }
    return sinChroma[n];   
}



double chroma[3000];
double getChroma(double freq){
    int n;
    n=freq/45000*6000;
    if(n<0||n>3000)
        return 0;
    if(chroma[n]<0.1){
        double c1;
        c1=523.25;
        while(freq>=2*c1)
             freq/=2.;
        while(freq<c1)
            freq*=2;
        freq/=c1;
        chroma[n]=log(freq)/log(2.);
    }
    return chroma[n];   

}
/*
struct hsv_colour hmv_s2hsv(double heat,double mood,double value,double s){
    double h;
    struct hsv_colour r;
    r.s=s;
    r.v=v;
//    mood=(mood-0.5)*2;
    h=atan2()   
    
    

}*/
void snLine(struct snoxel a,struct snoxel b){
           if(a.c.o/2 +b.c.o/2>2){
           plate(
            a.x,a.y,a.z,a.c,
            b.x,b.y,b.z,b.c);            
     /*               glColor4ubv((const GLubyte*)&(a.c));
                    glVertex3f (a.x,a.y,a.z);
                    glColor4ubv((const GLubyte*)&(b.c));
                    glVertex3f (b.x,b.y,b.z);
       */         }
}
int findNfreq (struct soundSpeq*ssp,double freq){
    int r,l,m;
    l=0;r=ssp->n-1;
    while(r-l>1){
        m=(l+r)/2;
        if(ssp->freqs[m]>freq){
            r=m;
        }else
            l=m;
        
    }
    if(fabs(freq-ssp->freqs[r])>fabs(freq-ssp->freqs[l]))
        return l;
    return r;
}

int linkes[5000][10];
int linkn[5000];
void zeroLink(){
    int i;
    for(i=0;i<5000;i++)
        linkn[i]=0;

}
void addlink(int a,int b){
    if(linkn[a]<10){
        linkes[a][linkn[a]]=b;
        linkn[a]++;
    }

}

int plateSnoxels[16*16*16*6][4];
int plateSnoxelsN=0;

void drPlateSn(){
    for(int i=0;i<plateSnoxelsN;i++){
    int a,b,c,d;
        a=plateSnoxels[i][0];
        b=plateSnoxels[i][1];
        c=plateSnoxels[i][2];
        d=plateSnoxels[i][3];
        if(d>=0){
            if((int)snoxels[a].cp.o+(int)snoxels[b].cp.o+(int)snoxels[c].cp.o+(int)snoxels[d].cp.o>4)
             plate(
           snoxels[a].x,snoxels[a].y,snoxels[a].z,snoxels[a].cp,
           snoxels[b].x,snoxels[b].y,snoxels[b].z,snoxels[b].cp,
           snoxels[c].x,snoxels[c].y,snoxels[c].z,snoxels[c].cp,
           snoxels[d].x,snoxels[d].y,snoxels[d].z,snoxels[d].cp);
        }else{
            if((int)snoxels[a].cp.o+(int)snoxels[b].cp.o+(int)snoxels[c].cp.o>3)
             plate(
           snoxels[a].x,snoxels[a].y,snoxels[a].z,snoxels[a].cp,
           snoxels[b].x,snoxels[b].y,snoxels[b].z,snoxels[b].cp,
           snoxels[c].x,snoxels[c].y,snoxels[c].z,snoxels[c].cp);
        
        
        
        
        }
   }

}
void  plateSn(int a,int b,int c,int d){
  // if(snoxels[a].gar == snoxels[b].gar
  // &&snoxels[a].gar == snoxels[c].gar
  // &&snoxels[a].gar == snoxels[d].gar
  // )
   {
       plateSnoxels[plateSnoxelsN][0]=a;
       plateSnoxels[plateSnoxelsN][1]=b;
       plateSnoxels[plateSnoxelsN][2]=c;
       plateSnoxels[plateSnoxelsN][3]=d;
       plateSnoxelsN++;
   
   }
/*       plate(
       snoxels[a].x,snoxels[a].y,snoxels[a].z,snoxels[a].c,
       snoxels[b].x,snoxels[b].y,snoxels[b].z,snoxels[b].c,
       snoxels[c].x,snoxels[c].y,snoxels[c].z,snoxels[c].c,
       snoxels[d].x,snoxels[d].y,snoxels[d].z,snoxels[d].c);
*/
}
void  plateSn3(int a,int b,int c){
  // if(snoxels[a].gar == snoxels[b].gar
  // &&snoxels[a].gar == snoxels[c].gar
   //)
   {
       plateSnoxels[plateSnoxelsN][0]=a;
       plateSnoxels[plateSnoxelsN][1]=b;
       plateSnoxels[plateSnoxelsN][2]=c;
       plateSnoxels[plateSnoxelsN][3]=-1;

       plateSnoxelsN++;
   
   }
/*       plate(
       snoxels[a].x,snoxels[a].y,snoxels[a].z,snoxels[a].c,
       snoxels[b].x,snoxels[b].y,snoxels[b].z,snoxels[b].c,
       snoxels[c].x,snoxels[c].y,snoxels[c].z,snoxels[c].c,
       snoxels[d].x,snoxels[d].y,snoxels[d].z,snoxels[d].c);
*/
}
/*
4 0
3 1
2 2
1 3
0 4
*/

void add4cycle(int sn,int deep,int*buf,int old){
    if(deep>0){
        *buf=sn;
        for(int i=0;i<linkn[sn];i++){
            if(old!=linkes[sn][i])
                add4cycle(linkes[sn][i],deep-1,buf+1,sn);
        }
    }else{
        buf-=4;
        if(*buf==sn && sn<buf[1] &&sn <buf[3]&&sn <buf[2]){
            plateSn(buf[0],buf[1],buf[2],buf[3]);
        }
    
    }

}
void add3cycle(int sn,int deep,int*buf,int old){
    if(deep>0){
        *buf=sn;
        for(int i=0;i<linkn[sn];i++){
            if(old!=linkes[sn][i])
                add3cycle(linkes[sn][i],deep-1,buf+1,sn);
        }
    }else{
        buf-=3;
        if(*buf==sn && sn<buf[1] &&sn <buf[2]){
            plateSn3(buf[0],buf[1],buf[2]);
        }
    
    }

}
double basefreqHeights[4096][16];
double cos_getChroma_basefreq[4096][16];
double sin_getChroma_basefreq[4096][16];
double getChroma_basefreq[4096][16];
//getChroma_basefreq
double log_basefreq[4096][16];
int fastTable=0;

void drawSoundSpeq(GLuint tex,struct soundSpeq*ssp,double r,double a1,double a2,double a3,double fov,double len,double width ){
//    zeroLink();
    int i,j;
    double maxMel;
    struct rgb c1;
    int snn=0;
    maxMel=log(MAXTONEHEIGHT+1);
    start3d_3a(r,a1,a2,a3,fov);
/*    fprintf(stderr,"r=%lf a1=%lf ",r,a1);
    fprintf(stderr,"a2=%lf a3=%lf ",a2,a3);
    fprintf(stderr,"fov=%lf len=%lf ",fov,len);
    fprintf(stderr,"w=%lf\n",width);*/
    double mamContrast=getOpt("mamContrast")*100;
    double zshift=2*getOpt("soundSpeq_zshift");
    double zeroPs=fabs(getOpt("soundSpeq_zeroPs"))*10;
    double fadePs=calcOpt("soundSpeq_fadePs")*10;
    double plateOp=calcOpt("soundSpeq_plateOp");
    double plateOpZero=calcOpt("soundSpeq_plateOpZero");
   
    double lineOpZero=calcOpt("soundSpeq_lineOpZero");
    double lineOp=calcOpt("soundSpeq_lineOp");
   
    double pointOpZero=calcOpt("soundSpeq_pointOpZero");
    double pointOp=calcOpt("soundSpeq_pointOp");
    double neampsize=calcOpt("soundSpeq_neampsize");
    
    double lowFreqBri=calcOpt("soundSpeq_lowFreqBri");
    double highFreqBri=calcOpt("soundSpeq_highFreqBri");
    
    highFreqBri-=lowFreqBri;
    
    double INGARBRIGHTKOEF=calcOpt("soundSpeq_INGARBRIGHTKOEF");
    double maxBasefreqHeight;
    double ampGarGamma=calcOpt("soundSpeq_ampGarGamma");
    maxBasefreqHeight=gz2mel(MAXTONEHEIGHT);
    double heatpow=calcOpt("soundSpeq_heatPow")*3;
//    fprintf(stderr,"..\n");
    
    double baseCroma;
    if(!fastTable){
        fastTable=1;
        for(i=0;i<ssp->n;i++){
             for(j=0;j<NGAR;j++){
                double basefreq;
                basefreq=ssp->freqs[i]/(j+1);
                basefreqHeights[i][j]=gz2mel(basefreq)/maxBasefreqHeight;
                cos_getChroma_basefreq[i][j]=cos(getChroma(basefreq)*2*M_PI);
                sin_getChroma_basefreq[i][j]=sin(getChroma(basefreq)*2*M_PI);
                getChroma_basefreq[i][j]=getChroma(basefreq)*2*M_PI;
            
                log_basefreq[i][j]=log(basefreq+1)*2/maxMel-0.5;
            }
        }
    }
    for(i=0;i<ssp->n;i++){
        for(j=0;j<NGAR;j++){
            double x,y,z;
            double a,h,s,v,heat,m;
            double basefreq;
            basefreq=ssp->freqs[i]/(j+1);
            snoxelGar[i][j]=-1;
            double basefreqHeight;
            basefreqHeight=basefreqHeights[i][j];//gz2mel(basefreq)/maxBasefreqHeight;

            if(basefreq<MAXTONEHEIGHT){
                z= (log_basefreq[i][j] /*log(basefreq+1)*2/maxMel-0.5*/ -zshift  + ssp->neamps[i]*neampsize )*len;
                a=getChroma_basefreq[i][j];//getChroma(basefreq)*2*M_PI;
                baseCroma=a;
                x=width*(j+1)/(NGAR+1);
                y=x*cos_getChroma_basefreq[i][j];//cos(a);
                x=x*sin_getChroma_basefreq[i][j];//sin(a);
            heat=2*(mypow(ssp->kos[i],heatpow)-0.5);
            //hsv_c1=hmv_h2hsv(heat,m,v,s);
            m=2*(ssp->mam[i*NGAR+j]-0.5);
            
            h=atan2(m*mamContrast,heat)/2/M_PI;
            if(h<0.)
                h+=1;
          
          
                s=ssp->garHi[i*NGAR+j];
                v=ssp->amps[i]*(1-INGARBRIGHTKOEF) +pow(ssp->amps[i]*ssp->gar[i*NGAR+j],ampGarGamma)*INGARBRIGHTKOEF;
          
          
                double br;
                br=  lowFreqBri + (highFreqBri )*basefreqHeight;
                
                c1=rgbCorrector(color(h,s,br));     
                double oo;

                c1.o=v*255;
                snoxels[snn].c=c1;
                oo=(v-lineOpZero)*255*lineOp;
                if(oo<0)
                    oo=0.;
                snoxels[snn].c.o=oo;
                
                snoxels[snn].cpp=c1;
                oo=(v-pointOpZero)*255*pointOp;
                if(oo<0)
                    oo=0.;
                snoxels[snn].cpp.o=oo;
                
                

                
                snoxels[snn].cp=c1;
                oo=(v-plateOpZero)*255*plateOp;
                if(oo<0)
                    oo=0.;
                
                snoxels[snn].cp.o=oo;
                
                snoxels[snn].x=x;
                snoxels[snn].y=y;
                snoxels[snn].z=z;
                snoxels[snn].gar=j;
                snoxels[snn].freq=ssp->freqs[i];
                snoxels[snn].baseFreq=ssp->freqs[i]/(j+1);
                snoxels[snn].baseCroma=baseCroma;
                snoxels[snn].nfreq=i;
                snoxels[snn].ps=zeroPs +fadePs*fabs(ssp->neamps[i]);
                if(snoxels[snn].ps<0.00001)
                    snoxels[snn].ps=0.00001;
                snoxelGar[i][j]=snn;
//                linkn[snn]=0;

                snn++;
                //glColor4ubv((const GLubyte*)&c1);
                //glVertex3f (x,y,z);
                
                /*fprintf(stderr,"%lf %lf",x,y);
                fprintf(stderr," %lf ",z);
                fprintf(stderr,"(%d %d",c1.r,c1.g);
                fprintf(stderr," %d) \n",c1.b);
                 */
                          
            }
        }
    
    }

    double lastps=4.0;
    double ps;
    if(zeroPs>0.1||fadePs>0.1){
        glPointSize(4.0);
        glBegin(GL_POINTS);
        for(i=0;i<snn;i++){
                ps=snoxels[i].ps;
                if(fabs(lastps-ps)>0.1){
                    lastps=ps;
                    glEnd();
                    glPointSize(ps);
                    glBegin(GL_POINTS);
                }
                glColor4ubv((const GLubyte*)&(snoxels[i].cpp));
                glVertex3f (snoxels[i].x,snoxels[i].y,snoxels[i].z);
                
        }
        glEnd();
    }
    if(plateSnoxelsN==0){
        glBegin(GL_LINES);
        for(i=0;i<snn;i++){
                    int sn2;
                    sn2=findNfreq(ssp,snoxels[i].freq/2);
                    if(sn2>0){
                        int nn;
                        nn=snoxelGar[sn2][snoxels[i].gar];
                        if(nn>0){
                            snLine(snoxels[i],snoxels[nn]);
                            addlink(i,nn);
                            addlink(nn,i);
                        }
                    }
                    if(snoxels[i].gar>=1){
                        sn2=findNfreq(ssp,snoxels[i].freq/(snoxels[i].gar+1)*(snoxels[i].gar));
                        if(sn2!=-1){
                            int nn=snoxelGar[sn2][snoxels[i].gar-1];
                            if(nn>0){
                                snLine(snoxels[i],snoxels[nn]);
                                addlink(i,nn);
                                addlink(nn,i);
                        
                            }
                        }
                    }
                    /*if(snoxels[i].nfreq>=2){
                        sn2=snoxels[i].nfreq-1;
                        if(sn2>0){
                            snLine(snoxels[i],snoxels[snoxelGar[sn2][snoxels[i].gar]]);
                            addlink(i,snoxelGar[sn2][snoxels[i].gar]);
                            addlink(snoxelGar[sn2][snoxels[i].gar],i);
    
                        }
                    }*/
                    if(snoxels[i].nfreq<ssp->n-1){
                        sn2=snoxels[i].nfreq+1;
                        
                        if(sn2<ssp->n){
                            int nn;
                            nn=snoxelGar[sn2][snoxels[i].gar];
                            if(nn>0){
                                snLine(snoxels[i],snoxels[nn]);
                                addlink(nn,i);
                                addlink(i,nn);
    
                            }
                        }
                    }
        }
        glEnd();
        int buf[10];
        for(i=0;i<snn;i++){
            add4cycle(i,4,buf,i);
            add3cycle(i,3,buf,i);
        
        }
    }else{

          for(i=0;i<snn;i++){
//              fprintf(stderr,"%d %d\n",i,linkn[i]);

              for(j=0;j<linkn[i];j++){
                  int nn;
                  nn=linkes[i][j];
  //                fprintf(stderr,"%d %d\n",i,nn);
                  if(i<nn)
                      snLine(snoxels[i],snoxels[nn]);
              }
            }
    
    }
    if(plateOp>0.04){
        drPlateSn();
    }
    end3d_3a(tex);
}

void drawSoundSpeqSquare(GLuint tex,struct soundSpeq*ssp,double r,double a1,double a2,double a3,double fov,double len,double width ){
//    zeroLink();
    int i,j;
    double maxMel;
    struct rgb c1;
    int snn=0;
    maxMel=log(MAXTONEHEIGHT+1);
    start3d_3a(r,a1,a2,a3,fov);
/*    fprintf(stderr,"r=%lf a1=%lf ",r,a1);
    fprintf(stderr,"a2=%lf a3=%lf ",a2,a3);
    fprintf(stderr,"fov=%lf len=%lf ",fov,len);
    fprintf(stderr,"w=%lf\n",width);*/
    double mamContrast=getOpt("mamContrast")*100;
    double zshift=2*getOpt("soundSpeq_zshift");
    double zeroPs=fabs(getOpt("soundSpeq_zeroPs"))*10;
    double fadePs=calcOpt("soundSpeq_fadePs")*10;
    double plateOp=calcOpt("soundSpeq_plateOp");
    double plateOpZero=calcOpt("soundSpeq_plateOpZero");
   
    double lineOpZero=calcOpt("soundSpeq_lineOpZero");
    double lineOp=calcOpt("soundSpeq_lineOp");
   
    double pointOpZero=calcOpt("soundSpeq_pointOpZero");
    double pointOp=calcOpt("soundSpeq_pointOp");
    double neampsize=calcOpt("soundSpeq_neampsize");
    double INGARBRIGHTKOEF=calcOpt("soundSpeq_INGARBRIGHTKOEF");

    for(i=0;i<ssp->n;i++){
        for(j=0;j<NGAR;j++){
            double x,y,z;
            double a,h,s,v,heat,m;
            double basefreq;
            basefreq=ssp->freqs[i]/(j+1);
            snoxelGar[i][j]=-1;
            if(basefreq<MAXTONEHEIGHT){
                a=getChroma(basefreq);//*2*M_PI;
                z= (log(basefreq+1)*2/maxMel-0.5 -zshift  +ssp->neamps[i]*neampsize );
                
                x=width*((j+1)/(NGAR+1))*2;
                y=(a)*len*2;
               // z=x*sin(a);
            heat=2*(ssp->kos[i]-0.5);
            //hsv_c1=hmv_h2hsv(heat,m,v,s);
            m=2*(ssp->mam[i*NGAR+j]-0.5);
            
            h=atan2(m*mamContrast,heat)/2/M_PI;
            if(h<0.)
                h+=1;
          
          
                s=ssp->garHi[i*NGAR+j];
                v=ssp->amps[i]*(1-INGARBRIGHTKOEF) +ssp->amps[i]*INGARBRIGHTKOEF*ssp->gar[i*NGAR+j];
                c1=rgbCorrector(color(h,s,1));     
                double oo;

                c1.o=v*255;
                snoxels[snn].c=c1;
                oo=(v-lineOpZero)*255*lineOp;
                if(oo<0)
                    oo=0.;
                snoxels[snn].c.o=oo;
                
                snoxels[snn].cpp=c1;
                oo=(v-pointOpZero)*255*pointOp;
                if(oo<0)
                    oo=0.;
                snoxels[snn].cpp.o=oo;
                
                

                
                snoxels[snn].cp=c1;
                oo=(v-plateOpZero)*255*plateOp;
                if(oo<0)
                    oo=0.;
                
                snoxels[snn].cp.o=oo;
                
                snoxels[snn].x=x;
                snoxels[snn].y=y;
                snoxels[snn].z=z;
                snoxels[snn].gar=j;
                snoxels[snn].freq=ssp->freqs[i];
                snoxels[snn].nfreq=i;
                snoxels[snn].ps=zeroPs +fadePs*ssp->fade[i];
                if(snoxels[snn].ps<0.00001)
                    snoxels[snn].ps=0.00001;
                snoxelGar[i][j]=snn;
                linkn[snn]=0;

                snn++;
                //glColor4ubv((const GLubyte*)&c1);
                //glVertex3f (x,y,z);
                
                /*fprintf(stderr,"%lf %lf",x,y);
                fprintf(stderr," %lf ",z);
                fprintf(stderr,"(%d %d",c1.r,c1.g);
                fprintf(stderr," %d) \n",c1.b);
                 */
                          
            }
        }
    
    }

    double lastps=4.0;
    double ps;
    if(zeroPs>0.1||fadePs>0.1){
        glPointSize(4.0);
        glBegin(GL_POINTS);
        for(i=0;i<snn;i++){
                ps=snoxels[i].ps;
                if(fabs(lastps-ps)>0.1){
                    lastps=ps;
                    glEnd();
                    glPointSize(ps);
                    glBegin(GL_POINTS);
                }
                glColor4ubv((const GLubyte*)&(snoxels[i].cpp));
                glVertex3f (snoxels[i].x,snoxels[i].y,snoxels[i].z);
                
        }
        glEnd();
    }
    glBegin(GL_LINES);
    
        for(i=0;i<snn;i++){
                int sn2;
                sn2=findNfreq(ssp,snoxels[i].freq/2);
                if(sn2>0){
                    int nn;
                    nn=snoxelGar[sn2][snoxels[i].gar];
                    if(nn>0){
                        snLine(snoxels[i],snoxels[nn]);
                        addlink(i,nn);
                        addlink(nn,i);
                    }
                }
                if(snoxels[i].gar>=1){
                    sn2=findNfreq(ssp,snoxels[i].freq/(snoxels[i].gar+1)*(snoxels[i].gar));
                    if(sn2!=-1){
                        int nn=snoxelGar[sn2][snoxels[i].gar-1];
                        if(nn>0){
                            snLine(snoxels[i],snoxels[nn]);
                            addlink(i,nn);
                            addlink(nn,i);
                    
                        }
                    }
                }
                /*if(snoxels[i].nfreq>=2){
                    sn2=snoxels[i].nfreq-1;
                    if(sn2>0){
                        snLine(snoxels[i],snoxels[snoxelGar[sn2][snoxels[i].gar]]);
                        addlink(i,snoxelGar[sn2][snoxels[i].gar]);
                        addlink(snoxelGar[sn2][snoxels[i].gar],i);

                    }
                }*/
                if(snoxels[i].nfreq<ssp->n-1){
                    sn2=snoxels[i].nfreq+1;
                     
                   
                    if(sn2<ssp->n ){
                        int nn;
                        nn=snoxelGar[sn2][snoxels[i].gar];
                        if(nn>0&& snoxels[i].baseCroma<snoxels[nn].baseCroma){
                            snLine(snoxels[i],snoxels[nn]);
                            addlink(nn,i);
                            addlink(i,nn);

                        }
                    }
                }
    }
    glEnd();

    if(plateSnoxelsN==0){
        int buf[10];
        for(i=0;i<snn;i++){
            add4cycle(i,4,buf,i);
            add3cycle(i,3,buf,i);
        
        }
    }
    if(plateOp>0.04){
        drPlateSn();
    }
    end3d_3a(tex);
}



double calcSumSspDis(struct soundSpeq*ssp1,double st,double fin){
    int i0,i1,i;
    double res;
    i0=st*ssp1->n;
    
    i1=fin*ssp1->n;
    res=0;
    if(i0<0)
        i0=0;
    for(i=i0;i<i1&&i<ssp1->n;i++){
        res+=ssp1->kos[i]*ssp1->amps[i];
    }
   
    return res;
}
#endif
