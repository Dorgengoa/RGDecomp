#include "types.h"
/* insect 0x00516620 -- 164 bytes / 41 words.  The DERIVED constructor: it runs
 * the 0x58-byte Slot base ctor (insect_InsectPieceStatsInit_513120, already byte-identical)
 * and then extends the same object out to 0xDC.
 *
 * The Slot declaration below is transcribed unchanged from
 * src/wf/insect/insect_InsectPieceStatsInit_513120.c -- the 0x2A/0x30 pair really is two
 * 6-byte arrays sharing one loop body, per insect-struct-overlap-declaration.
 *
 * Three things this unit measured, none of which was guessable:
 *
 *  1. `o->m70 = o->m71 = -1;` -- a CHAINED assignment emits its stores
 *     RIGHT-to-LEFT, which is the only way to get retail's `sb 0x71` BEFORE
 *     `sb 0x70`.  Same for `o->mC0 = o->mC4 = 0;` (`sw 0xC4` then `sw 0xC0`).
 *     Everything else is in plain source order.
 *
 *  2. `m90[3]` is f32, NOT s32.  Its clear loop is what materialises
 *     `mtc1 $0, $f0` in the loop PREHEADER; the loop body's own store is then
 *     peepholed back to the integer `sw $0, 0x90($3)`, and the four float
 *     stores AFTER the loop reuse the surviving $f0 as `swc1`.  Type the array
 *     s32 and mwcc folds all four tail stores to `sw $0` -- one word SHORT,
 *     and no spelling of the tail alone can recover it (measured: 4 chain
 *     forms, a named f32 local shared with the call arguments, volatile,
 *     static inline, -0.0f, an f64 round trip, and 486 pragmas).
 *
 *  3. insect_InsectPieceSetPos_5159b0 returns void, so `o->m6C = -1` in the jal delay slot
 *     is its own statement reusing the -1 already in $2, not a captured result.
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

typedef struct Unit {
    Slot base;                  /* +0x00 */
    s32  m58;                   /* +0x58 */
    s32  m5C;                   /* +0x5C */
    s32  m60;                   /* +0x60 */
    s32  m64;                   /* +0x64 */
    s32  m68;                   /* +0x68 */
    s16  m6C;                   /* +0x6C */
    s8   m6E;                   /* +0x6E */
    s8   m6F;                   /* +0x6F */
    s8   m70;                   /* +0x70 */
    s8   m71;                   /* +0x71 */
    u8   pad72[0x1E];           /* +0x72 */
    f32  m90[3];                /* +0x90 */
    u8   pad9C[0x24];           /* +0x9C */
    s32  mC0;                   /* +0xC0 */
    s32  mC4;                   /* +0xC4 */
    s32  mC8;                   /* +0xC8 */
    f32  mCC;                   /* +0xCC */
    f32  mD0;                   /* +0xD0 */
    f32  mD4;                   /* +0xD4 */
    f32  mD8;                   /* +0xD8 */
} Unit;                         /* sizeof 0xDC */

extern void insect_InsectPieceStatsInit_513120(Slot *o);
extern void insect_InsectPieceSetPos_5159b0(Unit *o, f32 x, f32 y, f32 z);

void insect_InsectPieceResetState_516620(Unit *o)
{
    s32 i;

    insect_InsectPieceStatsInit_513120(&o->base);
    o->m58 = 0;
    o->m70 = o->m71 = -1;
    o->m5C = 0;
    o->m60 = 0;
    o->m64 = 0;
    o->m68 = 0;
    o->m6E = 0;
    o->m6F = 0;
    o->m6C = -1;
    insect_InsectPieceSetPos_5159b0(o, 0.0f, 0.0f, 0.0f);
    o->mC0 = o->mC4 = 0;
    o->mC8 = 0;
    for (i = 0; i < 3; i++) {
        o->m90[i] = 0.0f;
    }
    o->mD8 = 0.0f;
    o->mCC = 0.0f;
    o->mD0 = 0.0f;
    o->mD4 = 0.0f;
}
