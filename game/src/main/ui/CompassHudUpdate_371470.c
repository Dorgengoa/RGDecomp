/* rgp:protos */
#define RGP_SELF_CompassHudUpdate_371470 1
#define RGP_SELF_clr 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x, y, z, w; } V371470;

/*rgp*/
/*rgp*/

static inline void clr(void *d, s32 n)
{
    u8 *p = (u8 *)d;
    if (p != NULL) {
        do {
            *p = 0;
            n -= 1;
            p += 1;
        } while (n != 0);
    }
}

void CompassHudUpdate_371470(u8 *arg0) {
    f32 temp_f1;
    s32 h;
    f32 f;
    f = *(f32 *)(arg0 + 0x18);
    temp_f1 = *(f32 *)(arg0 + 0x1C) + f;
    *(f32 *)(arg0 + 0x1C) = temp_f1;
    if (temp_f1 < 0.0f) {
        *(f32 *)(arg0 + 0x1C) = 0.0f;
    }
    if (!(*(f32 *)(arg0 + 0x1C) <= 1.0f)) {
        *(f32 *)(arg0 + 0x1C) = 1.0f;
    }
    if ((*(f32 *)(arg0 + 0x1C) <= 0.0f) && (*(f32 *)(arg0 + 0x18) < 0.0f)) {
        *(f32 *)(arg0 + 0x18) = 0.0f;
    }
    if (!(*(f32 *)(arg0 + 0x1C) < 1.0f) && !(*(f32 *)(arg0 + 0x18) <= 0.0f)) {
        *(f32 *)(arg0 + 0x18) = 0.0f;
    }
    h = *(s32 *)(arg0 + 0);
    if (h != 0) {
        f = *(f32 *)(arg0 + 0x10);
        {
            V371470 a __attribute__((aligned(16))) = {0};
            a.y = f;
            a.x = 0.0f;
            a.z = 0.0f;
            ModelSetRot_151080(h, &a);
        }
    }
    h = *(s32 *)(arg0 + 0xC);
    if (h != 0) {
        f = *(f32 *)(arg0 + 0x14);
        {
            V371470 b __attribute__((aligned(16))) = {0};
            b.y = f;
            b.x = 0.0f;
            b.z = 0.0f;
            FrameSetRot_14a390(h, &b);
        }
    }
}
