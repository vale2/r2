struct signal{
    int speqw;
    int speqh;
    double *signals;
    double *speq;
    double *k;
    double *k2;
    
//    int *counts;
};
struct signal* initSignal(int speqw,int speqh){
    int i;
    struct signal*r;
    r=(struct signal*)malloc(sizeof(struct signal));
    r->speqw=speqw;
    r->speqh=speqh;
    r->signals=(double*)malloc(speqw*speqh*sizeof(double));
    for(i=0;i<r->speqw*r->speqh;i++){
        r->signals[i]=0;
    }    
    r->speq=(double*)malloc(speqw*speqh*sizeof(double));
    for(i=0;i<r->speqw*r->speqh;i++){
        r->speq[i]=0;
    }    
    r->k=(double*)malloc(speqw*speqh*sizeof(double));
    for(i=0;i<r->speqw*r->speqh;i++){
        r->k[i]=1./pow(2,i/speqw);
    }    
    r->k2=(double*)malloc(speqw*speqh*sizeof(double));
    for(i=0;i<r->speqw*r->speqh;i++){
        r->k2[i]=1./pow(2,i/speqw) * 1./pow(2,i/speqw);
    }    
}

void fillsignal(struct signal*s,double v){
    int i;
    for(i=0;i<s->speqw*s->speqh;i++){
        s->signals[i]=s->signals[i]*(1-s->k[i])+v*s->k[i];
        s->speq[i]=s->speq[i]*(1-s->k2[i])+s->signals[i]*s->k2[i];
    }
}
void drawSignal(){



}
