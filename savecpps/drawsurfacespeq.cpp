#include"ok_colorline.cpp"

struct rgb midcolor(struct rgb a,struct rgb b);



void drawZSurface(double x,double y,double z,struct rgb c,double w,double h){
    glBegin(GL_QUADS);    
    glColor4ubv((const GLubyte*)&c);
    glVertex3f (x-w/2,y-h/2,z);
    glVertex3f (x-w/2,y+h/2,z);
    glVertex3f (x+w/2,y+h/2,z);
    glVertex3f (x+w/2,y-h/2,z);
    glEnd();
}
void drawSurfaceSpeq(GLuint tex,struct qs*q,double r,double a1,double a2,double fov,double pw,double mindl){
    double cx,cy,cz;
    double hx,hy,hz;
    
    cx=r*cos(a1);
    cy=r*sin(a1)*cos(a2);
    cz=r*sin(a1)*sin(a2);

    hx=r*cos(a1+M_PI/2);
    hy=r*sin(a1+M_PI/2)*cos(a2+M_PI);
    hz=r*sin(a1+M_PI/2)*sin(a2+M_PI);

    
//    saveGlScreen();
    glBindTexture(GL_TEXTURE_2D, tmpt);
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov,(double)GLW/GLH*aspectKoef,0.1,1000);

            
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(cx,cy,cz ,0,0,0, hx,hy,hz);
 
 // glEnable(GL_ALPHA_TEST);
//  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);

//  glPointSize(2.0);

  //glBegin(GL_LINE_STRIP);
  
  int x,y,z;
  double ax,ay,h,w1,w2,w3,az;
  double*p,*mm,*dis;
  struct rgb c,c2;
  //mm05
  
  w1=1./q->tones;
  w2=1./q->oqs;
  w3=1./2/q->oqs;
     
  glDisable(GL_TEXTURE_2D);
    
  p=q->dlinDises;
  for(y=0;y<q->oqs-2;y++)     
   for(x=0;x<q->tones;x++){
   //for(z=0;z<q->tones*2;z++,p++)
     double ikoefs[13];
     double i3koefs[13];
     int zz;  
     zz=y*(int)q->tones+x;
     for(int i=0;i<=12;i++){
                    ikoefs[i]=getDLD(*q,x,y,i);
                    i3koefs[i]=getDLD3(*q,x,y,i);
                }
   c=calcIColor(ikoefs,i3koefs,q->ks[zz]);
   c.o=0;
   ax=(x /(double)q->tones -0.5 ) *2.;
   ay=(y /(double)q->oqs -0.5 ) *2.;
   az=-1;
        if(correctColorFlag){
                        c=rgbCorrector(c);

        }
//        spx[x][y][0]=ax;
  ///      spy[x][y][0]=ay;
     //   spz[x][y][0]=az;
       // spc[x][y][0]=c;
        //        glColor4ubv((const GLubyte*)&c2);
        double aw,ah;

   aw=2./q->tones;
   ah=2./q->oqs;

  // drawZSurface(ax,ay,az,c,aw,ah);
   
   for(int di=1;di<=q->tones;di++){
        double l,a,r;
        if(zz+di<0 || zz+di>=q->oqs*(int)q->tones)
            continue;
        int ddi;
        ddi=di+q->tones-1;
        
        double d,dil;
        dil=pow(p[zz*2*(q->tones)+ddi],pw);
        ax=(x /(double)(q->tones-1) -0.5 ) *2.;
        ay=(y /(double)(q->oqs-3) -0.5 ) *2.;
        az=(di/(double)q->tones -0.5)*2;//*q->mm05[x+y*(q->tones)]
        aw=2.*dil/q->tones;
        ah=2.*dil/q->oqs;
        
        
        unsigned  hh;
        c2=c;//midcolor(getDiColor(di),c);
       // hh=255*pow(p[zz*2*(q->tones)+ddi],pw);
      //  c2.r=c.r*hh/255;
      //  c2.g=c.g*hh/255;
      //  c2.b=c.b*hh/255;
      
  //      if(correctColorFlag){
      //                  c2=rgbCorrector(c2);

    //    }
        c2.o=dil*255;

        spx[x][y][di]=ax;
        spy[x][y][di]=ay;
        spz[x][y][di]=az;
        spc[x][y][di]=c2;
        //        glColor4ubv((const GLubyte*)&c2);
        if(dil>mindl)
            drawZSurface(ax,ay,az,c2,aw,ah);
        
        
    
      
    }    
  }
  glEnable(GL_TEXTURE_2D);
    
    
  
 
 
    saveGlScreen2Tex(tex);
     //    glFinish();
  //     glBindTexture(GL_TEXTURE_2D, lsct);
    
   //    SDL_GL_SwapBuffers();

    glPopMatrix();
    glPopAttrib();
 //   restoreGlScreen();
}
