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

#define NB_MBAX 4334                                                           // Constante pour le fscanf ( commentaire )






//  ----------------------------------------------------------------------------------
//  ----------------------------------------------------------------------------------
//
// lecture_fichier_reseau, lis les données du fichier f, et les transforme en Reseau
//
//

void lecture_fichier_reseau(FILE *f, Reseau *R){
    char c;                                                                    // Caractere temporaire

    int nbNodes;                                                               // Variable qui va contenir le nombre de noeud
    int nbCables;                                                              // Variable qui va contenir le nombre de cables
    int gamma;                                                                 // Variable qui va contenir le gamma
    int numero;                                                                // Variable qui va contenir le numero
    int extr1;                                                                 // Variable qui va contenir l'extremité 1 d'une commodité
    int extr2;                                                                 // Variable qui va contenir l'extremité 2 d'une commodité
    int numeroNoeud;                                                           // Variable qui va contenir le numero du noeud
    int voisin;                                                                // Variable qui va contenir le voisin d'un noeud
    int i;                                                                     // Variable temporaire pour boucle

    char com [NB_MBAX];                                                        // Contient le commentaire ( ligne commencant par c )
    double a,b;                                                                // Variables temporaires pour capturer les coordonnees des points





    while(fscanf(f,"%c",&c) != EOF && c=='c' && getc(f)!='\n'){                // Tant que l'on a un commentaire
        fscanf(f,"%s",com);                                                    // On capture le commentaire
            if(strcmp(com,"NbNodes:")==0){ fscanf(f,"%d\n",&nbNodes);  }       // Si le commentaire est "NbNodes:", on capture sa valeur et on la stocke dans nbNodes
            else if(strcmp(com,"NbCables:")==0){fscanf(f,"%d\n",&nbCables); }  // Si le commentaire est "NbCables:", on capture sa valeur et on la stocke dans nbCables
            else if(strcmp(com,"Gamma:")==0){fscanf(f,"%d\n",&gamma); }        // Si le commentaire est "Gamma:", on capture sa valeur et on la stocke dans gamma
    }




    R->gamma = gamma;                                                          // On affecte au réseau R, le gamma que l'on a precedement capturé
    R->nbNoeuds = nbNodes;                                                     // On affecte au réseau R, le nombre de noeud que l'on a precedement capturé




    for(i=0;i<nbNodes;i++){                                                    // Pour tout les noeuds


            fscanf(f,"v %d %lf %lf \n",&numero,&a,&b);                         // On recupere leurs coordonnees et leurs numéros
            Noeud* tmp_noeud = (Noeud*)malloc(sizeof(Noeud));                  // On alloue dynamiquement un nouveau noeud


            if(tmp_noeud==NULL){
               printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__); // Verification de l'allocation dynamique
                return;
            }



            tmp_noeud->u = numero;                                              // On affecte à la variable u du nouveau Noeud tmp_noeud le numero capturé
            tmp_noeud->x = a;                                                   // On affecte à la variable x du nouveau Noeud tmp_noeud la coordonnee x capturé
            tmp_noeud->y = b;                                                   // On affecte à la variable x du nouveau Noeud tmp_noeud la coordonnee y capturé
            tmp_noeud->LVoisins = NULL;                                         // On affecte au pointeur LVoisins du nouveau Noeud tmp_noeud la valeur NULL




            CelluleLNoeud* tmp_cellule_noeud = (CelluleLNoeud*)malloc(sizeof(CelluleLNoeud)); // On alloue dynamiquement une nouvelle CelluleNoeud

            if(tmp_cellule_noeud==NULL){
               printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__); // Verification de l'allocation dynamique
                return;
            }



            tmp_cellule_noeud->ptrnoeud = tmp_noeud;                            // On affecte au pointeur ptrnoeud de la nouvelle CelluleNoeud créé,
                                                                                // l'adresse du nouveau Noeud créé.


            CelluleLNoeud* tmp_cellule_noeud_prec;                              // Pointeur contenant la CelluleNoeud precedente
            Noeud* tmp_noeud_prec;                                              // Pointeur contenant le Noeud precedent


    /* Si c'est le premier passage, le pointeur LNoeud du Réseau pointe vers la premiere CelluleNoeud créé, la CelluleNoeud precedente est egale à la
    CelluleNoeud courante, le Noeud precedent est egale au Noeud courant */

            if(i==0){
                R->LNoeuds = tmp_cellule_noeud;
                tmp_cellule_noeud_prec = tmp_cellule_noeud;
                tmp_noeud_prec=tmp_noeud;
            }


    /* Si c'est le dernier passage, le pointeur noeudSuiv de la CelluleNoeud precedente pointe vers la nouvelle celluleNoeud créé, et cette derniere
    celluleNoeud n'a pas de suivant, donc tmp_cellule_noeud->noeudSuiv = NULL   */

            else if(i==nbNodes-1){
                tmp_cellule_noeud_prec->noeudSuiv = tmp_cellule_noeud;
                tmp_cellule_noeud->noeudSuiv=NULL;
            }


    /* Sinon le pointeur noeudSuiv de la CelluleNoeud precedente pointe vers la nouvelle celluleNoeud créé, et la CelluleNoeud precedente est egale à
     la CelluleNoeud courante  */

            else{
                tmp_cellule_noeud_prec->noeudSuiv = tmp_cellule_noeud;
                tmp_cellule_noeud_prec = tmp_cellule_noeud;

            }


    }

    while(fscanf(f,"c \n")){}                                                   // Saut des commentaires


    for(i=0;i<nbCables;i++){

        fscanf(f,"a %d %d\n",&numeroNoeud,&voisin);
        CelluleLNoeud* celluleDunNoeud = R->LNoeuds;
        Noeud* noeudDuneCellule;
        Voisin* tmp_voisin;

        while(celluleDunNoeud!=NULL){
            noeudDuneCellule = celluleDunNoeud->ptrnoeud;
            if(noeudDuneCellule->u==numeroNoeud){
                    if(noeudDuneCellule->LVoisins==NULL){
                    Voisin* voisinDuNoeud = (Voisin*)malloc(sizeof(Voisin));
                        if(voisinDuNoeud==NULL){
                            printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__);
                            return;
                        }

                    voisinDuNoeud->v = voisin;
                    noeudDuneCellule->LVoisins = voisinDuNoeud;
                    voisinDuNoeud->voisSuiv = NULL;

                }
                else{
                    tmp_voisin = noeudDuneCellule->LVoisins;

                    while(tmp_voisin->voisSuiv!=NULL) {

                        tmp_voisin=tmp_voisin->voisSuiv;
                    }

                    Voisin* voisinDuNoeud = (Voisin*)malloc(sizeof(Voisin));
                    if(voisinDuNoeud==NULL){
                        printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__);
                        return;
                    }
                    voisinDuNoeud->v=voisin;
                    voisinDuNoeud->voisSuiv = NULL;

                    tmp_voisin->voisSuiv = voisinDuNoeud;


                }

            }

            celluleDunNoeud = celluleDunNoeud->noeudSuiv;
        }
    }

     while(fscanf(f,"c \n")){}

    i=0;

    while(fscanf(f,"%c",&c) != EOF && c=='k' && getc(f)!='\n'){
        fscanf(f," %d %d\n",&extr1,&extr2);

        CelluleLCommodite* commodite = (CelluleLCommodite*)malloc(sizeof(CelluleLCommodite));
        if(commodite==NULL){
            printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__);
            return;
        }
        commodite->extr1 = extr1;
        commodite->extr2 = extr2;

        CelluleLCommodite* commodite_prec;

        if(i==0){
            R->LCommodites = commodite;
            commodite_prec = commodite;
        }
        else{
            commodite_prec->commSuiv = commodite;
            commodite_prec = commodite;

        }

    i++;
    }



}


