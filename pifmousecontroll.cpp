extern int butParam;
extern double colorSeqSplash;
extern double loadPrevSplash;
extern double loadNextSplash;
void changeColorSeq(){
            colorSeqVar++;
            colorSeqVar=colorSeqVar%4;
            colorSeq2BufReady=0;
            colorSeqSplash=1.;
}

void loadPreset(){
    if (butParam==0){
        loadPrev();
        loadPrevSplash=1;
    }
    if (butParam==1){
        loadNext();
        loadNextSplash=1;
    }

}

extern int dialogParam;
extern int dX1;
extern int dY1;
extern int dX2;
extern int dY2;
extern SDL_Surface* dSc;
void pifRepeatMod(){
    if(butParam==0){
        if(zeros[9]>0)
            zeros[9]=zeros[9]-1.;
    }
    if(butParam==1){
        pifPosition=!pifPosition;
    }
    if(butParam==2){
        int pifParity;
        pifParity=zeros[10];
        pifParity=pifParity++;
        pifParity=pifParity&1;
        zeros[10]=pifParity;
    }
    if(butParam==3){
        if(zeros[9]<60)
            zeros[9]=zeros[9]+1.;
    }
    if(butParam==4){
            //int z;
           // z=zeros[1];
           // z++;
           // z=z%4;
            zeros[1]=0;
      //      fprintf(stderr,"naked!:%d\n",z);

    }
    if(butParam==5){
            //int z;
           // z=zeros[1];
           // z++;
           // z=z%4;
            zeros[1]=1;
    //        fprintf(stderr,"naked!:%d\n",z);

    }
    if(butParam==6){
            //int z;
           // z=zeros[1];
           // z++;
           // z=z%4;
            zeros[1]=2;
  //          fprintf(stderr,"naked!:%d\n",z);

    }
    if(butParam==7){
            //int z;
           // z=zeros[1];
           // z++;
           // z=z%4;
            zeros[1]=3;
//            fprintf(stderr,"naked!:%d\n",z);

    }
    
    

}
void editAngle(){
    bar(dSc,dX1,dY1,dX2,dY2,0);
    int sx1;
    sx1=dX1;
    if(dialogParam==13){
        sx1=(dX1*9+dX2)/10;
        addButton(dX1,dY1,sx1,(dY1*3+dY2)/4,4,pifRepeatMod);
        rectangle(dSc,dX1,dY1,sx1,(dY1*3+dY2)/4,BORDERCOLOR);

    
    }
    if(dialogParam==5){
        sx1=(dX1*9+dX2)/10;
        addButton(dX1,dY1,sx1,(dY1*3+dY2)/4,0,pifRepeatMod);
        rectangle(dSc,dX1,dY1,sx1,(dY1*3+dY2)/4,BORDERCOLOR);

        addButton(dX1,(dY1*3+dY2)/4,sx1,(dY1*2+dY2*2)/4,1,pifRepeatMod);
        rectangle(dSc,dX1,(dY1*3+dY2)/4,sx1,(dY1*2+dY2*2)/4,BORDERCOLOR);

        addButton(dX1,(dY1*2+dY2*2)/4,sx1,(dY1+dY2*3)/4,2,pifRepeatMod);
        rectangle(dSc,dX1,(dY1*2+dY2*2)/4,sx1,(dY1+dY2*3)/4,BORDERCOLOR);

        addButton(dX1,(dY1+dY2*3)/4,sx1,(dY2),3,pifRepeatMod);
        rectangle(dSc,dX1,(dY1+dY2*3)/4,sx1,(dY2),BORDERCOLOR);
    
    }
    rizePannel=1;
    drawAnglePannelStack(dSc,sx1,dY1,dX2,dY2,dialogParam);
    rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);
    
    
}
void editBar(){
    int sx1;
    bar(dSc,dX1,dY1,dX2,dY2,0);
    sx1=dX1;
    if(dialogParam==13){
        sx1=(dX1*9+dX2)/10;
        addButton(dX1,dY1,sx1,(dY1*3+dY2)/4,4,pifRepeatMod);
        if(fabs(zeros[1])<0.01)
            bar(dSc,dX1,dY1,sx1,(dY1*3+dY2)/4,BORDERCOLOR);        
       rectangle(dSc,dX1,dY1,sx1,(dY1*3+dY2)/4,BORDERCOLOR);

        addButton(dX1,(dY1*3+dY2)/4,sx1,(dY1*2+dY2*2)/4,5,pifRepeatMod);
        if(fabs(zeros[1]-1)<0.01)
            bar(dSc,dX1,(dY1*3+dY2)/4,sx1,(dY1*2+dY2*2)/4,BORDERCOLOR);        
        rectangle(dSc,dX1,(dY1*3+dY2)/4,sx1,(dY1*2+dY2*2)/4,BORDERCOLOR);

        addButton(dX1,(dY1*2+dY2*2)/4,sx1,(dY1+dY2*3)/4,6,pifRepeatMod);
        if(fabs(zeros[1]-2)<0.01)
            bar(dSc,dX1,(dY1*2+dY2*2)/4,sx1,(dY1+dY2*3)/4,BORDERCOLOR);
        rectangle(dSc,dX1,(dY1*2+dY2*2)/4,sx1,(dY1+dY2*3)/4,BORDERCOLOR);

        addButton(dX1,(dY1+dY2*3)/4,sx1,(dY2),7,pifRepeatMod);
        if(fabs(zeros[1]-3)<0.01)
            bar(dSc,dX1,(dY1+dY2*3)/4,sx1,(dY2),BORDERCOLOR);
        rectangle(dSc,dX1,(dY1+dY2*3)/4,sx1,(dY2),BORDERCOLOR);
    }
 
    rizePannel=1;
    drawPannelStack(dSc,sx1+1,dY1,dX2,dY2,dialogParam);
    rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);
    
    
}
void drawGLPannelKoefs(SDL_Surface*screen,int x1,int y1,int x2,int y2,int k);
void editGlPannelKoefs (){
    int sx1;
    bar(dSc,dX1,dY1,dX2,dY2,0);
    sx1=dX1;
 
    rizePannel=1;
    drawGLPannelKoefs(dSc,sx1+1,dY1,dX2,dY2,dialogParam);
    rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);

}



void drawColorCorrectorPannelStack(SDL_Surface*screen,int x1,int y1,int x2,int y2);

void drawFilterPannelStack(SDL_Surface*screen,int x1,int y1,int x2,int y2,int k);
void drawMapOq(SDL_Surface*screen,int x1,int y1,int x2,int y2);
void editMapOq(){
    bar(dSc,dX1,dY1,dX2,dY2,0);
    rizePannel=1;
    drawMapOq(dSc,dX1,dY1,dX2,dY2);
    rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);
 
}
void editFilter(){
 
    bar(dSc,dX1,dY1,dX2,dY2,0);
    rizePannel=1;
    drawFilterPannelStack(dSc,dX1,dY1,dX2,dY2,dialogParam);
    rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);
    
    
}
void drawGLPannelStack(SDL_Surface*screen,int x1,int y1,int x2,int y2);



