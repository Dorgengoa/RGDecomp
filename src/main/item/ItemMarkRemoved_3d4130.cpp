#include "types.h"

struct Bits_003D4130 {
    u8 b0 : 1;
    u8 b1 : 1;
    u8 r : 6;
};

class C_003D4130 {
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
    /* +0x02C */ virtual void v2C();
};

extern "C" s32 ItemIsUnheldFlaggedMaybe_3d4420(void);

extern "C" s32 ItemMarkRemoved_3d4130(C_003D4130 *o, s32 x)
{
    if (x == 0) {
        if (ItemIsUnheldFlaggedMaybe_3d4420() == 0) {
            return 0;
        }
    }
    ((Bits_003D4130 *)((u8 *)o + 0xA))->b1 = 1;
    o->v2C();
    return 1;
}
