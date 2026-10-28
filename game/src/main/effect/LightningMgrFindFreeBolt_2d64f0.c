/* rgp:protos */
#define RGP_SELF_LightningMgrFindFreeBolt_2d64f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Elem002d64f0 {
    u8 pad0[0xC2];
    s16 unkC2;
    u8 padC4[0xD0 - 0xC4];
} Elem002d64f0;

Elem002d64f0 *LightningMgrFindFreeBolt_2d64f0(Elem002d64f0 **arg0)
{
    Elem002d64f0 *elem;
    s32 i;

    elem = *arg0;
    if (elem == NULL) {
        return NULL;
    }
    i = 0;
    while (i < 0x40) {
        if (elem->unkC2 <= 0) {
            return elem;
        }
        i++;
        elem++;
    }
    return NULL;
}
