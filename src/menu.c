#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linkedList.h"

struct Node* root = NULL;
struct list* head = NULL;

void readData() {
	FILE *file;
	int id;
	char name[30];
	char apellido[30];
	char cancer[30];
	char medicamento[25];
	file = fopen("data.txt", "r");
	if (file == NULL){
		printf("No se encontro el archivo, creando un nuevo data.txt\n");
		file = fopen("data.txt", "w");
	}
	else {
		printf("Archivo cargado, listo para trabajar..... \n");
		while(5 == fscanf(file, "%d %30s %30s %30s %25s", &id, name, apellido, cancer, medicamento)) {
			root = insert(root, id, name, apellido, cancer, medicamento);
		}
		fclose(file);
	}
}

void appendData(int id, char name[30], char apellido[30], char cancer[30], char medicamento[25]) {
	FILE *file;
  	file = fopen("data.txt", "a");
  	fprintf(file, "\n%d %s %s %s %s", id, name, apellido, cancer, medicamento);
  	fclose(file);
}

void readNewData(char* fp) {
	FILE *file;
	int id;
	char name[30];
	char apellido[30];
	char cancer[30];
	char medicamento[25];
	file = fopen(fp, "r");
	if (file == NULL){
		printf("No se encontro el archivo, creando un nuevo %s\n", fp);
		file = fopen(fp, "w");
	}
	else {
		printf("Archivo cargado, listo para trabajar..... \n");
		while(5 == fscanf(file, "%d %30s %30s %30s %25s", &id, name, apellido, cancer, medicamento)) {
			root = insert(root, id, name, apellido, cancer, medicamento);
		}
		fclose(file);
	}
}

void createBackup(struct Node* root, char* file) {
	FILE *fp, *fc;
	int ch;
	fp = fopen("data.txt","r");
  	fc = fopen(file,"w");
  	if(fp == NULL || fc == NULL) {
    	printf("\nError.../createFile %s", file);
  	}
  	serialize(root, fc);
  	fclose(fp);
  	fclose(fc);
}

void menuInsertar() {
	int id, opcion;
	char nombre[30];
	char apellido[30];
	char cancer[30];
	char medicamento[25];
	printf("\n\t\t+-------------------+");
	printf("\n\t\t| Ingresar paciente |");
	printf("\n\t\t+-------------------+\n");
	printf("\n 1. Nuevo paciente ");
	printf("\n 2. Regresar menu principal \n");
	printf("\n Introduzca opcion (1-2): ");
	scanf("%d", &opcion);
	switch(opcion) {
	    case 1:
	    	system("clear");
	        printf("\n\t\t+--------------------------+");
	        printf("\n\t\t| Datos del nuevo paciente |");
	        printf("\n\t\t+--------------------------+\n");
	        printf("\t Ejemplo de como introducir datos: \n");
	        printf("\t\t introduzca ID: 5674");
	        printf("\n\t\t Nombre o Nombres del paciente: Jose_Humberto");
	        printf("\n\t\t Apellidos del paciente: Gonzalez_Robles");
	        printf("\n\t\t Tipo de cancer: Pulmon");
	        printf("\n\t\t Medicamento del paciente: Paracetamol \n");
	        printf("\n introduzca ID: ");
	        scanf("%d", &id);
	        if (findKey(root, id) == true) {
	        	printf("\n Ese id ya se encuentra dentro del registrado\n");
	        	break;
	        }
	        else {
		        printf("\n Nombre o Nombres del paciente: ");
			    scanf("%30s", nombre);
			    printf("\n Apellidos del paciente: ");
			    scanf("%30s", apellido);
			    printf("\n\t\t Tipo de cancer:");
			    scanf("%30s", cancer);
			    printf("\n Medicamento del paciente: ");
			    scanf("%25s", medicamento);
			    root = insert(root, id, nombre, apellido, cancer, medicamento);
			    appendData(id, nombre, apellido, cancer, medicamento);
			    break;
	        }
	    case 2:
	        break;
	}
}

