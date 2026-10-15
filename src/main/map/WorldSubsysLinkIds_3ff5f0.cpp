#pragma opt_propagation off
#include "types.h"

extern "C" {
extern void *IterNext_370040(void *arg0);
extern void IterInit_370170(void *arg0, s32 arg1);
}

class VObj {
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
    virtual s32 f(s16 x);
};

typedef struct {
    u8 pad0[0xA];
    s16 unkA;
    u8 padC[0x14 - 0xC];
    s32 *unk14;
} Node;

extern "C" {
s32 WorldSubsysLinkIds_3ff5f0(s32 arg0, void *arg1)
{
    s32 *var_18;
    Node *temp_2;
    s32 var_17;
    s32 var_5;
    Node *nd;
    u8 sp58[0x8];

    if (arg1 == NULL) {
        return 0;
    }
    var_5 = arg0;
    if (arg0 != 0) {
        var_5 += 0x88;
    }
    IterInit_370170(sp58, var_5);
    while ((nd = (Node *)IterNext_370040(sp58)), (temp_2 = nd) != NULL) {
        var_18 = temp_2->unk14;
        if ((var_18 != NULL) && (temp_2->unkA > 0)) {
            for (var_17 = 0; var_17 < temp_2->unkA; var_17++) {
                *var_18 = (*(VObj **)((u8 *)*(void **)((u8 *)arg1 + 0x98) + 0xC))->f(*(s16 *)var_18);
                var_18++;
            }
        }
    }
    return 1;
}
}
