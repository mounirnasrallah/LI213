#ifndef __CHAINE_H__
#define __CHAINE_H__

 /* Structure d'un point d'une chaine */

typedef struct point {
double x,y; /* Coordonnees du point */
struct point * ptSuiv ; /* Pointeur vers le point suivant dans la chaine */
} Point ;

/* Element de la liste chaine des chaines */

typedef struct chaine {
int numero ; /* Numero de la chaine */
Point * uneExtremite ; /* Une des 2 extremites de la chaine */
struct chaine * chSuiv ; /* Lien vers la chaine suivante */
} Chaine ;

/* Liste chainee des chaines */

typedef struct listechaine {
int gamma ; /* Nombre maximal de fibres par chaine */
int nbchaine ; /* Nombre de chaines */
Chaine * LCh; /* La liste des chaines */
} ListeChaine ;

# endif
