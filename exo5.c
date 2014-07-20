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
#include "exo4.h"
#include "exo5.h"


#define NB_MBAX 10000
#define EPSILON 1




ABRe* recherche_ABRe(ABRe* A,double x,double y){
    
    if( (A->fd==NULL) && (A->fg==NULL) ){
        return A;
    }
    
    int comparaison = compare(x,y,A->x,A->y);
    
    if ((comparaison==1) && (A->fg==NULL)){
        return A;
    }
    
    if ((comparaison==2) && (A->fd!=NULL)){
        return recherche_ABRe(A->fd,x,y);
    }
    
    if (comparaison==0)
    {   
        return A;   
    }
    
    if ((comparaison==1) && (A->fg!=NULL)){
        return recherche_ABRe(A->fg,x,y);
    }
    
    if ((comparaison==2) && (A->fd==NULL)){
        return A;
    }
}


ABRe* creer_ABRe(double x,double y,int u){

    Noeud* _noeud = (Noeud*) malloc(sizeof(Noeud));
    if(_noeud==NULL){
        printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__);
        return;
    }
    _noeud->x = x;
    _noeud->y = y;
    _noeud->u = u; 
    
    
    ABRe* _abr = (ABRe*)malloc(sizeof(ABRe));
    if(_abr==NULL){
        printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__);
        return;
    }
    _abr->x = x;
    _abr->y =y;
    
    _abr->ptrNoeud = _noeud;
    
    _abr->fg = NULL;
    _abr->fd = NULL;
    
    return _abr;
    
    
}

Noeud* inserer_ABRe(ABRe** A,double x,double y,int* u){
    
    if(*A==NULL){
        *A = creer_ABRe(x,y,(*u));
        (*u)++;
    }
    else{
        
        ABRe* _recherche = recherche_ABRe(*A, x, y);
        
        int comparaison = compare(x,y,_recherche->x,_recherche->y);
        
        if(comparaison==0){
            return _recherche->ptrNoeud;
        }
        
        if(comparaison==1){
            _recherche->fg = creer_ABRe(x,y,(*u));
            (*u)++;
            return _recherche->fg->ptrNoeud;
        }
        else{
            
            _recherche->fd = creer_ABRe(x,y,(*u));
            (*u)++;
            return _recherche->fd->ptrNoeud;
        }
        
    
    }
    
}




void initialisation_arbre(ListeChaine *L, ABRe** A){

    
    Chaine * _chaine;
    Point* _point;
    
    
    _chaine = L->LCh;
    
    int u = 0;
    
    while(_chaine!=NULL){
        
        _point = _chaine->uneExtremite;
        
        while(_point!=NULL){
            
            inserer_ABRe(A,_point->x,_point->y,&u);
             
            _point = _point->ptSuiv;
        }
        
        _chaine = _chaine->chSuiv;
    }
    
}


void convertir_arbre_to_commodite_inserer_reseau(ABRe* A, Reseau* R){

    if(R->LNoeuds==NULL){
        CelluleLNoeud* _cellule = (CelluleLNoeud*)malloc(sizeof(CelluleLNoeud));
        if(_cellule==NULL){
            printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__);
            return;
        }
        _cellule->ptrnoeud = A->ptrNoeud;
        R->LNoeuds = _cellule;
    }
    else{
        CelluleLNoeud* _cellule = (CelluleLNoeud*)malloc(sizeof(CelluleLNoeud));
        if(_cellule==NULL){
            printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__);
            return;
        }
        CelluleLNoeud* _cellulePrecedente = R->LNoeuds;
    
        _cellule->ptrnoeud = A->ptrNoeud;
    
        _cellule->noeudSuiv = _cellulePrecedente;
    
        R->LNoeuds = _cellule;
    }
}

void creer_reseau_avec_arbre(ABRe* A, Reseau* R){
    
    if(A==NULL){
    }
    else{
        
        creer_reseau_avec_arbre(A->fd,R);
        
        convertir_arbre_to_commodite_inserer_reseau(A,R);
        
        creer_reseau_avec_arbre(A->fg,R);
        
    }
    
    
}


int cable_existe(Noeud* precedent, Noeud* courant){

    Voisin* _voisin = courant->LVoisins;
    while(_voisin!=NULL){
        if(_voisin->v == precedent->u){
            return 1;
        }
        _voisin = _voisin->voisSuiv;
    }
    return 0;
}

