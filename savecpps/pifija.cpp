struct pifija{
    double signal[1026];
    int cur;
}pif[10];


double predict(int n,double feed,double minfreq,double maxfreq,double len){
    int l,lk;
//    return 0;
    ShortComplex sig[512];
    pif[n].signal[pif[n].cur]=feed;
    pif[n].signal[pif[n].cur+512]=feed;
    pif[n].cur++;
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
    if(maxfreq>0.00001)
    for(i=0;i<Nmax;i++){
        if(i>=minfreq*l&&i<=maxfreq*l){
            double freq=i/(double)l;
            double ph=atan2(sig[i].im, sig[i].re);
            double a=sqrt(sig[i].re*sig[i].re + sig[i].im*sig[i].im);
            r+=a*sin(l*freq+ph)*pow((maxfreq-freq)/maxfreq,0.3);

        }
    }
    
    
    return r;
}
