#ifndef __RESEAU_H__
#define __RESEAU_H__

 /* Element de la liste des noeuds voisins d'un noeud du reseau */

typedef struct voisin {
int v; /* Numero du voisin dans le Reseau*/
struct voisin * voisSuiv ; /* Pointeur sur le voisin suivant */
} Voisin ;

 /* Noeud du reseau */

typedef struct noeud {
int u; /* Numero du noeud dans le Reseau */
double x, y; /* Coordonnees du noeud */
Voisin * LVoisins ; /* Liste des noeuds voisins de u*/
} Noeud ;

/* Element de la liste chainee des noeuds du reseau */

typedef struct celluleLNoeud { 
Noeud * ptrnoeud ; /* Pointeur sur un noeud du reseau */
struct celluleLNoeud * noeudSuiv ; /* Noeud suivant dans la liste des noeuds */
} CelluleLNoeud ;

/* Element de la liste chainee des commodites du reseau */

typedef struct celluleLCommodite {
int extr1 , extr2 ;
struct celluleLCommodite * commSuiv ;
} CelluleLCommodite ;

/* Un reseau */

typedef struct {
int nbNoeuds ; /* Nombre total de noeuds dans le Reseau */
int gamma ; /* Nombre maximal de fibres dans un cable */
CelluleLCommodite * LCommodites ; /* Liste des commodites a relier */
CelluleLNoeud * LNoeuds ; /* Liste des noeuds du Reseau */
} Reseau ;

#endif
