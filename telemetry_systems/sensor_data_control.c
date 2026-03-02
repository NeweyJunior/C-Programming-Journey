#include <stdio.h>
#include <stdlib.h>

typedef struct sensor{
	float temperature;
	int sensorID;
	struct sensor* next;
}sensor;

sensor* addSensor(sensor* root, float addTemperature, int addSensorID);
sensor* deleteSensor(sensor* root);
void writeSensorData(sensor* root);

int main(){
	sensor* root = NULL;
	
	root = addSensor(root, 100.1, 1);
	root = addSensor(root, -100.1, 2);
	root = addSensor(root, 33.3, 3);
	root = addSensor(root, -25.78, 4);
	root = addSensor(root, 1453.6, 5);
	root = addSensor(root, -1923.10, 6);
	
	root = deleteSensor(root);
	
	writeSensorData(root);
	
	
	return 0;
}
sensor* addSensor(sensor* root, float addTemperature, int addSensorID){
	sensor* newSensor = (sensor*) calloc(1,sizeof(sensor));
	newSensor->temperature = addTemperature;
	newSensor->sensorID = addSensorID;
	
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
sensor* deleteSensor(sensor* root){
	sensor* toDelete = root;
	sensor* prev = NULL;
	
	if(root == NULL){
		printf("No data found.\n");
		return NULL;
	}
	
	while(root != NULL && (root->temperature < -100 || root->temperature > 100)){
		toDelete = root;
		root = root->next;
		free(toDelete);
	}
	
	if(root == NULL){
		printf("No data found.\n");
		return NULL;
	}
	
	sensor* temp = root;
	while(temp != NULL){
		if(temp->temperature < -100 || temp->temperature > 100){
			toDelete = temp;
			temp = temp->next;
			prev->next = temp;
			free(toDelete);
		}else{
			prev = temp;
			temp = temp->next;
		}
	}
	
	return root;
}
void writeSensorData(sensor* root){
	sensor* temp = root;
	printf("------ Sensor Data ------\n");
	while(temp != NULL){
		printf("Sensor ID: %d\n",temp->sensorID);
		printf("Sensor temperature: %.2f\n",temp->temperature);
		printf("---------------------------------\n");
		temp = temp->next;
	}
}
