/* rgp:protos */
#define RGP_SELF_InsectCageMgrSyncSlots_39ae00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S0039ae00 {
    u8 pad0[0x94];
    s16 arr[6];
    s16 n;
} S0039ae00;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void InsectCageMgrSyncSlots_39ae00(S0039ae00 *o)
{
    s32 j;
    s32 i;
    u8 *p;

    if (((unsigned char)InsectCageMgrIsEnabled_39b190(o)) != 0) {
    for (j = 0; j < 3; j++) {
        p = (u8 *)o + j * 0x30;
        for (i = 0; i < o->n; i++) {
            if (o->arr[i] == ((short)InsectCageSlotGetId_39b460(p))) {
                break;
            }
        }
        if (i >= o->n) {
            InsectCageSlotRelease_39b9c0(p);
        }
    }
    for (i = 0; i < o->n; i++) {
        InsectCageMgrGetOrLoadSlot_39a330(o, o->arr[i]);
    }
    for (i = 0; i < 3; i++) {
        InsectCageSlotLoadModel_39b700((u8 *)o + i * 0x30);
    }
    } else {
        InsectCageMgrReleaseAll_39a2e0(o);
    }
}