void menuEliminar() {
	int id, opcion;
	char confirmacion;
	struct Node* current = NULL;
	printf("\n\t\t+-------------------+");
	printf("\n\t\t| Eliminar paciente |");
	printf("\n\t\t+-------------------+\n");
	printf("\n 1. Deshabilitar al paciente ");
	printf("\n 2. Regresar menu principal \n");
	printf("\n Introduzca opcion (1-2): ");
	scanf("%d", &opcion);
	switch(opcion) {
	    case 1:
	    	system("clear");
	        printf("\n\t\t+--------------------------+");
	        printf("\n\t\t| Deshabilitar al paciente |");
	        printf("\n\t\t+--------------------------+\n");
	        printf("\n introduzca ID: ");
	        scanf("%d", &id);
	        if (findKey(root, id) == true) {
	   			printf("\n ¿Seguro que quiere deshabilitar al paciente? (S/N) ");
	        	scanf("%s", &confirmacion);
		        if (confirmacion == 'S' || confirmacion == 's') {
		        	if (findKey(root, id) == true) {
					    current = find(root, id);
					    printf(" Paciente %d %s %s deshabilitado\n", current->key, current->nombre, current->apellidos);
					    disableNode(root, id);
					}
					else {
					    printf(" Paciente no encontrado\n");
					}
		        }
		        if (confirmacion == 'N' || confirmacion == 'n'){
		        	printf(" Regreso al menu principal\n");
		        }
	        	break;
	        }
	        else {
	        	printf("\n Ese id no se encuentra registrado\n");
	        	break;
	        }
	        break; 
	    case 2:
	        break;
	}
}

void menuEditar() {
	int id, opcion;
	struct Node* current = NULL;
	char nombre[30];
	char apellido[30];
	char cancer[30];
	char medicamento[25];
	printf("\n\t\t+---------------------------+");
	printf("\n\t\t| Editar datos del paciente |");
	printf("\n\t\t+---------------------------+\n");
	printf("\n 1. Editar datos del paciente ");
	printf("\n 2. Regresar menu principal \n");
	printf("\n Introduzca opcion (1-2): ");
	scanf("%d", &opcion);
	switch(opcion) {
	    case 1:
	    	system("clear");
	    	printf("\n\t\t+--------------+");
	        printf("\n\t\t| Editar datos |");
	        printf("\n\t\t+--------------+\n");
	        printf("\n introduzca ID: ");
	        scanf("%d", &id);
	        if (findKey(root, id) == true) {
	        	printf("Paciente encontrado, por favor introdusca los datos\n");
	        	printf("\n Nombre: ");
	        	scanf("%30s", nombre);
	        	printf("\n Apellido: ");
	        	scanf("%30s", apellido);
	        	printf("\n Tipo de cancer: ");
	        	scanf("%30s", cancer);
	        	printf("\n Medicamento: ");
	        	scanf("%30s", medicamento);
				current = changeKey(root, id, nombre, apellido, cancer, medicamento);
				appendData(id, nombre, apellido, cancer, medicamento);
			}
			else {
				printf(" Paciente no encontrado\n");
			}
	        break; 
	    case 2:
	        break;
	}
}

void menuHabilitar() {
	int id, opcion;
	struct Node* current = NULL;
	printf("\n\t\t+--------------------+");
	printf("\n\t\t| habilitar paciente |");
	printf("\n\t\t+--------------------+\n");
	printf("\n 1. habilitar al paciente ");
	printf("\n 2. Regresar menu principal \n");
	printf("\n Introduzca opcion (1-2): ");
	scanf("%d", &opcion);
	switch(opcion) {
	    case 1:
	        system("clear");
	        printf("\n\t\t+-----------------------+");
	        printf("\n\t\t| habilitar al paciente |");
	        printf("\n\t\t+-----------------------+\n");
	        printf("\n introduzca ID: ");
	        scanf("%d", &id);
	        if (findKey(root, id) == true) {
			    current = find(root, id);
			    printf(" Paciente %d %s %s %s habilitado\n", current->key, current->nombre, current->apellidos, current->cancer);
			    enableNode(root, id);
			}
			else {
			    printf(" Paciente no encontrado\n");
			}
	        break; 
	    case 2:
	        break;
	}
}

