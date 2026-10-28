/* rgp:protos */
#define RGP_SELF_EvDoorObjGetCharaCollIgnoreMask_303810 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj {
    u8 pad000[0xD0];
    s32 mD0;
};

/*rgp*/
/*rgp*/

s32 EvDoorObjGetCharaCollIgnoreMask_303810(struct Obj *self)
{
    if ((((self->mD0 & 0x80000000) != 0) ^ 1) == 0) {
        return 0;
    }
    if (EvObjFlagBit30Clear_2f9cc0(self) == 0) {
        return 0;
    }
    if (((short)EvDoorObjGetState_304040(self)) != 0x1 && ((short)EvDoorObjGetState_304040(self)) != 0x2) {
        return 0;
    }
    return 0x40;
}
