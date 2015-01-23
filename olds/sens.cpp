#ifndef SENSMOD
#define SENSMOD
#define MIND 0.00000001
#define LATE 1000
#define SOFT 0

#define CORLEVEL 10
#define CORSPEED 0.99
#define CORMIND 0.001
#include"options.cpp"
struct corrector{
    double counts[CORLEVEL];
    double borders[CORLEVEL];
    double speed;
    char on;

};

void  monitorCorrector(struct corrector*c,char*name){
    char s[256];
   // sprintf(s,"%s_cor_on",name);
//    setOpt(s,c->on);
    
    //sprintf(s,"%s_cor_speed",name);
  //  setOpt(s,c->speed);
    for(int i=0;i<CORLEVEL;i++){
  //    sprintf(s,"%s_cor_counts_%d",name,i);
    //  setOpt(s,c->counts[i]);
//      sprintf(s,"%s_cor_borders_%d",name,i);
      //setOp(s,c->borders[i]);
        
    
    }    

}

void zeroCorrector(struct corrector*c){
    int i;
    for(i=0;i<CORLEVEL;i++){
        c->counts[i]=10.;
        c->borders[i]=(i+1.)/CORLEVEL;
    }
    c->speed=CORSPEED;
    c->on=0;
}

#include<math.h>

void checkC(double *a,int n,double a0){
    int done,i;
    double *l,*r;
    double lb,summ;
    done=0;
    while(!done){
        done=1;
        lb=a0;
        l=&lb;
        r=a;
        for(i=0;i<n;i++,l=r,r++){
            if(*r-*l<CORMIND){
                summ=(*r+*l);
                *l=(summ-CORMIND)/2-0.000000001;
                if(i!=n-1){
                    *r=(summ+CORMIND)/2+0.000000001;
                } 
                done=0;           
            }
        }
    }
}

void  checkCorrect(struct corrector*c){
    c->borders[CORLEVEL-1]=1.;
    checkC(c->borders,CORLEVEL,0);
}
void  checkCorrect05(struct corrector*c){
    c->borders[CORLEVEL-1]=1.;
    c->borders[CORLEVEL/2-1]=0.5;
    checkC(c->borders,CORLEVEL/2,0);
    checkC(c->borders+CORLEVEL/2,CORLEVEL/2,c->borders[CORLEVEL/2-1]);

}



