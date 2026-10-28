#include "types.h"

/* `lw $25,0x0($4)` / `lw $25,0x1A0($25)` / `jr $25` is a C++ VIRTUAL
   TAIL CALL; the slot is 4*index + 8, so this is declared virtual
   number 102.  A struct of function pointers gives `jalr $2`. */

class V2E8420 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v102(s32 a0, s32 a1, s32 a2) { VCM(void, (void *, s32, s32, s32), 0x1A0, a0, a1, a2); }
};

extern "C" void UnitStatusClear_2e8420(V2E8420 *o, s32 a)
{
    o->v102(a, 0, 1);
}
