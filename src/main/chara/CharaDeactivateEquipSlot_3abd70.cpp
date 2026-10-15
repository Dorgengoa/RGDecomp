#include "types.h"

class Obj5C {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
};

class Obj003ABD70 {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    u8 pad4[0x498 - 4];
    Obj5C *unk498;
};

extern "C" s32 CharaDeactivateEquipSlot_3abd70(Obj003ABD70 *arg0)
{
    Obj5C *temp;

    temp = arg0->unk498;
    if (temp != NULL) {
        temp->v21();
    }
    arg0->unk498 = 0;
    arg0->v12();
    return 1;
}
