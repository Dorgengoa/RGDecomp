#include "types.h"

/* 0x38 is read two ways: an explicit (u32)(h38 & 0x3FFF) >> 5 off a u16
   (andi/srl -- the (u32) is what makes it srl and not sra), and u64
   bitfields (dsll32/dsrl32 pairs; ld for the field that straddles bit 16,
   lhu 0x3A for the one that does not). */
struct Bits {
    u64 b00 : 14;
    u64 b14 : 6;
    u64 b20 : 6;
};

union U38 {
    u16 h38;
    struct Bits f;
};

struct Obj1 {
    u8  pad000[4];
    s16 m04;
    u8  pad006[0x32];
    union U38 u38;
};

struct Obj0 {
    u8   pad000[0x270];
    void *m270;
};

extern void DrawEnvSetZbuf_157520(void *, s32, s32, s32, s32);

void DrawEnvSetZbufFromDesc_144f70(struct Obj0 *p0, struct Obj1 *p1)
{
    if (p1 != 0) {
        DrawEnvSetZbuf_157520(p0->m270, ((u32)p1->u38.h38 & 0x3FFF) >> 5,
                     p1->u38.f.b14 << 6, p1->m04, p1->u38.f.b20);
    }
}
