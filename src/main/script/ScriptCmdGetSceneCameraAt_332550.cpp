#include "types.h"

struct Buf_00332550 {
    u8 d[0x10];
};

class C_00332550 {
    u8 pad000[0xC0];
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
    /* +0x044 */ virtual void s044();
    /* +0x048 */ virtual void s048();
    /* +0x04C */ virtual void s04C();
    /* +0x050 */ virtual void s050();
    /* +0x054 */ virtual void s054();
    /* +0x058 */ virtual void s058();
    /* +0x05C */ virtual void s05C();
    /* +0x060 */ virtual void s060();
    /* +0x064 */ virtual void s064();
    /* +0x068 */ virtual void s068();
    /* +0x06C */ virtual void s06C();
    /* +0x070 */ virtual void s070();
    /* +0x074 */ virtual void s074();
    /* +0x078 */ virtual void s078();
    /* +0x07C */ virtual void s07C();
    /* +0x080 */ virtual void s080();
    /* +0x084 */ virtual void s084();
    /* +0x088 */ virtual void s088();
    /* +0x08C */ virtual void s08C();
    /* +0x090 */ virtual void s090();
    /* +0x094 */ virtual void s094();
    /* +0x098 */ virtual void s098();
    /* +0x09C */ virtual void s09C();
    /* +0x0A0 */ virtual void s0A0();
    /* +0x0A4 */ virtual void s0A4();
    /* +0x0A8 */ virtual void vA8(Buf_00332550 *b);
};

struct G_00332550;
struct Obj_00332550;

extern "C" G_00332550 *GetCurrentScene_1f5be0(void);
extern "C" C_00332550 *ObjRecGetLiveObject_1c3bc0(G_00332550 *g, s32 n);
extern "C" void ScriptSlotStoreVec3_334790(Obj_00332550 *o, Buf_00332550 *b);

extern "C" s32 ScriptCmdGetSceneCameraAt_332550(Obj_00332550 *o, s32 mode)
{
    G_00332550 *g;
    C_00332550 *t;
    Buf_00332550 b;

    if (mode != 3) {
        return 0;
    }
    g = GetCurrentScene_1f5be0();
    if (g == 0) {
        return 0;
    }
    t = ObjRecGetLiveObject_1c3bc0(g, 1);
    if (t == 0) {
        return 0;
    }
    t->vA8(&b);
    ScriptSlotStoreVec3_334790(o, &b);
    return 1;
}
