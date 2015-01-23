#ifndef LIFEMOD
#define LIFEMOD
struct lifeField{
    int w,h,fsize;
    char*f1,*f2;
    int hashstates[64];
    int hashstateN;
}lifeMaps[30];

char lifenei[1024];
int lifedx[8]={-1,0,1,1,1,0,-1,-1};
int lifedy[8]={1,1,1,0,-1,-1,-1,0};
//    int hashstates[64];
//    int hashstateN;

int calcHashState(struct lifeField*lf){
    //hashstates[64]
    int i,j,r;
    r=0;
    for(i=0;i<lf->w;i++)
        for(j=0;j<lf->h;j++){
            r+=lf->f1[i+j*lf->w]*(i*3+j*5);
        }
    return r;
}
void stepLife(struct lifeField*lf){
    int i,j,k,ij;
    char*t;
    if(lf->w*lf->h>1024||lf->w==0||lf->h==0||lf->f1==NULL||lf->f2==NULL)
        return;
    for(i=lf->w*lf->h-1;i>=0;i--)
        lifenei[i]=0;
    for(i=0;i<lf->w;i++)
        for(j=0;j<lf->h;j++){
            ij=i+j*lf->w;
            for(k=0;k<8;k++){
                lifenei[ij]+=lf->f1[((i+lifedx[k]+lf->w)%lf->w)+((j+lifedy[k]+lf->h)%lf->h)*lf->w];    
            }
            lf->f2[ij]=( lf->f1[ij]&&lifenei[ij]==2 || lifenei[ij]==3);
        }
   t=lf->f1;
   lf->f1=lf->f2;
   lf->f2=t;
//    int hashstates[64];
//    int hashstateN;
    lf->hashstateN++;
    lf->hashstateN%=64;
    lf->hashstates[lf->hashstateN]=calcHashState(lf);
    int rep=0;
    for(i=0;i<64;i++)
//        for(j=0;j<i;j++){
            if(lf->hashstates[i]==lf->hashstates[lf->hashstateN] && i!=lf->hashstateN){
                rep=1;
            }
  //      }
    if(rep){
        i=rand()%lf->w;
        j=rand()%lf->h;
        if(rand()%2){
            lf->f1[j+j*lf->w]=1;
            lf->f1[(j+1)%lf->w+j*lf->w]=1;
            lf->f1[(j+2)%lf->w+j*lf->w]=1;
            lf->f1[(j+0)%lf->w+((j+1)%lf->h)*lf->w]=1;
            lf->f1[(j+1)%lf->w+((j+2)%lf->h)*lf->w]=1;
        }else{
            lf->f1[(j+2)%lf->w+((j+2)%lf->h)*lf->w]=1;
            lf->f1[(j+1)%lf->w+((j+2)%lf->h)*lf->w]=1;
            lf->f1[(j+0)%lf->w+((j+2)%lf->h)*lf->w]=1;
            lf->f1[(j+2)%lf->w+((j+1)%lf->h)*lf->w]=1;
            lf->f1[(j+1)%lf->w+((j+0)%lf->h)*lf->w]=1;
        
        
        }
    }
    

}

void initLife(struct lifeField*lf,int w,int h){
    if(lf->fsize<w*h){
        if(lf->fsize!=0&&lf->f1!=NULL){
            free(lf->f1);
        }
        if(lf->fsize!=0&&lf->f2!=NULL){
            free(lf->f2);
        }
        if(w*h!=0){
            lf->f1=(char*)malloc(w*h*sizeof(char));
            lf->f2=(char*)malloc(w*h*sizeof(char));
        }
        lf->w=w;
        lf->h=h;
        lf->fsize=w*h;
    }else{
        lf->w=w;
        lf->h=h;
    }

}
void randomLife(struct lifeField*lf,int w,int h){
    int i;
    initLife(lf,w,h);
    for(i=w*h-1;i>=0;i--){
        lf->f1[i]=rand()%2;
        lf->f2[i]=0;
    }

}

int  life2arr(struct lifeField*lf,int dw,double*p){
    int i,j,w,t;
    double v;
    if(dw<1)
        return 0;
    v=0;
    t=0;
    for(i=0;i<lf->w;i++,w++){
        if(w>=dw){
            //fprintf(stderr,"%d ",v);

            p[t]=v;
            t++;
            v=0;
        }
        for(j=0;j<lf->h;j++){
            v+=(j+1)/3.*lf->f1[i+j*lf->w];
        }
    
    }
          //  fprintf(stderr,"\n");

    return t;
}

void monitorLife(struct lifeField*lf){
    int i,j,k,ij;
    char*t;
    if(lf->w*lf->h>1024||lf->w==0||lf->h==0||lf->f1==NULL||lf->f2==NULL)
        return;
   if(getOpt("monitorLifeShow")<0.5)
    return;
   setOpt("monitorLife",0,lf->w);
   setOpt("monitorLife",1,lf->h);
    for(i=0;i<lf->w;i++)
        for(j=0;j<lf->h;j++){
            ij=i+j*lf->w;
            setOpt("monitorLife",2+ij,lf->f1[ij]);
        }
}


#define HLIFE 16
#define WLIFE 16
double lifestep=0;
void calcLife(){
    lifestep+=getOpt("lifeStep");
    if(lifestep>1){
        lifestep-=1;
        if(getOpt("lifeRand")>0.5){
            setOpt("lifeRand",0);
            randomLife(lifeMaps,WLIFE,HLIFE);    
        }
        if(lifeMaps->w*lifeMaps->h==0){
            randomLife(lifeMaps,WLIFE,HLIFE);    
        }
        stepLife(lifeMaps);
        monitorLife(lifeMaps);   
    }
}
#endif