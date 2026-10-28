/* rgp:protos */
#define RGP_SELF_insect_InsectPieceStatsInit_513120 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00513120 -- 240 bytes.  The zero-init CONSTRUCTOR for the 0x58-byte
 * slot record whose field-by-field copy is insect_InsectPieceCopyStats_512fe0: a base-ctor
 * call, a long row of scalar clears, three counted loops and a final -1.
 *
 * `sw $0, 0x10($16)` is issued THREE times back to back.  mwcc does not
 * dead-store-eliminate repeated stores through a struct pointer, so those are
 * three source statements (a chained assignment), not three members -- the
 * same shape as insect_InsectBattleObjInit_50e810's `f5EA0[i] = 1; f5EA0[i] = -1;`.
 *
 * The 0x2A and 0x30 clears share ONE loop body (a single `addu $3, $16, $4`
 * feeding `sb 0x2A($3)` and `sb 0x30($3)`), so they are two array assignments
 * inside one `for`, not two loops -- cf. insect-struct-overlap-declaration.
 *
 * 0x18/0x19 and 0x52 are NOT written here; they stay padding.
 */

typedef struct Slot {
    u8  pad00[0x10];
    s32 m10;                    /* +0x10 */
    s16 m14;                    /* +0x14 */
    s16 m16;                    /* +0x16 */
    u8  pad18[2];
    s16 m1A;                    /* +0x1A */
    s16 m1C;                    /* +0x1C */
    s16 m1E;                    /* +0x1E */
    s16 m20;                    /* +0x20 */
    u16 m22;                    /* +0x22 */
    s16 m24;                    /* +0x24 */
    u8  m26;                    /* +0x26 */
    u8  m27;                    /* +0x27 */
    u8  m28;                    /* +0x28 */
    u8  m29;                    /* +0x29 */
    u8  m2A[6];                 /* +0x2A */
    u8  m30[6];                 /* +0x30 */
    s8  m36;                    /* +0x36 */
    s8  m37;                    /* +0x37 */
    s8  m38;                    /* +0x38 */
    s8  m39;                    /* +0x39 */
    s16 m3A;                    /* +0x3A */
    s8  m3C[7];                 /* +0x3C */
    s8  m43[9];                 /* +0x43 */
    s8  m4C;                    /* +0x4C */
    s8  m4D;                    /* +0x4D */
    s8  m4E;                    /* +0x4E */
    s8  m4F;                    /* +0x4F */
    s16 m50;                    /* +0x50 */
    u8  pad52[2];
    s32 m54;                    /* +0x54 */
} Slot;                         /* sizeof 0x58 */

/*rgp*/

void insect_InsectPieceStatsInit_513120(Slot *o)
{
    s32 i;

    insect_InsectPieceClearAllStatus_5133c0(o);
    o->m10 = 0;
    o->m10 = 0;
    o->m10 = 0;
    o->m14 = 0;
    o->m16 = 0;
    o->m1A = 0;
    o->m1C = 0;
    o->m1E = 0;
    o->m20 = 0;
    o->m22 = 0;
    o->m24 = 0;
    o->m26 = 0;
    o->m27 = 0;
    o->m28 = 0;
    o->m29 = 0;
    for (i = 0; i < 6; i++) {
        o->m2A[i] = 0;
        o->m30[i] = 0;
    }
    o->m36 = 0;
    o->m37 = 0;
    o->m38 = 0;
    o->m39 = 0;
    o->m3A = 0;
    for (i = 0; i < 7; i++) {
        o->m3C[i] = 0;
    }
    for (i = 0; i < 9; i++) {
        o->m43[i] = 0;
    }
    o->m4C = 0;
    o->m4D = 0;
    o->m4E = 0;
    o->m4F = 0;
    o->m50 = 0;
    o->m54 = -1;
}
