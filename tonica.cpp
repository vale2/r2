
#define TDEF 128
double tstat[TDEF];
double tstatdwn=0.99999;
int *fr2tstat;

double getChroma(double freq);
void initTonica(struct soundSpeq*ssp){
    int i;
    for(i=0;i<TDEF;i++){
        tstat[i]=1;
    }

    fr2tstat=(int*)malloc(ssp->n*sizeof(int));
    for(i=0;i<ssp->n;i++){
        double chr;
        chr=getChroma(ssp->freqs[i]);
        int ichr;
        ichr=chr*TDEF+0.5;
        while(ichr>=TDEF)
            ichr-=TDEF;
        while(ichr<0)
            ichr+=TDEF;
        fr2tstat[i]=ichr;
    }
}
void tonicaDwn(){
    int i;
    for(i=0;i<TDEF;i++){
        tstat[i]*=tstatdwn;
    }

}
void inline  tonicaUp
