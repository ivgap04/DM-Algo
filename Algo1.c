
#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/*                                               */
/*                type booléen                   */
/*                                               */
/*************************************************/

typedef enum {false, true} bool;

/*************************************************/
/*                                               */
/*            factorielle                        */
/*                                               */
/*************************************************/

long fact (int n) 
{ if (n==0) return 1 ;
  else return n * fact(n-1) ; 
}

/*************************************************/

// itou avec un argument out => passage par adresse

void bisfact(int n, long * r) 
{ if (n==0) 
         *r = 1.0 ;
  else { bisfact(n-1,r) ;
         *r = *r *n ;
       }
}

long fact2 (int n)
{ long r ;
  bisfact(n,&r) ;
  return r ;
}

/*************************************************/

// itou en stoquant tout dans un tableau... (très bof en complexité espace)

long fact3(int n) 
{ long * T = (long *) malloc((n+1)*sizeof(long)) ;
  T[0] = 1 ;
  for (int i=1 ; i <= n ; i++)
          T[i] = i* T[i-1] ;
  long r = T[n] ;
  free(T) ;
  return r ;
}


/*************************************************/
/*                                               */
/*            Calcul de e                        */
/*                                               */
/*************************************************/


  // d'après google,
  // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995 
  //       9574966967 6277240766 3035354759 4571382178 5251664274
  // il est bien sûr interdit d'injecter directement cette approximation

float Efloat() {
    float e = 1.0;
    float u = 1.0;
    int n = 1;
    float epsilon = 1e-7;

    while (u > epsilon) {

        u = u / n;
        e += u;
        n++;
    }

    return e;
}

/*************************************************/

double Edouble() {
    double e = 1.0;
    double u = 1.0;
    int n = 1;
    double epsilon = 1e-15;

    while (u > epsilon) {
        u = u / n;
        e += u;
        n++;
    }

    return e;
}
  
/*************************************************/
/*                                               */
/*            Suite Y                            */
/*                                               */
/*************************************************/

void afficheYfloat (int n) {
    float e = Efloat();
    float y = e - 1;
    for(int i = 1; i <= n; i++){
        y = i*y -1;
        printf("Y(%d) = %f\n", i, y);
    }
}

/*************************************************/

void afficheYdouble (int n)  {
    double e = Edouble();
    double y = e - 1;
    for(int i = 1; i <= n; i++){
        y = (i * y) - 1;
        printf("Y(%d) = %f\n", i, y);
    }
}

/*************************************************/
/*                                               */
/*             Suite X                           */
/*                                               */
/*************************************************/

double X1(int n ) {
    double x = 1.;
    for(int i = 1; i <= n; i++){
        x = x + 1./x;
    }
    return x;
}

/*************************************************/

long double X1bis(long n) {
    long double x = 1.0;
    for(long i = 1; i <= n; i++){
        x = x + 1./x;
    }
    return x;
}

/*************************************************/

double X2(int n){
    if (n == 0) return 1.0;
    double x = X2(n-1);
    return x + 1./x;
}

/*************************************************/

double X3bis(int n, double x){
    if (n == 0) return x;
    return X3bis(n - 1, x + 1./x);
}

double X3(int n){
    return X3bis(n, 1.0);
}

/*************************************************/

void X4bis(int n, double *x){
    if (n == 0) return;
    *x = *x + 1./ *x;
    X4bis(n - 1, x);
}

double X4(int n){
    double x = 1.0;
    X4bis(n, &x);
    return x;
}

/*************************************************/
/*                                               */
/*             Binomiaux                         */
/*                                               */
/*************************************************/

long BadCpn (int p, int n){ // 0 <= p <= n
    if ( p == 0 || p == n) return 1;
    
    return BadCpn(p, n-1) + BadCpn(p - 1, n - 1);  
}  


/*************************************************/

long GoodCpn (int p, int n){  // 0 <= p <= n
    long tab[p+1];
    for(int i = 0; i <= p; i++){
        tab[i] = 0;
    }
    tab[0] = 1;

    for(int i = 1; i <= n; i++){
        int j;
        if(i < p) {j = i;}
        else {j = p;}
        for(; j >0; j--){
            tab[j] += tab[j - 1];
        }
    }
    return tab[p];
}

/*************************************************/
/*                                               */
/*               main                            */
/*                                               */
/*************************************************/


