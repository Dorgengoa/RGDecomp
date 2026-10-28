/* rgp:protos */
#define RGP_SELF_GetCam 1
#define RGP_SELF_ProjectToScreen_15d340 1
#include "port/game_protos.h"
#line 1
/* PARKED at triage (0 round trips): m2c's draft references `sp2C`, `sp4C`(??
 * as a scaling divisor after MtxMulPoint_13c890 fills `sp20`), and `sp74`/`sp10` --
 * only sp28/sp24/sp20 are declared, so the surrounding stack fields
 * (retail's real vector components) are un-named. Needs a raw-asm trace of
 * the frame before compiling. Deferred. See asm/matchings/main/ProjectToScreen_15d340.s. */
/* s49m: MATCH */
#include "types.h"

typedef struct {
    f32 x, y, z, w;
} Vec4;

typedef struct Obj0 {
    u8 pad000[0xF20];
    u8 *mF20;
} Obj0;

extern Obj0 *D_004810A4;
/*rgp*/

static inline u8 *GetCam(void)
{
    if (D_004810A4 == 0) {
        return 0;
    }
    return D_004810A4->mF20;
}

s32 ProjectToScreen_15d340(s32 *out, Vec4 *in)
{
    Vec4 v __attribute__((aligned(16)));
    f32 inv;
    u8 *p;

    MtxMulPoint_13c890(&v, GetCam() + 0x1C0, in);
    inv = 1.0f / v.w;
    v.x *= inv;
    v.y *= inv;
    v.z *= inv;
    out[0] = 16.0f * v.x;
    out[1] = 16.0f * v.y;
    out[2] = v.z;
    out[3] = 0;
    p = GetCam() + 0x14;
    if (v.x < 0.0f || v.x > 0xFFF) {
        return 0;
    }
    if (v.y < 0.0f || v.y > 0xFFF) {
        return 0;
    }
    if (v.w < *(f32 *)(p + 0xC) || v.w > *(f32 *)(p + 0x10)) {
        return 0;
    }
    return 1;
}
