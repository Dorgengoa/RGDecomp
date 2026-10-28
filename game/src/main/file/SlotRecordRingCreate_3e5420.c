/* rgp:protos */
#define RGP_SELF_SlotRecordRingCreate_3e5420 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on
#pragma opt_repositioncode off
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004658E8[0x100];

typedef struct {
    u8 pad0[0x8];
    u8 *unk8;
    u8 padC[0x5c];
    s32 unk68;
} T3e5420_arg0;

s32 SlotRecordRingCreate_3e5420(T3e5420_arg0 *arg0, u8 *arg1, s32 arg2) {
    u8 *p;
    s32 n;
    u8 *q;
    s16 *h;
    s32 t;

    WorldDataMgrRelease_3f0320(arg0->unk8, 1);
    q = arg0->unk8;
    p = *(u8 **)(q + 0x24);
    n = *D_004658E8;
    if (arg1 != 0) {
        p = arg1;
        if (arg2 > 0) {
            n = arg2;
        }
    }
    if (p == 0) {
        return 0;
    }
    if (n <= 0) {
        n = (*(s32 *)(p + 0x34) - *(s32 *)(p + 0x2C)) / 53;
    }
    h = *(s16 **)(q + 0x28);
    if (h != 0) {
        *h = 0xA;
    }
    t = ((s32)MemStackNew_14e130(0x18, p));
    if (t != 0) {
        SlotRecordRingInit_3ee730(t, p, n);
    }
    arg0->unk68 = t;
    if (t == 0) {
        return 0;
    }
    return n;
}
