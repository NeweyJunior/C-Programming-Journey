#include <stdio.h>
#include <string.h>

//------- CONSTANTS -------
#define HIGH_STRESS_COEFFICIENT 0.80
#define STRESS_FACTOR_COEFFICIENT 0.11
#define DEGREE_DIFFERENT_COEFFICIENT 0.0002//0.01
#define WEIGHT_PENALTY_COEFFICIENT 0.00015
#define SOFT_TIME_COEFFICIENT 0.995
#define MEDIUM_TIME_COEFFICIENT 1.00
#define HARD_TIME_COEFFICIENT 1.005
#define AVG_FUEL_COEFFICIENT 0.03
#define SOFT_TYRE_PENALTY 0.75

//-------------------------

typedef struct {
    char name[100];
    float length;
    float temperature;
    float referenceTime;
    float pitWay;
    int stressLevel;
    float trackFuelCoefficient;
    int totalLaps;
} Track;

Track allTracks[24] = {
	{"Australian GP (Albert Park)", 5.278, 24.0, 80.0, 21.0, 3, 1.65, 58},
    {"Chinese GP", 5.451, 22.0, 98.0, 23.0, 4, 1.70, 56},
    {"Japanese GP(Suzuka)", 5.807, 24.0, 92.0, 22.5, 5, 1.75, 53},
    {"Bahrain GP", 5.412, 26.0, 92.0, 23.0, 5, 1.70, 57},
    {"Saudi Arabian GP", 6.174, 29.0, 89.0, 21.0, 2, 1.75, 50},
    {"Miami GP", 5.412, 42.0, 90.0, 20.0, 3, 1.60, 57},
    {"Canadian GP", 4.361, 25.0, 74.0, 18.0, 2, 1.50, 70},
    {"Monaco GP", 3.337, 35.0, 73.0, 19.0, 1, 1.15, 78},
    {"Spanish GP", 4.657, 38.0, 78.0, 22.0, 5, 1.65, 66},
    {"Austrian GP", 4.318, 28.0, 68.0, 20.0, 3, 1.45, 71},
    {"British GP", 5.891, 20.0, 88.0, 24.0, 5, 1.75, 52},
    {"Belgian GP", 7.004, 18.0, 106.0, 22.0, 5, 2.35, 44},
    {"Hungarian GP", 4.381, 45.0, 78.0, 20.0, 4, 1.50, 70},
    {"Dutch GP", 4.259, 22.0, 73.0, 21.0, 4, 1.50, 72},
    {"Italian GP", 5.793, 30.0, 81.0, 24.0, 2, 1.80, 53},
    {"Madrid GP", 5.474, 32.0, 88.0, 20.0, 3, 1.60, 56},
    {"Azerbaijan GP", 6.003, 26.0, 103.0, 20.0, 3, 1.80, 51},
    {"Singapore GP", 4.940, 30.0, 98.0, 28.0, 4, 1.90, 62},
    {"United States GP", 5.513, 28.0, 96.0, 22.0, 4, 1.70, 56},
    {"Mexico City GP", 4.304, 24.0, 80.0, 22.0, 3, 1.40, 71},
    {"Sao Paulo GP", 4.309, 35.0, 72.0, 21.0, 3, 1.50, 71},
    {"Las Vegas GP", 6.201, 10.0, 94.0, 20.0, 2, 1.90, 50},
    {"Qatar GP", 5.419, 27.0, 83.0, 24.0, 5, 1.80, 57},
    {"Abu Dhabi GP", 5.281, 25.0, 86.0, 22.0, 3, 1.70, 58}
};

//--------global variables--------
float c1_coefficient = 1.60;
float c2_coefficient = 1.45;
float c3_coefficient = 0.95;
float c4_coefficient = 0.70;
float c5_coefficient = 0.50;
float c6_coefficient = 0.30;
float originalCarWeight = 798.0;
//--------------------------------

//------------functions-----------------
int calculateTyreLife(float, int, float, int, float, Track);
void calculateBestStrategy(int, float);
void menu();
void smallMenu();
float calculate_1Stop(Track , int, int, float);
float calculate_2Stop(Track , int, int, int, float);
//--------------------------------------

