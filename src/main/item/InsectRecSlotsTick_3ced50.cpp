#include "types.h"

typedef struct SubCED50 {
    u8 pad00[0xC];
    s32 unkC;
} SubCED50;

typedef struct Obj003CED50 {
    u8 pad00[0x18];
    SubCED50 *unk18;
} Obj003CED50;

class Base003ced50 {
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
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
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void unk10C(f32 x);
};

extern "C" Base003ced50 *InsectRecSlotGetItem_3cfb30(void *arg0, s32 arg1);

extern "C" s32 InsectRecSlotsTick_3ced50(Obj003CED50 *arg0, f32 fparg0)
{
    SubCED50 *sub;
    Base003ced50 *obj;
    s32 i;

    sub = arg0->unk18;
    if (sub == NULL) {
        return 0;
    }
    if (sub->unkC == 0) {
        return 0;
    }
    i = 0;
    do {
        obj = InsectRecSlotGetItem_3cfb30(arg0, i);
        if (obj != NULL) {
            obj->unk10C(fparg0);
        }
        i += 1;
    } while (i < 5);
    return 1;
}
