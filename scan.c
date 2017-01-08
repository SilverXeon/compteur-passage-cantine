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

long checkListe(char* nomFichier, long releve)
{
    char ligne[100]=""; //Chaine contenant le contenu de la ligne du fichier
    long codeBarre = 0; //Chaine contenant le numéro retenu au début de la ligne
    int i=-1;
    FILE* liste = NULL;
    int finFichier = 0; //Variables testant la fin du fichier

    //printf("Init varia fonction\n"); //Debug

    liste=fopen(nomFichier, "r+"); //A modifier avec La classe etc...

    //printf("Fichier ouvert\n"); //Debug

    while(releve != codeBarre)
    {
    finFichier=fgets(ligne, 100, liste); //Recupération de la ligne dans "ligne" et assignation de NULL ou 1 à finFichier
    //printf("Ligne recupere\n");
    //printf("%s", ligne);
    codeBarre=strtol(ligne, NULL, 10); //Recupération du numéro au début de la ligne
    i++; //incrémentation de i pour le numéro de ligne (d'où l'interet de mettre -1 en init afin d'avoir la ligne 0
    if(finFichier==NULL)
    {
        printf("!!!Nom non trouve dans le fichier !!!\n");
        return 99;
    }
    }
    //printf("Numero dans le CSV : %d\n", codeBarre); //Debug
    fclose(liste);
    return i;
}

int checkNomPrenom(char* nomFichier, int ligne, char *nom, char *prenom, int echo)
{
    FILE* liste = NULL;
    liste=fopen(nomFichier, "r+"); //A modifier selon les classes etc
    int charNom = 0;
    int posNom=0;
    int i=0;
    int aubers = 0;

    posNom=ligne*40+5+ligne; //Calcul de l'emplacement du Nom dans le fichier et dans la ligne
    //rewind(liste);
    fseek(liste, posNom, SEEK_SET);
    /*fgets(nom, 100, liste);
    printf("%s\n", nom);*/
    while(charNom!=';')
    {
        charNom=fgetc(liste);
        nom[i]=charNom;
        i++;
    }
    effacerPointVirgule(nom);
    if(echo)
        printf("Nom : %s\n", nom);

    /*while(nom[i]!=';')
    {
        nom[i]=fgetc(liste);
    }
    printf("%s", nom);*/
    charNom=0;
    i=0;
    //fseek(liste, -1, SEEK_CUR);
    while(charNom!=';')
    {
        charNom=fgetc(liste);
        prenom[i]=charNom;
        i++;
    }
    effacerPointVirgule(prenom);
    if(fgetc(liste)=='A')
        aubers=1;
    else
        aubers=0;


    //fgets(prenom, 4, liste); //4 caractere pour n'avoir que 3 lettres du nom, a augmenter si besoin mais prendre en compte les / dans une nouvelle fonction
    if(echo)
        printf("Prenom : %s\n", prenom);
    fclose(liste);
    return aubers;
}

void effacerPointVirgule(char *chaine)
{
    char *positionPointVirgule = NULL; //Pointeur sur la pos du ; dans la chaine

    positionPointVirgule = strchr(chaine, ';'); //Le pointeur prend l'adresse du ;
    if(positionPointVirgule!=NULL)
    {
        *positionPointVirgule = '\0'; //Remplacement du contenu du pointeur par \0(fin de chaine)
        return 0;
    }
    else
    {
        printf("Erreur lors de la recherche du ; dans la chaine Nom");
        return 0;
    }

}

