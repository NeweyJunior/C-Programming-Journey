#include <stdio.h>

float calculateLap(float,float,float);

struct driver{
    char name[20];
    char team[20];
    float sectors[3];
};

int main(){
    struct driver driver1;
    int chooseTyre;
    char tyres[3]={'s','m','h'};
    printf("enter team name:");
    scanf("%s",driver1.team);
    printf("enter driver name:");
    scanf("%s",driver1.name);
    printf("\n1-soft\n2-medium\n3-hard\nchoose tyre:");
    scanf("%d",&chooseTyre);
    printf("\nenter sector 1:");
    scanf("%f",&driver1.sectors[0]);
    printf("enter sector 2:");
    scanf("%f",&driver1.sectors[1]);
    printf("enter sector 3:");
    scanf("%f",&driver1.sectors[2]);
    printf("\n%s - (%s) - tyre: %c - lap time: %.2f\n",driver1.name,driver1.team,tyres[chooseTyre-1],calculateLap(driver1.sectors[0],driver1.sectors[1],driver1.sectors[2]));
    
    return 0;
}
float calculateLap(float sector1,float sector2,float sector3){
    float lapTime=sector1+sector2+sector3;
    return lapTime;
}
