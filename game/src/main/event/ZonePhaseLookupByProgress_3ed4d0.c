/* rgp:protos */
#define RGP_SELF_ZonePhaseLookupByProgress_3ed4d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on

typedef struct {
    u8 pad0[0x2C];
    s32 f2C;
    u8 pad30[4];
    s32 f34;
} Obj34;

typedef struct {
    u8 pad0[0x34];
    Obj34 *p34;
} Obj8;

typedef struct {
    u8 pad0[8];
    Obj8 *p8;
    u8 padC[4];
    s32 p10;
    u8 pad14[4];
    s32 p18;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 ZonePhaseLookupByProgress_3ed4d0(Obj *arg0, s32 arg1, s32 arg2) {
    s32 h;
    s32 hi;
    s32 q;
    s32 i;
    s32 v;
    s32 r;

    if (arg0->p18 == 0 || arg0->p10 == 0) {
        return 0;
    }
    if (arg1 < 0) {
        return 0;
    }
    h = ((short)StateGetChapter_3cd5b0(arg0->p10));
    hi = arg2;
    if (arg2 < 0) {
        arg2 = 0;
        hi = 4;
    }
    i = hi;
    q = (s16)arg1 / 100;
    for (; i >= arg2; i--) {
        v = ((short)ProgressValueGet_3cd2c0(arg0->p10, (long long)(h), (long long)(i), 0));
        if (v >= 0) {
            r = ZonePhaseSetLookup_414ae0(arg0->p8->p34->f2C, q, arg1, h, i, v);
            if (r != 0) {
                return r;
            }
        }
    }
    for (i = hi; i >= arg2; i--) {
        v = ((short)ProgressValueGet_3cd2c0(arg0->p10, (long long)(h), (long long)(i), 0));
        if (v >= 0) {
            r = ZonePhaseMatrixLookupValue_414700(arg0->p8->p34->f34, q, arg1, h, i, v);
            if (r != 0) {
                return r;
            }
        }
    }
    return 0;
}