void choixFichier(char* nomFichier, long codeBarre, char *classe, int *etude, int echo)
{
    /*if(DEBUG)
        printf("DEBUG : Entrer fonction choixFichier codeBarre = %ld", codeBarre);*/
    char suiteNomFichier[50] = {0};
    if(codeBarre<=999) { sprintf(classe, "Systeme");  sprintf(suiteNomFichier, "Sys.csv"); }
    if(codeBarre == 11 || (codeBarre>=1000 && codeBarre<=1999)) { sprintf(classe, "TPS"); *etude=0;sprintf(suiteNomFichier, "TPS.csv"); }
    if(codeBarre == 12 || (codeBarre>=2000 && codeBarre<=2999)) { sprintf(classe, "PS"); *etude=0; sprintf(suiteNomFichier, "PS.csv"); }
    if(codeBarre == 13 || (codeBarre>=3000 && codeBarre<=3999)) { sprintf(classe, "MS"); *etude=0; sprintf(suiteNomFichier, "MS.csv"); }
    if(codeBarre == 14 || (codeBarre>=4000 && codeBarre<=4999)) { sprintf(classe, "GS"); *etude=0; sprintf(suiteNomFichier, "GS.csv"); }
    if(codeBarre == 15 || (codeBarre>=5000 && codeBarre<=5999)) { sprintf(classe, "CP"); *etude=0; sprintf(suiteNomFichier, "CP.csv"); }
    if(codeBarre == 16 || (codeBarre>=6000 && codeBarre<=6999)) { sprintf(classe, "CE1"); *etude=1; sprintf(suiteNomFichier, "CE1.csv"); }
    if(codeBarre == 17 || (codeBarre>=7000 && codeBarre<=7999)) { sprintf(classe, "CE2"); *etude=1; sprintf(suiteNomFichier, "CE2.csv"); }
    if(codeBarre == 18 || (codeBarre>=8000 && codeBarre<=8999)) { sprintf(classe, "CM1"); *etude=1; sprintf(suiteNomFichier, "CM1.csv"); }
    if(codeBarre == 19 || (codeBarre>=9000 && codeBarre<=9999)) { sprintf(classe, "CM2"); *etude=1; sprintf(suiteNomFichier, "CM2.csv"); }
    /*if(DEBUG)
        printf("Condition Rempli\n Suite du Nom : %s", suiteNomFichier);*/
    strcat(nomFichier, suiteNomFichier);
    /*if(DEBUG)
        printf("Nom Fichier : %s\n", nomFichier);*/

}

void remplirFichier(char* classe, char* nom, char* prenom, int etude, char* mode, int manuel, char caractereManuel)
{
    char typeScan ='a';
    char temps[20]= {0};
    char nomFichier[50] = "fichiersEleve/";

    if(!manuel)
        checkTime(&typeScan, classe, etude, mode);
    remplirChaineTemps(temps);
    /*if(DEBUG)
    {
        printf("Chaine temps rempli\n %s\n", temps);
        printf("%c\n", typeScan);
    }*/
    //fonction checkTime avec envoi d'un char qui sera a,b,c etc... en fonction de l'heure

    FILE* fichierEleve = NULL;
    strcat(nomFichier, classe);
    strcat(nomFichier, nom);
    strcat(nomFichier, prenom);
    strcat(nomFichier, ".txt");

    fichierEleve = fopen(nomFichier, "a");

    if(!manuel)
        fprintf(fichierEleve, "%c %s\n", typeScan, temps);
    else
    {
        temps[9] = 'M';temps[10] = 'M';temps[12] = 'M';temps[13] = 'M';

        fprintf(fichierEleve, "%c %s\n", caractereManuel, temps);
    }
    fclose(fichierEleve);


}

void checkTime(char* typeScan, char* classe, int etude, char* mode)
{
    time_t secondes;
    struct tm heure;
    int heureAct;
    int minutes;
    //int etude = 0;
    time(&secondes);
    heure=*localtime(&secondes);
    heureAct=heure.tm_hour;
    minutes=heure.tm_min;

    //heureAct=16;
    /*if(classe == "CE1" || classe == "CE2" || classe == "CM1" || classe == "CM2")
    {
        etude = 1;
    }*/

    printf("Mode : ");
    if(heureAct <8){*typeScan = 'a'; sprintf(mode, "Garderie 7h15");}
    if(heureAct <=10 && heureAct >=8){*typeScan = 'b'; sprintf(mode, "Garderie 8h");}
    if(heureAct <=15 && heureAct >=11){*typeScan = 'c'; sprintf(mode, "Cantine");}
    if(((heureAct==17 && minutes<30) || (heureAct==16 && minutes>=30)) && etude == 0){*typeScan = 'd'; sprintf(mode, "Garderie 16h30");}
    if(((heureAct==17 && minutes<30) || (heureAct==16 && minutes>=30)) && etude == 1){*typeScan = 'e'; sprintf(mode, "Etude");}
    if((heureAct==17 && minutes>=30) || (heureAct==18 && minutes<30)){*typeScan = 'f'; sprintf(mode, "Garderie 17h30");}
    if((heureAct == 18 && minutes >30) || heureAct>=19 && heureAct <=23){*typeScan = 'g'; sprintf(mode, "Garderie 18h30");}

}

