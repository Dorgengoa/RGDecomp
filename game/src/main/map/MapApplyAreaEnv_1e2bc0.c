/* rgp:protos */
#define RGP_SELF_MapApplyAreaEnv_1e2bc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Src {
    u8 pad[0x1A0];
    s32 x1A0;
    f32 x1A4;
    f32 x1A8;
    u8 x1AC;
    u8 x1AD;
    u8 x1AE;
    u8 pad1AF[9];
    f32 x1B8;
    f32 x1BC;
} Src;

/*rgp*/
/*rgp*/

void MapApplyAreaEnv_1e2bc0(u8 *arg0, s32 arg1, s32 arg2)
{
    Src *s;
    s32 k;

    s = ((Src *)MapGetAreaLightSetById_1e54d0(arg0, arg1, 0));
    if (s == NULL) {
        return;
    }
    *(s32 *)(arg0 + 0xCC) = arg1;
    if (s->x1A0 != 0) {
        MapEnvSlotsSetTarget_1e5e40(arg0 + 0x68, arg1, arg2, s->x1AC, s->x1AD, s->x1AE, s->x1A4, s->x1A8, s->x1B8, s->x1BC);
    } else {
        k = 60000;
        MapEnvSlotsSetTarget_1e5e40(arg0 + 0x68, arg1, arg2, 128.0f, 128.0f, 128.0f, 1.0f, k, 0.0f, 0.0f);
    }
}
