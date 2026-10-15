#include "types.h"

/* Ask the object whether it accepts mode 0x1; hand it back if it does.  The
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
    virtual void d6();
    virtual s32 v7(s32);
};

extern "C" VA *EquipSlotDynamicCastKind1_39fec0(VA *o)
{
    return o->v7(0x1) != 0 ? o : 0;
}