int demanderMotDePasse(SDL_Surface* ecran)
{
    char chaineAfficher[4] = {0};
    int motDePasse[4] = {0};
    SDL_Surface* image= NULL;
    SDL_Surface* chaine = NULL;
    SDL_Rect position;
    position.x=0;
    position.y=0;
    int continuer=1, i=0;
    SDL_Rect positionCode;
    positionCode.x=196;
    positionCode.y=102;
    SDL_Event event;
    image=IMG_Load("motDePasse.png");
    TTF_Font* police = NULL;
    police=TTF_OpenFont("arial.ttf", 60);
    SDL_Color couleurNoire = {0,0,0};

    //SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255,255));
    SDL_BlitSurface(image, NULL, ecran, &position);

    SDL_Flip(ecran);
    while(continuer)
    {
        if(i==4)
            continuer=0;
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            exit(EXIT_FAILURE);
            break;
        case SDL_MOUSEBUTTONUP:
            if(event.button.button==SDL_BUTTON_LEFT)
            {
                if(event.button.x>=196 && event.button.x<=263 && event.button.y>=177 && event.button.y<=237) //1
                {
                    motDePasse[i]=1;
                    chaineAfficher[i]='*';
                    i++;
                }
                if(event.button.x>=281 && event.button.x<=347 && event.button.y>=177 && event.button.y<=237) //2
                {
                    motDePasse[i]=2;
                    chaineAfficher[i]='*';
                    i++;
                }
                if(event.button.x>=368 && event.button.x<=433 && event.button.y>=177 && event.button.y<=237) //3
                {
                    motDePasse[i]=3;
                    chaineAfficher[i]='*';
                    i++;
                }
                if(event.button.x>=196 && event.button.x<=263 && event.button.y>=247 && event.button.y<=308) //4
                {
                    motDePasse[i]=4;
                    chaineAfficher[i]='*';
                    i++;
                }
                if(event.button.x>=281 && event.button.x<=347 && event.button.y>=247 && event.button.y<=308) //5
                {
                    motDePasse[i]=5;
                    chaineAfficher[i]='*';
                    i++;
                }
                if(event.button.x>=368 && event.button.x<=433 && event.button.y>=247 && event.button.y<=308) //6
                {
                    motDePasse[i]=6;
                    chaineAfficher[i]='*';
                    i++;
                }
                if(event.button.x>=196 && event.button.x<=263 && event.button.y>=322 && event.button.y<=382) //7
                {
                    motDePasse[i]=7;
                    chaineAfficher[i]='*';
                    i++;
                }
                if(event.button.x>=281 && event.button.x<=347 && event.button.y>=322 && event.button.y<=382) //8
                {
                    motDePasse[i]=8;
                    chaineAfficher[i]='*';
                    i++;
                }
                if(event.button.x>=368 && event.button.x<=433 && event.button.y>=322 && event.button.y<=382) //9
                {
                    motDePasse[i]=9;
                    chaineAfficher[i]='*';
                    i++;
                }
                if(event.button.x>=284 && event.button.x<=350 && event.button.y>=394 && event.button.y<=455) //0
                {
                    motDePasse[i]=0;
                    chaineAfficher[i]='*';
                    i++;
                }
                if(event.button.x>=196 && event.button.x<=263 && event.button.y>=394 && event.button.y<=455) //retour
                {
                   if(i!=0)
                   {
                       i--;
                       chaineAfficher[i]='\0';
                       chaine=TTF_RenderText_Blended(police, chaineAfficher, couleurNoire);
                       SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255,255));
                       SDL_BlitSurface(image, NULL, ecran, &position);
                       SDL_BlitSurface(chaine, NULL, ecran, &positionCode);
                   }
                }
                if(event.button.x>=469 && event.button.x<=678 && event.button.y>=105 && event.button.y<=144) //revenir
                {
                    continuer = 0;
                    return 0;
                }
            }
            break;
        }
        if(i==4)
            continuer=0;
        chaine=TTF_RenderText_Blended(police, chaineAfficher, couleurNoire);
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,255,255,255));
        SDL_BlitSurface(image,NULL,ecran,&position);
        SDL_BlitSurface(chaine, NULL, ecran, &positionCode);
        SDL_Flip(ecran);

    }
    if(motDePasse[0]==3 && motDePasse[1]==5 && motDePasse[2]==7 && motDePasse[3]==8)
        return 1;
    else
        return 0;
}

