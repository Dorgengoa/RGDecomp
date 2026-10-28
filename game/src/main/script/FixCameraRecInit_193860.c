/* rgp:protos */
#define RGP_SELF_FixCameraRecInit_193860 1
#include "port/game_protos.h"
#line 1
#include "port/vu0intrin.h" /* rg:vu0bind */
#include "types.h"
/* FixCameraRecInit_193860 -- reset: f0 = 0, eight qwords cleared from VU0 vf0, then two
 * counted tables (4 x s32 = 0, 4 x {-1, 0}).  Asm-free (s88m, was a whole-function
 * asm source).  The old asm sqc2 was a scheduling barrier inside a 6-instruction
 * loop:
 * - goto form keeps the `b test` entry (a for-loop with constant bounds rotates);
 * - zero-word block split after the store keeps `sqc2` ahead of `i++`;
 * - zero-word block split at the loop head makes the latch's target start with a
 *   branch pcode, so the delay-slot pass does not thread `sll` into a bnel and
 *   leaves retail's `bnez; nop`. */

#pragma vu0_mmi_reg_binding on
typedef rg_s128 __attribute__((aligned(4))) rgvb_vz193860_t; /* rg:vu0bind vf0 */
#define vz193860 RG_VU0_BIND_VF(0, rgvb_vz193860_t)


typedef struct { s32 a; s32 b; } Pair193860;
typedef struct {
    s32 f0;
    s32 pad[3];
    rg_s128 v[8];
    s32 n1;
    s32 x[4];
    s32 n2;
    Pair193860 y[4];
} S193860;

void FixCameraRecInit_193860(S193860 *p)
{ RG_VU0_FRAME;
    s32 i;

    p->f0 = 0;
    i = 0;
    goto cond;
body:
    if (p) { p = (S193860 *)(s32)(u32)p; }
    p->v[i] = vz193860;
    if (p) { p = (S193860 *)(s32)(u32)p; }
    i++;
cond:
    if (i < 8) goto body;
    p->n1 = 4;
    for (i = 0; i < p->n1; i++) {
        p->x[i] = 0;
    }
    p->n2 = 4;
    for (i = 0; i < p->n2; i++) {
        p->y[i].b = 0;
        p->y[i].a = -1;
    }
}
