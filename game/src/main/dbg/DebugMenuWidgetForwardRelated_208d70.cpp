/* rgp:protos */
#line 1
#include "types.h"

/* retail's indirect call is `lw $25,0x2C($obj) / lw $25,0x28($25) / jalr $25`
   -- a jalr on $25 is C++ virtual dispatch, unreachable from any C spelling.
   vptr lands at offset 0x2C (after the declared data members); slot 0x28 is
   virtual index 8 (slot = 8 + 4*N). */

class VE00208d70 {
public:
    u8 pad00[0x2A];
    u16 unk2A;
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    void v8() { VCM0(void, 0x28); }
};

extern "C" VE00208d70 * DebugMenuWidgetGetCurrentChild_209dd0(void *);

extern "C" void DebugMenuWidgetForwardRelated_208d70(VE00208d70 *arg0)
{
    VE00208d70 *other;

    if (arg0->unk2A & 0x40) {
        other = DebugMenuWidgetGetCurrentChild_209dd0((void *)arg0);
        if ((other != NULL) && (other->unk2A & 0x40)) {
            other->v8();
        }
    }
}
