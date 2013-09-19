#include "bases.h"
#include "psycho.h"

/*
 * Soit F1!=0 et F2!=0 deux ``fr�quences'' quelconques du son avec F1!=F2
 *      A1 et A2 leurs amplitudes respectives.
 * La fr�quence du son est l'indice dans le tableau "dct".
 *
 * 
 * Si   C * abs(A1)   <   abs( A2 / (F2 - F1) )
 *   Alors Annuler A1
 *
 * Ne pas annuler la fr�quence nulle.
 *
 *
 * Essayez aussi avec d'autre formules et comparer
 * les taux de compressions et la qualit� auditive du r�sultat.
 *
 * La formule qui est donn�e ici ne repr�sente pas la r�alit�.
 * En fait ce sont des fonctions tabul�es qui sont utilis�es.
 * Ces fonctions tabul�es sont d�termin�es exp�rimentalement.
 */

/*
 * Le tableau "dct" est directement modifi�.
 * Il contient d�j� les coefficients de la dct
 */

void psycho(int nbe, float *dct, float c)
{















}

