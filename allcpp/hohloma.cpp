//#define M_PI 3.1415926
#include"SDL/SDL.h"
#include<math.h>

#include"colors.cpp"
#include"graphutil.cpp"

#define HS 5.0 
#define HSS 6.0
#define LEAFSIZE 50

#define LEAFGROW 10
#define DISAPIRE 400


#define STARTGROW 9
#define FORK 50
#define LEAF 5
#define GROW 2

#define BARRY 1
#define BARRYSIZE 5
#define GROWCLUSTER 2
#define CLUSTEREND 5
#define CLUSTER  200
#define SHAKE 50


#define VISUAL1X 35.0
#define VISUAL1Y 50.0
#define TIMEDEVIDE1X 10.0
#define SUMTIMEDEVIDE1X 30.0
#define TIMEDEVIDE1Y 10.0
#define SUMTIMEDEVIDE1Y 100.0
#define CHECKNEWSPROUT 100

#define NEWSPROUT   5
 
#define BERRYBURST 50000
#define BURSTTIME    1000
#define BURSTMINTIME 100
#define BURSTSIZE 200
#define GRAVITY 0.6
#define SWING .3
#define SWINGPERIOD 20
#define WINDCHANGE 1000
#define MAXWIND   2.0




#define CHILDTIMESTEP .3



#define TIMEDEVIDE2X 10.0
#define SUMTIMEDEVIDE2X 15.0
#define TIMEDEVIDE2Y 4.0
#define SUMTIMEDEVIDE2Y 10.0
#define VISUAL2X 25.0
#define VISUAL2Y 5.0
#define FADE 100 
double h_time;

double wind=0;
struct grow{
   unsigned int id;
   int weight;
   int fade;
   double x1,y1,x2,y2,a,da,dda,ph,r;//x1,y1,x2,y2 -координаты начала и конца, a - текущее изменения угла роста, ph - возраст
   int state;// 0 - росток, 1 - палочка, 2 - гроздь, 3 - листик, 4 - ягодка 
   int burst;
struct grow*next;
}*root;
unsigned int growid;


#define hashSize  1000
unsigned int fade(unsigned int color,unsigned int fade){
    unsigned int r,g,b;
    if(fade==0)
        return color;
    r=color & 255;
    g=(color / 256) & 255; 
    b=(color / 256 / 256) &255;
    if(fade>FADE)
        fade=FADE;
    r=r*(FADE-fade)/FADE;
    g=g*(FADE-fade)/FADE;
    b=b*(FADE-fade)/FADE;
    return r |  (g*256)  | (b*256*256);
 }
int hash(int id){
    return id % hashSize;
}
struct hash{
    int id;
    int flag;
    int count;
    int minweight;
    struct hash*next;

} *table[hashSize];



void zerroTable(){
    int i;
    for(i=0;i<hashSize;i++){
        table[i]=NULL;
    }
}
void freeTable(){
    int i;
    for(i=0;i<hashSize;i++){
        if(table[i]!=NULL){
            free(table[i]);        
            table[i]=NULL;
        }
    }
    
}

int getHashFlag(int id){
    int h;
    struct hash*p;
    h=hash(id);
    p=table[h];
    while(p){
        if(p->id==id)
            return p->flag;
        p=p->next;
    }
    
    return 0;
}

int getHashMinWeight(int id){
    int h;
    struct hash*p;
    h=hash(id);
    p=table[h];
    while(p){
        if(p->id==id)
            return p->minweight;
        p=p->next;
    }
    
    return 0;
}
int getHashCount(int id){
    int h;
    struct hash*p;
    h=hash(id);
    p=table[h];
    while(p){
        if(p->id==id)
            return p->count;
        p=p->next;
    }
    
    return 0;
}

void setHashFlag(int id,int flag){
    int h;
    struct hash*p;
    h=hash(id);
    p=table[h];
    while(p){
        if(p->id==id){
            p->flag=flag;
            return;
        }
        p=p->next;
    }
    p=(struct hash*)malloc(sizeof(struct hash));
    if(p!=NULL){
        p->id=id;
        p->flag=flag;
        p->count=0;
        p->minweight=0;
        p->next=table[h];
        table[h]=p;
    }else{
        printf("Memory error\n");    
    
    }
}

