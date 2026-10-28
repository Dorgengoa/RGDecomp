#include "types.h"

struct R3FAE00 { u8 pad000[0x10]; s32 f10; };
struct Base3FAE00 { u8 pad000[0x10]; };
struct C3FAE00 : Base3FAE00 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    struct R3FAE00 * v7(void *b, void *c, void *d) { return VCM(struct R3FAE00 *, (void *, void *, void *, void *), 0x24, b, c, d); }
};

extern "C" s32 BtlEffSetRowSelectEntry_3fae00(void *self, struct C3FAE00 *a, void *b, void *c, void *d)
{
    struct R3FAE00 *r;

    if (a == 0) return 0;
    r = a->v7(b, c, d);
    if (r == 0) return 0;
    if (r != 0) {
        return r->f10;
    }
    return 0;
}
