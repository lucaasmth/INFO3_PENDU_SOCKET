/******************************************************************************/
/*			Application: ....			              */
/******************************************************************************/
/*									      */
/*			 programme  SERVEUR 				      */
/*									      */
/******************************************************************************/
/*									      */
/*		Auteurs :  ....						      */
/*		Date :  ....						      */
/*									      */
/******************************************************************************/	

#include<stdio.h>
#include <curses.h>

#include<sys/signal.h>
#include<sys/wait.h>
#include<stdlib.h>

#include "fon.h"     		/* Primitives de la boite a outils */

#define SERVICE_DEFAUT "1111"

void serveur_appli (char *service);   /* programme serveur */


/******************************************************************************/	
/*---------------- programme serveur ------------------------------*/

int main(int argc,char *argv[])
{

	char *service= SERVICE_DEFAUT; /* numero de service par defaut */


	/* Permet de passer un nombre de parametre variable a l'executable */
	switch (argc)
 	{
   	case 1:
		  printf("defaut service = %s\n", service);
		  		  break;
 	case 2:
		  service=argv[1];
            break;

   	default :
		  printf("Usage:serveur service (nom ou port) \n");
		  exit(1);
 	}

	/* service est le service (ou numero de port) auquel sera affecte
	ce serveur*/
	
	serveur_appli(service);
}


/******************************************************************************/	
void serveur_appli(char *service)

/* Procedure correspondant au traitemnt du serveur de votre application */

{
	struct sockaddr_in *p_adr_socket;
	adr_socket(service, NULL, SOCK_STREAM, &p_adr_socket);
	int SocketServer = h_socket(AF_INET, SOCK_STREAM);
	if (SocketServer == -1) {
		printf("Impossible de créer la socket > Fin\n");
		return;
	}
	h_bind(SocketServer, p_adr_socket);
	h_listen(SocketServer, 1);
	int SocketClient = h_accept(SocketServer, p_adr_socket);

	char** dictionnaire = malloc(sizeof(char) * 10 * 15);
	dictionnaire[0] = "anniversaire";
	dictionnaire[1] = "hospitalier";
	dictionnaire[2] = "destructeur";
	dictionnaire[3] = "intimidation";
	dictionnaire[4] = "redemption";
	dictionnaire[5] = "souris";
	dictionnaire[6] = "table";
	dictionnaire[7] = "decapition";
	dictionnaire[8] = "anticipation";
	dictionnaire[9] = "invertebres";

	char joues[26] = {0};

	srand(time(NULL));
	char* mot = dictionnaire[rand() % 10];

	char *buff = malloc(sizeof(char) * 100);
	sprintf(buff, "%d", nblettres);
	h_writes(SocketClient, buff, 2);





}

/******************************************************************************/	

