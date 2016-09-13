#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "def.h"
#include "data.h"
#include "fonction.h"

int main (int argc, char* argv[])
{
  FILE* fichier;
  struct maillon_t* debut;
  struct maillon_t* ptcat = NULL;
  char saisie[BUFFER];
  short found = FALSE;
  executionOk(argc);
  fichier = ouvertureFichier(argv[1]);
  debut = initData(fichier);
  printf("Bienvenue dans le logiciel de recherche de reccette\nVeuillez saisir :q pour quitter.\n");
  while(strcasecmp(saisie,":q") != 0)
  {
    printf("Entrez votre critère de recherche : ");
    fgets(saisie, BUFFER, stdin);
    saisie[(strlen(saisie)-1)] = '\0';
    if(strcasecmp(saisie,":q") != 0)
    {
      ptcat = obtenirSuivant(debut);
      found = rechercheCategorie(ptcat, saisie);
      if(found != TRUE)
      {
        found = rechercheRecette(ptcat, saisie);
      }
      if(found == FALSE)
      {
        notFound(saisie);
      }
      found = FALSE;
    }
  }
  supprimerMaillon(debut);
  fermerFichier(fichier);
  return 0;
}

short rechercheCategorie(struct maillon_t* debut, char* string)
{
  struct maillon_t* cat = debut;
  struct maillon_t* rec;
  short found = FALSE;
  while(cat != NULL && found != TRUE)
  {
    if(strncasecmp(string, obtenirDonnees(cat), strlen(string)) == 0)
    {
      rec = obtenirEnfant(cat);
      while(rec != NULL)
      {
        printf("Recette : %s\n", obtenirDonnees(rec));
        rec = obtenirSuivant(rec);
      }
      found = TRUE;
    }
    else
    {
      cat = obtenirSuivant(cat);
    }
  }
  return found;
}

short rechercheRecette(struct maillon_t* debut, char* string)
{
  struct maillon_t* cat = debut;
  struct maillon_t* rec;
  short found = FALSE;
  while(cat != NULL && found != TRUE)
  {
    rec = obtenirEnfant(cat);
    while(rec != NULL)
    {
      if(strncasecmp(string, obtenirDonnees(rec), strlen(string)) == 0)
      {
        printf("%s\n", obtenirDonnees(rec));
        found = TRUE;
      }
      rec = obtenirSuivant(rec);
    }
    cat = obtenirSuivant(cat);
  }
  return found;
}

void notFound(char* saisie)
{
  short i;
  short space = FALSE;
  for(i = 0; i < strlen(saisie); i++)
  {
    if(saisie[i] == ' ')
    {
      space = TRUE;
    }
  }
  if(space == FALSE)
  {
    printf("Catégorie inexistante.\n");
  }
  else
  {
    printf("Aucun résultat trouvé.\n");
  }
}