int main() {
    menu();
    int chooseTrack, tyre, actionType, i = 1;
    float startFuel;
    
    while (i == 1) { 
        printf("1-Calculate tyre life || 2- Calculate best strategy || 3- Exit\n");
        printf("===========================================================================================\n");
        printf("What action do you want to take:");
        scanf("%d", &actionType);
        
        if (actionType == 3) {
            printf("Exiting simulator... See you on track!\n");
            return 0;
        }
        
        if (actionType == 1) {
            printf("-------------------------------------------------------------------------------------------\n");
            printf("Please select a track:");
            scanf("%d", &chooseTrack);
            printf("-------------------------------------------------------------------------------------------\n");
            
            if (chooseTrack > 24 || chooseTrack < 1) {
                printf("Please enter a valid track.\n");
                printf("-------------------------------------------------------------------------------------------\n");
                continue;
            }
            
            Track selectedTrack = allTracks[chooseTrack - 1];
            printf("SELECTED TRACK: %s\n", selectedTrack.name);
            printf("Temp: %.2f C | Length: %.3f km | Stress Level: %d | Number of laps: %d\n", 
                   selectedTrack.temperature, selectedTrack.length, selectedTrack.stressLevel, selectedTrack.totalLaps);
            printf("-------------------------------------------------------------------------------------------\n");
            
            printf("Enter starting fuel load (kg):");
            scanf("%f", &startFuel);
            printf("-------------------------------------------------------------------------------------------\n");
            
            printf("1) c1 | 2) c2 | 3) c3 | 4) c4 | 5) c5 | 6) c6 |\n");
            printf("Select tyre compound (1-6):");
            scanf("%d", &tyre);
            printf("===========================================================================================\n");
            
            int life = calculateTyreLife(selectedTrack.temperature, tyre, selectedTrack.length, selectedTrack.stressLevel, startFuel, selectedTrack);
            printf("%d lap tyre life\n", life);
            printf("===========================================================================================\n");
            
        } else if (actionType == 2) {
           printf("-------------------------------------------------------------------------------------------\n");
            printf("Please select a track:");
            scanf("%d", &chooseTrack);
            printf("-------------------------------------------------------------------------------------------\n");
            
            if (chooseTrack > 24 || chooseTrack < 1) {
                printf("Please enter a valid track.\n");
                printf("-------------------------------------------------------------------------------------------\n");
                continue;
            }
            
            Track selectedTrack = allTracks[chooseTrack - 1];
            printf("SELECTED TRACK: %s\n", selectedTrack.name);
            printf("Temp: %.2f C | Length: %.3f km | Stress Level: %d | Number of laps: %d\n", 
                   selectedTrack.temperature, selectedTrack.length, selectedTrack.stressLevel, selectedTrack.totalLaps);
            printf("-------------------------------------------------------------------------------------------\n");
            
            printf("Enter starting fuel load (kg):");
            scanf("%f", &startFuel);
            printf("-------------------------------------------------------------------------------------------\n");
            
            calculateBestStrategy(chooseTrack,startFuel);
        } else {
            printf("===========================================================================================\n");
            printf("Please select a valid process.\n");
            printf("===========================================================================================\n");
            continue;
        }
        smallMenu();
    }
    return 0;
}

