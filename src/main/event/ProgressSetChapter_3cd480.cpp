#include "types.h"

class C_003CD480 {
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
    /* +0x070 */ virtual s32 v70(s16 a);
};

struct Sub_003CD480 {
    u8 pad000[0x8];
    C_003CD480 *f08;
};

struct Obj_003CD480 {
    u8 pad000[0x4];
    Sub_003CD480 *f04;
    s16 f08;
};

extern "C" void ProgressReapplyChapter_3cd330(Obj_003CD480 *o, s32 n);

extern "C" s32 ProgressSetChapter_3cd480(Obj_003CD480 *o, s32 x)
{
    if (o->f04->f08->v70((s16)x) == 0) {
        return 0;
    }
    if (o->f08 == x) {
        return 1;
    }
    o->f08 = (s16)x;
    ProgressReapplyChapter_3cd330(o, 1);
    return 1;
}
