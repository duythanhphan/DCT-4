#include "image.h"


/*
 * Lecture d'une ligne du fichier.
 * On saute les lignes commen�ant par un "#" (commentaire)
 * On simplifie en consid�rant que les lignes ne d�passent pas MAXLIGNE
 */

void lire_ligne(FILE *f, char *ligne)
{






}

/*
 * Allocation d'une image
 */

struct image* allocation_image(int hauteur, int largeur)
{










return 0 ; /* pour enlever un warning du compilateur */
}

/*
 * Lib�ration image
 */

void liberation_image(struct image* image)
{






}

/*
 * Allocation et lecture d'un image au format PGM.
 * (L'ent�te commence par "P5\nLargeur Hauteur\n255\n"
 * Avec des lignes de commentaire possibles avant la derni�re.
 */

struct image* lecture_image(FILE *f)
{






































return 0 ; /* pour enlever un warning du compilateur */
}

/*
 * �criture de l'image (toujours au format PGM)
 */

void ecriture_image(FILE *f, const struct image *image)
{










}
