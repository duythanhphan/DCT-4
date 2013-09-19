/*
 * Cr�� le Wed Sep 12 15:59:46 2001 par Thierry EXCOFFIER
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>

extern volatile struct exception_c
{
  int profondeur ;
  int profondeur_max ;
  jmp_buf *buf ;
  int valeur_de_retour ;
} global_exception ;

/*
 * Le programme principal doit d�clarer le syst�me d'exception
 */

#define EXCEPTION_DECLARATION volatile struct exception_c global_exception = { 0 }

/*
 * Lancer une exception pour indiquer un probl�me
 * CETTE FONCTION NE RETOURNE PAS : l'ex�cution continue ailleur.
 *
 * VAL est le num�ro de l'exception.
 * La liste des exceptions est � la fin de ce fichier
 */

#define EXCEPTION_LANCE(VAL) longjmp(global_exception.buf[global_exception.profondeur-1], VAL)

/*
 * Ex�cuter un morceau de programme en r�cup�rant les exceptions
 * qui peuvent se produire.
 * CAS est une suite de :
 *     case Exception_toto:
 *         action ;
 *         break ;
 *
 * Il ne doit pas y avoir de cas "default:" car celui-ci est utilis�
 * pour faire remonter les exceptions au niveau sup�rieur.
 *
 * MENAGE est un morceau de code qui est ex�cut� AVANT de faire
 * les diff�rents cas, quand l'exception a eu lieu.
 */
#define EXCEPTION(CORPS, MENAGE, CAS)					     \
if ( global_exception.profondeur >= global_exception.profondeur_max )	     \
     global_exception.buf = realloc(global_exception.buf		     \
				    , ++global_exception.profondeur_max	     \
				      *sizeof(*global_exception.buf));	     \
global_exception.valeur_de_retour =					     \
	   setjmp(global_exception.buf[global_exception.profondeur]) ;	     \
if ( global_exception.valeur_de_retour == 0 )				     \
    {									     \
      global_exception.profondeur++ ;					     \
      CORPS ;								     \
      global_exception.profondeur-- ;					     \
    }									     \
else									     \
    {									     \
    MENAGE ;								     \
    switch(global_exception.profondeur--, global_exception.valeur_de_retour) \
        {								     \
        CAS								     \
        default:							     \
            if ( global_exception.profondeur )				     \
        	{							     \
        	/* Passe l'exception au niveau sup�rieur */		     \
        	EXCEPTION_LANCE(global_exception.valeur_de_retour) ;	     \
        	}							     \
            else							     \
        	fprintf(stderr, "***** Exception non r�cup�r�e : %d\n"	     \
			,global_exception.valeur_de_retour ) ;		     \
        }								     \
    }



enum {
  Exception_fichier_ouverture = 1,
  Exception_fichier_ecriture,
  Exception_fichier_lecture,
  Exception_fichier_fermeture,
  Exception_fichier_ecriture_dans_fichier_ouvert_en_lecture,
  Exception_fichier_lecture_dans_fichier_ouvert_en_ecriture,
  Exception_arbre_shannon_fano_invalide,

  Exception_derniere
} ;

#endif
