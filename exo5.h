#ifndef EXO5
#define EXO5

typedef struct _ABRe{
    double x,y;
    Noeud* ptrNoeud;
    struct _ABRe* fg;
    struct _ABRe* fd;
}ABRe;

ABRe* recherche_ABRe(ABRe* A,double x,double y);
ABRe* creer_ABRe(double x,double y,int u);
Noeud* inserer_ABRe(ABRe** A,double x,double y,int* u);
void initialisation_arbre(ListeChaine *L, ABRe** A);
void convertir_arbre_to_commodite_inserer_reseau(ABRe* A, Reseau* R);
void creer_reseau_avec_arbre(ABRe* A, Reseau* R);
void voisin_et_cables(ABRe* A,ListeChaine *L,Reseau* R);
void ajouter_voisins(Noeud* precedent, Noeud* courant);
int mainExo5(char* fichier_entrer, char* fichier_sortie);
#endif
