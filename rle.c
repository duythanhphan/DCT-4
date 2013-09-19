#include "bases.h"
#include "intstream.h"
#include "rle.h"

/*
 * Avant propos sur les "intstream"
 *
 * Un "intstream" permet de stocker des entiers dans un fichier.
 * A son ouverture (faite par les programmes de test) une m�thode
 * de codage de l'entier lui est associ�e.
 * Dans notre cas, cela sera les algorithmes d�velopp�s
 * dans "entier.c" ou "sf.c"
 *
 * Il faut remarquer que deux "intstream" peuvent permettre
 * d'�crire dans le m�me "bitstream". Les donn�es sont intercal�es
 * dans le fichier, pour les r�cup�rer il faut les relire en faisant
 * les lectures dans le m�me ordre que les �critures.
 */

/*
 * RLE : Run Length Encoding
 *
 * Version sp�cifique pour stocker les valeurs de la DCT.
 *
 * Au lieu de coder un entier par valeur
 * on va coder le nombre d'entiers qui sont nuls (entier positif)
 * suivi de la valeur du premier entier non nul.
 *
 * Par exemple pour coder le tableau :
 * 	5 8 0 0 4 0 0 0 0 2 1 0 0 0
 *    On stocke dans les deux "intstream"
 *      0 0     2         4 0       3      Nombres de 0
 *      5 8     4         2 1              La valeur diff�rentes de 0
 * Comme les deux "intstream" sont stock�s dans le m�me fichier
 * il faut absolument lire et �crire les valeurs dans le m�me ordre.
 *     (0,5) (0,8) (2,4) (4,2) (0,1) (3)
 */

/*
 * Stocker le tableau de flottant dans les deux "instream"
 * En perdant le moins d'information possible.
 */

void compresse(struct intstream *entier, struct intstream *entier_signe
	       , int nbe, const float *dct)
{





























}

/*
 * Lit le tableau de flottant qui est dans les deux "instream"
 */

void decompresse(struct intstream *entier, struct intstream *entier_signe
		 , int nbe, float *dct)
{

















}
