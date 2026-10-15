#include "types.h"

struct Obj315C70;

class VE315C70 {
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

struct Obj315C70 { VE315C70 *unk0; s32 unk4; };

extern "C" Obj315C70 *QuadTreeInsert_315880(void *, s32, s32, s32);

extern "C" void SpatialMgrQuadTreeInsertRef_315c70(void *arg0, s32 arg1, Obj315C70 **arg2) {
    s32 var_3;
    Obj315C70 *temp_2;
    Obj315C70 *temp_4;
    Obj315C70 *temp_4_2;
    VE315C70 *temp_4_3;
    Obj315C70 *temp_4_4;

    temp_2 = QuadTreeInsert_315880(arg0, *(s32 *)((u8 *)arg0 + 0x98), 1, arg1);
    if (temp_2 == NULL) {
        return;
    }
    temp_2->unk4 = arg1;
    if ((void *)temp_2 == (void *)arg2) {
        return;
    }
    temp_4 = (Obj315C70 *)temp_2->unk0;
    if (((temp_4 != NULL) ^ 1) != 0) {
        goto rest;
    }
    if (temp_4 != NULL) {
        temp_4->unk4 = temp_4->unk4 - 1;
    }
    temp_4_2 = (Obj315C70 *)temp_2->unk0;
    var_3 = (temp_4_2 != NULL) ? temp_4_2->unk4 : 0;
    if ((var_3 == 0) && (temp_4_2 != NULL)) {
        temp_4_3 = temp_4_2->unk0;
        if (temp_4_3 != NULL) {
            temp_4_3->v25(-1);
        }
        ((Obj315C70 *)temp_2->unk0)->unk4 = 0;
        temp_2->unk0 = (VE315C70 *)NULL;
    }
    temp_2->unk0 = (VE315C70 *)NULL;
rest:
    temp_4_4 = *arg2;
    temp_2->unk0 = (VE315C70 *)temp_4_4;
    if (temp_4_4 != NULL) {
        temp_4_4->unk4 = temp_4_4->unk4 + 1;
    }
}
