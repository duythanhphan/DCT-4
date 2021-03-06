#include "bases.h"
#include "bitstream.h"
#include "sf.h"
#include "intstream.h"
#include "image.h"
#include "rle.h"
#include "exception.h"
#include "ondelette.h"

/*
 * Les premi�res fonction vous sont fournies et vous permettent
 * d'�crire facilement la suite.
 */




/*
 * Allocation d'une matrice de float.
 * (tableau de pointeur sur tableau de flottants)
 */

float** allocation_matrice_float(int hauteur, int largeur)
 {
  int i ;
  float **table ;
  
  ALLOUER(table, hauteur) ;
  for(i=0; i<hauteur; i++)
    ALLOUER(table[i], largeur) ;
  return(table) ;
 }

/*
 * Lib�ration
 */

void liberation_matrice_float(float **table, int hauteur)
 {
  int i ;

  for(i=0; i<hauteur; i++)
    free(table[i]) ;

  free(table) ;
 }

/*
 * Elle fonctionne m�me pour des images rectangulaires.
 * Elle n'alloue pas la m�moire
 * La taille indiqu�e est celle de la matrice de d�part.
 */

void transposition_matrice(float **entree, float **sortie,
			   int hauteur, int largeur)
 {
  int j, i ;

  for(j=0; j<hauteur; j++)
    for(i=0; i<largeur; i++)
      sortie[i][j] = entree[j][i] ;
 }

/*
 * Cela vous permettra d'�crire plus facilement
 * la matrice de flottant dans un fichier image
 */
struct image* creation_image_a_partir_de_matrice_float(float **im
						       , int hauteur
						       , int largeur)
 {
  int j, i ;
  struct image *image ;
  
  image = allocation_image(hauteur, largeur) ;

  for(j=0; j<image->hauteur; j++)
    for(i=0; i<image->largeur; i++)
      {
	if ( im[j][i] > 255 )
	  image->pixels[j][i] = 255 ;
	else if ( im[j][i] < 0 )
	  image->pixels[j][i] = 0 ;
	else
	  image->pixels[j][i] = im[j][i] ;
      }

  return(image) ;
 }
/*
 * Affichage directe de la matrice de flottant sur l'�cran
 * Attention, si vous affichez l'image apr�s transformation ondelette
 * le r�sultat semblera tr�s bruit� car les valeurs n�gatives
 * vont �tre transform�es en blancs.
 */
void affiche_matrice_float(float **im, int hauteur, int largeur)
 {
  FILE *f ;
  struct image *image ;
  
  image = creation_image_a_partir_de_matrice_float(im, hauteur, largeur) ;
  f = popen("xv -", "w") ;
  ecriture_image(f, image) ;
  pclose(f) ;
  liberation_image(image) ;
 }





/*
 * Cette fonction effectue UNE SEULE it�ration d'une ondelette 1D
 * Voici quelques exemples de calculs
 *
 * Entree            Sortie
 * A                   A
 * A B               (A+B)/2 (A-B)/2
 * A B C             (A+B)/2    C    (A-B)/2
 * A B C D           (A+B)/2 (C+D)/2 (A-B)/2 (C-D)/2
 * A B C D E         (A+B)/2 (C+D)/2   E     (A-B)/2 (C-D)/2
 * A B C D E F       (A+B)/2 (C+D)/2 (E+F)/2 (A-B)/2 (C-D)/2 (E-F)/2
 */

void ondelette_1d(const float *entree, float *sortie, int nbe)
{









}

