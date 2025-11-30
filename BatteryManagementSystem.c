/*
 * Project: F1 ERS Battery Telemetry System
 * Author: Kerem Can KOÇ/NeweyJunior
 * Description: 
 * Simulates the Energy Recovery System (ERS) of an F1 car.
 * - Harvesting: Calculates charge from braking (MGU-K) and engine braking.
 * - Deployment: Calculates discharge during acceleration.
 * - Safety: Prevents battery overcharge (>100%) or deep discharge (<0%).
 * * Date: December 2025
 */

#include <stdio.h>
float reCharge(float,float,float,float);
float spendCharge(float,float);
float battery = 100;

int main(){
    float isBraking,brakeTime,currentSpeed,speedTime,isDischarging,dischargeTime;
    printf("*************************************\n");
    printf("   use charge situation questions\n");
    printf("*************************************\n");
    
    
    printf("is battery used(1-use/another one not used):");
    scanf("%f",&isDischarging);
    
    printf("enter a use time:");
    scanf("%f",&dischargeTime);
    printf("*************************************\n");
    
    spendCharge(isDischarging,dischargeTime);//battery use situation / battery use time
    
    printf("    Recharge situation questions    \n");
    printf("*************************************\n");
    printf("enter a brake situation(1-use/another one not used):");
    scanf("%f",&isBraking);
    
    printf("enter a brake time:");
    scanf("%f",&brakeTime);
    
    printf("enter a speed:");
    scanf("%f",&currentSpeed);
    
    printf("enter a speed time:");
    scanf("%f",&speedTime);
        
    reCharge(isBraking,brakeTime,currentSpeed,speedTime);//brake situation/brake time/speed/speed time
    
    printf("\n BATTERY = %f\n",battery);
    return 0;
}
float reCharge(float brake,float brakeTime,float speed,float speedTime){
    if(brake==1){
        battery=battery+brakeTime*2.5;
    }if(speed<=80 && speed>0){
        battery=battery+speedTime*2;
    }if(battery>100){
        battery=100;
    }else if(battery<0){
        battery=0;
    }
    return battery;
}
float spendCharge(float useCharge, float useTime){
    if(useCharge==1){
        battery=battery-useTime*5;
    }if(battery>100){
        battery=100;
    }else if(battery<0){
        battery=0;
    }
    return battery;
}
