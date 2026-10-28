/* rgp:protos */
#define RGP_SELF_NodeObjBasicCalcCollBounds_196c40 1
#include "port/game_protos.h"
#line 1
/* main s22: 1 WRONG ACCESS WIDTH(s) corrected from retail's own
   opcode (same registers + offset, different opcode -- a type defect no
   colouring lever can reach).  14 -> improved; still parked. */
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

typedef struct { u8 pad[0x70]; void *unk70; } O196;
s32 NodeObjBasicCalcCollBounds_196c40(O196 *arg0, s32 arg1)
{
    u8 sp70[0x40] __attribute__((aligned(16)));
    u8 sp30[0x40] __attribute__((aligned(16)));
    s32 temp_16;
    void *temp_3;

    if (arg0->unk70 == NULL) {
        return 0;
    }
    if (arg0->unk70 != NULL) {
        NodeCalcWorldMatrix_186130((s32)arg0, sp70);
        ModelFrameSetMatrix_14a190(arg0->unk70, sp70);
    }
    temp_16 = CollFrameTreeCalcBounds_16be80(arg0->unk70, arg1, 0, 0);
    if (arg0->unk70 != NULL) {
        MtxIdentity_13d2e0(sp30);
        ModelFrameSetMatrix_14a190(arg0->unk70, sp30);
        temp_3 = arg0->unk70;
        if (*(s8 *)((u8 *)temp_3 + 0x28) != 0) {
            *(s32 *)((u8 *)temp_3 + 4) = 0;
        }
    }
    return temp_16;
}