/*
 * Comme pour la DCT, on applique dans un sens puis dans l'autre.
 *
 * La fonction re�oit "image" et la modifie directement.
 *
 * Vous pouvez allouer plusieurs images interm�diaires pour
 * simplifier la fonction.
 *
 * Par exemple pour une image  3x6
 *    3x6 ondelette horizontale
 *    On transpose, on a donc une image 6x3
 *    6x3 ondelette horizontale
 *    On transpose � nouveau, on a une image 3x6
 *    On ne travaille plus que sur les basses fr�quences (moyennes)
 *    On ne travaille donc que sur le haut gauche de l'image de taille 2x3
 *
 * On recommence :
 *    2x3 horizontal   
 *    transposee => 3x2
 *    3x2 horizontal
 *    transposee => 2x3
 *    basse fr�quences => 1x2
 *
 * On recommence :
 *    1x2 horizontal
 *    transposee => 2x1
 *    2x1 horizontal (ne fait rien)
 *    transposee => 1x2
 *    basse fr�quences => 1x1
 *
 * L'image finale ne contient qu'un seul pixel de basse fr�quence.
 * Les autres sont des blocs de plus ou moins haute fr�quence.
 * Sur une image 8x8 :
 *
 * M   	F1H  F2H  F2H  F3H  F3H  F3H  F3H
 * F1V 	F1HV F2H  F2H  F3H  F3H  F3H  F3H
 * F2V 	F2V  F2HV F2HV F3H  F3H  F3H  F3H
 * F2V 	F2V  F2HV F2HV F3H  F3H  F3H  F3H
 * F3V 	F3V  F3V  F3V  F3HV F3HV F3HV F3HV
 * F3V 	F3V  F3V  F3V  F3HV F3HV F3HV F3HV
 * F3V 	F3V  F3V  F3V  F3HV F3HV F3HV F3HV
 * F3V 	F3V  F3V  F3V  F3HV F3HV F3HV F3HV
 *
 * La fr�quence F2 est plus petite (moins haute) que la fr�quence F3
 * F1H  Indique que c'est une fr�quence horizontale
 * F1V  Indique que c'est une fr�quence verticale
 * F1HV Indique que c'est une fr�quence calcul�e dans les 2 directions
 * 
 */

void ondelette_2d(float **image, int hauteur, int largeur)
{































}

/*
 * Quantification de l'ondelette.
 * La facteur de qualit� initial s'applique � la fr�quence la plus haute.
 * Quand on divise la fr�quence par 2 on divise qualit� par 8
 * tout en restant sup�rieur � 1.
 * Une qualit� de 1 indique que l'on a pas de pertes.
 */

void quantif_ondelette(float **image, int hauteur, int largeur, float qualite)
{














}

/*
 * Sortie des coefficients dans le bonne ordre afin
 * d'�tre bien compress� par la RLE.
 * Cette fonction n'est pas optimale, elle devrait faire
 * un zigzag en plus dans chacun des blocs.
 */

void codage_ondelette(float **image, int hauteur, int largeur, FILE *f)
 {
  int j, i ;
  float *t, *pt ;
  struct intstream *entier, *entier_signe ;
  struct bitstream *bs ;
  struct shannon_fano *sf ;
  int hau, lar ;

  /*
   * Conversion de la matrice en une table lin�aire
   * Pour pouvoir utiliser la fonction "compresse"
   */
  ALLOUER(t, hauteur*largeur) ;
  pt = t ;
  hau = hauteur ;
  lar = largeur ;

  while( hau != 1 || lar != 1 )
    {
      for(j=0; j<hau; j++)
	for(i=0; i<lar; i++)
	  if ( j>=(hau+1)/2 || i>=(lar+1)/2 )
	    *pt++ = image[j][i] ;

      hau = (hau+1)/2 ;
      lar = (lar+1)/2 ;
    }
  *pt = image[0][0] ;
  /*
   * Compression RLE avec Shannon-Fano
   */
  bs = open_bitstream("-", "w") ;
  sf = open_shannon_fano() ;
  entier = open_intstream(bs, Shannon_fano, sf) ;
  entier_signe = open_intstream(bs, Shannon_fano, sf) ;

  compresse(entier, entier_signe, hauteur*largeur, t) ;

  close_intstream(entier) ;
  close_intstream(entier_signe) ;
  close_bitstream(bs) ;
  free(t) ;
 }
  


/*
*******************************************************************************
* Fonctions inverses
*******************************************************************************
*/

void ondelette_1d_inverse(const float *entree, float *sortie, int nbe)
{









}


void ondelette_2d_inverse(float **image, int hauteur, int largeur)
{



































}


void dequantif_ondelette(float **image, int hauteur, int largeur, float qualite)
{














}