int compteCable(Reseau *R){

    int nb=0;
    CelluleLNoeud* celluleDunNoeud = R->LNoeuds;

    while(celluleDunNoeud!=NULL){
        Voisin* voisinDunNoeud = celluleDunNoeud->ptrnoeud->LVoisins;
        while (voisinDunNoeud!=NULL) {
          nb++;
          voisinDunNoeud = voisinDunNoeud->voisSuiv;
        }
        celluleDunNoeud = celluleDunNoeud->noeudSuiv;
    }

    return nb;
}

int compteNoeuds(Reseau *R){

    int nb=0;

    CelluleLNoeud* celluleDunNoeud = R->LNoeuds;

    while(celluleDunNoeud!=NULL){
        nb++;
        celluleDunNoeud = celluleDunNoeud->noeudSuiv;
    }

    return nb;
}

int recherche_voisin(Reseau *R, int u){
    CelluleLNoeud* celluleDunNoeud = R->LNoeuds;

    while(celluleDunNoeud!=NULL){
        if(celluleDunNoeud->ptrnoeud->u==u){
            if(celluleDunNoeud->ptrnoeud->LVoisins==NULL){return -1;}
            else{
                return celluleDunNoeud->ptrnoeud->LVoisins->v;
            }
        }
        else{}
        celluleDunNoeud = celluleDunNoeud->noeudSuiv;
    }
    return -1;
}


