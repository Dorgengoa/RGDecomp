/* rgp:protos */
#define RGP_SELF_insect_InsectBattleGetHeap_50e110 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050E110 -- pass-28 unnamed-listing conversion.  `sll 2` + `addu`
 * + `lw 0xD8` is an s32 array at +0xD8 read by the second argument. */
typedef struct Tab {
    u8 pad00[0xD8];
    s32 mD8[1];        /* +0xD8 */
} Tab;

s32 insect_InsectBattleGetHeap_50e110(Tab *t, s32 i)
{
    return t->mD8[i];
}
