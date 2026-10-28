/* rgp:protos */
#define RGP_SELF_DataTableGetKey_40a3b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Pool accessor of the ContainerViewGetAtFwd_3f9af0 family, SINGLE entry, with the returned
   pointer dereferenced unconditionally in the `jr` delay slot.
   Stride read off this unit's OWN listing: addiu 0x754 + mult -> the stride is too big for shift-add */

typedef struct Pool {
    u8   pad000[0x7C];
    s16  m7C;
    u8   pad07E[0xE];
    u8  *m8C;
} Pool;

s32 DataTableGetKey_40a3b0(Pool *p, s32 i)
{
    return (s16)(*(s16 *)((i >= 0 && i < p->m7C) ? (void *)(p->m8C + i * 0x754)
                                          : (void *)0));
}
