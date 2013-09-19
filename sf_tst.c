#include <math.h>
#include "sf.h"
#include "exception.h"
#include "bits.h"

void open_shannon_fano_tst()
{
  struct shannon_fano *sf ;
  int valeur, nb_occ ;

  sf = open_shannon_fano() ;

  if ( sf == NULL )
    {
      eprintf("Elle retourne NULL !\n") ;
      return ;
    }

  if ( sf_get_nb_evenements(sf) != 1 )
    {
      eprintf("A la cr�ation d'un shannon fano, il y a un evenement\n"); 
      return ;
    }

  if ( sf_get_nb_evenements(sf) != 1 )
    {
      eprintf("A la cr�ation d'un shannon fano, il y a un evenement\n"); 
      return ;
    }
  sf_get_evenement(sf, 0, &valeur, &nb_occ) ;
  if ( valeur != 0x7fffffff || nb_occ != 1 )
    {
      eprintf("L'�v�nement ESCAPE initial est mal initialis�\n"); 
      return ;
    }
}

void close_shannon_fano_tst()
{
  struct shannon_fano *sf, *sf2 ;

  sf = open_shannon_fano() ;
  close_shannon_fano(sf) ;
  sf2 = open_shannon_fano() ;
  if ( sf != sf2 )
    {
      eprintf("Cette fonction ne semble par �tre termin�e....\n") ;
      return ;
    }
}

void put_entier_shannon_fano_tst()
{
  struct shannon_fano *sf ;
  struct bitstream *bs ;
  int j, err ;
  int i, k, valeur, nb_occ, valeur2, nb_occ2 ;

  /*
   * Fichier contenant un seul �v�nement
   */

  sf = open_shannon_fano() ;
  bs = open_bitstream("xxx", "w") ;

  i = 123456789 ;
  put_entier_shannon_fano(bs, sf, i) ;

  if ( sf_get_nb_evenements(sf) != 2 )
    {
      eprintf("Apr�s l'ajout du premier �v�nement, il n'y pas 2 �venements\n");
      return ;
    }
  sf_get_evenement(sf, 0, &valeur, &nb_occ) ;
  sf_get_evenement(sf, 1, &valeur2, &nb_occ2) ;
  if ( valeur != i && valeur2 != i )
    {
      eprintf("La valeur envoy�e n'est pas stock�e dans la table\n");
      return ;      
    }
  if ( valeur != 0x7fffffff && valeur2 != 0x7fffffff )
    {
      eprintf("La valeur ESCAPE n'est plus dans la table\n");
      return ;      
    }

  close_bitstream(bs) ;
  close_shannon_fano(sf) ;

  bs = open_bitstream("xxx", "r") ;
  if ( bs == NULL )
    {
      perror("xxx") ;
      return ;
    }

  j = 0 ;
  EXCEPTION
    (
     j = get_bits(bs, sizeof(i)*8) ;
     ,
     ,
     case Exception_fichier_lecture:
      eprintf("Quand on �crit le premier �venement\n"
	      "le fichier doit au moins contenir la valeur de l'�venement\n"
	     ) ;
      return ;
     ) ;
  
  err = 1 ;
  EXCEPTION
    (
     get_bit(bs) ;
     ,
     ,
     case Exception_fichier_lecture:
     err = 0 ;
     break ;
     ) ;

  if ( err )
    {
      eprintf("Le fichier est trop grand (>4 octets)\n") ;
      return ;
    }
  if ( j != i )
    {
      eprintf("Vous avez mal stock� la valeur de l'�v�nement %d != %d\n"
	      , i, j) ;
      return ;
    }
  close_bitstream(bs) ;

  /*
   * Fichier contenant 8 fois le m�me �v�nement
   */

  sf = open_shannon_fano() ;
  bs = open_bitstream("xxx", "w") ;

  for(k=0; k<8; k++)
    put_entier_shannon_fano(bs, sf, i) ;


  if ( sf_get_nb_evenements(sf) != 2 )
    {
      eprintf("Il n'y pas 2 �venements\n");
      return ;
    }
  sf_get_evenement(sf, 0, &valeur, &nb_occ) ;
  sf_get_evenement(sf, 1, &valeur2, &nb_occ2) ;
  if ( valeur != i )
    {
      eprintf("L'�v�nement r�p�t� 8 fois n'est pas en premier dans le tableau\n");
      return ;      
    }
  if ( nb_occ != 8 )
    {
      eprintf("L'�v�nement r�p�t� 8 fois n'a pas 8 comme occurrence\n");
      return ;      
    }
  if ( valeur2 != 0x7fffffff )
    {
      eprintf("La valeur ESCAPE n'est plus dans la table\n");
      return ;      
    }
  if ( nb_occ2 != 2 )
    {
      eprintf("Le nombre d'occurrences de ESCAPE n'est pas 2 (c'est %d)\n"
	      , nb_occ2);
      return ;      
    }


  close_bitstream(bs) ;
  close_shannon_fano(sf) ;

  bs = open_bitstream("xxx", "r") ;
  if ( bs == NULL )
    {
      perror("xxx") ;
      return ;
    }

  EXCEPTION
    (
     j = get_bits(bs, sizeof(i)*8) ;
     get_bits(bs, 8) ;
     ,
     ,
     case Exception_fichier_lecture:
      eprintf("Le fichier doit contenir au moins 5 octets\n") ;
      return ;
     ) ;
  
  err = 1 ;
  EXCEPTION
    (
     get_bit(bs) ;
     ,
     ,
     case Exception_fichier_lecture:
     err = 0 ;
     break ;
     ) ;

  if ( err )
    {
      eprintf("Le fichier est trop grand (>5 octets)\n") ;
      return ;
    }
  if ( j != i )
    {
      eprintf("Vous avez mal stock� la valeur de l'�v�nement %d != %d\n"
	      , i, j) ;
      return ;
    }
  close_bitstream(bs) ;


  fprintf(stderr, "Le test (tr�s succint) est ") ;
}


