#ifndef DEF_H
#define DEF_H

/**
* Fonction qui retourne le prochain élément de la chaine
* @maillon: maillon de la chaine
* @return: maillon suivant de la chaine
*/
struct maillon_t* obtenirSuivant(struct maillon_t* maillon);

/**
* Fonction qui retourne un maillon enfant si l'objet est une catégorie
* @maillon: maillon de la catégorie
* @return: premier enfant de la catégorie
*/
struct maillon_t* obtenirEnfant(struct maillon_t* maillon);

/**
* Fonction qui permet d'obtenir le contenu
* @maillon: maillon qu'on veut obtenir l'information
*/
char* obtenirDonnees(struct maillon_t* maillon);

/**
* Fonction qui modifie le prochain élément d'une chaine
* @maillon: pointeur de l'élément dont on modifie le suivant
* @maillon2: prochain mailllon
*/
void modifierSuivant(struct maillon_t* maillon, struct maillon_t* maillon2);

/**
* Fonction qui permet d'atribuer un enfant à une catégorie
* @maillon: pointeur de la catégorie
* @maillon2: pointeur du premier enfant
*/
void modifierEnfant(struct maillon_t* maillon, struct maillon_t* maillon2);

/**
* Fonction qui permet de modifier la chaine de caractère contenue dans le maillon
* @maillon: maillon dont on veut modifier le contenu
* @string: chaine de caractère de données
*/
void modifierData(struct maillon_t* maillon, char* string);

/**
* Fonction qui permet d'insérer un maillon dans une chaine
* @maillon: maillon précédent le nouveau maillon
* @insert: maillon à insérer
*/
void insererMaillon(struct maillon_t* maillon, struct maillon_t* insert);

/**
* Création d'un maillon, allocation de memoire dynamique
*/
struct maillon_t* creerMaillon();

/**
* Création de data, allocation de memoire dynamique
* @taille: taille de la chaine de caractères à allouer
*/
char* creerData(int taille);

/**
* Suppression d'un maillon de memoire dynamique
* @maillon: maillon à libérer
*/
void supprimerMaillon(struct maillon_t* maillon);

/**
* Supression d'une chaine de caratère alloué dynamiquement
* @string: chaine de caractère à libérer
*/
void supprimerData(char* string);

/**
* Vérification des arguments de l'exécution du logiciel
* @argc: nombre d'arguments à l'exécution
*/
void executionOk(int argc);

/**
* Ouverture du fichier contenant les recettes
* @filename: nom du fichier et path à ouvrir
*/
FILE* ouvertureFichier(char* filename);

/**
* Fermetture d'un fichier
* @
*/
void fermerFichier(FILE* fichier);

/**
* Copie d'une chaine de caractère à une autre
*/
void copieString(char* chaine1, char* chaine2);


/**
* Création de la structure de donnée
*/
struct maillon_t* initData(FILE* fichier);

/**
* Lire une ligne du fichier
*/
char* lectureLigne(FILE* fichier, char* buffer, int taille);

/**
* Reconnaisance d'une ligne du fichier
*/
void analyzeLigne(char* ligne, struct maillon_t* debut);

/**
* Ajout à la fin de catégorie
*/
void ajoutCategorie(struct maillon_t* debut, char* string, char* data);

/**
* Obtenir nom recette
*/
char* getRecette(char* string, char* recette);

/**
* Obtenir catégorie
*/
char* getCategorie(char* string, char* categorie);

/*
* Découvrir si une catégorie existe
*/
struct maillon_t* catExiste(struct maillon_t* debut, char* string);

/*
* Recette existe
*/
struct maillon_t* reExiste(struct maillon_t* cat, char* string);

/*
* Ajouter une catégorie par ordre alphabétique
*/
struct maillon_t* addCatAlph(struct maillon_t* debut, char* string);


/**
* Ajouter recette alphabetique
*/
struct maillon_t* addRecAlph(struct maillon_t* cat, char* string);

/**
* Rechercher nom catégorie
*/
short rechercheCategorie(struct maillon_t* debut, char* string);

/**
* Rechercher recette
*/
short rechercheRecette(struct maillon_t* debut, char* string);

/**
* Affichage d'un message lorsqu'aucun résulat n'a été trouvé
*/
void notFound(char* saisie);

#endif
