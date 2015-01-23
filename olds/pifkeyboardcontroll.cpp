#define eqEPS 0.0000000001
#define notEq(a,b) ((fabs((a)-(b))>eqEPS)?1:0)

#define SHIFT 50
#define CONTRL  37
#define ALT   64
#define BACKSPACE 22
#include"koefs.cpp"
extern short int keys[256];
extern int mode;
extern int soundControllFlag;
extern int pifPosition;


/*
double pifColorSpeedr=0.01;
double pifColorSpeedg=0.11;
double pifColorSpeedb=1.11;
*/



double nextRational(double r){
       int a,b;
       double rr,ans;
       //char s[128]="Next Rational: 1\n";
       ans=5.;
       for(b=1;b<60;b++){
        for(a=0;a<=b && a<b ;a++){
            rr=((double)a)/b;
            if(notEq(r,rr) && rr>r && rr<ans){
                ans=rr;
                //sprintf(s,"Next Rational: %d/%d\n",a,b);
            }
        }
       
       }
      //  printf("%s",s);
    return ans;
}

double previusRational(double r){
       int a,b;
       double rr,ans;
       //char s[128]="Prev Rational: 0\n";
       ans=0;
       for(b=1;b<60;b++){
        for(a=0;a<=b && a<b ;a++){
            rr=((double)a)/b;
            if(notEq(r,rr) && rr<r && rr>ans){
        //        sprintf(s,"Prev Rational: %d/%d\n",a,b);
                ans=rr;
            }
        }
       
       }
      // printf("%s",s);
    return ans;
}