void menuReporte() {
	int opcion;
	struct list* tmp = NULL;
	printf("\n\t\t+---------------+");
	printf("\n\t\t| Reporte total |");
	printf("\n\t\t+---------------+\n");
	printf("\n 1. Reporte en order asendiente por id ");
	printf("\n 2. Reporte en order descendiente por id ");
	printf("\n 3. Reporte en order asendiente por nombre ");
	printf("\n 4. Reporte en order descendiente por nombre ");
	printf("\n 5. Reporte en order asendiente por medicamento ");
	printf("\n 6. Reporte en order descendiente por medicamento ");
	printf("\n 7. Regresar al menu principal \n");
	printf("\n Introduzca opcion (1-78): ");
	scanf("%d", &opcion);
	switch(opcion) {
	    case 1:
			system("clear");
		    printf("\n\t\t+-----------------------------------+");
		    printf("\n\t\t| Reporte en order asendiente por id|");
		    printf("\n\t\t+-----------------------------------+\n");
		    levelOrder(root);
		    break;
	    case 2:
	        system("clear");
	        printf("\n\t\t+-------------------------------------+");
	        printf("\n\t\t| Reporte en order descendiente por id|");
	        printf("\n\t\t+-------------------------------------+\n");
	        reverseLevelOrder(root);
	        break;
	    case 3:
	        system("clear");
	        printf("\n\t\t+---------------------------------------+");
	       	printf("\n\t\t| Reporte en order asendiente por nombre|");
	        printf("\n\t\t+---------------------------------------+\n");
	        createlistAvl(root, &head);
	        tmp = aseSortedListName(head);
	       	printList(tmp);
	       	head = NULL;
	       	tmp = NULL;
	        break; 
	    case 4:
	        system("clear");
	        printf("\n\t\t+-----------------------------------------+");
	        printf("\n\t\t| Reporte en order descendiente por nombre|");
	        printf("\n\t\t+-----------------------------------------+\n");
	        createlistAvl(root, &head);
	        reverseList(&head);
	        tmp = desSortedListName(head);
	       	printList(tmp);
	       	head = NULL;
	       	tmp = NULL;
	        break; 
	    case 5:
	        system("clear");
	        printf("\n\t\t+--------------------------------------------+");
	        printf("\n\t\t| Reporte en order asendiente por Medicamento|");
	        printf("\n\t\t+--------------------------------------------+\n");
	        createlistAvl(root, &head);
	        tmp = aseSortedListMed(head);
	       	printList(tmp);
	       	head = NULL;
	       	tmp = NULL;
	        break; 
	    case 6:
	        system("clear");
	        printf("\n\t\t+----------------------------------------------+");
	        printf("\n\t\t| Reporte en order descendiente por Medicamento|");
	        printf("\n\t\t+----------------------------------------------+\n");
	        createlistAvl(root, &head);
	        reverseList(&head);
	        tmp = aseSortedListMed(head);
	       	printList(tmp);
	       	head = NULL;
	       	tmp = NULL;
	        break; 
	 	case 7:
	    	break; 
	}
}

