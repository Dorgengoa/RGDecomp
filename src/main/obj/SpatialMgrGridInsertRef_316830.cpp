#include "types.h"

struct Obj316;

class VE316 {
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

struct Obj316 { VE316 *unk0; s32 unk4; };

extern "C" Obj316 *SpatialGridInsert_3163f0(void);

extern "C" void SpatialMgrGridInsertRef_316830(void *arg0, s32 arg1, Obj316 **arg2) {
    s32 var_3;
    Obj316 *temp_2;
    Obj316 *temp_4;
    Obj316 *temp_4_2;
    VE316 *temp_4_3;
    Obj316 *temp_4_4;

    temp_2 = SpatialGridInsert_3163f0();
    if (temp_2 == NULL) {
        return;
    }
    temp_2->unk4 = arg1;
    if ((void *)temp_2 == (void *)arg2) {
        return;
    }
    temp_4 = (Obj316 *)temp_2->unk0;
    if (((temp_4 != NULL) ^ 1) != 0) {
        goto rest;
    }
    if (temp_4 != NULL) {
        temp_4->unk4 = temp_4->unk4 - 1;
    }
    temp_4_2 = (Obj316 *)temp_2->unk0;
    var_3 = (temp_4_2 != NULL) ? temp_4_2->unk4 : 0;
    if ((var_3 == 0) && (temp_4_2 != NULL)) {
        temp_4_3 = temp_4_2->unk0;
        if (temp_4_3 != NULL) {
            temp_4_3->v25(-1);
        }
        ((Obj316 *)temp_2->unk0)->unk4 = 0;
        temp_2->unk0 = (VE316 *)NULL;
    }
    temp_2->unk0 = (VE316 *)NULL;
rest:
    temp_4_4 = *arg2;
    temp_2->unk0 = (VE316 *)temp_4_4;
    if (temp_4_4 != NULL) {
        temp_4_4->unk4 = temp_4_4->unk4 + 1;
    }
}
