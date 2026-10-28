/* rgp:protos */
#define RGP_SELF_NodeObjBasicResetMatrix_196ed0 1
#include "port/game_protos.h"
#line 1
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

/*rgp*/
/*rgp*/
/*rgp*/

void NodeObjBasicResetMatrix_196ed0(Obj00196ed0 *arg0)
{
    Sub6C_00196ed0 *s1;
    Mtx4 m __attribute__((aligned(16)));

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
