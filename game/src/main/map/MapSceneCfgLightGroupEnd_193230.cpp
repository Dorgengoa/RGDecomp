/* main s27m: CLOSED -- dst[i] = src[i] over 0x1D0-byte records copied MEMBERWISE
   (C++), `#pragma opt_loop_invariants off` (retail re-materialises each inner
   copy loop counter per record), and the whole body NESTED under
   `if (D_00481308 == 0)` so the first test is retail bnel-to-epilogue. */
#pragma opt_loop_invariants off
#include "types.h"
#include "vec.h"

typedef struct { f32 x; f32 y; f32 z; f32 w; } V4_193230;
typedef struct { s32 a; s32 b; } P_193230;
typedef struct { u128 a; u128 b; } Q_193230;

typedef struct {
    f32 f0;
    V4_193230 v10 __attribute__((aligned(16)));
    V4_193230 v20;
    P_193230 p30[8];
    P_193230 p70[8];
    s32 wB0;
    Q_193230 qC0[6];
    V4_193230 v180;
    V4_193230 v190;
    s32 w1A0;
    P_193230 p1A4[4];
} E_193230;

typedef struct {
    u8 pad0[4];
    s32 n;
    E_193230 *arr;
} Sub_193230;

typedef struct {
    u8 pad0[0x9C];
    s32 n;
    E_193230 *arr;
    u8 padA4[4];
    Sub_193230 sub;
} Base_193230;

extern "C" s32 D_00481308;
extern "C" Base_193230 *D_004812F4;

extern "C" s32 MapSceneCfgLightGroupEnd_193230(void)
{
    Base_193230 *base;
    Sub_193230 *sub;
    s32 i;

    if (D_00481308 == 0) {
        base = D_004812F4;
        sub = &base->sub;
        if ((sub != NULL) && (sub->arr != NULL) && (base->arr != NULL) && (sub->n == base->n)) {
            for (i = 0; i < base->n; i++) {
                base->arr[i] = sub->arr[i];
            }
        }
    }
    return 1;
}
