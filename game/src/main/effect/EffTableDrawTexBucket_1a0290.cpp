/* rgp:protos */
#line 1
#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

extern void DrawListGetStats_148940(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4);
extern s32 GetDrawCtx_15de80(void);
extern void ***HandleTableGet_1a3200(void *arg0, s32 arg1);
extern s32 *HandleTableGet_1a3580(void *arg0, s32 arg1, void *arg2);
extern void EffTexResApplyAnimMaybe_1a8410(s32 arg0, s32 arg1);
extern void EffTexResStepAnim_1a8460(s32 arg0, s32 arg1);

class VC_0 {
public:
    VC_VPTR_MEMBER;
    void f(s32 x0, void * x1, void * x2) { VCM(void, (void *, s32, void *, void *), 0xC, x0, x1, x2); }
};
void EffTableDrawTexBucket_1a0290(void *arg0, s32 arg1, f32 fparg0)
{
    void *var_19;
    s32 sp6C;
    s32 sp68;
    s32 sp64;
    s32 sp60;
    s32 *temp_2;
    s32 temp_18;
    s32 var_17;
    s32 var_4;
    void ***temp_2_2;
    void ***temp_2_3;
    void **var_17_2;
    void **var_4_2;
    void *temp_6;

    temp_6 = *(void **)((u8 *)arg0 + 0x10C);
    if (temp_6 != NULL) {
        var_4 = arg1 - *(s32 *)((u8 *)arg0 + 0x114);
        if ((var_4 < 0) || (var_4 >= *(s32 *)((u8 *)arg0 + 0x110))) {
            var_4 = -1;
        }
        if ((var_4 >= 0) &&
            (var_19 = *(void **)((u8 *)(*(void **)((u8 *)temp_6 + 0x8)) + ((arg1 - *(s32 *)((u8 *)temp_6 + 0x4)) * 4)),
             (var_19 != NULL))) {
            if (var_19 != NULL) {
                temp_2 = HandleTableGet_1a3580((u8 *)arg0 + 0x48, *(s32 *)((u8 *)var_19 + 0xC), temp_6);
                if (temp_2 != NULL) {
                    var_17 = *temp_2;
                } else {
                    var_17 = 0;
                }
                if (var_17 != 0) {
                    EffTexResStepAnim_1a8460(var_17, *(s32 *)((u8 *)arg0 + 0x0));
                    EffTexResApplyAnimMaybe_1a8410(var_17, *(s32 *)((u8 *)arg0 + 0x4));
                }
            }
            if (fparg0 < 1.0f) {
                temp_18 = GetDrawCtx_15de80();
                while (var_19 != NULL) {
                    temp_2_2 = HandleTableGet_1a3200((u8 *)arg0 + 0x14, *(s32 *)((u8 *)var_19 + 0x8));
                    if (temp_2_2 != NULL) {
                        var_17_2 = *temp_2_2;
                    } else {
                        var_17_2 = NULL;
                    }
                    if (var_17_2 != NULL) {
                        DrawListGetStats_148940(temp_18, &sp6C, &sp68, &sp64, &sp60);
                        if (!((f32) sp68 < (fparg0 * (f32) sp60))) {
                            return;
                        }
                        ((VC_0 *)(var_17_2))->f(*(s32 *)((u8 *)var_19 + 0x4), (u8 *)var_19 + 0x10, (u8 *)var_19 + 0x60);
                    }
                    var_19 = *(void **)((u8 *)var_19 + 0x0);
                }
            } else {
                while (var_19 != NULL) {
                    temp_2_3 = HandleTableGet_1a3200((u8 *)arg0 + 0x14, *(s32 *)((u8 *)var_19 + 0x8));
                    if (temp_2_3 != NULL) {
                        var_4_2 = *temp_2_3;
                    } else {
                        var_4_2 = NULL;
                    }
                    if (var_4_2 != NULL) {
                        ((VC_0 *)(var_4_2))->f(*(s32 *)((u8 *)var_19 + 0x4), (u8 *)var_19 + 0x10, (u8 *)var_19 + 0x60);
                    }
                    var_19 = *(void **)((u8 *)var_19 + 0x0);
                }
            }
        }
    }
}

}
