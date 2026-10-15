#include "types.h"

typedef struct S0039ae00 {
    u8 pad0[0x94];
    s16 arr[6];
    s16 n;
} S0039ae00;

extern void InsectCageMgrReleaseAll_39a2e0(S0039ae00 *);
extern void InsectCageMgrGetOrLoadSlot_39a330(S0039ae00 *, s16);
extern s32 InsectCageMgrIsEnabled_39b190(S0039ae00 *);
extern s32 InsectCageSlotGetId_39b460(void *);
extern void InsectCageSlotLoadModel_39b700(void *);
extern void InsectCageSlotRelease_39b9c0(void *);

void InsectCageMgrSyncSlots_39ae00(S0039ae00 *o)
{
    s32 j;
    s32 i;
    u8 *p;

    if (InsectCageMgrIsEnabled_39b190(o) != 0) {
    for (j = 0; j < 3; j++) {
        p = (u8 *)o + j * 0x30;
        for (i = 0; i < o->n; i++) {
            if (o->arr[i] == InsectCageSlotGetId_39b460(p)) {
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
