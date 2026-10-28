/* rgp:protos */
#define RGP_SELF_NavGraphFinalize_30f700 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_loop_invariants off

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern f32 D_0045B080[4];
extern s8 D_00482968;

void NavGraphFinalize_30f700(void *arg0) {
    f32 spE0[4] __attribute__((aligned(16)));
    f32 spD0[4] __attribute__((aligned(16)));
    s32 temp_30;
    s32 var_22;
    s32 var_19;
    s32 spC0;
    u32 var_18;
    s32 var_17;
    s32 var_16;
    s32 spB0;
    s32 temp_23;
    s32 var_21;
    s32 var_19_2;
    s32 temp_21;
    f32 temp_f20;
    u16 *temp_2;
    u32 var_18_2;
    s32 temp_2_2;
    s32 temp_2_3;

    if (((unsigned char)NavGraphIsValid_311140((int)arg0)) != 0) {
        temp_30 = *(s32 *)((u8 *)arg0 + 0xC0);
        var_22 = 0;
        var_19 = NavGraphGetNodes_310cc0(arg0);
        spC0 = ((unsigned short)NavGraphGetNodeCount_310cb0(arg0));
        for (var_18 = 0; var_18 < (u32) spC0; var_18++, var_19 += 0x24) {
            var_17 = NavGraphGetEdges_310c10(arg0);
            var_16 = 0;
            spB0 = ((unsigned short)NavGraphGetEdgeCount_310c00(arg0));
            temp_23 = temp_30 + (var_22 * 2);
            for (var_21 = 0; var_21 < (u32) spB0; var_21++, var_17 += 0x14) {
                if ((var_18 == (u32) ((short)NavEdgeGetNodeA_311700(var_17))) || (var_18 == (u32) ((short)NavEdgeGetNodeB_3116f0(var_17)))) {
                    temp_2 = (u16 *)(temp_23 + (var_16 * 2));
                    var_16 += 1;
                    *temp_2 = var_21;
                }
            }
            NavNodeSetEdges_311870(var_19, temp_23, var_16);
            NavNodeResetDist_311820(var_19);
            var_22 += var_16;
        }
        var_19_2 = NavGraphGetEdges_310c10(arg0);
        temp_21 = ((unsigned short)NavGraphGetEdgeCount_310c00(arg0));
        var_18_2 = 0;
        temp_f20 = (f32) 0xF4240 * D_0045B080[0];
        for (; var_18_2 < (u32) temp_21; var_18_2++, var_19_2 += 0x14) {
            NavEdgeSetBothDirFlags_311590(var_19_2);
            if (D_00482968 == 0) {
                NavEdgeSetCost_311640(var_19_2, temp_f20);
                temp_2_2 = ((s32)NavGraphGetNode_310cd0(arg0, ((short)NavEdgeGetNodeA_311700(var_19_2))));
                if (temp_2_2 != 0) {
                    temp_2_3 = ((s32)NavGraphGetNode_310cd0(arg0, ((short)NavEdgeGetNodeB_3116f0(var_19_2))));
                    if (temp_2_3 != 0) {
                        Vec3ToVec4W1_311970(temp_2_2, spE0);
                        Vec3ToVec4W1_311970(temp_2_3, spD0);
                        NavEdgeSetCost_311640(var_19_2, VecDist_1cb420(spE0, spD0));
                    }
                }
            }
        }
        D_00482968 = 0;
        *(s16 *)((u8 *)arg0 + 0x10E) = -1;
        *(u8 *)((u8 *)arg0 + 0x111) = 0;
    }
}
