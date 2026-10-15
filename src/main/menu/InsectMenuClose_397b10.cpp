#include "types.h"

/* vptr-at-offset-0x1B0 virtual call, slot +0x58 -> index (0x58-8)/4 = 20;
   "this" is D_00483518 itself, no explicit extra argument (m2c's
   `unk58(D_00483518)` is its usual mis-spelling of an implicit `this`). */

class V {
    u8 pad000[0x1B0];
public:
    virtual void slot008();
    virtual void slot00C();
    virtual void slot010();
    virtual void slot014();
    virtual void slot018();
    virtual void slot01C();
    virtual void slot020();
    virtual void slot024();
    virtual void slot028();
    virtual void slot02C();
    virtual void slot030();
    virtual void slot034();
    virtual void slot038();
    virtual void slot03C();
    virtual void slot040();
    virtual void slot044();
    virtual void slot048();
    virtual void slot04C();
    virtual void slot050();
    virtual void slot054();
    virtual void slot058();
};

extern "C" void NameTableFreeGroup_158ac0(s32 arg0, s32 arg1);
extern "C" void DrawCtxVif1HandlerStop_15dc40(void);
extern "C" s32 GetDrawCtxNameTable_15de40(void);
extern "C" void PadClearStickDpadThreshold_183940(void *arg0);
extern "C" void PadClearRepeatAll_183960(void *arg0);
extern "C" void ModelObjExEffectsStopAll_1b0870(V *arg0);
extern "C" s32 GetMenuResGroup_206a40(void);
extern "C" void InsectMenuReleaseRes_398360(void);
extern "C" void ResGroupUnloadGroup_42b650(s32 arg0, s32 arg1);

extern "C" s16 D_0047FF40;
extern "C" s16 D_0047FF4C;
extern "C" s16 D_0047FF50;
extern "C" s16 D_0047FF54;
extern "C" s16 D_00483500;
extern "C" s16 D_00483504;
extern "C" s16 D_00483508;
extern "C" V *D_00483518;
extern "C" s32 D_00483530;
extern "C" s32 D_00483534;
extern "C" u8 D_004B2570[];

extern "C" void InsectMenuClose_397b10(void)
{
    InsectMenuReleaseRes_398360();
    PadClearRepeatAll_183960(D_004B2570);
    PadClearStickDpadThreshold_183940(D_004B2570);
    D_00483530 = 0;
    D_0047FF40 = 1;
    D_00483534 = 0;
    D_0047FF50 = -1;
    D_0047FF4C = -1;
    D_0047FF54 = -1;
    D_00483504 = 0;
    D_00483500 = 0;
    D_00483508 = 0;
    if (D_00483518 != NULL) {
        DrawCtxVif1HandlerStop_15dc40();
        ModelObjExEffectsStopAll_1b0870(D_00483518);
        D_00483518->slot058();
        NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), 0x32E);
        D_00483518 = (V *)0;
    }
    ResGroupUnloadGroup_42b650(GetMenuResGroup_206a40(), 2);
}
