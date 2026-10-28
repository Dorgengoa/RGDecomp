/* rgp:protos */
#define RGP_SELF_SoundStreamSlotQueryState_1bd210 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

/*rgp*/
void SignalSema(s32);
void WaitSema(s32);
extern s32 D_004814F0[2];
extern u8 D_004A25F0[0x4A0];

s32 SoundStreamSlotQueryState_1bd210(s32 arg0) {
    u8 *p;
    u8 *q;
    s32 r;
    s32 v;
    s32 b;
    u8 t;

    if (arg0 < 0 || arg0 >= 4) {
        p = NULL;
    } else {
        p = D_004A25F0 + arg0 * 0x128;
    }
    if (p == NULL || D_004814F0[arg0] == 0) {
        p = NULL;
    }
    if (p == NULL) {
        return -2;
    }
    if (arg0 < 0 || arg0 >= 4) {
        q = NULL;
    } else {
        q = D_004A25F0 + arg0 * 0x128;
    }
    if (q == NULL || D_004814F0[arg0] == 0) {
        q = NULL;
    }
    if (q == NULL) {
        b = 0;
    } else {
        r = 0;
        if (*(s32 *)(q + 0xC) > 0) {
            WaitSema(*(s32 *)(q + 0xC));
        }
        if (*(u8 *)(q + 0x4D) == 0) {
            v = *(u8 *)(q + 0x50) != 0;
            if (v != 0) {
                v = *(s32 *)(q + 0x54) == *(s32 *)(q + 0x58);
            }
            if (v == 0) {
                r = 1;
            }
        } else {
            r = 1;
        }
        if (*(s32 *)(q + 0xC) > 0) {
            SignalSema(*(s32 *)(q + 0xC));
        }
        if (r != 0) {
            t = r != 0;
        } else {
            t = 0;
        }
        b = t;
    }
    if (b != 0) {
        return -1;
    }
    return SoundStreamSlotGetState_1be710(p);
}
