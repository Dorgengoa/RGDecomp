#include "types.h"

/* Ask the object whether it accepts mode 0x5; hand it back if it does.  The
   result is kept in the callee-saved register the `jalr` delay slot loads,
   so the null is written over it rather than branched around.

   Clone of EquipSlotDynamicCastKind2_39fe70: this group varies only in the mode constant and
   the vtable slot. */

class VA {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual s32 v6(s32);
};

extern "C" VA *InvObjCastToItem4B0_3d3cd0(VA *o)
{
    return o->v6(0x5) != 0 ? o : 0;
}
