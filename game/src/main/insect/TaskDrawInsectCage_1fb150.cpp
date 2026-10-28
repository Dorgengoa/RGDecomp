#include "types.h"

struct Buf_001FB150 {
    u8 d[0x10];
};

class C_001FB150 {
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
    /* +0x0A4 */ void vA4(Buf_001FB150 *b) { VCM(void, (void *, Buf_001FB150 *), 0xA4, b); }
};

struct Glob_001FB150 {
    u8 pad000[0x4344];
    s32 f4344;
};

extern "C" u8 D_004B8700[];
extern "C" Glob_001FB150 *GetCurrentScene_1f5be0(void);
extern "C" C_001FB150 *ObjRecGetLiveObject_1c3bc0(Glob_001FB150 *g, s32 n);
extern "C" void InsectCageMgrDraw_39a420(const u8 *p, Buf_001FB150 *b);

extern "C" void TaskDrawInsectCage_1fb150(void)
{
    Glob_001FB150 *g;
    C_001FB150 *t;
    Buf_001FB150 b __attribute__((aligned(16)));

    g = GetCurrentScene_1f5be0();
    t = ObjRecGetLiveObject_1c3bc0(g, g->f4344);
    if (t == 0) {
        return;
    }
    t->vA4(&b);
    InsectCageMgrDraw_39a420(D_004B8700, &b);
}
