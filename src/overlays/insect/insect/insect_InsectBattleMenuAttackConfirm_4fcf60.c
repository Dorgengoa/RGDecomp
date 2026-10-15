#include "types.h"
/* insect 0x004FCF60 -- 1,296 bytes, 324 instructions, 47 calls, 13 conditional
 * branches, br/ins 0.040.  Same state-dispatch family; chain
 * 0x4B,0x4A,0x49,0x46,0x47,0x1D,3,1 REVERSED gives source order
 * 1,3,0x1D,0x47,0x46,0x49,0x4A,0x4B, which is the block layout, with
 * case 0x47 falling through into case 0x46 (its test is the PLAIN `beq`, the
 * fall-through partner's is the `beql`).
 *
 * `ori $2,$0,0xC397 / andi $5,$2,0xFFFF` in case 1 is a `u16` LOCAL holding the
 * widget id, not two constants: the mask is the local's type and it survives
 * the select.  `insect_InsectBoardGetPiece_4ee9a0`'s coordinate parameters are `s16` -- the
 * first call feeds them `lb` off an s8 field and the second narrows the s32
 * frame slots to `lh`, which is mwcc narrowing the load, not two prototypes.
 */

typedef struct Card { u8 pad00[8]; s8 f8; s8 f9; s8 fA; s8 fB; } Card;
typedef struct Slot { u8 pad00[0x5C]; s32 f5C; } Slot;

typedef struct Ins {
    u8    pad000[0x878];
    void *f878;                 /* +0x0878 */
    void *f87C;                 /* +0x087C */
    u8    pad880[0x4F90 - 0x880];
    u8    f4F90[0x2C];          /* +0x4F90 */
    u8    f4FBC;                /* +0x4FBC */
    u8    pad4FBD[0x5B24 - 0x4FBD];
    s32   f5B24;                /* +0x5B24 */
    Slot *f5B28;                /* +0x5B28 */
    u8    pad5B2C[0x5DA0 - 0x5B2C];
    s32   f5DA0;                /* +0x5DA0 */
    s32   f5DA4;                /* +0x5DA4 */
    u8    pad5DA8[0x5EF1 - 0x5DA8];
    u8    f5EF1;                /* +0x5EF1 */
} Ins;

extern const u8 D_00523FC0[];

extern s32   insect_InsectBoardGetPiece_4ee9a0(void *a, s16 x, s16 y);
extern void  insect_InsectBattleCursorUpdateDesc_4f4530(Ins *o, const u8 *t, s32 k);
extern s32   insect_InsectBattleGetStep_50d6a0(Ins *o, s32 k);
extern void  insect_InsectBattleSetStep_50d7a0(Ins *o, s32 a, s32 b, s32 c);
extern void  insect_InsectBattleSetState_50d8c0(Ins *o, s32 a, s32 b, s32 c);
extern s32   insect_InsectBattleTestFlag_50da40(Ins *o, s32 k);
extern void  insect_InsectBattleClearFlag_50da90(Ins *o, s32 k);
extern void  insect_InsectBattleConfirmDialogOpen_50eaf0(s32 a, s32 b, void *c, s32 d);
extern void  insect_InsectCursorSetGetCurCell_511a90(void *a, s32 *x, s32 *y);
extern void  insect_InsectCursorSetGetCell_511a40(void *a, s32 k, s32 *x, s32 *y);
extern void  insect_InsectCursorSetPopPage_511ca0(void *a);
extern Card *insect_InsectCursorSetFindPage_511e60(void *a, s32 k);

extern void func_28F510(void *h, u16 id, s32 a, s32 b);
extern s32  func_290460(void *h, s32 id);
extern void func_290690(void *h, s32 id, f32 a, f32 b, f32 c);
extern f32  func_290770(void *h, s32 id);
extern void func_392B20(void *g, s32 w, s32 v);

