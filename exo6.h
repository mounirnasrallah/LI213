#ifndef EXO6 
#define EXO6 
#define NB_MAX_TAS 30

typedef struct _element{
    
    int numero;
    double clef;
    
}ElementTas;

struct _tas{
    
    int n;
    ElementTas tab[NB_MAX_TAS];
    
}Tas;


int fils_droit(int i);
int fils_gauche(int i);
int racine();
int pere(int i);
int nonRacine(int i);
int minimum(Tas* t);
void initialisation_tas(Tas*t);
int taille(Tas*t);
int est_un_noeud(Tas* t,int i);
int a_un_fils_gauche(Tas *t,int i);
int a_un_fils_droit(Tas *t,int i);
int est_une_feuille(Tas *t,int i);
void echanger(Tas* t, int i, int j);
￼void monter(Tas *t,int i);
void descendre(Tas *t,int i);
￼int plus_petit_fils(Tas *t,int i);
bool recherche(Tas* t,int i);
void insertion_minimum(Tas* t,ElementTas element);
void supprimer(Tas* t,int sup);
void distance(Noeud* un, Noeud* deux);

#endif