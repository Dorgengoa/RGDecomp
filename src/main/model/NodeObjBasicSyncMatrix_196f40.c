#include "types.h"
#include "vec.h"

typedef struct Obj00196f40 {
    u8 pad000[0x6C];
    void *unk6C;
    void *unk70;
} Obj00196f40;

extern void NodeCalcWorldMatrix_186130(Obj00196f40 *, Mtx4 *);
extern void ModelSetRootMatrix_1512e0(void *, Mtx4 *);
extern void ModelFrameSetMatrix_14a190(void *, Mtx4 *);

void NodeObjBasicSyncMatrix_196f40(Obj00196f40 *arg0)
{
    Mtx4 m1;
    Mtx4 m2;

    if (arg0->unk6C != 0) {
        NodeCalcWorldMatrix_186130(arg0, &m1);
        ModelSetRootMatrix_1512e0(arg0->unk6C, &m1);
    }
    if (arg0->unk70 != 0) {
        NodeCalcWorldMatrix_186130(arg0, &m2);
        ModelFrameSetMatrix_14a190(arg0->unk70, &m2);
    }
}
