#include <stdio.h>

int main(){
    double lapTime=0;
    double fastestLap,averageSpeed,length,allLapSpeeds=0;
    int fastestLapName,lapNumber;
    printf("Enter a number of laps:");
    scanf("%d",&lapNumber);
    printf("Enter a length of track (m):");
    scanf("%lf",&length);
    printf("===============================================\n");
    double speedPerLap[lapNumber],telemetry[lapNumber][3],lapTimes[lapNumber];
    
    for(int i=0; i<lapNumber; i++){//lap
        for(int j=0; j<3; j++){ //sector
            printf("enter lap %d a sector %d time:",i+1,j+1);
            scanf("%lf",&telemetry[i][j]);
            lapTime+=telemetry[i][j];
        }
        speedPerLap[i]=(float)length/lapTime*(3.6);
        printf("===============================================\n");
        printf("%d. lap time : %.2lf // Average lap speed: %.2f(km/h)\n",i+1,lapTime,speedPerLap[i]);
        printf("===============================================\n");
        lapTimes[i]=lapTime;
        lapTime=0;
    }
    fastestLap=lapTimes[0];
    for(int i=0; i<lapNumber; i++){
        if(lapTimes[i]<=fastestLap){
            fastestLap=lapTimes[i];
            fastestLapName=i+1;
        }
    }
    for(int i=0; i<lapNumber;i++){
        allLapSpeeds+=speedPerLap[i];
    }
    averageSpeed=(float)allLapSpeeds/lapNumber;
    printf("****************** RACE DATA ******************\n");
    printf("Fastest lap was Lap %d with time: %.2lf(second)\n",fastestLapName,fastestLap);
    printf("Average speed for race: %.2lf(km/h)\n",averageSpeed);
    printf("***********************************************\n");
    return 0;
}
