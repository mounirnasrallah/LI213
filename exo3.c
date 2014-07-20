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



#define NB_MBAX 4334
#define EPSILON 1





int cable_existe_liste_triee(Noeud* precedent, Noeud* courant){
    
    Voisin* _voisin = courant->LVoisins;
    while(_voisin!=NULL){
        if(_voisin->v == precedent->u){
            return 1;
        }
        _voisin = _voisin->voisSuiv;
    }
    return 0;
}

void ajouter_voisins_liste_triee(Noeud* precedent, Noeud* courant){
    
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
            if(_voisin->v == courant->u || (cable_existe_liste_triee(precedent,courant)==1)){
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



void voisin_et_cables_liste_triee(ListeChaine *L,Reseau* R){
    
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
        
        _commodite->extr1 = (rechercheNoeudPourVoisins(R,_point->x,_point->y))->ptrnoeud->u;
        
        _point_preced = _point;
        
        _point = _point->ptSuiv;
        
        while(_point->ptSuiv!=NULL){
            
            ajouter_voisins(rechercheNoeudPourVoisins(R,_point->x,_point->y)->ptrnoeud,(rechercheNoeudPourVoisins(R,_point->x,_point->y))->ptrnoeud);
            
            _point_preced = _point;
            _point = _point->ptSuiv;
        }
        
        ajouter_voisins((rechercheNoeudPourVoisins(R,_point_preced->x,_point_preced->y))->ptrnoeud,(rechercheNoeudPourVoisins(R,_point->x,_point->y))->ptrnoeud);
        
        _commodite->extr2 = (rechercheNoeudPourVoisins(R,_point->x,_point->y))->ptrnoeud->u;
        
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


/*
 ********************************************************************************************************************************************************
 ********************************************************************************************************************************************************
 ********************************************************************************************************************************************************
 ********************************************************************************************************************************************************
 
 */



void insererEnTete(Reseau *R, CelluleLNoeud * _cellulenoeud){
    
    CelluleLNoeud* tete = R->LNoeuds;
    R->LNoeuds = _cellulenoeud;
    _cellulenoeud->noeudSuiv = tete;

}

void insererMilieu(Reseau *R, CelluleLNoeud * _cellulenoeudAinserer,CelluleLNoeud * _cellulenoeud){
    
    CelluleLNoeud* suivant = _cellulenoeud->noeudSuiv;
    _cellulenoeud->noeudSuiv = _cellulenoeudAinserer;
    _cellulenoeudAinserer->noeudSuiv = suivant;
    
}

void insererEnFin(Reseau *R, CelluleLNoeud * _cellulenoeudAinserer,CelluleLNoeud * _cellulenoeud){
    
    _cellulenoeud->noeudSuiv = _cellulenoeudAinserer;
    
}


CelluleLNoeud* rechercheNoeudPourVoisins(Reseau *R,double x, double y){
    
    CelluleLNoeud* _parcourirCellule = R->LNoeuds;
    CelluleLNoeud* _cellulePrecedente = _parcourirCellule;
    
    while(_parcourirCellule!=NULL){
        
        switch(compare(x,y,_parcourirCellule->ptrnoeud->x,_parcourirCellule->ptrnoeud->y)){
            case 0 : return _parcourirCellule;
            case 1 : return _cellulePrecedente;
        }
        _cellulePrecedente = _parcourirCellule;
        _parcourirCellule= _parcourirCellule->noeudSuiv;
    }
    
    return _cellulePrecedente; 
    
}

CelluleLNoeud* rechercheNoeud(Reseau *R,double x, double y){

    CelluleLNoeud* _parcourirCellule = R->LNoeuds;
    CelluleLNoeud* _cellulePrecedente = _parcourirCellule;
    
    while(_parcourirCellule!=NULL){
        
        switch(compare(x,y,_parcourirCellule->ptrnoeud->x,_parcourirCellule->ptrnoeud->y)){
            case 0 : return _parcourirCellule;
            case 1 : return _cellulePrecedente;
        }
        _cellulePrecedente = _parcourirCellule;
        _parcourirCellule= _parcourirCellule->noeudSuiv;
    }
    
    return _cellulePrecedente;
    
}


//  *********************************************************************************************************************************************************************
//  *********************************************************************************************************************************************************************
//
// recherche_cree_noeud
//
//  *********************************************************************************************************************************************************************
//  ********************************************************************************************************************************************************************


Noeud* recherche_cree_noeud(Reseau *R, double x, double y,int *u) {
    
    
    CelluleLNoeud* _parcourirCellule;
    
    if(R->LNoeuds==NULL){
        
        Noeud* _noeud = (Noeud*) malloc(sizeof(Noeud));
        if(_noeud==NULL){
            printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__);
        }
        _noeud->x = x;
        _noeud->y = y;
        _noeud->u = *u;
        (*u)++;
        
        CelluleLNoeud* _cellulenoeud = (CelluleLNoeud*) malloc(sizeof(CelluleLNoeud));
        if(_cellulenoeud==NULL){
         printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__);
            return;
        }
        _cellulenoeud->ptrnoeud = _noeud;
        insererEnTete(R,_cellulenoeud);
        
        return _noeud;
        
    }
    else{
        
        _parcourirCellule = rechercheNoeud(R,x,y);
        
        if(compare(x,y,_parcourirCellule->ptrnoeud->x,_parcourirCellule->ptrnoeud->y)==0){
            
            return _parcourirCellule->ptrnoeud ;
        }
        else{
        
        Noeud* _noeud = (Noeud*) malloc(sizeof(Noeud));
            if(_noeud==NULL){
                printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__);
                return;
            }
        _noeud->x = x;
        _noeud->y = y;
        _noeud->u = *u;
        (*u)++;
            
        CelluleLNoeud* _cellulenoeud = (CelluleLNoeud*) malloc(sizeof(CelluleLNoeud));
        
            if(_cellulenoeud==NULL){
                printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__);
                return;
            }
            
        _cellulenoeud->ptrnoeud = _noeud;
            
        int comp = compare(x,y,_parcourirCellule->ptrnoeud->x,_parcourirCellule->ptrnoeud->y);

        if(_parcourirCellule==R->LNoeuds && comp==1){
            insererEnTete(R,_cellulenoeud);
            return _noeud;
        }
        if(_parcourirCellule==R->LNoeuds && comp==2){
            insererEnFin(R,_cellulenoeud,_parcourirCellule);
            return _noeud;
        }
        if(_parcourirCellule->noeudSuiv==NULL && comp==2){
            insererEnFin(R,_cellulenoeud,_parcourirCellule);
            return _noeud;
        }
        if(_parcourirCellule->noeudSuiv==NULL && comp==1){
            insererMilieu(R,_cellulenoeud,_parcourirCellule);
            return _noeud;
        }
        else{
            insererMilieu(R,_cellulenoeud,_parcourirCellule);
            return _noeud;
        }
        }
    }
}

  