void recoverFichier(char* nomMois, int numMois, int volontaire, SDL_Surface* ecran)
{
    int verif = 1;
    if(volontaire)
        verif=demanderMotDePasse(ecran);

    if(verif)
    {

        FILE* configDossier = NULL;
        char nomDossier[100] = {0};
        char nomListe[100] = "tableauEleve";
        char nomFichier[100] = {0};
        char commande[100] = {0};
        char classe[5] = {0};
        char nom[20] = {0};
        char prenom[20] = {0};
        int etude = 0;
        long codeBarre=1001;
        int nbrLigne=0;
        int numLigneCSV = 3;
        int nbrA=0, nbrB=0, nbrC=0, nbrD=0, nbrE=0, nbrF=0, nbrG=0, nbrH=0;
        int i=0;
        int echo = 0;
        int aubers = 0;

        configDossier = fopen("config.txt", "r");
        fgets(nomDossier, 100, configDossier);




        /*if(DEBUG)
            printf("DEBUG : Init variable recoverFichier\n");*/


        choixMois(nomMois, numMois);

        /*if(DEBUG)
            printf("DEBUG : Mois choisi : %d, %s\n", numMois, nomMois);*/

        strcat(nomDossier, nomMois);
        /*if(DEBUG)
            printf("DEBUG : Nom du dossier : %s \n", nomDossier);*/
        sprintf(commande, "mkdir %s", nomDossier);
        system(commande);
        strcat(nomDossier, "\\fichiersEleve");
        sprintf(commande, "mkdir %s", nomDossier );
        system(commande);
        /*if(DEBUG)
        {
            printf("DEBUG : Dossier crée a verifie\n");
        }*/

        while(codeBarre<10000)
        {
            viderChaine(nomMois, nomDossier, nomListe, nomFichier, classe, nom, prenom);
            numLigneCSV=3;
            /*if(DEBUG)
                printf("DEBUG : Entrer dans boucle tant que !=10 000\n");*/
            choixFichier(nomListe, codeBarre, classe, &etude, echo);
            /*if(DEBUG)
                printf("DEBUG : Fichier choisi : %s classe : %s\n", nomListe, classe);*/
            nbrLigne=compterNombreLigne(nomListe);
            /*if(DEBUG)
                printf("DEBUG : Nbrligne compte : %d\n", nbrLigne);*/
            /*if(DEBUG)
                printf("DEBUG : nomDossier avant creerCSV : %s\n", nomDossier);*/
            creerCSV(nomFichier, classe, nomDossier, nomMois);
            /*if(DEBUG)
                printf("DEBUG : CSV cree\n");*/
            for(i=0; i<nbrLigne; i++)
            {
                aubers=checkNomPrenom(nomListe, i, nom, prenom, echo);
                compterMode(&nbrA, &nbrB, &nbrC, &nbrD, &nbrE, &nbrF, &nbrG, &nbrH, nom, prenom, classe);
                if(aubers)
                    remplirCSV(nomFichier, numLigneCSV, nbrA, nbrB, nbrC, nbrD, nbrE, nbrF, nbrG,nbrH, nom, prenom, classe, 'O', codeBarre>=6000);
                else
                    remplirCSV(nomFichier, numLigneCSV, nbrA, nbrB, nbrC, nbrD, nbrE, nbrF, nbrG,nbrH, nom, prenom, classe, 'N', codeBarre>=6000);

                numLigneCSV++;
                nbrA=0;
                nbrB=0;
                nbrC=0;
                nbrD=0;
                nbrE=0;
                nbrF=0;
                nbrG=0;
                nbrH=0;
            }
            codeBarre=codeBarre+1000;
        }
        sprintf(nomDossier, "");
        rewind(configDossier);
        fgets(nomDossier, 100, configDossier);
        strcat(nomDossier, nomMois);
        fclose(configDossier);
        //printf("DEBUG : nomDossier : %s\n", nomDossier);
        if(volontaire)
            supprimerDossierEleve(nomDossier, 1, ecran);
        else
            supprimerDossierEleve(nomDossier, 0, ecran);
        system("CLS");
    }
    else
    {

    }
    //Dossier crée, ecrire un fichier par classe donc nouvelle fonction
}

void supprimerDossierEleve(char* nomDossier, int confirmation, SDL_Surface* ecran)
{
    char commande[150] = {0};
    char commandeMKDIR[150] = {0};
    char choix = 'O';
    int suppression = 1;
    //char vide = 0;

    if(confirmation)
    {
        system("CLS");
        suppression=confirmationSupression(ecran);
        choix = toupper(choix);
        if(choix != 'O')
        {
            suppression = 0;
        }
    }



    if(suppression)
    {
    strcat(nomDossier, "\\fichiersEleve");
    /*if(1)
        printf("DEBUG : nomDossier avant mkdir : %s\n", nomDossier);*/
    sprintf(commandeMKDIR, "MKDIR %s", nomDossier);
    system(commandeMKDIR);
    sprintf(commande, "COPY /Y fichiersEleve %s", nomDossier);
    system(commande);
    system("ERASE /S /F /Q fichiersEleve");
    }
    //system("mkdir fichiersEleve");
    //system("CLS");
}

