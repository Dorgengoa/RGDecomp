#include "types.h"
/* insect 0x004F6B80 -- 412 bytes.  Two nested fixed loops over the 0x994-byte
 * per-side blocks and their five slots; the qword at +0x180 is copied whole
 * into a 16-byte local, both live lanes are scaled and then biased, so each
 * lane is TWO statements and stores twice. */

typedef union Vec {
    s64 q[2];
    struct {
        f32 x;                      /* +0x00 */
        f32 y;                      /* +0x04 */
        f32 z;                      /* +0x08 */
        f32 w;                      /* +0x0C */
    } f;
} __attribute__((aligned(16))) Vec;

typedef struct Hit {
    u8  pad00[0x180];
    Vec f180;                       /* +0x180 */
} Hit;

typedef struct Ent {
    u8  pad00[0x6C];
    s16 f6C;                        /* +0x6C */
    u8  pad6E[0x71 - 0x6E];
    s8  f71;                        /* +0x71 */
} Ent;

typedef struct Ins {
    u8    pad0000[0x870];
    void *f870;                     /* +0x0870 */
} Ins;

extern void *func_141B00(void *h);
extern Hit  *func_1C4A90(void *h, s32 n);
extern void  insect_InsectBattleCellPrimSetup_4f7400(Ins *o, void *h, void *c);
extern Ent  *insect_InsectTeamGetPiece_5138d0(u8 *p, s32 i);
extern s32   insect_InsectPieceTestStatus_513280(Ent *e, s32 k);
extern s32   insect_InsectBoardFindPiece_4ee190(u8 *p, Ent *e, s32 *x, s32 *y);
extern void  insect_InsectBattleDrawCellQuad_4f6d30(Ins *o, void *h, s32 m, f32 x, f32 z,
                                 f32 a, f32 b);
extern void  insect_InsectBattleCellPrimEnd_4f6d20(Ins *o, void *a, void *h);

void insect_InsectBattleDrawPieceCells_4f6b80(Ins *o, void *a, void *c)
{
    Vec   v;
    s32   x;
    s32   y;
    u8   *w;
    u8   *p;
    void *h;
    s32   m;
    s32   j;
    s32   i;
    Ent  *e;

    w = (u8 *)o + 0x4960;
    h = func_141B00(a);
    insect_InsectBattleCellPrimSetup_4f7400(o, h, c);
    for (j = 0; j < 2; j++) {
        p = (u8 *)o + j * 0x994 + 0x35F8;
        for (i = 0; i < 5; i++) {
            e = insect_InsectTeamGetPiece_5138d0(p, i);
            if (insect_InsectPieceTestStatus_513280(e, 0x1B) != 0) {
                m = 4;
                if (e->f71 == 1) {
                    m = 5;
                }
                if (insect_InsectBoardFindPiece_4ee190(w, e, &x, &y) == 1) {
                    v = func_1C4A90(o->f870, e->f6C)->f180;
                    v.f.x = v.f.x / 4.0f;
                    v.f.z = v.f.z / 4.0f;
                    v.f.x = v.f.x + 2.0f;
                    v.f.z = v.f.z + 3.0f;
                    insect_InsectBattleDrawCellQuad_4f6d30(o, h, m, v.f.x, v.f.z, 0.0f, 1.0f);
                }
            }
        }
    }
    insect_InsectBattleCellPrimEnd_4f6d20(o, a, h);
}
