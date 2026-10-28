/* rgp:protos */
#define RGP_SELF_SysParamTableGetInt_15fe80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* The asymmetric guard pair, returning a FIELD rather than the address: 0x80
   entries of 8 bytes at +0x10, and the +0x10 folds into the load's own
   displacement instead of costing an addiu. */

typedef struct Rec8 {
    s32 v;             /* +0x00 */
    s32 unk4;
} Rec8;

typedef struct Owner10 {
    u8 pad000[0x10];
    Rec8 rec[1];       /* +0x10 */
} Owner10;

s32 SysParamTableGetInt_15fe80(Owner10 *o, s32 index)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < 0x80;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    return o->rec[index].v;
}
