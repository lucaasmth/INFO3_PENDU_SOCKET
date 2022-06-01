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
#include<string.h>
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
	int lenMot = strlen(mot);

	char* res = malloc(sizeof(char) * lenMot);
	for (int i = 0; i <lenMot ; i++)
	{
		res[i] = '-';
	}
	
	int LettresTrouvees = 0;
	int NbEssais = 10;
	while (1)
	{
		char lettrerecue;
		int boolTrouve = 0;
		for (int i = 0; i < lenMot; i++) {

			if (lettrerecue == mot[i]) {
				res[i] == lettrerecue;
				LettresTrouvees++;
				boolTrouve = 1;
			}
		}

		//Dis au client qu'il a trouvé une lettre
		//Envoi au client le tableau res mis à jour
		if (boolTrouve = 0)
			NbEssais--;

		if (NbEssais == 0)
		{
			//Perdu
			//Afficher le résultat qu'il fallait trouver
			break;
		}
		
		if(LettresTrouvees == lenMot){
			//
			// Gagné
			break;
		}
	}
	



}

/******************************************************************************/	

