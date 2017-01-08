#include <SDL/SDL_mixer.h>
#ifndef DEF_SCAN
#define DEF_SCAN


long checkListe(char* nomFichier, long releve);
int checkNomPrenom(char* nomFichier, int ligne, char *nom, char *prenom, int etude);
void effacerPointVirgule(char *nom);
void choixFichier(char* nomFichier, long codeBarre, char* classe, int* etude, int echo);
void remplirFichier(char* classe, char* nom, char* prenom, int etude, char* mode, int manuel, char caractereManuel);
void checkTime(char* typeScan, char* classe, int etude, char* mode);
void recoverFichier(char* nomMois, int numMois, int volontaire, SDL_Surface* ecran);
void choixMois(char* nomMois, int numMois);
void remplirChaineTemps(char* temps);
int compterNombreLigne(char* nomListe);
void creerCSV(char* nomFichier, char* classe, char* nomDossier, char* mois);
void compterMode(int* nbrA, int* nbrB, int* nbrC, int* nbrD, int* nbrE, int* nbrF, int* nbrG,int* nbrH, char* nom, char* prenom, char* classe);
void remplirCSV(char* nomFichier, int numLigneCSV, int nbrA, int nbrB, int nbrC, int nbrD, int nbrE, int nbrF, int nbrG,int nbrH, char* nom, char* prenom, char* classe, char aubers, int etude);
void supprimerDossierEleve(char* nomDossier, int confirmation, SDL_Surface* ecran);
void annulerSaisie(char* nom,char* prenom,char* classe);
int avertissDouble(SDL_Surface* ecran);
int ajoutManuel(SDL_Surface* ecran, Mix_Chunk* son, TTF_Font* police, char* nom, char* prenom, char* classe, char* mode);
void choixMode(char* caractere);
void viderChaine(char* nomMois, char* nomDossier, char* nomListe, char* nomFichier, char* classe, char* nom, char* prenom);
void choixModeManuel(char* mode, char caractere);
int confirmationSupression(SDL_Surface* ecran);
int demanderMotDePasse(SDL_Surface* ecran);

#endif // DEF_SCAN
