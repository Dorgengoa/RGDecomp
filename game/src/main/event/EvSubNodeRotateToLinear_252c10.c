/* rgp:protos */
#define RGP_SELF_EvSubNodeRotateToLinear_252c10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Src {
    u8 pad0[0x10];
    f32 v[4];
    s32 count;
} Src;

typedef struct Dst {
    u8 pad0[0x44];
    s32 cur;
    u8 pad48[0x38];
    f32 rot[4];
    u8 pad90[0x10];
    f32 delta[4];
} Dst;

/*rgp*/
extern f32 D_0047D1FC;
extern f32 D_0047DBA4;
extern f32 D_0047DBA8;
extern f32 D_0047DBAC;
extern f32 D_0047DBB0;

s32 EvSubNodeRotateToLinear_252c10(Src *arg0, Dst *__restrict arg1)
{
    s32 i;
    f32 *p;
    f32 f;

    if (arg0->count < 0) {
        for (i = 0; i < 3; i++) {
            p = &arg1->rot[i];
            *p += arg0->v[i];
            if (*p > D_0047D1FC) {
                *p -= D_0047DBA4;
            } else if (*p <= D_0047DBA8) {
                *p += D_0047DBA4;
            }
        }
    } else if (arg1->cur >= arg0->count) {
        sceVu0CopyVector(arg1->rot, arg0->v);
        arg1->cur = 0;
        return 0;
    } else {
        if (arg1->cur <= 0) {
            for (i = 0; i < 3; i++) {
                f = arg0->v[i] - arg1->rot[i];
                if (f > D_0047D1FC) {
                    f -= D_0047DBAC;
                } else if (f <= D_0047DBB0) {
                    f += D_0047DBAC;
                }
                arg1->delta[i] = f / (f32)arg0->count;
            }
        } else {
            for (i = 0; i < 3; i++) {
                p = &arg1->rot[i];
                *p += arg1->delta[i];
                if (*p > D_0047D1FC) {
                    *p -= D_0047DBAC;
                } else if (*p <= D_0047DBB0) {
                    *p += D_0047DBAC;
                }
            }
        }
        arg1->cur++;
    }
    return 1;
}
