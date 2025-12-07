#include <stdio.h>

int battery=100;
float speed;

void showMenu();
void activateMOM();
void MGU_K();
void Radio();
void clutchPedal(int);
int gearUp(int);
int gearDown(int);
void overtakeMode(int);
void X_mode();
void Z_mode();
float pitLane(float);

int main(){
    int process,rpm;
    int gear=1;
    showMenu();
    while(1){
        printf("\n---- INFORMATIONS ----\n");
        printf("speed:");
        scanf("%f",&speed);
        
        printf("rpm:");
        scanf("%d",&rpm);
        printf("---- ------------ ----\n");
        printf("Choose your process:");
        scanf("%d",&process);
    
        switch(process){
            case 0: return 0;
            
            case 1: activateMOM();
                break;
            
            case 2: MGU_K();
                break;
            
            case 3: speed = pitLane(speed);
                    printf("Current pit speed: %.2f",speed);
                break;
            
            case 4: Radio();
                break;
            
            case 5: clutchPedal(rpm);
                break;
            
            case 6: gear = gearUp(gear);
                    printf("new gear: %d",gear);
                break;
            
            case 7: gear = gearDown(gear);
                    printf("new gear: %d",gear);
                break;
            
            case 8: overtakeMode(rpm);
                break;
                
            case 9: X_mode();
                break;
                
            case 10: Z_mode();
                break;
            
        }
    }
    return 0;
}
float pitLane(float speed){
    if(speed > 80.5){
        speed=79.7;
    }
    return speed;
}
void showMenu(){
    printf("---RB22 STEERING WHEEL MENU---\n");
    printf("1-Activate MOM\n");
    printf("2-MGU-K\n");
    printf("3-Pit lane mode\n");
    printf("4-Radio open\n");
    printf("5-Clutch\n");
    printf("6-Gear up\n");
    printf("7-Gear down\n");
    printf("8-Overtake button\n");
    printf("9-X mode\n");
    printf("10-Z mode\n");
}
void activateMOM(){
        battery=battery-battery*0.1;
        if(battery<0){
            battery=0;
        }
        printf("MOM activated. Now your battery level %d percent",battery);
}
void MGU_K(){
    battery=battery+battery*0.1;
    if (battery>100){
        battery=100;
    }
    printf("MGU-K activated. Now your battery level %d percent",battery);
}
void Radio(){
    printf("radio open/close");
}
void clutchPedal(int rpm){
    rpm=rpm+rpm*0.1;
    if(rpm>15000){
        rpm=15000;
    }
    printf("clutch activated. %d rpm",rpm);
}
int gearUp(int gear){
    gear++;
    if(gear>=8){
        gear=8;
    }
    return gear;
}
int gearDown(int gear){
    gear--;
    if(gear<=0){
        gear=1;
    }
    return gear;
}
void overtakeMode(int rpm){
    rpm=rpm+rpm*0.2;
    if(rpm>15000){
        rpm=15000;
    }
    printf("overtake mode activated. %d rpm",rpm);
}
void X_mode(){
    printf("X mode activated, friction has decreased, speed up!");
}
void Z_mode(){
    printf("Z mode activated, pressing force increased!");
}
