#include <stdio.h>
#include <string.h>
int pitSituation(int,int,int);
int main(){
    int pitDecision=pitSituation(11,0,1);//tyre age/ weather situation/ SC situation
    char confirmSituation[50];
    if(pitDecision==1){
        strcpy(confirmSituation,"BOX BOX, BOX NOW!");
    }else{
        strcpy(confirmSituation,"S-STAY OUT, STAY OUT!");
    }
        printf("Should the driver be taken to the pits:\n%s",confirmSituation);
    return 0;    
}      
    int pitSituation(int tyreAge,int rainSituation,int safetyCar){
    int pitConfirm=0;
    if(rainSituation==1){
        pitConfirm=1;
    }else if(tyreAge>25){
        pitConfirm=1;
    }else if(safetyCar==1 && tyreAge>10){
        pitConfirm=1;
    }
 return pitConfirm;
}
