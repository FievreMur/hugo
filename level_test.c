/**
 * \file level.c
 * \brief Programme pour les level.
 * \author Quentin.L
 *
 * Programme pour recuperer un level dans le fichier source des level et le stocker dans un tableau a double entrée.
 * On recuper aussi la postion du manutencier.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
/**
 * \def MAX_LIGNE
 * \brief Définit le nombre max de caratere des ligne du fichier levels.lvl : 100.
*/

int level_choisi()
{
	int level=1;
	printf("Donner un level : ");
	scanf("%d",&level);
	printf("Level choisi : %d\n",level);
	return level;
}


/**
 * \fn void init_tableau(char tab[], int taille_ligne)
 * \brief fonction pour initialiser un tableau de char a 1 entrée.
 *
 * \param tab Tableau a initialiser.
 * \param taille_ligne Taille des ligne du tableau
 * \return Pas de return car fonction void.
 */
void init_tableau(char tab[], int taille_ligne)
{
	for(int i=0; i<=taille_ligne; i++)
	{
		tab[i]='\0';
	}
}


/**
 * \fn void init_tableau2(char** tab, int taille_ligne , int taille_collone)
 * \brief Fonction pour initialiser un tableau de char a 2 entrée.
 *
 * \param tab Tableau a initialiser.
 * \param taille_ligne Nombre de ligne du tableau.
 * \param taille_collone Taille des collones du tableau.
 * \return Pas de return car fonction void.
 */
void init_tableau2(char** tab, int taille_ligne , int taille_collone)
{

	printf("ici ca va\n");

	for(int i=0; i<taille_ligne; i++)
	{
		for(int j=0; j<taille_collone; j++)
		{
			tab[i][j]='\0';

		}
	}
}


/**
 * \fn void afficher_tableau2(char** tab, char nbr_ligne, char taille_collone)
 * \brief Fonction pour afficher un tableau de char a 2 entrée.
 *
 * \param tab Tableau a afficher.
 * \param taille_ligne Nombre de ligne du tableau.
 * \param taille_collone Taille des collones du tableau.
 * \return Pas de return car fonction void.
 */
void afficher_tableau2(char** tab, int nbr_ligne)
{
	for(int i=0; i<nbr_ligne; i++)
	{
		printf("%s", tab[i]);
	}
}


/**
 * \fn void tableau_level(int nb_ligne, int ligne_debut, int taille_ligne)
 * \brief Fonction qui permet stocker le level dans un tableau.
 *
 * \param tab Tableau a double entree ou seront stocker la map.
 * \param ligne_debut Ligne de debut du niveau dans le fichier levels.lvl.
 * \return Pas de return car fonction void.
 */
void tableau_level(char** tab, int caractere_depart, int nb_ligne,int ligne_plus_grande)
{
	FILE *fichier= NULL;
	char ligne[ligne_plus_grande];
	//init_tableau(ligne,ligne_plus_grande);

	init_tableau2(tab,nb_ligne,ligne_plus_grande);
	fichier = fopen("levels.lvl", "r");
    if ( fichier == NULL ) {
        printf( "Cannot open file");
        exit(EXIT_FAILURE);
    }

/*On place le curseur au debut du level*/
	int returnCode = fseek(fichier, caractere_depart, SEEK_SET);
	if (returnCode != 0)
	{
				printf("Changement de position impossible");
				fclose(fichier);
				exit(EXIT_FAILURE);
	}

	printf("nombre de lignes : %d\n", nb_ligne);
	for(int j=0;j<nb_ligne;j++){

			fgets(tab[j],ligne_plus_grande+1,fichier);
	}

	fclose(fichier);
}


/**
 * \fn void ligne_tableau()
 * \brief Fonction qui permet de recupere les infos de la postion du level dans le fichier.
 *
 * \return Pas de return car fonction void.
 */
