#ifndef FONCTION_H
#define FONCTION_H
#define BUFFER 120

void copieString(char* chaine1, char* chaine2)
{
  printf("%s\n", "Non implémenté"); // Voir si fonction vraiment utile. !!!
}

void executionOk(int argc)
{
  if (argc != 2)
  {
    printf("Paramètre manquant lors de l'exécution\n");
    exit(1);
  }
}

FILE* ouvertureFichier(char* filename)
{
  FILE* filePointeur = fopen(filename, "r");
  if(filePointeur == NULL)
  {
    printf("Erreur lors de l'ouverture du fichier : %d\n", errno);
    exit(1);
  }
  return filePointeur;
}

void fermerFichier(FILE* fichier)
{
  int fermetture = fclose(fichier);
  if(fermetture != 0)
  {
    printf("Erreur lors de la fermetture du fichier : %d\n", errno);
    exit(1);
  }
}

struct maillon_t* initData(FILE* fichier)
{
  struct maillon_t* start = creerMaillon();
  char buffer[BUFFER];
  char* ligne = buffer;
  while (ligne != NULL)
  {
    ligne = lectureLigne(fichier, ligne, BUFFER);
    if(ligne != NULL)
    {
      analyzeLigne(ligne, start);
    }
  }
  free(ligne);
  return start;
}

char* lectureLigne(FILE* fichier, char* buffer, int taille)
{
  char* test;
  test = fgets(buffer, taille, fichier);
  if(test == NULL)
  {
    buffer = NULL;
  }
  return buffer;
}

void analyzeLigne(char* ligne, struct maillon_t* debut)
{
  struct maillon_t* maillon = creerMaillon();
  char** cat = calloc(1,sizeof(char*));
  char recetteBuffer[BUFFER];
  char* data;
  char* reste;
  short nbCat = 0;
  short i = 0;
  if(ligne != NULL)
  {
    reste = getRecette(ligne, recetteBuffer);
    data = creerData(strlen(recetteBuffer)+1);
    strcpy(data, recetteBuffer);
    while (reste != NULL && *reste != '\0')
    {
      cat[nbCat] = creerData(strlen(reste));
      reste = getCategorie(reste, cat[nbCat]);
      if(reste != NULL && *reste != '\0')
      {
        nbCat++;
        cat = realloc(cat, (nbCat+1) * sizeof(char*));
      }
    }
    for (i = 0; i < nbCat; i++) {
      if(strlen(cat[i]) >= 2)
        ajoutCategorie(debut, cat[i], data);
      free(cat[i]);
    }
    free(cat[nbCat]);
    free(data);
    free(cat);
    free(maillon);
  }
}

char* getRecette(char* string, char* recette)
{
  char buffer[BUFFER];
  char* result;
  char cbuff;
  short count = 0;
  short char2;
  while (cbuff != '[' && count < BUFFER)
  {
    cbuff = string[count];
    buffer[count] = cbuff;
    count++;
  }
  count--;
  char2 = count - 1;
  if(buffer[count] == '[' && buffer[char2] == ' ')
  {
    buffer[char2] = '\0';
    result = string + char2;
  }
  else if (buffer[count] == '[')
  {
    buffer[count] = '\0';
    result = string + count;
  }
  strcpy(recette, buffer);
  return result;
}

char* getCategorie(char* string, char* categorie)
{
  char* result;
  char buffer[BUFFER];
  short count1 = 0;
  short count2 = 0;
  char cbuff = string[0];
  if(cbuff == '\0')
    return NULL;

  if((cbuff = ']'))
  {
    count1++;
    cbuff = string[count1];
  }
  while(cbuff != ']' && cbuff != '\n' && cbuff != '\r' && cbuff != '\0')
  {

    cbuff = string[count1];
    if(cbuff != '[' && cbuff != ']' && cbuff != '\n' && cbuff != '\r' && cbuff != '\0' && cbuff != ' ')
    {
      buffer[count2] = cbuff;
      count1++;
      count2++;
    }
    else if ((cbuff == '[' || cbuff == ' ') && cbuff != '\n' && cbuff != '\r' && cbuff != '\0')
    {
      count1++;
    }
  }
  buffer[count2] = '\0';
  result = string + count1;
  strcpy(categorie, buffer);
  return result;
}

