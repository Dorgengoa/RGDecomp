/* rgp:protos */
#define RGP_SELF_AmixerCfgTransCmd_16fe80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj0 { u8 pad000[0x8]; s32 m08; s32 m0C; };
extern struct Obj0 * D_00481188;
extern s32 D_00481190;
extern s32 D_0048119C;

s32 AmixerCfgTransCmd_16fe80(void)
{
    s32 i;
    s32 v;
    struct Obj0 *t1;

    i = D_0048119C;
    t1 = D_00481188;
    if (i < 0) {
        goto zero;
    }
    if (i < t1->m08) {
        goto ok;
    }
zero:
    v = 0;
    goto join;
ok:
    v = t1->m0C + (i * 20);
join:
    D_00481190 = v;
    if (v == 0) {
        return 0;
    }
    D_0048119C = D_0048119C + 1;
    return 1;
}