void drawColorPostCorrectorPannelStack(SDL_Surface*screen,int x1,int y1,int x2,int y2);
void editColorCorrector(){
 
    bar(dSc,dX1,dY1,dX2,dY2,0);
    rizePannel=1;
    drawColorCorrectorPannelStack(dSc,dX1,dY1,(dX2+dX1)/2,dY2);
    drawColorPostCorrectorPannelStack(dSc,(dX1+dX2)/2,dY1,dX2,dY2);

    rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);
    
    
}
void editGL(){
 
    bar(dSc,dX1,dY1,dX2,dY2,0);
    rizePannel=1;
    drawGLPannelStack(dSc,dX1,dY1,dX2,dY2);
    rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);
    
    
}
#include<string.h>
void drawColorStat(SDL_Surface*screen,int x1,int y1,int x2,int y2);
void editColorStat(){
    bar(dSc,dX1,dY1,dX2,dY2,0);
    rizePannel=1;
    drawColorStat(dSc,dX1,dY1,dX2,dY2);
    rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);
    
    
}

void editOqColorLines(){
    bar(dSc,dX1,dY1,dX2,dY2,0);
    rizePannel=1;
    drawOqColorLines(dSc,dX1,dY1,dX2,dY2);
    rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);
    
    
}


void editSaveDialog(){
    bar(dSc,dX1,dY1,dX2,dY2,0);
    rizePannel=1;
//    rizePannel=1;
    drawSaveDialog(dSc,dX1,dY1,dX2,dY2);
    rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);

}
void editLoadDialog(){
    bar(dSc,dX1,dY1,dX2,dY2,0);
    rizePannel=1;
//    rizePannel=1;
    drawLoadDialog(dSc,dX1,dY1,dX2,dY2);
    rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);

}
void editDrawQs(){
    bar(dSc,dX1,dY1,dX2,dY2,0);
    rizePannel=1;
    //calcQSDis(&qsAll);
    drawQs(dSc,dX1,dY1,dX2,dY2,&qsAll);

    rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);
}

extern struct playList*pls;
extern int plsn;
extern int curpls;
extern int curRabbit;

void loadRabbitFromDialog(){
    if(pls!=NULL && curpls>=0&&curpls<plsn&&curRabbit>=0&&curRabbit<pls[curpls].len&&pls[curpls].rabbits!=NULL){
        load_rabbit(pls[curpls].rabbits[curRabbit].name);    
    }
    
}


void rizeLoadDialog(){
    addDialog(butParam,editLoadDialog,loadRabbitFromDialog);
}  
void rizePicDialog(){
    addDialog(butParam,editSaveDialog,freePlayLists);
    printf("screenShoot 16\n");
}  

void rizeSaveDialog(){
   // saveNext();
    saveTimeStamp();
    rizePicDialog();
    
}  
void drawOptStack(SDL_Surface*screen,int x1,int y1,int x2,int y2,char const* *opts,Uint32*colors,int n);
void drawOptStackRBKoefs(SDL_Surface*screen,int x1,int y1,int x2,int y2,char const* *opts,Uint32*colors,int n);
void drawOptStack(SDL_Surface*screen,int x1,int y1,int x2,int y2,char const* *opts,Uint32*colors,int*optsn,int n);

void modyfyKoefCorrector(){
    int on;
    on=getOpt("correctorKoef",butParam);
    setOpt("correctorKoef",butParam,!on);
}

void drawHistoryKoef(SDL_Surface*screen,int x1,int y1,int x2,int y2,int n){
    double ly=-1;
    double lx=0;    
    int w,h;
    w=x2-x1;
    h=y2-y1;
    double x;
    double y;
    Uint32 t;
    t=GetTickCount();
    for(int i=1;i<HISLEN;i++){
        y=hisKoef[(hisCur[n]-i+2*HISLEN)%HISLEN][n];
        x=(t-hisKoefTime[(hisCur[n]-i+2*HISLEN)%HISLEN][n])/3000.;
        if(x>=0&&x<1){
            if(ly>=-0.001)
                drawLine(screen,x2-w*x,y2-h*y,x2-w*lx,y2-h*ly,getSoundKoefsColor(n,0));    
            lx=x;
            ly=y;
           
        }
    }
    
    
}


void  drawFreqsStartFin(SDL_Surface*screen,int x1,int y1,int x2,int y2,int n,double start,double fin){
    int i,w,h,a,b;
    Uint32 c;
    double v;
    w=x2-x1;
    h=y2-y1;
//    return;
    calcQSDis(&qsAll);
    
    for(i=0;i<w;i++){
        a=i*qsAll.oqs*qsAll.tones/w;
        b=a/qsAll.tones;
        a=a%qsAll.tones;        
        v=getQs(&qsAll,a,b);
        if(i<w*start || i>w*fin){
            c=GRAY;
        }else{
            c=WHITE;
        }
        drawLine(screen,x1+i,y2,x1+i,y2-v*h,c);    
        
    }

    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);

}
void  drawDisStartFin(SDL_Surface*screen,int x1,int y1,int x2,int y2,int n,double start,double fin){
    int i,w,h,a,b;
    Uint32 c;
    double v;
    w=x2-x1;
    h=y2-y1;
//    return;
    calcQSDis(&qsAll);
    
    for(i=0;i<w;i++){
        a=i*qsAll.oqs*qsAll.tones/w;
        b=a/qsAll.tones;
        a=a%qsAll.tones;        
        v=getQsDis(&qsAll,a,b);
        if(i<w*start || i>w*fin){
            c=GRAY;
        }else{
            c=WHITE;
        }
        drawLine(screen,x1+i,y2,x1+i,y2-v*h,c);    
        
    }

    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);

}
void  drawMMStartFin(SDL_Surface*screen,int x1,int y1,int x2,int y2,int n,double start,double fin){
    int i,w,h,a,b;
    Uint32 c;
    double v;
    w=x2-x1;
    h=y2-y1;
//    return;
    calcQSDis(&qsAll);
    
    for(i=0;i<w;i++){
        a=i*qsAll.oqs*qsAll.tones/w;
        b=a/qsAll.tones;
        a=a%qsAll.tones;        
        v=getQsMm05(&qsAll,a,b);
        if(i<w*start || i>w*fin){
            c=GRAY;
        }else{
            c=WHITE;
        }
        drawLine(screen,x1+i,y2,x1+i,y2-v*h,c);    
        
    }

    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);

}