void ajoutCategorie(struct maillon_t* debut, char* string, char* data)
{
  struct maillon_t* categorie;
  struct maillon_t* enfant;
  char* stringData;
  if(obtenirSuivant(debut) == NULL && obtenirEnfant(debut) == NULL)
  {
    categorie = creerMaillon();
    modifierSuivant(debut, categorie);
    stringData = creerData(strlen(string) +1);
    strcpy(stringData, string);
    modifierData(categorie, stringData);
    stringData = creerData(strlen(data)+1);
    strcpy(stringData, data);
    enfant = creerMaillon();
    modifierData(enfant, stringData);
    modifierEnfant(categorie, enfant);
  }
  else
  {
    categorie = catExiste(debut, string);
    if (categorie != NULL)
    {
      addRecAlph(categorie, data);
    }
    else
    {
      categorie = addCatAlph(debut, string);
      enfant = reExiste(categorie, data);
      if(enfant == NULL)
      {
        addRecAlph(categorie, data);
      }
    }
  }

}

struct maillon_t* catExiste(struct maillon_t* debut, char* string)
{
  struct maillon_t* pointeur = debut;
  char buffer[BUFFER];
  short value = FALSE;
  while(pointeur != NULL && value != TRUE)
  {
    pointeur = obtenirSuivant(pointeur);
    if( pointeur != NULL)
    {
      if (obtenirDonnees(pointeur) != NULL)
      {
        strcpy(buffer, obtenirDonnees(pointeur));
        if ( strcasecmp(buffer,string) == 0 )
        {
          value = TRUE;
        }
      }
    }
  }
  if(value == TRUE)
    return pointeur;
  else
    return NULL;
}

struct maillon_t* reExiste(struct maillon_t* cat, char* string)
{
  struct maillon_t* pointeur = obtenirEnfant(cat);
  char buffer[BUFFER];
  short value = FALSE;
  while(pointeur != NULL && value != TRUE)
  {
    if( pointeur != NULL)
    {
      if (obtenirDonnees(pointeur) != NULL)
      {
        strcpy(buffer, obtenirDonnees(pointeur));
        if ( strcasecmp(buffer,string) == 0 )
        {
          value = TRUE;
        }
      }
    }
    pointeur = obtenirSuivant(pointeur);
  }
  if(value == TRUE)
    return pointeur;
  else
    return NULL;
}

struct maillon_t* addCatAlph(struct maillon_t* debut, char* string)
{
  struct maillon_t* pointeur = obtenirSuivant(debut);
  struct maillon_t* pointeur2 = debut;
  char* data;
  short value = FALSE;
  short compare;
  while(value != TRUE && pointeur != NULL)
  {
    if(pointeur != NULL)
    {
      if(obtenirDonnees(pointeur) != NULL)
      {
        compare = strcasecmp(string, obtenirDonnees(pointeur));
        if (compare > 0)
        {
          pointeur2 = pointeur;
        }
        pointeur = obtenirSuivant(pointeur);
      }
      else
      {
        value = TRUE;
      }
    }
  }
  if(pointeur2 != NULL)
  {
    pointeur = creerMaillon();
    data = creerData(strlen(string) +1);
    strcpy(data, string);
    modifierData(pointeur, data);
    insererMaillon(pointeur2, pointeur);
  }
  return pointeur;
}

struct maillon_t* addRecAlph(struct maillon_t* cat, char* string)
{
  struct maillon_t* pointeur = obtenirEnfant(cat);
  struct maillon_t* pointeur2 = cat;
  char* data;
  short value = FALSE;
  short compare;
  while(value != TRUE && pointeur != NULL)
  {
    if(pointeur != NULL)
    {
      if(obtenirDonnees(pointeur) != NULL)
      {
        compare = strcasecmp(string, obtenirDonnees(pointeur));
        if (compare > 0)
        {
          pointeur2 = pointeur;
        }
        pointeur = obtenirSuivant(pointeur);
      }
      else
      {
        value = TRUE;
      }
    }
  }
  if(pointeur2 != NULL && pointeur2 != cat)
  {
    pointeur = creerMaillon();
    data = creerData(strlen(string) +1);
    strcpy(data, string);
    modifierData(pointeur, data);
    insererMaillon(pointeur2, pointeur);
  }
  else if(pointeur2 == cat)
  {
    pointeur = creerMaillon();
    data = creerData(strlen(string) +1);
    strcpy(data, string);
    modifierData(pointeur, data);
    insererEnfant(pointeur2, pointeur);
  }
  return pointeur2;
}

#endif
