#ifndef FRAQVERTEXMOD
#define FRAQVERTEXMOD
struct fraqVertex{
   double x,y,dx,dy;
   int ok;
}pVer[60][2][8192];

void zeroFraqVertex(){
    int i,j;
    for(i=0;i<60;i++)
        for(j=0;j<8192;j++){
            pVer[i][0][j].ok=0;
            pVer[i][1][j].ok=0;
            pVer[i][0][j].dx=0;
            pVer[i][1][j].dx=0;
            pVer[i][0][j].dy=0;
            pVer[i][1][j].dy=0;
        }

}
extern double pifTimeKoef;
struct fraqVertex a_replace;
struct fraqVertex *rePlace(int nRep,int nTree,int par,double x,double y,double soft,double weight){
   double dx,dy;

    struct fraqVertex *p;
//    double pifTimeKoef =1;
    a_replace.ok=0;
    if(soft>1.)
        soft=1.;
    if(nRep>=0&&nRep<60&&nTree>=0&&nTree<8192&&par>=0&&par<2){
        p=&(pVer[nRep][par][nTree]);
    }else{
        p=&a_replace;
    }


    if(p->ok){
        if(pifTimeKoef>10){
            p->x=x;
            p->y=y;      
            p->dx=0;
            p->dy=0;      
        }else
        if(weight<0.001){
            p->x=x*(1.-soft)+p->x*soft;
            p->y=y*(1.-soft)+p->y*soft;
        }else{
            weight=fabs(weight);
            if(weight>1.)
                weight=1.;
            dx=(x-p->x)/2;
            dy=(y-p->y)/2;
            if(soft*pifTimeKoef>1){
                p->dx=0;
                p->dy=0;    
            }else{
                p->dx=p->dx*(1-soft*pifTimeKoef);
                p->dy=p->dy*(1-soft*pifTimeKoef);
            }
            p->dx+=dx*(1-weight);
            p->dy+=dy*(1-weight);
            dx=p->dx*pifTimeKoef;
            dy=p->dy*pifTimeKoef;
            if(dx>1000)
                dx=1000;
            if(dy>1000)
                dy=1000;
            
            if(dx<-1000)
                dx=-1000;
            
            if(dy<-1000)
                dy=-1000;
            
            p->x+=dx;
            p->y+=dy;
            if(p->x<-1000.)
                p->x=-1000.;
            if(p->y<-1000.)
                p->y=-1000.;
            if(p->x>screenW+1000)
                p->x=screenW+1000;
            if(p->y>screenH+1000)
                p->y=screenH+1000;

            /*        
        
            double dx,dy;
            weight=fabs(weight);
            if(weight>1.)
                weight=1.;
            dx=(x-p->x)/2;
            dy=(y-p->y)/2;
            if(soft*pifTimeKoef>1){
                p->dx=0;
                p->dy=0;    
            }else{
                p->dx=p->dx*(1-soft*pifTimeKoef);
                p->dy=p->dy*(1-soft*pifTimeKoef);
            }
            p->dx+=dx*(1-weight);
            p->dy+=dy*(1-weight);
            if(p->dx<-100.);
                p->dx=-100.;
            if(p->dx>100.);
                p->dx=100.;
            if(p->dy<-100.);
                p->dy=-100.;
            if(p->dy>100.);
                p->dy=100.;

            p->x+=p->dx*pifTimeKoef;
            p->y+=p->dy*pifTimeKoef;
            if(p->x<-100)
                p->x=-100;
            if(p->y<-100)
                p->y=-100;
            if(p->x>screenW+100)
                p->x=screenW+100;
            if(p->y>screenH+100)
                p->y=screenH+100;
            */
        }
    }else{
        p->x=x;
        p->y=y;
        p->ok=1;
    }
    return p;
}

#endif
