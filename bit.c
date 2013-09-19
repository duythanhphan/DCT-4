#include "bit.h"

/*
 * Retourne le nombre de bits utilis� pour coder l'entier
 * Voici quelques chiffres :
 * v=0 --> 0 bit  car sa repr�sentation binaire est : ""
 * v=1 --> 1 bit  car sa repr�sentation binaire est : "1"
 * v=2 --> 2 bits car sa repr�sentation binaire est : "10"
 * v=3 --> 2 bits car sa repr�sentation binaire est : "11"
 * v=4 --> 3 bits car sa repr�sentation binaire est : "100"
 *
 * (Vous perdez des points de TP si vous utilisez une fonction travaillant
 * avec des nombres flottants)
 */

unsigned int nb_bits_utile(unsigned long v)
{
		unsigned int nb_bits;
		if(v)
		{
			nb_bits = nb_bits_utile(v/2);
			return nb_bits+1; 
		}
		else
			return 0; 

//return 0 ; /* pour enlever un warning du compilateur */
}

/*
 * Cette fonction retourne un entier ne contenant qu'un seul bit � 1.
 * La position de ce bit a 1 est indiqu� par le param�tre.
 *
 *  Position   Valeur binaire   Valeur decimale
 *     0       0...00000001           1
 *     1       0...00000010           2
 *     .       ............          ..
 *     7       0...10000000         128
 *     .       ............        ....
 *     .       ............        ....
 *
 * La choix de num�rotation de droite � gauche �t� faite car
 * la num�rotation des bits ne change pas en fonction de la taille de l'entier.
 *
 * En fait, cette fonction est �quivalente � "pow(2,position)"
 * (Vous perdez des points de TP si vous utilisez une fonction travaillant
 * avec des nombres flottants)
 */

unsigned long pow2(Position_Bit position)
{
	//unsigned int value;
	if(position)
		return pow2(position-1)*2; 
	else
		return 1;
	



//return 0 ; /* pour enlever un warning du compilateur */
}

/*
 * Cette fonction retourne le bit "n" d'un entier.
 * La valeur retourn�e sera un bool�en : Vrai ou Faux
 *
 * prend_bit(2,0) ==> 0
 * prend_bit(2,1) ==> 1
 * prend_bit(2,2) ==> 0
 */

Booleen prend_bit(unsigned long c,	     /* L'entier o� on prend le bit */
		  Position_Bit position	     /* La position du bit pris */
		  )
{
	return (c & (1 << position)) ? Vrai : Faux;
//return 0 ; /* pour enlever un warning du compilateur */
}

/*
 * Idem pour le stockage, on stocke la valeur "bit" � la position indiqu�e.
 * Si "bit" est � Faux            on met le bit � 0
 * Si "bit" est diff�rent de Faux on met le bit � 1
 */

unsigned long pose_bit(unsigned long c,	      /* Entier � modifier */
		       Position_Bit position, /* Position du bit � modifi� */
		       Booleen      bit	      /* Nouvelle valeur du bit */
		       )
{
	if(bit == Faux)
		return c & ~(1 << position);
	else
		return c | (1 << position);


//return 0 ; /* pour enlever un warning du compilateur */
}
