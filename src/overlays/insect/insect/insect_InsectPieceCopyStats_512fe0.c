#include "types.h"
/* insect 0x00512FE0 -- 316 bytes.  A field-by-field COPY of one 0x58-byte slot
 * record into another, guarded on the source pointer.
 *
 * `beqz $17, <epilogue>` with the whole body FALLING THROUGH is the source's
 * `if (src != NULL) { ... }` body -- main-pass32-spellings, not an early
 * return: there is one exit and it restores the frame once.
 *
 * Every copy here is an INTERLEAVED load/store pair (`lb 0x36 / sb 0x36`,
 * `lb 0x37 / sb 0x37`, ...), so by main-pass34-substructs section 1 they are
 * N separate member assignments, NOT a sub-struct copy.  Nothing in this unit
 * batches loads before stores.
 *
 * ACCESS WIDTHS come off the listing per field: 0x22 is `lhu` (u16) while the
 * adjacent 0x24 is `lh` (s16), and the store order is 0x24 BEFORE 0x22, which
 * is the source order.  0x26/0x28 are `lbu` (u8); 0x18, 0x36..0x39, 0x3C[],
 * 0x43[], 0x4C, 0x4F are `lb` (s8).
 *
 * The three loops index off the RECORD BASE (`addu $3, $17, $6` then
 * `lb $5, 0x3C($3)`), which is the plain array-member spelling.
 */

typedef struct Slot {
    u8  pad00[0x18];
    s8  m18;                    /* +0x18 */
    u8  pad19;
    s16 m1A;                    /* +0x1A */
    s16 m1C;                    /* +0x1C */
    s16 m1E;                    /* +0x1E */
    s16 m20;                    /* +0x20 */
    u16 m22;                    /* +0x22 */
    s16 m24;                    /* +0x24 */
    u8  m26;                    /* +0x26 */
    u8  pad27;
    u8  m28;                    /* +0x28 */
    u8  pad29;
    u8  m2A[6];                 /* +0x2A */
    u8  pad30[0x36 - 0x30];
    s8  m36;                    /* +0x36 */
    s8  m37;                    /* +0x37 */
    s8  m38;                    /* +0x38 */
    s8  m39;                    /* +0x39 */
    s16 m3A;                    /* +0x3A */
    s8  m3C[7];                 /* +0x3C */
    s8  m43[9];                 /* +0x43 */
    s8  m4C;                    /* +0x4C */
    u8  pad4D[2];
    s8  m4F;                    /* +0x4F */
    s16 m50;                    /* +0x50 */
    u8  pad52[2];
    s32 m54;                    /* +0x54 */
} Slot;                         /* sizeof 0x58 */

extern void insect_InsectPieceCopyStatus_513210(Slot *dst, Slot *src);
extern void insect_InsectPieceSetMaxHp_512ec0(Slot *p, s16 v, s32 f);
extern s32  insect_InsectPieceGetStat_512e20(Slot *p, s32 i, s32 f);

void insect_InsectPieceCopyStats_512fe0(Slot *dst, Slot *src)
{
    s32 i;

    if (src != NULL) {
        insect_InsectPieceCopyStatus_513210(dst, src);
        dst->m18 = src->m18;
        insect_InsectPieceSetMaxHp_512ec0(dst, src->m1A, 1);
        insect_InsectPieceSetMaxHp_512ec0(dst, src->m1E, 0);
        dst->m24 = src->m24;
        dst->m22 = src->m22;
        dst->m26 = src->m26;
        dst->m28 = src->m28;
        for (i = 0; i < 6; i++) {
            dst->m2A[i] = insect_InsectPieceGetStat_512e20(src, i, 1);
        }
        dst->m36 = src->m36;
        dst->m37 = src->m37;
        dst->m38 = src->m38;
        dst->m39 = src->m39;
        dst->m3A = src->m3A;
        for (i = 0; i < 7; i++) {
            dst->m3C[i] = src->m3C[i];
        }
        for (i = 0; i < 9; i++) {
            dst->m43[i] = src->m43[i];
        }
        dst->m4C = src->m4C;
        dst->m4F = src->m4F;
        dst->m50 = src->m50;
        dst->m54 = src->m54;
    }
}
