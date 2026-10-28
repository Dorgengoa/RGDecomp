/* rgp:protos */
#define RGP_SELF_DataTableGetKey_418ff0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Pool accessor of the ContainerViewGetAtFwd_3f9af0 family, SINGLE entry, with the returned
   pointer dereferenced unconditionally in the `jr` delay slot.
   Stride read off this unit's OWN listing: sll 2, addu, sll 1, addu, sll 2 -> ((((i<<2)+i)<<1)+i)<<2 = 44 */

typedef struct Pool {
    u8   pad000[0x7C];
    s16  m7C;
    u8   pad07E[0xE];
    u8  *m8C;
} Pool;

s32 DataTableGetKey_418ff0(Pool *p, s32 i)
{
    return *(s32 *)((i >= 0 && i < p->m7C) ? (void *)(p->m8C + i * 44)
                                          : (void *)0);
}
