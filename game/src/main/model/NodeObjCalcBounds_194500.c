/* rgp:protos */
#define RGP_SELF_NodeObjCalcBounds_194500 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"
#pragma optimization_level 3

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

typedef struct O194 {
    u8 pad[0xB0];
    u128 vB0;
    u128 vC0;
    u128 vD0;
    u128 vE0;
    u128 vF0;
    u128 v100;
} O194;

s32 NodeObjCalcBounds_194500(void *arg0)
{
    O194 *o = (O194 *)arg0;
    u128 buf[2];
    void *node;
    s32 var_18;
    s32 var_17;
    s32 temp_16;

    var_18 = 0;
    node = *(void **)((u8 *)arg0 + 0x94);
    var_17 = 0;
    while (node != NULL) {
        temp_16 = *(s32 *)((u8 *)node + 0x10);
        if (temp_16 != 0) {
            if (NodeObjBasicCalcModelBounds_196ce0(temp_16, buf) != 0) {
                if (var_18 == 0) {
                    var_18 = 1;
                    *(u128 *)((u8 *)arg0 + 0xB0) = buf[0];
                    *(u128 *)((u8 *)arg0 + 0xC0) = buf[1];
                } else {
                    BBoxUnion_13dea0((u8 *)arg0 + 0xB0, buf);
                }
            }
            if (NodeObjBasicCalcCollBounds_196c40(temp_16, buf) != 0) {
                if (var_17 == 0) {
                    var_17 = 1;
                    *(u128 *)((u8 *)arg0 + 0xE0) = buf[0];
                    *(u128 *)((u8 *)arg0 + 0xF0) = buf[1];
                } else {
                    BBoxUnion_13dea0((u8 *)arg0 + 0xE0, buf);
                }
            }
        }
        node = *(void **)((u8 *)node + 0x0);
    }
    VecAdd_13be20((u8 *)arg0 + 0xD0, (u8 *)arg0 + 0xC0, (u8 *)arg0 + 0xB0);
    VecScale_13be00(&o->vD0, &o->vD0, 0.5f);
    *(f32 *)((u8 *)arg0 + 0xDC) = 0.5f * VecDistance_13d3d0((void *)((s32)arg0 + 0xC0), (void *)((s32)arg0 + 0xB0));
    VecAdd_13be20((u8 *)arg0 + 0x100, (u8 *)arg0 + 0xF0, (u8 *)arg0 + 0xE0);
    VecScale_13be00(&o->v100, &o->v100, 0.5f);
    *(f32 *)((u8 *)arg0 + 0x10C) = 0.5f * VecDistance_13d3d0((void *)((s32)arg0 + 0xF0), (void *)((s32)arg0 + 0xE0));
    *(s32 *)((u8 *)arg0 + 0xA8) = var_18;
    *(s32 *)((u8 *)arg0 + 0xAC) = var_17;
    return var_18 | var_17;
}
