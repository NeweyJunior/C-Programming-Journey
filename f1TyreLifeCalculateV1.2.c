#include <stdio.h>
#include <string.h>

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
Track fetchTrackData(int);
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
            
            Track selectedTrack = fetchTrackData(chooseTrack);
            printf("SELECTED TRACK: %s\n", selectedTrack.name);
            printf("Temp: %.2f C | Length: %.3f km | Stress Level: %d | Number of laps: %d\n", 
                   selectedTrack.temperature, selectedTrack.length, selectedTrack.stressLevel, selectedTrack.totalLaps);
            printf("-------------------------------------------------------------------------------------------\n");
            
            printf("Enter starting fuel load (kg):");
            scanf("%f", &startFuel);
            printf("-------------------------------------------------------------------------------------------\n");
            
            printf("1-c1 || 2-c2 || 3-c3 || 4-c4 || 5-c5 || 6-c6 ||\n");
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
            
            Track selectedTrack = fetchTrackData(chooseTrack);
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

    float idealKm = 190.0;
    
    if(t.stressLevel==5){
        selectedCoefficient*=0.80;
    }
    
    float totalDistance = idealKm * selectedCoefficient;

    float referenceDegree = 20.0;
    float degreeDifference = trackDegree - referenceDegree;
    float degreeEffect = 1.0 - (degreeDifference * 0.01);

    float stressFactor = 1 - ((trackStress - 1) * 0.06);

    float grainingPenalty = 1.0;

    if (trackDegree <= 25.0 && trackStress <= 3) {
        grainingPenalty = 0.85;
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
    float weightPenalty = 1 - (averageWeight * 0.003);

    float realDistance = totalDistance * degreeEffect * stressFactor * grainingPenalty * weightPenalty;

    int howManyLaps = (int)realDistance / trackLength;

    return howManyLaps;
}

