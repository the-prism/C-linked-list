#ifndef DATA_H
#define DATA_H

/**
* Type boolean, FALSE = 0 TRUE = 1
*/
enum Boolean_t {FALSE,TRUE};

/**
* Structure de maillon de la liste chainée
*/
struct maillon_t
{
  char* data;
  struct maillon_t* suivant;
  struct maillon_t* enfant;
};

struct maillon_t* obtenirSuivant(struct maillon_t* maillon)
{
  return maillon->suivant;
}

struct maillon_t* obtenirEnfant(struct maillon_t* maillon)
{
  return maillon->enfant;
}

char* obtenirDonnees(struct maillon_t* maillon)
{
  return maillon->data;
}

void modifierSuivant(struct maillon_t* maillon, struct maillon_t* maillon2)
{
  maillon->suivant = maillon2;
}

void modifierEnfant(struct maillon_t* maillon, struct maillon_t* maillon2)
{
  maillon->enfant = maillon2;
}

void modifierData(struct maillon_t* maillon, char* string)
{
  maillon->data = string;
}

void insererMaillon(struct maillon_t* maillon, struct maillon_t* insert)
{
  struct maillon_t* suite = obtenirSuivant(maillon);
  modifierSuivant(maillon, insert);
  modifierSuivant(insert, suite);
}

void insererEnfant(struct maillon_t* maillon, struct maillon_t* insert)
{
  struct maillon_t* suite = obtenirEnfant(maillon);
  modifierEnfant(maillon, insert);
  modifierSuivant(insert, suite);
}

struct maillon_t* creerMaillon()
{
  struct maillon_t* maillon = malloc(sizeof(struct maillon_t));
  maillon->data = NULL;
  maillon->suivant = NULL;
  maillon->enfant = NULL;
  return maillon;
}

char* creerData(int taille)
{
  char* string = calloc(taille,sizeof(char));
  return string;
}

void supprimerMaillon(struct maillon_t* maillon)
{
  if(maillon->data == NULL && maillon->suivant == NULL && maillon->enfant == NULL)
  {
    free(maillon);
    /* Vérification d'erreur */
  }
  else
  {
    if(maillon->data !=NULL)
    {
      supprimerData(maillon->data);
    }
    if(maillon->suivant != NULL)
    {
      supprimerMaillon(maillon->suivant);
    }
    if(maillon->enfant != NULL)
    {
      supprimerMaillon(maillon->enfant);
    }
    free(maillon);
  }
}

void supprimerData(char* string)
{
  if(string != NULL)
  {
    free(string);
    /*Vérification d'erreur*/
  }
}

#endif
