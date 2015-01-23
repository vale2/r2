#include<stdio.h>
#define SIMPLES 6
int simple[SIMPLES]={2,3,5,7,11,13};
int findSyms(int l){
    if(l==1 || l==0)
        return 0;
    int r=0;
    for(int i=0;i<SIMPLES;i++){
        if(l%simple[i] == 0){
            r=findSyms(l/simple[i])+1;
            break;
        }
        
    }
    return r;
        
}


int _2(int a){
    int r,i;
    for(i=0,r=1;i<a;i++,r*=2);
    return r;
}

int findFree(int i0,int l,int s){
    //int r;
   // if(l==1||l==0)
     //   return 0;
    
    if(s==0){
        if(l>0)
            return _2(l)-1;
        else 
            return 0;
    }
    int r=0;
    for(int i=i0;i<SIMPLES;i++){
        if(l%simple[i] == 0){
            r+=findFree(i,l/simple[i],s-1);
            
        }
        
    }
    return r;
        
}


unsigned int grayencode(unsigned int g) {
    return g ^ (g >> 1);
}

int generateSym(int i0,char*m,int s,int n,int l){
    char mm[360];
    int a,i;
    if(s==0){
        if(n>=_2(l)){
            return _2(l)-1; 
        }
        a=1;
        for(i=0;i<l;i++,a=a*2){
            if(n&a){
                m[i]=1;
            }else{
                m[i]=0;
            }
        }
        return 0;
    }
    
    int r=0;
    int rr=0;
    for(i=i0;i<SIMPLES;i++){
        if(l%simple[i] == 0){
            int j,k;
            int ll=l/simple[i];
            r=generateSym(i,mm,s-1,n-rr,ll);
            if(r==0){
                for(j=0;j<ll;j++){
                   for(k=0;k<simple[i];k++){
                       m[k*ll+j]=mm[j];    
                   }
            
                }
                return 0;
            }else{
                rr+=r;
                continue;
            }
        }
        
    }
    return rr;
}

void gcs(char*m,double s,double n,int l){
    int ms;
    int ss;
    int mn;
    int nn;
    ms=findSyms(l);
    ss=ms*s;
    mn=findFree(0,l,ss);
 
 
    nn=(mn-1)*n;
    if(nn == 0){
        nn=mn-1;
    }
    if(nn==0 || generateSym(0,m,ss,nn,l)!=0){
        for(int i=0;i<l;i++)
            m[i]=1;
    
    }
    
    //nn=grayencode(nn);   

}
