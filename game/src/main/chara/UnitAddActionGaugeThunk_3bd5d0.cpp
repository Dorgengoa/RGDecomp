/* rgp:protos */
#line 1
#include "types.h"

/* ONE symbol, TWO entries: a 4-word virtual tail-call thunk (slot 0x270 =
   index 154) then a null-guarded forwarder that VIRTUAL-calls slot 0x2D8 =
   index 180 with *p.  `jalr $25` is a C++ virtual; a struct of function
   pointers gives `jalr $2` and cannot match. */

class V3BD5D0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v180(s16 a) { return VCM(s32, (void *, s16), 0x2D8, a); }
};

extern "C" void __attribute__((naked)) UnitAddActionGaugeThunk_3bd5d0(V3BD5D0 *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *624(%eax)"); 

}

extern "C" s32 func_003BD5D0_e1(V3BD5D0 *o, s16 *p)
{
    s32 r;

    /* retail's `beqz $5` branches to the FAILURE block, which sits AFTER the
       payload -- the null check's THEN is the payload and the ELSE is `0`.
       The early-return spelling loses the duplicated `ld $31` and is a word
       short. */
    if (p != 0) {
        r = o->v180(*p);
    } else {
        r = 0;
    }
    return r;
}
