#include "types.h"

struct Buf176 {
    f32 v[16];
};

class C176 {
    u8 pad000[0xC0];
public:
    /* +0x08 */ virtual void slot08();
    /* +0x0C */ virtual void slot0C();
    /* +0x10 */ virtual void slot10();
    /* +0x14 */ virtual void slot14();
    /* +0x18 */ virtual void slot18(Buf176 *b);
};

extern "C" f32 Atan2f_1291a8(f32 y, f32 x);

extern "C" f32 CameraGetYaw_176fa0(C176 *self)
{
    Buf176 b;

    self->slot18(&b);
    return Atan2f_1291a8(b.v[8], b.v[10]);
}