void ajouter_voisins(Noeud* precedent, Noeud* courant){

    Voisin* voisin;
    Voisin* precedent_voisin;
    
    if(precedent->LVoisins==NULL){
        voisin = (Voisin*)malloc(sizeof(Voisin));
        if(voisin==NULL){
            printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__);
            return;
        }
        voisin->v = courant->u;
        precedent->LVoisins = voisin;
    }
    else{
        Voisin* _voisin = precedent->LVoisins;
        while(_voisin!=NULL){
            if(_voisin->v == courant->u || (cable_existe(precedent,courant)==1)){
                return;
            }
            else{
            }
            precedent_voisin = _voisin;
            _voisin = _voisin->voisSuiv;
        }
        voisin = (Voisin*)malloc(sizeof(Voisin));
        if(voisin==NULL){
            printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__);
            return;
        }
        voisin->v = courant->u;
        precedent_voisin->voisSuiv = voisin;
    }

}



void voisin_et_cables(ABRe* A,ListeChaine *L,Reseau* R){

    Chaine * _chaine;
    Point* _point;
    Point* _point_preced;
    CelluleLCommodite* commodite_precedente;
    
    _chaine = L->LCh;
    
    int premierPassage = 1;
    
    while(_chaine!=NULL){
        
        _point = _chaine->uneExtremite;
        
        CelluleLCommodite* _commodite = (CelluleLCommodite*)malloc(sizeof(CelluleLCommodite*));
        if(_commodite==NULL){
            printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__);
            return;
        }
        _commodite->extr1 = (recherche_ABRe(A,_point->x,_point->y))->ptrNoeud->u;
        
        _point_preced = _point;
        
        _point = _point->ptSuiv;
        
        while(_point->ptSuiv!=NULL){
            
            ajouter_voisins((recherche_ABRe(A,_point_preced->x,_point_preced->y))->ptrNoeud,(recherche_ABRe(A,_point->x,_point->y))->ptrNoeud);
            
            _point_preced = _point;
            _point = _point->ptSuiv;
        }
        
        ajouter_voisins((recherche_ABRe(A,_point_preced->x,_point_preced->y))->ptrNoeud,(recherche_ABRe(A,_point->x,_point->y))->ptrNoeud);
        
        _commodite->extr2 = (recherche_ABRe(A,_point->x,_point->y))->ptrNoeud->u;
        
        if(premierPassage==1){
            R->LCommodites = _commodite;
            commodite_precedente = _commodite;
            premierPassage++;
        }
        else{
            commodite_precedente->commSuiv=_commodite;
            commodite_precedente=_commodite;
        }
        
        _chaine = _chaine->chSuiv;
    }
    


}


//  *********************************************************************************************************************************************************************
//  *********************************************************************************************************************************************************************
//
// recree_reseau
//
//  *********************************************************************************************************************************************************************
//  *********************************************************************************************************************************************************************


void recree_reseau_ABRe(ListeChaine *L, Reseau *R){
    
    R->gamma = L->gamma;
    
    ABRe* A = NULL;
    
    initialisation_arbre(L,&A);
    
    creer_reseau_avec_arbre(A,R);
    
    voisin_et_cables(A,L,R);
    
    R->nbNoeuds = compteNoeuds(R);
    
      
}







//  *********************************************************************************************************************************************************************
//  *********************************************************************************************************************************************************************
//
//  main
//
//  *********************************************************************************************************************************************************************
//  *********************************************************************************************************************************************************************


int mainExo5(char* fichier_entrer, char* fichier_sortie){
    
    FILE *fic;
    fic = fopen(fichier_entrer, "r");
    
    ListeChaine* liste = (ListeChaine*)malloc(sizeof(ListeChaine));                     // Creation d'une ListeChaine
    if(liste==NULL){
        printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__);
        return;
    }
    
    Reseau* R = (Reseau*)malloc(sizeof(Reseau));
    if(R==NULL){
        printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__);
        return;
    }
    
    lecture_chaine(fic,liste);
    
    FILE *ecr;
    
    ecr = fopen(fichier_sortie, "a");
    
    recree_reseau_ABRe(liste,R);
    
    ecrit_reseau_disque(R,ecr);
    
    fclose(ecr);
    
    fclose(fic);
    
    free(liste);
    
    free(R);
    
    return 0;
    
}


