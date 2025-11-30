#include <stdio.h>
//************************************
int min(int,int);
int max(int,int);
int square(int);
int cube(int);
int absolute(int);
void menu();
//************************************
int main(){
    int sonuc;
    int num1,num2;
    menu();
    int process;
    printf("*****************************\n");
    printf("choose your process:");
    scanf("%d",&process);
    printf("*****************************\n");
    switch (process){
        case 1: printf("enter the numbers to compare:");
                scanf("%d %d",&num1,&num2);
                printf("*****************************\n");
                sonuc=min(num1,num2);
                printf("\nResult:%d",sonuc);
            break;
        case 2: printf("enter the numbers to compare:");
                scanf("%d %d",&num1,&num2);
                printf("*****************************\n");
                sonuc=max(num1,num2);
                printf("\nResult:%d",sonuc);
            break;
        case 3: printf("enter the number to square process:");
                scanf("%d",&num1);
                printf("*****************************\n");
                sonuc=square(num1);
                printf("\nResult:%d",sonuc);
            break;
        case 4: printf("enter the number to cube process:");
                scanf("%d",&num1);
                printf("*****************************\n");
                sonuc=cube(num1);
                printf("\nResult:%d",sonuc);
            break;
        case 5: printf("enter the number to absolute process:");
                scanf("%d",&num1);
                printf("*****************************\n");
                sonuc=absolute(num1);
                printf("\nResult:%d",sonuc);
            break;
        default: printf("Please select a valid process.");
            break;
    }
    return 0;
}
void menu(){
    printf("*****************************\n");
    printf("*---   CALCULATOR MENU   ---*\n");
    printf("*****************************\n");
    printf("1-min\n");
    printf("2-max\n");
    printf("3-square\n");
    printf("4-cube\n");
    printf("5-absolute\n");
}

int min(int x, int y){
    if(x<y)
    return x;
    else
    return y;
}
int max(int x, int y){
    if(x>y)
    return x;
    else
    return y;
}
int square(int x){
    return x*x;
}
int cube(int x){
    return x*x*x;
}
int absolute(int x){
    if(x<0)
    return -x;
    else
    return x;
}
