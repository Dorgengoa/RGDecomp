/* rgp:protos */
#define RGP_SELF_EffDefDestroyInstancesByTag_19ff40 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

/*rgp*/
extern s32 EffInstDestroyByHandle_1a0b00(void *arg0, s32 arg1);
extern void **HandleTableGet_1a1d50(s32 arg0, int);

void EffDefDestroyInstancesByTag_19ff40(void *arg0, s32 arg1,s32 arg2)
{
    volatile s32 sp4C;
    void **temp_2;
    void *temp_3;
    void *temp_4;
    void *temp_4_2;
    void *var_16;
    void *var_18;

    sp4C = arg1;
    temp_2 = HandleTableGet_1a1d50((s32)((u8 *)arg0 + 0xB0), (int)arg1);
    if (temp_2 != NULL) {
        var_16 = *temp_2;
    } else {
        var_16 = NULL;
    }
    if (var_16 != NULL) {
        var_18 = *(void **)((u8 *)var_16 + 0x5C);
        while (var_18 != NULL) {
            if (*(s32 *)((u8 *)var_18 + 0xD0) == arg2) EffInstDestroyByHandle_1a0b00(arg0, *(s32 *)((u8 *)var_18 + 0xE0));
            var_18 = *(void **)((u8 *)var_18 + 0xDC);
        }
        if (((unsigned char)EffDefHasInstances_19ab00(var_16)) != 0) return;
        if ((*(void **)((u8 *)arg0 + 0x108) == var_16) ||
            (*(void **)((u8 *)var_16 + 0x58) != NULL) ||
            (*(void **)((u8 *)var_16 + 0x54) != NULL)) {
            temp_4 = *(void **)((u8 *)var_16 + 0x54);
            if (temp_4 == NULL) {
                temp_3 = *(void **)((u8 *)var_16 + 0x58);
                if (temp_3 != NULL) {
                    *(void **)((u8 *)temp_3 + 0x54) = NULL;
                }
                *(void **)((u8 *)arg0 + 0x108) = *(void **)((u8 *)var_16 + 0x58);
            } else {
                *(void **)((u8 *)temp_4 + 0x58) = *(void **)((u8 *)var_16 + 0x58);
                temp_4_2 = *(void **)((u8 *)var_16 + 0x58);
                if (temp_4_2 != NULL) {
                    *(void **)((u8 *)temp_4_2 + 0x54) = *(void **)((u8 *)var_16 + 0x54);
                }
            }
            *(void **)((u8 *)var_16 + 0x58) = NULL;
            *(void **)((u8 *)var_16 + 0x54) = NULL;
        }
    }
}
