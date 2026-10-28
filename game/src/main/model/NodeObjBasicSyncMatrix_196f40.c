/* rgp:protos */
#define RGP_SELF_NodeObjBasicSyncMatrix_196f40 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

typedef struct Obj00196f40 {
    u8 pad000[0x6C];
    void *unk6C;
    void *unk70;
} Obj00196f40;

/*rgp*/
/*rgp*/
/*rgp*/

void NodeObjBasicSyncMatrix_196f40(Obj00196f40 *arg0)
{
    Mtx4 m1 __attribute__((aligned(16)));
    Mtx4 m2 __attribute__((aligned(16)));

    if (arg0->unk6C != 0) {
        NodeCalcWorldMatrix_186130(arg0, &m1);
        ModelSetRootMatrix_1512e0(arg0->unk6C, &m1);
    }
    if (arg0->unk70 != 0) {
        NodeCalcWorldMatrix_186130(arg0, &m2);
        ModelFrameSetMatrix_14a190(arg0->unk70, &m2);
    }
}