//            (dSc,a,b,c,d,dialogParam)
void koefRithmChose(){
    int n,ch;
    n=butParam/KOEFNUM;
    ch=butParam%KOEFNUM;
    setOpt("koefRithmChose",n,ch);
}
void  drawKoefRithmChose(SDL_Surface*screen,int x1,int y1,int x2,int y2,int n){
        int w,h;
        w=x2-x1;
        h=y2-y1;
        int ch;
        ch=getOpt("koefRithmChose",n);
        for(int i=0;i<KOEFNUM;i++){
                int a,b,c,d,bb;
                a=x1+w/10+i*w*0.8/KOEFNUM;
                b=y1+h/10;  
                bb=b+(1.-soundKoefs[i])*h*8./10.;
                c=x1+w/10+(i+1)*w*0.8/KOEFNUM;
                d=y2-h/10;                
              if(i==ch){
                bar(screen,a,bb,c,d,getSoundKoefsColor(i,0));
              }else{
                rectangle(screen,a,bb,c,d,getSoundKoefsColor(i,0));
              }
              int type; 
              type=getOpt("typeKoef",i);

              if(type!=3 && type!=7){
                    addButton(a,b,c,d,n*KOEFNUM+i,koefRithmChose);
              }
        }
        rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);

}
void modyfyKoefType(){
    int n,type;
    n=butParam%32;
    type=butParam/32;
    setOpt("typeKoef",n,type);
}
void drawKoefSensorSetup(){
        int w,h,i;
        w=dX2-dX1;
        h=dY2-dY1;
        bar(dSc,dX1,dY1,dX2,dY2,0);
        rizePannel=1;
        int on=getOpt("correctorKoef",dialogParam);
        int type=getOpt("typeKoef",dialogParam);
        double freqsStart,freqsFin;
        setOpt("send_qsAll_ks",1);
        freqsStart=getOpt("freqKoefStart",dialogParam);
        freqsFin=getOpt("freqKoefFin",dialogParam);
        //"koefRithmMinFreq""koefRithmMaxFreq""koefRithmLen"
        const char *s[]={"speedKoefUp","speedkoefDown","freqKoefStart","freqKoefFin","koefRithmMinFreq","koefRithmMaxFreq","koefRithmLen"};
        int ns[7];
        Uint32 colors[]={YELLOW,CYAN,BLUE,GREEN,RED,MAGENTA,WHITE};
        ns[0]=dialogParam;
        ns[1]=dialogParam;
        ns[2]=dialogParam;
        ns[3]=dialogParam;
        ns[4]=dialogParam;
        ns[5]=dialogParam;
        ns[6]=dialogParam;
///        fprintf(stderr,"dialogParam:%d\n",dialogParam);
        if(type!=7)
            drawOptStack(dSc,dX1,dY1,(dX2+dX1)/3,dY2,s,colors,ns,4);
        else
            drawOptStack(dSc,dX1,dY1,(dX2+dX1)/3,dY2,s,colors,ns,7);
        int a,b,c,d,b1;
        a=(dX2+dX1)/3;
        b=dY2-h/(12+1);
        c=(dX2+dX1)/2;
        d=dY2;
        if(on){
            bar(dSc,a,b,c,d,BORDERCOLOR);
        }else{
            rectangle(dSc,a,b,c,d,BORDERCOLOR);
        }
        addButton(a,b,c,d,dialogParam,modyfyKoefCorrector);
        for(i=0;i<12;i++){
            b=dY1+i*h/(12+1);
            d=dY1+(i+1)*h/(12+1);
            if(type==i){
                bar(dSc,a,b,c,d,BORDERCOLOR);
            }else{
                rectangle(dSc,a,b,c,d,BORDERCOLOR);
                addButton(a,b,c,d,dialogParam+32*i,modyfyKoefType);
            }
        
        
        }



//        int a,b,c,d,b1;
        a=(dX2+dX1)/2+5;
        b1=dY1+5;
        b=(dY2+dY1)/2;
        c=dX2-5;
        d=dY2-5;
        drawHistoryKoef(dSc,a,b1,c,b,dialogParam);
        if(type==0){ ///RAW_EQ
            drawFreqsStartFin(dSc,a,b,c,d,dialogParam,freqsStart,freqsFin);
        }else if(type==1){//FADES
    //        drawFadesStartFin(dSc,a,b,c,d,dialogParam,freqsStart,freqsFin);
        }else if(type==3 || type==7){//RITHM
            drawKoefRithmChose(dSc,a,b,c,d,dialogParam);
        
  //          drawDisStartFin(dSc,a,b,c,d,dialogParam,freqsStart,freqsFin);
        }else if(type==4){//DISONANCE
           drawDisStartFin(dSc,a,b,c,d,dialogParam,freqsStart,freqsFin);
        }else if(type==5){///MAJOR-MINOR

            drawMMStartFin(dSc,a,b,c,d,dialogParam,freqsStart,freqsFin);
        }
        
        rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);

}

void rizeKoefSensorSetup(){
//        fprintf(stderr,"butParam:%d\n",butParam);

    addDialog(butParam,drawKoefSensorSetup);
}

void switchInputShowPage();
void switchInputShow();
extern int inputShow;
extern int inputShowPage;
void  drawValue(SDL_Surface*screen,double x,double y,double w,double h,double value,double myscale,Uint32 color);
void drawKoefsSensorSetup(){
        bar(dSc,dX1,dY1,dX2,dY2,0);
        rizePannel=1;
        int w,h;
        w=dX2-dX1;
        h=dY2-dY1;
        bar(screen,dX1,dY1-w/10,dX1+w/3,dY1,RED);
        addButton(dX1,dY1-w/10,dX1+w/3,dY1,0,switchInputShow);

        bar(screen,dX1+w/3,dY1-w/10,dX1+2*w/3,dY1,CYAN);
        addButton(dX1+w/3,dY1-w/10,dX1+2*w/3,dY1,0,switchInputShowPage);
        
        setOpt("send_qsAll_ks",0);
           if(inputShow==0){

            for(int i=0;i<KOEFNUM;i++){
                    int a,b,c,d,bb;
                    a=dX1+w/10+i*w*0.8/KOEFNUM;
                    b=dY1+h/10;
      
                    bb=b+(1.-soundKoefs[i])*h*8./10.;
      
                    c=dX1+w/10+(i+1)*w*0.8/KOEFNUM;
                    d=dY2-h/10;                
                  bar(dSc,a,bb,c,d,getSoundKoefsColor(i,0));
                  rectangle(dSc,a,b,c,d,BORDERCOLOR);
              
                  addButton(a,b,c,d,i,rizeKoefSensorSetup);

            }
        }else{
         char s[128];    
        for(int i=0;i<16;i++){
            sprintf(s,"KoefAr16_%d",inputShowPage);
//            soundKoefsHistory[0][i]=getOpt(s,i);
        //    for(j=HISTORYLEN-1;j>=0;j--){
                Uint32 color;
                color=(255*i/16)+(255*(15-i)/16)*256*256;
                drawValue(screen,dX1+0.1*w +i*0.8*w/16,dY1+h*0.1,0.8*w/16,h*0.8,getOpt(s,i),1,color);
                
           // }
    
        }
       addButton(dX1,dY1,dX2,dY2,inputShowPage+inputShow*KOEFNUM,rizeKoefSensorSetup);
        
        }

       rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);

}
void rizeKoefsSensorSetup(){
    addDialog(0,drawKoefsSensorSetup);
}
void drawOptStack(SDL_Surface*screen,int x1,int y1,int x2,int y2,char const**opts,Uint32*colors,int* optsn ,int n);
int OptStackKoefsPage=0;
void modifyOptStackKoefsPage(){
    OptStackKoefsPage++;
    OptStackKoefsPage%=2;
}
void drawOptStackKoefs(){
    char optsbuf[KOEFNUM+2][32];
    char* opts[KOEFNUM+2];

    int optsn[KOEFNUM+2];
    Uint32 colors[KOEFNUM+2];
    int i;

    bar(dSc,dX2,dY1,dX2 + (dX2-dX1)/10,dY1+(dY2-dY1)/10,OptStackKoefsPage?MAGENTA:BLUE);
    addButton(dX2,dY1,dX2 + (dX2-dX1)/10,dY1+(dY2-dY1)/10,0,modifyOptStackKoefsPage);

    for(int i=0;i<KOEFNUM+2;i++){
        setOpt(sdialogParam,i,getOpt(sdialogParam,i));
        strcpy(optsbuf[i],sdialogParam);
        if(i<2){
            optsn[i]=i;
        }else{
            optsn[i]=2+i-2+OptStackKoefsPage*KOEFNUM;
        }
        opts[i]=optsbuf[i];
        if(i>=2){
            colors[i]=getSoundKoefsColor(i-2+OptStackKoefsPage*KOEFNUM,0);
        }else {
            colors[i]=i?CYAN:WHITE;
        }
    }
    //fprintf(stderr,"drawOptStackKoefs\n");
    drawOptStack(dSc,dX1,dY1,dX2,dY2,(char const**)opts,colors,optsn,KOEFNUM+2);
    
}







