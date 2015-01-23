
double*v_freqs=NULL;
double*v_amps=NULL;
double*ampsr=NULL;
double*ampsl=NULL;
double*a1r=NULL;
double*a2r=NULL;
double*a1l=NULL;
double*a2l=NULL;
double *v_ufr=NULL;
int nfreqs=0;
int*nview;
double* genFreqs(int &n){
    double fr0,fr1,fr;
    double dcw;
    double *freqs;    
    int i;
    dcw=0.1;
    fr0=40;
    fr1=700;
    for(fr=fr0,n=1;fr<fr1;fr+=critWidth(fr)*dcw,n++);
    freqs=(double*)malloc(n*sizeof(double));
    if(freqs==NULL){
        n=0;
        return NULL;
    }
    for(fr=fr0,i=0;i<n;fr+=critWidth(fr)*dcw,i++)
        freqs[i]=fr;
    return freqs;
}

int viewFreqs(double *koefs){
//double&*ramps,double&*rfreqs,int&n){
    double r,l;
    int i;
    double sqsr;
    initmysin();
    if(!initSensKoefs){
        initSensKoefs=1;
        zeroSenses(sensKoefs,KOEFNUM,"mainSensors",1);

        
    }
    setSesorsSpeed(); 

    sqsr=sqrt(SAMPLE_RATE);
    if(nfreqs==0){
       v_freqs=genFreqs(nfreqs);
       v_amps=(double*)malloc(nfreqs*sizeof(double));
       ampsr=(double*)malloc(nfreqs*sizeof(double));
       ampsl=(double*)malloc(nfreqs*sizeof(double));
       a1r=(double*)malloc(nfreqs*sizeof(double));
       a2r=(double*)malloc(nfreqs*sizeof(double));
       a1l=(double*)malloc(nfreqs*sizeof(double));
       a2l=(double*)malloc(nfreqs*sizeof(double));
       v_ufr=(double*)malloc(nfreqs*sizeof(double));
       nview=(int*)malloc(nfreqs*sizeof(int));
       for(i=0;i<nfreqs;i++){
         v_amps[i]=0;
         ampsr[i]=0;
         ampsl[i]=0;
         a1l[i]=0;
         a2l[i]=0;
         a1r[i]=0;
         a2r[i]=0;
         v_ufr[i]=0;
         nview[i]=1;
       }
    }
    for(;data.begin!=data.end;data.begin++,data.begin%=data.len){
     //       putS2(data.buff1[data.begin]);
       //     putS1(data.buff2[data.begin]);

            r=data.buff1[data.begin]/32768.;
            l=data.buff2[data.begin]/32768.;
            for(i=0;i<nfreqs;i++){
                while(v_ufr[i]>sqsr){
                    v_ufr[i]-=sqsr;
                    ampsr[i]=sqrt(a1r[i]*a1r[i]+a2r[i]*a2r[i]);//nview[i];
                   // a1r[i]*=0.99999;
                    //a2r[i]*=0.99999;
                    
                    // ampsl[i]=sqrt(a1l[i]*a1l[i]+a2l[i]*a2l[i]);
                    v_amps[i]=ampsr[i];///2+ampsl[i]/2;
                    nview[i]=0;
                }
                nview[i]++;
                t=v_ufr[i]/sqsr*2.*M_PI;
                a1r[i]=a1r[i]+r*mysin(t);
//                a1r[i]+=r*mysin(t);
                double t;
                t=t +M_PI*3/2;
                while(t>M_PI*2){
                 
                     t-=M_PI*2;
                }
              
                
                a2r[i]=a2r[i]+r*mysin(t);
//                  a2r[i]+=r*mysin(t);
                //a1l[i]=a1l[i]*0.9999+l*sin(v_ufr[i]/sqsr*2.*M_PI)*0.0001;
               // a2l[i]=a2l[i]*0.9999+l*cos(v_ufr[i]/sqsr*2.*M_PI)*0.0001;
                v_ufr[i]+=(v_freqs[i]/sqsr);
                
            }
    }
   // for(i=0;i<nfreqs;i++){
     //fprintf(stderr,"%1.2lf  ",v_amps[i]);
   
   // }
 //    fprintf(stderr,"\n");
   // fflush(stderr);
    speq2qs(v_amps,v_freqs,nfreqs,12,-3,6,&qsAll);    
    calcQSDis(&qsAll);
      
    calcSoundSpeq(ssp1,v_amps,v_freqs,nfreqs);
 //   fflush(stderr);
        int ti;
        int tithmnumv2;
        tithmnumv2=0;
        for(ti=0;ti<KOEFNUM;ti++){
            if(fabs(getOpt("typeKoef",ti))<0.5){
                koefs[ti]=senseValue(sensKoefs+ti,findEqValue(v_freqs,v_amps,nfreqs,getOpt("freqKoefStart",ti),getOpt("freqKoefFin",ti)));        
            }
            if(fabs(getOpt("typeKoef",ti) - 7.)<0.5){
                    
                    double v;
                    v=predict(tithmnumv2++,koefs[(int)getOpt("koefRithmChose",ti)],getOpt("koefRithmMinFreq",ti),getOpt("koefRithmMaxFreq",ti),getOpt("koefRithmLen",ti));
                    
                    koefs[ti]=senseValue(sensKoefs+ti,v);        
            
            }
            
            
        }

   return 0;
}
