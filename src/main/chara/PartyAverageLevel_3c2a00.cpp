#include "types.h"

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
    virtual s32 f();
};

extern "C" {
extern VObj *CharaMgrPoolFindById_3a8c60(s32 arg0, s16 arg1);
extern void *D_00483890;

s32 PartyAverageLevel_3c2a00(void *arg0)
{
    s32 var_17;
    s16 temp_5;
    s32 var_16;
    s16 temp_19;
    s32 var_20;
    VObj *temp_2;

    if (D_00483890 == NULL) {
        return 0;
    }
    temp_19 = *(s16 *)((u8 *)arg0 + 0x18C);
    var_17 = 0;
    var_16 = 0;
    var_20 = 0;
    while (var_20 < temp_19) {
        temp_5 = *(s16 *)((u8 *)arg0 + (var_20 * 2) + 0x190);
        if (temp_5 >= 0) {
            temp_2 = CharaMgrPoolFindById_3a8c60(*(s32 *)((u8 *)D_00483890 + 0x14), temp_5);
            if (temp_2 != NULL) {
                var_17 += temp_2->f();
                var_16 += 1;
            }
        }
        var_20 += 1;
    }
    var_20 = 0;
    do {
        temp_5 = *(s16 *)((u8 *)arg0 + (var_20 * 2) + 0x196);
        if (temp_5 >= 0) {
            temp_2 = CharaMgrPoolFindById_3a8c60(*(s32 *)((u8 *)D_00483890 + 0x14), temp_5);
            if (temp_2 != NULL) {
                var_17 += temp_2->f();
                var_16 += 1;
            }
        }
        var_20 += 1;
    } while (var_20 < 7);
    return (s32) ((f32) var_17 / (f32) var_16);
}
}
