#ifndef MYGLUTMOD
#define MYGLUTMOD
void start3d_3a(double r,double a1,double a2,double a3,double fov){
    double ax,ay,az,si,co;
    double bx,by,bz,cx,cy,cz,dx,dy,dz;
    ax=cos(a1);
    ay=sin(a1)*cos(a2);
    az=sin(a1)*sin(a2);

    bx=-ay;
    by=ax;
    bz=0;

    cx=ay*bz-az*by;
    cy=az*bx-ax*bz;
    cz=ax*by-ay*bx;
    
    si=sin(a3);
    co=cos(a3);
    dx=bx*si+cx*co;
    dy=by*si+cy*co;
    dz=bz*si+cz*co;

    ax*=r;
    ay*=r;
    az*=r;
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov,(double)GLW/GLH,0.001,1000);

            
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    camz=az;
    camx=ax;
    camy=ay;
    platesN=0;
    gluLookAt(ax,ay,az ,0,0,0, dx,dy,dz);
  //glDisable(GL_BLEND);
   glDisable(GL_TEXTURE_2D);
    
   glEnable(GL_BLEND);
   glEnable(GL_DEPTH_TEST);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void drawAllPlates();
void end3d_3a(GLuint tex){
    drawAllPlates();
    glEnable(GL_TEXTURE_2D);
    saveGlScreen2Tex(tex);
    glPopMatrix();
    glPopAttrib();

}
#endif
