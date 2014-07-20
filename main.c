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
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reseau.h"
#include "chaine.h"
#include "exo1.h"
#include "exo2.h"
#include "exo3.h"
#include "exo4.h"
#include "exo5.h"




//  *********************************************************************************************************************************************************************
//  *********************************************************************************************************************************************************************
//
//  main
//
//  *********************************************************************************************************************************************************************
//  *********************************************************************************************************************************************************************


int main(){

  
    struct rusage debut;
    struct rusage fin;

    int i=0;
    
    
    system("rm -f exercice1/* exercice2/* exercice3/* exercice4/* exercice5/*");
    
    
    char* fichiers_chaines[20]={"instances_chaines/00014_burma.cha","instances_chaines/00048_att.cha","instances_chaines/00076_eil.cha","instances_chaines/00144_pr.cha","instances_chaines/00280_a.cha","instances_chaines/00493_d.cha","instances_chaines/00666_fr.cha","instances_chaines/01400_fl.cha","instances_chaines/03795_fl.cha","instances_chaines/05934_rl.cha","instances_chaines/00022_ulysses.cha","instances_chaines/00052_berlin.cha","instances_chaines/00101_eil.cha","instances_chaines/00150_ch.cha","instances_chaines/00417_fl.cha","instances_chaines/00575_rat.cha","instances_chaines/00783_rat.cha","instances_chaines/02392_pr.cha","instances_chaines/04461_fnl.cha","instances_chaines/07397_pla.cha"};
    
    char* fichiers_reseaux[20]={"instances_reseaux/00014_burma.res","instances_reseaux/00048_att.res","instances_reseaux/00076_eil.res","instances_reseaux/00144_pr.res","instances_reseaux/00280_a.res","instances_reseaux/00493_d.res","instances_reseaux/00666_fr.res","instances_reseaux/01400_fl.res","instances_reseaux/03795_fl.res","instances_reseaux/05934_rl.res","instances_reseaux/00022_ulysses.res","instances_reseaux/00052_berlin.res","instances_reseaux/00101_eil.res","instances_reseaux/00150_ch.res","instances_reseaux/00417_fl.res","instances_reseaux/00575_rat.res","instances_reseaux/00783_rat.res","instances_reseaux/02392_pr.res","instances_reseaux/04461_fnl.res","instances_reseaux/07397_pla.res"};
    
    
    
    
    
    
    char* fichiersExo1[20]={"exercice1/00014_burma.cha","exercice1/00048_att.cha","exercice1/00076_eil.cha","exercice1/00144_pr.cha","exercice1/00280_a.cha","exercice1/00493_d.cha","exercice1/00666_fr.cha","exercice1/01400_fl.cha","exercice1/03795_fl.cha","exercice1/05934_rl.cha","exercice1/00022_ulysses.cha","exercice1/00052_berlin.cha","exercice1/00101_eil.cha","exercice1/00150_ch.cha","exercice1/00417_fl.cha","exercice1/00575_rat.cha","exercice1/00783_rat.cha","exercice1/02392_pr.cha","exercice1/04461_fnl.cha","exercice1/07397_pla.cha"};
    
       
    printf("******************************************************************  Exercice 1 ******************************************************************\n\n");
    
    
    for(i=0;i<20;i++){
     
        printf("*********************************************************\n");
        
    char *pathFichierIn=fichiers_chaines[i];  
        
    char *pathFichierOut=fichiersExo1[i];
    
    
    getrusage(RUSAGE_SELF,&debut);
    
    mainExo1(pathFichierIn,pathFichierOut);
    
    getrusage(RUSAGE_SELF,&fin);
    
    printf("Le temps utilisateur d'execution des instructions est de %ld.%06ld secondes \n",(long int)((fin.ru_utime.tv_sec - debut.ru_utime.tv_sec)),(long int)((fin.ru_utime.tv_usec - debut.ru_utime.tv_usec)) );
    
    printf("Le temps système d'execution des instructions est de %ld.%06ld secondes \n",(long int)((fin.ru_stime.tv_sec - debut.ru_stime.tv_sec)),(long int)((fin.ru_stime.tv_usec - debut.ru_stime.tv_usec)));
   
    
    printf("\n \n Le fichier de départ est %s \n",pathFichierIn);

    printf("\n");
    
    //system(cmd_fichiers_chaines[i]);

    printf("\n");
    
    printf("\n \n Le fichier de sortie est %s \n",pathFichierOut);
    
    printf("\n");
        
    //system(cmd_fichiersExo1[i]);  
            
    printf("\n");


    
    }

    
    
    
    /* EXO 2 */

    
    char* fichiersExo2[20]={"exercice2/00014_burma.cha","exercice2/00048_att.cha","exercice2/00076_eil.cha","exercice2/00144_pr.cha","exercice2/00280_a.cha","exercice2/00493_d.cha","exercice2/00666_fr.cha","exercice2/01400_fl.cha","exercice2/03795_fl.cha","exercice2/05934_rl.cha","exercice2/00022_ulysses.cha","exercice2/00052_berlin.cha","exercice2/00101_eil.cha","exercice2/00150_ch.cha","exercice2/00417_fl.cha","exercice2/00575_rat.cha","exercice2/00783_rat.cha","exercice2/02392_pr.cha","exercice2/04461_fnl.cha","exercice2/07397_pla.cha"};    
    
    printf("-------------------------------------------------\n  Exercice 2 \n-------------------------------------------------\n\n");
    
    
    for(i=0;i<20;i++){
        
        printf("*********************************************************\n");

        char *pathFichierIn=fichiers_reseaux[i];  
        
        char *pathFichierOut=fichiersExo2[i];
        
        
        getrusage(RUSAGE_SELF,&debut);
        
        mainExo2(pathFichierIn,pathFichierOut);
        
        getrusage(RUSAGE_SELF,&fin);
        
        printf("Le temps utilisateur d'execution des instructions est de %ld.%06ld secondes \n",(long int)((fin.ru_utime.tv_sec - debut.ru_utime.tv_sec)),(long int)((fin.ru_utime.tv_usec - debut.ru_utime.tv_usec)) );
        
        printf("Le temps système d'execution des instructions est de %ld.%06ld secondes \n",(long int)((fin.ru_stime.tv_sec - debut.ru_stime.tv_sec)),(long int)((fin.ru_stime.tv_usec - debut.ru_stime.tv_usec)));
        
        
        printf("\n \n Le fichier de départ est %s \n",pathFichierIn);
        
        printf("\n");
        
        
        
        
        printf("\n");
        
        printf("\n \n Le fichier de sortie est %s \n",pathFichierOut);
        
        printf("\n");
        
        
        //
        
        
        printf("\n");
    

    }

   
    /* EXO 3 */
    
    char* fichiersExo3[20]={"exercice3/00014_burma.cha","exercice3/00048_att.cha","exercice3/00076_eil.cha","exercice3/00144_pr.cha","exercice3/00280_a.cha","exercice3/00493_d.cha","exercice3/00666_fr.cha","exercice3/01400_fl.cha","exercice3/03795_fl.cha","exercice3/05934_rl.cha","exercice3/00022_ulysses.cha","exercice3/00052_berlin.cha","exercice3/00101_eil.cha","exercice3/00150_ch.cha","exercice3/00417_fl.cha","exercice3/00575_rat.cha","exercice3/00783_rat.cha","exercice3/02392_pr.cha","exercice3/04461_fnl.cha","exercice3/07397_pla.cha"};
    
    
    printf("-------------------------------------------------\n  Exercice 3 \n-------------------------------------------------\n\n");
    
    
    for(i=0;i<20;i++){
        printf("*********************************************************\n");

        char *pathFichierIn=fichiers_chaines[i];  
        
        char *pathFichierOut=fichiersExo3[i];
        
        
        getrusage(RUSAGE_SELF,&debut);
        
        mainExo3(pathFichierIn,pathFichierOut);
        
        getrusage(RUSAGE_SELF,&fin);
        
        printf("Le temps utilisateur d'execution des instructions est de %ld.%06ld secondes \n",(long int)((fin.ru_utime.tv_sec - debut.ru_utime.tv_sec)),(long int)((fin.ru_utime.tv_usec - debut.ru_utime.tv_usec)) );
        
        printf("Le temps système d'execution des instructions est de %ld.%06ld secondes \n",(long int)((fin.ru_stime.tv_sec - debut.ru_stime.tv_sec)),(long int)((fin.ru_stime.tv_usec - debut.ru_stime.tv_usec)));
        
        
        printf("\n \n Le fichier de départ est %s \n",pathFichierIn);
        
        printf("\n");
        
        
        
        
        printf("\n");
        
         printf("\n \n Le fichier de sortie est %s \n",pathFichierOut);
        
        printf("\n");
        
        
        //
        
        
        printf("\n");
    
    }
    

    /* EXO 4 */
    
    char* fichiersExo4[20]={"exercice4/00014_burma.cha","exercice4/00048_att.cha","exercice4/00076_eil.cha","exercice4/00144_pr.cha","exercice4/00280_a.cha","exercice4/00493_d.cha","exercice4/00666_fr.cha","exercice4/01400_fl.cha","exercice4/03795_fl.cha","exercice4/05934_rl.cha","exercice4/00022_ulysses.cha","exercice4/00052_berlin.cha","exercice4/00101_eil.cha","exercice4/00150_ch.cha","exercice4/00417_fl.cha","exercice4/00575_rat.cha","exercice4/00783_rat.cha","exercice4/02392_pr.cha","exercice4/04461_fnl.cha","exercice4/07397_pla.cha"};   
    
    printf("-------------------------------------------------\n  Exercice 4 \n-------------------------------------------------\n\n");
    
    
    for(i=0;i<20;i++){
        printf("*********************************************************\n");

        char *pathFichierIn=fichiers_chaines[i];  
        
        char *pathFichierOut=fichiersExo4[i];
        
        
        getrusage(RUSAGE_SELF,&debut);
        
        mainExo4(pathFichierIn,pathFichierOut);
        
        getrusage(RUSAGE_SELF,&fin);
        
        printf("Le temps utilisateur d'execution des instructions est de %ld.%06ld secondes \n",(long int)((fin.ru_utime.tv_sec - debut.ru_utime.tv_sec)),(long int)((fin.ru_utime.tv_usec - debut.ru_utime.tv_usec)) );
        
        printf("Le temps système d'execution des instructions est de %ld.%06ld secondes \n",(long int)((fin.ru_stime.tv_sec - debut.ru_stime.tv_sec)),(long int)((fin.ru_stime.tv_usec - debut.ru_stime.tv_usec)));
        
        
        printf("\n \n Le fichier de départ est %s \n",pathFichierIn);
        
        printf("\n");
        
        
        
        
        printf("\n");
        
        printf("\n \n Le fichier de sortie est %s \n",pathFichierOut);
        
        printf("\n");
        
        
        //
        
        
        printf("\n");
       

    }

    /* EXO 5 */
    
     char* fichiersExo5[20]={"exercice5/00014_burma.cha","exercice5/00048_att.cha","exercice5/00076_eil.cha","exercice5/00144_pr.cha","exercice5/00280_a.cha","exercice5/00493_d.cha","exercice5/00666_fr.cha","exercice5/01400_fl.cha","exercice5/03795_fl.cha","exercice5/05934_rl.cha","exercice5/00022_ulysses.cha","exercice5/00052_berlin.cha","exercice5/00101_eil.cha","exercice5/00150_ch.cha","exercice5/00417_fl.cha","exercice5/00575_rat.cha","exercice5/00783_rat.cha","exercice5/02392_pr.cha","exercice5/04461_fnl.cha","exercice5/07397_pla.cha"};   
    
    printf("-------------------------------------------------\n  Exercice 5 \n-------------------------------------------------\n\n");
    
    
    for(i=0;i<20;i++){
        printf("*********************************************************\n");

        char *pathFichierIn=fichiers_chaines[i];  
        
        char *pathFichierOut=fichiersExo5[i];
        
        getrusage(RUSAGE_SELF,&debut);
        
        mainExo5(pathFichierIn,pathFichierOut);
        
        getrusage(RUSAGE_SELF,&fin);
        
        printf("Le temps utilisateur d'execution des instructions est de %ld.%06ld secondes \n",(long int)((fin.ru_utime.tv_sec - debut.ru_utime.tv_sec)),(long int)((fin.ru_utime.tv_usec - debut.ru_utime.tv_usec)) );
        
        printf("Le temps système d'execution des instructions est de %ld.%06ld secondes \n",(long int)((fin.ru_stime.tv_sec - debut.ru_stime.tv_sec)),(long int)((fin.ru_stime.tv_usec - debut.ru_stime.tv_usec)));
        
        
        printf("\n \n Le fichier de départ est %s \n",pathFichierIn);
        
        printf("\n");
        
        
        printf("\n");
        
        printf("\n \n Le fichier de sortie est %s \n",pathFichierOut);        
        printf("\n");
        
        
        printf("\n");
       

    }

    
    return EXIT_SUCCESS;

}
