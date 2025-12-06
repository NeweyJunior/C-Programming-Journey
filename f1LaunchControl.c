#include <stdio.h>

int antiStallSystem();

int main(){
    int rpm;
    float engineTemp,gasRatio;
    printf("--- RB21 LAUNCH CONTROL SEQUENCE---\n\n");
    printf("[SYSTEM CHECK]\n");
    printf("Enter engine temparature (C):");
    scanf("%f",&engineTemp);
    
    if(engineTemp>120){
        printf(">>ENGINE OVERHEAT! START ABORTED.");
        return 0;
    }
    printf("\n[GRID POSITION]\n");
    printf("5 red lights are ON...\nHold the RPM for optimal launch!\n");
    printf("Enter gas ratio(0-100):");
    scanf("%f",&gasRatio);
    
    if(gasRatio>100 || gasRatio<0){
        printf(">>Such a thing cannot happen.");
        return 0;
    }
    rpm = gasRatio * 150;
    
    printf("\n>>Engine temparature (C): %.1f",engineTemp);
    printf("\n>>Current RPM: %d\n",rpm);
    
    if(rpm<5000){
        rpm = antiStallSystem();
        printf(">> RECOVERY SUCCESSFUL! Current RPM: %d. You are slow but alive!\n", rpm);
    }else if(rpm<10000 && rpm>=5000){
        printf("\nLow rpm! Not optimal!");
    }else if(rpm>12000){
        printf("\nHigh rpm! You skidded!");
    }else if(rpm<=12000 && rpm>=10000){
        printf("\nPerfect take off! Congratulations!");
    }
    return 0;
}
int antiStallSystem(){
    printf("\n!!! WARNING: ANTI-STALL ACTIVE!!!\n");
    printf("The clutch was automatically engaged, the engine is being saved...\n");
    return 5000;
}
