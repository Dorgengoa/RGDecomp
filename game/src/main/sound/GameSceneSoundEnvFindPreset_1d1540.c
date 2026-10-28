/* rgp:protos */
#define RGP_SELF_GameSceneSoundEnvFindPreset_1d1540 1
#include "port/game_protos.h"
#line 1
#include "types.h"
struct Obj0 { u8 pad000[0x5E18]; s32 m5E18; };
s32 GameSceneSoundEnvFindPreset_1d1540(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s32 l1;
    s32 l0;
    s32 mid;
    s16 t1;
    s16 t2;
    s32 off;
    u8 *e;
    t0 = p0->m5E18;
    l0 = (t0 + -1);
    l1 = 0;
    while (l1 < l0) {
        mid = (l1 + l0) / 2;
        t1 = *(s16 *)((u8 *)p0 + mid * 36 + 0x5E1C);
        if (t1 < p1) {
            l1 = mid + 1;
        } else {
            l0 = mid;
        }
    }
    off = l1 * 36;
    e = (u8 *)(off + (s32)p0);
    t2 = *(s16 *)(e + 0x5E1C);
    if (t2 != p1) {
        return 0;
    }
    return (s32)(e + 0x5E1C);
}