int confirmationSupression(SDL_Surface* ecran)
{
    SDL_Surface* image = NULL;
    SDL_Rect position;
    position.x=0;
    position.y=0;
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255,255));
    image=IMG_Load("alerteSuspressionFichier.png");
    SDL_BlitSurface(image, NULL, ecran, &position);
    SDL_Flip(ecran);
    int continuer = 1;
    SDL_Event event;

    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer=0;
            exit(EXIT_FAILURE);
            break;
        case SDL_MOUSEBUTTONUP:
            if(event.button.button==SDL_BUTTON_LEFT)
            {
                if(event.button.x>=186 && event.button.x<=329 && event.button.y>=205 && event.button.y<=333)
                {
                    continuer = 0;
                    return 1;
                }
                if(event.button.x>=363 && event.button.x<=511 && event.button.y>=203 && event.button.y<=335)
                {
                    continuer = 0;
                    return 0;
                }
            }
            break;
        }

    }
    SDL_FreeSurface(image);
    return 0;
}




void viderChaine(char* nomMois, char* nomDossier, char* nomListe, char* nomFichier, char* classe, char* nom, char* prenom)
{
    sprintf(nomDossier, "C:\\Users\\Pierre\\Desktop\\");
    /*if(DEBUG)
        printf("DEBUG : viderChaine : nomMois : %s\n", nomMois);*/
    strcat(nomDossier, nomMois);

    sprintf(nomListe, "tableauEleve");

    sprintf(nomFichier, "");

    sprintf(classe, "");

    sprintf(nom, "");

    sprintf(prenom, "");
}

void remplirChaineTemps(char* temps)
{
    struct tm heureAct;
    time_t secondes;
    time(&secondes);
    heureAct=*localtime(&secondes);
    /*if(DEBUG)
        printf("remplissage de la structure heureAct fait \n");*/
    sprintf(temps, "%.2d/%.2d/%.2d %.2d:%.2d", heureAct.tm_mday, heureAct.tm_mon+1, heureAct.tm_year-100, heureAct.tm_hour, heureAct.tm_min);
    /*if(DEBUG)
        printf("Chaine de la fonction rempli\n");*/

}

void choixMois(char* nomMois, int numMois)
{
    switch(numMois)
    {
        case 1:
        sprintf(nomMois, "Janvier");
        break;

        case 2:
        sprintf(nomMois, "Fevrier");
        break;
        case 3:
        sprintf(nomMois, "Mars");
        break;
        case 4:
        sprintf(nomMois, "Avril");
        break;
        case 5:
        sprintf(nomMois, "Mai");
        break;
        case 6:
        sprintf(nomMois, "Juin");
        break;
        case 7:
        sprintf(nomMois, "Juillet");
        break;
        case 8:
        sprintf(nomMois, "Aout");
        break;
        case 9:
        sprintf(nomMois, "Septembre");
        break;
        case 10:
        sprintf(nomMois, "Octobre");
        break;
        case 11:
        sprintf(nomMois, "Novembre");
        break;
        case 12:
        sprintf(nomMois, "Decembre");
        break;
        case 13:
        sprintf(nomMois, "Force");
    }

}

int compterNombreLigne(char* nomListe)
{
    /*if(DEBUG)
        printf("DEBUG : nomListe : %s\n", nomListe);*/
    FILE* fichier=NULL;
    int nbrLigne=0;
    char tampon[100]={0};
    fichier=fopen(nomListe, "r");
    /*if(DEBUG)
        printf("DEBUG : fichier ouvert\n");*/
    while(fgets(tampon, 100, fichier)!=NULL)
    {
        nbrLigne++;
    }

    return nbrLigne;
}