int calculateTyreLife(float trackDegree, int tyreType, float trackLength, int trackStress, float startFuel, Track t) {
    float selectedCoefficient;

    switch (tyreType) {
        case 1: selectedCoefficient = c1_coefficient; break;
        case 2: selectedCoefficient = c2_coefficient; break;
        case 3: selectedCoefficient = c3_coefficient; break;
        case 4: selectedCoefficient = c4_coefficient; break;
        case 5: selectedCoefficient = c5_coefficient; break;
        case 6: selectedCoefficient = c6_coefficient; break;
        default: selectedCoefficient = c3_coefficient; break;
    }

    float idealKm = 250.0;
    
    if(t.stressLevel == 5){
        selectedCoefficient *= HIGH_STRESS_COEFFICIENT;
    }
    
    if(t.length > 5.0 && (tyreType == 5 || tyreType == 6)){
        selectedCoefficient *= SOFT_TYRE_PENALTY;
    }
    
    float totalDistance = idealKm * selectedCoefficient;

    float referenceDegree = 20.0;
    float degreeDifference = trackDegree - referenceDegree;
    float degreeEffect = 1.0 - (degreeDifference * DEGREE_DIFFERENT_COEFFICIENT);

    float stressFactor = 1 - ((trackStress - 1) * STRESS_FACTOR_COEFFICIENT);

    float grainingPenalty = 1.0;

    if (trackDegree <= 25.0 && trackStress <= 3) {
        grainingPenalty = 0.94;
    }

    if (degreeEffect <= 0.0) {
        printf("!!! CRITICAL ERROR !!! Tire burst due to excessive heat!\n");
        return 0;
    }
    
    float startWeight = startFuel + originalCarWeight; 
    float lastWeight = startWeight;

    for (int i = 0; i < t.totalLaps; i++) {
        lastWeight -= t.trackFuelCoefficient;
    }
    
    float averageWeight = (startWeight + lastWeight - (2 * originalCarWeight)) / 2;
    float weightPenalty = 1 - (averageWeight * WEIGHT_PENALTY_COEFFICIENT);

    float realDistance = totalDistance * degreeEffect * stressFactor * grainingPenalty * weightPenalty;

    int howManyLaps = (int)realDistance / trackLength;

    return howManyLaps;
}