void menuBuscarID() {
	int opcion, id;
	struct Node* current = NULL;
	struct Node* tmp = NULL;
	system("clear");
	printf("\n\t\t+----------------------------+");
	printf("\n\t\t| Buscar por ID del paciente |");
	printf("\n\t\t+----------------------------+\n");
	printf("\n 1. Buscar excatamente por la ID ");
	printf("\n 2. Buscar por valores Mayores a la ID o excatamente la ID ");
	printf("\n 3. Buscar por valores Menores a la ID o excatamente la ID ");
	printf("\n 4. Regresar menu Buscar \n");
	printf("\n Introduzca opcion (1-4): ");
	scanf("%d", &opcion);
	switch(opcion) {
		case 1:
			system("clear");
	       	printf("\n\t\t+------------------------------+");
	       	printf("\n\t\t| Buscar excatamente por la ID |");
	        printf("\n\t\t+------------------------------+\n");
	        printf("\n introduzca ID del paciente: ");
			scanf("%d", &id);
			if (findKey(root, id) == true) { 
			    current = find(root, id);
			    printf("Se encontro al paciente \n");
			    printf("Datos del paciente: %d %s %s %s %s\n", current->key, current->nombre, current->apellidos, 
			    	current->cancer, current->medicamento);
			}
			else {
			    printf(" Paciente no encontrado\n");
			}
	        break;
		case 2:
			system("clear");
	       	printf("\n\t+--------------------------------------------------------+");
	       	printf("\n\t| Buscar por valores Mayores a la ID o excatamente la ID |");
	        printf("\n\t+--------------------------------------------------------+\n");
	        printf("\n introduzca ID del paciente: ");
			scanf("%d", &id);
			if (findKey(root, id) == true) { 
				printf("Datos del paciente o cercanos a el \n");
			    current = find(root, id);
			    tmp = findMax(root);
			    printRange(root, id, tmp->key);
			}
			else {
				printf(" Paciente no encontrado\n");
			}
	       	break;
		case 3:
			system("clear");
	       	printf("\n\t+--------------------------------------------------------+");
	       	printf("\n\t| Buscar por valores Menores a la ID o excatamente la ID |");
	       	printf("\n\t+--------------------------------------------------------+\n");
	       	printf("\n introduzca ID del paciente: ");
			scanf("%d", &id);
			if (findKey(root, id) == true) { 
				printf("Datos del paciente o cercanos a el \n");
			    current = find(root, id);
			    tmp = findMin(root);
			    printRange(root, tmp->key, id);
			}
			else {
				printf(" Paciente no encontrado\n");
			}
	       	break;
		case 4:
			break;
	}
}

void menuBuscar() {
	int opcion, id;
	char name[20];
	char substring[20];
	printf("\n\t\t+-----------------+");
	printf("\n\t\t| Buscar paciente |");
	printf("\n\t\t+-----------------+\n");
	printf("\n 1. Buscar por ID del paciente ");
	printf("\n 2. Buscar por nombre del paciente ");
	printf("\n 3. Regresar menu principal \n");
	printf("\n Introduzca opcion (1-3): ");
	scanf("%d", &opcion);
	switch(opcion) {
	    case 1:
	    	menuBuscarID();
			break;
	    case 2:
	        system("clear");
	        printf("\n\t\t+--------------------------------+");
	        printf("\n\t\t| Buscar por nombre del paciente |");
	        printf("\n\t\t+--------------------------------+\n");
	        printf("\n 1. Buscar excatamente por el nombre del paciente ");
	        printf("\n 2. Buscar por sub palabra ");
	        printf("\n 3. Regresar menu Buscar \n");
	        printf("\n Introduzca opcion (1-3): ");
	        scanf("%d", &opcion);
	        switch(opcion) {
				case 1:
					system("clear");
					printf("\n\t\t+-----------------------------------------------+");
	       			printf("\n\t\t| Buscar excatamente por el nombre del paciente |");
	       			printf("\n\t\t+-----------------------------------------------+\n");
	       			printf("\n\t Ejemplo de se debe introducir: \n\t Nombre o Nombres del paciente: Jose_Humberto \n");
	       			printf(" Nombre o Nombres del paciente: ");
	       			scanf("%s", name);
	       			createlistAvl(root, &head);
	       			searchNameList(head, name);
	       			head = NULL;
	        		break;
				case 2:
					system("clear");
	       			printf("\n\t\t+------------------------+");
	       			printf("\n\t\t| Buscar por sub palabra |");
	        		printf("\n\t\t+------------------------+\n");
	        		printf("\n\t Ejemplo: ");
	        		printf("\n\t Nombre o Nombres del paciente: Jose_Humberto");
	        		printf("\n\t o apellidos del paciente: Gonzalez_Robles");
	        		printf("\n\t o medicamento del paciente: Paracetamol");
	       			printf("\n intruzca una palabra relacionada con un paciente: ");
	       			scanf("%s", name);
	       			createlistAvl(root, &head);
	       			searchApeList(head, name);
	       			searchMedList(head, name);
	       			head = NULL;
	        		break;
				case 3:
					break;
			}
	        break;
	 	case 3:
	    	break;
	}
}

