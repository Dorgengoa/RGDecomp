#include "types.h"
typedef struct { s32 a, b; } E8_2cadb0;
struct U2cadb0 {
    virtual void *v0();
    virtual void *v1();
    virtual void *v2();
    virtual void *v3();
    virtual void *v4();
    virtual void *v5();
    virtual void *v6();
    virtual void *v7();
    virtual void *v8();
    virtual void *v9();
    virtual void *v10();
    virtual void *v11();
    virtual void *v12();
    virtual void *v13();
    virtual void *v14();
    virtual s32 v15();
};
struct C2cadb0 { u8 pad000[0x14]; s32 m14; };
extern "C" C2cadb0 * GetGameData_1fede0(void);
extern "C" s32 ScriptSlotGetInt_2cc9c0(E8_2cadb0 *);
extern "C" s32 CharaMgrPoolFindById_3a8c60(s32, s32);
extern "C" U2cadb0 * CharaFindSlotByRecId_3ad390(s32, s32);
extern "C" void ScriptSlotStoreIntRef_2cc900(E8_2cadb0 *, s32);

extern "C" s32 AiCmdCharaHasActivatableSlot_2cadb0(E8_2cadb0 *p0)
{
    C2cadb0 *ctx;
    s32 a;
    s32 b;
    s32 ok;
    s32 r;
    U2cadb0 *o;

    ctx = GetGameData_1fede0();
    a = ScriptSlotGetInt_2cc9c0(p0++);
    b = ScriptSlotGetInt_2cc9c0(p0++);
    ok = 0;
    r = CharaMgrPoolFindById_3a8c60(ctx->m14, a);
    if (r != 0) {
        o = CharaFindSlotByRecId_3ad390(r, b);
        if (o != 0) {
            if (o->v15() != 0) {
                ok = 1;
            }
        }
    }
    ScriptSlotStoreIntRef_2cc900(p0, ok);
    return 1;
}
