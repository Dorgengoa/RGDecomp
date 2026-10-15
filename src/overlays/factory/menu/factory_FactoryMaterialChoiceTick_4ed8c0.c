#include "types.h"

#pragma opt_dead_assignments off

/* factory.bin overlay, 0x004ED8C0 -- 512 B / 128 words, 4 branches, 12 calls.
 * EPILOGUE TAIL-MERGE family (scripts/f_tmerge.py), lane fy03.
 *
 * PLAIN-IF cell of lane fy01's family key.  The `b .L004EDAA8` at 004EDA78 has
 * a plain `nop` in its delay slot (it jumps OVER the else-arm, it is not the
 * tail-merge `b`); the tail-merge is the guard `beql $16,$0,.L004EDAAC` whose
 * ANNULLED slot holds `ld $31,0x20($29)` -- i.e. the second `ld $31` is the
 * duplicated first instruction of the shared tail, and there is ONE trailing
 * `return 1`.
 *
 * * `bnel $17,$2,.L004EDA80` PAST the arm with the else's own `addiu $2,$0,2`
 *   annulled = an if/else-if CHAIN, case order AS WRITTEN (1 then 2).
 * * The two calls whose results are compared are NAMED locals: `func_28E170`
 *   returns s32 into $17 and `func_28EC60` a pointer into $16, both
 *   callee-saved because both are live across the following calls.
 * * `D_00484A58` is re-read at every use (eleven `lw ..,-0x718($28)`); the one
 *   read that serves `->f40`, `->f0A` and `->f0C` together is a single source
 *   statement with no call between the three.
 * * `sll/addu` chains are `x * 44 + 7` and `y * 50 + 0x4A` on `s16` fields.
 *
 * !! `#pragma opt_dead_assignments off` IS THE UNIT.  Without it the schedule
 * around the func_290F60/func_2905B0 pair is 13 words wrong at the right
 * length, and TWENTY-NINE source spellings (four ways of naming the ->f40
 * handle x six ways of naming/casting the u16 id) are INERT -- 24 of the 29
 * produce an object with the BASELINE's sha1.  With the pragma the residue
 * falls to 3 (the whole func_2905B0 cluster closes by itself) and the
 * previously-inert `w = D_00484A58->f40;` local becomes LIVE and closes the
 * last three: retail issues `lw $4,0x40($2)` BEFORE the two `lh`, which is the
 * separate assignment statement that -O4's dead-assignment pass folds away.
 * Five placements of that local (before `n`, after `n`, after `r`, with px/py
 * temps, and read before the ->f06 store) all give the SAME byte-identical
 * object; `volatile` on it is 2 words long.  Nine other pragmas were measured
 * here: opt_lifetimes/opt_unroll_loops/global_optimizer/opt_pointer_analysis/
 * opt_partial_redundancy/opt_loop_invariants/optimization_level 3/usefloatacc/
 * opt_constnonchanging/scheduling/opt_strength_reduction are all INERT, and
 * opt_propagation off (+2), opt_common_subs off (+6) and peephole off (+8)
 * are long.
 * * `andi $5,..,0xFFFF` on the computed ids means func_2905B0/func_2904E0 take
 *   a `u16` id; the two constant ids (0x67) get a bare `addiu`.
 * * `-0x7C6C`/`-0x7E14`/`-0x7C68` are `D_0047D504`/`D_0047D35C`/`D_0047D508`
 *   in mwcc's .lit4 pool; 1.0f and -1.0f come from `lui`+`mtc1`.
 * * `D_004B2570` is outside the gp window; `extern const u8 []` gives the
 *   `lui 0x4B` / `addiu 0x2570` pair.
 */

typedef struct Node {
    u8  pad00[0x12];
    s16 f12;                                    /* +0x12 */
} Node;

typedef struct View {
    u8    pad00[0x6];
    s16   f06;                                  /* +0x06 */
    u8    pad08[0x2];
    s16   f0A;                                  /* +0x0A */
    s16   f0C;                                  /* +0x0C */
    u8    pad0E[0x32];
    void *f40;                                  /* +0x40 */
    void *f44;                                  /* +0x44 */
    void *f48;                                  /* +0x48 */
} View;

extern View    *D_00484A58;                     /* _gp - 0x718  */
extern f32      D_0047D35C;                     /* _gp - 0x7E14 */
extern f32      D_0047D504;                     /* _gp - 0x7C6C */
extern f32      D_0047D508;                     /* _gp - 0x7C68 */
extern const u8 D_004B2570[];

extern void  factory_FactoryMaterialCursorBob_4f3a70(View *v, s32 a, s32 b);
extern s32   func_28E170(const void *a, const void *b, s32 c, s32 d);
extern void  func_28EA90(void *ctx, s32 id, s32 a);
extern Node *func_28EC60(void *ctx);
extern void  func_28EDE0(void *ctx, s32 id, s32 a);
extern void  func_2904E0(void *w, u16 id, f32 a, f32 b, f32 c, f32 d, f32 e);
extern void  func_2905B0(void *w, u16 id, f32 a, f32 b, f32 c, f32 d);
extern void  func_290690(void *w, s32 id, f32 a, f32 b, f32 c);
extern void  func_290F60(void *w, s32 id, s32 x, s32 y);

s32 factory_FactoryMaterialChoiceTick_4ed8c0(s32 unused, s32 start)
{
    Node *n;
    void *w;
    s32   r;

    if (start != 0) {
        func_28EA90(D_00484A58->f44, 0x8926, 0);
        factory_FactoryMaterialCursorBob_4f3a70(D_00484A58, 1, 1);
        func_290690(D_00484A58->f40, 0x76, 1.0f, D_0047D504, -1.0f);
    }
    r = func_28E170(D_00484A58->f44, D_004B2570, 0, 0);
    n = func_28EC60(D_00484A58->f44);
    if (r == 1) {
        if (n != 0) {
            D_00484A58->f06 = n->f12;
            w = D_00484A58->f40;
            func_290F60(w, 0x77, D_00484A58->f0A * 44 + 7,
                        D_00484A58->f0C * 50 + 0x4A);
            func_2905B0(D_00484A58->f40, n->f12 + 0x72, D_0047D35C, D_0047D35C,
                        D_0047D35C, -1.0f);
            func_2904E0(D_00484A58->f40, n->f12 + 0x72, 1.0f, 1.0f, 1.0f, -1.0f,
                        D_0047D508);
            func_2905B0(D_00484A58->f40, 0x67, D_0047D35C, D_0047D35C,
                        D_0047D35C, -1.0f);
            func_2904E0(D_00484A58->f40, 0x67, 1.0f, 1.0f, 1.0f, -1.0f,
                        D_0047D508);
            func_28EDE0(D_00484A58->f48, 0x8994, 0);
        }
    } else if (r == 2) {
        D_00484A58->f06 = -1;
        func_28EDE0(D_00484A58->f48, 0x8994, 0);
    }
    return 1;
}
