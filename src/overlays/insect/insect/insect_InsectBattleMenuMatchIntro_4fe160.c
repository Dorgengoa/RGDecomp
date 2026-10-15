#include "types.h"
/* insect 0x004FE160 -- 1,344 bytes, 336 instructions, 42 calls, 22 conditional
 * branches.  The insect_InsectBattleGetStep_50d6a0(o, 2) state-dispatch family again; the
 * header of the family is insect_InsectBattleMenuTeamSelect_5004f0.c and the closest sibling is
 * insect_InsectBattleMenuPieceCmd_501810.c.
 *
 * Compare chain 9, 0x1D, 0x15, 1 -- REVERSED -- and the block ADDRESSES run
 * 0x4FE1DC (1), 0x4FE45C (0x15), 0x4FE49C (0x1D), 0x4FE4E8 (9), i.e. that same
 * order forwards.  So the source case order is 1, 0x15, 0x1D, 9 with case 1
 * FALLING THROUGH into case 0x15 (the `beql` for 0x15 carries the arm's own
 * `lw $4,0x878($18)` in its delay slot and case 1's last call is immediately
 * above the label).
 *
 * D_00480F08 / D_00480F10 are MAIN-image small data (gp = 0x00485170) read with
 * `lhu` at a stride of FOUR -- `[i * 2]` on a `u16` array, exactly as
 * insect_InsectBattleMenuTeamSelect_5004f0 does with D_00480EF0 / D_00480F00.
 * D_00480F18 / D_00480F1C are the gp float pair copied into the case-9 id
 * table as ONE 8-byte struct copy through a cast (`lwc1`/`swc1`).
 */

typedef struct V2 { f32 x, y; } V2;

typedef struct Panel { u8 pad00[0x28]; s16 f28; } Panel;

typedef struct Sub { u8 pad00[0x8]; s16 f08; } Sub;

typedef struct Widget {
    u8     pad00[0x20];
    Panel *f20;                 /* +0x20 */
} Widget;

typedef struct Ins {
    u8    pad000[0x878];
    void *f878;                 /* +0x0878 */
    u8    pad87C[0x35F8 - 0x87C];
    u8    f35F8[0x3F8C - 0x35F8];   /* +0x35F8 */
    u8    f3F8C[0x4F90 - 0x3F8C];   /* +0x3F8C */
    u8    f4F90[0x2C];              /* +0x4F90 */
    u8    f4FBC;                    /* +0x4FBC */
    u8    pad4FBD[0x5054 - 0x4FBD];
    u8    f5054[0x506C - 0x5054];   /* +0x5054 */
    u8    f506C[0x5DA0 - 0x506C];   /* +0x506C */
    s32   f5DA0;                    /* +0x5DA0 */
    s32   f5DA4;                    /* +0x5DA4 */
    u8    pad5DA8[0x5EF8 - 0x5DA8];
    s32   f5EF8;                    /* +0x5EF8 */
} Ins;

extern u16 D_00480F08[4];       /* 8 bytes: at the small-data threshold */
extern u16 D_00480F10[4];
extern f32 D_00480F18;
extern f32 D_00480F1C;

extern void  insect_InsectCursorSetGetCell_511a40(void *a, s32 k, s32 *x, s32 *y);
extern s32   insect_InsectBattleGetStep_50d6a0(Ins *o, s32 k);
extern void  insect_InsectBattleSetStep_50d7a0(Ins *o, s32 a, s32 b, s32 c);
extern s32   insect_InsectBattleTestFlag_50da40(Ins *o, s32 k);
extern void  insect_InsectBattleSetFlag_50dad0(Ins *o, s32 k);
extern const char *insect_InsectTeamGetName_5138b0(void *a);
extern void *insect_InsectTeamGetPiece_5138d0(void *a, s32 i);
extern s32   insect_InsectMsgTextWidth_512ab0(void *p, const void *s, s32 k);
extern s32   insect_InsectPieceIsKing_514b00(void *p);

extern void    func_28F510(void *h, s32 id, const char *s, s32 i);
extern void    func_28F5D0(void *h, s32 id, s32 a, s32 b, s32 c);
extern void    func_290010(void *h, s32 id, s32 a, s32 b);
extern Widget *func_290460(void *h, s32 id);
extern void    func_290690(void *h, s32 id, f32 a, f32 b, f32 c);
extern void    func_2907A0(void *h, s32 id, f32 v);
extern s32     func_290D30(void *h, s32 id);
extern void    func_290F50(void *h, s32 id, s32 a, s32 b, s32 c, f32 t);
extern void    func_290F60(void *h, s32 id, s32 a, s32 b);
extern void    func_392A20(void *g, void *w, s32 a);
extern void    func_393AC0(void *g, void *w, s32 a, s32 b, s32 c);

