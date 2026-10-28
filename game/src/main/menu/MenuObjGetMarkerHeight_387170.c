/* rgp:protos */
#define RGP_SELF_MenuObjGetMarkerHeight_387170 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

extern f32 D_0047D248;

f32 MenuObjGetMarkerHeight_387170(void *arg0) {
    u128 sp0 = *(u128 *)((u8 *)arg0 + 0x1A0);
    f32 inner;
    f32 spf;

    inner = D_0047D248 * *(f32 *)((u8 *)arg0 + 0x4CC);
    spf = *(f32 *)((u8 *)&sp0 + 4);
    return inner * spf;
}
