#include "types.h"
/* insect 0x004F4FE0 -- 696 bytes, 174 instructions, 29 calls.
 * Draws every live slot entry through a display handle.  The 16-byte clear at
 * $29+0xC0 is the same written-out `sb` do-while as insect_InsectBattleCamTargetToCell_4f2ff0.
 */

typedef struct Ent {
    u8  pad00[0x6C];
    s16 f6C;                        /* +0x6C */
} Ent;

typedef struct Slot {
    u8 pad00[0x994];
} Slot;

typedef struct Obj {
    u8   pad00[0xC0];
    s32  fC0;                       /* +0xC0 */
    u8   padC4[0x870 - 0xC4];
    s32  f870;                      /* +0x870 */
    u8   pad874[0x35F8 - 0x874];
    Slot f35F8[2];                  /* +0x35F8 */
    u8   pad4920[0x5D90 - 0x4920];
    f32  f5D90;                     /* +0x5D90 */
} Obj;

extern f32   func_128FD0(f32 x);
extern f32   func_128D30(f32 x);
extern void  func_1418C0(s32 h, s32 k, f32 v);
extern s32   func_141B00(s32 h);
extern void  func_141A20(s32 h);
extern void  func_13E500(s32 h, s32 a);
extern void  func_13E4F0(s32 h, s32 a);
extern void  func_13E4C0(s32 h, s32 a, s32 b);
extern void  func_13E4D0(s32 h, s32 a);
extern void  func_13E460(s32 h, s32 a);
extern void  func_13E3B0(s32 h, s32 a);
extern void  func_13E3D0(s32 h, s32 a);
extern void  func_13E390(s32 h, s32 a);
extern void  func_13E450(s32 h, s32 a);
extern void  func_13E430(s32 h, s32 a);
extern void  func_13E2F0(s32 h, s32 a);
extern void  func_13E400(s32 h, s32 a);
extern void  func_13E3E0(s32 h, s32 a);
extern Ent  *insect_InsectTeamGetPiece_5138d0(Slot *s, s32 j);
extern s32   insect_InsectPieceIsInPlay_5149e0(Ent *e);
extern s32   insect_InsectPieceIsDizzy_514c10(Ent *e);
extern s32   func_1C4A90(s32 h, s16 k);
extern void  func_1ADEC0(s32 t, s32 z, f32 *p);
extern void  insect_InsectBattleCalcQuadCorners_4f47a0(Obj *o, f32 *a, f32 *b, f32 *c, f32 *d,
                                 f32 *e, s32 g,
                                 f32 p, f32 q, s32 i, f32 r, f32 s, f32 t, f32 u);
extern void  insect_InsectBattleDrawStarSprite_4f4e10(Obj *o, s32 h, f32 *p);

void insect_InsectBattleDrawDizzyStars_4f4fe0(Obj *o)
{
    f32  v0[4];
    f32  v1[4];
    f32  v2[4];
    f32  v3[4];
    f32  v4[4];
    s32  h;
    s32  i;
    Slot *sl;
    s32  j;
    Ent *e;
    s32  t;
    u8  *p;
    u32  n;
    f32  ang;
    f32  cs;
    f32  sn;

    ang = (3.1415927f * o->f5D90) / 180.0f;
    cs = func_128FD0(ang);
    sn = -func_128D30(ang);
    func_1418C0(o->fC0, 0x2A6, 1.0f);
    h = func_141B00(o->fC0);
    func_13E500(h, 1);
    func_13E4F0(h, 1);
    func_13E4C0(h, 6, 0);
    func_13E4D0(h, 1);
    func_13E460(h, 0);
    func_13E3B0(h, 1);
    func_13E3D0(h, 0);
    func_13E390(h, 0);
    func_13E460(h, 1);
    func_13E450(h, 2);
    func_13E430(h, 0);
    func_13E2F0(h, 0);
    func_13E400(h, 1);
    func_13E3E0(h, 1);
    for (i = 0; i < 2; i++) {
        sl = &o->f35F8[i];
        for (j = 0; j < 5; j++) {
            e = insect_InsectTeamGetPiece_5138d0(sl, j);
            if (e != 0) {
                if (insect_InsectPieceIsInPlay_5149e0(e) != 0) {
                    if (insect_InsectPieceIsDizzy_514c10(e) != 0) {
                        p = (u8 *)v0;
                        n = 0x10;
                        if (p != 0) {
                            do {
                                *p = 0;
                                n--;
                                p++;
                            } while (n != 0);
                        }
                        t = func_1C4A90(o->f870, e->f6C);
                        if (t != 0) {
                            func_1ADEC0(t, 0, v0);
                            v0[1] = v0[1] + 1.5f;
                        }
                        insect_InsectBattleCalcQuadCorners_4f47a0(o, v1, v2, v3, v4, v0, 0,
                                            1.0f, 1.0f, 1, cs, sn, 0.0f, 0.0f);
                        insect_InsectBattleDrawStarSprite_4f4e10(o, h, v1);
                        insect_InsectBattleDrawStarSprite_4f4e10(o, h, v2);
                        insect_InsectBattleDrawStarSprite_4f4e10(o, h, v3);
                        insect_InsectBattleDrawStarSprite_4f4e10(o, h, v4);
                    }
                }
            }
        }
    }
    func_141A20(o->fC0);
}
