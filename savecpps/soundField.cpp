


double ampDi(int di){
    return 1.;
}
double xy2t(double x,double y){
    return fabs(x-qsAll.tones)/10+fabs(qsAll.oqs-y)/10;
}
#define sf_DISES 13
int sf_kosd[sf_DISES]={0,12,7,5,3,4,8,9,6,2,10,1,11};
int sf_kosdd[sf_DISES]={ 0, 11, 9, 4, 5, 3, 8, 2, 6, 7, 10, 12, 1};

double sf_freqs[sf_DISES]={1,1.2,2,2.2,2.4,2.7,2.9,3.1,3.5,3.9,4.7,5.6,5.6};

double freqDi(int di){
    di-=qsAll.tones-1;
    di=abs(di);
    
    return sf_freqs[sf_kosdd[di]];

}
double calcZ(int adr,double dx,double dy,double x,double y){
    double l1,l2,l3,l4,lu,ld,l,z;
    int adr2,adr3,adr4;
    z=0;
    int oqst;
    oqst=qsAll.oqs*qsAll.tones;
    adr2=adr+1;
    adr3=adr+12;
    adr4=adr+13;
    if(adr2>=oqst){
        adr2=adr;
    }
    if(adr3>=oqst){
        adr3=adr;
    }
    if(adr4>=oqst){
        adr4=adr3;
    }
    int di;
    for(di=0;di<=qsAll.tones+qsAll.tones-1;di++){
           l1=qsAll.linDises[adr*2*(qsAll.tones)+di];
           l2=qsAll.linDises[adr2*2*(qsAll.tones)+di];
           l3=qsAll.linDises[adr3*2*(qsAll.tones)+di];
           l4=qsAll.linDises[adr4*2*(qsAll.tones)+di];
           lu=l3*(1-dx)+l4*dx;
           ld=l1*(1-dx)+l2*dx;
           l=ld*dy+lu*(1-dy);
           z+=l*ampDi(di)*sin(xy2t(x,y)*freqDi(di));   
        
    }
    return z;
}

void drawSoundField(){
    double x,y,z;
    double dx,dy,sx,sy;
    int adr,x1,y1;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100,(double)GLW/GLH,1,1000);

    
      glPushAttrib(GL_ALL_ATTRIB_BITS);
      glPushMatrix();

      glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      gluLookAt(0,0,20, 0,0,0, 0,1,0);

   //   glPointSize(2.0);

    
    
    dx=0.1;
    dy=0.1;
      glBegin(GL_POINTS);

 //   glColor3ub(1,1,1);
   // glVertex3d(0,0,0);
            
    for(y=0;y<qsAll.oqs;y+=dy)
        for(x=0;x<qsAll.tones;x+=dx){
            x1=round(x);
            y1=round(y);
            adr=x1+y1*qsAll.tones;
            sx=x-x1;
            sy=y-y1;
            z=calcZ(adr,sx,sy,x,y);
 //          glColor3ub(v[i].r, v[i].g, v[i].b);
            glColor3ub(x*255/qsAll.tones,255,y*255/qsAll.oqs);

           glVertex3d((x-qsAll.tones/2.), (y-qsAll.oqs/2.), z/400.);
        
        }


  glEnd();
  glFlush();
  SDL_GL_SwapBuffers();
  glPopMatrix();
  glPopAttrib();


}
