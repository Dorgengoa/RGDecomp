#include "types.h"

class C001C3A50 {
    u8 pad0[0x20];
public:
    virtual void slot08();
};

extern "C" C001C3A50 *ObjRecTableGet_1c3b80(void);

extern "C" s32 ObjRecTableResetSlot_1c3a50(void)
{
    C001C3A50 *t;

    t = ObjRecTableGet_1c3b80();
    if (t == 0) {
        return 0;
    }
    t->slot08();
    return 1;
}
