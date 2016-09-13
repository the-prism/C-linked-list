#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "def.h"
#include "data.h"
#include "fonction.h"

int main (int argc, char* argv[])
{
  /* FILE* fichier;
  struct maillon_t* debut;
  struct maillon_t* cat1;
  struct maillon_t* cat2;
  struct maillon_t* mail1;
  struct maillon_t* mail2;
  struct maillon_t* mail3;
  char* string;
  debut = creerMaillon();
  cat1 = creerMaillon();
  cat2 = creerMaillon();
  mail1 = creerMaillon();
  mail2 = creerMaillon();
  mail3 = creerMaillon();
  modifierSuivant(debut, cat1);
  modifierSuivant(cat1, cat2);
  modifierEnfant(cat1, mail1);
  modifierSuivant(mail1, mail2);
  modifierEnfant(cat2, mail3);
  string = creerData(10);
  modifierData(cat1, string);
  string = creerData(10);
  modifierData(cat2, string);
  string = creerData(10);
  modifierData(mail2, string);
  supprimerMaillon(debut);
  */
  char* string = "Recette [cat] [test] [mon] [criss] [d'enfant] [dechienne] [boab] [alpha]\n";
  char* string2 = "Motherfucher [cat]\n";
  char* string3 = "Est ce que sa marche [mon] [criss] [alpha]\n";
  char* string4 = "Zulu [cat] [mon]\n";
  char tab[10];
  char cat[10];
  struct maillon_t* debut;
  struct maillon_t* pt;
  struct maillon_t* re;
  // /*
  FILE* fichier;
  executionOk(argc);
  fichier = ouvertureFichier(argv[1]);
  debut = initData(fichier);
  // */

//  debut = creerMaillon();

  /* result = '\0';
  printf("Result:%s\nTab:%s\n", result, tab);

  while(*result != '\0')
  {
    result = getCategorie(result, cat);
    printf("Result:%s\n", result);
    printf("Cat:%s\n", cat);
  }
  result = getCategorie(result, cat);
  printf("R:%s\n", result);
  printf("S:%s\n", cat);
*/
 /*
  analyzeLigne(string, debut);
  analyzeLigne(string2, debut);
  analyzeLigne(string3, debut);
  analyzeLigne(string4, debut);
 */
  pt = obtenirSuivant(debut);

  while(pt != NULL)
  {
    printf("Categorie :%s\n", obtenirDonnees(pt));
    re = obtenirEnfant(pt);
    if(re != NULL)
    {
      while(re != NULL)
      {
        printf("Recette : %s\n", obtenirDonnees(re));
        re = obtenirSuivant(re);
      }
    }
    pt = obtenirSuivant(pt);
  }
  supprimerMaillon(debut);
  fermerFichier(fichier);
  printf("MON TABANAK\n" );
  return 0;
}