void calculateBestStrategy(int trackID, float startFuel){
    Track t = allTracks[trackID - 1];
    
    float strategies[22] = {
        // --- 1 STOP ---
        calculate_1Stop(t, 5, 3, startFuel), // [0] S-M
        calculate_1Stop(t, 5, 1, startFuel), // [1] S-H
        calculate_1Stop(t, 3, 5, startFuel), // [2] M-S
        calculate_1Stop(t, 3, 1, startFuel), // [3] M-H
        calculate_1Stop(t, 1, 5, startFuel), // [4] H-S
        calculate_1Stop(t, 1, 3, startFuel), // [5] H-M

        // --- 2 STOP (SOFT START) ---
        calculate_2Stop(t, 5, 5, 3, startFuel), // [6] S-S-M
        calculate_2Stop(t, 5, 5, 1, startFuel), // [7] S-S-H
        calculate_2Stop(t, 5, 3, 5, startFuel), // [8] S-M-S
        calculate_2Stop(t, 5, 3, 3, startFuel), // [9] S-M-M
        calculate_2Stop(t, 5, 3, 1, startFuel), // [10] S-M-H
        calculate_2Stop(t, 5, 1, 5, startFuel), // [11] S-H-S
        calculate_2Stop(t, 5, 1, 3, startFuel), // [12] S-H-M
        calculate_2Stop(t, 5, 1, 1, startFuel), // [13] S-H-H

        // --- 2 STOP (MEDIUM START) ---
        calculate_2Stop(t, 3, 5, 5, startFuel), // [14] M-S-S
        calculate_2Stop(t, 3, 5, 3, startFuel), // [15] M-S-M
        calculate_2Stop(t, 3, 5, 1, startFuel), // [16] M-S-H
        calculate_2Stop(t, 3, 3, 5, startFuel), // [17] M-M-S
        calculate_2Stop(t, 3, 3, 1, startFuel), // [18] M-M-H
        calculate_2Stop(t, 3, 1, 5, startFuel), // [19] M-H-S

        // --- 2 STOP (HARD START) ---
        calculate_2Stop(t, 1, 5, 5, startFuel), // [20] H-S-S
        calculate_2Stop(t, 1, 5, 3, startFuel)  // [21] H-S-M
    };
    
    // --- Strategy Names ---
    char *strategyNames[22] = {
        "Soft-Medium", "Soft-Hard", "Medium-Soft", "Medium-Hard", "Hard-Soft", "Hard-Medium",
        "S-S-M", "S-S-H", "S-M-S", "S-M-M", "S-M-H", "S-H-S", "S-H-M", "S-H-H",
        "M-S-S", "M-S-M", "M-S-H", "M-M-S", "M-M-H", "M-H-S",
        "H-S-S", "H-S-M"
    };
    // --- Comparsion Process ---
    float smallest = 0;
    int bestIndex = 0;
    for(int i = 0; i < 22; i++){
        if(i == 0) smallest = strategies[0];
        else if(strategies[i] < smallest){
            smallest = strategies[i];
            bestIndex = i;
        }
    }
    int totalSeconds = (int) smallest;
    printf("The winner strategy is : %s !\n",* (strategyNames + bestIndex));
    printf("Estimated total race time : %d min. %d sec.\n",totalSeconds / 60, totalSeconds % 60);
    printf("-------------------------------------------------------------------------------------------\n");

    
    
}
float calculate_1Stop(Track t, int tyre1, int tyre2, float startFuel){
    
    //---- stint 1 ----
    int laps1 = calculateTyreLife(t.temperature, tyre1, t.length, t.stressLevel, startFuel, t);
    
    if (laps1 >= t.totalLaps) return 999999.0; // Because if the potential lap race passes, a pit stop is not necessary.
    
    float speed1;
    if (tyre1 >= 4) speed1 = t.referenceTime * SOFT_TIME_COEFFICIENT; // Soft
    else if (tyre1 == 3) speed1 = t.referenceTime * MEDIUM_TIME_COEFFICIENT; // Medium
    else speed1 = t.referenceTime * HARD_TIME_COEFFICIENT; // Hard
    
    float fuelBurn1 = laps1 * t.trackFuelCoefficient;
    float avgFuel1 = startFuel - (fuelBurn1 / 2);
    
    float time1 = (laps1 * speed1) + (laps1) * (avgFuel1 * AVG_FUEL_COEFFICIENT);
    
    //---- stint 2 ----
    int lapsRemaining = t.totalLaps - laps1;
    float currentFuel = startFuel - fuelBurn1;
    
    int laps2 = calculateTyreLife(t.temperature, tyre2, t.length, t.stressLevel, currentFuel, t);
    
    if(laps2<lapsRemaining) return 999999.0; // tyre is not enough
    
    float speed2;
    if (tyre2 == 5) speed2 = t.referenceTime * SOFT_TIME_COEFFICIENT;
    else if (tyre2 == 3) speed2 = t.referenceTime * MEDIUM_TIME_COEFFICIENT;
    else speed2 = t.referenceTime * HARD_TIME_COEFFICIENT;
    
    float fuelBurn2 = lapsRemaining * t.trackFuelCoefficient;
    float avgFuel2 = currentFuel - (fuelBurn2 / 2);
    
    float time2 = (lapsRemaining * speed2) + (lapsRemaining) * (avgFuel2 * AVG_FUEL_COEFFICIENT);
    
    return time1 + t.pitWay + time2;
}
float calculate_2Stop(Track t, int tyre1, int tyre2, int tyre3, float startFuel){
    //---- stint 1 ----
    int laps1 = calculateTyreLife(t.temperature,tyre1,t.length,t.stressLevel, startFuel, t);
    
    float speed1;
    if(tyre1 == 5) speed1 = t.referenceTime * SOFT_TIME_COEFFICIENT; //soft
    else if(tyre1 == 3) speed1= t.referenceTime * MEDIUM_TIME_COEFFICIENT; //medium
    else speed1 = t.referenceTime * HARD_TIME_COEFFICIENT; //hard
    
    float fuelBurn1 = t.trackFuelCoefficient * laps1;
    float avgFuel1 = startFuel - (fuelBurn1/2);
    
    float time1 = (laps1 * speed1) + (laps1) * (avgFuel1 * AVG_FUEL_COEFFICIENT);
    
    //---- stint 2 ----
    int lapsRemaining = t.totalLaps - laps1;
    float fuelAtPit1 = startFuel - fuelBurn1;
    
    int laps2 = calculateTyreLife(t.temperature, tyre2, t.length, t.stressLevel, fuelAtPit1, t);
    
    float speed2;
    if (tyre2 == 5) speed2 = t.referenceTime * SOFT_TIME_COEFFICIENT; //soft 
    else if (tyre2 == 3) speed2 = t.referenceTime * MEDIUM_TIME_COEFFICIENT; //medium
    else speed2 = t.referenceTime * HARD_TIME_COEFFICIENT; //hard
    
    float fuelBurn2 = laps2 * t.trackFuelCoefficient;
    float avgFuel2 = fuelAtPit1 - (fuelBurn2 / 2);
    
    float time2 = (laps2 * speed2) + (laps2) * (avgFuel2 * AVG_FUEL_COEFFICIENT);
    
    //---- stint 3 ----
    int lastStint = t.totalLaps - laps1 - laps2;
    
	if (lastStint <= 0) return 999999.0; // To prevent the time from taking a negative value and therefore choosing a multiple pit stop strategy.
    
    float lastFuel = fuelAtPit1 - fuelBurn2;
    
    int laps3 = calculateTyreLife(t.temperature, tyre3, t.length, t.stressLevel, lastFuel, t);
    
    if(lastStint > laps3) return 999999.0; // tyre is not enough
    
    float speed3;
   	if(tyre3 == 5) speed3 = t.referenceTime * SOFT_TIME_COEFFICIENT; // soft
   	else if(tyre3 == 3) speed3 = t.referenceTime * MEDIUM_TIME_COEFFICIENT; //medium
   	else speed3 = t.referenceTime * HARD_TIME_COEFFICIENT; //hard
    
    float fuelBurn3 = lastStint * t.trackFuelCoefficient;
    float avgFuel3 = lastFuel - (fuelBurn3/2);
    
    float time3 = (lastStint * speed3) + (lastStint) * (avgFuel3 * AVG_FUEL_COEFFICIENT);

    return time1 + time2 + time3 + (2 * t.pitWay); 
}

