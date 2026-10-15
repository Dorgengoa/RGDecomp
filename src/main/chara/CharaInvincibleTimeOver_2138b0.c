#include "types.h"

struct Obj0;

struct Obj0 {
    u8 pad000[0xAE0];
    f32 mAE0;
};

s32 CharaInvincibleTimeOver_2138b0(struct Obj0 *p0)
{
    return p0->mAE0 <= 0.0f;
}
