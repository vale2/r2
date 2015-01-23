#include<stdio.h>
#include<math.h>

void ratio(double d,int &a,int &b){
    int i,j;
    double w;
    double mw=10;
    for(i=1;i<12;i++){
        for(j=i;j<12;j++){
            w=fabs(j/(double)i - d);
            
            if(mw>w){
                a=i;
                b=j;
                mw=w;
            }
        }
    }

}

int main(){
    double a=1;
    int i,b,c;
    for(i=0;i<12;i++,a*=pow(2,1/12.)){
        ratio(a,b,c);
        int x,y,z;
        x=0;
        while(c>=b){
            x++;
            c-=b;
        }
        double t;
        
        if(c>0){
            t=c/(double)b;
        }else
            t=1;
        printf("%d (%d + %d/%d) (%0.3f)\n",i,x,c,b,t);
    
    }
    


    return 0;
}
