/* rgp:protos */
#define RGP_SELF_EffectReleaseByGroup_2e12f0 1
#define RGP_SELF_busy 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
void *memset(void *, s32, s32);

typedef struct {
    s32 unk0;
    u8 pad4[4];
    u8 *unk8;
    s32 unkC;
    u8 pad10[0x54 - 0x10];
    s32 unk54;
    u8 pad58[8];
    s32 unk60;
    u8 pad64[0xC];
} E2e1;

static inline s32 busy(u8 *p) { s32 r = *(s32 *)(p + 0x28) != 0; return r; }

void EffectReleaseByGroup_2e12f0(u8 *arg0, s32 arg1) {
    s32 h;
    E2e1 *e;
    s32 i;

    h = ((s32)GetLoaderMgr_1f59d0());
    if (h == 0) {
        return;
    }
    EffDefsDestroyByGroup_1a0180(arg0 + 0x58, arg1);
    e = (E2e1 *)(arg0 + 0x174);
    i = 0;
    do {
        if (e->unk54 == arg1) {
        if (e->unk60 >= 0) {
            LoaderReleaseById_1cd340(h, e->unk60);
        }
        if (e->unk8 != 0 && !busy(e->unk8)) {
            if (e->unkC != 0) {
                MemStackHeapFree_14dcb0(e->unk8, e->unkC);
            }
        }
        memset(e, 0, 0x70);
        e->unk0 = -1;
        e->unk60 = -1;
        }
        i++;
        e++;
    } while (i < 0x30);
    EffectEntriesReleaseByGroup_2de680(arg0 + 0x1674, arg1);
}
