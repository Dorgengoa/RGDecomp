#include "types.h"

class VE314B {
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
    virtual void v9(void);
};

struct Slot314B { void *m0; void **m4; };

extern "C" void GetGameData_1fede0(void);

extern "C" void HandleRegistryApplyHitsAll_314be0(Slot314B *arg0)
{
    Slot314B *cur;
    s32 i;
    VE314B *p;

    cur = arg0;
    GetGameData_1fede0();
    i = 0;
    do {
        if (((cur->m4 != NULL) ^ 1) != 0) {
            goto next;
        }
        p = (cur->m4 != NULL) ? (VE314B *)(*cur->m4) : (VE314B *)NULL;
        p->v9();
next:
        i += 1;
        cur += 1;
    } while (i < 0x200);
}