void creerCSV(char* nomFichier, char* classe, char* nomDossier, char* mois)
{
    FILE* fichier = NULL;
    char entete[200] = {0};
    /*if(DEBUG)
        printf("DEBUG : nomFichier : %s, nomDossier : %s\n", nomFichier, nomDossier);*/
    strcat(nomDossier, "\\");
    strcat(nomDossier, classe);
    strcat(nomDossier, ".csv");
    sprintf(nomFichier, nomDossier);
    /*if(DEBUG)
        printf("DEBUG : nomFichier : %s\n", nomFichier);*/
    sprintf(entete, "%s\nNom;Prenom;Aubers;Garderie 7:15;Garderie 8:00;Cantine;Garderie 16:30;Etude;Garderie 17:30;Garderie 18:30;Cantine exceptionelle;TOTAL\n", mois);
    fichier= fopen(nomFichier, "w+");

    //fichierCSV=fopen(nomFichier, "a");

    /*if(DEBUG)
        printf("DEBUG : entete \n %s\n", entete);*/

    fprintf(fichier, entete);
    /*if(DEBUG)
        printf("DEBUG : ligne ecrite");*/

    fclose(fichier);
    /*if(DEBUG)
        printf("DEBUG : fichierCSV cree aller le verifier, nomFichier : %s\n", nomFichier);*/

}

void compterMode(int* nbrA, int* nbrB, int* nbrC, int* nbrD, int* nbrE, int* nbrF, int* nbrG,int* nbrH, char* nom, char* prenom, char* classe)
{

    FILE* fichierEleve = NULL;
    char nomFichier[100] = {0};
    char tampon[100] = {0};
    char caractereReleve = 0;
    sprintf(nomFichier, "fichiersEleve/%s%s%s.txt", classe, nom, prenom);
    /*if(DEBUG)
        printf("DEBUG : nom du fichier eleve : %s\n", nomFichier);*/
    fichierEleve=fopen(nomFichier, "r");

    do
    {
        caractereReleve=fgetc(fichierEleve);
        fgets(tampon, 100, fichierEleve);
        if(caractereReleve=='a'){*nbrA=*nbrA+1;}
		if(caractereReleve=='b'){*nbrB=*nbrB+1;}
		if(caractereReleve=='c'){*nbrC=*nbrC+1;}
		if(caractereReleve=='d'){*nbrD=*nbrD+1;}
		if(caractereReleve=='e'){*nbrE=*nbrE+1;}
		if(caractereReleve=='f'){*nbrF=*nbrF+1;}
		if(caractereReleve=='g'){*nbrG=*nbrG+1;}
		if(caractereReleve=='h'){*nbrH=*nbrH+1;}
	}while(caractereReleve!=EOF);
	/*if(DEBUG)
        printf("DEBUG : nbrA : %d nbrb : %d nbrC : %d\n", *nbrA, *nbrB, *nbrC);*/
	fclose(fichierEleve);

}

void remplirCSV(char* nomFichier, int numLigneCSV, int nbrA, int nbrB, int nbrC, int nbrD, int nbrE, int nbrF, int nbrG,int nbrH, char* nom, char* prenom, char* classe, char aubers, int etude)
{
    FILE* fichierCSV=NULL;
    //char prix[10]={0};
    //int i=0;
    /*char tarifA[6] ={0};
    char tarifB[6] ={0};
    char tarifC[6] ={0};
    char tarifD[6] ={0};
    char tarifE[6] ={0};
    char tarifF[6] ={0};
    char tarifG[6] ={0};*/
    char ligne[500]={0};



    if(!etude)
        sprintf(ligne, "%s;%s;%c;%d;%d;%d;%d;%d;%d;%d;%d;=D%d*01,50+E%d*01,00+F%d*04,00+G%d*01,00+H%d*01,50+I%d*02,00+J%d*02,00+K%d*06,00\n", nom, prenom, aubers, nbrA, nbrB, nbrC, nbrD, nbrE, nbrF, nbrG,nbrH, numLigneCSV,numLigneCSV,numLigneCSV,numLigneCSV,numLigneCSV,numLigneCSV,numLigneCSV, numLigneCSV);
    else
        sprintf(ligne, "%s;%s;%c;%d;%d;%d;%d;%d;%d;%d;%d;=D%d*01,50+E%d*01,00+F%d*04,00+G%d*01,00+H%d*01,50+I%d*01,00+J%d*01,00+K%d*06,00\n", nom, prenom, aubers, nbrA, nbrB, nbrC, nbrD, nbrE, nbrF, nbrG,nbrH, numLigneCSV,numLigneCSV,numLigneCSV,numLigneCSV,numLigneCSV,numLigneCSV,numLigneCSV, numLigneCSV);

    //printf("ligne : %s\n", ligne);
    fichierCSV=fopen(nomFichier, "a");
    fprintf(fichierCSV, ligne);
    fclose(fichierCSV);
}