void rizeOptStackKoefs(){
    addDialog(sbutParam,drawOptStackKoefs);
}


#include"rithm.cpp"
void drawRtmsOne(){
    bar(dSc,dX1,dY1,dX2,dY2,0);
    int i,j,k,x1,y1,x2,y2,w,h;
    char s1[128];
    char s2[128];
    i=dialogParam;
//    for(i=0;i<RTMS;i++){
       w=dX2-dX1;
       h=dY2-dY1;
       sprintf(s1,"rtms_%d_basefreq",i);
//       rtms[i].basefr=calcOpt(s1);       
       x1=dX1;
       y1=dY1;
       x2=dX1+w/(RTMSIZE+1);
       y2=dY2;
       
       setOpt(s1,getOpt(s1));
       addEValue(x1,y1,x2,y2,getOptAdress(s1,0));
       rectangle(dSc,x1,y1,x2,y2,VERYGREEN);
       bar(dSc,x1,y1,x2,y1+h*getOpt(s1,0),VERYGREEN);
        
       
       
       for(j=0;j<RTMSIZE;j++){
            for(k=0;k<RTMSIZE;k++){
                sprintf(s1,"rtms_%d_amps_%d_%d",i,j,k);
                setOpt(s1,getOpt(s1));

                sprintf(s2,"rtms_%d_phs_%d_%d",i,j,k);
                setOpt(s2,getOpt(s2));

                   x1=dX1+(j+1)*w/(RTMSIZE+1);
                   y1=dY1+k*h/RTMSIZE;
                   x2=dX1+(j+2)*w/(RTMSIZE+1);
                   y2=dY1+(k+1)*h/RTMSIZE;
            
                   addEValue(x1,y1,x2,y2,getOptAdress(s2,0),getOptAdress(s1,0));
                 //  addEValueW(x1,y1,x2,y2,getOptAdress(s2,0));

                   double v,v2;
                   v=getOpt(s1,0);
                   v2=getOpt(s2,0);

                 //  drawLine(dSc,x1,y1+h/2./RTMSIZE,x2,y1+h/2./RTMSIZE,GREEN);

                   bar(dSc,x1,y2-h*v/RTMSIZE,x1+v2*w/RTMSIZE,y2,RED);
                   bar(dSc,x1+v2*w/RTMSIZE,y2-h*v/RTMSIZE,x2,y2,MAGENTA);
                   
                   rectangle(dSc,x1,y1,x2,y2,VERYGREEN);
               
               
  //             addEValue(x1,y1,x2,y2,getOptAdress(s2,0));

                //rtms[i].amps[j][k]=calcOpt(s1);
                //rtms[i].phs[j][k]=calcOpt(s2);
          }
      }
    

    rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);

}

void rizeRtmsOne(){
    addDialog(butParam,drawRtmsOne);
}


void drawRtmsConfig(){
    bar(dSc,dX1,dY1,dX2,dY2,0);
    int h,w,rows,cells,x,y,x1,x2,y1,y2,i;
    w=dX2-dX1;
    h=dY2-dY1;
    rows=1;
    cells=RTMS;//(RTMS+rows-1)/rows;
    x=0;y=0;
    for(i=0;i<RTMS;i++,x++){    
      x1=dX1+x*w/cells;
      y1=dY1+y*h/rows;
      x2=dX1+(x+1)*w/cells;
      y2=dY1+(y+1)*h/rows;
      
      bar(dSc,x1,y1,x2,y2,colors[i%COLORS]);
      addButton(x1,y1,x2,y2,i,rizeRtmsOne);
    }
    rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);

}
void rizeRtmsConfig(){
    addDialog(butParam,drawRtmsConfig);
}

void drawColorPostCorrectorPannelStack(SDL_Surface*screen,int x1,int y1,int x2,int y2){
        bar(screen,x1,y1,x2,y2,0);
        rizePannel=1;
        const char *s[]={"allgamma","redgamma","greengamma","bluegamma"};
        Uint32 c[]={WHITE,RED,GREEN,BLUE};
        drawOptStack(screen,x1,y1,x2,y2,s,c,4);
        rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);


}

void drawSensorsSpeed(){
        bar(dSc,dX1,dY1,dX2,dY2,0);
        rizePannel=1;
        const char *s[]={"speedSpeqUp","speedSpeqDown","speedSizeUp","speedSizeDown","speedFadeUp","speedFadeDown","quickSpeqAmpGamma","nearSoundArrays","mamContrast","neAmpSpeedUp","neAmpSpeedDown","soundSpeq_INGARBRIGHTKOEF","soundSpeq_ampGarGamma"
 ,"soundSpeq_lowFreqBri","soundSpeq_highFreqBri"    ,"soundSpeq_heatPow","soundSpeq_heatPow2","shspeed"
        
        };
        Uint32 c[]={YELLOW,CYAN,RED,BLUE,MAGENTA,GREEN,WHITE,CYAN,GREEN,YELLOW,CYAN,WHITE,MAGENTA,0xaaaaaa,0xffffff,RED,MAGENTA,WHITE};
        drawOptStack(dSc,dX1,dY1,dX2,dY2,s,c,18);
        rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);
}