double correctValue(struct corrector*c,double value){//value beetween [0..1]
    int n,i;
    n=trunc(CORLEVEL*value);
    double lborder=0;
    double ret;
    double sum,subsum;
    double sums[CORLEVEL];
    sum=0;subsum=0;
    if(!c->on){
        return value;
    }
    for(i=0;i<CORLEVEL;i++){ 
        sum=sum+c->counts[i];
        sums[i]=sum;
    }
    if(value<0.00001){
        ret=0.;
        i=0;
    }else{
        if(sum>0.00001){
            if(n<=0)
                lborder=0;
            else
                lborder=c->borders[n-1];
            ret=lborder+(value-n/(double)CORLEVEL)*c->counts[i]/sum;
        }else{
            ret=0.;
        }
    }
    
    
    c->counts[n]=c->counts[n]+1;
    for(i=0;i<CORLEVEL;i++){ 
        c->counts[i]=c->counts[i]*c->speed;
    }
    
    
    lborder=0;
    double p1,p2;
    for(i=1;i<CORLEVEL-1;i++){
        p1=c->counts[i]/(c->borders[i]-c->borders[i-1]);
        p2=c->counts[i-1]/(c->borders[i-1]-lborder);
        if(p1>p2){
           if((c->borders[i-1]-lborder)*c->speed>CORMIND){
                c->borders[i-1]=lborder+(c->borders[i-1]-lborder)*c->speed;
           } else{
                c->borders[i-1]=lborder+CORMIND;
           }
        }else{
           if((c->borders[i]-c->borders[i-1])*c->speed>CORMIND){
                c->borders[i-1]=c->borders[i]-(c->borders[i]-c->borders[i-1])*c->speed;
           }else{
                c->borders[i-1]=c->borders[i]-CORMIND;
           }
        }
        
        p1=c->counts[i]/(c->borders[i]-c->borders[i-1]);
        p2=c->counts[i+1]/(c->borders[i+1]-c->borders[i]);
        
        if(p1<p2){
           if((c->borders[i]-c->borders[i-1])*c->speed>CORMIND){
                c->borders[i]=c->borders[i-1]+(c->borders[i]-c->borders[i-1])*c->speed;
           }else{
                c->borders[i]=c->borders[i-1]+CORMIND;
           } 
        }else{
           if((c->borders[i+1]-c->borders[i])*c->speed>CORMIND){
                c->borders[i]=c->borders[i+1]-(c->borders[i+1]-c->borders[i])*c->speed;
           }else{
                c->borders[i]=c->borders[i+1]-CORMIND;
           }
        }
        
        lborder=c->borders[i-1];
    }
    checkCorrect(c);
    return ret;
}
double correctValue05(struct corrector*c,double value){//value beetween [0..1]
    int n,i;
    n=trunc(CORLEVEL*value);
    double lborder=0;
    double ret;
    double sum,subsum;
    double sums[CORLEVEL];
    sum=0;subsum=0;
    if(!c->on){
        return value;
    }
    for(i=0;i<CORLEVEL;i++){ 
        sum=sum+c->counts[i];
        sums[i]=sum;
    }
    if(value<0.00001){
        ret=0.;
        i=0;
    }else{
        if(sum>0.00001){
            if(n<=0)
                lborder=0;
            else
                lborder=c->borders[n-1];
            ret=lborder+(value-n/(double)CORLEVEL)*c->counts[i]/sum;
        }else{
            ret=0.;
        }
    }
    
    
    c->counts[n]=c->counts[n]+1;
    for(i=0;i<CORLEVEL;i++){ 
        c->counts[i]=c->counts[i]*c->speed;
    }
    
    
    lborder=0;
    double p1,p2;
    for(i=1;i<CORLEVEL-1;i++){
        p1=c->counts[i]/(c->borders[i]-c->borders[i-1]);
        p2=c->counts[i-1]/(c->borders[i-1]-lborder);
        if(p1>p2 && i-1!=CORLEVEL/2-1){
           if((c->borders[i-1]-lborder)*c->speed>CORMIND){
                c->borders[i-1]=lborder+(c->borders[i-1]-lborder)*c->speed;
           } else{
                c->borders[i-1]=lborder+CORMIND;
           }
        }else if(i-1!=CORLEVEL/2-1){
           if((c->borders[i]-c->borders[i-1])*c->speed>CORMIND){
                c->borders[i-1]=c->borders[i]-(c->borders[i]-c->borders[i-1])*c->speed;
           }else{
                c->borders[i-1]=c->borders[i]-CORMIND;
           }
        }
        
        p1=c->counts[i]/(c->borders[i]-c->borders[i-1]);
        p2=c->counts[i+1]/(c->borders[i+1]-c->borders[i]);
        
        if(p1<p2){
           if((c->borders[i]-c->borders[i-1])*c->speed>CORMIND){
                c->borders[i]=c->borders[i-1]+(c->borders[i]-c->borders[i-1])*c->speed;
           }else{
                c->borders[i]=c->borders[i-1]+CORMIND;
           } 
        }else{
           if((c->borders[i+1]-c->borders[i])*c->speed>CORMIND){
                c->borders[i]=c->borders[i+1]-(c->borders[i+1]-c->borders[i])*c->speed;
           }else{
                c->borders[i]=c->borders[i+1]-CORMIND;
           }
        }
        
        lborder=c->borders[i-1];
    }
    checkCorrect05(c);
    return ret;
}