void annulerSaisie(char* nom,char* prenom,char* classe)
{
    FILE* fichier = NULL;
    char chaine[100] = {0};
    //char caractere = 0;
    //int nbLigne = 0;
    //long position = 0;

    sprintf(chaine, "fichiersEleve\\%s%s%s.txt", classe, nom, prenom);
    /*if(DEBUG)
        printf("DEBUG : nomFichierAnnule : %s\n", chaine);*/

    fichier = fopen(chaine, "r+");

    /*if(fichier == NULL)
    {
        printf("Probleme fichier\n");
        exit(EXIT_FAILURE);
    }*/
    fgets(chaine, 100, fichier);
    //printf("Chaine Releve : %s\n", chaine);
    fseek(fichier, -18, SEEK_END);
    //position = ftell(fichier);
    //printf("position dans le fichier : %ld\n", position);
    fprintf(fichier, "-----ANNULE-----\n");
    fclose(fichier);

}

int avertissDouble(SDL_Surface* ecran)
{
    SDL_Surface* image = NULL;
    SDL_Event event;
    SDL_Rect position;
    position.x=0;
    position.y=0;
    int continuer = 1;
    image = IMG_Load("alerteDouble.png");

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255,255));
    SDL_BlitSurface(image, NULL, ecran, &position);
    SDL_Flip(ecran);

    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            exit(EXIT_FAILURE);
            break;
        case SDL_MOUSEBUTTONUP:
            if(event.button.button==SDL_BUTTON_LEFT)
            {
                if(event.button.x>=158 && event.button.x<=262 && event.button.y>=496 && event.button.y<=539)
                {
                    continuer = 0;
                    return 1;
                }
                if(event.button.x>=314 && event.button.x<=415 && event.button.y>=492 && event.button.y<=538)
                {
                    continuer = 0;
                    return 0;
                }
            }
            break;
        }
    }
    SDL_FreeSurface(image);
    return 1;
}

int ajoutManuel(SDL_Surface* ecran,Mix_Chunk* son, TTF_Font* police, char* nom, char* prenom, char* classe, char* mode)
{
    char code[5] = {0};
    char caractereARemplir = 0;
    char aubers = 0;
    long releve = 0;
    int etude = 0;
    long numLigne = 0;
    char nomFichier[100] = "tableauEleve";
    SDL_Surface* imageCode = NULL;
    SDL_Surface* imageChoix = NULL;
    SDL_Surface* affCode = NULL;

    SDL_Event event;
    SDL_Rect positionImage, posCode;
    SDL_Color couleurNoire = {0,0,0};
    positionImage.x=0;
    positionImage.y=0;
    posCode.x=185;
    posCode.y=269;
    imageCode = IMG_Load("scanManuelCode.png");
    imageChoix = IMG_Load("scanManuelMode.png");
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255,255));
    SDL_BlitSurface(imageCode, NULL, ecran, &positionImage);
    SDL_Flip(ecran);
    int continuer = 1, i=0;

    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            exit(EXIT_FAILURE);
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
                    Mix_PlayChannel(5, son, 0);
                 break;
            case SDLK_1:
                 if(i<=3)
                 {
                    strcat(code, "1");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, son, 0);
                 break;
            case SDLK_2:
                 if(i<=3)
                 {
                    strcat(code, "2");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, son, 0);
                 break;
            case SDLK_3:
                 if(i<=3)
                 {
                    strcat(code, "3");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, son, 0);
                 break;
            case SDLK_4:
                 if(i<=3)
                 {
                    strcat(code, "4");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, son, 0);
                 break;
            case SDLK_5:
                 if(i<=3)
                 {
                    strcat(code, "5");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, son, 0);
                 break;
            case SDLK_6:
                 if(i<=3)
                 {
                    strcat(code, "6");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, son, 0);
                 break;
            case SDLK_7:
                 if(i<=3)
                 {
                    strcat(code, "7");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, son, 0);
                 break;
            case SDLK_8:
                 if(i<=3)
                 {
                    strcat(code, "8");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, son, 0);
                 break;
            case SDLK_9:
                 if(i<=3)
                 {
                    strcat(code, "9");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, son, 0);
                 break;
            case SDLK_KP0:
                 if(i<=3)
                 {
                    strcat(code, "0");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, son, 0);
                 break;
            case SDLK_KP1:
                 if(i<=3)
                 {
                    strcat(code, "1");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, son, 0);
                 break;
            case SDLK_KP2:
                 if(i<=3)
                 {
                    strcat(code, "2");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, son, 0);
                 break;
            case SDLK_KP3:
                 if(i<=3)
                 {
                    strcat(code, "3");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, son, 0);
                 break;
            case SDLK_KP4:
                 if(i<=3)
                 {
                    strcat(code, "4");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, son, 0);
                 break;
            case SDLK_KP5:
                 if(i<=3)
                 {
                    strcat(code, "5");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, son, 0);
                 break;
            case SDLK_KP6:
                 if(i<=3)
                 {
                    strcat(code, "6");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, son, 0);
                 break;
            case SDLK_KP7:
                 if(i<=3)
                 {
                    strcat(code, "7");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, son, 0);
                 break;
            case SDLK_KP8:
                 if(i<=3)
                 {
                    strcat(code, "8");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, son, 0);
                 break;
            case SDLK_KP9:
                 if(i<=3)
                 {
                    strcat(code, "9");
                    i++;
                 }
                 else
                    Mix_PlayChannel(5, son, 0);
                 break;
            case SDLK_BACKSPACE:
                    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255,255));
                    SDL_BlitSurface(imageCode, NULL, ecran, &positionImage);
                    if(i!=0)
                        i--;
                    else
                        Mix_PlayChannel(5, son, 0);
                    code[i] = '\0';
                    break;
            case SDLK_RETURN:
                continuer = 0;
                //checkListe, checkNomPrenom, choixMode etc...
                releve = strtol(code, NULL, 10);
                choixFichier(nomFichier, releve, classe, &etude, 0);
                numLigne = checkListe(nomFichier, releve);
                if(numLigne==99)
                    return 0;
                checkNomPrenom(nomFichier, numLigne, nom, prenom, 0);
                SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255,255));
                SDL_BlitSurface(imageChoix, NULL, ecran, &positionImage);
                SDL_Flip(ecran);
                choixMode(&caractereARemplir);
                choixModeManuel(mode, caractereARemplir);
                remplirFichier(classe, nom, prenom, etude, "VIDE",1, caractereARemplir);
                break;
            default:
                break;
        }
    }
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255,255));
    SDL_BlitSurface(imageCode, NULL, ecran, &positionImage);
    affCode = TTF_RenderText_Blended(police, code, couleurNoire);
    SDL_BlitSurface(affCode, NULL, ecran, &posCode);
    SDL_Flip(ecran);
}
SDL_FreeSurface(imageCode);
SDL_FreeSurface(imageChoix);
SDL_FreeSurface(affCode);
return 1;
}