void drawSint1Controll(){
}
#define SINT2GARS 16
void drawSint2VoiceGars(){
    double gar[SINT2GARS];
    double gar_kos[SINT2GARS];
    char s[SINT2GARS][100];
    const char *ss[SINT2GARS];
    Uint32 c[SINT2GARS];
    int voice,i;
    voice=dialogParam;
     for(i=0;i<SINT2GARS;i++){
        unsigned int a;
        a=i*255/SINT2GARS;
         c[i]=a+(255-a)*256*256;
         sprintf(s[i],"myplay_sint2_voce%d_gar%d",voice,i);
         setOpt(s[i],getOpt(s[i]));
         //gar[i]=calcOpt(s[i]);
        ss[i]=s[i];
     }
    drawOptStackRBKoefs(dSc,dX1,dY1,dX2,dY2/2+dY1/2,ss,c,SINT2GARS);
 
     for(i=0;i<SINT2GARS;i++){
                 sprintf(s[i],"myplay_sint2_voce%d_gar_kos%d",voice,i);
                ss[i]=s[i];
 
//                    gar_kos[i]=calcOpt(s[i]);
    }
    drawOptStackRBKoefs(dSc,dX1,dY2/2+dY1/2,dX2,dY2,ss,c,SINT2GARS);
    rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);

}
void rizeSint2VoiceGars(){
    addDialog(butParam,drawSint2VoiceGars);

}
void drawSint2Voice(){
    int voice=dialogParam;
    char s[100][100];
    const char *ss[100];
    int optsN=13;
    int i;
    Uint32 c[]={WHITE,CYAN,MAGENTA,RED,GREEN,YELLOW,0xaaaaAA,10110,11211,12312,13413,14514,15615,16716,17817,18918,19019,20120};
    const char *optss[]={"volume","pitchHeight","chromaHeight","kos","pan","width","density","vibrate_amp","vibrate_fr","tremolo_amp","tremolo_fr","sinpow","garMetod"};
    for(i=0;i<optsN;i++){
        sprintf(s[i],"myplay_sint2_voce%d_%s",voice,optss[i]);
        ss[i]=s[i];
    }
    drawOptStackRBKoefs(dSc,dX1,dY1,(dX2*9+dX1)/10,dY2,ss,c,optsN);
    bar(dSc,(dX2*9+dX1)/10,(dY2+dY1*2)/3,dX2,(dY2*2+dY1)/3,MAGENTA);
    addButton((dX2*9+dX1)/10,(dY2+dY1*2)/3,dX2,(dY2*2+dY1)/3,voice,rizeSint2VoiceGars);
    rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);
}
void rizeSint2Voice(){
    addDialog(butParam,drawSint2Voice);
}
void drawSint2Controll(){
    int x,y,i;
    int rp;
    int x1,y2,x2,y1,w,h;
    x1=dX1;
    x2=dX2;
    y1=dY1;
    y2=dY2;
    bar(dSc,x1,y1,x2,y2,BLACK);
    w=x2-x1;
    h=y2-y1;
    rp=rizePannel;
    rizePannel=0;
    for(y=0,i=0;y<3;y++)
        for(x=0;x<4;x++,i++){
            dX1=x1+x*w/4+1;
            dY1=y1+y*h/3+1;
            dX2=dX1+w/4-1;
            dY2=dY1+h/3-1;
            dialogParam=i;
            drawSint2Voice();           
            addButton(dX1,dY1,dX2,dY2,i,rizeSint2Voice);
        }
    dX1=x1;
    dX2=x2;
    dY1=y1;
    dY2=y2;

    rectangle(dSc,x1,y1,x2,y2,BORDERCOLOR);
    
    rizePannel=rp;

}
void rizeSintControll(){
    if(butParam=1)
        addDialog(butParam,drawSint2Controll);
}

void drawMyplayControll(){
        int sintN=2;
        int i,h;
        h=dY2-dY1;
        Uint32 sintC[]={WHITE,MAGENTA};
///        void(*sintFunc[2])();
//        sintFunc[0]=drawSint1Controll;
  //      sintFunc[1]=rizeSintControll;
        
        
        bar(dSc,dX1,dY1,dX2,dY2,0);
        rizePannel=1;
        const char *s[]={"myplay","myplay_simpleVol","myplay_reverb","myplay_nearfreq","myplay_metod","myplay_mode"};
        Uint32 c[]={CYAN,RED,BLUE,BLUE,WHITE,MAGENTA,MAGENTA,WHITE,WHITE};
        drawOptStack(dSc,dX1,dY1,(dX1*2+dX2*8)/10,dY2,s,c,6);
        for(i=0;i<sintN;i++){
            bar(dSc,(dX1*2+dX2*8)/10+1,dY2-i*h/sintN,dX2,dY2-(i+1)*h/sintN,sintC[i]);
            addButton((dX1*2+dX2*8)/10+1,dY2-(i+1)*h/sintN,dX2,dY2-(i)*h/sintN,i,rizeSintControll);
        
        }

        rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);
}

void drawLifeMonitor(SDL_Surface*screen,int x1,int y1,int x2,int y2){
    int w,h,i,j,sw,sh;
    sw=x2-x1;
    sh=y2-y1;
    w=getOpt("monitorLife",0);
    h=getOpt("monitorLife",1);
    for(i=0;i<w;i++){
        for(j=0;j<h;j++){
            if(getOpt("monitorLife",2+j*w+i)>0.5){
                bar(screen,x1+i*sw/w,y1+j*sh/h,x1+(i+1)*sw/w,y1+(j+1)*sh/h,WHITE);   
            }else{
                bar(screen,x1+i*sw/w,y1+j*sh/h,x1+(i+1)*sw/w,y1+(j+1)*sh/h,0);   
                rectangle(screen,x1+i*sw/w,y1+j*sh/h,x1+(i+1)*sw/w,y1+(j+1)*sh/h,WHITE);   
            }
        }
    }

}
void drawLifeControll(){
        int i,h,w;
        h=dY2-dY1;
        w=dX2-dX1;
        Uint32 c[]={WHITE,RED};
        bar(dSc,dX1,dY1,dX2,dY2,0);
        rizePannel=1;
        const char *s[]={"lifeStep","lifeRand"};
        setOpt("monitorLifeShow",1);
        drawOptStack(dSc,dX1,dY1,dX1+w/8,dY2,s,c,2);
        
        drawLifeMonitor(dSc,dX1+w/8+1,dY1,dX2,dY2);        
        
        rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);


}


void drawColorLineOpt(){
        bar(dSc,dX1,dY1,dX2,dY2,0);
        rizePannel=1;
        const char *s[]={"ampZero","ampAsc","lwZero","lwMax","lopmin","lopmax","lwbmin","lwbmax"};
        Uint32 c[]={CYAN,RED,BLUE,BLUE,MAGENTA,MAGENTA,WHITE,WHITE};
        drawOptStack(dSc,dX1,dY1,dX2,dY2,s,c,8);
        rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);
}

void drawSpeakerControll(){

        bar(dSc,dX1,dY1,dX2,dY2,0);
        rizePannel=1;
        const char *s[]={"speaker1x","speaker1y","speaker2x","speaker2y"};
        Uint32 c[]={BLUE,CYAN,RED,MAGENTA};
        drawOptStack(dSc,dX1,dY1,dX2,dY2,s,c,4);
        rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);

//    s1x=w*getOpt("speaker1x");
  //  s1y=h*getOpt("speaker1y");
    //s2x=w*getOpt("speaker2x");
    //s2y=h*getOpt("speaker2y");

}
#define OCVTH 3

char _rBuf[256];
const char* multiTh(int th,const char*s,char *rBuf){
    if(th==0){
        strcpy(rBuf,s);
        return s;
    }
    sprintf(rBuf,"%s_th%d",s,th);
    return rBuf;

}
const char* multiTh(int th,const char*s){
    return multiTh(th,s,_rBuf);

}


int ocvth=0;

void setVideoFileNum(){
    setOpt(multiTh(ocvth,"videoFileNum"),butParam);
}

void setnOCVPlayList(){
    setOpt(multiTh(ocvth,"nOCVPlayList"),butParam);

}

