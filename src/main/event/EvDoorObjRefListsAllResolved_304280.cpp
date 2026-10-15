#include "types.h"

class C_00304280 {
    u8 pad000[0xDC];
public:
    /* +0x008 */ virtual void s008();
    /* +0x00C */ virtual void s00C();
    /* +0x010 */ virtual void s010();
    /* +0x014 */ virtual s32 v14();
};

extern "C" s32 EventRefListAllResolved_304890(s32 *p);

extern "C" s32 EvDoorObjRefListsAllResolved_304280(C_00304280 *o)
{
    s32 i;
    s32 *base;

    if (o->v14() == 0) {
        return 0;
    }
    for (i = 0; i < *(s16 *)((u8 *)o + 0x188); i++) {
        base = *(s32 **)((u8 *)o + 0x180);
        if (EventRefListAllResolved_304890(base + i * 3) == 0) {
            return 0;
        }
    }
    return 1;
}
