/******************************************************************************/
/*			Application: ...					*/
/******************************************************************************/
/*									      */
/*			 programme  CLIENT				      */
/*									      */
/******************************************************************************/
/*									      */
/*		Auteurs : ... 					*/
/*									      */
/******************************************************************************/	


#include <stdio.h>
#include <curses.h> 		/* Primitives de gestion d'ecran */
#include <sys/signal.h>
#include <sys/wait.h>
#include<stdlib.h>
#include<string.h>

#include "fon.h"   		/* primitives de la boite a outils */

#define SERVICE_DEFAUT "1111"
#define SERVEUR_DEFAUT "127.0.0.1"
#define TAILLE_BUFFER 1024

void client_appli (char *serveur, char *service);


/*****************************************************************************/
/*--------------- programme client -----------------------*/

int main(int argc, char *argv[])
{

	char *serveur= SERVEUR_DEFAUT; /* serveur par defaut */
	char *service= SERVICE_DEFAUT; /* numero de service par defaut (no de port) */


	/* Permet de passer un nombre de parametre variable a l'executable */
	switch(argc)
	{
 	case 1 :		/* arguments par defaut */
		  printf("serveur par defaut: %s\n",serveur);
		  printf("service par defaut: %s\n",service);
		  break;
  	case 2 :		/* serveur renseigne  */
		  serveur=argv[1];
		  printf("service par defaut: %s\n",service);
		  break;
  	case 3 :		/* serveur, service renseignes */
		  serveur=argv[1];
		  service=argv[2];
		  break;
    default:
		  printf("Usage:client serveur(nom ou @IP)  service (nom ou port) \n");
		  exit(1);
	}

	/* serveur est le nom (ou l'adresse IP) auquel le client va acceder */
	/* service le numero de port sur le serveur correspondant au  */
	/* service desire par le client */
	
	client_appli(serveur,service);
}

/*****************************************************************************/
void client_appli (char *serveur,char *service)

/* procedure correspondant au traitement du client de votre application */

{
	int socket = h_socket(AF_INET, SOCK_STREAM);
	struct sockaddr_in *adr_serveur = malloc(sizeof(struct sockaddr_in));
	adr_socket(service, serveur, SOCK_STREAM, &adr_serveur);
	h_connect(socket, adr_serveur);

	char* buffer = malloc(TAILLE_BUFFER);
	//On lit le nombre de lettres à deviner
	int read = h_reads(socket, buffer, TAILLE_BUFFER);
	if(read == -1) {
		printf("Erreur\n");
		exit(1);
	}
	if(read == 0) {
		printf("Fin de la communication\n");
		exit(1);
	}
	int longueur_mot = atoi(buffer);
	printf("Nombre de lettres à deviner: %d\n", longueur_mot);
	char* mot = malloc(longueur_mot);
	for(int i = 0; i < longueur_mot; i++) {
		mot[i] = '_';
	}
	while(1) {
		printf("%s\n", mot);
		printf("Entrez une lettre: ");
		fgets(buffer, TAILLE_BUFFER, stdin);

		h_writes(socket, buffer, TAILLE_BUFFER);
		read = h_reads(socket, buffer, TAILLE_BUFFER);
		if(read == -1) {
			printf("Erreur\n");
			break;
		}
		if(read == 0) {
			printf("Fin de la communication\n");
			break;
		}
		printf("Message recu: %s\n", buffer);
		if(strcmp(buffer, "GAGNE") == 0) {
			printf("GAGNE\n");
			break;
		}
		if(strcmp(buffer, "PERDU") == 0) {
			printf("PERDU\n");
			break;
		}
		for(int i = 0; i < longueur_mot; i++) {
			mot[i] = buffer[i];
		}
	}
	h_close(socket);
}

/*****************************************************************************/

