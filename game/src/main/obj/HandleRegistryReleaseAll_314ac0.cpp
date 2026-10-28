#include "types.h"

class VE314A {
public:
    u8 pad000[0xB0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v25(s32 a0) { VCM(void, (void *, s32), 0x6C, a0); }
};

struct ObjA { VE314A *unk0; s32 unk4; };
struct Cursor { u8 pad0[4]; ObjA *unk4; };

extern "C" void HandleRegistryReleaseAll_314ac0(Cursor *arg0)
{
    Cursor *cur;
    s32 i;
    ObjA *a;
    ObjA *a2;
    s32 refc;
    VE314A *b;

    cur = arg0;
    i = 0;
    do {
        a = cur->unk4;
        if (((a != 0) ^ 1) != 0) {
            goto next;
        }
        if (a != 0) {
            a->unk4 = a->unk4 - 1;
        }
        a2 = cur->unk4;
        refc = (a2 != 0) ? a2->unk4 : 0;
        if (refc == 0 && a2 != 0) {
            b = a2->unk0;
            if (b != 0) {
                b->v25(-1);
            }
            cur->unk4->unk4 = 0;
            cur->unk4 = 0;
        }
        cur->unk4 = 0;
next:
        i += 1;
        cur += 1;
    } while (i < 0x200);
}
