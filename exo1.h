#ifndef EXO1
#define EXO1
double longueurChaine(Chaine *l);
double longueurTotale(ListeChaine *L);
int compte_point(ListeChaine *L);
void lecture_chaine(FILE *f, ListeChaine *L);
void ecrit_chaine_txt(ListeChaine *L, FILE *f);
int mainExo1(char* fichier_entrer, char* fichier_sortie);
#endif
