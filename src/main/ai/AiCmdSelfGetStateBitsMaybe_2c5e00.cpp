#include "types.h"

class V2C5E00 {
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
    virtual s32 f48();
};

extern "C" {
extern u8 *GetGameData_1fede0(void);
extern void ScriptSlotStoreIntRef_2cc900(s32, s32);
extern s32 ScriptSlotGetInt_2cc9c0(s32);
extern u8 *CharaMgrPoolFindById_3a8c60(s32, s32);
extern V2C5E00 *CharaFindSlotByRecId_3ad390(u8 *, s32);
extern s32 D_004DB928[0x10];
}

extern "C" s32 AiCmdSelfGetStateBitsMaybe_2c5e00(s64 *arg0)
{
    V2C5E00 *v;
    u32 *fl;
    s32 base;
    s32 i;
    u8 *o;

    o = CharaMgrPoolFindById_3a8c60(*(s32 *)(GetGameData_1fede0() + 0x14), D_004DB928[0]);
    if (o == 0) {
        return 0;
    }
    fl = (u32 *)(o + 0x238);
    if (fl == 0) {
        return 0;
    }
    switch (ScriptSlotGetInt_2cc9c0((s32)arg0++)) {
    case 0:
        ScriptSlotStoreIntRef_2cc900((s32)arg0, *fl & 3);
        break;
    case 1:
        ScriptSlotStoreIntRef_2cc900((s32)arg0, *fl & 0xC);
        break;
    case 2:
        ScriptSlotStoreIntRef_2cc900((s32)arg0, *fl & 0x30);
        break;
    case 3:
        ScriptSlotStoreIntRef_2cc900((s32)arg0, *fl & 0xC0);
        break;
    case 4:
        base = ScriptSlotGetInt_2cc9c0((s32)arg0++);
        for (i = 0; i < 3; i++) {
            v = CharaFindSlotByRecId_3ad390(o, base + i);
            if (v != 0) {
                ScriptSlotStoreIntRef_2cc900((s32)arg0, v->f48() & 0xFF);
                return 1;
            }
        }
        ScriptSlotStoreIntRef_2cc900((s32)arg0, 0);
        break;
    }
    return 1;
}
