/* rgp:protos */
#define RGP_SELF_RandGaussian_197d70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#define K 2.3283064e-10f

f32 RandGaussian_197d70(u32 *seed)
{
    u32 r1;
    u32 r2;
    u32 r3;
    u32 r4;
    u32 r5;
    u32 r6;
    u32 r7;
    u32 r8;
    u32 r9;
    u32 r10;
    u32 r11;
    u32 r12;

    r1 = *seed * 0x5D588B65 + 1;
    *seed = r1;
    r2 = r1 * 0x5D588B65 + 1;
    *seed = r2;
    r3 = r2 * 0x5D588B65 + 1;
    *seed = r3;
    r4 = r3 * 0x5D588B65 + 1;
    *seed = r4;
    r5 = r4 * 0x5D588B65 + 1;
    *seed = r5;
    r6 = r5 * 0x5D588B65 + 1;
    *seed = r6;
    r7 = r6 * 0x5D588B65 + 1;
    *seed = r7;
    r8 = r7 * 0x5D588B65 + 1;
    *seed = r8;
    r9 = r8 * 0x5D588B65 + 1;
    *seed = r9;
    r10 = r9 * 0x5D588B65 + 1;
    *seed = r10;
    r11 = r10 * 0x5D588B65 + 1;
    *seed = r11;
    r12 = r11 * 0x5D588B65 + 1;
    *seed = r12;
    return K * (f32)r2 + K * (f32)r1 + K * (f32)r3 + K * (f32)r4 + K * (f32)r5 + K * (f32)r6 + K * (f32)r7 + K * (f32)r8 + K * (f32)r9 + K * (f32)r10 + K * (f32)r11 + K * (f32)r12 - 6.0f;
}
