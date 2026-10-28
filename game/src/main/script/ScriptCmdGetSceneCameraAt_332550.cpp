#include "types.h"

struct Buf_00332550 {
    u8 d[0x10];
};

class C_00332550 {
    u8 pad000[0xC0];
public:
    /* +0x008 */ VC_VPTR_MEMBER;
    /* +0x00C */ 
    /* +0x010 */ 
    /* +0x014 */ 
    /* +0x018 */ 
    /* +0x01C */ 
    /* +0x020 */ 
    /* +0x024 */ 
    /* +0x028 */ 
    /* +0x02C */ 
    /* +0x030 */ 
    /* +0x034 */ 
    /* +0x038 */ 
    /* +0x03C */ 
    /* +0x040 */ 
    /* +0x044 */ 
    /* +0x048 */ 
    /* +0x04C */ 
    /* +0x050 */ 
    /* +0x054 */ 
    /* +0x058 */ 
    /* +0x05C */ 
    /* +0x060 */ 
    /* +0x064 */ 
    /* +0x068 */ 
    /* +0x06C */ 
    /* +0x070 */ 
    /* +0x074 */ 
    /* +0x078 */ 
    /* +0x07C */ 
    /* +0x080 */ 
    /* +0x084 */ 
    /* +0x088 */ 
    /* +0x08C */ 
    /* +0x090 */ 
    /* +0x094 */ 
    /* +0x098 */ 
    /* +0x09C */ 
    /* +0x0A0 */ 
    /* +0x0A4 */ 
    /* +0x0A8 */ void vA8(Buf_00332550 *b) { VCM(void, (void *, Buf_00332550 *), 0xA8, b); }
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
    Buf_00332550 b __attribute__((aligned(16)));

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
