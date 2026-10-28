/* rgp:protos */
#define RGP_SELF_EvObjLiftSetPathFromStops_335cc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x, y, z, w; } Vec4;
typedef struct { Vec4 r[4]; } Mtx4;

typedef struct {
    u8  pad00[0xF0];
    s32 fF0;
    u8  padF4[0x18];
    s16 f10C;
    s16 f10E;
} Obj;

/*rgp*/
typedef struct { u8 d[0x30]; } Sub;
typedef struct { Sub a; Sub b; } Node;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* stack locals allocated in REVERSE declaration order:
   m1 -> 0xF0, e -> 0xE0, d -> 0xD0, m2 -> 0x90, c -> 0x80, b -> 0x70 */
s32 EvObjLiftSetPathFromStops_335cc0(Obj *self, s32 i0, s32 i1)
{
    Mtx4 m1 __attribute__((aligned(16)));
    Vec4 e __attribute__((aligned(16)));
    Vec4 d __attribute__((aligned(16)));
    Mtx4 m2 __attribute__((aligned(16)));
    Vec4 c __attribute__((aligned(16)));
    Vec4 b __attribute__((aligned(16)));
    Node *t;
    s32 h0;
    s32 h1;

    /* two tests branching in OPPOSITE directions = an || */
    if (self->fF0 == 0 || ((short)EventPathRecGetPointCount_2e4190(self->fF0)) < 2) {
        return 0;
    }
    t = ((Node *)EventPathRecGetPoints_2e4180(self->fF0));
    if (t == 0) {
        return 0;
    }
    h0 = ((s32)EvObjLiftGetTargetSet_336040(self, i0));
    if (h0 == 0 || TargetRefIsActive_2e6f00(((s32)EvTargetSetGetFirstRef_336960(h0))) == 0) {
        return 0;
    }
    h1 = ((s32)EvObjLiftGetTargetSet_336040(self, i1));
    if (h1 == 0 || TargetRefIsActive_2e6f00(((s32)EvTargetSetGetFirstRef_336960(h1))) == 0) {
        return 0;
    }
    TargetRefBuildMatrix_3368d0(h0, &m1);
    MatToRotPos_1cade0(&e, &d, &m1);
    SrtInit_1c74d0(&t->a);
    SrtSetRot_1c73d0(&t->a, 0.0f, e.y, 0.0f);
    SrtSetPosFromVec_1c7410(&t->a, &d);
    TargetRefBuildMatrix_3368d0(h1, &m2);
    MatToRotPos_1cade0(&c, &b, &m2);
    SrtInit_1c74d0(&t->b);
    SrtSetRot_1c73d0(&t->b, 0.0f, c.y, 0.0f);
    SrtSetPosFromVec_1c7410(&t->b, &b);
    self->f10C = i0;
    self->f10E = i1;
    return 1;
}