static int simple(int n)
{
  return(n) ;
}

static int aleatoire(int n)
{  
  srand(n) ;
  return( rand() % 50 ) ;
}

static int aleatoire2(int n)
{  
  srand(n) ;
  return( pow( rand() % 50, .1 ) ) ;
}


void get_entier_shannon_fano_tst()
{
  struct shannon_fano *sf ;
  struct bitstream *bs ;
  int i, j, k ;
  int (*t[])(int) = { simple, aleatoire, aleatoire2 } ;
  char *tt[] =  { "les nombres successif entre -1000 et 1000",
		  "2000 nombres al�atoires entre 0 et 49 inclus"
		  "2000 nombres al�atoires entre 0 et 49 inclus en gaussienne"
  } ;
  for(k=0; k < TAILLE(t); k++)
    {
      sf = open_shannon_fano() ;
      bs = open_bitstream("xxx", "w") ;
      
      for(i = -1000; i < 1000; i++)
	{
	put_entier_shannon_fano(bs, sf, (*t[k])(i)) ;
	sf_table_ok(sf) ;
	}

      close_bitstream(bs) ;
      close_shannon_fano(sf) ;
      
      sf = open_shannon_fano() ;
      bs = open_bitstream("xxx", "r") ;
      
      for(i = -1000; i < 1000; i++)
	{
	  j = get_entier_shannon_fano(bs, sf) ;
	  sf_table_ok(sf) ;
	  if ( j != (*t[k])(i) )
	    {
	      eprintf("Compresse/D�compresse %s\n", tt[k]) ;
	      eprintf("J'attend %d et je re�ois %d\n", (*t[k])(i), j) ;
	      return ;
	    }
	}

      close_bitstream(bs) ;
      close_shannon_fano(sf) ;
    }
}
