#include <stdio.h>
struct driver{
    float sector1;
    float sector2;
    float sector3;
};

float lapTime(float,float,float);
void timeConverter(float);

int main(){
    struct driver driver1,driver2,driver3;
    float fastestSector1,fastestSector2,fastestSector3;
    printf("please enter a driver 1 sector 1:");
    scanf("%f",&driver1.sector1);
    
    printf("please enter a driver 1 sector 2:");
    scanf("%f",&driver1.sector2);
    
    printf("please enter a driver 1 sector 3:");
    scanf("%f",&driver1.sector3);
    
    printf("\n****************************************************\n");
    
    printf("please enter a driver 2 sector 1:");
    scanf("%f",&driver2.sector1);
    
    printf("please enter a driver 2 sector 2:");
    scanf("%f",&driver2.sector2);
    
    printf("please enter a driver 2 sector 3:");
    scanf("%f",&driver2.sector3);
    
    printf("\n****************************************************\n");
    
    printf("please enter a driver 3 sector 1:");
    scanf("%f",&driver3.sector1);
    
    printf("please enter a driver 3 sector 2:");
    scanf("%f",&driver3.sector2);
    
    printf("please enter a driver 3 sector 3:");
    scanf("%f",&driver3.sector3);

    printf("\n****************************************************\n");
    
    //--------------------Sector 1------------------------------------
    fastestSector1=driver1.sector1;
    if(driver2.sector1<fastestSector1){
        fastestSector1=driver2.sector1;
    }
    if(driver3.sector1<fastestSector1){
        fastestSector1=driver3.sector1;
    }
    
    //--------------------Sector 2------------------------------------
    fastestSector2=driver1.sector2;
    if(driver2.sector2<fastestSector2){
        fastestSector2=driver2.sector2;
    }
    if(driver3.sector2<fastestSector2){
        fastestSector2=driver3.sector2;
    }
    
    //--------------------Sector 3------------------------------------
    fastestSector3=driver1.sector3;
    if(driver2.sector3<fastestSector3){
        fastestSector3=driver2.sector3;
    }
    if(driver3.sector3<fastestSector3){
        fastestSector3=driver3.sector3;
    }
    
    //----------------------------------------------------------------
    printf("\n****************************************************\n");
    printf("\ndriver 1 lap time : ");
    timeConverter(lapTime(driver1.sector1, driver1.sector2, driver1.sector3));
    
    printf("\ndriver 2 lap time : ");
    timeConverter(lapTime(driver2.sector1, driver2.sector2, driver2.sector3));
    
    printf("\ndriver 3 lap time : ");
    timeConverter(lapTime(driver3.sector1, driver3.sector2, driver3.sector3));
    
    printf("\n****************************************************\n");
    printf("\nincredible lap: ");
    timeConverter(lapTime(fastestSector1,fastestSector2,fastestSector3));
    
    return 0;
}

float lapTime(float sector1,float sector2,float sector3){
    float totalTime;
    totalTime = sector1+sector2+sector3 ;
    return totalTime;
}
void timeConverter(float lapTime){
    int minute,second;
    float splitSecond; 
    minute = lapTime / 60;
    second = lapTime - (minute*60);
    splitSecond = lapTime - (minute*60) - second;
    printf("%d.%d.%.0f",minute,second,splitSecond*1000);
}
