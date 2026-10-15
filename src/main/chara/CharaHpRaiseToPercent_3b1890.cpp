#include "types.h"

class VE3B1890 {
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
    virtual s32 unkC0(f32 a);
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
    virtual void unkF4(s32 a);
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void v65();
    virtual void v66();
    virtual void v67();
    virtual void v68();
    virtual void v69();
    virtual void v70();
    virtual void v71();
    virtual s32 unk128(s32 a);

    u8 pad4[0x14 - 4];
    s32 unk14;
};

extern "C" s32 CharaHpRaiseToPercent_3b1890(VE3B1890 *arg0, f32 fparg0)
{
    s32 var_5;

    if (arg0->unkC0(fparg0) != 0) {
        return 0;
    }
    f32 t = (f32) arg0->unk128(1) / 100.0f;
    var_5 = (s32) (t * fparg0);
    if (var_5 <= 0) {
        var_5 = 1;
    }
    if ((u32) arg0->unk14 < (u32) var_5) {
        arg0->unkF4(var_5);
    }
    return 1;
}
