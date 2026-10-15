#include "types.h"

class V {
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
    virtual void fC8(s32);
};

extern "C" V *PoolGetUsedElem_36acb0(s32 arg0, s32 arg1);
extern "C" void ObjMgrGroupLetterSlotsReset_3bc270(void *arg0);
extern s32 D_004659C8[4];

extern "C" s32 ObjMgrBroadcastPhase_3ba9a0(u8 *arg0, s32 arg1)
{
    s32 n;
    s32 i;
    V *v;
    u8 *t;

    t = *(u8 **)(arg0 + 4);
    if (t == 0) {
        return 0;
    }
    if (!(*(*(u8 **)(t + 0x20) + 0x24C) & 1)) {
        return 0;
    }
    if (*(s32 *)(arg0 + 0x10) == 0) {
        return 0;
    }
    n = D_004659C8[0];
    for (i = 0; i < n; i++) {
        v = PoolGetUsedElem_36acb0(*(s32 *)(arg0 + 0x10), i);
        if (v != 0) {
            v->fC8(arg1);
        }
    }
    ObjMgrGroupLetterSlotsReset_3bc270(arg0);
    return 1;
}
