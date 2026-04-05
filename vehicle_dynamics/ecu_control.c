#include <stdio.h>
#define LED_NUMBER 8

typedef struct ECU{
    int rpm; // Engine speed, integer, max 15000
    int gear; // The current gears are 1-8.
    float brakePressure; // Brake pedal depress percentage, 0-100
    float gapFront; // The time difference between your vehicle and the vehicle in front is given in seconds,float
    int drsZone; // Is the car in the DRS zone of the track? 1 = Yes, 0 = No
}ECU;

void gearData(int* RPM);
void drsDecision(ECU* carData);

int main(){
    ECU rb22Data = {};

    while(1){
        printf("======================================================\n");
        printf("Enter RPM: ");
        scanf("%d",&rb22Data.rpm);

        if(rb22Data.rpm < 0 || rb22Data.rpm > 15000){
            printf("False data!\n");
            while(getchar() != '\n');
            continue;
        }

        printf("Enter gear: ");
        scanf("%d",&rb22Data.gear);

        if(rb22Data.gear < 1 || rb22Data.gear > 8){
            printf("False data!\n");
            while(getchar() != '\n');
            continue;
        }

        printf("Enter brake pressure: ");
        scanf("%f",&rb22Data.brakePressure);

        if(rb22Data.brakePressure < 0.0 || rb22Data.brakePressure > 100.0){
            printf("False data!\n");
            while(getchar() != '\n');
            continue;
        }

        printf("Enter gap for front: ");
        scanf("%f",&rb22Data.gapFront);

        if(rb22Data.gapFront < 0.0){
            printf("False data!\n");
            while(getchar() != '\n');
            continue;
        }

        printf("Enter drs zone situation (1-yes / 0-no): ");
        scanf("%d",&rb22Data.drsZone);

        if(rb22Data.drsZone != 1 && rb22Data.drsZone != 0){
            printf("False data!\n");
            while(getchar() != '\n');
            continue;
        }
        printf("------------------------------\n");
        gearData(&rb22Data.rpm);
        printf("------------------------------\n");
        drsDecision(&rb22Data);
        printf("======================================================\n");
    }


    return 0;
}
void gearData(int* RPM){
    int gearLed = 00000000;
    int gearLedArray[8];
    int activeLed;
    for(int i = 0; i < 8; i++){
        gearLedArray[i] = 0;
    }

    if(*RPM >= 0 && *RPM < 10500){
        activeLed = 0;
    }else if(10500 <= *RPM && *RPM < 11500){
        activeLed = 2;
    }else if(11500 <= *RPM && *RPM < 12200){
        activeLed = 4;
    }else if(12200 <= *RPM && *RPM < 12500){
        activeLed = 6;
    }else if(*RPM >= 12500){
        activeLed = 8;
    }else{
        printf("False data!\n");
    }
    for (int i = 0; i < activeLed; i++) {
            gearLed |= (1 << i);
        }

        for(int i = 0; i < activeLed; i++){
            gearLedArray[i] = 1;
        }

        printf("Gear Situation: ");

        for(int i = 0; i < LED_NUMBER; i++){
            printf("%d",gearLedArray[i]);
        }
        printf("\n");

        for(int i = 0; i < activeLed; i++){
            printf("#");
        }

        for(int j = 0; j < LED_NUMBER - activeLed; j++){
            printf("_");
        }
        printf("\n");
        
}

void drsDecision(ECU* carData){
    if(carData->drsZone == 1 && carData->brakePressure == 0 && carData->gapFront < 1.0){
        printf("DRS open;\n");
    }else{
        printf("DRS close.\n");
    }
}