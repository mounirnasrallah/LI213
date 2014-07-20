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
#include <math.h>
#include "reseau.h"
#include "chaine.h"
#include "exo1.h"
#include "exo2.h"
#include "exo3.h"
#include "exo4.h"

#define NB_TAB 8000




int cable_existe_hachage(Noeud* precedent, Noeud* courant){
    
    Voisin* _voisin = courant->LVoisins;
    while(_voisin!=NULL){
        if(_voisin->v == precedent->u){
            return 1;
        }
        _voisin = _voisin->voisSuiv;
    }
    return 0;
}

void ajouter_voisins_hachage(Noeud* precedent, Noeud* courant, Hachage **H){
    
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
            if(_voisin->v == courant->u || (cable_existe_hachage(precedent,courant)==1)){
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



void voisin_et_cables_hachage(ListeChaine *L,Reseau* R, Hachage **H){
    
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
        
        _commodite->extr1 = (recherche_noeud(R,H,_point->x,_point->y))->ptrNoeud->u;
        
        _point_preced = _point;
        
        _point = _point->ptSuiv;
        
        while(_point->ptSuiv!=NULL){
            
            ajouter_voisins(recherche_noeud(R,H,_point->x,_point->y)->ptrNoeud,(recherche_noeud(R,H,_point->x,_point->y))->ptrNoeud);
            
            _point_preced = _point;
            _point = _point->ptSuiv;
        }
        
        ajouter_voisins((recherche_noeud(R,H,_point_preced->x,_point_preced->y))->ptrNoeud,(recherche_noeud(R,H,_point->x,_point->y))->ptrNoeud);
        
        _commodite->extr2 = (recherche_noeud(R,H,_point->x,_point->y))->ptrNoeud->u;
        
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


 /*****************************************************************************************************************
  
    clef
  
 *****************************************************************************************************************/


int clef(double x, double y){
    return (int)(y+(((x+y)*(x+y+1))/2));
}

int fonction_hachage(int key){
    
    double a = (sqrt(5)-1)/2;
    
    int hash = (int)(NB_TAB*((key*a)-((int)(key*a))));
    
    if(hash>NB_TAB){
        return NB_TAB;
    }
    else{
        return hash;
    }
    
     
}


Hachage* recherche_noeud(Reseau *R,Hachage **H,double x, double y){
    
    int key = clef(x,y);
    int hash = fonction_hachage(key);
    Hachage* contenu = H[hash];
    
    if(contenu==NULL){
    }
    else{
    while(contenu->hachSuiv!=NULL){
        if(contenu->ptrNoeud->x==x && contenu->ptrNoeud->y==y){
            return contenu;
        }
        contenu=contenu->hachSuiv;
    }
    }
    return contenu;
}

Noeud* recherche_cree_noeud_hachage(Reseau *R, Hachage **H, double x, double y,int * v){
    
    
    int key = clef(x,y);
    int hash = fonction_hachage(key);
    Hachage* contenu = H[hash];
    
    if(contenu==NULL){
        Noeud* _noeud = (Noeud*) malloc(sizeof(Noeud));
        if(_noeud==NULL){
            printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__);
            return;
        }
        _noeud->x = x;
        _noeud->y = y;
        _noeud->u = *v;
        (*v)++;
        
        Hachage* _hachage = (Hachage*)malloc(sizeof(Hachage));
        if(_hachage==NULL){
            printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__);
            return;
        }
        _hachage->x = x;
        _hachage->y = y;
        _hachage->ptrNoeud = _noeud;
        H[hash] = _hachage;
        
        inserer_cellule_reseau(R,_noeud);
        
        return _noeud;
    }
    else{
        
        Hachage* _recherche = recherche_noeud(R,H,x,y);
        
        if(_recherche->ptrNoeud->x == x && _recherche->ptrNoeud->y == y){
            return _recherche->ptrNoeud;
        }
        else{
            Noeud* _noeud = (Noeud*) malloc(sizeof(Noeud));
            if(_noeud==NULL){
                printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__);
                return;
            }
    
            _noeud->x = x;
            _noeud->y = y;
            _noeud->u = *v;
            (*v)++;
            
            Hachage* _hachage = (Hachage*)malloc(sizeof(Hachage));
            if(_hachage==NULL){
                printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__);
                return;
            }
            _hachage->x = x;
            _hachage->y = y;
            _hachage->ptrNoeud = _noeud;
            
            _recherche->hachSuiv = _hachage;
            
            inserer_cellule_reseau(R,_noeud);
            
            return _noeud;
        }
    }
}


void inserer_cellule_reseau(Reseau* R, Noeud* noeud){

    CelluleLNoeud* preced = R->LNoeuds;
    CelluleLNoeud* nouvelle_cellule = (CelluleLNoeud*)malloc(sizeof(CelluleLNoeud));
    if(nouvelle_cellule==NULL){
        printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__);
        return;
    }
    nouvelle_cellule->ptrnoeud = noeud;
    nouvelle_cellule->noeudSuiv = preced;
    R->LNoeuds = nouvelle_cellule;
    R->nbNoeuds = R->nbNoeuds + 1;
    
}


void recree_reseau_hachage(ListeChaine *L, Reseau *R){
    
    int u =0;
    int *v = &u;
    int c;
    
    R->gamma = L->gamma;
    
    Hachage * H[NB_TAB];
    
    for(c=0;c<NB_TAB;c++){
        H[c]=NULL;
    }
    
    int i,k;
    k=1;
    Chaine * _chaine;
    Point* _point;
    Noeud* nouveauNoeud;
    CelluleLCommodite * _commodite_prec;
    
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
            
            Noeud* nouveauNoeud = recherche_cree_noeud_hachage(R,H,_point->x,_point->y,v);
            
            if(i==1){
                _commodite->extr1=nouveauNoeud->u;
                i++;
            }
            
            _point = _point->ptSuiv;
        }
        
        nouveauNoeud = recherche_cree_noeud_hachage(R,H,_point->x,_point->y,v);
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
    
    voisin_et_cables_hachage(L,R,H);
    
    R->nbNoeuds = compteNoeuds(R);

}


//  *********************************************************************************************************************************************************************
//  *********************************************************************************************************************************************************************
//
//  main
//
//  *********************************************************************************************************************************************************************
//  *********************************************************************************************************************************************************************


int mainExo4(char* fichier_entrer, char* fichier_sortie){
    
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
    
    recree_reseau_hachage(liste,R);
    
    ecrit_reseau_disque(R,ecr);
    
    fclose(ecr);
    
    fclose(fic);
    
    free(liste);
    
    free(R);
    
    return 0;
    
}