void insect_InsectBattleMenuMatchIntro_4fe160(Ins *o)
{
    s32    x7C;
    s32    x78;
    s8     b74[2];
    void  *g68[2];
    u16    v60[4];
    void  *g;
    u8    *q;
    u32    c;
    Panel *p;
    Sub   *sp;
    s32    n;
    s32    i;
    s32    j;

    insect_InsectCursorSetGetCell_511a40(o->f4F90, 8, &x7C, &x78);
    g = o->f5054;

    switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
    case 1:
        func_2907A0(o->f878, 0x755B, 0.0f);
        func_290690(o->f878, 0x755B, 1.0f, 0.125f, -1.0f);
        func_393AC0(g, func_290460(o->f878, 0x7569), 0xA0, 0x24, 3);
        func_393AC0(g, func_290460(o->f878, 0x756A), 0xA0, 0x24, 2);
        func_392A20(g, func_290460(o->f878, 0x756B), 0xA0);
        func_392A20(g, func_290460(o->f878, 0x756C), 0xA0);
        q = (u8 *)g68;
        c = 8;
        if (q != 0) {
            do {
                *q = 0;
                c -= 1;
                q += 1;
            } while (c != 0);
        }
        g68[0] = o->f35F8;
        g68[1] = o->f3F8C;
        i = 0;
        do {
            n = insect_InsectMsgTextWidth_512ab0(o->f506C, insect_InsectTeamGetName_5138b0(g68[i]), 2);
            func_28F510(o->f878, D_00480F08[i * 2],
                        insect_InsectTeamGetName_5138b0(g68[i]), 0);
            func_28F5D0(o->f878, D_00480F08[i * 2], (0xA0 - n) / 2, 8, 0);
            j = 0;
            do {
                if (insect_InsectPieceIsKing_514b00(insect_InsectTeamGetPiece_5138d0(g68[i], j)) != 0) {
                    func_290F60(o->f878, D_00480F10[i + i],
                                j * 0x1F + 0xA, 0x1A);
                }
                j++;
            } while (j < 5);
            i++;
        } while (i < 2);
        func_290F60(o->f878, 0x755B, o->f5DA0 + 0x17A, (o->f5DA4 - 0x40) / 2);
        func_290F50(o->f878, 0x755B, (o->f5DA0 - 0x17A) / 2,
                    (o->f5DA4 - 0x40) / 2, 0, 0.5f);
        func_290F60(o->f878, 0x7566, (o->f5DA0 - 0x88) / 2, 0xC);
        insect_InsectBattleSetStep_50d7a0(o, 0x15, 2, -1);
        /* fallthrough */
    case 0x15:
        func_290010(o->f878, 0x755B, 1, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 2, -1);
        insect_InsectBattleSetStep_50d7a0(o, 2, 0, -1);
        break;
    case 0x1D:
        func_290F50(o->f878, 0x755B, -0x17A, (o->f5DA4 - 0x40) / 2, 0, 0.5f);
        insect_InsectBattleSetStep_50d7a0(o, 9, 2, -1);
        break;
    case 9:
        if (func_290D30(o->f878, 0x755B) == 0) {
            func_2907A0(o->f878, 0x7565, 0.0f);
            func_290690(o->f878, 0x7565, 1.0f, 0.125f, -1.0f);
            func_290010(o->f878, 0x7565, 1, -1);
            if (insect_InsectBattleTestFlag_50da40(o, 0x38) == 0) {
                func_290010(o->f878, 0x758A, 0, -1);
                func_290010(o->f878, 0x758B, 0, -1);
            }
            q = (u8 *)b74;
            c = 2;
            if (q != 0) {
                do {
                    *q = 0;
                    c -= 1;
                    q += 1;
                } while (c != 0);
            }
            b74[0] = insect_InsectBattleTestFlag_50da40(o, 0);
            b74[1] = insect_InsectBattleTestFlag_50da40(o, 1);
            *(V2 *)&v60[0] = *(V2 *)&D_00480F18;
            i = 0;
            do {
                p = func_290460(o->f878, v60[i * 2])->f20;
                p->f28 = 0x1C;
                sp = (Sub *)((u8 *)p + 0x20);
                if (b74[i] != 0) {
                    sp->f08 = 0x54;
                } else if ((o->f4FBC & (4 << i)) != 0) {
                    sp->f08 = 0x38;
                }
                i++;
            } while (i < 2);
            insect_InsectBattleSetStep_50d7a0(o, 0xA, 2, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0xF, 0, -1);
            insect_InsectBattleSetFlag_50dad0(o, 0x42);
            o->f5EF8 = 3;
        }
        break;
    }
}
