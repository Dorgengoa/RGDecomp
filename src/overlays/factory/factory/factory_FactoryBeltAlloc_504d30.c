#include "types.h"

/* factory.bin overlay, 0x00504D30 -- allocate a 6-byte-element vertex list.
 *
 * Struct is the seed's (src/wf/factory/factory_FactoryBeltStart_504cc0.c) verbatim.
 *
 * Branch polarity, read per test:
 *   blezl $17 -> exit, `daddu $2,$0,$0` in the delay slot  => if (n <= 0) return 0;
 *   bnel  $16,$0 -> PAST the zero-return                   => if (!heap) return 0;
 *   bnez  $2 -> PAST the zero-return, `sw $2,0x0($18)`
 *               in the delay slot                          => named local p,
 *                                                             stored, then tested
 * n*6 is `sll 1; addu; sll 1`.
 *
 * MEASURED (build/wv35_variants.py, 6 spellings in one round trip): the two
 * guards must be ONE `||` join.  Two separate `if`s each get their own packed
 * `b exit / move v0,zero` pair and the function is ONE WORD LONG (0x84 vs
 * 0x80): the join gives mwcc a SHARED return-0 block, whose incoming edge
 * stops the `move` folding into the `b`'s delay slot (retail's
 * `daddu $2,$0,$0 / b / nop` at 0x00504D64) and lets the FIRST test become a
 * branch-likely straight to the epilogue with the zero TAIL-DUPLICATED into
 * its delay slot (`blezl $17, .L00504D98 / daddu $2,$0,$0`).
 * `n < 1 ||` and the brace-less form are the SAME object (sha1 2f33541c).
 * Measured misses: `if (n > 0 && heap != NULL) {...} return 0;` -> 0x78,
 * `if (n > 0) { ... } return 0;` -> 0x7C,
 * `||` join with the p-test inverted into `if (p != NULL) {...} return 0;`
 * -> right length, 5 bad words.
 */

typedef struct FacVert {
    s16 x;      /* 0x0 */
    s16 y;      /* 0x2 */
    s16 z;      /* 0x4 */
} FacVert;

typedef struct FacVertList {
    FacVert *buf;   /* 0x0 */
    s16      cap;   /* 0x4 */
    s16      count; /* 0x6 */
    s16      f8;    /* 0x8 */
} FacVertList;

extern void  factory_FactoryBeltReset_504dc0(FacVertList *l);
extern void *func_14E1B0(s32 size, void *heap);

s32 factory_FactoryBeltAlloc_504d30(FacVertList *l, s32 n, void *heap)
{
    FacVert *p;

    factory_FactoryBeltReset_504dc0(l);

    if (n <= 0 || heap == NULL) {
        return 0;
    }

    p = (FacVert *)func_14E1B0(n * 6, heap);
    l->buf = p;
    if (p == NULL) {
        return 0;
    }

    l->cap = n;
    return 1;
}
