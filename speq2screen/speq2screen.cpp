#include<stdio.h>
#include<math.h>
#include"sdlutils.cpp"
struct speqPoint{
    double freq,k,v,k_koef,v_koef,koef,dx;
    int ns;
    double d[10];
};


#define SPEQTW 500
#define ZOOM 10
    double x[SPEQTW];
    double y[SPEQTW];
    double q[SPEQTW];
    double t[1000];
    double frk[1000];
SDL_Surface* sc;
int scw,sch;

//void dri(double )

void DrawInt(double *freqs,double *amps,double*ph,int n,double watchForward){
    int i,j;
    double r,a,d,k,v;
    double tt;
    k=0;v=0;
    d=0;
//    double le[SPEQTW];
  //  double x,y;
    //for(i=0;i<SPEQTW;i++){
      //  le[i]=0;
    //} 
    int wf,nextfr;
    double nextfrt,tmpfrt;  
    for(wf=0;wf+1<n&&freqs[0]/freqs[wf+1]<=watchForward;wf++){
        t[wf]=ph[wf+1];
//        frk[wf]=0;
        frk[wf]=freqs[wf+1]/freqs[0];
//         printf("frk[%d]=%lf\n",wf,frk[wf]);
    }
    double yy=0;
    double lyy=0;
    double xx=0;
    double dy,koef;
    double dx=0;
    int xxcount=0;
    xx=0;
    yy=ph[0];
    for(i=0;xxcount<1000*ZOOM;i++){
        nextfr=0;
        nextfrt=t[0]+frk[0];
        for(j=0;j<wf;j++){
            if(nextfrt>t[j]+frk[j]){
                nextfrt=t[j]+frk[j];
                nextfr=j;  
            }
        }
        t[nextfr]+=frk[nextfr];
     //   q[i]=amps[nextfr+1] * (freqs[nextfr+1]/freqs[0]);
        yy+=frk[nextfr];
        while(yy>1){
            yy-=1.;
            xx+=0.001;
        }
        while(xx>1){
            xx-=1.;
            xxcount++;
//            SDL_Flip( sc );
  //         while(readKey()<0);

        }
        
        int c,mx,my;
        mx=xx*scw;
        my=yy*sch*ZOOM;
        if(mx<scw && my<sch){
            c=getPixel(sc,mx,  my);
            c=c&255;
//        if(c==0)
            if(c<255){
                c++;
                if(c+c/4<255){
                c=c+c/4;
                }else
                   c=255;
            }
        //if(c/2+)
            if(3*c/4+64<255)
                c=3*c/4+64;
            else 
                c=255;
            c=c|(c*256)|(c*256*256);
            putPixel(sc, mx, my,c);
        }
//          SDL_Flip( sc );
  //        while(readKey()<0);

                
    }    
    
    
}