void decodage_ondelette(float **image, int hauteur, int largeur, FILE *f)
 {
  int j, i ;
  float *t, *pt ;
  struct intstream *entier, *entier_signe ;
  struct bitstream *bs ;
  struct shannon_fano *sf ;

  /*
   * Decompression RLE avec Shannon-Fano
   */
  ALLOUER(t, hauteur*largeur) ;
  bs = open_bitstream("-", "r") ;
  sf = open_shannon_fano() ;
  entier = open_intstream(bs, Shannon_fano, sf) ;
  entier_signe = open_intstream(bs, Shannon_fano, sf) ;

  decompresse(entier, entier_signe, hauteur*largeur, t) ;

  close_intstream(entier) ;
  close_intstream(entier_signe) ;
  close_bitstream(bs) ;

  /*
   * Met dans la matrice
   */
  pt = t ;
  while( hauteur != 1 || largeur != 1 )
    {
      for(j=0; j<hauteur; j++)
	for(i=0; i<largeur; i++)
	  if ( j>=(hauteur+1)/2 || i>=(largeur+1)/2 )
	      image[j][i] = *pt++ ;

      hauteur = (hauteur+1)/2 ;
      largeur = (largeur+1)/2 ;
    }
  image[0][0] = *pt++ ;

  free(t) ;
 }
  
/*
 * Programme de test.
 * La ligne suivante compile, compresse et d�compresse l'image
 * et affiche la taille compress�e.

export QUALITE=1  # Qualit� de "quantification"
export SHANNON=1  # Si 1, utilise shannon-fano dynamique
ondelette <DONNEES/bat710.pgm 1 >xxx && ls -ls xxx && ondelette_inv <xxx | xv -

 */

void ondelette_encode_image(float qualite)
 {
  struct image *image ;
  float **im ;
  int i, j ;

  image = lecture_image(stdin) ;
  assert(fwrite(&image->hauteur, 1, sizeof(image->hauteur), stdout)
	 == sizeof(image->hauteur)) ;
  assert(fwrite(&image->largeur, 1, sizeof(image->largeur), stdout)
	 == sizeof(image->largeur));
  assert(fwrite(&qualite       , 1, sizeof(qualite)       , stdout)
	 == sizeof(qualite));

  im = allocation_matrice_float(image->hauteur, image->largeur) ;
  for(j=0; j<image->hauteur; j++)
    for(i=0; i<image->largeur; i++)
      im[j][i] = image->pixels[j][i] ;

  fprintf(stderr, "Compression ondelette, image %dx%d\n"
	  , image->largeur, image->hauteur) ;
  ondelette_2d     (im, image->hauteur, image->largeur         ) ;
  fprintf(stderr, "Quantification qualit� = %g\n", qualite) ;
  quantif_ondelette(im, image->hauteur, image->largeur, qualite) ;
  fprintf(stderr, "Codage\n") ;
  codage_ondelette (im, image->hauteur, image->largeur, stdout ) ;

  //  affiche_matrice_float(im, image->hauteur, image->largeur) ;
 }

void ondelette_decode_image()
 {
  int hauteur, largeur ;
  float qualite ;
  struct image *image ;
  float **im ;

  assert(fread(&hauteur, 1, sizeof(hauteur), stdin) == sizeof(hauteur)) ;
  assert(fread(&largeur, 1, sizeof(largeur), stdin) == sizeof(largeur)) ;
  assert(fread(&qualite, 1, sizeof(qualite), stdin) == sizeof(qualite)) ;

  im = allocation_matrice_float(hauteur, largeur) ;

  fprintf(stderr, "D�codage\n") ;
  decodage_ondelette   (im, hauteur, largeur, stdin ) ;

  fprintf(stderr, "D�quantification qualit� = %g\n", qualite) ;
  dequantif_ondelette  (im, hauteur, largeur, qualite) ;

  fprintf(stderr, "D�compression ondelette, image %dx%d\n"
	  , largeur, hauteur) ;
  ondelette_2d_inverse (im, hauteur, largeur         ) ;

  //  affiche_matrice_float(im, hauteur, largeur) ;
  image = creation_image_a_partir_de_matrice_float(im, hauteur, largeur) ;
  ecriture_image(stdout, image) ;
 }


