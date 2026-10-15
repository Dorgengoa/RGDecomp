#include "types.h"

class SubB003cd550 {
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
    virtual s32 v26(s16 a);
};

typedef struct SubA003cd550 {
    u8 pad0[0x8];
    SubB003cd550 *unk8;
} SubA003cd550;

typedef struct Obj003cd550 {
    u8 pad0[0x4];
    SubA003cd550 *unk4;
} Obj003cd550;

extern "C" s32 StateGetChapter_3cd5b0(Obj003cd550 *arg0);

extern "C" s32 ProgressGetChapterRec_3cd550(Obj003cd550 *arg0)
{
    SubA003cd550 *a;
    SubB003cd550 *b;
    s16 val;

    a = arg0->unk4;
    if (a == 0) {
        return 0;
    }
    val = (s16) StateGetChapter_3cd5b0(arg0);
    a = arg0->unk4;
    b = a->unk8;
    return b->v26(val);
}