void ecrit_reseau_disque(Reseau *R, FILE *f){

    fprintf(f,"c NbNodes: %d \n",R->nbNoeuds);
    fprintf(f,"c NbCables: %d \n",compteCable(R));
    fprintf(f,"c Gamma: %d \n",R->gamma);
    fprintf(f,"c \n");

    CelluleLNoeud* celluleDunNoeud = R->LNoeuds;

    while(celluleDunNoeud!=NULL){
    fprintf(f,"v %d %lf %lf \n",celluleDunNoeud->ptrnoeud->u,celluleDunNoeud->ptrnoeud->x,celluleDunNoeud->ptrnoeud->y);
        celluleDunNoeud = celluleDunNoeud->noeudSuiv;
    }

    fprintf(f,"c \n");

    celluleDunNoeud = R->LNoeuds;
    Noeud* LeNoeud;
    Voisin* voisinDunNoeud;


        celluleDunNoeud = R->LNoeuds;

    while(celluleDunNoeud!=NULL){
        Voisin* voisinDunNoeud = celluleDunNoeud->ptrnoeud->LVoisins;
        if(voisinDunNoeud==NULL){}
        else{
            while (voisinDunNoeud!=NULL) {
                fprintf(f,"a %d %d \n",celluleDunNoeud->ptrnoeud->u,voisinDunNoeud->v);
                voisinDunNoeud = voisinDunNoeud->voisSuiv;
            }

        }
        celluleDunNoeud = celluleDunNoeud->noeudSuiv;
    }


    CelluleLCommodite* commodite = R->LCommodites;

    fprintf(f,"c \n");

    while(commodite!=NULL){
        fprintf(f,"k %d %d \n",commodite->extr1,commodite->extr2);
        commodite = commodite->commSuiv;
    }
}


void ecrit_reseau_xfig(Reseau *R, FILE *f,int epaisseur){

    int i=0;
    Reseau *tmp_r=R;
    int t[tmp_r->nbNoeuds];
    CelluleLNoeud *tmp=R->LNoeuds;



    int tab_donnees[R->nbNoeuds][2];
    for(i=0;i<tmp_r->nbNoeuds;i++) {
        tab_donnees[tmp_r->LNoeuds->ptrnoeud->u][0]= (int) tmp_r->LNoeuds->ptrnoeud->x *100 * 3;
        tab_donnees[tmp_r->LNoeuds->ptrnoeud->u][1]= (int) tmp_r->LNoeuds->ptrnoeud->y * 100 * 3;
        tmp_r->LNoeuds=tmp_r->LNoeuds->noeudSuiv;
    }

    while(tmp) {
        t[tmp->ptrnoeud->u]=0;
        while(tmp->ptrnoeud->LVoisins) {
            t[tmp->ptrnoeud->u]++;

            tmp->ptrnoeud->LVoisins=tmp->ptrnoeud->LVoisins->voisSuiv;
        }
        tmp=tmp->noeudSuiv;
    }
    printf("ici et %d\n", t[3]);

    fprintf(f, "#FIG 3.2\n");
    fprintf(f, "Landscape\n");
    fprintf(f, "Center\n");
    fprintf(f, "Metric\n");
    fprintf(f, "A4\n");
    fprintf(f, "100.00\n");
    fprintf(f, "Single\n");
    fprintf(f, "-2\n");
    fprintf(f, "1500 2\n");

    for(i=0;i<tmp_r->nbNoeuds;i++) {
        fprintf(f, "1 4 0 2 %d 0 50 0 10 0.000 1 0.0000 %d %d 100 100 0 0 0 0\n", i, tab_donnees[i][0], tab_donnees[i][1] );
    }

    while(tmp_r->LCommodites) {
        fprintf(f, "2 1 -1 %d 0 %d 50 0 -1 0.000 0 0 -1 0 0 2\n",epaisseur,i);
        fprintf(f, "        ");
        fprintf(f, "%d %d ",tab_donnees[tmp_r->LCommodites->extr1][0], tab_donnees[tmp_r->LCommodites->extr1][1] );
        fprintf(f, "%d %d\n",tab_donnees[tmp_r->LCommodites->extr2][0], tab_donnees[tmp_r->LCommodites->extr2][1] );
        tmp_r->LCommodites=tmp_r->LCommodites->commSuiv;
        i++;
    }

    fclose(f);

}


   int mainExo2(char* fichier_entrer, char* fichier_sortie){

       FILE *fic;
       fic = fopen(fichier_entrer, "r");
        Reseau* R = (Reseau*)malloc(sizeof(Reseau));
       if(R==NULL){
           printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__);
           return -1;
       }
       if(fic == NULL){
           printf("Erreur lors de l'ouverture du fichier");
            exit(1);
        }
       else{
           lecture_fichier_reseau(fic,R);
           FILE *ecr;
           ecr = fopen(fichier_sortie, "a");
           ecrit_reseau_disque(R,ecr);
           fclose(ecr);
       }
        fclose(fic);

        return 0;
    }




