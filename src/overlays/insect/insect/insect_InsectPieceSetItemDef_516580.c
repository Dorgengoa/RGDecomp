#include "types.h"
/* insect 0x00516580 -- 152 B / 38 words.
 * `beqz $16` past the whole body: `if (s != 0) { ... }`.
 * insect_InsectPieceItemDefGetSpecies_5166d0 takes three OUT parameters (its own listing opens with
 * `sw $3, 0x0($5)` / `sw $3, 0x0($6)` storing -1 through them), so the three
 * stack slots at 0x3C/0x38/0x34 are address-taken s32 locals -- which is why
 * 0x3C is RE-LOADED for the range test after already being stored as a byte
 * (insect-outparam-named-copy: an address-taken local is re-loaded at every
 * use).  mwcc allocates stack locals in REVERSE declaration order, so the one
 * passed as parameter two sits at the HIGHEST slot (0x3C) and is declared
 * FIRST -- the reverse order (c,b,a) put it at 0x34 and cost five words.
 * `addiu $3, $3, -0xF / sltiu $1, $3, 0x2` is the unsigned range form of a
 * two-value test on the first out value.
 * The `beql` past the arm carries a tail-duplicated `sw $16, 0xE0($17)`, so
 * that store is AFTER the if, not inside it. */

typedef struct Src {
    u8  pad00[0x0C];
    s32 m0C;                    /* +0x0C */
    u8  pad10[0x30 - 0x10];
    s32 m30;                    /* +0x30 */
} Src;

typedef struct Dst {
    u8   pad00[0x38];
    u8   m38;                   /* +0x38 */
    u8   m39;                   /* +0x39 */
    s16  m3A;                   /* +0x3A */
    u8   pad3C[0x60 - 0x3C];
    s32  m60;                   /* +0x60 */
    s32  m64;                   /* +0x64 */
    u8   pad68[0xE0 - 0x68];
    Src *mE0;                   /* +0xE0 */
} Dst;

extern void insect_InsectPieceItemDefGetSpecies_5166d0(Src *s, s32 *a, s32 *b, s32 *c);
extern void insect_InsectPieceApplySpeciesTable_515c20(Dst *d);
extern void insect_InsectPieceSetStatus_5132d0(Dst *d, s32 n);

void insect_InsectPieceSetItemDef_516580(Dst *d, Src *s)
{
    s32 a;
    s32 b;
    s32 c;

    if (s != 0) {
        insect_InsectPieceItemDefGetSpecies_5166d0(s, &a, &b, &c);
        d->m38 = a;
        d->m39 = b;
        d->m3A = c;
        insect_InsectPieceApplySpeciesTable_515c20(d);
        d->m60 = s->m0C;
        d->m64 = s->m30;
        if ((u32)(a - 0xF) < 2) {
            insect_InsectPieceSetStatus_5132d0(d, 0x20);
        }
        d->mE0 = s;
    }
}