void setVideoTh(){
    ocvth=butParam;

}
void drawOCVTHSwetchers(SDL_Surface*screen,int x1,int y1,int x2,int y2){
    int w;
    w=x2-x1;
    for(int i=0;i<OCVTH;i++){
        if(i!=ocvth){
            addButton(x1+i*w/3,y1,x1+(i+1)*w/3,y2,i,setVideoTh);
            rectangle(screen,x1+i*w/3,y1,x1+(i+1)*w/3,y2,BORDERCOLOR);
        }else{
            bar(screen,x1+i*w/3,y1,x1+(i+1)*w/3,y2,BORDERCOLOR);
        }
    }

}

void startCalibrateCam(){
    char s[32];
    sprintf(s,"calibrateCam%d",butParam);
    setOpt(s,1);
}
void drawPaints(SDL_Surface*screen,int x1,int y1,int x2,int y2){
    int w,h;
    w=x2-x1;
    h=y2-y1;
    bar(screen,x1,y1,x2,y2,0);

    rectangle(screen,x1,y1,x1+w/3,y2,RED);
    //addButton(x1,y1,x1+w/3,y2,ocvth,startCalibrateCam);
    


    rectangle(screen,x1,y1,x2,y2,BORDERCOLOR);


}
    
      //        drawTimbres(tex_timbre,calcOpt("timbre_a1")*2*M_PI,calcOpt("timbre_a2")*2*M_PI,calcOpt("timbre_r")*10,calcOpt("timbre_fov")*160+0.0001);

void drawTimbreControll(){
        bar(dSc,dX1,dY1,dX2,dY2,0);
        rizePannel=1;
        const char *s[]={"timbre1","timbre2","timbre3","timbre_a1","timbre_a2","timbre_r","timbre_fov"};
        Uint32 c[]={CYAN,YELLOW,BLUE,YELLOW,MAGENTA,RED,WHITE,GREEN,BLUE,CYAN,WHITE,RED,BLUE,GREEN,YELLOW,WHITE,WHITE,WHITE,YELLOW,MAGENTA|BLUE,RED|GREEN};
        drawOptStackRBKoefs(dSc,dX1,dY1,dX2,dY2,(const char **)s,c,7);               
        rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);

}
    
    
    
void drawQslControll(){
        bar(dSc,dX1,dY1,dX2,dY2,0);
        rizePannel=1;
        const char *s[]={"qsLayer1","qsLayer2","qsLayer3","qsLayer_r","qsLayer_a1","qsLayer_a2","qsLayer_a3","qsLayer_sideShift","qsLayer_pow","qsLayer_rpow","qsLayer_r0","qsLayer_fov","qsLayer_len","qsLayer_rAsum"
        ,"qsLayer_pAlpha","qsLayer_platesType", "qsLayer_pZero", "qsLayer_lZero","qsLayer_minPointValue","qsLayer_lineWidth","qsLayer_normLen","qsLayer_disValueKoef"};
        Uint32 c[]={CYAN,YELLOW,BLUE,YELLOW,MAGENTA,RED,MAGENTA,WHITE,GREEN,BLUE,CYAN,WHITE,RED,BLUE,GREEN,YELLOW,WHITE,WHITE,WHITE,YELLOW,MAGENTA|BLUE,RED|GREEN};
        drawOptStackRBKoefs(dSc,dX1,dY1,dX2,dY2,(const char **)s,c,22);               
        rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);

}
void drawSoundSpeqControll(){
        bar(dSc,dX1,dY1,dX2,dY2,0);
        rizePannel=1;
        const char *s[]={"soundSpeq1","soundSpeq2","soundSpeq3","soundSpeq_r","soundSpeq_a1",
                        "soundSpeq_a2","soundSpeq_a3","soundSpeq_fov","soundSpeq_len","soundSpeq_width"
        
        ,"soundSpeq_zshift"
,"soundSpeq_zeroPs","soundSpeq_fadePs"     ,"soundSpeq_plateOp"   ,"soundSpeq_plateOpZero"
        ,"soundSpeq_lineOpZero","soundSpeq_lineOp","soundSpeq_pointOpZero","soundSpeq_pointOp","soundSpeq_neampsize"
        };

        
        
        Uint32 c[]={CYAN,YELLOW,BLUE,YELLOW,MAGENTA,RED,MAGENTA,WHITE,GREEN,BLUE,CYAN,WHITE,RED,BLUE,GREEN,YELLOW,WHITE,WHITE,WHITE,YELLOW,MAGENTA|BLUE,RED|GREEN};
        drawOptStackRBKoefs(dSc,dX1,dY1,dX2,dY2,(const char **)s,c,20);               
        rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);

}
void drawSoundSpeqSquareControll(){
        bar(dSc,dX1,dY1,dX2,dY2,0);
        rizePannel=1;
        const char *s[]={"soundSpeqSquare1","soundSpeqSquare2","soundSpeqSquare3","soundSpeqSquare_r","soundSpeqSquare_a1",
                        "soundSpeqSquare_a2","soundSpeqSquare_a3","soundSpeqSquare_fov","soundSpeqSquare_len","soundSpeqSquare_width"
        
        ,"soundSpeq_zshift"
,"soundSpeq_zeroPs","soundSpeq_fadePs"     ,"soundSpeq_plateOp"   ,"soundSpeq_plateOpZero"
        ,"soundSpeq_lineOpZero","soundSpeq_lineOp","soundSpeq_pointOpZero","soundSpeq_pointOp","soundSpeq_neampsize"
        };

        
        
        Uint32 c[]={CYAN,YELLOW,BLUE,YELLOW,MAGENTA,RED,MAGENTA,WHITE,GREEN,BLUE,CYAN,WHITE,RED,BLUE,GREEN,YELLOW,WHITE,WHITE,WHITE,YELLOW,MAGENTA|BLUE,RED|GREEN};
        drawOptStackRBKoefs(dSc,dX1,dY1,dX2,dY2,(const char **)s,c,20);               
        rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);

}
void drawQsPlateControll(){
        bar(dSc,dX1,dY1,dX2,dY2,0);
        rizePannel=1;
        const char *s[]={"qsPlateOp1","qsPlateOp2","qsPlateOp3","qsPlateRGamma","qsPlateA0","qsPlateNormLen"};
        Uint32 c[]={CYAN,YELLOW,BLUE,GRAY,MAGENTA,RED,GREEN,BLUE,CYAN,WHITE,RED,BLUE,GREEN,WHITE,WHITE,MAGENTA|BLUE};
        drawOptStackRBKoefs(dSc,dX1,dY1,dX2,dY2,(const char **)s,c,6);               
        rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);

}
void drawTouchControll(){
        bar(dSc,dX1,dY1,dX2,dY2,0);
        rizePannel=1;
        const char *s[]={"touchSpeq1","touchSpeq_r","touchSpeq_a1","touchSpeq_a2",
                         "touchSpeq_fov","touchSpeq_pwks","touchSpeq_pwksr","touchSpeq_minfreq",
                         "touchSpeq_maxfreq","touchSpeq_type"};
        Uint32 c[]={CYAN,YELLOW,BLUE,GRAY,MAGENTA,RED,GREEN,BLUE,CYAN,WHITE,RED,BLUE,GREEN,WHITE,WHITE,MAGENTA|BLUE};
        drawOptStackRBKoefs(dSc,dX1,dY1,dX2,dY2,(const char **)s,c,10);               
        rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);

}

    //if(getOpt()>0.00001 && touchSpeq_ready){
      //   drawSpec(tex_touch,calcOpt()*2,calcOpt()*2*M_PI,calcOpt()*2*M_PI,calcOpt()*2*M_PI);