void menu() {
    printf("===========================================================================================\n");
    printf("-------                       STRATEGY CALCULATE SIMULATOR                          -------\n");
    printf("===========================================================================================\n");
    printf("WELCOME TO THE STRATEGY CALCULATION SIMULATOR V1.0! THE PURPOSE OF THIS SIMULATOR IS\nTO FIND THE STRATEGY THAT WILL FINISH THE RACE IN THE FASTEST WAY.\n");
    printf("===========================================================================================\n");
    printf("1-AUSTRALIA GP || 2-CHINESE GP || 3-JAPANESE GP || 4-BAHRAIN GP || 5-SAUDI ARABIAN GP ||\n");
    printf("6-MIAMI GP || 7-CANADA GP || 8-MONACOGP || 9-SPANISH GP || 10-AUSTRIAN GP ||\n");
    printf("11-BRITISH GP || 12-BELGIAN GP || 13-HUNGARIAN GP || 14-DUTCH GP || 15-ITALIAN GP ||\n");
    printf("16-MADRID GP || 17-AZERBAIJAN GP || 18-SINGAPORE GP || 19-US GP || 20-MEXICO CITY GP ||\n");
    printf("21-SAO PAULO GP || 22-LAS VEGAS GP || 23-QATAR GP || 24-ABU DHABI GP || \n");
    printf("===========================================================================================\n");
}

void smallMenu() {
    printf("1-AUSTRALIA GP || 2-CHINESE GP || 3-JAPANESE GP || 4-BAHRAIN GP || 5-SAUDI ARABIAN GP ||\n");
    printf("6-MIAMI GP || 7-CANADA GP || 8-MONACOGP || 9-SPANISH GP || 10-AUSTRIAN GP ||\n");
    printf("11-BRITISH GP || 12-BELGIAN GP || 13-HUNGARIAN GP || 14-DUTCH GP || 15-ITALIAN GP ||\n");
    printf("16-MADRID GP || 17-AZERBAIJAN GP || 18-SINGAPORE GP || 19-US GP || 20-MEXICO CITY GP ||\n");
    printf("21-SAO PAULO GP || 22-LAS VEGAS GP || 23-QATAR GP || 24-ABU DHABI GP || \n");
    printf("===========================================================================================\n");
}
