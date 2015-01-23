#define MAXPARTICLES 3000
struct  particle{
    double x,y,dx,dy;
} ps[MAXPARTICLES];

void layer2particles(SDL_Surface*sc,struct layer*l,double g,double co,double v0,double k){
    int n,i,x,y,dx,dy,a,v,b;
    double kx,ky,f;
    kx=(l->w)/((double)sc->w);
    ky=(l->h)/((double)sc->h);
    
    n=co*MAXPARTICLES;
    if(n>MAXPARTICLES){
        n=MAXPARTICLES;
    }
    for(i=0;i<n;i++){
        x=round(ps[i].x *kx);
        y=round(ps[i].y *ky);
        b=x+y*l->w;
        for(dx=-1;dx<=1;dx++){
            for(dy=-1;dy<=1;dy++){
                if(!dx && !dy || x+dx<0 || x+dx>=l->w|| y+dy<0 || y+dy>=l->h || x<0 || x>=l->w|| y<0 || y>=l->h)
                    continue;
                a=x+dx+(y+dy)*l->w;
                ps[i].dx+=dx*(l->p[a]-l->p[b])*g;
                ps[i].dy+=dy*(l->p[a]-l->p[b])*g;
            }
        }
//        ps[i].dx+=(rand()%1001 - 500)/10000.;
  //      ps[i].dy+=(rand()%1001 - 500)/10000.;
        ps[i].x+=ps[i].dx;
        ps[i].y+=ps[i].dy;
        ps[i].dy*=k;
        ps[i].dx*=k;
        
        x=ps[i].x;
        y=ps[i].y;
        if( x>=0&&x<sc->w && y>=0 && y<sc->h && fabs(ps[i].dx)+fabs(ps[i].dy)>0.2){
            //circle(sc,sc->w/2,sc->h/2,10,WHITE);
            circle(sc,x,y,2,WHITE);

//            putpixel(sc,x,y,WHITE);
        }else{
            ps[i].x=rand()%sc->w;
            ps[i].y=rand()%sc->h;
            f=(rand()%1000)/500.*M_PI;
            v=v0*(rand()%1000)/1000.;
            ps[i].dx=v*cos(f);
            ps[i].dy=v*sin(f);            
        }        
    
    }

}


