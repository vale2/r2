#ifndef RTMMOD
#define RTMMOD
#define RTMSIZE 8
#define RTMS 1
struct rithm{
    double amps[RTMSIZE][RTMSIZE];
    double phs[RTMSIZE][RTMSIZE];
    double basefr;
}rtms[RTMS];

void updateRtms(){
    int i,j,k;
    char s1[128];
    char s2[128];
    for(i=0;i<RTMS;i++){
       sprintf(s1,"rtms_%d_basefreq",i);
       rtms[i].basefr=10*calcOpt(s1);
//       fprintf(stderr,"rtms[i].basefr=%lf\n",rtms[i].basefr);
        for(j=0;j<RTMSIZE;j++){
            for(k=0;k<RTMSIZE;k++){
                sprintf(s1,"rtms_%d_amps_%d_%d",i,j,k);
                sprintf(s2,"rtms_%d_phs_%d_%d",i,j,k);
                rtms[i].amps[j][k]=calcOpt(s1);
                
                rtms[i].phs[j][k]=calcOpt(s2);
            }
        }
    }
}
double calcRtm(int n,double time){
    double res;
    res=0;
    int  i,j;
    for(i=0;i<RTMSIZE;i++)
        for(j=0;j<RTMSIZE;j++){
            res+=rtms[n].amps[i][j]*sin(2*M_PI*(time*rtms[n].basefr*(i+1)/(j+1)+rtms[n].phs[i][j]));
        
        }  
    return res;   
}
double lastRtm[RTMS];
double lastDRtm[RTMS];
double firstRtm=-1;
void my_sound_click(int n,double a);
void doRtm(){
    int i;
    double time;
    updateRtms();
    time=GetTickCount()/1000.;
    if(firstRtm<0.){
        firstRtm=time;
    }
    time-=firstRtm;
    for(i=0;i<RTMS;i++){
        double rtm,drtm;
        rtm=calcRtm(i,time);
        drtm=rtm-lastRtm[i];
//        fprintf(stderr,"RTMS%d",i);
  //      fprintf(stderr," %1.3f\n",rtm);
        if(/*lastDRtm[i]<=0.&&drtm>=0.*/lastRtm[i]<0&&rtm>=0){
//            fprintf(stderr," CLICK(%lf)!\n",rtm);
            my_sound_click(i,rtm);   
        }    
        lastRtm[i]=rtm;
        lastDRtm[i]=drtm;
    }
}
#endif
