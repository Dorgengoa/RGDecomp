#include "types.h"
/* insect 0x00516180 -- 480 bytes, 120 instructions.  Initialises a combat
 * record from its definition row. */

typedef struct Head {
    s16 f00;                        /* +0x00 */
} Head;

typedef struct Def {
    u8   pad00[4];
    s32  f04;                       /* +0x04 */
    Head *f08;                      /* +0x08 */
    s16  f0C;                       /* +0x0C */
    u8   b0 : 1;                    /* +0x0E */
    u8   b1 : 1;
    u8   b2 : 1;
    u8   b3 : 5;
    u8   pad0F[1];
    s16  f10;                       /* +0x10 */
    s16  f12;                       /* +0x12 */
    s16  f14;                       /* +0x14 */
    s16  f16;                       /* +0x16 */
    s16  f18;                       /* +0x18 */
    s16  f1A;                       /* +0x1A */
    s16  f1C[6];                    /* +0x1C */
} Def;

typedef struct Obj {
    u8   pad00[0x10];
    Def *f10;                       /* +0x10 */
    u8   pad14[4];
    s8   f18;                       /* +0x18 */
    u8   pad19[0x22 - 0x19];
    s16  f22;                       /* +0x22 */
    s16  f24;                       /* +0x24 */
    s8   f26;                       /* +0x26 */
    u8   pad27[1];
    s8   f28;                       /* +0x28 */
    u8   pad29[1];
    s8   f2A[6];                    /* +0x2A */
    u8   pad30[6];
    s8   f36;                       /* +0x36 */
    s8   f37;                       /* +0x37 */
    s8   f38;                       /* +0x38 */
    s8   f39;                       /* +0x39 */
    u8   pad3A[2];
    s8   f3C[7];                    /* +0x3C */
    s8   f43[9];                    /* +0x43 */
    s8   f4C;                       /* +0x4C */
    u8   pad4D[2];
    s8   f4F;                       /* +0x4F */
    s16  f50;                       /* +0x50 */
    u8   pad52[2];
    s32  f54;                       /* +0x54 */
    u8   pad58[4];
    s32  f5C;                       /* +0x5C */
    u8   pad60[8];
    s32  f68;                       /* +0x68 */
} Obj;

extern s32 func_133710(void);
extern void insect_InsectPieceSetMaxHp_512ec0(Obj *o, s16 v, s32 k);
extern void insect_InsectPieceSetItemDef_516580(Obj *o, Head *h);
extern void insect_InsectPieceSetStatus_5132d0(Obj *o, s32 k);

void insect_InsectPieceLoadFromStoryDef_516180(Obj *o, Def *s)
{
    s32 i;

    if (s == 0) {
        return;
    }
    o->f10 = s;
    o->f5C = s->f04;
    if (s->f10 >= 6) {
        o->f18 = 5;
        o->f22 = 0x2BC;
        o->f24 = 0x2BC;
    } else {
        o->f18 = s->f10;
        o->f22 = func_133710() % 60 + 20;
        o->f24 = 100;
    }
    insect_InsectPieceSetMaxHp_512ec0(o, s->f14, 1);
    o->f50 = s->f1A;
    o->f26 = s->f16;
    o->f28 = s->f18;
    for (i = 0; i < 6; i++) {
        o->f2A[i] = s->f1C[i];
    }
    o->f36 = s->f12;
    o->f37 = func_133710() % 30 + 50;
    o->f54 = s->f08->f00;
    insect_InsectPieceSetItemDef_516580(o, s->f08);
    for (i = 0; i < 7; i++) {
        o->f3C[i] = 0;
    }
    for (i = 0; i < 9; i++) {
        o->f43[i] = 0;
    }
    o->f4C = 0;
    if (o->f38 == 12) {
        o->f4C = o->f39 * 5 + 0x32;
    }
    o->f4F = 3;
    o->f68 = s->f0C;
    if (s->b0 != 0) {
        insect_InsectPieceSetStatus_5132d0(o, 0x1A);
    }
    if (s->b1 != 0) {
        insect_InsectPieceSetStatus_5132d0(o, 0x16);
    }
    if (s->b2 != 0) {
        insect_InsectPieceSetStatus_5132d0(o, 0x17);
    }
}