void menuHerramientas() {
	int opcion;
	char confirmacion;
	char file[10] = "";
	printf("\n\t\t+------------------------------+");
	printf("\n\t\t| Herramientas administrativas |");
	printf("\n\t\t+------------------------------+\n");
	printf("\n 1. Guardar datos ");
	printf("\n 2. Leer desde otro archivo de datos txt");
	printf("\n 3. Regresar menu principal \n");
	printf("\n Introduzca opcion (1-3): ");
	scanf("%d", &opcion);
	switch(opcion) {
	    case 1:
	        system("clear");
	        printf("\n\t\t+----------------------------+");
	        printf("\n\t\t| Guardando datos ingresados |");
	        printf("\n\t\t+----------------------------+\n");  
  			printf("Ingrese El nombre del nuevo archivo a guardar: ");
  			scanf("%10s", file);
  			createBackup(root, file);
	        printf("Se han guardo con exito los datos en el archivo %s\n", file);
	        break; 
		case 2:
			system("clear");
	        printf("\n\t\t+--------------------------------------+");
	        printf("\n\t\t| Leer desde otro archivo de datos txt |");
	        printf("\n\t\t+--------------------------------------+\n");
	        printf("Ingrese El nombre del nuevo archivo a leer: ");
  			scanf("%10s", file);
  			printf("\n ¿Seguro que desea cargar ese nuevo archivo? (S/N) ");
	        scanf("%s", &confirmacion);
  			if (confirmacion == 'S' || confirmacion == 's') {
  				root = NULL;
	        	readNewData(file);
	        }
	        if (confirmacion == 'N' || confirmacion == 'n'){
	        	printf(" regreso al menu principal\n");
	        }
	    	break;
	    case 3:
	   		break;
	}
}

int main() {
	system("clear");
	int opcion;
	readData();
	do {
	    printf("\n\t\t+----------------------------------+");
	    printf("\n\t\t| Control de pacientes Oncológicos |");
	    printf("\n\t\t+----------------------------------+\n");
	    printf("\n 1. Ingresar paciente");
	    printf("\n 2. Eliminar Paciente");
	    printf("\n 3. Editar paciente");
	    printf("\n 4. Recuperar paciente");
	    printf("\n 5. Reporte Total");
	    printf("\n 6. Buscar");
	    printf("\n 7. Herramientas administrativas");
	    printf("\n 8. Salir\n");
	    printf("\n Introduzca opcion (1-8): ");
	    scanf("%d", &opcion);
	    switch (opcion) {
	        case 1:
	           	menuInsertar();
	            break;
	        case 2: 
	            menuEliminar();
	            break;
	        case 3:
	            menuEditar();
	            break;
	        case 4:
	            menuHabilitar();
	            break;
	        case 5:
	            menuReporte();
	            break;
	        case 6:
	            menuBuscar();
	            break;
	        case 7:
	            menuHerramientas();
	            break;
	        case 8:
	            printf(" Se han guardado los datos en el archivo data.txt\n");
	            break;
    	}
	} while (opcion != 8);
    return 0;
}