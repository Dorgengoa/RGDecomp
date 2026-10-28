/* rgp:protos */
#define RGP_SELF_JudgeObjectHitIntervalCheckMaybe_3140e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R003140e0 {
    u8 pad0[4];
    s8 lim : 6;
} R003140e0;

/*rgp*/

s32 JudgeObjectHitIntervalCheckMaybe_3140e0(u8 *o, s32 k)
{
    s32 idx;
    s8 *p;
    s16 *c;
    R003140e0 *r;
    s32 lim;

    if (k < 0 || k >= 12) {
        if (k >= 0x80) {
            if (k >= 0x9C) {
                idx = -1;
            } else {
                idx = k - 0x74;
            }
        } else {
            idx = -1;
        }
    } else {
        idx = k;
    }
    if (idx < 0) {
        return 0;
    }
    p = (s8 *)((u32)idx + (u32)o + 0x120);
    if (*p <= 0) {
        *p = 1;
        *(s16 *)(&((s16 *)(o + 0xD0))[idx]) = 0;
    } else {
        r = ((R003140e0 *)ExecInfoGetActDataMaybe_3a7170(o + 0x10));
        if (r == 0) {
            return 0;
        }
        k = r->lim;
        if (k <= 0) {
            goto fail;
        }
        c = (s16 *)(&((s16 *)(o + 0xD0))[idx]);
        if (*c < k || *c <= 0) {
        fail:
            return 0;
        }
        (*p)++;
        *c = 0;
    }
ok:
    return 1;
}
