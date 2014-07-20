#ifndef EXO4
#define EXO4

typedef struct _hachage{
    double x,y;
    Noeud* ptrNoeud;
    struct _hachage* hachSuiv;
}Hachage;

void inserer_cellule_reseau(Reseau* R, Noeud* noeud);
void recree_reseau_hachage(ListeChaine *L, Reseau *R);
Noeud* recherche_cree_noeud_hachage(Reseau *R, Hachage **H, double x, double y,int* v);
Hachage* recherche_noeud(Reseau *R,Hachage **H,double x, double y);
int fonction_hachage(int key);
int clef(double x, double y);
int mainExo4(char* fichier_entrer, char* fichier_sortie);
int cable_existe_hachage(Noeud* precedent, Noeud* courant);
void ajouter_voisins_hachage(Noeud* precedent, Noeud* courant, Hachage **H);
void voisin_et_cables_hachage(ListeChaine *L,Reseau* R, Hachage **H);
int mainExo4(char* fichier_entrer, char* fichier_sortie);
#endif
