#include "types.h"
/* insect 0x0051F050 -- 372 bytes.  Eight register arguments ($4..$11) fill a
 * freshly allocated record; the `dsll32/dsra32 ..,16` pairs sit AT THE CALL,
 * not in the prologue, so it is the CALLEE that takes `s16` and our own
 * parameters are words ([[ixa09 s16 parameter]]). */

typedef struct Rec {
    void *f00;                      /* +0x00 */
    void *f04;                      /* +0x04 */
    void *f08;                      /* +0x08 */
    void *f0C;                      /* +0x0C */
    s8    f10;                      /* +0x10 */
    s8    f11;                      /* +0x11 */
    s8    f12;                      /* +0x12 */
    s8    f13;                      /* +0x13 */
    s8    f14;                      /* +0x14 */
} Rec;

typedef struct Obj {
    u8    pad00[0x58];
    void *f58;                      /* +0x58 */
    u8    pad5C[0xC4 - 0x5C];
    u8    fC4[4];                   /* +0xC4 */
} Obj;

extern void  insect_InsectBoardMarkReachableTargets_4ec580(void *h);
extern void  insect_InsectBoardFindPiece_4ee190(void *h, void *a, s32 *x, s32 *y);
extern s32   insect_InsectBoardIsTargetMarked_4ee8c0(void *h, s32 x, s32 y);
extern Rec  *insect_InsectAiActionNew_523330(u8 *p);
extern void  insect_InsectBoardCalcAttackRange_4ec720(void *h, void *a, void *b, s16 x, s16 y);
extern s32   insect_InsectBoardIsInAttackRange_4ee850(void *h, s32 a, s32 b);

Rec *insect_InsectAiAddMoveSpecialAction_51f050(Obj *o, void *a, void *b, void *c, s32 d, s32 e,
                         s32 f, s32 g)
{
    s32  x;
    s32  y;
    s32  hit;
    Rec *r;

    if (a == 0 || b == 0) {
        return 0;
    }
    hit = 0;
    insect_InsectBoardMarkReachableTargets_4ec580(o->f58);
    insect_InsectBoardFindPiece_4ee190(o->f58, b, &x, &y);
    if (insect_InsectBoardIsTargetMarked_4ee8c0(o->f58, x, y) != 0) {
        hit = 1;
    }
    r = insect_InsectAiActionNew_523330(o->fC4);
    if (r != 0) {
    r->f00 = a;
    r->f04 = b;
    r->f10 = d;
    r->f11 = e;
    r->f14 = 1;
    if (hit != 0) {
        r->f08 = b;
        r->f14 = r->f14 | 2;
    }
    if (c != 0) {
        insect_InsectBoardCalcAttackRange_4ec720(o->f58, c, a, d, e);
        if (insect_InsectBoardIsInAttackRange_4ee850(o->f58, f, g) != 0) {
            r->f0C = c;
            r->f12 = f;
            r->f13 = g;
            r->f14 = r->f14 | 4;
        }
    }
    }
    return r;
}
