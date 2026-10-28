/* rgp:protos */
#line 1
#include "types.h"

class O {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v206(s32 a0) { return VCM(s32, (void *, s32), 0x340, a0); }
    
    
    
    
    
};

extern "C" s32 CharaDataGetEntry0ThunkMaybe_3afd00(O *o)
{
    return o->v206(0);
}

extern "C" void __attribute__((naked)) func_003AFD00_e1(O *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *828(%eax)"); 

}

extern "C" void __attribute__((naked)) func_003AFD00_e2(O *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *840(%eax)"); 

}

extern "C" void __attribute__((naked)) func_003AFD00_e3(O *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *840(%eax)"); 

}

extern "C" void __attribute__((naked)) func_003AFD00_e4(O *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *848(%eax)"); 

}

extern "C" void __attribute__((naked)) func_003AFD00_e5(O *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *852(%eax)"); 

}

extern "C" s32 func_003AFD00_e6(O *o, s32 x)
{
    s32 r = o->v206(x);

    if (r != 0) {
        r = r + 4;
    } else {
        r = 0;
    }
    return r;
}
