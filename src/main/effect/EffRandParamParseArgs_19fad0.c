#include "types.h"
typedef __int128 s128;

typedef struct E19f { s32 x0; s32 x4; } E19f;

extern s32 SlotGetInt_15f720(E19f *);
extern f32 VariantGetFloat_15f740(E19f *);
extern void EffRandParamSet_19a2a0(s32, s32, s32, f32 *, f32 *);

s32 EffRandParamParseArgs_19fad0(s32 arg0, E19f *arg1, s32 arg2)
{
    f32 spB0[4];
    s128 spA0;
    s32 i;
    s32 v16;
    s32 flag;
    s32 v22;
    E19f *p;
    s32 idx;
    s32 depth;


    flag = 0;
    v16 = 0;
    idx = 0;
    v22 = 0;
    spA0 = 0;
    i = 0;
    depth = 0;

loop:
    if (i < arg2) {
        p = &arg1[i];
        if (p->x0 == 0) {
            v16 = SlotGetInt_15f720(p);
            flag = 1;
            idx = 0;
        } else {
            if (flag == 0) {
                spB0[idx] = VariantGetFloat_15f740(p);
                depth++;
            } else {
                ((f32 *)&spA0)[idx] = VariantGetFloat_15f740(p);
                depth--;
            }
            idx++;
            if (idx >= 4) {
                idx = 3;
            }
        }
        i++;
        if (depth != 0) {
            goto loop;
        }
    }
    if (i < arg2) {
        v22 = SlotGetInt_15f720(&arg1[i]);
        i++;
    }
    EffRandParamSet_19a2a0(arg0, v16, v22, spB0, (f32 *)&spA0);
    return i;
}
