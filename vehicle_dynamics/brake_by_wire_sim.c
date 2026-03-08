#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct car{
	int gearMode;
	short int ersMode;
	float brakingRate;
	float rearBrakeRate;
	float instantaneousSpeed;
}car;

int main(){
	car carSituation;
	srand(time(NULL));

	for(int i = 1; i <= 100; i++){
		carSituation.instantaneousSpeed = rand() % 400;
		printf("Speed: %.2f\n",carSituation.instantaneousSpeed);
		
		if(carSituation.instantaneousSpeed > 380.0 || carSituation.instantaneousSpeed < 0){
			printf("Speed error!\n\n");
			continue;
		}
		
		carSituation.gearMode = rand() % 10;
		printf("Gear mode: %d\n",carSituation.gearMode);
		
		if(carSituation.gearMode > 8 || carSituation.gearMode < 0){
			printf("Gear mode error!\n\n");
			continue;
		}

		carSituation.brakingRate = rand() % 110;
		printf("Braking rate: %.2f\n",carSituation.brakingRate);
		
		if(carSituation.brakingRate > 100){
			printf("Braking rate error!\n\n");
			continue;
		}
		
		if((carSituation.gearMode >= 6) && (carSituation.brakingRate <= 80.25 && carSituation.brakingRate >= 69.75) && (carSituation.instantaneousSpeed >= 275)){
			carSituation.rearBrakeRate = 92.33;
			carSituation.ersMode = 1;
			printf("ERS activated (Because the rear brakes almost locked up)\n");

			carSituation.instantaneousSpeed = rand() % 400;
			printf("After braking speed: %.2f\n",carSituation.instantaneousSpeed);
			
			if(carSituation.instantaneousSpeed > 380.0 || carSituation.instantaneousSpeed < 0){
				printf("After braking speed error!\n\n");
				continue;
			}

			carSituation.gearMode = rand() % 10;
			printf("After braking gear mode: %d\n",carSituation.gearMode);
			
			if(carSituation.gearMode > 8 || carSituation.gearMode < 0){
				printf("After braking gear mode error!\n\n");
				continue;
			}
			
			if((carSituation.instantaneousSpeed < 200.25) && (carSituation.gearMode < 6 && carSituation.gearMode >= 0)){
				carSituation.rearBrakeRate = carSituation.brakingRate;
				carSituation.ersMode = 0;
				printf("ERS deactivated (The brakes have become safe)\n");
			}
			printf("\n");
		}else{
			printf("ERS deactivated\n\n");
		}
	}
	return 0;
}
