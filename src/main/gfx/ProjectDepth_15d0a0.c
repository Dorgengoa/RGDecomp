#include "types.h"
typedef struct { f32 w[4]; } SD4_0047DF20;
extern SD4_0047DF20 D_0047DF20 __attribute__((section(".sdata")));

typedef struct S004810A4 {
    u8 pad0[0xF20];
    s32 unkF20;
} S004810A4;

extern void MtxMulPoint_13c890(f32 *out, s32 arg1, f32 *in);
extern const f32 D_0047DF24 __attribute__((section(".sdata")));
extern const f32 D_0047DF28 __attribute__((section(".sdata")));
extern S004810A4 *D_004810A4;

s32 ProjectDepth_15d0a0(f32 fparg0)
{
    f32 in[4];
    f32 out[4];
    f32 temp_f0;
    f32 temp_f3;
    s32 var_2;

    *(SD4_0047DF20 *)in = D_0047DF20;
    in[2] = -fparg0;
    if (D_004810A4 == NULL) {
        var_2 = 0;
    } else {
        var_2 = D_004810A4->unkF20;
    }
    MtxMulPoint_13c890(out, var_2 + 0x200, in);
    temp_f3 = 1.0f / out[3];
    out[0] *= temp_f3;
    out[1] *= temp_f3;
    temp_f0 = out[2] * temp_f3;
    out[2] = temp_f0;
    return (s32) temp_f0;
}
