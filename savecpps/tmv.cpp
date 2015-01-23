#include"hsv.cpp"
#ifndef tmvMOD
#define tmvMOD
/*
tmv - colorspace model
t - temperge, m - mood, v - value, based on hsv model of color cirle, where blue-green (cyan) is 0 of temperge, red-orange is 1 of temperge, 
purpure side of circle (darker tones of color) - 0 of mood, yelow is lighter - 1 of mood, and native value to hsv model.

*/


struct tmv{// all beetween 0..1
    double t,m,v;
};

inline double fsign(double a){
    if(a>=0.0)
        return 1.;
    return -1.;

}
struct hsv_colour tmv2hsv(struct tmv c,double gray,double back){ 
    struct hsv_colour hsv_c; 
    
    hsv_c.s=fabs(c.m-0.5)*2;
    hsv_c.h=(c.t*fsign(c.m-0.5)/2.+1/6.);
    if(back<0.001){
        hsv_c.v=c.v- c.v*gray* + gray*(0.5-fabs(c.m-0.5))/0.5;
    }else{
        if(c.m>0.5){
            hsv_c.v=back + c.v*(1-back); // -gray*(1-fabs(c.m-0.5)/0.5);
        
        }else{
            hsv_c.v=back - c.v*(back);
        
        
        }
    
    }
    
    while(hsv_c.h<0.)
        hsv_c.h=hsv_c.h+1.;
    while(hsv_c.h>=1.)
        hsv_c.h=hsv_c.h-1.;

    if(hsv_c.s>=1.)
        hsv_c.s=0.9999;

    if(hsv_c.s<0.)
        hsv_c.s=0.;

    if(hsv_c.v>=1)
        hsv_c.v=.99999;

    if(hsv_c.v<0.)
        hsv_c.v=0.;

    
    return hsv_c;
}

#endif
