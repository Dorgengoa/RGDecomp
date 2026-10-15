#include "types.h"

class C_003D4BD0 {
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
    /* +0x040 */ virtual s32 v40(s32 a);
};

struct Rec_003D4BD0 {
    u8 pad000[0x14];
    s32 f14;
};

extern "C" Rec_003D4BD0 *D_004838E8;
extern "C" s32 CharaMgrPoolFindById_3a8c60(s32 n);

extern "C" s32 ItemGetHeldModelNameByCharaIdMaybe_3d4bd0(C_003D4BD0 *o)
{
    Rec_003D4BD0 *r;

    r = D_004838E8;
    if (r == 0) {
        return 0;
    }
    return o->v40(CharaMgrPoolFindById_3a8c60(r->f14));
}