void drawQsSurfControll(){
        bar(dSc,dX1,dY1,dX2,dY2,0);
        rizePannel=1;
        const char *s[]={"qsSurf1","qsSurf2","qsSurf3","qsSurf_r","qsSurf_a1","qsSurf_a2","qsSurf_fov","qsSurf_pw","qsSurf_mindl"};
        Uint32 c[]={CYAN,YELLOW,BLUE,GRAY,MAGENTA,RED,GREEN,BLUE,CYAN,WHITE,RED,BLUE,GREEN,WHITE,WHITE,MAGENTA|BLUE};
        drawOptStackRBKoefs(dSc,dX1,dY1,dX2,dY2,(const char **)s,c,9);               
        rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);

}
void changeOvcAutoSwitch(){
    if(getOpt("ovcAutoSwitch")<0.5)
        setOpt("ovcAutoSwitch",1);
    else
        setOpt("ovcAutoSwitch",0);
}
void drawAutoSwitch(SDL_Surface*screen,int x1,int y1,int x2,int y2){//""
    bar(screen,x1,y1,x2,y2,BLUE);
    addButton(x1,y1,x2,y2,1,changeOvcAutoSwitch);

}
void drawOpenCVControll(){
        bar(dSc,dX1,dY1,dX2,dY2,0);
        rizePannel=1;
        
        
        //    setOpt("OVCLoopBegin",0);
//    setOpt("OVCLoopEnd",1);

        //
//        const char *s[]={"videoFile1","vf1size","videoFile2","vf2size","videoFile3","vf3size","OVCLoopBegin","OVCpercentPos","OVCLoopEnd"};

        const char *_s[]={"videoFile1","videoFile2","videoFile3","videoSpeed","videoZoom","videoAspect","videoPosX","videoPosY","OVCLoopBegin","OVCpercentPos","OVCLoopEnd","ovcAutoSwitchLimit"};


//
    
    
  //  ovcAutoSwitchLimit[th]=getOpt(multiTh(th,

        char sbuf[12][64];
        char *s[12];
        for(int i=0;i<12;i++){
            s[i]=sbuf[i];
            multiTh(ocvth,_s[i],s[i]);
//            fprintf(stderr,"ocvth:%d - ",i);
  //          fprintf(stderr,"%s\n",s[i]);        
        }
        Uint32 c[]={CYAN,YELLOW,BLUE,MAGENTA,WHITE,BLUE,GREEN,GREEN,RED,WHITE,RED,CYAN};
        drawAutoSwitch(dSc,dX2-(dX2-dX1)/10,dY1,dX2,dY1+(dY2-dY1)/10);//"ovcAutoSwitch"
        
        drawOptStackRBKoefs(dSc,dX1,dY1,(dX2+dX1)/2,dY1+(dY2-dY1)*6/10,(const char **)s,c,12);
        drawOCVTHSwetchers(dSc,dX1,dY1+(dY2-dY1)*6/10,(dX2+dX1)/2,dY1+(dY2-dY1)*8/10);
        drawPaints(dSc,dX1,dY1+(dY2-dY1)*8/10,(dX2+dX1)/2,dY2);
        
        int all,cur,rows,lines,x,y,i;
        all=getOpt(multiTh(ocvth,"videoFileN"));
        cur=getOpt(multiTh(ocvth,"videoFileNum"));
        for(rows=1;rows*rows<=all;rows++);
        for(lines=1;(lines)*rows<=all;lines++);
        int x0,y0,h,w;

        w=((dX2+dX1)/2-dX1);
        x0=(dX2+dX1)/2+w/10;
        w=w*0.8;

        h=(dY2-dY1);
        y0=dY1+h/10;
        h=h*0.8;
        lines++;
        rows++;
        for(i=0;i<OCVCAMS;i++){
            int a,b,c,d;
            a=x0 + i *w*(rows-1)/(rows)  /OCVCAMS;
            b=y0;
            c=a+w*(rows-1)/(rows)/OCVCAMS;
            d=b+h/lines;
            if(i==-cur-1){
                bar(dSc,a,b,c,d,RED);
            }else{
                rectangle(dSc,a,b,c,d,RED);
                addButton(a,b,c,d,-i-1,setVideoFileNum);
            }
        
        
        }
        
        
        for(x=0,y=1,i=0;i<all;i++){
            int a,b,c,d;
            a=x0 + x *w  /rows;
            b=y0 + y * h /lines;
            c=a+w /rows;
            d=b+h /lines;
            if(i==cur){
                bar(dSc,a,b,c,d,BORDERCOLOR);
            }else{
                rectangle(dSc,a,b,c,d,BORDERCOLOR);
                addButton(a,b,c,d,i,setVideoFileNum);
            }
            x++;
            if(x>=rows-1){
                y++;
                x=0;
            }
        }
        cur=getOpt(multiTh(ocvth,"nOCVPlayList"));
        for(i=0;i<OCVPLYLISTS;i++){
            
            int a,b,c,d;
            a=x0 + w - w/rows;
            b=y0 + i * h /OCVPLYLISTS;
            c=a+w /rows;
            d=b+h /OCVPLYLISTS;

            if(i==cur){
                bar(dSc,a,b,c,d,CYAN);
            }else{
                rectangle(dSc,a,b,c,d,CYAN);
                addButton(a,b,c,d,i,setnOCVPlayList);
            }
        
        }

        rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);
}

void closeLifeMonitor(){
        setOpt("monitorLifeShow",0);
}
void rizedrawLifeControll(){
    addDialog(butParam,drawLifeControll,closeLifeMonitor);
}

void rizeDrawOqColorLines(){
    addDialog(butParam,editOqColorLines);
}
void rizeSpeakerControll(){
    addDialog(butParam,drawSpeakerControll);
}



void rizeSensorsSpeed(){
    addDialog(butParam,drawSensorsSpeed);
}
void rizeColorLineOpt(){
    addDialog(butParam,drawColorLineOpt);
}
void rizeMyplayControll(){
    addDialog(butParam,drawMyplayControll);
}

void rizeOpenCVControll(){
    addDialog(butParam,drawOpenCVControll);
}


void rizeQsPlateControll(){
    addDialog(butParam,drawQsPlateControll);
}
void rizeQsSurfControll(){
    addDialog(butParam,drawQsSurfControll);
}
void rizeTouchControll(){
    addDialog(butParam,drawTouchControll);
}
 
 
 


void rizeTimbreControll(){
    addDialog(butParam,drawTimbreControll);
}



void rizeQslControll(){
    addDialog(butParam,drawQslControll);
}
void rizeSoundSpeqControll(){
    addDialog(butParam,drawSoundSpeqControll);
}
void rizeSoundSpeqSquareControll(){
    addDialog(butParam,drawSoundSpeqSquareControll);
}
 
 
 
