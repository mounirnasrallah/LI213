#ifndef EXO2
#define EXO2
void lecture_fichier_reseau(FILE *f, Reseau *R);
int compteCable(Reseau *R);
int recherche_voisin(Reseau *R, int u);
void ecrit_reseau_disque(Reseau *R, FILE *f);
int compteNoeuds(Reseau *R);
int mainExo2(char* fichier_entrer, char* fichier_sortie);
#endif
