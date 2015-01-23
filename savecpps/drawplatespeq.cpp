#include"interfer.cpp"

extern GLuint tmpt;
  struct rgb qsc[16][16];
  double qsx[16][16];
  double qsy[16][16];


void quad(double x1,double y1,struct rgb c1,
double x2,double y2,struct rgb c2,
double x3,double y3,struct rgb c3,
double x4,double y4,struct rgb c4){
    glBegin(GL_QUADS);
    glColor4ubv((const GLubyte*)&c1);
    glVertex2f (x1,y1);

    glColor4ubv((const GLubyte*)&c2);
    glVertex2f (x2,y2);
    glColor4ubv((const GLubyte*)&c3);
    glVertex2f (x3,y3);
    glColor4ubv((const GLubyte*)&c4);
    glVertex2f (x4,y4);

    glEnd();
}
void tria(double x1,double y1,struct rgb c1,
double x2,double y2,struct rgb c2,
double x3,double y3,struct rgb c3
){
    glBegin(GL_TRIANGLES);
    glColor4ubv((const GLubyte*)&c1);
    glVertex2f (x1,y1);

    glColor4ubv((const GLubyte*)&c2);
    glVertex2f (x2,y2);
    glColor4ubv((const GLubyte*)&c3);
    glVertex2f (x3,y3);

    glEnd();
}
struct rgb midcolor(struct rgb a,struct rgb b){
    struct rgb r;
    int rr,gg,bb;
    rr=a.r+(int)b.r;
    gg=a.g+(int)b.g;
    bb=a.b+(int)b.b;
   r.r=rr/2;
   r.g=gg/2;
   r.b=bb/2;
   return r;
}

