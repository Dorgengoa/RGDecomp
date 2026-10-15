#include "types.h"
#pragma opt_propagation off

extern void LoadHandlePoll_1ccb00(void *);
extern void WarpMenuRelease_39ddd0(void *);
extern void MemStackAlign64_14d8e0(void *);
extern s32 MemStackAllocQw_14d950(s32, s32);
extern void memcpy(s32, s32, s32);
extern s32 GetDrawCtxNameTable_15de40(void);
extern void NameTableRegisterImArchive_1594d0(s32, s32, s32, s32, s32);
extern void LoaderReleaseHandle_1ccb70(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

/* PARKED at 6 bad words, exact length (was 16 B short before this session's
   control-flow fix). The pass-11 decoder had inverted two early-return
   paths: retail calls WarpMenuRelease_39ddd0(p0) and returns immediately when
   (t1==-1||t2==-1) or when (r6==0||r9==0); the stub instead always fell
   through into MemStackAlign64_14d8e0 on a merged pointer. Fixing that closed 16 B.
   Remaining 6 words are two DISTINCT residue classes, both confirmed
   INERT to every source-level spelling tried (operand swap, `-(-x)`
   de-commutation, statement reorder, direct field access, an explicit
   carried accumulator, and a full opt_schedule/peephole/optimization_level
   0-4 pragma sweep -- all either no-ops or regressions):
     1. 0x0039DB84 / 0x0039DCB0 (both loop index*3 sites): retail emits
        `addu $2,$2,$16`, we emit `addu $2,$16,$2` -- same operands,
        transposed, on a loop-carried value. Every commutative-add lever
        in memory/levers.d/mwcc-commutative-add-operand-order.md was tried.
     2. 0x0039DC3C/DC50 and DC5C/DC60: two independent field loads
        (p0->m04 vs p0->m08, then p0->m10 vs p0->m14) that fill a
        branch-likely delay slot in the OPPOSITE order from retail,
        regardless of source statement order or inlining at the call site.
   Do not re-sweep spelling on these two classes without a new mechanism;
   see mwcc-callee-saved-creation-order.md's "frozen pair" ceiling. */

struct Obj0;
typedef struct { u8 b[12]; } E12;

struct Obj0 {
    u8 pad000[0x2];
    s16 m02;
    s32 m04;
    s32 m08;
    u8 pad00C[0x2];
    s16 m0E;
    s32 m10;
    s32 m14;
    u8 pad018[0x8];
    s32 m20;
    s16 m24;
    u8 pad026[0xA];
    u8 m30;
};

void WarpMenuLoadStep_39db50(struct Obj0 *p0)
{
                s32 arg_h2;

    s16 t0;
    s32 l0;
    s16 t1;
    s16 t2;
    struct Obj0 * rv2;
    s32 t3;
    s32 t4;
    u32 rv5;
    s32 t5;
    s32 r6;
    s32 t6;
    u32 rv8;
    s32 t7;
    s32 r9;
    s32 r12;
    s32 t12;
    s32 t13;
    s32 l15;
    u8 t14;

    t0 = p0->m24;
    if (t0 == 1) {
        l0 = 0;
        do {
            LoadHandlePoll_1ccb00((struct Obj0 *)&((E12 *)p0)[l0]);
            l0 = (l0 + 1);
        } while (l0 < 2);
        t1 = p0->m02;
        if (t1 != 0) {
            t2 = p0->m0E;
            if (t2 != 0) {
                if (t1 == -1 || t2 == -1) {
                    WarpMenuRelease_39ddd0(p0);
                    return;
                }
                t3 = p0->m20;
                rv2 = (struct Obj0 *)t3;
                MemStackAlign64_14d8e0(rv2);
                t4 = p0->m08;
                rv5 = (t4 & 0xF) ? ((((u32)t4) >> 4) + 1) : (((u32)t4) >> 4);
                t5 = p0->m20;
                r6 = MemStackAllocQw_14d950(t5, rv5);
                t6 = p0->m14;
                rv8 = (t6 & 0xF) ? ((((u32)t6) >> 4) + 1) : (((u32)t6) >> 4);
                t7 = p0->m20;
                r9 = MemStackAllocQw_14d950(t7, rv8);
                if (r6 == 0 || r9 == 0) {
                    WarpMenuRelease_39ddd0(p0);
                    return;
                }
                arg_h2 = p0->m08;
                memcpy(r6, p0->m04, arg_h2);
                arg_h2 = p0->m14;
                memcpy(r9, p0->m10, arg_h2);
                r12 = GetDrawCtxNameTable_15de40();
                t12 = p0->m20;
                NameTableRegisterImArchive_1594d0(r12, r6, 0x330, t12, 0);
                t13 = p0->m20;
                NameTableRegisterImArchive_1594d0(r12, r9, 0x330, t13, 0);
                l15 = 0;
                do {
                    LoaderReleaseHandle_1ccb70((struct Obj0 *)&((E12 *)p0)[l15]);
                    l15 = (l15 + 1);
                } while (l15 < 2);
                t14 = p0->m30;
                if (t14 != 0) {
                    p0->m24 = 4;
                } else {
                    p0->m24 = 2;
                }
            }
        }
        return;
    }
}
