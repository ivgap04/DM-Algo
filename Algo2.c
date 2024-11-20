
/************* La correction du TD 2 devrait �tre mise sur ecampus ce samedi    ******/

#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/*                                               */
/*                type bool�en                   */
/*                                               */
/*************************************************/

typedef enum {false, true} bool;

/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct Bloc
{
    int valeur ;
    struct Bloc * suite;
} Bloc;

typedef Bloc *Liste ;

/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/


/*** les 5 fonctionnalit�s suivantes sont plus du sucre syntaxique que du code utile  ***/
/*** sauf � vouloir pouvoir basculer � moindre frais sur une impl�menation des listes ***/
/**** diff�rentes des listes chain�es propos�es dans le cadre de ce projet            ***/

// Liste Vide() { return NULL ; }
// void initVide(Liste *L) { *L = NULL ; }
// bool estVide(Liste l) { return l == NULL ; }
// int premier(Liste l) { return l->valeur ; }
// Liste suite(Liste l) { return l->suite ; }

/****************/

void depile(Liste *L)
{   Liste tmp = *L ;
    *L = (*L)->suite ;
    free(tmp) ;
}

Liste ajoute(int x, Liste l)
{   Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->valeur = x ;
    tmp->suite = l ;
    return tmp ;
}

void empile(int x, Liste *L) 
{ *L = ajoute(x,*L) ; }

/*****************************/
/*                           */
/*       Affiche             */
/*                           */
/*****************************/

void affiche_rec(Liste l)
{
    if (l == NULL)
        printf("\n");
    else
    {
        printf("%d ", l->valeur);
        affiche_rec(l->suite);
    }
}


void affiche_iter(Liste l)
{
    Liste L2 = l;
    while( L2 != NULL )
    {
        printf("%d ", L2->valeur);
        L2 = L2->suite;
    }
    printf("\n");
}

/****************************/
/*                          */
/*       Longueur           */
/*                          */
/****************************/

int longueur_rec (Liste l)
{
    if (l == NULL)
         return 0 ;
    else return (1 + longueur_rec(l->suite)) ;
}


int longueur_iter (Liste l)
{
    Liste P = l;
    int cpt = 0 ;
    while (P != NULL)
    {   P = P->suite ;
        cpt++ ;
    }
    return cpt ;
}

/*****************************************/
/*                                       */
/*                 VireDernier           */
/*     avec un depile                    */
/* � la main opportuniste (version iter) */
/* ou en utilisant depiie (version rec ) */ 
/*                                       */
/*****************************************/

void VD (Liste *L)
          // *L non NULL ie liste non vide
{
     if ( (*L)->suite == NULL )
            depile(L) ;   // moralement : depile(& (*L)) ;
     else VD (& (*L)->suite) ;
}

void VireDernier_rec (Liste *L)
{
     if ( *L != NULL )
          VD(L);        // moralement : VD(& (*L)) ;
}

/*************/

void VireDernier_iter (Liste *L)
{
    if ( *L != NULL)
    {
        while ( (*L)->suite != NULL )
                 L = &  (*L)->suite  ;
        free(*L) ;
        *L = NULL ;
     }
}


/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L)
{
    if ( *L != NULL )
    {
        depile(L);
        VideListe(L);
    }
      
}

/********************************************/
/*                                          */
/*          DeuxEgalX                       */
/*                                          */
/********************************************/

bool DeuxEgalX (Liste L, int x){
    if (L == NULL || L->suite == NULL)
        return x == 0;
    return L->suite->valeur == x;
}
   

/********************************************/
/*                                          */
/*          ContientZero                    */
/*                                          */
/********************************************/

bool ContientZeroRec (Liste L){
    if (L == NULL)
        return false;
    return L->valeur == 0 || ContientZeroRec(L->suite);
}

/********************************************/

bool ContientZeroIter (Liste L){
    while (L != NULL){
        if (L->valeur == 0)
            return true;
        L = L->suite;
    }
    return false;
}

/********************************************/
/*                                          */
/*          SousEnsemble                    */
/*                                          */
/********************************************/