int ligne_tableau(int level_choisi,int *nb_ligne, int *caractere_depart, int* ligne_plus_grande, int *x, int* y)
{
	FILE* fichier= NULL;
	int caractere_actuel;

	int controle_level=';';
	int controle_linge='\n';

	int compteur_ligne=0;
	int level_trouver=0;

	*nb_ligne = 0;
	*caractere_depart = 0;
	*ligne_plus_grande = 0;

	fichier = fopen("levels.lvl","r");
		if ( fichier == NULL )
		{
				printf( "Le fichier ne peut etre ouvert");
				exit(EXIT_FAILURE);
		}

		/*Concatenation du level choisi avec le string "LEVEL " */
	char level[10];
	snprintf(level,10,"LEVEL %d",level_choisi);

	char verif_level[strlen(level)];
	init_tableau(verif_level,strlen(level));

	/*Fonction qui compte le nombre de caractere avant le debut du niveau*/
	while(1)
	{
		caractere_actuel=fgetc(fichier);
		(*caractere_depart)++;
		if(caractere_actuel==controle_level)
			{
				fgets(verif_level,strlen(level)+1,fichier);
				if(strcmp(verif_level,level)==0)
				{
					if(level_choisi>=10) //le caractere de depart est un caractere avant si le level est superieur a 10
										{
												(*caractere_depart)+=strlen(verif_level)-1;
										}
					else
										{
												 (*caractere_depart)+=strlen(verif_level);
										}
					level_trouver=1;
					break;
				}
				else
				{
					(*caractere_depart)+=strlen(level);
				}
			}
				if(caractere_actuel==EOF)
				{
						printf("Level introuvable ressayer.\n");
						break;
				}
	}
	if(level_trouver==1)
	{
		caractere_actuel=fgetc(fichier); /* On recupere le dernier caratere du saut de ligne */

		while(1)
		{
			caractere_actuel=fgetc(fichier);
			if(caractere_actuel==controle_level)
			{
					while(caractere_actuel!=controle_linge)
					{
								(*caractere_depart)++;
								caractere_actuel=fgetc(fichier);
					}
					(*caractere_depart)++;
			 }
			 else
			 {
				break;
			 }
		 }
		 
		 
		 /*Fonction qui compte le nombre de ligne et la ligne la plus grande du level*/
		 while(1)
		 {
			 	
				caractere_actuel=fgetc(fichier);
				compteur_ligne++;
				
				

				if(caractere_actuel == '@')
				{
						*y = *nb_ligne;
						*x = compteur_ligne-1;
				}

				if(caractere_actuel==controle_linge)
				{
						 (*nb_ligne)++;

						 if(*ligne_plus_grande<compteur_ligne)
						 {
									*ligne_plus_grande=compteur_ligne;
						 }
						 compteur_ligne=0;
				}
				if(caractere_actuel==controle_level||caractere_actuel==EOF)
				{
						break;
				}
			}
			*ligne_plus_grande += 1;
		}


	fclose(fichier);
	return level_trouver;
}

/**
 * \fn void iniatilisation_jeu(char** tab)
 * \brief Initialise le jeu en renvoyant la position du manutencier au depart, le level de depart et un tableau permetant la modifiction pour le jeu.
 *
 * \return Pas de return car fonction void.
 */
 /*
int  main(int argc, char *argv[])
{
    ligne_tableau();
    //creation du tableau de depart
    char **tab_init= malloc(sizeof(*tab_init) * nb_ligne);

    for (int i = 0; i < 20; i++)
    {
        tab_init[i] = malloc(sizeof(**tab_init) * ligne_plus_grande);
    }

    //creation du talbeau pour les modification
    char **tab_jeu= malloc(sizeof(*tab_jeu) * nb_ligne);

    for (int i = 0; i < 20; i++)
    {
        tab_jeu[i] = malloc(sizeof(**tab_jeu) * ligne_plus_grande);
    }

    // Remplissage des tableau
    tableau_level(tab_init,ligne_depart);
    tableau_level(tab_jeu,ligne_depart);

    afficher_tableau2(tab_init,nb_ligne,ligne_plus_grande);
    //afficher_tableau2(tab_jeu,nb_ligne,ligne_plus_grande);
    return EXIT_SUCCESS;
}
*/
