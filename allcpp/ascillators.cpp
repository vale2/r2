#include"koefs.cpp"
#define GARMONY 10
struct asc{
    int n;
    double t[GARMONY];
    double a[GARMONY];
    double z[GARMONY];
    double f[GARMONY];
}ascellator[DRAWKOEFNUM];

void zeroAsc(){
    int i;
    for(i=0;i<DRAWKOEFNUM;i++)
        ascellator[i].n=0;

}
void setAscellator(int n,double t,double a,double z,double f){

   ascellator[n].t[0]=t;
   ascellator[n].a[0]=a;
      ascellator[n].z[0]=z;
   ascellator[n].f[0]=f;
   ascellator[n].n=1;

}
void addAscellator(int n,double t,double a,double z,double f){
   if(ascellator[n].n<GARMONY){
        ascellator[n].t[ascellator[n].n]=t;
        ascellator[n].a[ascellator[n].n]=a;
        ascellator[n].z[ascellator[n].n]=z;
        ascellator[n].f[ascellator[n].n]=f;
        ascellator[n].n++;
   }
}
double ascell(int n,double t){
    double r;
    int i;
    r=0.;
 //  printf("Calc asc# %d :\n",n);
    for(i=0;i<ascellator[n].n;i++){
        r+=ascellator[n].z[i]+ascellator[n].a[i]*sin((ascellator[n].f[i]+t/ascellator[n].t[i]));
   //     printf("%lf %lf %lf %lf\n",ascellator[n].t[i],ascellator[n].a[i],ascellator[n].z[i],ascellator[n].f[i]);
    }
   // fflush(stdout);
    return r;

}

