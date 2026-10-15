#include "types.h"

typedef struct RetB {
    u8 pad000[0x2C];
    s16 unk2C;
} RetB;

class VtB {
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
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual RetB *v26(s64 a);
};

typedef struct Unk34B {
    u8 pad000[8];
    VtB *unk8;
} Unk34B;

typedef struct Unk8B {
    u8 pad000[0x34];
    Unk34B *unk34;
} Unk8B;

typedef struct Arg0B {
    u8 pad000[8];
    Unk8B *unk8;
} Arg0B;

typedef struct RetC {
    u8 pad000[0x1C];
    s32 unk1C;
} RetC;

extern "C" RetC *GroupFindByNameInRange_411390(Unk34B *a, s64 b, s64 c, s32 d);

extern "C" s32 WorldSavedFlagTestMaybe_3ed400(Arg0B *arg0, s16 arg1, s16 arg2, s32 arg3)
{
    s16 var_3;
    Unk8B *temp_2_2;
    RetB *temp_2_3;
    RetC *temp_2;

    if (arg3 == 0) {
        return 0;
    }
    temp_2_2 = arg0->unk8;
    if (temp_2_2 == NULL) {
        return 0;
    }
    temp_2_3 = temp_2_2->unk34->unk8->v26((s64)arg1);
    if (temp_2_3 == NULL) {
        return 1;
    }
    var_3 = temp_2_3->unk2C;
    if (var_3 < 0) {
        var_3 = 1;
    }
    temp_2 = GroupFindByNameInRange_411390(arg0->unk8->unk34, (s64)var_3, (s64)arg2, arg3);
    if (temp_2 == NULL) {
        return 1;
    }
    return (temp_2->unk1C & 2) != 0;
}
