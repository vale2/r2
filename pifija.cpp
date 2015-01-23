
#define PIFLEN 2048
struct pifija{
    double signal[PIFLEN+10];
    int cur;
    double time;    
    double nextStep;
    double iv;
    double sum;
}pif[10];


Uint32 secBegin=0;
double secFromBegin(){
     if(secBegin==0){
        secBegin=GetTickCount();
        return 0;
     }
    return (GetTickCount() - secBegin)/1000.;

}

/*
double predict(int n,double feed,double minfreq,double maxfreq,double len,double quant){
    int l,lk;
//    return 0;
    if(pif[n].time<0.01){
        pif[n].time=secFromBegin();
        pif[n].nextStep=pif[n].time+quant;
        pif[n].iv=feed;
        pif[n].sum=0;
    }else{
        double myt,t;
        t=secFromBegin();
        myt=t-pif[n].time;
        if(t>=pif[n].nextStep){
            double lfeed,rfeed,tt,sum;
            lfeed=(feed-pif[n].iv)*(pif[n].nextStep-pif[n].time)/(t-pif[n].time);
            pif[n].sum+=(pif[n].iv+lfeed)/2*(pif[n].nextStep-pif[n].time)/quant;
            sum=pif[n].sum;
            pif[n].sum=(lfeed+feed)/2*(t-pif[n].nextStep)/quant;
            pif[n].iv=feed;
            pif[n].nextStep=pif[n].nextStep+quant;
            pif[n].time=t;
            
            pif[n].signal[pif[n].cur]=sum;
            pif[n].signal[pif[n].cur+512]=sum;
            pif[n].cur++;
            
        }else{
            pif[n].time=t;
            pif[n].sum+=(pif[n].iv+feed)/2*myt/quant;
            pif[n].iv=feed;
            double ssym,dd;
            dd=(quant-(pif[n].nextStep-pif[n].time));
            if(dd>0.001){
                ssym=pif[n].sum/dd*quant;
                pif[n].signal[pif[n].cur]=ssym;
                pif[n].signal[pif[n].cur+512]=ssym;
            }
        }
    
    
    }
    
    
    ShortComplex sig[512];
    if(pif[n].cur>=512)
        pif[n].cur=0;
    l=len*512;
    if(l<0)
        l=0;
    if(l>=512){
        l=512;
        lk=9;
    }else if(l>=256){
        l=256;
        lk=8;
    }else if(l>=128){
        l=128;
        lk=7;
    }else{
        l=64;
            lk=6;

    }
    for(i=0;i<l;i++){
        sig[i].re=pif[n].signal[pif[n].cur+512-l+i];
        sig[i].im=0;
    }
//    fprintf(stderr,"fft for %d\n",lk);
  //  fprintf(stderr,"minfreq  %lf; ",minfreq);
    //fprintf(stderr," maxfreq %lf\n",maxfreq);
    

    fft(sig,lk,0);
    int Nmax= (l + 1) / 2;
    double r=0;
    double ld;
    ld=(pif[n].time-pif[n].nextStep)/quant;
    if(maxfreq>0.00001)
    for(i=0;i<Nmax;i++){
        if(i>=minfreq*l&&i<=maxfreq*l){
            double freq=i/(double)l;
            double ph=atan2(sig[i].im, sig[i].re);
            double a=sqrt(sig[i].re*sig[i].re + sig[i].im*sig[i].im);
            r+=a*sin((l+ld)*freq+ph)*pow((maxfreq-freq)/maxfreq,0.3);

        }
    }
    
    
    return r;
}

*/


double predict(int n,double feed,double minfreq,double maxfreq,double len,double quant){
    int l,lk;
//    return 0;
    
    ShortComplex sig[PIFLEN/2];
    pif[n].signal[pif[n].cur]=feed;
    pif[n].signal[pif[n].cur+PIFLEN/2]=feed;
    pif[n].cur++;
    if(pif[n].cur>=PIFLEN/2)
        pif[n].cur=0;
    l=len*PIFLEN/2;
    if(l<0)
        l=0;
    if(l>=4096){
        l=4096;
        lk=12;
    }else      
    if(l>=2048){
        l=2048;
        lk=11;
    }else      
    if(l>=1024){
        l=1024;
        lk=10;
    }else      
    if(l>=512){
        l=512;
        lk=9;
    }else if(l>=256){
        l=256;
        lk=8;
    }else if(l>=128){
        l=128;
        lk=7;
    }else{
        l=64;
            lk=6;

    }
    for(i=0;i<l;i++){
        sig[i].re=pif[n].signal[pif[n].cur+PIFLEN/2-l+i];
        sig[i].im=0;
    }
//    fprintf(stderr,"fft for %d\n",lk);
  //  fprintf(stderr,"minfreq  %lf; ",minfreq);
    //fprintf(stderr," maxfreq %lf\n",maxfreq);
    

    fft(sig,lk,0);
    int Nmax= (l + 1) / 2;
    double r=0;
    double rmax=0;
    if(maxfreq>0.00001)
    for(i=0;i<Nmax;i++){
        if(i>=minfreq*l&&i<=maxfreq*l){
            double freq=i/(double)l;
            double ph=atan2(sig[i].im, sig[i].re);
            double a=sqrt(sig[i].re*sig[i].re + sig[i].im*sig[i].im);
            r+=a*sin(l*freq+ph)*pow((maxfreq-freq)/maxfreq,0.3);
            rmax+=a;
        }
    }
    
    if(rmax>=0.001)
        return r/rmax;
    else
     return r;
}


