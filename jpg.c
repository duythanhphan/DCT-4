#include "matrice.h"
#include "dct.h"
#include "jpg.h"
#include "image.h"

/*
 * Calcul de la DCT ou de l'inverse DCT sur un petit carr� de l'image.
 * On fait la transformation de l'image ``sur place'' c.a.d.
 * que le param�tre "image" est utilis� pour l'entr�e et la sortie.
 *
 * DCT de l'image :  DCT * IMAGE * DCT transpos�e
 * Inverse        :  DCT transpos�e * I' * DCT
 */
void dct_image(int inverse, int nbe, float **image)
{





















}

/*
 * Quantification/D�quantification des coefficients de la DCT
 * Si inverse est vrai, on d�quantifie.
 * Attention, on reste en calculs flottant (en sortie aussi).
 */
void quantification(int nbe, int qualite, float **extrait, int inverse)
{








}
/*
 * ZIGZAG.
 * On fournit � cette fonction les coordonn�es d'un point
 * et elle nous donne le suivant (Toujours YX comme d'habitude)
 *
 * +---+---+---+---+     +---+---+---+
 * |00 |01 |   |   |     |   |   |   |
 * | ----/ | /---/ |     | ----/ | | |
 * |   |/  |/  |/  |     |   |/  |/| |
 * +---/---/---/---+     +---/---/-|-+
 * |10/|  /|  /|   |     |  /|  /| | |
 * | / | / | / | | |     | / | / | | |
 * | | |/  |/  |/| |     | | |/  |/  |
 * +-|-/---/---/-|-+     +-|-/---/---+
 * | |/|  /|  /| | |     | |/|  /|   |
 * | / | / | / | | |     | / | ----- |
 * |   |/  |/  |/  |     |   |   |   |
 * +---/---/---/---+     +---+---+---+
 * |  /|  /|  /|   |    
 * | /---/ | /---- |    
 * |   |   |   |   |    
 * +---+---+---+---+    
 */
void zigzag(int nbe, int *y, int *x)
{


















}
/*
 * Extraction d'une matrice de l'image (le r�sultat est d�j� allou�).
 * La sous-image carr�e � la position et de la taille indiqu�e
 * est stock�e dans matrice "extrait"
 */

static void extrait_matrice(int y, int x, int nbe
			    , const struct image *entree
			    , float **extrait
			    )
 {
  int i, j ;

  for(j=0;j<nbe;j++)
    for(i=0;i<nbe;i++)
      if ( j+y < entree->hauteur && i+x < entree->largeur )
	extrait[j][i] = entree->pixels[j+y][i+x] ;
      else
	extrait[j][i] = 0 ;
 }

/*
 * Insertion d'une matrice de l'image.
 * C'est l'op�ration inverse de la pr�c�dente.
 */

static void insert_matrice(int y, int x, int nbe
			   , float **extrait
			   , struct image *sortie
			   )
 {
  int i, j ;

  for(j=0;j<nbe;j++)
    for(i=0;i<nbe;i++)
      if ( j+y < sortie->hauteur && i+x < sortie->largeur )
	{
	  if ( extrait[j][i] < 0 )
	    sortie->pixels[j+y][i+x] = 0 ;
	  else
	    {
	      if ( extrait[j][i] > 255 )
		sortie->pixels[j+y][i+x] = 255 ;
	      else
		sortie->pixels[j+y][i+x] = rint(extrait[j][i]) ;
	    }
	}
 }


/*
 * Compression d'une l'image :
 * Pour chaque petit carr� on fait la dct et l'on stocke dans un fichier
 */
void compresse_image(int nbe, const struct image *entree, FILE *f)
 {
  static float **tmp = NULL ;
  int i, j, k ;

  if ( tmp == NULL )
    {
      tmp = allocation_matrice_carree_float(nbe) ;
    }

  for(j=0;j<entree->hauteur;j+=nbe)
    for(i=0;i<entree->largeur;i+=nbe)
      {
	extrait_matrice(j, i, nbe, entree, tmp) ;
	dct_image(0, nbe, tmp) ;
	for(k=0; k<nbe; k++)
	  assert(fwrite(tmp[k], sizeof(**tmp), nbe, f) == nbe) ;
      }
 }

/*
 * D�compression image
 * On r�cup�re la DCT de chaque fichier, on fait l'inverse et
 * on ins�re dans l'image qui est d�j� allou�e
 */
void decompresse_image(int nbe, struct image *entree, FILE *f)
 {
  static float **tmp = NULL ;
  int i, j, k ;

  if ( tmp == NULL )
    {
      tmp = allocation_matrice_carree_float(nbe) ;
    }

  for(j=0;j<entree->hauteur;j+=nbe)
    for(i=0;i<entree->largeur;i+=nbe)
      {
	for(k=0; k<nbe; k++)
	  assert(fread(tmp[k], sizeof(**tmp), nbe, f) == nbe) ;
	dct_image(1, nbe, tmp) ;
	insert_matrice(j, i, nbe, tmp, entree) ;
      }
 }