void calculateBestStrategy(int trackID,float startFuel){
    Track t = fetchTrackData(trackID);
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
    float smallest=0;
    int bestIndex=0;
    for(int i=0; i<22; i++){
        if(i==0) smallest = strategies[0];
        else if(strategies[i]<smallest){
            smallest = strategies[i];
            bestIndex=i;
        }
    }
    int totalSeconds = (int) smallest;
    printf("The winner strategy is : %s !\n",*(strategyNames+bestIndex));
    printf("Estimated total race time : %d min. %d sec.\n",totalSeconds/60,totalSeconds%60);
    printf("-------------------------------------------------------------------------------------------\n");

    
    
}
float calculate_1Stop(Track t,int tyre1,int tyre2,float startFuel){
    
    //---- stint 1 ----
    int laps1=calculateTyreLife(t.temperature, tyre1, t.length, t.stressLevel, startFuel, t);
    
    float speed1;
    if (tyre1 >= 4) speed1 = t.referenceTime * 0.98; // Soft
    else if (tyre1 == 3) speed1 = t.referenceTime * 1.00; // Medium
    else speed1 = t.referenceTime * 1.02; // Hard
    
    float fuelBurn1 = laps1 * t.trackFuelCoefficient;
    float avgFuel1 = startFuel - (fuelBurn1 / 2);
    
    float time1 = (laps1 * speed1) + (laps1) * (avgFuel1 * 0.03);
    
    //---- stint 2 ----
    int lapsRemaining = t.totalLaps - laps1;
    float currentFuel = startFuel - fuelBurn1;
    
    int laps2 = calculateTyreLife(t.temperature, tyre2, t.length, t.stressLevel, currentFuel, t);
    
    if(laps2<lapsRemaining) return 999999.0; // tyre is not enough
    
    float speed2;
    if (tyre2 == 5) speed2 = t.referenceTime * 0.98;
    else if (tyre2 == 3) speed2 = t.referenceTime * 1.00;
    else speed2 = t.referenceTime * 1.02;
    
    float fuelBurn2 = lapsRemaining * t.trackFuelCoefficient;
    float avgFuel2 = currentFuel - (fuelBurn2 / 2);
    
    float time2 = (lapsRemaining * speed2) + (lapsRemaining) * (avgFuel2 * 0.03);
    
    return time1 + t.pitWay + time2;
}
float calculate_2Stop(Track t,int tyre1,int tyre2,int tyre3,float startFuel){
    //---- stint 1 ----
    int laps1=calculateTyreLife(t.temperature,tyre1,t.length,t.stressLevel, startFuel, t);
    
    float speed1;
    if(tyre1 == 5) speed1 = t.referenceTime * 0.98; //soft
    else if(tyre1 == 3) speed1= t.referenceTime; //medium
    else speed1 = t.referenceTime * 1.02; //hard
    
    float fuelBurn1 = t.trackFuelCoefficient * laps1;
    float avgFuel1 = startFuel - (fuelBurn1/2);
    
    float time1 = (laps1 * speed1) + (laps1) * (avgFuel1 * 0.03);
    
    //---- stint 2 ----
    int lapsRemaining = t.totalLaps - laps1;
    float fuelAtPit1 = startFuel - fuelBurn1;
    
    int laps2 = calculateTyreLife(t.temperature, tyre2, t.length, t.stressLevel, fuelAtPit1, t);
    
    float speed2;
    if (tyre2 == 5) speed2 = t.referenceTime * 0.98; //soft 
    else if (tyre2 == 3) speed2 = t.referenceTime * 1.00; //medium
    else speed2 = t.referenceTime * 1.02; //hard
    
    float fuelBurn2 = laps2 * t.trackFuelCoefficient;
    float avgFuel2 = fuelAtPit1 - (fuelBurn2 / 2);
    
    float time2 = (laps2 * speed2) + (laps2) * (avgFuel2 * 0.03);
    
    //---- stint 3 ----
    int lastStint = t.totalLaps - laps1 - laps2;
    float lastFuel = fuelAtPit1 - fuelBurn2;
    
    int laps3 = calculateTyreLife(t.temperature, tyre3, t.length, t.stressLevel, lastFuel, t);
    
    if(lastStint>laps3) return 999999.0; // tyre is not enough
    
    float speed3;
    if(tyre3 == 5) speed3 = t.referenceTime * 0.98; // soft
    else if(tyre3 == 3) speed3 = t.referenceTime; //medium
    else speed3 = t.referenceTime * 1.02; //hard
    
    float fuelBurn3 = lastStint * t.trackFuelCoefficient;
    float avgFuel3 = lastFuel - (fuelBurn3/2);
    
    float time3 = (lastStint * speed3) + (lastStint) * (avgFuel3 * 0.03);

    return time1 + time2 + time3 + (2 * t.pitWay); 
}

    
Track fetchTrackData(int choose) {
    Track t;

    switch (choose) {
        case 1:
            strcpy(t.name, "Australian GP (Albert Park)");
            t.length = 5.278; t.temperature = 24.0; t.referenceTime = 80.0;
            t.pitWay = 21.0; t.stressLevel = 3; t.trackFuelCoefficient = 1.65; t.totalLaps = 58;
            break;
        case 2:
            strcpy(t.name, "Chinese GP");
            t.length = 5.451; t.temperature = 22.0; t.referenceTime = 98.0;
            t.pitWay = 23.0; t.stressLevel = 4; t.trackFuelCoefficient = 1.70; t.totalLaps = 56;
            break;
        case 3:
            strcpy(t.name, "Japanese GP(Suzuka)");
            t.length = 5.807; t.temperature = 24.0; t.referenceTime = 92.0;
            t.pitWay = 22.5; t.stressLevel = 5; t.trackFuelCoefficient = 1.75; t.totalLaps = 53;
            break;
        case 4:
            strcpy(t.name, "Bahrain GP");
            t.length = 5.412; t.temperature = 26.0; t.referenceTime = 92.0;
            t.pitWay = 23.0; t.stressLevel = 5; t.trackFuelCoefficient = 1.70; t.totalLaps = 57;
            break;
        case 5:
            strcpy(t.name, "Saudi Arabian GP");
            t.length = 6.174; t.temperature = 29.0; t.referenceTime = 89.0;
            t.pitWay = 21.0; t.stressLevel = 2; t.trackFuelCoefficient = 1.75; t.totalLaps = 50;
            break;
        case 6:
            strcpy(t.name, "Miami GP");
            t.length = 5.412; t.temperature = 42.0; t.referenceTime = 90.0;
            t.pitWay = 20.0; t.stressLevel = 3; t.trackFuelCoefficient = 1.60; t.totalLaps = 57;
            break;
        case 7:
            strcpy(t.name, "Canadian GP");
            t.length = 4.361; t.temperature = 25.0; t.referenceTime = 74.0;
            t.pitWay = 18.0; t.stressLevel = 2; t.trackFuelCoefficient = 1.50; t.totalLaps = 70;
            break;
        case 8:
            strcpy(t.name, "Monaco GP");
            t.length = 3.337; t.temperature = 35.0; t.referenceTime = 73.0;
            t.pitWay = 19.0; t.stressLevel = 1; t.trackFuelCoefficient = 1.15; t.totalLaps = 78;
            break;
        case 9:
            strcpy(t.name, "Spanish GP");
            t.length = 4.657; t.temperature = 38.0; t.referenceTime = 78.0;
            t.pitWay = 22.0; t.stressLevel = 5; t.trackFuelCoefficient = 1.65; t.totalLaps = 66;
            break;
        case 10:
            strcpy(t.name, "Austrian GP");
            t.length = 4.318; t.temperature = 28.0; t.referenceTime = 68.0;
            t.pitWay = 20.0; t.stressLevel = 3; t.trackFuelCoefficient = 1.45; t.totalLaps = 71;
            break;
        case 11:
            strcpy(t.name, "British GP");
            t.length = 5.891; t.temperature = 20.0; t.referenceTime = 88.0;
            t.pitWay = 24.0; t.stressLevel = 5; t.trackFuelCoefficient = 1.75; t.totalLaps = 52;
            break;
        case 12:
            strcpy(t.name, "Belgian GP");
            t.length = 7.004; t.temperature = 18.0; t.referenceTime = 106.0;
            t.pitWay = 22.0; t.stressLevel = 5; t.trackFuelCoefficient = 2.35; t.totalLaps = 44;
            break;
        case 13:
            strcpy(t.name, "Hungarian GP");
            t.length = 4.381; t.temperature = 45.0; t.referenceTime = 78.0;
            t.pitWay = 20.0; t.stressLevel = 4; t.trackFuelCoefficient = 1.50; t.totalLaps = 70;
            break;
        case 14:
            strcpy(t.name, "Dutch GP");
            t.length = 4.259; t.temperature = 22.0; t.referenceTime = 73.0;
            t.pitWay = 21.0; t.stressLevel = 4; t.trackFuelCoefficient = 1.50; t.totalLaps = 72;
            break;
        case 15:
            strcpy(t.name, "Italian GP");
            t.length = 5.793; t.temperature = 30.0; t.referenceTime = 81.0;
            t.pitWay = 24.0; t.stressLevel = 2; t.trackFuelCoefficient = 1.80; t.totalLaps = 53;
            break;
        case 16:
            strcpy(t.name, "Madrid GP");
            t.length = 5.474; t.temperature = 32.0; t.referenceTime = 88.0;
            t.pitWay = 20.0; t.stressLevel = 3; t.trackFuelCoefficient = 1.60; t.totalLaps = 56;
            break;
        case 17:
            strcpy(t.name, "Azerbaijan GP");
            t.length = 6.003; t.temperature = 26.0; t.referenceTime = 103.0;
            t.pitWay = 20.0; t.stressLevel = 3; t.trackFuelCoefficient = 1.80; t.totalLaps = 51;
            break;
        case 18:
            strcpy(t.name, "Singapore GP");
            t.length = 4.940; t.temperature = 30.0; t.referenceTime = 98.0;
            t.pitWay = 28.0; t.stressLevel = 4; t.trackFuelCoefficient = 1.90; t.totalLaps = 62;
            break;
        case 19:
            strcpy(t.name, "United States GP");
            t.length = 5.513; t.temperature = 28.0; t.referenceTime = 96.0;
            t.pitWay = 22.0; t.stressLevel = 4; t.trackFuelCoefficient = 1.70; t.totalLaps = 56;
            break;
        case 20:
            strcpy(t.name, "Mexico City GP");
            t.length = 4.304; t.temperature = 24.0; t.referenceTime = 80.0;
            t.pitWay = 22.0; t.stressLevel = 3; t.trackFuelCoefficient = 1.40; t.totalLaps = 71;
            break;
        case 21:
            strcpy(t.name, "Sao Paulo GP");
            t.length = 4.309; t.temperature = 35.0; t.referenceTime = 72.0;
            t.pitWay = 21.0; t.stressLevel = 3; t.trackFuelCoefficient = 1.50; t.totalLaps = 71;
            break;
        case 22:
            strcpy(t.name, "Las Vegas GP");
            t.length = 6.201; t.temperature = 10.0; t.referenceTime = 94.0;
            t.pitWay = 20.0; t.stressLevel = 2; t.trackFuelCoefficient = 1.90; t.totalLaps = 50;
            break;
        case 23:
            strcpy(t.name, "Qatar GP");
            t.length = 5.419; t.temperature = 27.0; t.referenceTime = 83.0;
            t.pitWay = 24.0; t.stressLevel = 5; t.trackFuelCoefficient = 1.80; t.totalLaps = 57;
            break;
        case 24:
            strcpy(t.name, "Abu Dhabi GP");
            t.length = 5.281; t.temperature = 25.0; t.referenceTime = 86.0;
            t.pitWay = 22.0; t.stressLevel = 3; t.trackFuelCoefficient = 1.70; t.totalLaps = 58;
            break;
    }        
    return t;
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