bool SousEnsemble(Liste l1, Liste l2){
    while (l1 != NULL) {
        if (l2 == NULL || l1->valeur < l2->valeur) {
            return false;
        } else if (l1->valeur == l2->valeur) {
            l1 = l1->suite;
        }
        l2 = l2->suite;
    }
    return true;
}

/********************************************/
/*                                          */
/*          SommeAvantKieme0                */
/*                                          */
/********************************************/

int SAvK0Rec(Liste L, int k){
    if(L == NULL || k == 0) 
        return 0;

    if(L->valeur == 0) 
        return SAvK0Rec(L->suite, k - 1);
    
    return L->valeur + SAvK0Rec(L->suite, k);
}

/********************************************/

int SAvK0Iter(Liste L, int k){
    int sum = 0;
    int cpt = 0;
    while(L != NULL){
        if(L->valeur == 0){
            cpt++;
            if(cpt == k) break;
        }else{
            sum += L->valeur;
        }
        L = L->suite;
    }
}

/********************************************/

int SAvK0_sf_aux(Liste L, int k, int sum){
    if(L == NULL || k == 0) 
        return sum;

    if(L->valeur == 0) 
        return SAvK0_sf_aux(L->suite, k-1,sum);

    return SAvK0_sf_aux(L->suite, k, sum + L->valeur);

}

int SAvK0_sf(Liste L, int k){
    return SAvK0_sf_aux(L, k, 0);
}

/********************************************/

void SAvK0_sp_aux(Liste L, int k, int *sum){
    if(L == NULL || k == 0)
        return;

    if(L->valeur == 0) {
        SAvK0_sp_aux(L->suite, k-1, sum);
    }else{
        *sum += L->valeur;
        SAvK0_sp_aux(L->suite, k, sum);
    }
}

int SAvK0_sp(Liste L, int k){
    int sum = 0;
    SAvK0_sp_aux(L, k, &sum);
    return sum;
}

/********************************************/
/*                                          */
/*          SommeApresRetroKieme0           */
/*                                          */
/********************************************/

void SApK0_aux(Liste L, int k, int *sum, int *cpt){
    if(L==NULL){
        *cpt = k;
        return;
    }

    SApK0_aux(L->suite, k, sum, cpt );
    *sum += L->valeur;

    if(L->valeur == 0){
        (*cpt)--;
    }

    if(*cpt <= 0){
        *sum -= L->valeur;
    }
}

int SApK0(Liste L, int k){
    int sum = 0;
    int cpt = 0;
    SApK0_aux(L, k, &sum, &cpt);
    return sum;
}

/********************************************/
/*                                          */
/*          TueDoublons                     */
/*                                          */
/********************************************/

void TueDoublons1 (Liste *L){
    if(*L == NULL || (*L)->suite == NULL){
        return;
    }

}


/********************************************/
void TueDoublons2_rec (Liste *L){
    return;
}

void TueDoublons2_iter(Liste *L){return;}
   
/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/


int main(int argc, char** argv)
{
    Liste l ;

        l = NULL ;
        VireDernier_rec  (&l) ;
        VireDernier_iter (&l) ;
        affiche_rec(l) ; 
        affiche_iter(l) ; 
        printf(" %d \n", longueur_iter(l)) ; 
        printf(" %d \n", longueur_rec(l)) ; 
        printf(" %d \n", DeuxEgalX(l,0)) ; 
        printf(" %d \n", DeuxEgalX(l,1)) ; 
        printf(" %d \n", ContientZeroRec(l)) ;
        printf(" %d \n", ContientZeroIter(l)) ; 
        VideListe(&l);

    Liste L = NULL;
        empile(0, &L);
        empile(2, &L);
        empile(8, &L);
        empile(0, &L);
        empile(0, &L);
        empile(9, &L);
        empile(4, &L);
        empile(0, &L);
        empile(1, &L);
        empile(0, &L);
        empile(3, &L);
        empile(2, &L);
        affiche_rec(L);
        printf(" %d \n", SApK0(L, 4));
        printf(" %d \n", SApK0(L, 10));
        VideListe(&L);
        return 0;
}





