extern short int keys[256];
#include"soundutil.cpp"

#define SHIFT 50
#define CONTRL  37
#define ALT   64
#define BACKSPACE 22
#define KEY_R 27
#define KEY_F 41
#define KEY_T 28
#define KEY_G 42
#define KEY_Y 29
#define KEY_H 43
extern double pifColorSpeedr;
extern double pifColorSpeedg;
extern double pifColorSpeedb;
extern int showColorSeq;




void soundKeyboardControll(){
     if(keys[KEY_R]){
        pifColorSpeedr*=1.03;
        
     }
     if(keys[KEY_F]){
        pifColorSpeedr/=1.03;
        
     }
     if(keys[KEY_T]){
        pifColorSpeedg*=1.03;
        
     }
     if(keys[KEY_G]){
        pifColorSpeedg/=1.03;
        
     }
     if(keys[KEY_Y]){
        pifColorSpeedb*=1.03;
        
     }
     if(keys[KEY_H]){
        pifColorSpeedb/=1.03;
        
     }



    if(keys[66]==2){
        if(!keys[CONTRL]){
            colorSeqVar++;
            colorSeqVar=colorSeqVar%4;
            colorSeq2BufReady=0;
        }else{
            showColorSeq=!showColorSeq;
        
        }
    }
    
    if(keys[49]==2){
            addMelodyTorithm++;
            addMelodyTorithm=addMelodyTorithm&1;
    }
    if(keys[20]==2){
        if(keys[CONTRL] && keys[SHIFT]){
            minColorSeqFreq=minColorSeqFreq/1.1;
    
        }else
        if(keys[CONTRL]){
            MaxDanceFreq=MaxDanceFreq/2;
        }else if(keys[SHIFT]){
             amplifierKoefHighValue=amplifierKoefHighValue*1.1;
        }else if(keys[ALT]){
             amplifierKoefLowValue=amplifierKoefLowValue*1.1;
        }
    }
    if(keys[21]==2){
        if(keys[CONTRL] && keys[SHIFT]){
            minColorSeqFreq=minColorSeqFreq*1.1;
    
        }else
        if(keys[CONTRL]){
             MaxDanceFreq=MaxDanceFreq*2;
        }else if(keys[SHIFT]){
             amplifierKoefHighValue=amplifierKoefHighValue/1.1;
        }else if(keys[ALT]){
             amplifierKoefLowValue=amplifierKoefLowValue/1.1;
        }

    }
    if(keys[BACKSPACE]==2){
        drawAddaptiveVolumeFlag=!drawAddaptiveVolumeFlag;
       // printf("drawAddaptiveVolumeFlag changed %d\n",drawAddaptiveVolumeFlag);
    }
    

}

