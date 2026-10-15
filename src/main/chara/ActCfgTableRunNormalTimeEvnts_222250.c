#include "types.h"

extern s32 StrNotEqual_1f5300(void *arg0, void *arg1);
extern void ActCfgTableRunTimeEvntRefs_221ea0(s32 arg0, s32 arg1, s32 arg2, s64 arg3, f32 arg4, f32 arg5);
extern void ActTimeEvntRunInRange_2281d0(s32 arg0, s32 arg1, f32 arg2, f32 arg3);
extern s32 IntCompare_42ca30(s32 arg0, s16 arg1);
extern s32 DListGetHead_42ea60(s32 arg0);
extern s32 DListGetCountPow2_42ea70(s32 arg0);
extern s32 DListNodeAdvance_42eb00(s32 arg0, s32 arg1);

typedef struct {
    u8 pad0[0x28];
    s8 **unk28;
    s16 unk2C;
} TV;

typedef struct {
    u8 pad0[0x4];
    s32 unk4;
    s32 unk8;
    u8 padC[0x18];
    s16 unk24;
    s16 unk26;
} TP;

static inline s8 **find(TV *v, s8 *name) {
    s8 **p;
    s32 i;
    p = v->unk28;
    if (p == 0) return 0;
    for (i = 0; i < v->unk2C; i++, p = (s8 **)((u8 *)p + 0x34)) {
        if (*name == **p && StrNotEqual_1f5300(*p + 1, name + 1) == 0) return p;
    }
    return 0;
}

void ActCfgTableRunNormalTimeEvnts_222250(s32 arg0, s32 arg1, s32 arg2, s8 *arg3, f32 fparg0, f32 fparg1)
{
    s32 res;
    s32 lo;
    s32 n;
    s32 node;
    s32 c;
    TV *v;
    s8 **p;
    s32 i;
    s32 q;
    s32 j;

    lo = DListGetHead_42ea60(arg0 + 0x7C);
    if (lo == 0) {
        res = 0;
    } else {
        res = 0;
        n = DListGetCountPow2_42ea70(arg0 + 0x7C);
        while (n > 0) {
            n >>= 1;
            node = DListNodeAdvance_42eb00(lo, n);
            if (node != 0) {
                c = IntCompare_42ca30(arg2, *(s16 *)(node + 0x3E));
                if (c == 0) {
                    res = node;
                    break;
                }
                if (c > 0) {
                    lo = node;
                }
            }
        }
    }
    if (res == 0) v = 0; else v = (TV *)(res + 0x10);
    if (v == 0) {
        p = 0;
    } else if (arg3 == 0) {
        p = 0;
    } else {
        p = find(v, arg3);
    }
    if (p != 0) {
        q = ((TP *)p)->unk8;
        if (q != 0) {
            for (j = 0; j < ((TP *)p)->unk26; j++, q += 0x10) {
                ActTimeEvntRunInRange_2281d0(q, arg1, fparg0, fparg1);
            }
        }
        ActCfgTableRunTimeEvntRefs_221ea0(arg0, arg1, ((TP *)p)->unk4, ((TP *)p)->unk24, fparg0, fparg1);
    }

}
