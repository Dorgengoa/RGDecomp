#include "types.h"

/* `lw $25,0x0($4)` / `lw $25,0x1AC($25)` / `jr $25` is a C++ VIRTUAL
   TAIL CALL; the slot is 4*index + 8, so this is declared virtual
   number 105.  A struct of function pointers gives `jalr $2`. */

class V2F46B0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v105(s32 a0, s32 a1) { VCM(void, (void *, s32, s32), 0x1AC, a0, a1); }
};

extern "C" void UnitStatusFxStop_2f46b0(V2F46B0 *o)
{
    o->v105(1, 0);
}
