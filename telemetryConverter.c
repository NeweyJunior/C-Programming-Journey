#include <stdio.h>
float convertToMph(float);
float convertToFahrenheit(float);
float convertToLbs(float);
void menu();

int main(){
    int process;
    float result,num1;
    menu();
    printf("choose your process:");
    scanf("%d",&process);
    printf("****************************\n");
    switch(process){
        case 1: printf("enter a kph:");
                scanf("%f",&num1);
                printf("****************************\n");
                result=convertToMph(num1);
                printf("%f KPH = %f MPH",num1,result);
                printf("\n****************************\n");
            break;
        case 2: printf("enter a celcius:");
                scanf("%f",&num1);
                printf("****************************\n");
                result=convertToFahrenheit(num1);
                printf("%f C = %f F",num1,result);
                printf("\n****************************\n");
            break;
        case 3: printf("enter a kg:");
                scanf("%f",&num1);
                printf("****************************\n");
                result=convertToLbs(num1);
                printf("%f KG = %f LBS",num1,result);
                printf("\n****************************\n");
            break;
        default:printf("please enter a valid process.");
                printf("\n****************************\n");
            break;
    }
    return 0;
}
float convertToMph(float kph){
    kph*=0.621371;
    return kph;
}
float convertToFahrenheit(float celcius){
    celcius=(celcius*9/5)+32;
    return celcius;
}
float convertToLbs(float kg){
    kg*=2.20462;
    return kg;
}
void menu(){
    printf("****************************\n");
    printf("******* CONVERT MENU *******\n");
    printf("****************************\n");
    printf("1) KPH->MPH\n");
    printf("2) CELCIUS->FAHRENHEIT\n");
    printf("3) KG->LBS\n");
    printf("****************************\n");
}
