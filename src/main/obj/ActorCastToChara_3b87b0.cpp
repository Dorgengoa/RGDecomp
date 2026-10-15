#include "types.h"

/* Ask the object whether it accepts mode 0x3e8; hand it back if it does.  The
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
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual s32 v11(s32);
};

extern "C" VA *ActorCastToChara_3b87b0(VA *o)
{
    return o->v11(0x3e8) != 0 ? o : 0;
}