void pifKeyboardControll(){
    double*ck;
    ck=controllKoef;
    if(mode!=5)
        return;
   // if(keys[96]==2){
   //     ALLFRAQ=!ALLFRAQ;
   // }
    /*
    
    ck[0*KOEFNUM+1]=7;
    ck[0*KOEFNUM+0]=7;
    ck[0*KOEFNUM+4]=11;
    
    //pifangle
    dkoef[5]=M_PI/10000;
    
    
    
    //pscale
    ck[4*KOEFNUM+6]=10;
    koefascell[4]=1./10.0;
    
    //pwind
    ck[3*KOEFNUM+5]=10;
    koefascell[3]=1./10.0;
    
    
    */
    
   
    
    
    if(keys[64]){//alt
        if(keys[55] == 2){
            ck[0*KOEFNUM+0]=ck[0*KOEFNUM+0]*1.1;            
        }
    
        if(keys[54] == 2){
            ck[0*KOEFNUM+0]=ck[0*KOEFNUM+0]/1.1;            
        }    
        if(keys[46]){
                zeros[3]=zeros[3]+0.03;
             }                              // l
        if(keys[59]){

                zeros[3]=zeros[3]-0.03;
            }                               // ,
         if(keys[47]){

                zeros[4]=zeros[4]+0.03;
         }                             // ;
         if(keys[60]){

                zeros[4]=zeros[4]-0.03;
          }                           
        
        
    }
     if(keys[50]){//shift
      /*  if(keys[55] == 2){
            ck[0*KOEFNUM+1]=ck[0*KOEFNUM+1]*1.1;            
        }
    
        if(keys[54] == 2){
            ck[0*KOEFNUM+1]=ck[0*KOEFNUM+1]/1.1;            
        } 
        */
        if(keys[46]){
                ck[3*KOEFNUM+5]=ck[3*KOEFNUM+5]*1.1;
             }                              // l
        if(keys[59]){

                ck[3*KOEFNUM+5]=ck[3*KOEFNUM+5]/1.1;
            }                               // ,
         if(keys[47]){

                ck[4*KOEFNUM+6]=ck[4*KOEFNUM+6]*1.1;
         }                             // ;
         if(keys[60]){

                ck[4*KOEFNUM+6]=ck[4*KOEFNUM+6]/1.1;
          }         
        
        
           
    }
    if(keys[37]){//ctrl
        if(keys[55] == 2){
            ck[0*KOEFNUM+4]=ck[0*KOEFNUM+4]*1.1;            
        }
    
        if(keys[54] == 2){
            ck[0*KOEFNUM+4]=ck[0*KOEFNUM+4]/1.1;            
        }    

                          



    }
    
    if(keys[45]==2){
        zeros[9]=zeros[9]+1.;   //k
     }
    if(keys[44]==2){  //j
        if(zeros[9]>1.001)
            zeros[9]=zeros[9]-1.;   
     }
     if(keys[30]==2){  //j
        int pifParity;
        pifParity=zeros[10];
        pifParity=pifParity++;
        pifParity=pifParity&1;
        zeros[10]=pifParity;
        
        //printf("pifParity: %d\n",pifParity);

     }
     
     
    if(keys[23]==2){
        soundControllFlag=!soundControllFlag;   
     }
    if(keys[110]){
            setZeroPifControllKoef();   
    }
    if(keys[52] == 2){
            int z;
            z=zeros[1];
            z++;
            z=z%4;
            zeros[1]=z;
            //printf("naked! %f\n",zeros[1]);

     }                          // z
     if(keys[53] == 2){
        int z;
        z=zeros[2];
        if(z)
         zeros[2]=0.;
         else
         zeros[2]=1.;
            
      }                      // x
      if(keys[40] == 2){
        pifPosition=!pifPosition;
      }  //d
      if(keys[54] == 2){//c
            int z;
            if(keys[37]){//ctrl
                if(zeros[15]>0.9999)
                    zeros[15]=zeros[15]-1.;
                
            }else
            if(!keys[50]){///!SHUFT
            
                z=zeros[0];
                if(z)
                     zeros[0]=z-1;
           }else{//SHIFT
              
               z=maxDrawKoef[0];
                if(z>2)
                     maxDrawKoef[0]=z-1;
           
           }
       }                        
       
       
       if(keys[55] == 2){//v
            int z;
            if(keys[37]){//ctrl
                if(zeros[15]<9)
                    zeros[15]=zeros[15]+1.;
                
            }else
            if(!keys[50]){///!SHUFT
                z=zeros[0];
                if(z<16)
                     zeros[0]=z+1;
            }else{///SHIFT
                z=maxDrawKoef[0];
                if(z<16)
                     maxDrawKoef[0]=z+1;
            
            }

        }
        
        
        
        
        
        if(keys[46]&&keys[CONTRL]){

                koefascell[3]*=1.1;
             }                              // l
        if(keys[59]&&keys[CONTRL]){

                koefascell[3]/=1.1;
            }                               // ,
         if(keys[47]&&keys[CONTRL]){

                koefascell[4]*=1.1;
         }                             // ;
         if(keys[60]&&keys[CONTRL]){

                koefascell[4]/=1.1;
          }                             // .
          if(keys[48]){
            //if(mode==5)
               if(keys[64]){//alt
                    if(keys[48]==2){
                        dkoef[5]=nextRational(dkoef[5]/M_PI/2.)*M_PI*2.;
                    }
                }else if(keys[50])
                    dkoef[5]*=1.0001;
                else 
                    dkoef[5]*=1.1;
          }                            // '
          if(keys[61]){
                if(keys[64]){
                    if(keys[61]==2){
                        dkoef[5]=previusRational(dkoef[5]/M_PI/2.)*M_PI*2.;
                    }
                 }else if(keys[50]){
                    dkoef[5]/=1.0001;
                 }else
                    dkoef[5]/=1.1;
                
           }                             // /
           if(keys[56]==2){

                   dkoef[3]*=-1;
           }                              // b
           if(keys[57]==2){

                dkoef[4]*=-1;
            }                              // n
            if(keys[58]==2){

                    dkoef[5]*=-1;
            }                              // m
            if(keys[27]){

                    zeros[6]*=1.1;
            }                              // r
            if(keys[41]){

                    zeros[6]/=1.1;
             }                              // f
             if(keys[28]){

                    zeros[7]*=1.1;
             }                              // g
             if(keys[42]){

                    zeros[7]/=1.1;
             }                              // f
             if(keys[29]){

                    zeros[8]*=1.1;
             }                              // g
             if(keys[43]){

                    zeros[8]/=1.1;
             }

    if(keys[112]){
       if(!keys[64]){//!ALT{
          if(zeros[13] < 180. && keys[112] == 2)
            zeros[13]=zeros[13]+1.;
        }else{
           ck[12*KOEFNUM+6]=ck[12*KOEFNUM+6]*1.01;
           ck[12*KOEFNUM+5]=ck[12*KOEFNUM+5]*1.01;;
        }
    }
    if(keys[117]){
        if(!keys[64]){//!ALT{
            if(zeros[13] > 3.01 && keys[117] == 2)
                zeros[13]=zeros[13]-1.;
        }else{
           ck[12*KOEFNUM+6]=ck[12*KOEFNUM+6]/1.01;
           ck[12*KOEFNUM+5]=ck[12*KOEFNUM+5]/1.01;;
        }
    }


}

