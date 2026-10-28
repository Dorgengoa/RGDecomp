#include "types.h"

class VE314 {
public:
    u8 pad000[0xB0];
    VC_VPTR_MEMBER;
    
    
    
    
    void v5() { VCM0(void, 0x1C); }
};

struct Slot314 { void *m0; void **m4; };

extern "C" void HandleRegistryDrawAll_314b70(Slot314 *arg0)
{
    Slot314 *cur;
    s32 i;
    VE314 *p;
    s32 skip;

    cur = arg0;
    i = 0;
    do {
        if (((cur->m4 != NULL) ^ 1) != 0) {
            goto next;
        }
        p = (cur->m4 != NULL) ? (VE314 *)(*cur->m4) : (VE314 *)NULL;
        p->v5();
next:
        i += 1;
        cur += 1;
    } while (i < 0x200);
}