void insect_InsectBattleMenuAttackConfirm_4fcf60(Ins *o)
{
    s32 x6C;
    s32 x68;
    s32 x64;
    s32 x60;
    s32 x5C;
    s32 x58;
    void *g;
    void *p16;
    void *rec;
    Card *c;
    Card *d;
    Slot *sl;
    s32 hit;
    s32 ia;
    s32 ib;
    u16 id;
    u8 b;

    c = insect_InsectCursorSetFindPage_511e60(o->f4F90, 2);
    rec = (u8 *)o + 0x4960;
    x6C = c->f8;
    x68 = c->f9;
    hit = insect_InsectBoardGetPiece_4ee9a0(rec, x6C, x68);
    g = (u8 *)o + 0x5054;
    p16 = (u8 *)o + 0x506C;
    if (hit == 0) {
        insect_InsectCursorSetGetCell_511a40(o->f4F90, 0xA, &x6C, &x68);
        hit = insect_InsectBoardGetPiece_4ee9a0(rec, x6C, x68);
    }
    if (hit != 0) {
        switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
        case 1:
            func_290690(o->f878, 0x755F, 0.0f, 0.125f, -1.0f);
            func_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
            insect_InsectBattleSetStep_50d7a0(o, 3, 2, -1);
            id = 0xC397;
            sl = o->f5B28;
            if (o->f5EF1 != 0) {
                id = 0xC39E;
            }
            func_28F510(o->f87C, id, sl->f5C, 0);
            break;
        case 3:
            if (func_290770(o->f87C, 0xC37E) <= 0.0f) {
                insect_InsectBattleSetStep_50d7a0(o, 0x1B, 0, -1);
                insect_InsectBattleSetStep_50d7a0(o, 0xA, 2, -1);
            }
            break;
        case 0x1D:
            func_290690(o->f878, 0x755F, 1.0f, 0.125f, -1.0f);
            func_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
            insect_InsectBattleSetStep_50d7a0(o, 0xA, 2, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x1D, 0, -1);
            break;
        case 0x47:
            func_290690(o->f87C, 0xC378, 1.0f, 0.125f, -1.0f);
            func_290690(o->f87C, 0xC37E, 1.0f, 0.125f, -1.0f);
            insect_InsectBattleConfirmDialogOpen_50eaf0(o->f5DA0, o->f5DA4, p16, 0xF);
            insect_InsectBattleSetStep_50d7a0(o, 0x46, 2, -1);
            /* fallthrough */
        case 0x46:
            insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00523FC0, 1);
            o->f4FBC = o->f4FBC & 0xFD;
            insect_InsectBattleSetStep_50d7a0(o, 0x49, 2, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x49, 0, -1);
            break;
        case 0x49:
            insect_InsectCursorSetGetCurCell_511a90(o->f4F90, &x64, &x60);
            insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00523FC0, 0);
            b = !(x64 != 0);
            func_392B20(g, func_290460(o->f87C, 0xC37B), b);
            func_392B20(g, func_290460(o->f87C, 0xC37C), x64);
            break;
        case 0x4A:
            func_290690(o->f87C, 0xC378, 0.0f, 0.125f, -1.0f);
            func_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
            insect_InsectCursorSetPopPage_511ca0(o->f4F90);
            insect_InsectBattleSetStep_50d7a0(o, 0x1C, 0, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0xA, 2, -1);
            break;
        case 0x4B:
            insect_InsectCursorSetGetCell_511a40(o->f4F90, 0xB, &x5C, &x58);
            o->f5B24 = insect_InsectBoardGetPiece_4ee9a0(rec, x5C, x58);
            func_290690(o->f87C, 0xC378, 0.0f, 0.125f, -1.0f);
            func_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
            insect_InsectBattleSetState_50d8c0(o, 2, 3, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x51, 2, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x51, 0, -1);
            insect_InsectBattleClearFlag_50da90(o, 0x22);
            ia = 2;
            ib = 0xA;
            if (insect_InsectBattleTestFlag_50da40(o, 0x3D) != 0) {
                insect_InsectBattleClearFlag_50da90(o, 0x3D);
                ib = 2;
                ia = 0xA;
            }
            c = insect_InsectCursorSetFindPage_511e60(o->f4F90, ia);
            d = insect_InsectCursorSetFindPage_511e60(o->f4F90, ib);
            d->f8 = c->f8;
            d->f9 = c->f9;
            d->fA = c->fA;
            d->fB = c->fB;
            insect_InsectBattleClearFlag_50da90(o, 0x42);
            break;
        }
    }
}
