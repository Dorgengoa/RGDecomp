/* rgp:protos */
#define RGP_SELF_CharaGetCollWidth_238640 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S00238640_inner {
    u8 pad0[0x4C8];
    f32 unk4C8;
} S00238640_inner;

typedef struct S00238640 {
    u8 pad0[0x3F4];
    S00238640_inner *unk3F4;
} S00238640;

extern u8 D_0045B080[0x400];
extern f32 D_0047DB14 __attribute__((section(".sdata")));
extern f32 D_0047DB50;

f32 CharaGetCollWidth_238640(S00238640 *arg0)
{
    S00238640_inner *other;
    f32 a;
    f32 b;

    a = 2.0f * (D_0047DB50 * (*(f32 *)D_0045B080));
    other = arg0->unk3F4;
    if (other != NULL) {
        b = 2.0f * (other->unk4C8 * (D_0047DB14 * (*(f32 *)D_0045B080)));
    } else {
        b = 0.0f;
    }
    if (b > a) {
        return b;
    }
    b = a;
    return b;
}
