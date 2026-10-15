#include "types.h"

class Obj {
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
    virtual s32 f5C();
};

struct G90 {
    u8 pad[0x10];
    s32 m10;
    s32 m14;
};
struct G94 {
    u8 pad[0x84];
    s32 m84;
};

extern "C" {
Obj *CharaMgrPoolFindById_3a8c60(s32 arg0, s32 arg1);
s32 StateGetChapter_3cd5b0(s32 arg0);
s32 SkillGetCharaStateMaybe_3e0df0(s32 arg0);
s32 SkillActionCreate_3e0f40(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 SkillDefFindMaybe_40ea70(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_00466810[8][8];
extern G90 *D_00483990;
extern G94 *D_00483994;
}

extern "C" s32 ComboSkillTriggerMaybe_3e0a50(s32 arg0, s32 arg1)
{
    Obj *o;
    s32 ta;
    s32 tb;
    s32 a;
    s32 b;
    s32 v;
    bool ok;
    s32 r;

    if (D_00483990 == NULL) {
        return 0;
    }
    o = CharaMgrPoolFindById_3a8c60(D_00483990->m14, arg0);
    if (o == NULL) {
        return 0;
    }
    ta = o->f5C();
    r = SkillGetCharaStateMaybe_3e0df0(arg0);
    if (r == 1 || r == 3) {
        return 0;
    }
    o = CharaMgrPoolFindById_3a8c60(D_00483990->m14, arg1);
    if (o == NULL) {
        return 0;
    }
    tb = o->f5C();
    a = ta - 0x2AF9;
    b = tb - 0x2AF9;
    if (a < 0 || a >= 8 || b < 0 || b >= 8) {
        return 0;
    }
    v = D_00466810[a][b];
    if (v < 0) {
        return 0;
    }
    ok = 1;
    if (StateGetChapter_3cd5b0(D_00483990->m10) == 1) {
        ok = 0;
    }
    if (StateGetChapter_3cd5b0(D_00483990->m10) < 3) {
        if (ta == 0x2AFE || tb == 0x2AFE) {
            ok = 0;
        }
    }
    if (!ok) {
        return 0;
    }
    if (SkillDefFindMaybe_40ea70(D_00483994->m84, -1, v) != 0) {
        return SkillActionCreate_3e0f40(-1, v, arg0, 0, 0);
    }
    return 0;
}
