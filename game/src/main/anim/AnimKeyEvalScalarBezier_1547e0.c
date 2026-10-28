/* rgp:protos */
#define RGP_SELF_AnimKeyEvalScalarBezier_1547e0 1
#include "port/game_protos.h"
#line 1
/* PARKED s17b: not attempted. m2c's draft references several undeclared
   stack locals (spE4/spE8/spEC/spF0) it lost track of -- a switch on
   arg1->unk1 (case 16/32, others presumably fall through to nothing) doing
   blend-curve evaluation via SplineEvalBezierScalar_14b720/SplineEvalBezierSolveTime_14b8a0. Needs a from-scratch
   asm read of asm/matchings/main/AnimKeyEvalScalarBezier_1547e0.s to recover the missing
   fields (likely more of arg1's struct). Not attempted this lane. */
/* s49m: MATCH */
#include "types.h"

typedef struct {
    f32 t;
    s32 type;
    s32 keys;
    s32 base;
    s32 count;
    s32 keyA;
    s32 keyB;
    s32 timeA;
    s32 timeB;
} AnimClock;

typedef struct { f32 x, y, z, w; } V4;
typedef struct { f32 v[5]; } K5;
typedef struct { s16 v[5]; } S5;

/*rgp*/
/*rgp*/
/*rgp*/

void AnimKeyEvalScalarBezier_1547e0(f32 *arg0, u8 *arg1, f32 fparg0)
{
    AnimClock c __attribute__((aligned(16)));
    V4 a[5] __attribute__((aligned(16)));
    V4 b[5] __attribute__((aligned(16)));
    f32 r;

    c.type = arg1[2];
    c.keys = *(s32 *)(arg1 + 0x8);
    c.count = *(u16 *)(arg1 + 0x6);
    c.t = fparg0;
    c.base = *(s16 *)(arg1 + 0x4);
    r = AnimKeyFindSpan_155ff0(&c);
    if (arg1[1] == 0x20) {
        K5 *tbl = *(K5 **)(arg1 + 0xC);
        if (r == 0.0f) {
            *arg0 = tbl[c.keyA].v[0];
        } else {
            SplineEvalBezierScalar_14b720(arg0, &tbl[c.keyA], &tbl[c.keyB], (f32)c.timeA, (f32)c.timeB, r);
        }
    } else if (arg1[1] == 0x10) {
        S5 *tbl = *(S5 **)(arg1 + 0xC);
        S5 *pa = &tbl[c.keyA];
        S5 *pb = &tbl[c.keyB];
        if (r == 0.0f) {
            *arg0 = 0.000030517578f * (f32)pa->v[0] * *(f32 *)(arg1 + 0x10);
        } else {
            a[0].x = 0.000030517578f * (f32)pa->v[0] * *(f32 *)(arg1 + 0x10);
            a[1].x = 0.000030517578f * (f32)pa->v[1] * *(f32 *)(arg1 + 0x10);
            a[2].x = 0.000030517578f * (f32)pa->v[2] * *(f32 *)(arg1 + 0x10);
            b[0].x = 0.000030517578f * (f32)pb->v[0] * *(f32 *)(arg1 + 0x10);
            b[3].x = 0.000030517578f * (f32)pb->v[3] * *(f32 *)(arg1 + 0x10);
            b[4].x = 0.000030517578f * (f32)pb->v[4] * *(f32 *)(arg1 + 0x10);
            SplineEvalBezierSolveTime_14b8a0(arg0, a, b, (f32)c.timeA, (f32)c.timeB, r);
        }
    }
}
