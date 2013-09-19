/*
 * Cr�� le Wed Jan  9 16:15:31 2002 par Thierry EXCOFFIER
 */

#ifndef _HOME_EXCO_REDACTEX_COURS_TRANS_COMP_IMAGE_TP_DCT2_INTSTREAM_H
#define _HOME_EXCO_REDACTEX_COURS_TRANS_COMP_IMAGE_TP_DCT2_INTSTREAM_H

struct bitstream ;
struct shannon_fano ;
struct intstream ;

/*
 * Structure de donn�e permettant d'utiliser de mani�re
 * transparente deux m�thodes d'�galisation de probabilit�.
 *
 * ATTENTION : deux "intstream" peuvent partager le m�me "bitstream".
 */

enum intstream_type
{  Entier
  ,Entier_Signe
  ,Shannon_fano
} ;

/*
 * Si "shannon_fano" est null, on utilise le Huffman static
 */
struct intstream* open_intstream(struct bitstream *bitstream
				 , enum intstream_type type
				 , struct shannon_fano *shannon_fano) ;
/*
 * La fermeture ne FERME PAS le "bitstream" et le "shannon_fano"
 * car ils n'ont pas �t� cr�� par "open_intstream"
 */
void        close_intstream(struct intstream *is) ;
void   put_entier_intstream(struct intstream *is, int evenement) ;
int    get_entier_intstream(struct intstream *is) ;

#endif