struct speqPoint viewFreq(double *freqs,double *amps,double*ph,int n,double rmax,double watchForward){
    int i,j;
    double r,a,d,k,v;
    double tt;
    k=0;v=0;
    d=0;
//    double le[SPEQTW];
  //  double x,y;
    //for(i=0;i<SPEQTW;i++){
      //  le[i]=0;
    //} 
    int wf,nextfr;
    double nextfrt,tmpfrt;  
    struct speqPoint res;
    res.freq=freqs[0];
    res.k=0;
    res.v=0;
    if(freqs[0]<0.001)
        return res;
    for(wf=0;wf+1<n&&freqs[0]/freqs[wf+1]<=watchForward;wf++){
        t[wf]=ph[wf+1];
//        frk[wf]=0;
        frk[wf]=freqs[wf+1]/freqs[0];
//         printf("frk[%d]=%lf\n",wf,frk[wf]);
    }
    if(wf==0)
        return res; 
    double yy=0;
    double lyy=0;
    double xx=0;
    double dy,koef;
    double dx=0;
    for(i=0;i<SPEQTW&&xx<200.;i++){
        //nextPoint(freqs,amps,n,watchForward,x[i],y[i],q[i]);
//        nextfr=-1;
        nextfr=0;
        nextfrt=t[0]+frk[0];
        for(j=1;j<wf;j++){
            if(nextfrt>t[j]+frk[j]){
                nextfrt=t[j]+frk[j];
                nextfr=j;  
            }
        }
        t[nextfr]+=frk[nextfr];
        q[i]=amps[nextfr+1] * (freqs[nextfr+1]/freqs[0]);
        
        yy=t[nextfr];
        
        while(yy-lyy>=1.){
            lyy+=1;
          //  xx+=1;
        }
        
        y[i]=yy-lyy;
        xx=x[i]=yy/100;
        putPixel(sc, x[i]*scw,  y[i]*sch,0xFFFFFF);

 //      printf("%lf %lf\n",x[i],y[i]);
        for(j=i-1;j>=0;j--){
        //    if(x[i]-x[j]>rmax)
          //      break; 
            
           // if(y)
            dy=(y[i]-y[j]);
            if(fabs(dy)>0.5){
                if(fabs(1-dy)<fabs(-1-dy))
                    dy=1-dy;
                 else
                    dy=-1-dy;
            }
            /*
            if(dy>0.5)
              dy=1-y[i]+y[j];
            if(dy<-0.5)
              dy=-1 - dy;
            */
            r=(x[i]-x[j])*(x[i]-x[j])+(dy*dy);
           // r=r*r;
          //  if(r>rmax*rmax)
            //    continue;
            //            r=r*r;
           // a=atan2(y[i]-y[j],x[i]-x[j]);
            
            koef=q[i]*q[j]/r;
            k+=fabs(dy)*koef/(x[i]-x[j]);
            dx+=(x[i]-x[j])*koef;
            v+=dy/(x[i]-x[j])*koef;
            d+=koef;
        }        
    }    
    
    
    res.k=k/d;
    res.v=v/d;
    res.k_koef=k;
    res.v_koef=v;
    res.koef=d;
    res.dx=dx;
    return res;
}


    
void  DrInt(double d){
    double freqs[10];
    double amps[10];
    double ph[10];
    freqs[0]=1;
    freqs[1]=1*pow(2,d/12.);
    amps[0]=1;
    amps[1]=1;
    ph[0]=0.3;
    ph[1]=0.3;
    struct speqPoint r; 
     DrawInt(freqs,amps,ph,2,2); 
    r.ns=1;
    r.d[0]=d;
}
void  DrInt3(int d1,int d2){
    double freqs[10];
    double amps[10];
    double ph[10];
     freqs[0]=1;
     freqs[1]=1*pow(2,d1/12.);
     freqs[2]=1*pow(2,d2/12.);
    amps[0]=1;
    amps[1]=1;
    amps[2]=1;
    ph[0]=0.3;
    ph[1]=0.3;
    ph[2]=0.3;
    struct speqPoint r;
 //   if(d!=0)
    DrawInt(freqs,amps,ph,3,2); 

   // else
     //   r=viewFreq(freqs,amps,ph,1,0.3,2.0001); 
    
//    printf("3Tone %d %d: k=%lf, v=%lf\n",d1,d2,r.k,r.v);
}


struct speqPoint  printInt(double d){
    double freqs[10];
    double amps[10];
    double ph[10];
    freqs[0]=1;
    freqs[1]=1*pow(2,d/12.);
    amps[0]=1;
    amps[1]=1;
    ph[0]=0.3;
    ph[1]=0.3;
    struct speqPoint r;
 //   if(d!=0)
        r=viewFreq(freqs,amps,ph,2,0.3,2.0001); 
    r.ns=1;
    r.d[0]=d;
   // else
     //   r=viewFreq(freqs,amps,ph,1,0.3,2.0001); 
    return r;
//    printf("Int %d: k=%lf, v=%lf\n",d,r.k,r.v);
}
struct speqPoint print3Tone(int d1,int d2){
    double freqs[10];
    double amps[10];
    double ph[10];
     freqs[0]=1;
     freqs[1]=1*pow(2,d1/12.);
     freqs[2]=1*pow(2,d2/12.);
    amps[0]=1;
    amps[1]=1;
    amps[2]=1;
    ph[0]=0.3;
    ph[1]=0.3;
    ph[2]=0.3;
    struct speqPoint r;
 //   if(d!=0)
    r=viewFreq(freqs,amps,ph,3,0.5,2.0001); 

    r.ns=2;
    r.d[0]=d1;
    r.d[1]=d2;
    return r;
   // else
     //   r=viewFreq(freqs,amps,ph,1,0.3,2.0001); 
    
//    printf("3Tone %d %d: k=%lf, v=%lf\n",d1,d2,r.k,r.v);
}
void cls(){
    int x,y;
    for(x=0;x<scw;x++){
        for(y=0;y<sch;y++)
            putPixel(sc,x,y,0);
    }
}
void sortk(struct speqPoint* m,int n){
    int i,j;
    struct speqPoint t;
    for(i=0;i<n;i++)
        for(j=0;j<i;j++){
            if(m[i].k<m[j].k){
                t=m[i];
                m[i]=m[j];
                m[j]=t;
            }
        
        }
}
void sortv(struct speqPoint* m,int n){
    int i,j;
    struct speqPoint t;
    for(i=0;i<n;i++)
        for(j=0;j<i;j++){
            if(m[i].v<m[j].v){
                t=m[i];
                m[i]=m[j];
                m[j]=t;
            }
        
        }
}


