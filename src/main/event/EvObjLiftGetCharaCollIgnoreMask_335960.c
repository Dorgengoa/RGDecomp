#include "types.h"

struct Obj {
    u8 pad000[0xD0];
    s32 mD0;
};

extern s32 EvObjFlagBit30Clear_2f9cc0(struct Obj *o);
extern s32 EvObjLiftGetPlayState_336120(struct Obj *o);

s32 EvObjLiftGetCharaCollIgnoreMask_335960(struct Obj *self)
{
    if ((((self->mD0 & 0x80000000) != 0) ^ 1) == 0) {
        return 0;
    }
    if (EvObjFlagBit30Clear_2f9cc0(self) == 0) {
        return 0;
    }
    if (EvObjLiftGetPlayState_336120(self) != 0x1 && EvObjLiftGetPlayState_336120(self) != 0x3) {
        return 0;
    }
    return 0x40;
}
