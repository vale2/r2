
#define NTRIBLES 7
#define NOBRTONES 16 
extern double  camz;
extern double  camx;
extern double  camy;
extern int platesN;

void GL3dAt(double a1,double a2,double r,double fov){
    double cx,cy,cz;
    double hx,hy,hz;

    cx=r*cos(a1);
    cy=r*sin(a1)*cos(a2);
    cz=r*sin(a1)*sin(a2);
    hx=r*cos(a1+M_PI/2);
    hy=r*sin(a1+M_PI/2)*cos(a2+M_PI);
    hz=r*sin(a1+M_PI/2)*sin(a2+M_PI);

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov,(double)GLW/GLH,0.1,1000);

            
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  camz=cz;
  camx=cx;
  camy=cy;
  platesN=0;
  gluLookAt(cx,cy,cz ,0,0,0, hx,hy,hz);
  //glDisable(GL_BLEND);
 
  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


}


void GL3dFin(GLuint tex){
    saveGlScreen2Tex(tex);

    glPopMatrix();
    glPopAttrib();
}


struct timbre{
    double basicFreq;
    double obertoneAmps[NOBRTONES];
    double present;
}cur_timbres[NTRIBLES];



double checkFreq(double*freqs,double*amps,int n,double &basic,int garmonic){
    double bprev,bnext;
    int i,j;
    double EPS=basic/10;
    bprev=-100;
    bnext=-100;
    double maxamp;
    double rezFreq;
    for(j=0;j<n;j++){
        if(freqs[j]<basic-EPS){
            bprev=freqs[j];
        }else if(freqs[j]>basic+EPS){
            bnext=freqs[j];
            break;
        }
    }
    maxamp=0;
    if(bprev>-1){
        j--;
        for(;j<n&&freqs[j]<bprev*(garmonic+1);j++);
    
        for(;j<n&&freqs[j]<bnext*(garmonic+1);j++){
            if(maxamp<amps[j]){
                rezFreq=freqs[j]/n;
                maxamp=amps[j];
            }    
        
        }
        basic=rezFreq;
        return maxamp;
    }
//    basic=reFreq;
    return 0;
}

void checkTimbre(double*freqs,double*amps,int n,struct timbre& cur){
    int i;
    cur.present=0;
    double fr;
    double basics[NOBRTONES];
    double prezents[NOBRTONES];
    double baseic=0;
    double cprezent=0;
    double prezent=0;
    
    for(i=0;i<NOBRTONES;i++){
        fr=cur.basicFreq;
        cprezent=checkFreq(freqs,amps,n,fr,i);
        prezents[i]+=cprezent;
        prezent+=cprezent;
        basics[i]=fr;
        cur.obertoneAmps[i]=cprezent;
        baseic+=fr*cprezent;
    }
    baseic/=cprezent;
    cur.present=prezent/NOBRTONES;
    cur.basicFreq=baseic;
}


void     sendTimbres(){
    char s[128];
/*    double basicFreq;
    double obertoneAmps[NOBRTONES];
    double present;
*/
    int k,i;
    for(k=0;k<NTRIBLES;k++){
        sprintf(s,"timbres_%d_baseFreq",k);
        setOpt(s,cur_timbres[k].basicFreq);
        sprintf(s,"timbres_%d_present",k);
        setOpt(s,cur_timbres[k].present);
        sprintf(s,"timbres_%d_obertoneAmps",k);
        for(i=0;i<NOBRTONES;i++){
            setOpt(s,i,cur_timbres[k].obertoneAmps[i]);
        }
    
    }
}
double *timbreAmps=NULL;
double *maxTimbreAmps=NULL;
int timbreAmpsn=0;
double *normAmps(double*raw_amps,int n){
    if(timbreAmps==NULL|| n!=timbreAmpsn){
        if(timbreAmps!=NULL)
            free(timbreAmps);
        if(maxTimbreAmps!=NULL)
            free(maxTimbreAmps);
        timbreAmps=(double*)malloc(n*sizeof(double));
        maxTimbreAmps=(double*)malloc(n*sizeof(double));
        timbreAmpsn=n;
        for(i =0;i<n;i++){
            timbreAmps[i]=1;
            maxTimbreAmps[i]=raw_amps[i];
            if(maxTimbreAmps[i]<0.001)
                maxTimbreAmps[i]=0.001;
        }
        return timbreAmps;
    }
    for(i =0;i<n;i++){
        if(maxTimbreAmps[i]<raw_amps[i])
            maxTimbreAmps[i]=raw_amps[i];
        timbreAmps[i]=raw_amps[i]/maxTimbreAmps[i];;
    }
    return timbreAmps;

}