void printIt(struct speqPoint* m,int n){
    int d1,d2;
    const char *intervals[13]={"Prima","m Sec","b Sec","m Tercya","b Tercya","Kvarta","3Tone","Kvinta","m Sexta","b Sexta","m Septima","b Septima","Oqtava"};
//    const char* sobr[3]={"1", "Second","T"}
    
    for(int i=0;i<n;i++){
        printf("%dTone:",m[i].ns+1);
        for(int j=0;j<m[i].ns;j++)
            printf(" %lf",m[i].d[j]);
        printf(": k=%lf, v=%lf, koef=%lf, dx=%lf",m[i].k,m[i].v,m[i].koef,m[i].dx);
        if(m[i].ns==1){
            if(fabs(m[i].d[0]-(int)m[i].d[0])<0.0001){
                printf("    ( %s )\n",(const char*)intervals[(int)m[i].d[0]]);
            }
        }else if(m[i].ns==2){
            d1=m[i].d[0];
            d2=m[i].d[1];
            int sh,obr,dd1,dd2;
            obr=0;
            while(1){
                dd1=d2-d1;
                dd2=12 - d1;
                if(dd2<d2){
                    obr++;
                    d1=dd1;
                    d2=dd2;
                }else
                 break;
            }
            printf("    (%d-st of ",obr+1);
            if(d1==3 && d2-d1==3){
                printf("    small )\n ");
            }else if(d1==4 && d2 -d1 == 4){
                printf("    big )\n ");
            }else if(d1==3 && d2 -d1 == 4){
                printf("    minor )\n ");
            }else if(d1==4 && d2 -d1 == 3){
                printf("    major )\n ");
            }else{          
                printf(" %d %d )\n",d1,d2-d1);
            }
        }else{
            printf("\n");
        }
    }
    


}
int main(){
   struct speqPoint ints[26];
   struct speqPoint _3tones[13*13];
    int ij=0;
    int j,i;
 
    sc=makeScreen(); 
    scw=sc->w;
    sch=sc->h;
/*    for(i=0;i<6;i++){
          DrInt(2+i*12);
//          printf("%d\n",ma[i]);
            SDL_Flip( sc );
             while(readKey()<0);
//            cls();

    }
 
 
 return 0;
  */  int ma[7]={2,4,5,7,9,10};
    int mi[7]={2,3,5,7,8,10};
 /*   for(i=0;i<6;i++){
          DrInt(ma[i]);
          printf("%d\n",ma[i]);
            SDL_Flip( sc );
             while(readKey()<0);
//            cls();

    }
    for(i=0;i<6;i++){
          DrInt(mi[i]);
          printf("%d\n",mi[i]);
            SDL_Flip( sc );
             while(readKey()<0);
  //          cls();

    }
    
    return 0;
 */
  /* while(1)
    for(i=1;i<=100;i++){
        for(j=1;j<i;j++){
          if(i%12==0 || j%12 ==0)
           continue;
          DrInt3(i,j);
          //printf("%d %d\n",i,j);
            SDL_Flip( sc );
             while(readKey()<0);
            cls();

        }
    }
    
    
    return 0;
    for(i=0;i<=12;i++){
      ints[i]=printInt(i);
        SDL_Flip( sc );
//         while(readKey()<0);
        cls();

    }

 
 */
 
    for(i=1;i<100;i++){
     for(j=1;j<i;j++,ij++){
      DrInt3(i,j);
      /* _3tones[ij]=print3Tone(j,i);
        _3tones[ij].k=(ints[i].k_koef+ints[j].k_koef +ints[i-j].k_koef) /(ints[i].koef+ints[j].koef + ints[i-j].koef) +
                    fabs(ints[i].v_koef-ints[j].v_koef)*(ints[i].dx+ints[j].dx)
                    +
                     fabs(ints[i].v_koef-ints[i-j].v_koef)  *(ints[i].dx+ints[i-j].dx);///(ints[i].koef+ints[i-j].koef);
                     
                     
        _3tones[ij].v=(ints[i].v_koef+ints[j].v_koef + ints[i-j].v_koef)/(ints[i].koef+ints[j].koef + ints[i-j].koef);
        */
          SDL_Flip( sc );
        printf("%d %d\n",i,j);
        while(readKey()<0);
        cls();
     }
    }
 
 

    sortk(ints,13);
    printIt(ints,13);
    for(i=0;i<13;i++){
        printInt(ints[i].d[0]);
        SDL_Flip( sc );
        printf("%lf\n",ints[i].d[0]);
        //while(readKey()<0);
        cls();

    }
    printf("\n\n\n\n=======================\n\n\n\n");
    
    sortv(ints,13);
    for(i=0;i<13;i++){
        printInt(ints[i].d[0]);
        SDL_Flip( sc );
        printf("%lf\n",ints[i].d[0]);
//        while(readKey()<0);
        cls();

    }
    
 
    sortk(_3tones,ij);
    printIt(_3tones,ij);
    printf("\n\n\n\n\n=======================\n\n\n\n");
    sortv(_3tones,ij);
    printIt(_3tones,ij);

    return 0;
}
