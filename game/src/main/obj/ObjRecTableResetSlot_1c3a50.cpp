/* rgp:protos */
#line 1
#include "types.h"

class C001C3A50 {
    u8 pad0[0x20];
public:
    VC_VPTR_MEMBER; void slot08() { VCM0(void, 0x8); }
};

extern "C" C001C3A50 * ObjRecTableGet_1c3b80(void *, int);

extern "C" s32 ObjRecTableResetSlot_1c3a50(void *rgp_a0, int rgp_a1)
{
    C001C3A50 *t;

    t = ObjRecTableGet_1c3b80((void *)rgp_a0, (int)rgp_a1);
    if (t == 0) {
        return 0;
    }
    t->slot08();
    return 1;
}
