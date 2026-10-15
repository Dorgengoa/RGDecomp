#include "types.h"

struct Obj {
    u8 pad000[0xD0];
    s32 mD0;
};

extern s32 EvObjFlagBit30Clear_2f9cc0(struct Obj *o);
extern s32 ObjTypeVehicleGetPlayState_3380a0(struct Obj *o);

s32 ObjTypeVehicleGetCharaCollIgnoreMask_337c40(struct Obj *self)
{
    if ((((self->mD0 & 0x80000000) != 0) ^ 1) == 0) {
        return 0;
    }
    if (EvObjFlagBit30Clear_2f9cc0(self) == 0) {
        return 0;
    }
    if (ObjTypeVehicleGetPlayState_3380a0(self) != 0x1 && ObjTypeVehicleGetPlayState_3380a0(self) != 0x3) {
        return 0;
    }
    return 0x40;
}