void proccessTimbre(double*freqs,double*raw_amps,double*ph,int n){
    int i,j,k,k2;
    struct timbre current;
    struct timbre *maxs;
    double*amps;
   
    fprintf(stderr,"processTimbre\n");

    amps=normAmps(raw_amps,n);
    maxs=cur_timbres;
    for(i=0;i<NTRIBLES;i++){
        maxs[i].present=0;
    }
    for(i=0;i<3;i++){
        for(j=0;j<n;j++){
            if(freqs[j]<0.000001)
                continue;
            current.basicFreq=freqs[j]/(i+1);
            checkTimbre(freqs,amps,n,current);
            for(k=0;k<NTRIBLES;k++){
                if(maxs[k].present<current.present){
                    for(k2=k+1;k2<NTRIBLES;k2++){
                        maxs[k2]=maxs[k2-1];
                    }
                    maxs[k]=current;
                    break;
                }
            }
        }
    }

    sendTimbres();
}

/*
void drawTimbreStatus(SDL_Surface*screen,int x1,int y1,int x2,int y2){}

void drawTimbreStatusDialog(){
    drawTimbreStatus(dSc,dX1,dY1,dX2,dY1);
}
void rizeTimbreStatus(){
    addDialog(butParam,drawTimbreStatusDialog);


}

*/

double findInOq(double freq){
    double c1=404;
    if(freq<=0.1)
        freq=0.1;
    while(freq>=c1*2){
        freq/=2.;
    }
    while(freq<c1){
        freq*=2.;
    }
    return log(freq/c1)/log(2.);
}


void l3d(double x1,double y1,double z1,double x2,double y2,double z2){
    glBegin(GL_LINES);
    glVertex3f (x1,y1,z1);
    glVertex3f (x2,y2,z2);
    glEnd();
}
void drawTimbre(struct timbre &tim){
    double tx,ty,tz,inOq,maxamp,a,r,dz,dxy,ldz,ldxy;
    int i;
/*
    double basicFreq;
    double obertoneAmps[NOBRTONES];
    double present;

*/
    tz=log(tim.basicFreq/24000. + 1)/log(2) -0.5;
    inOq=2*M_PI*findInOq(tim.basicFreq);
    ty=sin(inOq)/2.;
    tx=cos(inOq)/2.;
    maxamp=0;
    for(i=0;i<NOBRTONES;i++){
        if(maxamp<tim.obertoneAmps[i])
            maxamp=tim.obertoneAmps[i];
    }
    if(maxamp<0.001)
       maxamp=0.001;
       ldz=-100;
    for(i=0;i<NOBRTONES;i++){
        a=(((i%2)*2)-1)*((i/2)*M_PI/2./(NOBRTONES/2));
        r=tim.obertoneAmps[i]/maxamp/10.;
        dz=r*sin(a);
        dxy=r*cos(a);
        l3d(tx+dxy,ty+dxy,tz+dz,tx-dxy,ty+dxy,tz+dz);
        l3d(tx-dxy,ty+dxy,tz+dz,tx-dxy,ty-dxy,tz+dz);
        l3d(tx-dxy,ty-dxy,tz+dz,tx+dxy,ty-dxy,tz+dz);
        l3d(tx+dxy,ty-dxy,tz+dz,tx+dxy,ty+dxy,tz+dz);


//        if(ldz>-100){
  //      }
//        ldz=dz;
  //      ldxy=dxy;
    }

}


void drawTimbres(GLuint tex,double a1,double a2,double r,double fov){
    struct timbre *maxs;
    maxs=cur_timbres;
    int i;
    GL3dAt(a1,a2,r,fov);
    fprintf(stderr,"drawTimbre\n");

    for(i=0;i<NTRIBLES;i++){
        if(maxs[i].present>0.0001){
           drawTimbre(maxs[i]);
        }
    }





    GL3dFin(tex);
}
/*void drawTimbreStatus(SDL_Surface*screen,int x1,int y1,int x2,int y2){
    char s[128];
    int k,i;
    int i,w,h;
    Uint32 c;
    double a;
    w=x2-x1;
    h=y2-y1;
    double value[NOBRTONES+2];
    bar(screen,x1,y1,x2,y2,0);
    if(rizePannel==0)
        addButton(x1,y1,x2,y2,0,rizeTimbreStatus);

    for(k=0;k<NTRIBLES;k++){
        sprintf(s,"timbres_%d_baseFreq",k);
        basicFreq=getOpt(s);
        sprintf(s,"timbres_%d_present",k);
        present=getOpt(s);
        sprintf(s,"timbres_%d_obertoneAmps",k);
        for(i=0;i<NOBRTONES;i++){
            value[i+2]=getOpt(s,i);
        }
    
    }




    
    for(i=0;i<18;i++){
        a=colorStat[i];
        if(a<0.)
            a=0.;
        if(a>1.)
            a=1.;
        c=(64+i*(128+64)/18);
        c=c|(c*256)|(c*256*256);
        bar(screen,x1+i*w/18/2,y2,x1+(i+1)*w/18/2 -1,y2-h*a,c);
    }
    for(i=18;i<36;i++){
        a=colorStat[i];
        if(a<0.)
            a=0.;
        if(a>1.)
            a=1.;
        c=((i-18)*128/18);
        c=(c+128)|((128-c)*256)|((c+128)*256*256);
        bar(screen,x1+i*w/18/2,y2,x1+(i+1)*w/18/2 -1,y2-h*a,c);
    }

    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);

}
*/



