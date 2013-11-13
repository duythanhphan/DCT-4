/*
 * Le but du shannon-fano dynamique est de ne pas transmettre la table
 * des occurrences. Pour ce faire, on ajoute � la table un symbole ESCAPE
 * qui permet l'ajout d'�l�ments � la table.
 * Le d�compresseur sait qu'apr�s un �v�nement ESCAPE il trouvera
 * la valeur (et non le code) d'un �v�nement � ajouter � la table.
 */


#include "bits.h"
#include "sf.h"

#define VALEUR_ESCAPE 0x7fffffff /* Plus grand entier positif */

struct evenement
 {
  int valeur ;
  int nb_occurrences ;
 } ;

struct shannon_fano
 {
  int nb_evenements ;
  struct evenement evenements[200000] ;
 } ;

/*
 * Allocation des la structure et remplissage des champs pour initialiser
 * le tableau des �v�nements avec l'�v�nement ESCAPE (avec une occurrence).
 */
struct shannon_fano* open_shannon_fano()
{
	struct shannon_fano* sf;
	ALLOUER(sf,1);
	sf->nb_evenements = 1; 
	sf->evenements[0].valeur = VALEUR_ESCAPE;
	sf->evenements[0].nb_occurrences = 1; 
	return sf;
}

/*
 * Fermeture (lib�ration m�moire)
 */
void close_shannon_fano(struct shannon_fano *sf)
{
	free(sf);
}

/*
 * En entr�e l'�v�nement (sa valeur, pas son code shannon-fano).
 * En sortie la position de l'�v�nement dans le tableau "evenements"
 * Si l'�v�nement n'est pas trouv�, on retourne la position
 * de l'�v�nement ESCAPE.
 */

static int trouve_position(const struct shannon_fano *sf, int evenement)
{
	unsigned int i; 
	unsigned int escape;
	for(i=0; i<sf->nb_evenements; ++i)
	{
		if(sf->evenements[i].valeur == evenement)
			return i;
		if(sf->evenements[i].valeur == VALEUR_ESCAPE)
			escape = i; 
	}
	return escape;
	

//return 0 ; /* pour enlever un warning du compilateur */
}

/*
 * Soit le sous-tableau "evenements[position_min..position_max]"
 * Les bornes sont incluses.
 *
 * LES FORTES OCCURRENCES SONT LES PETITS INDICES DU TABLEAU
 *
 * Il faut trouver la s�paration.
 * La s�paration sera cod�e comme l'indice le plus fort
 * des fortes occurrences.
 *
 * La s�paration minimise la valeur absolue de la diff�rence
 * de la somme des occurrences sup�rieures et inf�rieures.
 *
 * L'algorithme (trivial) n'est pas facile � trouver, r�fl�chissez bien.
 */
static int trouve_separation(const struct shannon_fano *sf
			     , int position_min
			     , int position_max)
{
	/*unsigned int sum_inf = 0;
	unsigned int sum_sup = 0;
	//unsigned int pos_min = position_min; 
	//unsigned int pos_max = position_max;
	unsigned int i; 
	for(i=position_min; i<=position_max; ++i)
	{
		sum_sup += sf->evenements[i].nb_occurrences;
	}
	
	for(i=position_min; i<=position_max; ++i)
	{
		sum_sup -= sf->evenements[i].nb_occurrences;
		sum_inf += sf->evenements[i].nb_occurrences;
		if(sum_inf > sum_pos)
			return i-1;
	}*/

	unsigned int sum_inf = 0;
	unsigned int sum_sup = 0;	

	while(position_min <= position_max)
	{
		if(sum_inf < sum_sup)
		{
			sum_inf += sf->evenements[position_min].nb_occurrences;
			++position_min; 
		}
		else
		{
			sum_sup += sf->evenements[position_max].nb_occurrences;
			--position_max; 
		}
	}
	return position_max;

}

/*
 * Cette fonction (simplement it�rative)
 * utilise "trouve_separation" pour g�n�rer les bons bit dans "bs"
 * le code de l'�v�nement "sf->evenements[position]".
 */

static void encode_position(struct bitstream *bs,struct shannon_fano *sf,
		     int position)
{
	int position_min = 0;
	int position_max = sf->nb_evenements;
	int sep = -1; 
	while(sep != trouve_separation(sf, position_min, position_max))
	{
		if (sep > position)
		{
			position_max = sep;
			put_bit(bs, 0);
		}
		else
		{
			position_min = sep;
			put_bit(bs, 1);
		}
	}
}

/*
 * Cette fonction incr�mente le nombre d'occurrence de
 * "sf->evenements[position]"
 * Puis elle modifie le tableau pour qu'il reste tri� par nombre
 * d'occurrence (un simple �change d'�v�nement suffit)
 *
 * Les faibles indices correspondent aux grand nombres d'occurrences
 */

static void incremente_et_ordonne(struct shannon_fano *sf, int position)
{

















}

/*
 * Cette fonction trouve la position de l'�v�nement puis l'encode.
 * Si la position envoy�e est celle de ESCAPE, elle fait un "put_bits"
 * de "evenement" pour envoyer le code du nouvel l'�v�nement.
 * Elle termine en appelant "incremente_et_ordonne" pour l'�v�nement envoy�.
 */
void put_entier_shannon_fano(struct bitstream *bs
			     ,struct shannon_fano *sf, int evenement)
{
	












}

/*
 * Fonction inverse de "encode_position"
 */
static int decode_position(struct bitstream *bs,struct shannon_fano *sf)
{


















return 0 ; /* pour enlever un warning du compilateur */
}

/*
 * Fonction inverse de "put_entier_shannon_fano"
 *
 * Attention au pi�ge : "incremente_et_ordonne" change le tableau
 * donc l'�v�nement trouv� peut changer de position.
 */
int get_entier_shannon_fano(struct bitstream *bs, struct shannon_fano *sf)
{

















return 0 ; /* pour enlever un warning du compilateur */
}

/*
 * Fonctions pour les tests, NE PAS MODIFIER, NE PAS UTILISER.
 */
int sf_get_nb_evenements(struct shannon_fano *sf)
 {
   return sf->nb_evenements ;
 }
void sf_get_evenement(struct shannon_fano *sf, int i, int *valeur, int *nb_occ)
 {
   *valeur = sf->evenements[i].valeur ;
   *nb_occ = sf->evenements[i].nb_occurrences ;
 }
int sf_table_ok(const struct shannon_fano *sf)
 {
  int i, escape ;

  escape = 0 ;
  for(i=0;i<sf->nb_evenements;i++)
    {
    if ( i != 0
        && sf->evenements[i-1].nb_occurrences<sf->evenements[i].nb_occurrences)
	{
	   fprintf(stderr, "La table des �v�nements n'est pas tri�e\n") ;
	   return(0) ;
	}
    if ( sf->evenements[i].valeur == VALEUR_ESCAPE )
	escape = 1 ;
    }
 if ( escape == 0 )
	{
	   fprintf(stderr, "Pas de ESCAPE dans la table !\n") ;
	   return(0) ;
	}
 return 1 ;
 }
