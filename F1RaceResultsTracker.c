#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node* next;
	int raceID;
}node;

int addAmount = 1;

void writeList(node* root);
node* addListsEnd(node*root, int addData);
node* addTopOfTheList(node* root, int addData);
node* deleteListsData(node* root, int limit);

int main(){
	node* root = NULL;

	root = addListsEnd(root,4);
	root = addListsEnd(root,1);
	root = addListsEnd(root,4);
	root = addListsEnd(root,10);
	root = addListsEnd(root,2);
	root = addListsEnd(root,20);
	root = addListsEnd(root,5);
	root = addListsEnd(root,4);
	root = addListsEnd(root,9);
	root = addListsEnd(root,2);
	root = addListsEnd(root,1);
	root = addListsEnd(root,1);
	root = addListsEnd(root,2);
	root = addListsEnd(root,1);
	root = addListsEnd(root,3);
	root = addListsEnd(root,3);
	root = addListsEnd(root,1);
	root = addListsEnd(root,1);
	root = addListsEnd(root,1);
	root = addTopOfTheList(root,2);
	root = addTopOfTheList(root,6);
	root = addTopOfTheList(root,1);
	root = addTopOfTheList(root,4);
	root = addTopOfTheList(root,2);
	root = deleteListsData(root, 10);
	writeList(root);
	
	return 0;
}
void writeList(node* root){
	node* temp = root;
	printf("---- Races in which Max Verstappen scored points ----\n");
	while(temp != NULL){
		printf("%d. race, with %d. place\n",temp->raceID,temp->data);
		temp = temp->next;
	}
}
node* addListsEnd(node* root, int addData){ 
	node* newNode = (node*) calloc(1,sizeof(node));
	newNode->data = addData;
	newNode->next = NULL;
	
	
	if(root == NULL){
		newNode->raceID = addAmount;
    	addAmount++;
		return newNode;
	}
	
	node* temp = root;
    while(temp->next != NULL){
        temp = temp->next;
    }
	
	while(temp->next != NULL){
		temp= temp->next;
	}
	newNode->raceID = addAmount;
    addAmount++;
	temp->next = newNode;
	
	return root;
}
node* addTopOfTheList(node* root, int addData){
	node* newNode = (node*) calloc(1,sizeof(node));
	newNode->data = addData;
	newNode->next = root;
	node* temp = newNode;
	
	for(int i = addAmount; i >= 1; i--){
		if(temp != NULL){
			temp->raceID = addAmount - i + 1;
			temp = temp->next;
		}
	}
	
	addAmount++;
	return newNode;  
}

node* deleteListsData(node* root, int limit){
	node* temp = root;
	node* toDelete;
	node* prev = NULL;
	
	while(temp == root && temp->data > limit){
		toDelete = temp;
		temp = temp->next;
		free(toDelete);
		root = temp;
	}
	
	while(temp != NULL){
		if(temp->next != NULL && temp->data > limit){
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
