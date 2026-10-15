#include "types.h"
#include "vec.h"

typedef struct Sub6C_00196ed0 {
    u8 pad000[0x100];
    s32 unk100;
} Sub6C_00196ed0;

typedef struct Sub70_00196ed0 {
    u8 pad000[4];
    s32 unk4;
    u8 pad008[0x28 - 8];
    s8 unk28;
} Sub70_00196ed0;

typedef struct Obj00196ed0 {
    u8 pad000[0x6C];
    Sub6C_00196ed0 *unk6C;
    Sub70_00196ed0 *unk70;
} Obj00196ed0;

extern void MtxIdentity_13d2e0(void *);
extern void ModelFrameSetMatrix_14a190(void *, Mtx4 *);
extern void ModelDetachRootFrames_151460(void *);

void NodeObjBasicResetMatrix_196ed0(Obj00196ed0 *arg0)
{
    Sub6C_00196ed0 *s1;
    Mtx4 m;

    s1 = arg0->unk6C;
    if (s1 != 0) {
        s1->unk100 = 0;
        ModelDetachRootFrames_151460(s1);
    }
    if (arg0->unk70 != 0) {
        MtxIdentity_13d2e0(&m);
        ModelFrameSetMatrix_14a190(arg0->unk70, &m);
        if (arg0->unk70->unk28 != 0) {
            arg0->unk70->unk4 = 0;
        }
    }
}
