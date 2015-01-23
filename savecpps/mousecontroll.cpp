#ifndef MOUSECONTOLLMOD
#define MOUSECONTOLLMOD
#include"colors.cpp"
#define MAXDROPS 128
struct drop{
    int x,y;
    double r;
}drops[MAXDROPS];
//int ndrops=0;

void addDrop(int x,int y){
    int i;
    for(i=0;i<MAXDROPS;i++){
        if(drops[i].r<=0.){
            drops[i].x=x;
            drops[i].y=y;
            drops[i].r=15;   
            return;
        }
    }
}
void showDrops(SDL_Surface* screen){
    int i;
    for(i=0;i<MAXDROPS;i++){
        if(drops[i].r>0){
            circle(screen,drops[i].x,drops[i].y,drops[i].r,GREEN);
            drops[i].r*=2.3;   
            if(drops[i].r>screen->w)
                drops[i].r=-1;
        }
    }


}




#define MAXEVALUES 1024
struct eValue{
    int x1,y1,x2,y2,x,y,mx,my;
    int type;
    double d;
    void *ptr;
    double last;    
    double min,max;
    struct adr adr;
}eValues[MAXEVALUES],selectedEValue;
int neValues=0;
void clearEvalues(){
    neValues=0;
}
void addEValue(int x1,int y1,int x2,int y2,struct adr a){
    if (neValues > MAXEVALUES)
        return;
    eValues[neValues].x1=x1;
    eValues[neValues].y1=y1;
    eValues[neValues].x2=x2;
    eValues[neValues].y2=y2;
    eValues[neValues].d=0.001;        
    eValues[neValues].min=0;        
    eValues[neValues].max=1.;        

    eValues[neValues].ptr=NULL;
    eValues[neValues].adr=a;
    eValues[neValues].type=3;
    neValues++;
    


}
void addEValue(int x1,int y1,int x2,int y2,double min,double max,struct adr a){
    if (neValues > MAXEVALUES)
        return;
    eValues[neValues].x1=x1;
    eValues[neValues].y1=y1;
    eValues[neValues].x2=x2;
    eValues[neValues].y2=y2;
    eValues[neValues].d=0.001;        
    eValues[neValues].min=min;        
    eValues[neValues].max=max;        

    eValues[neValues].ptr=NULL;
    eValues[neValues].adr=a;
    eValues[neValues].type=3;
    neValues++;
    


}
void addEValue(int x1,int y1,int x2,int y2,int type,double d,double min,double max,void*ptr){
    if (neValues > MAXEVALUES)
        return;
    eValues[neValues].x1=x1;
    eValues[neValues].y1=y1;
    eValues[neValues].x2=x2;
    eValues[neValues].y2=y2;
    eValues[neValues].d=d;        
    eValues[neValues].min=min;        
    eValues[neValues].max=max;        

    eValues[neValues].ptr=ptr;
    eValues[neValues].type=type;
    neValues++;
}
int selectEValue(int x,int y){
   int i;
    for(i=neValues-1;i>=0;i--){
        if(x>=eValues[i].x1 && x<=eValues[i].x2
            &&
            y>=eValues[i].y1 && y<=eValues[i].y2
            &&(eValues[i].ptr!=NULL||eValues[i].type==3&&correctOpt(eValues[i].adr))
        ){
            selectedEValue=eValues[i];
            selectedEValue.x=x;
            selectedEValue.y=y;
            if(selectedEValue.type==0){
                selectedEValue.last=*((double*)selectedEValue.ptr);
            }
            else if(selectedEValue.type==1){
                selectedEValue.last=*((int*)selectedEValue.ptr);
            }else if(selectedEValue.type==3){
                selectedEValue.last=getOpt(selectedEValue.adr);
            }
            return 1;
        }
    }
    selectedEValue.ptr=NULL;
    return 0;
}
void markSelectedValue(SDL_Surface* screen){
    if(selectedEValue.ptr!=NULL ||selectedEValue.type==3&&correctOpt(selectedEValue.adr)){
        rectangle(screen,selectedEValue.x1,selectedEValue.y1,selectedEValue.x2,selectedEValue.y2,RED);
        drawLine(screen,selectedEValue.x,selectedEValue.y,selectedEValue.mx,selectedEValue.y,WHITE);
        drawLine(screen,selectedEValue.mx,selectedEValue.y,selectedEValue.mx,selectedEValue.my,WHITE);
        
    }

}
void relizeSelectedValue(){
    selectedEValue.ptr=NULL;
    selectedEValue.type=0;
}
void modifySelected(int x,int y){
    if(selectedEValue.ptr!=NULL||selectedEValue.type==3&&correctOpt(selectedEValue.adr)){
        double d;
        selectedEValue.mx=x;
        selectedEValue.my=y;
        d=selectedEValue.last  + ((x-selectedEValue.x)+(selectedEValue.y-y))*selectedEValue.d;
        if(d>selectedEValue.max)
                d=selectedEValue.max;
        if(d<selectedEValue.min)
                d=selectedEValue.min;
        
        if(selectedEValue.type==0){
            double*v;
            v=(double*)selectedEValue.ptr;
            *v=d;                
            
        }
        else if(selectedEValue.type==1){
            int*v;
            v=(int*)selectedEValue.ptr;
            *v=d;
        } 
        else if(selectedEValue.type==3){
            //int*v;
            //v=(int*)selectedEValue.ptr;
            setOpt(selectedEValue.adr,d);
            
        }            
    }
}

