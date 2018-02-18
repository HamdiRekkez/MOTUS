#include <stdio.h>
#include <time.h>
#include <string.h>
#include <windows.h>

typedef struct joueur{
                      char nom[20];
                      int score;
                      struct joueur *suiv;
                      }un_joueur;
                      
///////////////////////////////////////
/////////////COLOR///////////////////
///////////////////////////////////////          
void color(int Texte,int Fond)
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,Fond*16+Texte);
}
////////////////////////////////////////
////ouverture du fichier////////////////
////////////////////////////////////////
char* ouverture()
{
      int nombre_caractere;
      FILE *f;
      char *fichier;
      fichier=(char*)malloc(30*sizeof(char));
do
      {
      printf(" + Choisissez la longueur du mot : \n");
      printf("     - Pour mots de 6 caracteres Tapez 1\n");
      printf("     - Pour mots de 7 caracteres Tapez 2\n");
      printf("     - Pour mots de 8 caracteres Tapez 3\n");
      scanf("%d",&nombre_caractere);
      }while((nombre_caractere!=1) && (nombre_caractere!=2) && (nombre_caractere!=3));
      if (nombre_caractere==1)(fichier="mots6");
      else if (nombre_caractere==2)(fichier="mots7");
      else fichier="mots8";
      return(fichier);
}
///////////////////////////////////////
///////////Enregistrer partie//////////
///////////////////////////////////////

int save_game()
{
     FILE *f;
     un_joueur joueur1,joueur2;
     int nb_mot_jouer,nb_tentative;
     f = fopen ("save","w");
     if (f==NULL)
     {printf("Un Erreur est survenue !!");}
     else{
          fwrite(&joueur1,sizeof(un_joueur),1,f);
          fwrite(&joueur2,sizeof(un_joueur),1,f);
          fprintf(f,"%d/n",nb_mot_jouer);
          fprintf(f,"%d/n",nb_tentative);
          }
     fclose(f);
     printf("Partie Enregistrer !!");
     return 0;
 }
////////////////////////////////////////
///////Choix aléatoire du mot///////////
////////////////////////////////////////
char* choix_mot(char *fichier)
{
FILE *f;
int nb_lignes=0,i,j;
char c,*mot;
int  nb_caract;
srand(time(NULL));
f = fopen (fichier,"rt");

///on compte le nombre de lignes dans le fichier
 while ( c = fgetc(f),! feof (f) )
     {
	 if(c == '\n')
		 { nb_lignes++;
		 }
      }
 fclose(f);
mot=(char*)malloc(9*sizeof(char));

//choix du mot dans le fichier choisit
f = fopen(fichier, "rt");//pour revenir au debut
srand(time(NULL));
	j=rand()%nb_lignes;
	
i=0;
 do{
  fscanf(f,"%s",mot);
  i++;
  }while(i!=j);
  fclose(f);
   return(mot);
 }
////////////////////////////////////////
//////////saisi du mot//////////////////
////////////////////////////////////////
 
char * saisi ()
{
char * mot_saisi;
int i;
mot_saisi=(char*)malloc(10*sizeof(char));
printf("\n Entrer mot : ");
scanf("%s",mot_saisi);
printf("\n");
if (mot_saisi=="1")
save_game(); //Quitter et enregistrer partie.
else
{
//Controle sur la saisie du joueur.
for(i=0;i<strlen(mot_saisi);i++)
{
if(mot_saisi[i]=='é'||mot_saisi[i]=='è'||mot_saisi[i]=='é'||mot_saisi[i]=='ê'||mot_saisi[i]=='ë') mot_saisi[i]='E';
if(mot_saisi[i]=='û') mot_saisi[i]='U';
if(mot_saisi[i]=='ô') mot_saisi[i]='O';
if(mot_saisi[i]=='ç') mot_saisi[i]='C';
if(mot_saisi[i]=='â') mot_saisi[i]='A';
if(mot_saisi[i]=='î') mot_saisi[i]='I';
}
}
return (strupr(mot_saisi));
}
////////////////////////////////////////
//////////affichage en cloueur//////////
///////////////////////////////////////
void jaune (char car) //affiche la lettre en jaune (existe dans le mot mais mal placé)
{
color(12,0);
printf("%c ",car);
color(7,0);
}
void rouge (char car) //affiche la lettre en rouge (bien placé)
{
color(14,0); 
printf("%c ",car);
color(7,0);
}
void blanc (char car) //affiche la lettre en blanc (n'existe pas dans le mot)
{
printf("%c ",car);
}
////////////////////////////////////////
//////////affichage de l'aide//////////
///////////////////////////////////////
int affich_aide()
{
    system("cls");
    color(9,0);
    printf("\n\n\n                               **** AIDE ****\n\n");
    printf("     - Il s'agit de deviner un mot choisi aleatoirement par votre ordinateur.\n\n");
    printf("     -Il existe 3 niveaux de difficulte selon la longueur du mot\n");
    printf("             mots de 6, 7 ou 8 caractéres\n\n");
    printf("     - Le Joueur dispose de 7 tentatives pour deviner un mot\n\n");
    printf("     -Chaque tentative non reussie fait perdre le joueur 10 points.\n\n");
    printf("     -Le Jeu se termine apres que le joueur devine 5 mots.\n\n");
    printf("     -Le jeu est illimite.Amusez vous !!\n\n");
    return 0;
    }
////////////////////////////////////////
//////////affichage de credit//////////
///////////////////////////////////////
int affich_credit()
{
    system("cls");
    color(9,0);
    printf("\n\n\n                               **** CREDIT ****\n\n");
    printf("                                     MOTUS V1.0\n\n");
    printf("     Developpe par : Hamdi Rakkez\n");
    printf("                      Houssem Louati\n\n");
    printf("     Le jeu a ete developpe dans le cadre d'un\n\n");
    printf("     mini-projet a ESPRIT en 3eme annee telecom.\n\n");
    printf("     Ce mini-projet a ete encadre par :Mr. Khodjet Ghazi \n\n");
    printf("                                       Mme Ben Amor Imen  \n\n");
    return 0;
    }
////////////////////////////////////////
//////////comparaison///////////////////
////////////////////////////////////////
char* comparaison(char* un_mot,char* le_mot,char* result)
{  int i,j;
int A[strlen(le_mot)],B[strlen(le_mot)];
int place[strlen(le_mot)];

for(i=0;i<strlen(le_mot);i++)
{A[i]=0;B[i]=0;place[i]=0;} //Initialisation à 0 du 3 tableau

for(i=0;i<strlen(le_mot);i++)
   {
     if( un_mot[i]==le_mot[i]) //si un caractere est bien place
        {
        result[i]=le_mot[i];
        A[i]=1;B[i]=1;
        place[i]=2;//affectation final apré test
        }
  }
for(i=0;i<strlen(le_mot);i++)  //si un caractere est mal place
     {  for(j=0;j<strlen(le_mot);j++)
           if(un_mot[i]==le_mot[j])
               if (A[j]==0)
                  if(B[i]==0)
                   {
                   A[j]=1;B[i]=1;
                   place[i]=1; //affectation final apré test
                   }
       }
for(i=0;i<strlen(le_mot);i++)
       {if(place[i]==0){blanc(un_mot[i]);} //caractere n'existe pas dans le mot
        if(place[i]==1){rouge(un_mot[i]);} //caractere existe mais mal placé
        if(place[i]==2){jaune(un_mot[i]);} //caractere est bien placé
       }
         return(result);
}
