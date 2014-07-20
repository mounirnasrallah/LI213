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

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "exo6.h"


int fils_droit(int i){
    return (i<<1)+1;
}

int fils_gauche(int i){
    return i<<1;
}

int racine(){
    return 1;
}

int pere(int i){
    if(i==1){
        return 1;
    }
    else{
        return i>>1;
    }
}

int nonRacine(int i){
    return i!=racine();
}

int minimum(Tas* t){
    return t->tab[racine()];
}

void initialisation_tas(Tas*t){
    t->n=0;
}
int taille(Tas*t){
    return t->n;
}

int est_un_noeud(Tas* t,int i) {
    return i<=taille(t);
}

int a_un_fils_gauche(Tas *t,int i) {
    return est_un_noeud(t,fils_gauche(i));
}

int a_un_fils_droit(Tas *t,int i) {
    return est_un_noeud(t,filsDroit(i));
}

int est_une_feuille(Tas *t,int i) {
    return ! a_un_fils_gauche(t,i);
}

void echanger(Tas* t, int i, int j){
    int tmp=t->tab[i]; 
    t->tab[i]=t->tab[j]; 
    t->tab[j]=tmp;
}

￼void monter(Tas *t,int i) {  ￼ ￼ 
    if (!nonRacine(i)) return; 
    ￼￼￼￼￼￼int pere_de_i = pere(i);
    ￼ if (t->tab[pere_de_i]->clef>t->tab[i]->clef) {
        echanger(t,i,pere_de_i);
        monter(t,pere_de_i);
    } 
}


void descendre(Tas *t,int i) {
    if (est_une_feuille(t,i)) return; 
    int fils=plusPetitFils(t,i);
    if (t->tab[i]->clef > t->tab[fils]->clef) { 
        echanger(t,fils ,i); 
        descendre(t,fils);
        ￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼} 
}

￼int plus_petit_fils(Tas *t,int i) { 
    if (! a_un_fils_droit(t,i)) {
        return filsGauche(i);
    } 
    else {
        int fg=fils_gauche(i);
        int fd=fils_droit(i); ￼ ￼
        return (t->tab[fg] < t->tab[fd])?fg:fd; 
    }
}

bool recherche(Tas* t,int i){
    if(t->tab[i]==NULL){
        return false;  
    }
    else{
        return true;
    }
}

void insertion_minimum(Tas* t,ElementTas element){
    if(t->n < NB_MAX_TAS){
        t->n++;
        t->tab[t->n]=element;
        monter(t,t->n);
    }
    else{
        printf("erreur");
    }
}

void supprimer(Tas* t,int sup){
    t->tab[sup] = NULL;
    
}


void distance(Noeud* un, Noeud* deux){
    return sqrt((((deux->x)-(un->x))*((deux->x)-(un->x)))+(((deux->y)-(un->y))*((deux->y)-(un->y))));
}



void dijkstra(Reseau* R){

    Tas* tasMin = (Tas*)malloc(sizeof(Tas));
    if(tasMin==NULL){
        printf("Erreur d'allocation dynamique ! malloc() Fichier : %s Ligne : %d \n ",__FILE__,__LINE__);
        return;
    }

}



int mainExo6(){
    
    
    return EXIT_SUCESS;
}