struct sense{
    double min,max,lat,mind,superMin,superMax;
    double soft;
    double softup;

    double last;
    struct corrector c;
    char o5;
    struct adr monitor;
    char name[128];
};


#define MAXSENSORS 100000
int nSensors=0;
struct sensEl{
    struct sense*s;
    struct sense zero;
    char name[128];
    int n;   
}sensors[MAXSENSORS];


void regSensor(struct sense*s,const char *name,int snsn){
    for(int i=0;i<nSensors;i++){
        if(!strcmp(name,sensors[i].name)){
            sensors[i].s=s;
            sensors[i].zero=*s;
            sensors[i].n=snsn;
            return;
        }
    }    
    if(nSensors<MAXSENSORS){
        sensors[nSensors].s=s;
        sensors[nSensors].zero=*s;
        strcpy(sensors[nSensors].name,name);
        sensors[nSensors].n=snsn;
        nSensors++;
    }
}


void zeroSense(struct sense*s,const char*name,int snsn){
    char str[128];
    s->mind=MIND;
    
    s->min=0;
    s->superMin=0;
    s->superMax=s->mind;
    s->last=0;
    s->max=s->mind;
    s->lat=LATE;
    s->soft=SOFT;
    s->softup=SOFT;
    zeroCorrector(&(s->c));
    s->o5=0;
    //sprintf(str,"monitor_%s",name);
   // setOpt(str,snsn,0.);
 //   s->monitor=getOptAdress(str);
    //if(s->monitor.id<0){
    //    s->monitor.id=1/0;
    // }
    strcpy(s->name,str);
    regSensor(s,name,snsn);
}

void zeroSense(struct sense*s,const char*name){
     zeroSense(s,name,0);

}
void zeroSense05(struct sense*s,const char*name,int snsn){
    zeroSense(s,name,snsn);
    s->o5=1;
}
void zeroSense05(struct sense*s,const char*name){
    zeroSense05(s,name,0);
}

void zeroSenses(struct sense*s,int n,const char*name,int on){
    char st[128];
    sprintf(st,"%s",name);
    for(int i=0;i<n;i++){
        zeroSense(s+i,st,i);
        s[i].c.on=on;
    }
}
void zeroSenses(struct sense*s,int n,const char*name){
    zeroSenses(s,n,name,0);
}
/*void zeroSenses(struct sense*s,int n,const char*name,int on){
    zeroSenses(s,n,name,on);
}*/

void zeroSenses05(struct sense*s,int n,const char*name){
    char st[128];
    sprintf(st,"%s",name);
    for(int i=0;i<n;i++){
        zeroSense05(s+i,st,i);
    }

}


void  nearbyCorrect(struct corrector*c1,struct corrector*c2,double d){
    double a,b;
    for(int i=0;i<CORLEVEL;i++){
        if(c1->borders[i]<(1.-d)*c2->borders[i]){
            c1->borders[i]=(1.-d)*c2->borders[i];
        }
        if(c2->borders[i]<(1.-d)*c1->borders[i]){
            c2->borders[i]=(1.-d)*c1->borders[i];
        }
    
    }
}
void  nearbyCorrect05(struct corrector*c1,struct corrector*c2,double d){
    double a,b;
    for(int i=0;i<CORLEVEL;i++){
        if(i==CORLEVEL/2-1)
            continue;
        if(c1->borders[i]<(1.-d)*c2->borders[i]){
            c1->borders[i]=(1.-d)*c2->borders[i];
        }
        if(c2->borders[i]<(1.-d)*c1->borders[i]){
            c2->borders[i]=(1.-d)*c1->borders[i];
        }
    
    }
}



