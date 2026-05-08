#include <stdio.h>
#include <stdlib.h>

typedef struct sensor{
    int sensorID;
    float vibration;
    int RPM;
    float electricPower;
    struct sensor* next;
}sensor;

sensor* addSensor(sensor* root, int sensorID, float vibration, int RPM, float electricPower);
void updateAndshowData(sensor* root);
sensor* deleteSensorData(sensor* root);
void saveToFile(sensor* root);

int main(void){

    FILE* readSensorData;
    readSensorData = fopen("C:\\Users\\LENOVO\\Desktop\\C-Programming-Journey\\telemetry_systems\\readSensorData.txt", "r");

    char buffer[100];
    sensor* root = NULL;

    if(readSensorData == NULL){
        printf("File opening is failed.\n");
        return 1;
    }else{
        int i = 1, RPM, numberOfReadData;
        float vibration, electricPower;

        while(fgets(buffer, sizeof(buffer), readSensorData) != NULL){

            numberOfReadData = sscanf(buffer, "%f, %d, %f", &vibration, &RPM, &electricPower);

            if(numberOfReadData == 3){
                root = addSensor(root, i, vibration, RPM, electricPower);
            }else{
                printf("%d. ROW: Skipped due to error.\n", i);
            }
            
            i++;
        }
        updateAndshowData(root);
        fclose(readSensorData);
    }

    saveToFile(root);
    
    root = deleteSensorData(root);
    return 0;
}

sensor* addSensor(sensor* root, int sensorID, float vibration, int RPM, float electricPower){
    sensor* newSensor = (sensor*) calloc(1, sizeof(sensor));
    newSensor->sensorID = sensorID;
    newSensor->vibration = vibration;
    newSensor->RPM = RPM;
    newSensor->electricPower = electricPower;

    if(root == NULL){
        return newSensor;
    }

    sensor* temp = root;

    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newSensor;

    return root;
}

void updateAndshowData(sensor* root){
    sensor* temp = root;
   
    while(temp != NULL){
        printf("%d. ROW: Vibration = %.3f | RPM = %d | Electric Power = %.3f \n"
        , temp->sensorID , temp->vibration, temp->RPM, temp->electricPower);

        if(temp->vibration > 100.0){
            temp->RPM = temp->RPM - (0.1 * temp->RPM);
            temp->electricPower = temp->electricPower - (0.05 * temp->electricPower);

            // If the RPM and electrical power decrease, the vibration should also decrease by 5%.
            temp->vibration = temp->vibration - (0.05 * temp->vibration);

            printf("Because the vibration was high, the RPM and electrical power were reduced, thus reducing the vibration as well.\n", temp->sensorID);
            printf("NEW DATA %d. ROW: Vibration = %.3f | RPM = %d | Electric Power = %.3f \n"
            , temp->sensorID, temp->vibration, temp->RPM, temp->electricPower);
            printf("=============================================================================================================\n");
       }
       temp = temp->next;
    }
}

sensor* deleteSensorData(sensor* root){
    sensor* temp = root;
    sensor* back;

    while(temp != NULL){
        back = temp;
        temp = temp->next;
        free(back);
    }
    return NULL;
}

void saveToFile(sensor* root){
    FILE* writeSensorData;

    writeSensorData = fopen("C:\\Users\\LENOVO\\Desktop\\C-Programming-Journey\\telemetry_systems\\writeSensorData.txt", "w");

    if(writeSensorData == NULL){
        printf("Write process is failed.\n");
    }else{
        sensor* temp = root;

        while(temp != NULL){
            fprintf(writeSensorData, "%.3f, %d, %.3f \n", temp->vibration, temp->RPM, temp->electricPower);
            temp = temp->next;
        }
        printf("=============================================================================================================\n");
        printf("Write process is successfull.\n");
        fclose(writeSensorData);
    }
}