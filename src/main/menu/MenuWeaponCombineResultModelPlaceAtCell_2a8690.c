#include "types.h"

#pragma opt_foldconstants off

typedef struct {
    f32 x, y, z, w;
} V002A8690;

extern void ModelSetScale_150ff0(s32, V002A8690 *);
extern void ModelSetPos_151110(s32, V002A8690 *);
extern void MotionListResetAll_171e00(s32);
extern void ModelObjPlayMotionByName_1867a0(s32, void *, s32);
extern u8 D_00461458[];
extern f32 D_0047D740;
extern f32 D_0047D744;
extern f32 D_0047EC40;
extern f32 D_0047EC44;
extern f32 D_0047EC48;
extern f32 D_0047EC4C;
extern s8 D_00482494;
extern s32 D_004824B8;

static inline void zero002A8690(void *p, s32 n)
{
    u8 *q = p;

    if (q != NULL) {
        do {
            *q++ = 0;
        } while (--n != 0);
    }
}

s32 MenuWeaponCombineResultModelPlaceAtCell_2a8690(s32 arg0, s32 arg1) {
    V002A8690 a;f32 *q = (f32 *)&a;
    V002A8690 b;
    f32 f;
    s32 d;

    if (D_004824B8 != 0) {
        D_00482494 = 1;
        MotionListResetAll_171e00(D_004824B8 + 0x1F0);
        ModelObjPlayMotionByName_1867a0(D_004824B8, D_00461458, 2);
        q[0] = D_0047EC40;
        q[1] = D_0047EC44;
        q[2] = D_0047EC48;
        q[3] = D_0047EC4C;
        a.x = D_0047D740 * (f32)arg0 + 11.0f;
        a.y = -5.875f * (f32)arg1 + 35.0f;
        a.z = 0.0f;
        ModelSetPos_151110(D_004824B8, (V002A8690 *)&a);
        d = D_004824B8;
        {u8 *p=(u8 *)&b;u32 n=16;if(p){do{*p=0;n--;p++;}while(n);}}
        f = D_0047D744;
        b.x = f;
        b.y = f;
        b.z = f;
        ModelSetScale_150ff0(d, &b);
        return 1;
    }
    return 0;
}
