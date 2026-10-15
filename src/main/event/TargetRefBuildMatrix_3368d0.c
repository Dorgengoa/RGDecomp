#include "types.h"

typedef struct { u8 pad[0x30]; s32 f30; } Q_003368d0;

extern s32 TargetRefGetKind_2e7130(void *);
extern f32 TargetRefGetRadius_2e7100(void *);
extern void MatRotY_1cb200(Q_003368d0 *, f32);
extern void TargetRefGetPos_2e6a60(void *, void *);
extern void TargetRefGetMatrix_2e6870(void *, Q_003368d0 *);

void TargetRefBuildMatrix_3368d0(void *p, Q_003368d0 *q)
{
    if (TargetRefGetKind_2e7130(p) == 1) {
        MatRotY_1cb200(q, TargetRefGetRadius_2e7100(p));
        TargetRefGetPos_2e6a60(p, &q->f30);
    } else {
        TargetRefGetMatrix_2e6870(p, q);
    }
}
