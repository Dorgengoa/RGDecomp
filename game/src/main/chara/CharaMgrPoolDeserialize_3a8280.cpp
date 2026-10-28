#include "types.h"

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    void f18(u8 * a0, s32 a1) { VCM(void, (void *, u8 *, s32), 0x18, a0, a1); }
};

typedef struct S003a8280 {
    u8 pad0[8];
    s32 unk8;
} S003a8280;

extern "C" {
void PoolClear_36ade0(s32);
s32 UnpackWordTriple_370d70(u8 *, s32, s32 *, s32 *, s32 *);
Obj *CharaCreateByKind_3a8e70(S003a8280 *, s32);
}
extern "C" s32 D_004658F8[];

extern "C" s32 CharaMgrPoolDeserialize_3a8280(S003a8280 *arg0, u8 *arg1, s32 arg2)
{
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    s32 total;
    s32 n;
    Obj *o;
    u8 *p;
    s32 rem;

    if (arg1 == NULL || arg2 <= 0) {
        return 0;
    }
    p = arg1;
    rem = arg2;
    total = 0;
    if (D_004658F8[0] < arg2) {
        return 0;
    }
    PoolClear_36ade0(arg0->unk8);
    while (rem > 0) {
        sp5C = 0;
        sp58 = 0;
        sp54 = 0;
        n = UnpackWordTriple_370d70(p, rem, &sp5C, &sp58, &sp54);
        if (n <= 0) {
            break;
        }
        total += n;
        rem -= n;
        p += n;
        if (sp5C == 4) {
            o = CharaCreateByKind_3a8e70(arg0, sp58);
            if (o != NULL) {
                o->f18(p, sp54);
            }
        }
        total += sp54;
        rem -= sp54;
        p += sp54;
    }
    return total;
}
