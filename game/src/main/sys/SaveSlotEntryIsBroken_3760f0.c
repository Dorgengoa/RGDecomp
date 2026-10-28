/* rgp:protos */
#define RGP_SELF_SaveSlotEntryIsBroken_3760f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct P3760F0 { s8 m0; s8 m1; } P3760F0;

s32 SaveSlotEntryIsBroken_3760f0(P3760F0 *p)
{
    if (p->m0 == 1) {
        if (p->m1 == 1) return 1;
    }
    return 0;
}
