#include "types.h"

class C_00332620 {
    u8 pad000[0x190];
public:
    /* +0x008 */ virtual void s008();
    /* +0x00C */ virtual void s00C();
    /* +0x010 */ virtual void s010();
    /* +0x014 */ virtual void s014();
    /* +0x018 */ virtual void s018();
    /* +0x01C */ virtual void s01C();
    /* +0x020 */ virtual void s020();
    /* +0x024 */ virtual void s024();
    /* +0x028 */ virtual void s028();
    /* +0x02C */ virtual void s02C();
    /* +0x030 */ virtual void s030();
    /* +0x034 */ virtual void s034();
    /* +0x038 */ virtual void s038();
    /* +0x03C */ virtual void s03C();
    /* +0x040 */ virtual void s040();
    /* +0x044 */ virtual s32 v44();
};

struct Obj_00332620;

extern "C" C_00332620 *D_004826E0;
extern "C" void ScriptSlotStoreIntRef_3347f0(Obj_00332620 *o, s16 v);

extern "C" s32 ScriptCmdEffectGetNextEntryId_332620(Obj_00332620 *o, s32 mode)
{
    s32 r;

    if (mode != 1) {
        return 0;
    }
    r = D_004826E0->v44();
    ScriptSlotStoreIntRef_3347f0(o, (s16)r);
    return 1;
}