void  nearbySense(struct sense*s1,struct sense*s2,double d){
    double a,b;
    if(s1->o5){
        nearbyCorrect05(&(s1->c),&(s2->c),d);
        return;
    }else{
        nearbyCorrect(&(s1->c),&(s2->c),d);
    }
    a=(s1->max-s1->superMin)/(s1->superMax-s1->superMin);
    b=(s2->max-s2->superMin)/(s2->superMax-s2->superMin);
    if(a<(1.-d)*b){
        s1->max=(1.-d)*b*(s1->superMax-s1->superMin)+s1->superMin;
    }   
    if(b<(1.-d)*a){
        s2->max=(1.-d)*a*(s2->superMax-s2->superMin)+s2->superMin;
    }   
    


    /*a=(s1->min-s1->superMin)/(s1->superMax-s1->superMin);
    b=(s2->min-s2->superMin)/(s2->superMax-s2->superMin);
    if(a*(1.-d)>b){
        s1->min=b*(s1->superMax-s1->superMin)+s1->superMin;
    }   
    if(b<(1.-d)*a){
        s2->max=a*(s2->superMax-s2->superMin)+s2->superMin;
    } */  
    

}

void nearbySenses(struct sense*s,int n,double d){
    for(int i=0;i<n-1;i++){
        nearbySense(s+i,s+i+1,d);
    }
}



double senseValue05(struct sense*s,double v){
       if(s->last>=v){
           v=v*(1-s->soft)+s->last*(s->soft);
       }else{
           v=v*(1-s->softup)+s->last*(s->softup);
       
       }

       
       s->last=v;
       if(s->max<v){
            s->max=v;        
        }
        if(s->min>v){
            s->min=v;        
        }
        if(s->min<s->superMin){
            s->superMin=s->min;
        }
        if(s->max>s->superMax){
            s->superMax=s->max;
        }
        s->max=(s->max*s->lat+v)/(s->lat+1);

        s->min=(s->min*s->lat+v)/(s->lat+1);
//        double t;
            
        if(s->max - s->min<s->mind){
           s->max=v+s->mind/2;
           s->min=v-s->mind/2;;
        }
      
        return correctValue05(&(s->c),0.5+ (v-s->min-(s->max-s->min)/2)/(((s->max-s->min))));
}
void monitorSense(struct sense*s,double value){
    char name[256];
    sprintf(name,"%s_min",s->name);
//    setOpt(name,s->min);

    sprintf(name,"%s_max",s->name);
  //  setOpt(name,s->max);

    sprintf(name,"%s_value",s->name);
    //setOpt(name,value);

    sprintf(name,"%s_superMin",s->name);
    //setOpt(name,s->superMin);

    sprintf(name,"%s_superMax",s->name);
   // setOpt(name,s->superMax);

    monitorCorrector(&(s->c),s->name);


}

double senseValue(struct sense*s,double v){
//       fprintf(stderr,"snsv\n",s->name);

      // if(getOpt(s->monitor)>0.5){
           // fprintf(stderr,"monitoring %s\n",s->name);
        //    monitorSense(s,v);
      // }
       if(s->o5){
            return senseValue05(s,v); 
       }
       if(s->last>=v){
           v=v*(1-s->soft)+s->last*(s->soft);
       }else{
           v=v*(1-s->softup)+s->last*(s->softup);
       
       }
       s->last=v;
       if(s->max<v){
            s->max=v;        
        }
        if(s->min>v){
            s->min=v;        
        }
        if(s->min<s->superMin){
            s->superMin=s->min;
        }
        if(s->max>s->superMax){
            s->superMax=s->max;
        }

        s->max=(s->max*s->lat+v)/(s->lat+1);

        s->min=(s->min*s->lat+v)/(s->lat+1);
        if(s->max - s->min<s->mind){
            s->max=s->min+s->mind;
        }
        return  correctValue(&(s->c),(v-s->min)/(s->max-s->min));
}


struct sense* makeSence(char*s,int n){
        struct sense*r;
        r=(struct sense*)malloc(n*sizeof(struct sense));
        if(r==NULL)
            return NULL;
        zeroSenses(r,n,s,0);
        return r;
}
#endif
