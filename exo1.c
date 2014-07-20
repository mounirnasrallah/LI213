/* ********************************************************
   ********************************************************
   ********************************************************
 
    NASR ALLAH Mounir
    Numéro étudiant : 3001324
 
 
    Projet: Réorganisation d'un réseau de fibres optiques
    2011-2012

    21 Mai 2012
 
   ********************************************************
   ********************************************************
   ********************************************************
 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reseau.h"
#include "chaine.h"
#include "exo1.h"
#include "exo2.h"
#include "exo3.h"

#define NB_MBAX 4334 // Constante pour le fscanf ( commentaire )






//  ----------------------------------------------------------------------------------
//  ----------------------------------------------------------------------------------
//
// longueurChaine, parcours la Chaine l pour y compter le nombre de points
//
//

double longueurChaine(Chaine *l){
    
    double cmpt=0;                      // variable compteur
    Point* tmp = l->uneExtremite;       // Pointeur temporaire pour parcourir la chaine, est égale au point de l'extremité de la chaine, puis évolue ensuite. 
    
    while (tmp!=NULL)                   // Tant que l'on a pas fini de parcourir la chaine
    {
        cmpt++;                         // On incremente le compteur 
        tmp = tmp->ptSuiv;              // tmp est égale au point suivant de la chaine
    }
    
    return cmpt;                        // On retourne le nombre total de points de la chaine

}




//  ----------------------------------------------------------------------------------
//  ----------------------------------------------------------------------------------
//
// longueurTotale, parcours la ListeChaine pour y compter le nombre de Chaine
//
//

double longueurTotale(ListeChaine *L){
    
    double resultat = 0;                // Variable contenant le résultat final
    Chaine* tmp = L->LCh;               // Pointeur temporaire afin de parcourir la ListeChaine
    
    while(tmp!=NULL)                    // Tant que l'on a pas fini de parcourir la ListeChaine
    {                  
        resultat = resultat+1;          // On increment la varaible resultat
        tmp = tmp->chSuiv;              // On passe à la chaine suivante
    }
    
    return resultat;                    // On retourne le nombre de chaines

}




//  ----------------------------------------------------------------------------------
//  ----------------------------------------------------------------------------------
//
// compte_point, parcours la ListeChaine pour y sommer le nombre de point de chaque Chaine
//
//

int compte_point(ListeChaine *L){
    
    int resultat = 0;                                   // Variable contenant le résultat final
    Chaine* tmp = L->LCh;                               // Pointeur temporaire afin de parcourir la ListeChaine
        
    while (tmp!=NULL){                                  // Tant que l'on a pas fini de parcourir la ListeChaine
        resultat += (int)longueurChaine(tmp);           // On somme le variable resultat avec le nombre de points de la chaine courante
        tmp = tmp->chSuiv;                              // On passe à la chaine suivante
    }
    return resultat;                                    // On retourne le nombre de points total
}




//  ----------------------------------------------------------------------------------
//  ----------------------------------------------------------------------------------
//
// lecture_chaine, lis les données du fichier f, et les transforme en ListeChaine
//
//

void lecture_chaine(FILE *f, ListeChaine *L){ 
 
    char c;                                                                             // Caractere temporaire
    int numero;                                                                         // numero contient le numero de la chaine courante
    int nombre;                                                                         // nombre contient le nombre de points de la chaine courante
    int i,j,k;                                                                          // Variables temporaires pour les boucles
    int nombreChaine, gamma;                                                            // nombreChaine contient la valeur de NbChain du fichier, et gamma celui de Gamma
    char com [NB_MBAX];                                                                 // Contient le commentaire ( ligne commencant par c )
    double a,b;                                                                         // Variables temporaires pour capturer les coordonnees des points
    
    
    
    while(fscanf(f,"%c",&c) != EOF && c=='c' && getc(f)!='\n'){                          // Tant que l'on a un commentaire
        
        fscanf(f,"%s",com);
                                                                                         // On capture le commentaire
        if(strcmp(com,"NbChain:")==0){ fscanf(f,"%d\n",&nombreChaine);  }                // Si le commentaire est "NbChain:", on capture sa valeur et on la stocke dans 
                                                                                         // la variable nombreChaine
        
        else if(strcmp(com,"Gamma:")==0){fscanf(f,"%d\n",&gamma); }                      // Si le commentaire est "Gamma:", on capture sa valeur et on la stocke dans 
                                                                                         // la variable gamma
    }
    
    
    L->gamma = gamma;                                                                    // On affecte à la ListeChaine L, le gamma que l'on a precedement capturé
    L->nbchaine = nombreChaine;                                                          // On affecte à la ListeChaine L, le nombreChaine que l'on a precedement capturé
    
    
    Chaine* tabChaine [nombreChaine];                                                    // On créé un tableau de pointeurs ayant nombreChaine élements
    
    
    for(i=0;i<nombreChaine;i++){                                                         // On capture tout les points de la chaine
        
        Chaine* tmp_chaine = (Chaine*)malloc(sizeof(Chaine));                            // On alloue l'espace pour une Chaine
        
        if(tmp_chaine==NULL){ 
            printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__); // Verification de l'allocation dynamique
            return; 
        }
        
        tabChaine[i] = tmp_chaine;                                                       // On stocke l'adresse de la nouvelle chaine dans le tableau tabChaine
        
        fscanf(f,"h %d %d : ", &numero,&nombre);                                         // on capture le numero de la chaine, et le nombre de points de la chaine
        
        tmp_chaine->numero = numero;                                                     // On affecte à la variable numero de la nouvelle chaine tmp_chaine le numero capturé
        
        Point* tmp_point_prec;                                                           // Le pointeur tmp_point_prec, contiendra l'adresse du point precedent

        
        for(j=0;j<nombre;j++){                                                           // Pour j allant de 0 à nombre-1
             
            fscanf(f,"%lf %lf /", &a,&b);                                                // On capture les coordonnees du point
            Point* tmp_point = (Point*)malloc(sizeof(Point));                            // On alloue dynamiquement un nouveau point   
            
            if(tmp_point==NULL){ 
                printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__); // Verification de l'allocation dynamique
                return; 
            }
            
            tmp_point->x = a;                                                             // On affecte au point créé sa coordonnee x
            tmp_point->y = b;                                                             // On affecte au point créé sa coordonnee y
            
            if(j==0){                                                                     // Si c'est le premier point de la chaine, on l'affecte comme etant l'extremité 
                tmp_chaine->uneExtremite = tmp_point;                                     // de la nouvelle chaine, et tmp_point_prec est egale à tmp_point
                tmp_point_prec = tmp_point;
            }
            else if(j==nombre-1){                                                         // Si c'est le dernier point de la chaine, le pointeur ptSuiv est NULL, et  
                tmp_point_prec->ptSuiv = tmp_point;                                       // le pointeur ptSuiv de l'avant dernier point est egale à l'adresse du dernier point
                tmp_point->ptSuiv = NULL;
            }
            else{
               tmp_point_prec->ptSuiv = tmp_point;                                        // Sinon le point suivant du point precedent est le point courant
               tmp_point_prec = tmp_point;                                                // et le point courant devient le point precedent
            }
            
                                  
        }
       while(fscanf(f,"\n")){}  
    }
        
    L->LCh = tabChaine[0];                                                                // La listeChaine L, a comme premiere Chaine la chaine pointé par tabChaine[0]
                                                                                          // Donc la premiere chaine capturé
    
    for(k=0;k<nombreChaine-1;k++){                                                          
        tabChaine[k]->chSuiv = tabChaine[k+1];                                            // On raccorde les chaines entre elles
    }
    
        tabChaine[nombreChaine-1]->chSuiv = NULL;                                         // La derniere chaine, a comme chaine suivante "NULL"
  
    
    
}




//  ----------------------------------------------------------------------------------
//  ----------------------------------------------------------------------------------
//
// ecrit_chaine_txt, parcours ListeChaine, et y ecrit les données dans le fichier f
//
//

void ecrit_chaine_txt(ListeChaine *L, FILE *f){ 
    
    fprintf(f,"c NbChain:%d \n",L->nbchaine);                                               // Ecrit un commentaire contenant le nombre de chaine dans le fichier
    fprintf(f,"c Gamma:%d \n",L->gamma);                                                    // Ecrit un commentaire contenant le gamma dans le fichier
    fprintf(f,"c \n");                                                                      // Ecrit un commentaire vide
    
    Chaine * tmp_chaine;                                                                    // Pointeur temporaire pour parcourir les chaines
    Point * tmp_point;                                                                      // Pointeur temporaire pour parcourir les points
    
    tmp_chaine = L->LCh;                                                                    // la chaine courante est la premiere de la listeChaine
    
    while(tmp_chaine!=NULL){                                                                // Tant que l'on a pas parcouru toutes les chaines
        
        tmp_point = tmp_chaine->uneExtremite;                                               // Le point courant est l'extremite de la chaine courante
        
        fprintf(f,"h %d %d :",tmp_chaine->numero,(int)longueurChaine(tmp_chaine));               // On ecrit dans le fichier, le numero et le nombre de points de la chaine courante
        
        while(tmp_point!=NULL){                                                             // Tant qu'il y a des points dans la chaine
            
            fprintf(f," %lf %lf /",tmp_point->x,tmp_point->y);                              // On ecrit les points dans le fichier
            tmp_point = tmp_point->ptSuiv;                                                  // On passe au point suivant
        }
        
        tmp_chaine = tmp_chaine->chSuiv;                                                    // On passe à la chaine suivante
        fprintf(f,"\n");                                                                    // On met un retour à la ligne
        
    }
    
       
}



void ecrit_chaine_xfig(ListeChaine *L, FILE *f, int zoom, int epaisseur) {
    
    int n, m, i=0, j=0, a=0, b=0;
    n=longueurTotale(L);
    m=longueurChaine(L->LCh);
    int tab[n][m+1][2]; 
    Point *tmp_pt;
    Chaine *tmp_ch=L->LCh;
    while(tmp_ch) {
        tmp_pt=tmp_ch->uneExtremite;
        while(tmp_pt)
        {
            tab[j][i][0]= (int) (tmp_pt->x * 100 *zoom);
            tab[j][i][1]= (int) (tmp_pt->y * 100* zoom);
            i++;
            tmp_pt=tmp_pt->ptSuiv;
        }
        tab[j][i][0]=0; 
        j++;
        i=0;
        tmp_ch=tmp_ch->chSuiv;
    }
    
    
    fprintf(f, "#FIG 3.2\nLandscape\nCenter\nMetric\nA4\n100.00\nSingle\n-2\n1500 2\n");
   
    
    int nb_pt[n];
    i=0;
    j=0;
    
        for(i=0;i<n;i++) {
        
        while(tab[i][j][0]!=0) j++;
        nb_pt[i]=j;
        
        j=0;
        
    }
    
    for(a=0;a<n;a++) {
        
        for(b=0;b<nb_pt[a]; b++) {
            fprintf(f, "1 4 0 2 %d 0 50 0 10 0.000 1 0.0000 %d %d 100 100 0 0 0 0\n", a, tab[a][b][0], tab[a][b][1]);
            
        }
    }
    fprintf(f, "\n");
    
    
    a=0;b=0;
    for(a=0;a<n;a++) {
        fprintf(f, "2 1 -1 %d 0 %d 50 0 -1 0.000 0 0 -1 0 0 %d\n",epaisseur, a, nb_pt[a]);
        fprintf(f, "        ");
        for(b=0;b<nb_pt[a];b++) {
            fprintf(f, "%d %d ", tab[a][b][0], tab[a][b][1]);
        }
        fprintf(f, "\n");
    }
    
    fclose(f);
}



//  ----------------------------------------------------------------------------------
//  ----------------------------------------------------------------------------------
//
// ecrit_chaine_txt, parcours ListeChaine, et y ecrit les données dans le fichier f
//
//


int mainExo1(char* fichier_entrer, char* fichier_sortie){
     
       FILE *fic; 
       fic = fopen(fichier_entrer, "r");                                               // Ouverture du fichier 00014_burma.cha en lecture
        
        
       ListeChaine* liste = (ListeChaine*)malloc(sizeof(ListeChaine));                     // Creation d'une ListeChaine
        
        if(liste==NULL){ 
            printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__);   // Verification de l'allocation dynamique
            return EXIT_FAILURE; 
        }
        
       if(fic == NULL){
           printf("Erreur lors de l'ouverture du fichier %s \n ",fichier_entrer);            // Verification de l'ouverture du fichier
           return EXIT_FAILURE; 
        }
       else{
           lecture_chaine(fic,liste);
           FILE *ecr; 
           ecr = fopen(fichier_sortie, "a");
           ecrit_chaine_txt(liste,ecr);
           fclose(ecr);
       }
        fclose(fic);
    
    free(liste);
    
        return 0;
}