//  *********************************************************************************************************************************************************************
//  *********************************************************************************************************************************************************************
//
// recree_reseau
//
//  *********************************************************************************************************************************************************************
//  *********************************************************************************************************************************************************************


void recree_reseau(ListeChaine *L, Reseau *R){

    int i,k;
    k=1;
    int u = 0; 
    Chaine * _chaine;
    Point* _point;
    Noeud* nouveauNoeud;
    CelluleLCommodite * _commodite_prec;
    R->gamma = L->gamma;
    
    _chaine = L->LCh;
    
    _point = _chaine->uneExtremite;
    
    
    while(_chaine!=NULL){
        
        CelluleLCommodite* _commodite = (CelluleLCommodite*)malloc(sizeof(CelluleLCommodite*));
        
        if(_commodite==NULL){
            printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__);
            return;
        }
        
        _point = _chaine->uneExtremite;
    
        i = 1;
        
        while(_point->ptSuiv!=NULL){
            
                Noeud* nouveauNoeud = recherche_cree_noeud(R,_point->x,_point->y,&u);
            
            if(i==1){
                _commodite->extr1=nouveauNoeud->u;
                i++;
               
            }
        
            _point = _point->ptSuiv;
        }
        
        nouveauNoeud = recherche_cree_noeud(R,_point->x,_point->y,&u);
        _commodite->extr2=nouveauNoeud->u;
        
                
        if(k==1){
            R->LCommodites = _commodite;
            _commodite_prec = _commodite;
            k++;
            
        }
        else{
            _commodite_prec->commSuiv = _commodite;
            
            
            _commodite_prec = _commodite;
        }
        
        _chaine = _chaine->chSuiv;
    }
    
    voisin_et_cables_liste_triee(L,R);
    
    R->nbNoeuds = compteNoeuds(R);
    
}





//  *********************************************************************************************************************************************************************
//  *********************************************************************************************************************************************************************
//
// compare, Retourne 1 si x1 y1 est avant x2 y2, retourne 2 sinon
//
//  *********************************************************************************************************************************************************************
//  *********************************************************************************************************************************************************************



int compare(double x1, double y1, double x2, double y2){

    if(x1==x2){
        if(y1==y2){
            return 0;
        }
        else{
            if(y1<y2){
                return 1;
            }
            else{
                return 2;
            }
        }
    }
    else{
        if(x1<x2){
            return 1;}
        else{
            return 2;
        }
}
}








//  *********************************************************************************************************************************************************************
//  *********************************************************************************************************************************************************************
//
//  main
//
//  *********************************************************************************************************************************************************************
//  *********************************************************************************************************************************************************************


int mainExo3(char* fichier_entrer, char* fichier_sortie){

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

    recree_reseau(liste,R);
    
     R->nbNoeuds = compteCable(R);

    ecrit_reseau_disque(R,ecr);

    fclose(ecr);
    
    fclose(fic);
    
    free(liste);
    
    free(R);

    return 0;

}
