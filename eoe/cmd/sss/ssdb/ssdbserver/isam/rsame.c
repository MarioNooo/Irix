/* Copyright (C) 1979-1996 TcX AB & Monty Program KB & Detron HB

   This software is distributed with NO WARRANTY OF ANY KIND.  No author or
   distributor accepts any responsibility for the consequences of using it, or
   for whether it serves any particular purpose or works at all, unless he or
   she says so in writing.  Refer to the Free Public License (the "License")
   for full details.
   Every copy of this file must include a copy of the License, normally in a
   plain ASCII text file named PUBLIC.	The License grants you the right to
   copy, modify and redistribute this file, but only under certain conditions
   described in the License.  Among other things, the License requires that
   the copyright notice and this notice be preserved on all copies. */

/* L{ser nuvarande record med direktl{sning */
/* Klarar b}de poster l{sta med nyckel och rrnd. */

#include "isamdef.h"

	/* Funktionen ger som resultat:
	   0 = Ok.
	   1 = Posten borttagen
	  -1 = EOF (eller motsvarande: se errno) */


int ni_rsame(N_INFO *info, byte *record, int inx)


					/* If inx >= 0 find record using key */
{
  DBUG_ENTER("ni_rsame");

  if (inx >= (int) info->s->state.keys || inx < -1)
  {
    my_errno=HA_ERR_WRONG_INDEX;
    DBUG_RETURN(-1);
  }
  if (info->lastpos == NI_POS_ERROR || info->update & HA_STATE_DELETED)
  {
    my_errno=HA_ERR_KEY_NOT_FOUND;	/* No current record */
    DBUG_RETURN(-1);
  }
  info->update&= HA_STATE_CHANGED;

  /* L{s record fr}n datafilen */

#ifndef NO_LOCKING
  if (_ni_readinfo(info,F_RDLCK,1))
    DBUG_RETURN(-1);
#endif

  if (inx >= 0)
  {
    info->lastinx=inx;
    VOID(_ni_make_key(info,(uint) inx,info->lastkey,record,info->lastpos));
    VOID(_ni_search(info,info->s->keyinfo+inx,info->lastkey,0,SEARCH_SAME,
		    info->s->state.key_root[inx]));
  }

  if ((*info->read_record)(info,info->lastpos,record) == 0)
    DBUG_RETURN(0);
  if (my_errno == HA_ERR_RECORD_DELETED)
  {
    my_errno=HA_ERR_KEY_NOT_FOUND;
    DBUG_RETURN(1);
  }
  DBUG_RETURN(-1);
} /* ni_rsame */