void choixModeManuel(char* mode, char caractere)
{
        switch(caractere)
        {
        case 'a':
            sprintf(mode, "Garderie 7h15");
            break;
        case 'b':
            sprintf(mode, "Garderie 8h");
            break;
        case 'c':
            sprintf(mode, "Cantine");
            break;
        case 'd':
            sprintf(mode, "Garderie 16h30");
            break;
        case 'e':
            sprintf(mode, "Etude");
            break;
        case 'f':
            sprintf(mode, "Garderie 17h30");
            break;
        case 'g':
            sprintf(mode, "Garderie 18h30");
            break;
        case 'h':
            sprintf(mode, "Cantine Exceptionel");
            break;
        }
}


void choixMode(char* caractere)
{
    SDL_Event event;
    int continuer = 1;

    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_MOUSEBUTTONUP:
            if(event.button.x>=31 && event.button.x<=297 && event.button.y>=69 && event.button.y<=128)
            {
                *caractere = 'a';
                continuer = 0;
            }

            if(event.button.x>=30 && event.button.x<=256 && event.button.y>=165 && event.button.y<=226)
            {
                *caractere = 'b';
                continuer = 0;
            }

            if(event.button.x>=30 && event.button.x<=185 && event.button.y>=270 && event.button.y<=321)
            {
                *caractere = 'c';
                continuer = 0;
            }

            if(event.button.x>=30 && event.button.x<=315 && event.button.y>=368 && event.button.y<=421)
            {
                *caractere = 'd';
                continuer = 0;
            }

            if(event.button.x>=379 && event.button.x<=498 && event.button.y>=69 && event.button.y<=125)
            {
                *caractere = 'e';
                continuer = 0;
            }

            if(event.button.x>=377 && event.button.x<=654 && event.button.y>=167 && event.button.y<=225)
            {
                *caractere = 'f';
                continuer = 0;
            }

            if(event.button.x>=380 && event.button.x<=661 && event.button.y>=260 && event.button.y<=322)
            {
                *caractere = 'g';
                continuer = 0;
            }
            if(event.button.x>=377 && event.button.x<=715 && event.button.y>=361 && event.button.y<=426)
            {
                *caractere = 'h';
                continuer = 0;
            }
            break;
        case SDL_QUIT:
            continuer = 0;
            exit(EXIT_FAILURE);
            break;
        }
    }

}
