/* rgp:protos */
#define RGP_SELF_StatusEffectHitIconsUpdate_33c940 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off
#pragma opt_propagation on

/*rgp*/
/*rgp*/
/*rgp*/
extern volatile f32 D_0047DAA0 __attribute__((section(".sdata")));

typedef struct {f32 x,y,z,w;} Vec;
typedef struct {u8 pad[0x10];s16 type,pad2,id;u8 pad3[0x30-0x16];Vec v[6];f32 ages[6];} Obj;
void StatusEffectHitIconsUpdate_33c940(Obj *arg0)
{
    u8 *base;
    u8 *vecslot;
    f32 temp_f1;
    f32 temp_f1_2;
    s32 var_4;
    s32 var_4_2;
    s32 var_5;

    base = (u8 *)arg0;
    if ((arg0->type != 0) &&
        (((s32)ObjRecGetLiveObject_1c4a90(((s32)GetStaticScene_1c6c70()), arg0->id)) != 0)) {
        var_4 = 1;
        if (arg0->type == 1) {
            do {
                arg0->ages[var_4] = 0.0f;
                var_4 += 1;
            } while (var_4 < 6);
            arg0->v[0].x = (f32) (RandRangeFloat_1ca5d0(2.0f) - 1.0f);
            arg0->v[0].y = RandRangeFloat_1ca5d0(1.0f);
            arg0->v[0].z = (f32) (RandRangeFloat_1ca5d0(2.0f) - 1.0f);
            arg0->v[0].w = 1.0f;
            arg0->ages[0] = D_0047DAA0;
            arg0->type = 3;
        }
        if (arg0->type == 3) {
            var_5 = 0;
            do {
                temp_f1 = arg0->ages[var_5];
                if (!(temp_f1 <= 0.0f)) {
                    temp_f1 +=1.0f;temp_f1_2=temp_f1;
                    arg0->ages[var_5] = temp_f1_2;
                    if (!(temp_f1_2 < 9.0f)) {
                        arg0->ages[var_5] = 0.0f;
                    }
                }
                var_5 += 1;
            } while (var_5 < 6);
            var_4_2 = 0;
            while (var_4_2 < 6) {
                vecslot = base + var_4_2 * 0x10;
                if (arg0->ages[var_4_2] <= 0.0f) {
                    arg0->v[var_4_2].x = (f32) (RandRangeFloat_1ca5d0(2.0f) - 1.0f);
                    arg0->v[var_4_2].y = RandRangeFloat_1ca5d0(1.0f);
                    arg0->v[var_4_2].z = (f32) (RandRangeFloat_1ca5d0(2.0f) - 1.0f);
                    arg0->v[var_4_2].w = 1.0f;
                    arg0->ages[var_4_2] = D_0047DAA0;
                    return;
                }
                var_4_2 += 1;
            }
        }
    }
}
