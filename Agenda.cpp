#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include "Func_Cont.h"

char Nombres[6][10]={"Juan", "Lucas", "Maria", "Ana", "Pablo", "Santiago"};
char Apellidos[6][10]={"Mendoza", "Olivarez", "Cardozo", "Diaz", "Aguirre", "Sosa"};

typedef struct Agenda{
	char *ApellidoyNombre;
	int telefono;
} Agenda;

typedef struct Nodo{
	Agenda *Datos_Personas;
	Nodo *Siguiente;
	int id_Cont;	
}Nodo;

typedef struct Lista{
	Nodo *head; //Apunta al inicio de la lista
	int id_actual;
} Lista;


//------------------------------------------------Declaracion de Funciones------------------------------------------------
void CrearLista(Lista *L);
void Crear_Contacto(Agenda **Persona);
void Cargar_Datos(Agenda *Persona);
void Mostrar_Datos(Agenda *Persona);
void Mostrar_Lista (Lista *Lista);
void InsertarAlFinal (Lista *L, Agenda * Persona);
int esListaVacia(Lista *L);
void Menu(Lista *L);
void Resultado_Busqueda(Lista *L);
Nodo *Buscar_Contacto(Lista *L, int Numero);
void Eliminar_Contacto(Lista *L);
//------------------------------------------------------------------------------------------------------------------------

int main(void){
	Lista *Contactos;
	Agenda *Nuevo;

	int cant_cont;

	cant_cont = cantidad_cont();
	CrearLista(Contactos);
	srand(time(NULL));

	for (int i = 0; i < cant_cont; ++i){
		//Creo el contacto
		Crear_Contacto(&Nuevo);
		InsertarAlFinal(Contactos, Nuevo);
	}
	 Mostrar_Lista(Contactos);
	 Pausa();
	 Menu(Contactos); 

	return 0;
}
void Menu(Lista *L){
	int opcion, cant;
	char seguir;
	Agenda *Nuevo;

	do{
	    opcion = opcion_menu();
		switch(opcion){
		   case 1:
		     Resultado_Busqueda(L);
		     break;
		   case 2:
		     //Agregar_Contacto();
		     cant = cantidad_cont();
		     for (int i = 0; i < cant; ++i){
		     	Crear_Contacto(&Nuevo);
		     	InsertarAlFinal (L, Nuevo);
		     	Mostrar_Lista(L);
		     }
		     break;
		   case 3:
		      Eliminar_Contacto(L);
		      Mostrar_Lista(L);
		     break;
	    }
	    seguir=seguir_prom();
	    if (seguir == 'N' || seguir == 'n'){
	    	final();
	    }
	}while(seguir == 'S' || seguir == 's');
} 

//--------------------------Funciones de lista
void CrearLista(Lista *L){
	L->head=NULL;
	L->id_actual = 1;
}
void Mostrar_Lista (Lista *Lista) {
	//Muestra los elementos de la lista
	Nodo * p_aux = Lista->head;

	if (p_aux == NULL) {
		printf("(Sin Contactos)\n");
	}
	else{
		while (p_aux != NULL) {
			printf("------Contacto Nº[%d]\n", p_aux->id_Cont);
			Mostrar_Datos(p_aux->Datos_Personas);
			printf("\n");
			p_aux = p_aux->Siguiente;
		}
	}
}
void InsertarAlFinal (Lista *L, Agenda * Persona){
	//Inserta un nuevo nodo al principio de la lista con el valor ingresado
	Nodo *nuevo, *p_aux;
	p_aux = L->head;

	nuevo = (Nodo*)malloc(sizeof(Nodo));

	nuevo->Datos_Personas = Persona;
	nuevo->id_Cont = L->id_actual;
	nuevo->Siguiente = NULL;

	if (esListaVacia(L)) L->head = nuevo;
	else {
		while (L->head->Siguiente != NULL) {
			L->head = L->head->Siguiente;		
		}
		L->head->Siguiente = nuevo;
		L->head = p_aux; //Regresa a la direccion original
	}
	L->id_actual++;
}

int esListaVacia (Lista *L){
	//Booleano
	//Retorna 1 si la lista es vacia
	return (L->head == NULL);
}

Nodo *Buscar_Contacto(Lista *L, int Numero){
	Nodo *Aux = L->head;

	while(Aux !=NULL){
		if (Aux->Datos_Personas->telefono == Numero){
			return Aux;
		}
		Aux = Aux->Siguiente;
	}
	return Aux;
}
void Resultado_Busqueda(Lista *L){
	Nodo *Cont_Bus;
	int Numero = Num_contacto();

	Cont_Bus = Buscar_Contacto(L, Numero);
	printf("\n--Datos: \n");
	printf("Apellido y Nombre: %s\n", Cont_Bus->Datos_Personas->ApellidoyNombre);
	printf("Numero de Tel/Cel: %d\n", Cont_Bus->Datos_Personas->telefono);
}
void EliminarX(Lista *L){
	Nodo *Nodo;
	//int Numero = Num_contacto();
	//Nodo = Buscar_Contacto(L, Numero);

    if (!Nodo){
    	printf("Contacto Eliminado\n");
    	Nodo = L->head;
    	L->head = L->head->Siguiente;
    	free(Nodo);
    }
}
void Eliminar_Contacto (Lista *L) {
	int Numero = Num_contacto();
	Nodo *P_Aux, *Ant, *Sig;
	P_Aux = L->head;

	if (esListaVacia(L)) {
		printf("No hay elementos para borrar\n");
	}
	else {
		if (P_Aux->Siguiente == NULL) {
			//La lista tiene un solo elemento
			if (P_Aux->Datos_Personas->telefono == Numero) {
				//El elemento es el buscado
				EliminarX(L);
			}
			else {
				//El elemento no es el buscado
				printf("No se encontro el elemento\n");
			}
		}
		else {
			//La lista tiene mas de un elemento
			if (P_Aux->Datos_Personas->telefono == Numero){
				//El elemento a borrar es el primero
				EliminarX(L);
			}
			else {
				Ant = P_Aux;
				P_Aux = P_Aux->Siguiente;
				Sig = P_Aux->Siguiente;

				while (Sig != NULL && P_Aux->Datos_Personas->telefono != Numero) {
					Ant = P_Aux;
					P_Aux = P_Aux->Siguiente;
					Sig = P_Aux->Siguiente;					
				}

				if (P_Aux->Datos_Personas->telefono == Numero) {
					//Se encontró el elemento a eliminar
					Ant->Siguiente = Sig;
					free(P_Aux);
				}
				else {
					//No se encontró el elemento a eliminar
					printf("No se encontro el elemento\n");
				}
			}
		}
	}
}


//--------------------------Funciones para cargar los datos
void Crear_Contacto(Agenda **Persona) {
	*Persona = (Agenda*)malloc(sizeof(Agenda));
	Cargar_Datos(*Persona);
}

void Cargar_Datos(Agenda *Persona){
	Persona->ApellidoyNombre=(char*)malloc(40);
	strcpy((Persona->ApellidoyNombre), Apellidos[rand()%6]);
 	strcat((Persona->ApellidoyNombre), ", ");
 	strcat((Persona->ApellidoyNombre),Nombres[rand()%6]);
 	Persona->telefono = 1500000000 + rand()%(3999999999);
}
void Mostrar_Datos(Agenda *Persona){
	printf("Apellido y Nombre: %s\n",Persona->ApellidoyNombre);
	printf("Numero de Tel/Cel: %d\n", Persona->telefono);
}
