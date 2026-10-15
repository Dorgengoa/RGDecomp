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

extern s32 EventPathRecGetPointCount_2e4190(s32);
typedef struct { u8 d[0x30]; } Sub;
typedef struct { Sub a; Sub b; } Node;
extern Node *EventPathRecGetPoints_2e4180(s32);
extern s32 EvObjLiftGetTargetSet_336040(Obj *, s32);
extern s32 EvTargetSetGetFirstRef_336960(s32);
extern s32 TargetRefIsActive_2e6f00(s32);
extern void TargetRefBuildMatrix_3368d0(s32, Mtx4 *);
extern void MatToRotPos_1cade0(Vec4 *, Vec4 *, Mtx4 *);
extern void SrtInit_1c74d0(void *);
extern void SrtSetRot_1c73d0(void *, f32, f32, f32);
extern void SrtSetPosFromVec_1c7410(void *, Vec4 *);

/* stack locals allocated in REVERSE declaration order:
   m1 -> 0xF0, e -> 0xE0, d -> 0xD0, m2 -> 0x90, c -> 0x80, b -> 0x70 */
s32 EvObjLiftSetPathFromStops_335cc0(Obj *self, s32 i0, s32 i1)
{
    Mtx4 m1;
    Vec4 e;
    Vec4 d;
    Mtx4 m2;
    Vec4 c;
    Vec4 b;
    Node *t;
    s32 h0;
    s32 h1;

    /* two tests branching in OPPOSITE directions = an || */
    if (self->fF0 == 0 || EventPathRecGetPointCount_2e4190(self->fF0) < 2) {
        return 0;
    }
    t = EventPathRecGetPoints_2e4180(self->fF0);
    if (t == 0) {
        return 0;
    }
    h0 = EvObjLiftGetTargetSet_336040(self, i0);
    if (h0 == 0 || TargetRefIsActive_2e6f00(EvTargetSetGetFirstRef_336960(h0)) == 0) {
        return 0;
    }
    h1 = EvObjLiftGetTargetSet_336040(self, i1);
    if (h1 == 0 || TargetRefIsActive_2e6f00(EvTargetSetGetFirstRef_336960(h1)) == 0) {
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