int main(int argc, char** argv)
{

       float z1 ;
       double z2 ;
       long double z3 ;
       
       int cpt ;  
 
/************************************************************************/
 
      // mettre "if true" vs "if false" selon que vous voulez les tests ou pas
  
/************************  taille des nombres  *************************/
      
if (false) {     

       printf("tailles des entiers (peuvent varier selon le compilo) :\n") ;
       
       printf("short : %d octets\n", (int) sizeof(short));
       printf("int : %d octets\n", (int) sizeof(int));
       printf("long : %d octets\n", (int) sizeof(long));
       printf("long long : %d octets\n", (int) sizeof(long long));
       printf("float : %d octets\n", (int) sizeof(float));
       printf("double : %d octets\n", (int) sizeof(double));
       printf("long double : %d octets\n", (int) sizeof(long double));
       printf("\n") ;
  
       printf("limite des flottants (peuvent varier selon le compilo) :\n") ;
       
       z1 = 2.0 ; cpt = 0 ;
       while ( z1 > 1 ) { z1 = (z1-1)/10+1 ; cpt ++ ; }
       printf("1+1/10^c devient 1 a partir de c=%d pour les float\n", cpt) ; 
    
       z2 = 2.0 ; cpt = 0 ;
       while ( z2 > 1 ) { z2 = (z2-1)/10+1 ; cpt ++ ; }
       printf("1+1/10^c devient 1 a partir de c=%d pour les double\n", cpt) ; 
      
       z3 = 2.0 ; cpt = 0 ;
       while ( z3 > 1 ) { z3 = (z3-1)/10+1 ; cpt ++ ; }
       printf("1+1/10^c devient 1 a partir de c=%d pour les long double\n", cpt) ; 
       
       z1 = 1.0 ; cpt = 0 ;
       while ( z1 > 0 ) { z1 = z1/10 ; cpt ++ ; }
       printf("1/10^c devient 0 a partir de c=%d pour les float\n", cpt) ; 
       
       z2 = 1.0 ; cpt = 0 ;
       while ( z2 > 0 ) { z2 = z2/10 ; cpt ++ ; }
       printf("1/10^c devient 0 a partir de c=%d pour les double\n", cpt) ; 
       
       z3 = 1.0 ; cpt = 0 ;
       while ( z3 > 0 ) { z3 = z3/10 ; cpt ++ ; }
       printf("1/10^c devient 0 a partir de c=%d pour les long double\n", cpt) ; 
        
       printf("\nce programme suppose que les \"long\" font au moins 8 octets\n") ;
       printf("Si ce n'est pas le cas, utiliser des \"long long\" ? \n\n") ;

}

/************************  factorielle  *************************/

if (false) {

     printf("factorielles de 0, de 5, de 20, trois codes : \n") ;
     printf("%ld \n",fact(0)) ;
     printf("%ld \n",fact2(0)) ;
     printf("%ld \n",fact3(0)) ;
     printf("%ld \n",fact(5)) ;
     printf("%ld \n",fact2(5)) ;
     printf("%ld \n",fact3(5)) ;
     printf("%ld \n",fact(20)) ;
     printf("%ld \n",fact2(20)) ;
     printf("%ld \n",fact3(20)) ;
     printf("Note : fact(20) est le dernier qui passe correctement avec 8 octets \n") ;
     printf("\n") ;
 
}


/******************    Autour de e      *******************************/

  // d'après google,
  // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995 
  //       9574966967 6277240766 3035354759 4571382178 5251664274

if (false) {  
        printf("Valeurs de e en float et en double :\n") ;
        printf(" e1 = %.20f  \n", Efloat() ) ;
        printf(" e2 = %.30lf \n", Edouble() ) ;         
}

if (true) {  
            printf("Valeurs de Y, selon float, double :\n") ;
            afficheYfloat(30) ;
            afficheYdouble(30) ;
}

if (false){
    int n = 100;

    printf("X1(%d) = %.15f\n", n, X1(n));
    printf("X2(%d) = %.15f\n", n, X2(n));
    printf("X3(%d) = %.15f\n", n, X3(n));
    printf("X4(%d) = %.15f\n", n, X4(n));

    for (int k = 1; k <= 9; k++) {
        int nk = 1;
        for (int i = 0; i < k; i++) nk *= 10;

        printf("X1(10^%d) = %.15f\n", k, X1(nk));

        if (k <= 5) {
            printf("X2(10^%d) = %.15f\n", k, X2(nk));
            printf("X3(10^%d) = %.15f\n", k, X3(nk));
            printf("X4(10^%d) = %.15f\n", k, X4(nk));
        }
    }

    for (int k = 1; k <= 12; k ++){
        long nk = 1;
        for(int i = 0; i < k; i++) nk *= 10;
        printf("X1bis(10^%d) = %.15LF\n",k, X1bis(nk));
    }

    return 0;
}
if(false){
    printf("BadCpn test:\n");
    for(int n =0; n <= 30; n++){
        printf("C(%d, %d) = %ld\n", 2 * n, n, BadCpn(n, 2 * n));
    }
}

if(false){
    printf("GoodCpn test:\n");
    for(int n =0; n <= 30; n++){
        printf("C(%d, %d) = %ld\n", 2 * n, n, GoodCpn(n, 2 * n));
    }
}
    return 0;
}






