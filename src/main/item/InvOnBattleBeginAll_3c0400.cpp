#include "types.h"

extern "C" {
class Item {
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
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void fF4();
};

struct Bf { u8 b0 : 1; u8 b1 : 1; u8 rest : 6; };
struct A3 { u8 pad[0x168]; s32 unk168; };
extern Item *PoolGetUsedElem_36acb0(s32, s32);
extern s32 D_00465B50[4];
extern void *D_00483890;

s32 InvOnBattleBeginAll_3c0400(struct A3 *arg0)
{
    s32 temp_16;
    s32 var_17;
    Item *temp_2;

    if (D_00483890 == NULL) {
        return 0;
    }
    if (*(u8 *)(*(u8 **)((u8 *)D_00483890 + 0x20) + 0x24C) & 1) {
        return 0;
    }
    if (arg0->unk168 == 0) {
        return 0;
    }
    temp_16 = D_00465B50[0];
    for (var_17 = 0; var_17 < temp_16; var_17++) {
        temp_2 = PoolGetUsedElem_36acb0(arg0->unk168, var_17);
        if (temp_2 != NULL && ((struct Bf *)((u8 *)temp_2 + 0xA))->b1 == 0) {
            temp_2->fF4();
        }
    }
    return 1;
}

}
