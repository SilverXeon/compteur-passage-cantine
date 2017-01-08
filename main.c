#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDl/SDL_ttf.h>
#include <fmodex/fmod.h>
#include "scan.h"
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <SDL/SDL_mixer.h>

int main ( int argc, char** argv )
{

    SDL_Surface* ecran = NULL;
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
    Mix_AllocateChannels(32);
    Mix_Chunk *confirmation;
    Mix_Chunk *exclamation;
    Mix_Chunk *alerte;
    Mix_Chunk *attention;





    char nom[20] = "", prenom[20] = "", classe[4] = "", mode[20] = "", code[6] = {0};
    int aubers = 0;
    long nombreScan = 0;
    char chaineNombreScan[15] = "Scan : ";
    char choixDouble = 0;
    long convertit=0; //long du scan de la douchette
    long verifDouble = 0;
    int numLigne=0; //Variables permettant de se localiser dans le fichier
    int echo = 1, detectDouble = 0, i=0;
    //FILE* fichierListe = NULL;

    char nomFichier[100] = "tableauEleve";
    int etude = 0;


     FILE* fichierMois = NULL;
     int mois=0, moisFichier=0;
     struct tm temps;
     time_t secondes;
    time(&secondes);
    temps=*localtime(&secondes);
    mois=temps.tm_mon+1;
    fichierMois=fopen("mois.txt", "r+");
    fscanf(fichierMois, "%d", &moisFichier);
    fclose(fichierMois);
    if(mois!=moisFichier)
    {
        char nomMois[15]= {0};

        //printf("La recupuration des fichiers a commence pour le mois de %s, ceci seront disponibles sur le bureau\n", nomMois);

        recoverFichier(nomMois, moisFichier, 0, ecran);

        /*rewind(fichierMois);
        fprintf(fichierMois, "%.2d", mois);*/
        remove("mois.txt");
        fichierMois=fopen("mois.txt", "a");
        fprintf(fichierMois, "%.2d", mois);
        fclose(fichierMois);
    }


    SDL_Event event;

    SDL_Surface* image = NULL;
    SDL_Surface* affNom = NULL;
    SDL_Surface* affPrenom = NULL;
    SDL_Surface* affClasse = NULL;
    SDL_Surface* affMode = NULL;
    SDL_Surface* affCode = NULL;
    SDL_Surface* historique[5] = {NULL};
    SDL_Surface* affNombreScan = NULL;
    //char historiqueNom[5][20] = {0};
    char historiqueNom1[20] = {0};
    char historiqueNom2[20] = {0};
    char historiqueNom3[20] = {0};
    char historiqueNom4[20] = {0};
    char historiqueNom5[20] = {0};


    SDL_Surface* erreurNom = NULL;
    SDL_Surface* avertiAnnul = NULL;
    SDL_Rect posNom, posPrenom, posClasse, posMode, posImage, posCode, posAvertiAnnul, posHistorique, posNombreScan;
    posNombreScan.x=335;
    posNombreScan.y=25;
    posHistorique.x=380;
    posHistorique.y=400;
    posImage.x=0;
    posImage.y=0;
    posNom.x = 548;
    posNom.y = 124;
    posPrenom.x=596;
    posPrenom.y=165;
    posClasse.x = 566;
    posClasse.y = 203;
    posMode.x=558;
    posMode.y=239;
    posCode.x=148;
    posCode.y=148;
    posAvertiAnnul.x=413;
    posAvertiAnnul.y=310;

    SDL_Rect posErreurNom;
    posErreurNom.x=42;
    posErreurNom.y=264;
    int continuer = 1, j=0;

    TTF_Init();
    TTF_Font* police = NULL;
    police=TTF_OpenFont("arial.ttf", 20);
    SDL_Color couleurNoire = {0,0,0};
    SDL_Color couleurBlanche = {255,255,255};

    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(1000, 700, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Comptabilite", NULL);
    SDL_WM_SetIcon(SDL_LoadBMP("Icon_CodeBarreWC.bmp"), NULL);
    image = IMG_Load("fond.png");
    erreurNom = IMG_Load("alerteNomNonTrouve.png");
    avertiAnnul = IMG_Load("alerteAnnulation.png");
    SDL_BlitSurface(image, NULL, ecran, &posImage);
    SDL_Flip(ecran);

    exclamation = Mix_LoadWAV("exclamation.wav");
    alerte = Mix_LoadWAV("chord.wav");
    confirmation = Mix_LoadWAV("sonConfirmation.wav");
    attention = Mix_LoadWAV("ding.wav");




    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
        switch(event.key.keysym.sym)
        {
             case SDLK_0:
                 if(i<=3)
                 {
                    strcat(code, "0");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, attention, 0);
                 break;
            case SDLK_1:
                 if(i<=3)
                 {
                    strcat(code, "1");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, attention, 0);
                 break;
            case SDLK_2:
                 if(i<=3)
                 {
                    strcat(code, "2");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, attention, 0);
                 break;
            case SDLK_3:
                 if(i<=3)
                 {
                    strcat(code, "3");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, attention, 0);
                 break;
            case SDLK_4:
                 if(i<=3)
                 {
                    strcat(code, "4");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, attention, 0);
                 break;
            case SDLK_5:
                 if(i<=3)
                 {
                    strcat(code, "5");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, attention, 0);
                 break;
            case SDLK_6:
                 if(i<=3)
                 {
                    strcat(code, "6");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, attention, 0);
                 break;
            case SDLK_7:
                 if(i<=3)
                 {
                    strcat(code, "7");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, attention, 0);
                 break;
            case SDLK_8:
                 if(i<=3)
                 {
                    strcat(code, "8");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, attention, 0);
                 break;
            case SDLK_9:
                 if(i<=3)
                 {
                    strcat(code, "9");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, attention, 0);
                 break;
            case SDLK_KP0:
                 if(i<=3)
                 {
                    strcat(code, "0");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, attention, 0);
                 break;
            case SDLK_KP1:
                 if(i<=3)
                 {
                    strcat(code, "1");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, attention, 0);
                 break;
            case SDLK_KP2:
                 if(i<=3)
                 {
                    strcat(code, "2");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, attention, 0);
                 break;
            case SDLK_KP3:
                 if(i<=3)
                 {
                    strcat(code, "3");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, attention, 0);
                 break;
            case SDLK_KP4:
                 if(i<=3)
                 {
                    strcat(code, "4");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, attention, 0);
                 break;
            case SDLK_KP5:
                 if(i<=3)
                 {
                    strcat(code, "5");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, attention, 0);
                 break;
            case SDLK_KP6:
                 if(i<=3)
                 {
                    strcat(code, "6");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, attention, 0);
                 break;
            case SDLK_KP7:
                 if(i<=3)
                 {
                    strcat(code, "7");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, attention, 0);
                 break;
            case SDLK_KP8:
                 if(i<=3)
                 {
                    strcat(code, "8");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, attention, 0);
                 break;
            case SDLK_KP9:
                 if(i<=3)
                 {
                    strcat(code, "9");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, attention, 0);
                 break;
            case SDLK_BACKSPACE:
                   if(i!=0)
                   {
                       SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255,255));
                        SDL_BlitSurface(image, NULL, ecran, &posImage);
                        affNom = TTF_RenderText_Blended(police, nom, couleurNoire);
                        affPrenom = TTF_RenderText_Blended(police, prenom, couleurNoire);
                affClasse = TTF_RenderText_Blended(police, classe, couleurNoire);
                affMode = TTF_RenderText_Blended(police, mode, couleurNoire);
                SDL_BlitSurface(affNom, NULL, ecran, &posNom);
                SDL_BlitSurface(affPrenom, NULL, ecran, &posPrenom);
                SDL_BlitSurface(affClasse, NULL, ecran, &posClasse);
                SDL_BlitSurface(affMode, NULL, ecran, &posMode);
                posHistorique.y=340;
                    for(j=0;j<5;j++)
                    {
                        SDL_BlitSurface(historique[j], NULL, ecran, &posHistorique);
                        posHistorique.y=posHistorique.y+23;
                    }

                        i--;

                    code[i] = '\0';
                   }
                 else
                    Mix_PlayChannel(5, attention, 0);
                    break;
            case SDLK_RETURN:
                //programme ecrit avant

                i=0;
                sprintf(nomFichier, "tableauEleve");
                choixDouble = 'O';
                convertit = strtol(code, NULL, 10);
                if(convertit==verifDouble)
                {
                    detectDouble=1;
                    Mix_PlayChannel(2, exclamation, 0);
                    choixDouble=avertissDouble(ecran);
                    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255,255));
                    SDL_BlitSurface(image, NULL, ecran, &posImage);
                    affNom = TTF_RenderText_Blended(police, nom, couleurNoire);
                    affPrenom = TTF_RenderText_Blended(police, prenom, couleurNoire);
                    affClasse = TTF_RenderText_Blended(police, classe, couleurNoire);
                    affMode = TTF_RenderText_Blended(police, mode, couleurNoire);
                    SDL_BlitSurface(affNom, NULL, ecran, &posNom);
                    SDL_BlitSurface(affPrenom, NULL, ecran, &posPrenom);
                    SDL_BlitSurface(affClasse, NULL, ecran, &posClasse);
                    SDL_BlitSurface(affMode, NULL, ecran, &posMode);


                    SDL_Flip(ecran);

                }

                verifDouble=convertit;

                if(choixDouble)
                {
                    choixFichier(nomFichier, convertit, classe, &etude, echo);


                if(convertit>=1000) //Les chiffres inférieur à 1000 correspondant aux codes Systeme
                {
                    numLigne=checkListe(nomFichier, convertit); //Appel de la fonction checkListe afin d'avoir le numéro de ligne dans le fichier
                }
                if(numLigne!=99 && convertit>=1000) //0099 represente une erreur de nom
                {
                    Mix_PlayChannel(1, confirmation, 0);
                    aubers = checkNomPrenom(nomFichier, numLigne, nom, prenom, echo); //Fonction de recuperation du nom et du prenom depuis des liste
                    remplirFichier(classe, nom, prenom, etude, mode, 0, 'a'); //Remplissage des fichiers eleve pour le compte
                    nombreScan++;
                    sprintf(chaineNombreScan, "Scan : %ld", nombreScan);
                    /*for(i=0;i<4;i++)
                    {
                        sprintf(historiqueNom[i+1], historiqueNom[i]);
                    }
                    sprintf(historiqueNom[0],nom);
                    sprintf(chaineHistorique, "");*/
                    sprintf(historiqueNom5, historiqueNom4);
                    sprintf(historiqueNom4, historiqueNom3);
                    sprintf(historiqueNom3, historiqueNom2);
                    sprintf(historiqueNom2, historiqueNom1);
                    sprintf(historiqueNom1, nom);

                    historique[0] = TTF_RenderText_Shaded(police, historiqueNom1, couleurNoire, couleurBlanche);
                    historique[1] = TTF_RenderText_Shaded(police, historiqueNom2, couleurNoire, couleurBlanche);
                    historique[2] = TTF_RenderText_Shaded(police, historiqueNom3, couleurNoire, couleurBlanche);
                    historique[3] = TTF_RenderText_Shaded(police, historiqueNom4, couleurNoire, couleurBlanche);
                    historique[4] = TTF_RenderText_Shaded(police, historiqueNom5, couleurNoire, couleurBlanche);

                    //sprintf(chaineHistorique, "%s\n%s\n%s\n%s\n%s", historiqueNom1, historiqueNom2, historiqueNom3, historiqueNom4, historiqueNom5);
                    //historique = TTF_RenderText_Shaded(police, chaineHistorique, couleurNoire, couleurBlanche);

                }
                else if(numLigne==99)
                {
                    Mix_PlayChannel(3, alerte, 1);
                    SDL_BlitSurface(erreurNom, NULL, ecran, &posErreurNom);
                    SDL_Flip(ecran);
                    SDL_Delay(1500);
                    sprintf(nom, "ERREUR");
                    sprintf(prenom, "ERREUR");
                    sprintf(classe, "ERR");
                    sprintf(mode, "ERREUR");
                    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255,255));
                    SDL_BlitSurface(image, NULL, ecran, &posImage);
                    affNom = TTF_RenderText_Blended(police, nom, couleurNoire);
                    affPrenom = TTF_RenderText_Blended(police, prenom, couleurNoire);
                    affClasse = TTF_RenderText_Blended(police, classe, couleurNoire);
                    affMode = TTF_RenderText_Blended(police, mode, couleurNoire);
                    SDL_BlitSurface(affNom, NULL, ecran, &posNom);
                    SDL_BlitSurface(affPrenom, NULL, ecran, &posPrenom);
                    SDL_BlitSurface(affClasse, NULL, ecran, &posClasse);
                    SDL_BlitSurface(affMode, NULL, ecran, &posMode);
                }
                }



                SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255,255));
                SDL_BlitSurface(image, NULL, ecran, &posImage);
                affNombreScan = TTF_RenderText_Blended(police, chaineNombreScan, couleurNoire);
                affNom = TTF_RenderText_Blended(police, nom, couleurNoire);
                affPrenom = TTF_RenderText_Blended(police, prenom, couleurNoire);
                affClasse = TTF_RenderText_Blended(police, classe, couleurNoire);
                affMode = TTF_RenderText_Blended(police, mode, couleurNoire);
                SDL_BlitSurface(affNombreScan, NULL, ecran, &posNombreScan);
                SDL_BlitSurface(affNom, NULL, ecran, &posNom);
                SDL_BlitSurface(affPrenom, NULL, ecran, &posPrenom);
                SDL_BlitSurface(affClasse, NULL, ecran, &posClasse);
                SDL_BlitSurface(affMode, NULL, ecran, &posMode);
                sprintf(code, "");
                posHistorique.y=400;
                    for(i=0;i<5;i++)
                    {
                        SDL_BlitSurface(historique[i], NULL, ecran, &posHistorique);
                        posHistorique.y=posHistorique.y+23;
                    }
                    i=0;

                if(detectDouble)
                {
                    SDL_Surface* indicComptage = NULL;
                    if(choixDouble)
                    {
                        indicComptage = TTF_RenderText_Blended(police, "Compté", couleurNoire);
                    }
                    else
                    {
                        indicComptage = TTF_RenderText_Blended(police, "Ignoré", couleurNoire);
                    }

                    SDL_BlitSurface(indicComptage, NULL, ecran, &posAvertiAnnul);
                    SDL_FreeSurface(indicComptage);
                    detectDouble=0;
                }


                break;
            default:
                break;
        }
        break;
            case SDL_MOUSEBUTTONUP:
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    if(event.button.x>= 47 && event.button.x<=319 && event.button.y>=228 && event.button.y <= 391)
                    {
                        annulerSaisie(nom, prenom, classe);
                        SDL_BlitSurface(avertiAnnul, NULL, ecran, &posAvertiAnnul);
                        sprintf(historiqueNom1, "       ANNULE      ");
                        historique[0] = TTF_RenderText_Shaded(police, historiqueNom1, couleurNoire, couleurBlanche);
                        posHistorique.y=400;
                        SDL_BlitSurface(historique[0], NULL, ecran, &posHistorique);

                    }
                    if(event.button.x>=8 && event.button.x<=322 && event.button.y>=579 && event.button.y<=611)
                    {
                        Mix_PlayChannel(4, exclamation, 0);
                        recoverFichier("Volontaire", 0, 1, ecran);
                        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255,255));
                        SDL_BlitSurface(image, NULL, ecran, &posImage);
                        SDL_Flip(ecran);
                    }
                    if(event.button.x>=805 && event.button.x<=940 && event.button.y>=115 && event.button.y<=274)
                    {

                        sprintf(code, "");
                        if(!ajoutManuel(ecran, attention,police, nom, prenom, classe, mode))
                        {
                            Mix_PlayChannel(3, alerte, 1);
                            SDL_BlitSurface(erreurNom, NULL, ecran, &posErreurNom);
                            SDL_Flip(ecran);
                            SDL_Delay(1500);
                            sprintf(nom, "ERREUR");
                            sprintf(prenom, "ERREUR");
                            sprintf(classe, "ERR");
                            sprintf(mode, "ERREUR");
                        }
                    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255,255));
                    SDL_BlitSurface(image, NULL, ecran, &posImage);
                    affNom = TTF_RenderText_Blended(police, nom, couleurNoire);
                    affPrenom = TTF_RenderText_Blended(police, prenom, couleurNoire);
                    affClasse = TTF_RenderText_Blended(police, classe, couleurNoire);
                    affMode = TTF_RenderText_Blended(police, mode, couleurNoire);
                    SDL_BlitSurface(affNom, NULL, ecran, &posNom);
                    SDL_BlitSurface(affPrenom, NULL, ecran, &posPrenom);
                    SDL_BlitSurface(affClasse, NULL, ecran, &posClasse);
                    SDL_BlitSurface(affMode, NULL, ecran, &posMode);
                        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255,255));
                        SDL_BlitSurface(image, NULL, ecran, &posImage);
                        affNom = TTF_RenderText_Blended(police, nom, couleurNoire);
                        affPrenom = TTF_RenderText_Blended(police, prenom, couleurNoire);
                        affClasse = TTF_RenderText_Blended(police, classe, couleurNoire);
                        affMode = TTF_RenderText_Blended(police, mode, couleurNoire);
                        SDL_BlitSurface(affNom, NULL, ecran, &posNom);
                        SDL_BlitSurface(affPrenom, NULL, ecran, &posPrenom);
                        SDL_BlitSurface(affClasse, NULL, ecran, &posClasse);
                        SDL_BlitSurface(affMode, NULL, ecran, &posMode);
                        SDL_Flip(ecran);
                        Mix_PlayChannel(1, confirmation, 0);
                        sprintf(code, "");

                    }
                }
                break;
        }

        affCode = TTF_RenderText_Blended(police, code, couleurNoire);
        SDL_BlitSurface(affCode, NULL, ecran, &posCode);
        SDL_Flip(ecran);

    }

    TTF_CloseFont(police);
    TTF_Quit();
    Mix_FreeChunk(exclamation);
    Mix_FreeChunk(confirmation);
    Mix_FreeChunk(alerte);
    Mix_FreeChunk(attention);
    Mix_CloseAudio();
    SDL_FreeSurface(image);
    SDL_FreeSurface(affNom);
    SDL_FreeSurface(affPrenom);
    SDL_FreeSurface(affClasse);
    SDL_FreeSurface(affMode);
    for(i=0;i<5;i++)
    {
        SDL_FreeSurface(historique[i]);
    }
    SDL_FreeSurface(erreurNom);
    SDL_FreeSurface(avertiAnnul);
    SDL_Quit();
    return 0;
}
