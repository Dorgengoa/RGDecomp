/* rgp:protos */
#line 1
#include "types.h"

struct Buf176 {
    f32 v[16];
};

class C176 {
    u8 pad000[0xC0];
public:
    /* +0x08 */ VC_VPTR_MEMBER;
    /* +0x0C */ 
    /* +0x10 */ 
    /* +0x14 */ 
    /* +0x18 */ void slot18(Buf176 *b, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { VCM(void, (void *, Buf176 *, int, int), 0x18, b, rgp_fwd2, rgp_fwd3); }
};

extern "C" f32 Atan2f_1291a8(f32 y, f32 x);

extern "C" f32 CameraGetYaw_176fa0(C176 *self, int rgp_a1, int rgp_a2, int rgp_a3)
{
    Buf176 b __attribute__((aligned(16)));

    self->slot18(&b, (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    return Atan2f_1291a8(b.v[8], b.v[10]);
}
