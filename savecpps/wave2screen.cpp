

#define W2SW 200
double w2ar[W2SW];
double w2y[W2SW];
double w2vMax=1;
double w2vMin=0;
 
double w2arMax;
void saveGlScreen2Tex(GLuint tex);
void wave2screenOutput(GLuint tex){
//  glEnable(GL_TEXTURE_2D);
  glDisable(GL_TEXTURE_2D);
    glClearColor(0,0,0,1);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glDisable(GL_BLEND);
    double a;
 
    w2arMax=w2arMax*0.999;
    a=w2vMin*0.999+w2vMax/1000;
    w2vMax=w2vMax*0.999+w2vMin/1000;
    w2vMin=a;

    for(int i=0;i<W2SW;i++){
        w2y[i]=log(w2ar[i]+1);
        if(w2y[i]>w2arMax){
            w2arMax=w2y[i];
        }
    }
    glPointSize(4.0);

    glBegin(GL_POINTS);
    glColor4f(1,1,1,0);

    for(int i=0;i<W2SW;i++){
        float y;
        y=GLH - w2y[i]*GLH/w2arMax;
        if(y<GLH-3)
            glVertex2f (i*GLW/W2SW,y);
      //  fprintf(stderr,"%lf ",(double)i*GLW/W2SW);
        
       // fprintf(stderr," %lf\n",(double)w2y[i]*GLH/w2arMax);
    }
    
    
    glEnd();
    
//    war[v*799]=war[v*799]*127./128.;

 // glBindTexture(GL_TEXTURE_2D, tex);
   saveGlScreen2Tex(tex);
//   fprintf(stderr,"wave2screen output\n");

}



void wave2screenInput(double v){
//    fprintf(stderr,"wave2screen input\n");
    if(v<w2vMin){
        w2vMin=v;
    }
    if(v>w2vMax){
        w2vMax=v;
    }
    
    v=(v-w2vMin)/(w2vMax-w2vMin);
    for(int i=0;i<W2SW;i++)
        w2ar[i]=w2ar[i]*127./128.;
    w2ar[(int)(v*(W2SW-1))]+=1;
}
