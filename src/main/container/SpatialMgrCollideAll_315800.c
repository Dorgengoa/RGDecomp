#include "types.h"

typedef struct Node Node;
struct Node {
    u8 pad000[4];
    s32 m04;
    Node *m08;
};

typedef struct {
    u8 pad000[0x94];
    Node **m94;
    s32 m98;
} Obj;

extern void HitShapeListCalcBounds_315350(void *, s32);
extern void QuadTreeApplyHits_315660(Obj *, Node *, void *, s32);

void SpatialMgrCollideAll_315800(Obj *arg0) {
    u8 sp30[0x20];
    Node **temp_4;
    Node *var_16;

    temp_4 = arg0->m94;
    if (temp_4 == NULL || arg0->m98 == 0) {
        return;
    }
    var_16 = *temp_4;
    while (var_16 != NULL) {
        HitShapeListCalcBounds_315350(sp30, var_16->m04);
        QuadTreeApplyHits_315660(arg0, var_16, sp30, arg0->m98);
        var_16 = var_16->m08;
    }
}
