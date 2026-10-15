#include "types.h"

/* MAIN MenuMainResLoad_299080 -- CALLED BY the settled seed src/wf/main/MainMenuInit_297510.c
   and re-using its data reading:  D_004823F8 is the block that seed allocates
   with `MemStackNew_14e1b0((s16)n * 0x38, D_00482334)`, so it is an array of
   0x38-byte elements and retail's `((i<<3)-i)<<3` is that *56 strength
   reduction; the dead `lbu 0x24C / andi 1` is the seed's `n = 3; if (bit)
   n = 3;` (mwcc folds the select, keeps the condition).

   Branch polarity, read per test:
     * `bnel $2,$0` PAST the `b` -> fall-through is the if BODY -> the guard is
       the positive `if (p == 0) return 1;`
     * `bnel $17,$2` PAST the arm -> if/else-if chain, cases AS WRITTEN, so
       `if (i == 2) {...} else {...}`; the constant 2 is rematerialised in the
       loop-back delay slot each iteration.
     * `bnel $17,$0` PAST the call -> `if (i == 0) LoaderQueueSeparatorGlobal_28afd0();`

   TWO MEASURED SPELLINGS, 8-arm sweep (build/wf34-var/n99080, one round trip):

   1. `extern s32 D_00482400[2];` -- SHORTER THAN THE TRUTH.  It is indexed
      0..2 so it is at least 12 bytes, and a gp extern declared LONGER than
      8 bytes leaves small data: the incomplete-array spelling
      `extern s32 D_00482400[];` cost a %hi/%lo pair per use (+3 words) where
      retail has `addiu $2,$28,%gp_rel(D_00482400)`.  `[1]` and the scalar
      `(&D_00482400)[i]` form are ONE identical object (095c62e3) and both
      still wrong; only `[2]` is right.

   2. LoadHandleArrayReset_28b160's SECOND PARAMETER IS `s16`.  Retail sign-extends `n` TWICE
      -- once into $5 for the call, once in place into $16 as the hoisted loop
      bound -- and mwcc will not emit two `dsll32/dsra32` pairs from two
      explicit `(s16)n` casts, it CSEs them.  An IMPLICIT conversion at the
      call plus an EXPLICIT `(s16)n` in the loop condition are the two
      constructs it keeps apart.  Measured INERT (all one object, ee0a8892):
      `s16 n` used bare, `n = (s16)n;` before the loop, and a separate
      `s16 m = (s16)n;` bound -- the loop-bound axis is a null; the CALLEE
      PROTOTYPE is the whole lever.  */

typedef struct Cfg99080 { u8 pad000[0x24C]; u8 m24C; } Cfg99080;
typedef struct Sys99080 { u8 pad00[0x20]; Cfg99080 *m20; } Sys99080;
typedef struct Elem99080 { u8 pad00[0x38]; } Elem99080;

extern Sys99080 *GetGameData_1fede0(void);
extern void LoadHandleArrayReset_28b160(void *, s16);
extern void LoadHandleRequestAlloc_28b3e0(void *, void *, s32, s32, void *, s32);
extern void LoadHandleRequestFile_28b550(void *, s32, s32, s32);
extern void LoaderQueueSeparatorGlobal_28afd0(void);

extern void *D_00482338;
extern Elem99080 *D_004823F8;
extern s32 D_004823FC;
extern s32 D_00482400[2];
extern s32 D_0048240C;
extern s32 D_0047EBA0;

s32 MenuMainResLoad_299080(void)
{
    Sys99080 *p;
    s32 n;
    s32 i;

    p = GetGameData_1fede0();
    if (p == 0) {
        return 1;
    }
    n = 3;
    if ((p->m20->m24C & 1) != 0) {
        n = 3;
    }
    LoadHandleArrayReset_28b160(D_004823F8, n);
    for (i = 0; i < (s16)n; i++) {
        if (i == 2) {
            LoadHandleRequestAlloc_28b3e0(&D_004823F8[i], &D_004823FC, D_00482400[i], 0,
                         D_00482338, 0);
        } else {
            LoadHandleRequestFile_28b550(&D_004823F8[i], D_00482400[i], 0, 0);
        }
        if (i == 0) {
            LoaderQueueSeparatorGlobal_28afd0();
        }
    }
    LoaderQueueSeparatorGlobal_28afd0();
    D_0048240C = 0;
    D_0047EBA0 = -1;
    return 0;
}
