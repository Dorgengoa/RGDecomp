#include "types.h"

class VE314A {
public:
    u8 pad000[0xB0];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void v25(s32);
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