void clearButtons();
void addButton(int x1,int y1,int x2,int y2,int param,void(*handler)());
#define MAXDIALOGS 128
struct dialog{
    void (*drawDialog)();
    void (*doneDialog)();
    int param;
    char sparam[32];
}dialogs[MAXDIALOGS];
int ndialogs=0;
int dialogParam=0;
char sdialogParam[32];
int dX1;
int dY1;
int dX2;
int dY2;
SDL_Surface* dSc;

//    (butParam,editAngle);
void addDialog(int param,void(*draw)(),void(*done)()){
    if (ndialogs > MAXDIALOGS)
        return;
    dialogs[ndialogs].drawDialog=draw;
    dialogs[ndialogs].doneDialog=done;
    dialogs[ndialogs].param=param;
    ndialogs++;
}
void addDialog(char*sparam,void(*draw)(),void(*done)()){
    if (ndialogs > MAXDIALOGS)
        return;
    dialogs[ndialogs].drawDialog=draw;
    dialogs[ndialogs].doneDialog=done;
    dialogs[ndialogs].param=-6666;
    strcpy(dialogs[ndialogs].sparam,sparam);

    ndialogs++;
}
void addDialog(int param,void(*draw)()){
    addDialog(param,draw,NULL);
}

void addDialog(char* sparam,void(*draw)()){
    addDialog(sparam,draw,NULL);
}


void doneDialog(int distructor){
    if(ndialogs>0){
       ndialogs--;
       if(distructor&&dialogs[ndialogs].doneDialog!=NULL)
           (dialogs[ndialogs].doneDialog)();

    }

}
void doneDialog(){
    doneDialog(1);
}
extern int rizePannel;
void showDialog(SDL_Surface* screen){
    if(ndialogs>0){
        clearButtons();
        clearEvalues();
        dialogParam=dialogs[ndialogs-1].param;
        if(dialogParam==-6666){
            strcpy(sdialogParam,dialogs[ndialogs-1].sparam);
        }
        dX1=screen->w/10;
        dX2=8*screen->w/10;
        dY1=screen->h/10;
        dY2=8*screen->h/10;       
        dSc=screen;
        int rp;
        rp=rizePannel;
        rizePannel=1;
        (*dialogs[ndialogs-1].drawDialog)();
        rizePannel=rp;

        bar(screen,dX2,dY2,screen->w,screen->h,VERYGREEN);
        addButton(dX2,dY2,screen->w,screen->h,0,doneDialog);        
    }

}


#define MAXBUTTS 20240
struct butt{
    int x1,y1,x2,y2;
    int param;
    int type;
    char sparam[32];
    void(*handler)();
    
}butts[MAXBUTTS];
int nbutts=0;
int butParam;
char sbutParam[32];


void clearButtons(){
    nbutts=0;

}
void addButton(int x1,int y1,int x2,int y2,int param,void(*handler)()){
    if (nbutts >= MAXBUTTS)
        return;
    butts[nbutts].x1=x1;
    butts[nbutts].y1=y1;
    butts[nbutts].x2=x2;
    butts[nbutts].y2=y2;
    butts[nbutts].type=1;
    butts[nbutts].handler=handler;
    butts[nbutts].param=param;
    nbutts++;
}
void addRelizeButton(int x1,int y1,int x2,int y2,int param,void(*handler)()){
    if (nbutts >= MAXBUTTS)
        return;
    butts[nbutts].x1=x1;
    butts[nbutts].y1=y1;
    butts[nbutts].x2=x2;
    butts[nbutts].y2=y2;
    butts[nbutts].type=3;
    butts[nbutts].handler=handler;
    butts[nbutts].param=param;
    nbutts++;
}

void addRelizeButton(int x1,int y1,int x2,int y2,char*s_param,void(*handler)()){
    if (nbutts >= MAXBUTTS)
        return;
    butts[nbutts].x1=x1;
    butts[nbutts].y1=y1;
    butts[nbutts].x2=x2;
    butts[nbutts].y2=y2;
    butts[nbutts].type=3;
    butts[nbutts].handler=handler;
    butts[nbutts].param=-6666;
    strcpy(butts[nbutts].sparam,s_param);

    nbutts++;
}


void addSButton(int x1,int y1,int x2,int y2,int param,void(*handler)()){
    if (nbutts >= MAXBUTTS)
        return;
    butts[nbutts].x1=x1;
    butts[nbutts].y1=y1;
    butts[nbutts].x2=x2;
    butts[nbutts].y2=y2;
    butts[nbutts].type=2;
    butts[nbutts].handler=handler;
    butts[nbutts].param=param;
    nbutts++;
}

int clickRelizeMouse(int x,int y){
    int i;
    for(i=nbutts-1;i>=0;i--){
        if((butts[i].type==3) &&  x>=butts[i].x1 && x<=butts[i].x2
            &&
            y>=butts[i].y1 && y<=butts[i].y2
        ){
            butParam=butts[i].param;
            if(butts[i].param=-6666){
                strcpy(sbutParam,butts[i].sparam);
            }
            (*butts[i].handler)();
            return 1;
        }
    }
    return 0;
}

int clickMouse(int x,int y){
    int i;
    for(i=nbutts-1;i>=0;i--){
        if((butts[i].type==1) &&  x>=butts[i].x1 && x<=butts[i].x2
            &&
            y>=butts[i].y1 && y<=butts[i].y2
        ){
            butParam=butts[i].param;
            (*butts[i].handler)();
            return 1;
        }
    }
    return 0;
}
int sclickMouse(int x,int y){
    int i;
    for(i=nbutts-1;i>=0;i--){
        if((butts[i].type==2) &&  x>=butts[i].x1 && x<=butts[i].x2
            &&
            y>=butts[i].y1 && y<=butts[i].y2
        ){
            butParam=butts[i].param;
            (*butts[i].handler)();
            return 1;
        }
    }
    return 0;
}
#endif
