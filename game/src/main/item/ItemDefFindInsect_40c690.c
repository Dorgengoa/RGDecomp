/* rgp:protos */
#define RGP_SELF_ItemDefFindInsect_40c690 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* FIVE integer arguments: the EE ABI passes them in $4-$11, so `addiu $8,$0,-1`
   is the fifth argument, not a spill. */
/*rgp*/
void * ItemDefFindInsect_40c690(s32 a, s32 b, s32 c) { return ItemDefFindByKeys_40c6b0(a, 0x14, b + 0x7D0, c, -1); }
