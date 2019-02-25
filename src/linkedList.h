#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avlTree.h"

//structure type to point to the nodes of a tree and also create self-referential list used for queueing. 
struct queue {
    struct Node* nodeptr;
    struct queue* next;
};

//resulting singly linked list
struct list{
    int num;
    char nombre[30];
    char apellidos[30];
    char cancer[30];
    char medicamento[25];
    struct list* next;
};

//helper to create a node for a queue
struct queue* nodeQueue(struct queue* node, struct Node* root) {
	node = (struct queue*)malloc(sizeof(struct queue));
    node->nodeptr = root;
    node->next = NULL;
    return(node);
}

//helper to create a node for the linked list
struct list* nodeList(struct queue* node, int key, char nom[30], char ape[30], char cancer[30], char med[25]) { 
    struct list* temp = (struct list*)malloc(sizeof(struct list)); 
   	temp->num = node->nodeptr->key;
    strcpy(temp->nombre, node->nodeptr->nombre);
    strcpy(temp->apellidos, node->nodeptr->apellidos);
    strcpy(temp->cancer, node->nodeptr->cancer);
    strcpy(temp->medicamento, node->nodeptr->medicamento);
    temp->next = NULL;
    return(temp); 
} 

//Create a linked list from a avlTree
void createlistAvl(struct Node* root, struct list** head) {
    struct queue* qhead, * qrear, * qtemp, * qrelease;
    struct list* temp, *rear;
    if (root == NULL) {
        return;
    }
    qhead = nodeQueue(qhead, root);
    qrear = qhead;
    while (qhead != NULL) {
        temp = nodeList(qhead, qhead->nodeptr->key, qhead->nodeptr->nombre, 
        	qhead->nodeptr->apellidos, qhead->nodeptr->cancer, qhead->nodeptr->medicamento);
        if (*head == NULL) {
            *head = temp;
        }
        else {
            rear->next = temp;
        }
        rear = temp;
        if (qhead->nodeptr->left != NULL) {
            qtemp = (struct queue *)malloc(sizeof(struct queue));
            qtemp->nodeptr = qhead->nodeptr->left;
            qtemp->next = NULL;
            qrear->next = qtemp;
            qrear = qtemp;
        }
        if (qhead->nodeptr->right != NULL) {
            qtemp = (struct queue *)malloc(sizeof(struct queue));
            qtemp->nodeptr = qhead->nodeptr->right;
            qtemp->next = NULL;
            qrear->next = qtemp;
            qrear = qtemp;
        }
        qrelease = qhead;
        qhead = qhead->next;
        free(qrelease);
    }
}

//Function to reverse the linked list
static void reverseList(struct list** head) { 
    struct list* prev   = NULL; 
    struct list* current = * head; 
    struct list* next = NULL; 
    while (current != NULL) { 
        next  = current->next;   
        current->next = prev;    
        prev = current; 
        current = next; 
    } 
    * head = prev; 
} 

//compare two node to give the max
int comparePeople(const struct list* a, const struct list* b) {
    return strcmp(a->nombre, b->nombre);
}

//compare two node to give the min
int comparePeopleDes(const struct list* a, const struct list* b) {
    return -strcmp(a->medicamento, b->medicamento);
}

//Ascending order by name
struct list* aseSortedListName(struct list* head) {
    struct list* tmp = head;
    if (head == NULL) {
        return NULL;
    }
    struct list** pp = &head;
    while (*pp != NULL && comparePeople(tmp, *pp) >= 0) {
        pp = &(*pp)->next;
    }
    tmp->next = *pp;
    *pp = tmp;
    return tmp;
}

//Descending order by name
struct list* desSortedListName(struct list* head) {
    struct list* tmp = head;
    if (head == NULL) {
        return NULL;
    }
    struct list** pp = &head;
    while (*pp != NULL && comparePeopleDes(tmp, *pp) >= 0) {
        pp = &(*pp)->next;
    }
    tmp->next = *pp;
    *pp = tmp;
    return tmp;
}

//Sort the list by medicamento
struct list* aseSortedListMed(struct list* head) {
   	struct list* current = head;
  	struct list* N = head;
   	struct list* S = head->next;
   	struct list* X = head->next->next; 
   	struct list* W = head->next->next->next;
   	struct list* E = head->next->next->next->next;
   	while (current != NULL){
      	if (current->next->medicamento >= head->medicamento){
          	E->next = N;
          	W->next = NULL;
          	head = E;
       	}
        current = current->next;
    }
    return head;
}

//find a link with given key
struct list* findList(struct list* head, int key) {
   	struct list* current = head;
   	if(head == NULL) {
      	return NULL;
   	}
   	while(current->num != key) {
      	if(current->next == NULL) {
         	return NULL;
      	} 
      	else {
         	current = current->next;
      	}
   	}      
   	return current;
}

//Search for the int id
void searchKeyList(struct list* head, int key){
	while (head != NULL && head->num != key) {
        head = head->next;
    }
    if (head != NULL && head->num == key) {
        printf("Se encontro al paciente: %d \n", key);
        printf("Datos del paciente: ");
        printf("%d ", head->num);
        printf("%s ", head->nombre);
        printf("%s ", head->apellidos);
        printf("%s ", head->cancer);
        printf("%s \n", head->medicamento);
    }
}

//Search for the string nombre
void searchNameList(struct list* head, char* word) {
    while (head != NULL && strcmp(head->nombre, word) != 0) {
        head = head->next;
    }
    if (head != NULL && strcmp(head->nombre, word) == 0) {
        printf("Se encontro al paciente: %s \n", word);
        printf("Datos del paciente: ");
        printf("%d ", head->num);
        printf("%s ", head->nombre);
        printf("%s ", head->apellidos);
        printf("%s ", head->cancer);
        printf("%s \n", head->medicamento);
    }
}

//Search for the string apellido
void searchApeList(struct list* head, char* word) {
    while (head != NULL && strcmp(head->apellidos, word) != 0) {
        head = head->next;
    }
    if (head != NULL && strcmp(head->apellidos, word) == 0) {
        printf("Se encontro al paciente: %s \n", word);
        printf("Datos del paciente: ");
        printf("%d ", head->num);
        printf("%s ", head->nombre);
        printf("%s ", head->apellidos);
        printf("%s ", head->cancer);
        printf("%s \n", head->medicamento);
    }
}

//Search for the string medicamento
void searchMedList(struct list* head, char* word) {
    while (head != NULL && strcmp(head->medicamento, word) != 0) {
        head = head->next;
    }
    if (head != NULL && strcmp(head->medicamento, word) == 0) {
        printf("Se encontro al paciente: %s \n", word);
        printf("Datos del paciente: ");
        printf("%d ", head->num);
        printf("%s ", head->nombre);
        printf("%s ", head->apellidos);
        printf("%s ", head->cancer);
        printf("%s \n", head->medicamento);
    }
}

//Print the list
void printList(struct list* head){
    while (head != NULL){
    	printf(" %d ", head->num); 
        printf("%s ", head->nombre);
        printf("%s ", head->apellidos);
        printf("%s ", head->cancer);
        printf("%s \n", head->medicamento);
        head = head->next;
    }
}

//Delete a node of the list
void deleteList(struct list** head){
    struct list* temp;
    temp = *head;
    while (temp != NULL){
        * head = (*head)->next;
        free(temp);
        temp =* head;
    }
}

//Count the number of nodes in a linked list
int countList(struct list* head) {
    int cnt = 0;
    struct list* current = head;
    while (current != NULL) {
        cnt++;
        current = current->next;
    }
	return(cnt);
}