#define min2(a,b) (((a)>(b))?(b):(a))
#define min3(x,y,z) (min2(min2((x),(y)),(z)))
void drawPlateSpeq(GLuint tex,struct qs*q,double rgamma,double a0,double normLen){
  
//    saveGlScreen();
    glBindTexture(GL_TEXTURE_2D, tmpt);

   glClearColor(0,0,0,1);
            
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glDisable(GL_BLEND);
 
  //glEnable(GL_BLEND);
 // glEnable(GL_DEPTH_TEST);
//  glPointSize(2.0);

  //glBegin(GL_LINE_STRIP);
  
  int x,y,z,ww,hh;
  double r,al,ax,ay,h,w1,w2,w3,az;
  double*p;
  double lfx,lfy;
  lfx=-100;
  lfy=-100;
  struct rgb c,c2,lfc;
  p=q->dlinDises;
  w1=1./q->tones;
  w2=1./q->oqs;
  w3=1./2/q->oqs;
  
  glPointSize(2);
  double allmm=0;
  double partmm=0;
  for(y=0;y<q->oqs;y++)     
   for(x=0;x<q->tones;x++){
            allmm+=q->mm05[x+y*(q->tones)];
   }

  
  
     
  glDisable(GL_TEXTURE_2D);
  for(y=0;y<q->oqs;y++)     
   for(x=0;x<q->tones;x++){
   //for(z=0;z<q->tones*2;z++,p++)
     double ikoefs[13];
     double i3koefs[13];
     int zz;  
     zz=y*(int)q->tones+x;
     partmm+=q->mm05[x+y*(q->tones)];
  
     for(int i=0;i<=12;i++){
                    ikoefs[i]=getDLD(*q,x,y,i);
                    i3koefs[i]=getDLD3(*q,x,y,i);
                }
     c=calcIColor(ikoefs,i3koefs,q->ks[zz]);
       if(correctColorFlag){
                        c=rgbCorrector(c);

        }
     
     qsc[x][y]=c;
     r=pow(   1-((zz/(double)q->oqs/(double)q->tones)*normLen +(1-normLen)*partmm/allmm)   ,rgamma);
     al=x*2*M_PI/q->tones;
     ax=r*sin(al+a0)*GLW/2+GLW/2;
     ay=r*cos(al+a0)*GLH/2+GLH/2;
     qsx[x][y]=ax;
     qsy[x][y]=ay;
     struct rgb black;
     black.r=0;
     black.g=0;
     black.b=0;
     black.o=0;
     
     
     if(y==0 && x>0){
        double fx,fy,HX,HY,LX,LY;
        fx=(ax+qsx[x-1][y])/2;
        fy=(ay+qsy[x-1][y])/2;
        LX=fx/GLW;
        HX=(GLW-fx)/GLW;
        LY=(fy)/GLH;
        HY=(GLH-fy)/GLH;
        if(LX<=min3(HX,LY,HY)){
          fx=0;
     
        }
        if(LY<=min3(HX,LX,HY)){
          fy=0;
     
        }
        if(HY<=min3(HX,LX,LY)){
          fy=GLH;
     
        }
        if(HX<min3(LX,HY,LY)){
          fx=GLW;
        }
        double fx1,fy1;
        fx1=fx;
        fy1=fy;
        LX=fx/GLW;
        HX=(GLW-fx)/GLW;
        LY=(fy)/GLH;
        HY=(GLH-fy)/GLH;
        if(LX<=min3(HX,LY,HY)&&LX>0.){
          fx1=0;
     
        }
        if(LY<=min3(HX,LX,HY)&&LY>0.){
          fy1=0;
     
        }
        if(HY<=min3(HX,LX,LY)&&HY>0.){
          fy1=GLH;
     
        }
        if(HX<min3(LX,HY,LY)&&HX>0.){
          fx1=GLW;
        }
        
        
        
          /* if(lfx<-10){
                tria(ax,ay,c,
                    qsx[x-1][y],qsy[x-1][y],qsc[x-1][y],
                    fx,fy,midcolor(qsc[x-1][y],c));
            }else{
                quad(ax,ay,c,
                    qsx[x-1][y],qsy[x-1][y],qsc[x-1][y],
                    lfx,lfy,lfc,
                    fx,fy,midcolor(qsc[x-1][y],c));
            
            
            }
    
            */
            if(x>0)
                quad(ax,ay,c,
                    qsx[x-1][y],qsy[x-1][y],qsc[x-1][y],
                    fx,fy,midcolor(qsc[x-1][y],c),
                    fx1,fy1,midcolor(black,midcolor(qsc[x-1][y],c))
                    
                    
                    );
            
            
            
            
        lfc=midcolor(qsc[x-1][y],c);
        lfx=fx;
        lfy=fy;
     }
     
     if(y==q->oqs-1&&x==0){
        tria(ax,ay,c,
        qsx[q->tones-1][y-1],qsy[q->tones-1][y-1],qsc[q->tones-1][y-1],
        GLW/2,GLH/2,midcolor(qsc[q->tones-1][y-1],c));
        
     }
     
     
     
     if(y==q->oqs-1&&x>0){
        tria(ax,ay,c,
        qsx[x-1][y],qsy[x-1][y],qsc[x-1][y],
        GLW/2,GLH/2,midcolor(qsc[x-1][y],c));
        
     }
     
     if(x>0&&y>0){
        quad(ax,ay,c,
        qsx[x-1][y],qsy[x-1][y],qsc[x-1][y],
        qsx[x-1][y-1],qsy[x-1][y-1],qsc[x-1][y-1],
        qsx[x][y-1],qsy[x][y-1],qsc[x][y-1]);
     }else if(y>1){
        quad(ax,ay,c,
        qsx[q->tones-1][y-1],qsy[q->tones-1][y-1],qsc[q->tones-1][y-1],
        qsx[q->tones-1][y-2],qsy[q->tones-1][y-2],qsc[q->tones-1][y-2],
        qsx[x][y-1],qsy[x][y-1],qsc[x][y-1]);
        
     }
  }
  //ww=GLW*step;
  //hh=GLH*step;
 // for(y=0;y<)
  
  
    glEnable(GL_TEXTURE_2D);
    saveGlScreen2Tex(tex);
    glClearColor(0,0,0,1);
    glColor4f(0,0,0,1);

  //  restoreGlScreen();
    
}


