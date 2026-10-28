/* rgp:protos */
#define RGP_SELF_EvObjLiftGetCharaCollIgnoreMask_335960 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj {
    u8 pad000[0xD0];
    s32 mD0;
};

/*rgp*/
/*rgp*/

s32 EvObjLiftGetCharaCollIgnoreMask_335960(struct Obj *self)
{
    if ((((self->mD0 & 0x80000000) != 0) ^ 1) == 0) {
        return 0;
    }
    if (EvObjFlagBit30Clear_2f9cc0(self) == 0) {
        return 0;
    }
    if (((short)EvObjLiftGetPlayState_336120(self)) != 0x1 && ((short)EvObjLiftGetPlayState_336120(self)) != 0x3) {
        return 0;
    }
    return 0x40;
}
