#include "types.h"

/* retail's indirect call is `lw $25,0x2C($obj) / lw $25,0x28($25) / jalr $25`
   -- a jalr on $25 is C++ virtual dispatch, unreachable from any C spelling.
   vptr lands at offset 0x2C (after the declared data members); slot 0x28 is
   virtual index 8 (slot = 8 + 4*N). */

class VE00208d70 {
public:
    u8 pad00[0x2A];
    u16 unk2A;
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
};

extern "C" VE00208d70 *DebugMenuWidgetGetCurrentChild_209dd0(void);

extern "C" void DebugMenuWidgetForwardRelated_208d70(VE00208d70 *arg0)
{
    VE00208d70 *other;

    if (arg0->unk2A & 0x40) {
        other = DebugMenuWidgetGetCurrentChild_209dd0();
        if ((other != NULL) && (other->unk2A & 0x40)) {
            other->v8();
        }
    }
}
