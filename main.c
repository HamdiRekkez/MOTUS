#include "entete_fonction.h"
////////////////////////////////////////
////////////////main///////////////////
//////////////////////////////////////
int main()
{
int nb_caract,i,mode,k,score =70;
int rubrique=0;
int choixMenu;
char *fichier,*le_mot,*un_mot,*result,car,val='1',date;
char b;
un_joueur joueur1,joueur2;
// Menu //
MENU:
system("cls");

color(9,0);
printf("\n");
printf("         MMM       MMM   OOOOOO   TTTTTTTTTTT  UUUU   UUUU   SSSSSSS \n");
color(2,0);
printf("          MMM     MMM   OOO  OOO  TTTTTTTTTTT   UU     UU   SSS    SS\n");
color(3,0);
printf("          MMMMM MMMMM   OO    OO      TTT       UU     UU   SS       \n");
color(4,0);  
printf("          MM  MMM  MM   OO    OO      TTT       UU     UU    SSSSSSS \n");
color(5,0);
printf("          MM   M   MM   OO    OO      TTT       UU     UU          SS\n"); 
color(6,0); 
printf("          MM       MM   OOO  OOO      TTT       UUU   UUU   SS    SSS\n");
color(8,0);
printf("         MMMM     MMMM   OOOOOO       TTT        UUUUUUU     SSSSSSS \n");
color(2,0);
printf("\n\n\n                               **** M E N U ****\n\n");
printf("                           1.COMMENCER NOUVELLE PARTIE\n");
printf("                           2.AIDE\n");
printf("                           3.CREDIT\n");
printf("                           4.Quitter\n");
printf("\n\nVotre choix?\n\n");
printf("->");
scanf("%d", &choixMenu);

switch(choixMenu)
    {
                     case 1:
                          //jouer
                          goto JOUER;
                          break;
                     case 2:
                          //afficher aide
                          affich_aide();
                          system("pause");
                          goto MENU;
                          break;  
                     case 3:
                          //afficher credit
                          affich_credit();
                          system("pause");
                          goto MENU;
                          break;
                     case 4:
                          goto EXIT;
                          break;
                     default:
                             goto MENU;
                             break;
    }
JOUER:
color(9,0);
system("cls");
printf("**********************************BIENVENUE************************************\n");
printf("*******************************************************************************\n");
printf("*************************     M   O   T   U   S     ***************************\n");  
printf("*******************************************************************************\n\n\n");
color(7,0);
fichier=(char*)malloc (30*sizeof(char));
le_mot=(char*) malloc (9*sizeof(char));
un_mot=(char*) malloc (9*sizeof(char));
result=(char*) malloc (9*sizeof(char));

fichier=ouverture(); //Ouverture du fichier associé au choix pris
joueur1.score=0;
joueur2.score=0;
    printf(" + Donner le mode du jeu: \n");
printf("     - Tapez 1 pour mode solo \n");
printf("     - Tapez 2 pour mode multi-joueur \n");
scanf("%d",&mode);

if(mode==2)
{
   printf(" + Joueur 1: Entrez votre nom puis votre prenom : \n");
   scanf("%s ",&joueur1.nom);
   fflush(stdin);

   printf(" + Joueur 2: Entrez votre nom puis votre prenom : \n\n");
   scanf("%s ",&joueur2.nom);
   fflush(stdin);
   system("pause");
}
else{
     printf(" + Entrez votre nom puis votre prenom : \n\n");
     scanf("%s ",&joueur1.nom);
     fflush(stdin);
     printf("\n");
     system("pause");
     }
system("cls"); //Vidage d'écran

for(k=0;k<5;k++)
{
   le_mot=choix_mot(fichier);
   printf("\n");
   color(13,0);
   printf("***** Attention Nouveau Mot *****\n");
   printf(" ****** Joueur : %s ******\n\n",joueur1.nom);
   BASC:
   color(7,0);
   
   *(result+0)=*(le_mot+0);
   for(i=1;i<strlen(le_mot);i++)
   *(result+i)='-';
   jaune(*(result+0));
   for(i=1;i<strlen(le_mot);i++)
   blanc(*(result+i));
   printf("\n");
   //boucle de 7 tentative pour diviner le mot
   for(i=0;i<7;i++)
{
   printf("\nIl vous reste %d chances\n",7-i);
   un_mot=saisi();
   if(strlen(le_mot)==strlen(un_mot))
   result=comparaison(un_mot,le_mot,result);
   else
   printf("\nLe mot que vous avez entre est incomplet !!");
   printf("\n\nResultat: %s\n\n",result);
   if((strcmp( un_mot,le_mot)==0))
   {color(3,0);
   printf("**** Bravo vous avez devine le mot apres %d coup(s) ****\n",i+1);
   color(7,0);
   save_game();
   break;}
   }
   printf("Le mot est : %s\n",le_mot);
   if(mode==2)
{
   system("cls");
   color(13,0);
   printf("***** Attention Nouveau Mot *****\n");
   printf(" ****** Joueur : %s ******\n\n",joueur2.nom);
   color(7,0);
   goto BASC;
}
}

if(mode==2) //mode multi-joueurs (2 joueurs)
{
printf("Le score de %s est : %d \n",joueur1.nom,joueur1.score);
printf("Le score de %s est : %d \n",joueur2.nom,joueur2.score);
}
else //Mode solo (1 joueur)
joueur1.score=score;
printf("Votre score est : %d \n",joueur1.score);

system("Pause");
printf("Voulez vous Jouer une autre fois ?? (y/n)");
scanf("%c",&b);
if (b='y')goto MENU;
EXIT:
return(0);
}