void countHash(int id,int weight){
    int h;
    struct hash*p;
    h=hash(id);
    p=table[h];
    while(p){
        if(p->id==id){
            if(p->minweight > weight){
                p->minweight=weight;
            }
            p->count++;
            return;
        }
        p=p->next;
    }
    p=(struct hash*)malloc(sizeof(struct hash));
    if(p!=NULL){
        p->id=id;
        p->flag=0;
        p->count=1;
        p->minweight=weight;
        p->next=table[h];
        table[h]=p;
    }else{
        printf("Memory error\n");    
    
    }
}


char *space;
unsigned int *sumspace;

int h_h,h_w;

void h_line(SDL_Surface *sc,int x1, int y1, int x2, int y2,int c){
      drawLine(sc,x1,y1,x2,y2,c);
}
void setSpacePixel(int x,int y){
    if(x>=0 && x< h_w && y>=0 && y<h_w )
        space[x+y*h_w]=1;
}


double xvisual(struct grow *p){
    return cos((p->ph+h_time/TIMEDEVIDE1X)/SUMTIMEDEVIDE1X)*VISUAL1X+cos((p->ph+h_time/TIMEDEVIDE2X)/SUMTIMEDEVIDE2X)*VISUAL2X;

}
double yvisual(struct grow *p){
    return sin((p->ph+h_time/TIMEDEVIDE1Y)/SUMTIMEDEVIDE1Y)*VISUAL1Y+sin((p->ph+h_time/TIMEDEVIDE2Y)/SUMTIMEDEVIDE2Y)*VISUAL2Y;

}


