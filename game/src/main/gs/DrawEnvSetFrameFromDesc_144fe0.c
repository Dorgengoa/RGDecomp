/* rgp:protos */
#define RGP_SELF_DrawEnvSetFrameFromDesc_144fe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* 0x38 is read two ways: an explicit (u32)(h38 & 0x3FFF) >> 5 off a u16
   (andi/srl -- the (u32) is what makes it srl and not sra), and u64
   bitfields (dsll32/dsrl32 pairs; ld for the field that straddles bit 16,
   lhu 0x3A for the one that does not). */
struct Bits {
    __extension__ unsigned int b00 : 14;
    unsigned int b14 : 6;
    unsigned int b20 : 6;
} __attribute__((aligned(8)));

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

/*rgp*/

void DrawEnvSetFrameFromDesc_144fe0(struct Obj0 *p0, struct Obj1 *p1, s32 p2)
{
    if (p1 != 0) {
        DrawEnvSetFrame_1575e0(p0->m270, ((u32)p1->u38.h38 & 0x3FFF) >> 5,
                     p1->u38.f.b14 << 6, p1->m04, p1->u38.f.b20, p2);
    }
}
