#include <stdio.h>
#include <stdlib.h>
#define LIMIT 25000

typedef struct sector{
	int time;
	struct sector* next;
}sector;

sector *addData(sector* lastNode, int data);
sector* getFastSectors(sector* baslangic, int limit);

int main(){
	sector *firstSector, *tail;
	firstSector = (sector*) calloc(1,sizeof(sector));
	firstSector->time = 25000;
	firstSector->next = NULL;
	
	tail = addData(firstSector,24178);
	tail = addData(tail,25679);
	tail = addData(tail,24868);
	tail = addData(tail,25476);
	tail = addData(tail,24439);
	
	sector* fastRoot = getFastSectors(firstSector, LIMIT);
    
    
    printf("----- Fast Sectors -----\n");
    sector* temp = fastRoot;
    while(temp != NULL){
        printf("%d ms\n", temp->time);
        temp = temp->next;
    }
	
	return 0;
}
sector *addData(sector* lastNode, int data){
	sector* add = (sector*) calloc(1,sizeof(sector));
	add->time = data;
	add->next = NULL;
	
	lastNode->next = add;
	
	return add;
}
sector* getFastSectors(sector* start, int limit){
	sector* fastRoot = NULL; 
    sector* fastTail = NULL;
    
    sector* temp = start; 
    
    while(temp != NULL){
        if(temp->time <= LIMIT){
            if(fastRoot == NULL){
                fastRoot = (sector*) calloc(1, sizeof(sector));
                fastRoot->time = temp->time;
                fastRoot->next = NULL;
                
                fastTail = fastRoot; 
            }
            else {
                fastTail = addData(fastTail, temp->time);
            }
        }
        temp = temp->next;
    }
    return fastRoot;
}