void rizeDrawQs(){
    addDialog(butParam,editDrawQs);
}


void rizeMapOq(){
    addDialog(butParam,editMapOq);
}
void rizeColorStat(){
    addDialog(butParam,editColorStat);
}


void rizeAnglePannel(){
    addDialog(butParam,editAngle);
}
void rizeBarPannel(){
    addDialog(butParam,editBar);
}
void rizeGLPannelKoefs(){
    addDialog(butParam,editGlPannelKoefs);
}


void rizeFilterPannel(){
    addDialog(butParam,editFilter);
}
void rizeColorCorrectorPannel(){
    addDialog(butParam,editColorCorrector);
}
void rizeGLPannel(){
    addDialog(butParam,editGL);
}




struct layer*OSDtauch=NULL;
//#define OSDh 90
//#define OSDw 120
void markOSDTauch(){
    int a;
    a=OSDtauch->p[butParam];
   // a=a+80;
   // if(a>255)
        a=255;
    OSDtauch->p[butParam]=a;
    
}

void OSDDone(){
    printf("\nosd ");
    sendLayer(OSDtauch,stdout);    
 //   fprintf(stderr,"\nosd %d\n",OSDtauch!=NULL);

//    while(1);
}
int nosdImgs=0;
struct layer* osdImgs[128];

void copyOsd2buff(){
    if(butParam>=0&&butParam<128){
       if(OSDtauch!=NULL);
           freeLayer(OSDtauch);
       OSDtauch=copyLayer(osdImgs[butParam]);
       doneDialog();
    }
}
void OSDchoose(){
    bar(dSc,dX1,dY1,dX2,dY2,0);
    if(nosdImgs<=0){
        drawLine(dSc,dX1,dY1,dX2,dY2,RED);
    
    }else{
        int h,w,n,x,y,i;
        h=dY2-dY1;
        w=dX2-dX1;
        n=round(sqrt(nosdImgs)+.4999999);
//        fprintf(stderr,"%d",nosdImgs,n);
  //      fprintf(stderr,", %d\n",n);
        for(i=0,y=0;i<nosdImgs;y++){
            for(x=0;x<n && i<nosdImgs;x++,i++){
                int x1,y1,x2,y2;
                x1=dX1+x*w/n;
                x2=dX1+(x+1)*w/n-1;
                y1=dY1+y*h/n;
                y2=dY1+(y+1)*h/n-1;
                drawLayer(dSc,osdImgs[i],x1,y1,x2,y2);   
                addButton(x1,y1,x2,y2,i,copyOsd2buff);
                rectangle(dSc,x1,y1,x2,y2,BORDERCOLOR);
            
            }
        
        }
        
   
    }
    
    
    
    rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);

}
#include"bmp2layer.cpp"

void loadOsd(){
    char name[128];
    char fullname[256];
    FILE*f;
    int i;
    if(nosdImgs==0){
        i=0;
        f=fopen("osdlogo/list","r");
        if(f!=NULL){
            for(;i<128&&!feof(f);i++){
                if(fscanf(f,"%s",name)>0){
                    sprintf(fullname,"osdlogo/%s",name);
                    osdImgs[i]=bmp2layer(fullname);
                }
                if(osdImgs[i]==NULL)
                    i--;
            }
            fclose(f);
        }
        nosdImgs=i;
    }
    addDialog(0,OSDchoose,NULL);
}

void OSDEdit();
void osdDrawIt(){
     int i,j;
      for(i=0;i<OSDtauch->h;i++)
            for(j=0;j<OSDtauch->w;j++){
                OSDtauch->p[i*OSDtauch->w+j]=0;
            }
      addDialog(0,OSDEdit,NULL);
}
void osdTurnOff(){
    printf("\nosd 0 0\n");
    //OSDtauch;
    //OSDtauch;
    doneDialog(0);
}

void OSDCreate(){
    int sx;
    sx=(dX1*9+dX2)/10;
    bar(dSc,dX1,dY1,dX2,dY2,0);
    drawLayer(dSc,OSDtauch,sx,dY1,dX2,dY2);   
        addButton(dX1,dY1,sx,(dY1*3+dY2)/4,0,loadOsd);
    rectangle(dSc,dX1,dY1,sx,(dY1*3+dY2)/4,BORDERCOLOR);
        addButton(dX1,(dY1*3+dY2)/4,sx,(dY1+dY2)/2,0,osdDrawIt);
    rectangle(dSc,dX1,(dY1*3+dY2)/4,sx,(dY1+dY2)/2,BORDERCOLOR);
        addButton(dX1,(dY1+dY2*3)/4,sx,dY2,0,osdTurnOff);
    rectangle(dSc,dX1,(dY1+dY2*3)/4,sx,dY2,BORDERCOLOR);

    
    
    rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);
}
void OSDEdit(){
    int i,j;
    bar(dSc,dX1,dY1,dX2,dY2,0);
    if(OSDtauch==NULL)
        return;
    for(i=0;i<OSDtauch->h;i++)
        for(j=0;j<OSDtauch->w;j++){
            int x1,y1,x2,y2,mx,my;
            double m;
            x1=(dX1*(OSDtauch->w-j) + dX2*(j) )/ (OSDtauch->w);
            y1=(dY1*(OSDtauch->h-i) + dY2*(i) )/ (OSDtauch->h);

            x2=(dX1*(OSDtauch->w-j-1) + dX2*(j+1) )/ (OSDtauch->w) -1;
            y2=(dY1*(OSDtauch->h-i-1) + dY2*(i+1) )/ (OSDtauch->h) -1;
            addSButton(x1 ,y1,x2,y2,j+i*OSDtauch->w,markOSDTauch);
            m=1 - OSDtauch->p[i*OSDtauch->w+j]/255.;
            mx=(dX2-dX1)/OSDtauch->w * m/2;
            
            my=(dY2-dY1)/OSDtauch->h * m/2;
            
            rectangle(dSc,x1+mx,y1+my,x2-mx,y2-my,WHITE);
        }
        
 
 
    rectangle(dSc,dX1,dY1,dX2,dY2,BORDERCOLOR);
}
void rizeOSD(){
    int i,j;
   // if(OSDtauch == NULL){
     //   OSDtauch=makeLayer(OSDw,OSDh);
  //  }
   // if(OSDtauch != NULL){
     //   freeLayer(OSDtauch);
   // }
   if(OSDtauch == NULL){
     OSDtauch=bmp2layer("osdlogo/default.bmp");
   }
    if(OSDtauch==NULL){
        OSDtauch=makeLayer(120,90);
        for(i=0;i<OSDtauch->h;i++)
            for(j=0;j<OSDtauch->w;j++){
                OSDtauch->p[i*OSDtauch->w+j]=0;
            }

    }    
    if(OSDtauch!=NULL){
       /* int i,j;
         for(i=0;i<OSDtauch->h;i++)
            for(j=0;j<OSDtauch->w;j++){
                OSDtauch->p[i*OSDtauch->w+j]=0;
            }

        */
        addDialog(0,OSDCreate,OSDDone);
   //      addDialog(0,OSDEdit,OSDDone);
    }
}
