/* rgp:protos */
#define RGP_SELF_MapSceneCfgGetPcpName_193720 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Asymmetric guard pair: count at +0x44, s32 table at +0x48. */

typedef struct Owner44 {
    u8 pad000[0x44];
    s32 count;         /* +0x44 */
    s32 rec[1];        /* +0x48 */
} Owner44;

s32 MapSceneCfgGetPcpName_193720(Owner44 *o, s32 index)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < o->count;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    return o->rec[index];
}
