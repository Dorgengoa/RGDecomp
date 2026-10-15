#include "types.h"

class Obj {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5C();

    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    u8 unk14[0x64];
    s16 unk78;
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 pad7B;
    u8 pad7C[4];
    s16 unk80;

    void reset();
};

extern "C" void MemStackInit_14d810(void *, s32, s32);
extern s16 D_004830FC;

extern "C" void DataTableReset_368f70(Obj *arg0)
{
    D_004830FC = 0;
    arg0->unkC = 0;
    arg0->unk10 = 0;
    MemStackInit_14d810(arg0->unk14, 0, 0);
    arg0->unk78 = 0;
    arg0->unk8 = 0;
    arg0->b0 = 0;
    arg0->unk80 = 4;
    arg0->unk4 = 0;
    arg0->b1 = 0;
    arg0->b2 = 0;
    arg0->v20();
    arg0->v5C();
}
