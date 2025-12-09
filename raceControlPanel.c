#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void showMenu();
void controlEngine();
void calculateFuel(float,float);
void tyreControl();
void calculateDownforce(float);

int main(){
    int process;
    float lapTime,speed,consumption;
    srand(time(NULL));
    while (1){
        showMenu();
        printf("Please select a process:");
        scanf("%d",&process);
        printf("=========================================\n");
        
        switch(process){
            case 0: 
                return 0;
            case 1: controlEngine();
                    printf("=========================================\n");
                break;
            case 2: printf("Please enter a lap time:"); 
                    scanf("%f",&lapTime);
                    printf("Please enter a consumption:");
                    scanf("%f",&consumption);
                    calculateFuel(lapTime,consumption);
                    printf("=========================================\n");
                break;
            case 3: tyreControl();   
                    printf("=========================================\n");
                break;
            case 4: printf("Please enter a speed(km/h):");
                    scanf("%f",&speed);
                    calculateDownforce(speed);
                    printf("=========================================\n");
                break;
            default: 
                continue;
        }
    }
    
    return 0;
}
void showMenu(){
    printf("\n===== F1 TELEMETRY AND CONTROL PANEL ====\n");
    printf("1-Engine Temparature Test\n");
    printf("2-Calculate Fuel\n");
    printf("3-Tyre Pressure Control\n");
    printf("4-Aerodynamic Calculus\n");
    printf("0-Exit\n");
    printf("=========================================\n");
}
void controlEngine(){
    int temparature=rand()%(131-80+1)+80;
    if(temparature>110){
        printf("ALARM: ENGINE OVERHEAT (%d)! ENTER THE PIT!\n",temparature);
    }else if(temparature<=110){
        printf("Engine temparature is normal (%d).\n",temparature);
    }   
}
void calculateFuel(float lapTime,float consumption){
    printf("Fuel: %.2f\n",(float)lapTime*consumption*1.05);
}
void tyreControl(){
    
    for(int i=1; i<=4; i++){
        int tyrePressure=rand()%(35-18+1)+18;
        if(tyrePressure<22){
            printf("Tyre %d: RISK OF EXPLOSION! (%d PSI)\n",i,tyrePressure);
        }else if(tyrePressure>=22){
            printf("Tyre %d: OK (%d PSI)\n",i,tyrePressure);
        }
    }
}
void calculateDownforce(float speed){
    float force = (0.5)*(pow(speed,2));
    printf("Downforce: %.2f\n",force);
}