int getSpacePixel(int x,int y){
    return space[x+y*h_w];
}
int check_h_spaceLine(int x1,int y1,int x2,int y2){
    x1/=5;
    x2/=5;
    y1/=5;
    y2/=5;
    if(x1<0)
        return 1;
    if(x1>=h_w)
        return 1;
        
    if(x2<0)
     return 1;
    if(x2>=h_w)
        return 1;
        
    if(y1<0)
    return 1;
    if(y1>=h_h)
        return 1;
        
    if(y2<0)
     return 1;
    if(y2>=h_h)
        return 1;
        
    
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    //
    int error = deltaX - deltaY;
    //
    if(getSpacePixel(x2, y2))
        return 1;
    while(x1 != x2 || y1 != y2) {
        if(getSpacePixel(x1, y1))
            return 1;
        const int error2 = error * 2;
        //
        if(error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
    }
    return 0;
}

int checkSpace(struct grow*p){
    if(p->state == 3){ // ЛИСТ
        double dx,dy;
        int l;
        dx=p->x2-p->x1;
        dy=p->y2-p->y1;
        l=sqrt(dx*dx+dy*dy) +0.9;
        if(p->x1 < 5+l || p->x1 > h_w * 5 -5 -l
                            ||
           p->y1 < 5+l || p->y1 > h_h * 5 -5 -l
           ||
           p->x2 < 5+l || p->x2 > h_w * 5 -5 -l
                ||
                           p->y2 < 5+l || p->y2 > h_h * 5 -5 -l
        
         )
         return 1;
    
    }

    if(check_h_spaceLine(p->x2+ cos(p->a)*HS,p->y2 + sin(p->a)*HS,p->x2 + cos(p->a)*HSS,p->y2 + sin(p->a)*HSS))
        return 0;
    return 1;

 
}
int check_h_spaceCircle(int x2,int y2,int r){

    int x,y,rr;
    x2=(x2+2)/5;
    y2=(y2+2)/5;
    r=(r+2)/5;
    for(x=x2-r;x<=x2+r;x++)
        for(y=y2-r;y<=y2+r;y++){
        rr=((x-x2)*(x-x2)+(y-y2)*(y-y2));
            if(rr<=r*r){
                if(x>=0&&x<h_w&&y>=0&&y<h_h)
                    if(getSpacePixel(x,y)){
                        return 1;
                    
                    }            
            }
        
        }
        return 0;

}
void h_spaceCircle(int x2,int y2,int r){

    int x,y,rr;
    x2=(x2+2)/5;
    y2=(y2+2)/5;
    r=(r+2)/5;
    for(x=x2-r;x<=x2+r;x++)
        for(y=y2-r;y<=y2+r;y++){
        rr=sqrt((x-x2)*(x-x2)+(y-y2)*(y-y2));
            if(rr<=r){
                if(x>=0&&x<h_w&&y>=0&&y<h_h)
                    setSpacePixel(x,y);
            }
        
        }
        
}



int checkBerrySpace(struct grow*p){       
   
    if(check_h_spaceCircle(p->x1+xvisual(p),p->y1+yvisual(p),p->r))
        return 0;
    return 1;

 
}
void h_spaceLine(int x1,int y1,int x2,int y2){
    x1/=5;
    x2/=5;
    y1/=5;
    y2/=5;
    if(x1<0)
     x1=0;
    if(x1>=h_w)
        x1=h_w-1;
        
    if(x2<0)
     x2=0;
    if(x2>=h_w)
        x2=h_w-1;
        
    if(y1<0)
     y1=0;
    if(y1>=h_h)
        y1=h_h-1;
        
    if(y2<0)
     y2=0;
    if(y2>=h_h)
        y2=h_h-1;
        
    
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    //
    int error = deltaX - deltaY;
    //
    setSpacePixel(x2, y2);
    while(x1 != x2 || y1 != y2) {
        setSpacePixel(x1, y1);
        const int error2 = error * 2;
        //
        if(error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
    }
}


void   drawSprout(SDL_Surface *screen,struct grow *p){
    h_line(screen,p->x1+xvisual(p),p->y1+yvisual(p),p->x2+xvisual(p),p->y2+yvisual(p),WHITE);
    h_spaceLine(p->x1,p->y1,p->x2,p->y2);
}

void   drawStick(SDL_Surface *screen,struct grow *p){
    int weight,i;
    weight=p->weight - getHashMinWeight(p->id);
    if(weight<0)
        weight=0;
    
    weight=log(weight*4);

    if(weight<1)
        weight=1;
    
    
    h_line(screen,p->x1+xvisual(p) ,p->y1+yvisual(p)   ,p->x2+xvisual(p)  ,p->y2+yvisual(p) ,fade(YELLOW,p->fade));
    
     h_line(screen,p->x1+xvisual(p) + weight*(p->id & 1) ,p->y1+yvisual(p)  + weight*(1 - p->id & 1),p->x2+xvisual(p) + weight*( p->id & 1),p->y2+yvisual(p)+ weight*(1 - p->id & 1),fade(YELLOW,p->fade));
    for(i=0;i<weight;i++){
       // h_line(screen,p->x1+xvisual(p) + i*(p->id & 1) ,p->y1+yvisual(p)  + i*(1 - p->id & 1),p->x2+xvisual(p) + i*( p->id & 1),p->y2+yvisual(p)+ i*(1 - p->id & 1),fade(YELLOW,p->fade));
        
        h_spaceLine(p->x1 +  i*(p->id & 1),p->y1+ i*(1 - p->id & 1),p->x2 + i*(p->id & 1),p->y2+ i*(1 - p->id & 1));
    }
}




void putLeaf(SDL_Surface *screen,int x1,int y1,int x2,int y2,int myfade){  
        int i,dx,dy,xx,yy;
        double a,cosa,sina,d;
        dx=x2 - x1;
        dy=y2 - y1;
        a=atan2(dy,dx);
        a-=M_PI/2;
        cosa=cos(a);
        sina=sin(a);
        
        for(i=0;i<LEAFSIZE;i++){
            xx=x1+dx*i/LEAFSIZE;
            yy=y1+dy*i/LEAFSIZE;
            if(i<LEAFSIZE/2)
              d=sqrt(i);
            else
              d=sqrt(LEAFSIZE-i);
           
           
            h_line(screen,xx,yy,xx+cosa*d,yy+sina*d,fade(GREEN,myfade));
        }
}

void putLeaf2(SDL_Surface *screen,double x1,double y1,double x2,double y2,int myfade){  
        int i,LS;
        double dx,dy,xx,yy;
        double a,cosa,sina,d,h1,h2,t,ls;
        //return ;
        dx=x2 - x1;
        dy=y2 - y1;
        a=atan2(dy,dx);
        ls=sqrt(dx*dx+dy*dy);
        LS=ls+1;
        a-=M_PI/2;
        cosa=cos(a);
        sina=sin(a);
        
        for(i=0;i<LS*1;i++){
            xx=x1+dx*i/1.0/ls;
            yy=y1+dy*i/1.0/ls;
            
            t = i*3.14*3.14/ls/1.0;
            h1 = sin(sqrt(t)) * ls/3.0;
            h2 = -sin(sqrt(2.0*t))/(1.0 + t*2) * ls/3.0;
           
           setPixel(screen,xx+h2*cosa,yy+h2*sina,fade(GREEN,myfade));
           setPixel(screen,xx+h1*cosa,yy+h1*sina,fade(GREEN,myfade));
           
          // h_line(screen,xx+h2*cosa,yy+h2*sina,xx+h1*cosa,yy+h1*sina,fade(GREEN,myfade));
        }
}



void   drawLeaf(SDL_Surface *screen,struct grow *p){
   
    putLeaf2(screen,p->x1+xvisual(p),p->y1+yvisual(p),p->x2+xvisual(p),p->y2+yvisual(p),p->fade);
    
   
   
    h_spaceLine(p->x1,p->y1,p->x2,p->y2);
}

void h_Circle(SDL_Surface *screen,int x2,int y2,int r,int c){

    int x,y,rr;
    r*=r;
    for(x=x2-r;x<=x2+r;x++)
        for(y=y2-r;y<=y2+r;y++){
        rr=((x-x2)*(x-x2)+(y-y2)*(y-y2));
            if(rr <=r){
                if(x>=0&&x<screen->w&&y>=0&&y<screen->h && viewPixel(screen,x,y) == 0  )
                    putpixel(screen,x,y, c);            
            }
        
        }

}

void   drawBerry(SDL_Surface *screen,struct grow *p){
    int dr;
    dr=0;
   
    if(p->burst>0){
        dr=SHAKE*fabs(sin(sqrt(p->burst)))/ sqrt(sqrt(p->burst));
    }
    
    h_Circle(screen,p->x1+xvisual(p),p->y1+yvisual(p),p->r+dr,fade(RED,p->fade));
    
   // if(check_h_spaceCircle(p->x1+xvisual(p),p->y1+yvisual(p),p->r+dr) && p->burst<1.0){
     //   p->burst=200;  
    
   // }
    h_spaceCircle(p->x1+xvisual(p),p->y1+yvisual(p),p->r+dr);
    //h_spaceCircle(p->x1,p->y1,p->x2,p->y2);
}

void   drawBurst(SDL_Surface *screen,struct grow *p){
    if(p->r>4)
        h_Circle(screen,p->x1+xvisual(p),p->y1+yvisual(p),p->r,fade(WHITE,p->fade));
    
}

unsigned int inline getR(unsigned int c){
    return c&255;
}
unsigned int inline getG(unsigned int c){
    return (c/256)&255;
}
unsigned int inline getB(unsigned int c){
    return (c/256/256)&255;
}
unsigned int inline getC(unsigned int r,unsigned int g,unsigned int b){
    if(r>255)
        r=255;
    if(g>=255)
        g=255;
    if(b>255)
        b=255;
    return r | (g*256) | (b*256*256);

}



void   	smooth(SDL_Surface* screen ){
    //int rdx,rdy,gdx,gdy
    int x,y,i,j,a;
    unsigned int c,r,g,b;
    unsigned int *p;
    int bpp = screen->format->BytesPerPixel;
    int pitch = screen->pitch/bpp;
    int matrix[9]={ 1,2,1,
                       2,4,2,
                       1,2,1};//16
    for(y=1,p=((unsigned int *)screen->pixels)+pitch;y<screen->h-1;y++,p+=pitch - screen->w+1)
        for(x=1,p++;x<screen->w-1;x++,p++)
        {
            r=0;
            g=0;
            b=0;
            for(i=-1,a=0;i<=1;i++)
                for(j=-1;j<=1;j++,a++){
                    c=*(p+i+j*pitch);
                    r+=getR(c)*matrix[a];    
                    g+=getG(c)*matrix[a];    
                    b+=getB(c)*matrix[a];    
                }
            r/=16;
            g/=16;
            b/=16;
            c=getC(r,g,b);
            *p=c;
        
        }



}




void drawHohloma(SDL_Surface* screen){

    struct grow *p;
    
 //   SDL_FillRect(screen,NULL, 0x000000); 
    
    if(space!=NULL)
     memset(space,0,h_h*h_w);
    h_time+=1;
    for(p=root;p!=NULL;p=p->next){
        if(p->state==0){
            drawSprout(screen,p);
        }
        if(p->state==1){
            drawStick(screen,p);
        }
        if(p->state==3){
            drawLeaf(screen,p);
        }
        if(p->state==4){
            drawBerry(screen,p);
            
        }
        if(p->state==5){
            drawBurst(screen,p);
        }
    }    
  	
 
  	//postProcess( screen );
  //	printf("Hello\n");
	//fflush(stdout);

  //	SDL_GL_SwapBuffers();
  	//SDL_Flip( screen ); 
  	//SDL_UpdateRect(screen, 0, 0, 0, 0)  ;
}


int checkSumSpace(int x, int y){
    int s,i,j;
    s=0;
    for(i=x-3;i<x+4;i++){
        for(j=y-3;j<y+4;j++){
            if(i>=0&&i<h_w&&j>=0&&j<h_h){
                s+=sumspace[i+j*h_w];
            }
        }
    }

    return s;
}
void     checkPostBurst(){
    grow *tmp,*p,*parrent;
    while(root != NULL && root->state==5 && root->r < 5){
        p=root->next;
       // printf("free root %d\n",root->id);
        free(root);
        root=p;
   }
   parrent=root;
   while(parrent!=NULL && parrent->next != NULL){
        if(parrent->next->state==5 && parrent->next->r < 5){
           // printf("free %d\n",parrent->next->id);
            tmp=parrent->next->next;
            free(parrent->next);
            parrent->next=tmp;
            
        }else{
            parrent = parrent->next;
        }
    }
}
void     distructBurst(int x,int y,double r){
    grow *tmp,*p,*parrent;
    while(root != NULL && root->state!=5 && (root->x1-x)*(root->x1-x)+ (root->y1-y)*(root->y1-y)<r*r){
        p=root->next;
       // printf("free root %d\n",root->id);
        free(root);
        root=p;
   }
   parrent=root;
   while(parrent!=NULL && parrent->next != NULL){
        if(parrent->next->state!=5 && parrent->next->state!=5 && (parrent->next->x1-x)*(parrent->next->x1-x)+ (parrent->next->y1-y)*(parrent->next->y1-y)<r*r){
           // printf("free %d\n",parrent->next->id);
            tmp=parrent->next->next;
            free(parrent->next);
            parrent->next=tmp;
            
        }else{
            parrent = parrent->next;
        }
    }
}

void burst(int x,int y,double ph){
   struct grow*p,*newroot,*pnext;
   double r;
   p=(struct grow*)malloc(sizeof(struct grow));
   if(p!=NULL){
       p->x1=x;
       p->y1=y;
       p->ph=ph;
       r=rand()%BURSTSIZE;
       p->r=r;
       p->ph=ph;
       p->state=5;//ВЗРЫВ
       p->next=root;
       p->id=0;
       p->weight=0;
       p->fade=0;
       root=p;
                     
   }
/*   newroot=NULL;
   for(p=root;p!=NULL;p=pnext){
        if(p->state!=5 && (p->x1-x)*(p->x1-x)+ (p->y1-y)*(p->y1-y)<r*r){
            pnext=p->next;
            free(p);
        }else{
            pnext=p->next;
            p->next=newroot;
            newroot=p;        
        }
   
   }
   root=newroot;
 */  
     distructBurst(x,y,r);
}


/*

void     checkPostBurst(grow ** p){
grow *tmp;  
   // return;
    while(*p != NULL){
        if((*p)->state==5 && (*p)->r < 5){
            tmp=(*p)->next;
            (*p)->state=6;
            free(*p);
            *p=tmp;
        }else{
            p = & ((*p)->next);
        }
    }
}


*/

void moveHohloma(){
    struct grow *addon,*p,*q,*newroot,*pnext;
    int forksign,x,y,s,sm,sx,sy;
    addon=NULL;
    freeTable();
    for(x=0;x<h_w;x++){
        for(y=0;y<h_h;y++){
            if(!getSpacePixel(x,y)){
                if(!(rand()%NEWSPROUT)){
                    sumspace[x+y*h_w]++;    
                }        
            }else{
                sumspace[x+y*h_w]=0;
            
            }
        }
    }
    
    
    if(!(rand()%CHECKNEWSPROUT)){
       
        sm=-32000;
        for(x=0;x<h_w;x++){
            for(y=0;y<h_h;y++){
                s=checkSumSpace(x,y);
                if(s>sm){
                    sm=s;
                    sx=x;
                    sy=y;
                }
        
            }
        }
        if(sm>0){
             p=(struct grow*)malloc(sizeof(struct grow));
             if(p!=NULL){
                 double a,da,dda;
                 a=((rand()%1000)/1000.0)*2.0*M_PI;
                 da=((rand()%1000)/50000.0)*M_PI;
                 dda=((rand()%1000)/2500000.0)*2.0*M_PI;
                 p->id=growid++;
                 p->x1=sx*5+2;
                 p->y1=sy*5+2;
                 p->x2=sx*5+2+cos(a)*HS;
                 p->y2=sy*5+2+sin(a)*HS;
                 p->a=a;
                 p->da=da;
                 p->dda=dda;
                 p->ph=0;
                 p->burst=0;
                 p->state=0;
                 p->weight=0;
                 p->fade=0;
        
        
                 p->next=root;
                 root=p;
                if(sumspace!=NULL)
                    memset(sumspace,0,h_h*h_w*sizeof(unsigned int));  
                 
              }        
        
        }
    }
    
  // newroot=NULL;
  int minid= -1 ;
   for(p=root;p!=NULL;p=p->next){
        if(minid==-1 || minid> p->id){
            minid=p->id;
        }
        countHash(p->id,p->weight);
        if(p->state==0){//Росток
            setHashFlag(p->id,2);        
        }
        
        
    /*    if(p->state==5 && p->r < 5){
            pnext=p->next;
            free(p);
        }else{
            pnext=p->next;
            p->next=newroot;
            newroot=p;        
        }
   */
   }
  
  if(!(rand()%DISAPIRE)){
    if(minid!=-1){
        for(p=root;p!=NULL;p=p->next){
            if(p->id == minid){
                p->burst=-1;   
            
            }
        }
    
    }  
  
  
  }
  
  //root=newroot;
   
    checkPostBurst();
    
    
    
   
   
    for(p=root;p!=NULL;p=p->next){
        if(p->state!=5 && (getHashFlag(p->id)!=2/* &&  (growid -  p->id > 10  || growid < p->id) */ ) && getHashCount(p->id)<150){
            p->burst=-1;

        }
        if(p->burst==-1){
            //p->y1+=GRAVITY;
            //p->y2+=GRAVITY;
            p->fade++;
           //p->x1+=wind+SWING*cos((p->ph+h_time)/SWINGPERIOD);
           //p->x2+=wind+SWING*cos((p->ph+h_time)/SWINGPERIOD);
           if(p->fade>=FADE||p->y1>h_h*5 && p->y2 > h_h*5){
            p->state=5;
            p->r=3;
        } 
        }
        
        
        
        if(p->state==5){//Взрыв
            p->r=p->r*0.8;
            
        }
        
        if(p->state==3){//ЛИСТ
            double dx,dy,sz,a,x2,y2;
            if(!(rand()%LEAFGROW)){
                dx = p->x2 - p->x1;
                dy = p->y2 - p->y1;
                sz = sqrt(dx*dx + dy* dy);
                if(sz>0.1){
                    a=atan2(dy,dx);
                    if(sz < LEAFSIZE){
                        sz*=1.04;
                        x2=p->x2;
                        y2=p->y2;
                        p->x2=p->x1+sz*cos(a);
                        p->y2=p->y1+sz*sin(a);               
                        if(!checkSpace(p)){
                            p->x2=x2;
                            p->y2=y2;
                        }
                    }
                }
            }
        }
        
        if(p->state==4){//Ягода
            if(p->burst>1){
                p->burst--;
            }else if(p->burst==1){
                    burst(p->x1,p->y1,p->ph);
                    break;            
            
            }else if(!(rand()%BERRYBURST)){
                p->burst=BURSTMINTIME+rand()%BURSTTIME;
                printf("BERRYBURST %d\n",p->burst);
            
            }
            
        
        }
        if(p->state==2){///Гроздь
          if(!(rand()%GROWCLUSTER)){
                p->state=1;
                if((rand()%CLUSTEREND)){
                    q=(struct grow*)malloc(sizeof(struct grow));/// растём линейно
                    if(q==NULL)
                       continue;
                    q->id=p->id;
                    q->x1=p->x2;
                    q->y1=p->y2;
                    q->a=p->a+p->da;
                    q->da=p->da+p->dda;
                    q->dda=p->dda;
                    q->burst=0;
                    q->x2=q->x1+cos(q->a)*HS;
                    q->y2=q->y1+sin(q->a)*HS;
                    q->ph=p->ph+CHILDTIMESTEP;
                    q->state=2;
                    q->weight=p->weight-1;
                    q->next=addon;
                    q->fade=p->fade;
                    if(checkSpace(q)){
                          addon=q;            
                    }else{
                        free(q);            
                    }  
                 }
                 if(!(rand()%BARRY)){
                    q=(struct grow*)malloc(sizeof(struct grow));/// Ягодка
                    if(q==NULL)
                        continue;
                    q->id=p->id;
                    forksign=1-2*(rand()%2); //1 или -1;
                    q->a=p->a+M_PI/2.0*forksign;
                    q->x1=p->x2+cos(q->a)*BARRYSIZE;
                    q->y1=p->y2+sin(q->a)*BARRYSIZE;

                    q->da=forksign*p->da;
                    q->r=BARRYSIZE;
                    q->burst=0;
                    q->ph=p->ph+CHILDTIMESTEP;
                    q->state=4;
                    q->next=addon;
                    q->weight=p->weight-1;
                    q->fade=p->fade;
                    if(checkBerrySpace(q)){
                        addon=q;            
                    }else{
                        free(q);            
                    }    
                 }
                 
                
                 
                 
          
          }          
        
        }
        
        if(p->state==0){// Росток
            if(!(rand()%GROW)){
                p->state=1;
                q=(struct grow*)malloc(sizeof(struct grow));/// растём линейно
                if(q==NULL)
                    continue;
                q->id=p->id;;
                q->x1=p->x2;
                q->y1=p->y2;
                q->a=p->a+p->da;
                q->da=p->da+p->dda;
                q->dda=p->dda;
                q->burst=0;
                q->x2=q->x1+cos(q->a)*HS;
                q->y2=q->y1+sin(q->a)*HS;
                q->ph=p->ph+CHILDTIMESTEP;
                q->state=0;
                q->weight=p->weight-1;
                q->next=addon;
                q->fade=p->fade;
                if(checkSpace(q)){
                        addon=q;            
                }else{
                    free(q);            
                }
                if(!(rand()%CLUSTER)){
                    q=(struct grow*)malloc(sizeof(struct grow));/// порождаем ветку
                    if(q==NULL)
                        continue;
                    q->id=p->id;;
                    forksign=1-2*(rand()%2); //1 или -1;
                    q->x1=p->x2;
                    q->y1=p->y2;
                    q->a=p->a+M_PI/6.0*forksign;
                    q->da=forksign*p->da;
                    q->dda=((rand()%1000)/2500000.0)*2.0*M_PI;
                    q->x2=q->x1+cos(q->a)*HS;
                    q->y2=q->y1+sin(q->a)*HS;
                    q->ph=p->ph+CHILDTIMESTEP;
                    q->state=2;
                    q->burst=0;
                    q->weight=p->weight-1;
                    q->next=addon;
                    q->fade=p->fade;
                    if(checkSpace(q)){
                        addon=q;            
                    }else{
                        free(q);   
                                 
                    }    
                
                }
                
                if(!(rand()%FORK)){
                    q=(struct grow*)malloc(sizeof(struct grow));/// порождаем ветку
                    if(q==NULL)
                        continue;
                    q->id=p->id;
                    forksign=1-2*(rand()%2); //1 или -1;
                    q->x1=p->x2;
                    q->y1=p->y2;
                    q->a=p->a+M_PI/6.0*forksign;
                    q->da=forksign*p->da;
                    q->dda=((rand()%1000)/2500000.0)*2.0*M_PI;
                    q->x2=q->x1+cos(q->a)*HS;
                    q->y2=q->y1+sin(q->a)*HS;
                    q->ph=p->ph+CHILDTIMESTEP;
                    q->state=0;
                    q->burst=0;
                    q->weight=p->weight-1;
                    q->next=addon;
                    q->fade=p->fade;
                    if(checkSpace(q)){
                        addon=q;            
                    }else{
                        free(q);   
                                 
                    }    
                
                }
                if(!(rand()%LEAF)){
                    double sz;
                    q=(struct grow*)malloc(sizeof(struct grow));/// порождаем ветку
                    if(q==NULL)
                        continue;
                    q->id=p->id;;
                    forksign=1-2*(rand()%2); //1 или -1;
                    q->x1=p->x2;
                    q->y1=p->y2;
                    q->a=p->a+M_PI/6.0*forksign;
                    q->da=forksign*p->da;
                    
                    sz=0.3;//((rand()%100 )/100.0) +.1;
                    q->x2=q->x1+cos(q->a)*LEAFSIZE * sz;
                    q->y2=q->y1+sin(q->a)*LEAFSIZE * sz;
                    q->ph=p->ph+CHILDTIMESTEP;
                    q->state=3;
                    q->burst=0;
                    q->weight=p->weight-1;
                    q->next=addon;
                    q->fade=p->fade;
                    if(checkSpace(q)){
                        addon=q;            
                    }else{
                        free(q);            
                    }    
                
                }
                
            }
        
        }
    }
    if(root!=NULL){
        for(p=root;p->next!=NULL;p=p->next);
        p->next=addon;    
    }else{
        root=addon;    
    }
}
void zeroHohloma(SDL_Surface* screen){
    int x,y,i;
    double a,da,dda;
    struct grow*p;
    wind=(rand()%1000)*MAXWIND*2/1000.0 - MAXWIND;
    for(x=0;x<screen->w;x++){
        for(y=0;y<screen->h;y++){
            putpixel(screen,x,y,0);        
        }
    
    }
    root=NULL;
   
    for(i=0;i<STARTGROW;i++){
        p=(struct grow*)malloc(sizeof(struct grow));
        if(p==NULL)
            continue;
        
        x=rand()%(screen->w);
        y=rand()%(screen->h);
        a=((rand()%1000)/1000.0)*2.0*M_PI;
        da=((rand()%1000)/50000.0)*M_PI;
        dda=((rand()%1000)/2500000.0)*2.0*M_PI;
        p->id=growid++;
        p->x1=x;
        p->y1=y;
        p->x2=x+cos(a)*HS;
        p->y2=y+sin(a)*HS;
        p->a=a;
        p->da=da;
        p->dda=dda;
        p->ph=0;
        p->state=0;
        p->burst=0;
        p->weight=0;
        p->fade=0;
        p->next=root;
        root=p;
    }
    h_w=(screen->w)/5;
    h_h=(screen->h)/5;
    space=(char*)malloc(h_h*h_w*sizeof(char));
    sumspace=(unsigned int*)malloc(h_h*h_w*sizeof(unsigned int));
   
    
    if(space!=NULL)
        memset(space,0,h_h*h_w);
    if(sumspace!=NULL)
        memset(sumspace,0,h_h*h_w*sizeof(unsigned int));  
    
}
void closeHohloma(){
    struct grow*p,*q;
    p=root;
    while(p!=NULL){
        q=p->next;
        free(p);
        p=q;    
    }
    if(space!=NULL){
        free(space);
    }
     if(sumspace!=NULL){
        free(sumspace);
    }

}