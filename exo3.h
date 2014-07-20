#ifndef EXO3
#define EXO3
void recree_reseau(ListeChaine *L, Reseau *R);
int compare(double x1, double y1, double x2, double y2);
int cable_existe_liste_triee(Noeud* precedent, Noeud* courant);
void ajouter_voisins_liste_triee(Noeud* precedent, Noeud* courant);
void voisin_et_cables_liste_triee(ListeChaine *L,Reseau* R);
CelluleLNoeud* rechercheNoeudPourVoisins(Reseau *R,double x, double y);
void insererEnTete(Reseau *R, CelluleLNoeud * _cellulenoeud);
void insererMilieu(Reseau *R, CelluleLNoeud * _cellulenoeudAinserer,CelluleLNoeud * _cellulenoeud);
void insererEnFin(Reseau *R, CelluleLNoeud * _cellulenoeudAinserer,CelluleLNoeud * _cellulenoeud);
CelluleLNoeud* rechercheNoeud(Reseau *R,double x, double y);
Noeud* recherche_cree_noeud(Reseau *R, double x, double y,int *u);
int mainExo3(char* fichier_entrer, char* fichier_sortie);
#endif
