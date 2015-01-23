#include"sens.cpp"
#include"koefs.cpp"
#ifndef GLOPTSMOD
    #define GLOPTSMOD
    
    #define GLOPTS 15
    #define GLOPTKOEFS (KOEFNUM+1)
    
    double glOpt[GLOPTS];
    double lglOpt[GLOPTS];
    
    double glOptKoefs[GLOPTS*GLOPTKOEFS];
    double lglOptKoefs[GLOPTS*GLOPTKOEFS];
   // struct sense GLSense[GLOPTS];

    
void zeroGlOpt(){
    int i,j;
//    for(i=0;i<GLOPTS;i++){
     //   zeroSense(GLSense+i);
     for(i=0;i<GLOPTS;i++){
        glOpt[i]=0.;
    }
    glOpt[2]=0.5;
    glOpt[3]=0.5;
    glOpt[4]=0.5;
    glOpt[6]=0.5;
    glOpt[7]=0.5;
        

        for(j=0;j<GLOPTS*GLOPTKOEFS;j++){
                glOptKoefs[j]=0.;
            }
    
  //  }
}
double lopt[GLOPTS];
void calcGlOpt(double *opt){
        int i,j;
        double v;
        for(i=0;i<GLOPTS;i++){
            v=glOpt[i];
            for(j=0;j<KOEFNUM;j++){
                v+=soundKoefs[j]*glOptKoefs[i*GLOPTKOEFS+ j+1];
            }
            double soft=glOptKoefs[i*GLOPTKOEFS+0];
            if(v>1.)
                v=1.;
            if(v<0.)
                v=0.;
            if(soft>1.)
                soft=1.;
            if(soft<0.)
                soft=0.;
            opt[i]=lopt[i]*soft+v*(1-soft);
            lopt[i]=opt[i];
            
            //senseValue(GLSense+i,v);
        }
    
    
    }
    
    
    
#endif

