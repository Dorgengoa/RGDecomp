#include "types.h"
#pragma opt_common_subs off

extern void EffInstFreeParticles_19a7b0(void *, s32, void *);
extern s32 EffInstUpdate_19a8b0(void *, s32, f32, void *);
extern s32 EffDefHasInstances_19ab00(void *);
extern void EffInstStopEmitters_19ab10(void *, void *);
extern void EffInstResetRecords_19aba0(void *, void *);
extern void EffDefDestroy_1a0a90(void *, s32);
extern void EffInstDestroyByHandle_1a0b00(void *, s32);

void EffTableUpdate_1a0620(void *arg0, f32 fparg0) {
    s32 temp_16;
    u8 *var_20;
    u8 *var_19;
    s32 var_18;
    s32 var_17;
    s32 var_16;
    u8 *temp_23;
    u8 *var_16_2;
    s32 temp_3;
    s32 temp_22;

    temp_3 = *(s32 *)((u8 *)arg0 + 0x0) + 1;
    *(s32 *)((u8 *)arg0 + 0x0) = temp_3;
    if (temp_3 > 0x3fffffff) {
        *(s32 *)((u8 *)arg0 + 0x0) = 0;
    }
    temp_22 = *(s32 *)((u8 *)arg0 + 0x10);
    var_20 = *(u8 **)((u8 *)arg0 + 0x108);
    while (var_20 != NULL) {
        if (*(u8 *)(var_20 + 0x51) == 0) {
            var_19 = *(u8 **)(var_20 + 0x5C);
            while (var_19 != NULL) {
                temp_16 = *(s32 *)(var_19 + 0xC8);
                temp_23 = *(u8 **)(var_19 + 0xDC);
                var_17 = var_18 = 1;
                if (temp_16 != 0) {
                    if (temp_16 & 8) {
                        EffInstFreeParticles_19a7b0(var_20, temp_22, var_19);
                        EffInstResetRecords_19aba0(var_20, var_19);
                        *(s32 *)(var_19 + 0xC8) = *(s32 *)(var_19 + 0xC8) & ~8;
                        var_18 = 0;
                        if (*(s32 *)(var_20 + 0x78) > 0) {
                            *(s32 *)(var_19 + 0xC8) = *(s32 *)(var_19 + 0xC8) | 0x20;
                        }
                    }
                    if (temp_16 & 2) {
                        var_18 = 0;
                    }
                    if (temp_16 & 0x10) {
                        EffInstStopEmitters_19ab10(var_20, var_19);
                        *(s32 *)(var_19 + 0xC8) = *(s32 *)(var_19 + 0xC8) & ~0x10;
                    }
                    if (temp_16 & 0x20) {
                        var_17 += *(s32 *)(var_20 + 0x78);
                        *(s32 *)(var_19 + 0xC8) = *(s32 *)(var_19 + 0xC8) & ~0x20;
                    }
                }
                if (var_18 != 0) {
                    for (var_16 = 0; var_16 < var_17; var_16++) {
                        if (EffInstUpdate_19a8b0(var_20, temp_22, fparg0, var_19) != 0) {
                            continue;
                        }
                        *(s32 *)(var_19 + 0xCC) = *(s32 *)(var_19 + 0xCC) | 0x10000;
                        if (*(s32 *)(var_19 + 0xC8) & 4) {
                            EffInstDestroyByHandle_1a0b00(arg0, *(s32 *)(var_19 + 0xE0));
                        }
                        break;
                    }
                }
                var_19 = temp_23;
            }
        }
        var_20 = *(u8 **)(var_20 + 0x58);
    }
    do {
        var_16_2 = *(u8 **)((u8 *)arg0 + 0x108);
        while (var_16_2 != NULL) {
            if ((*(u8*)(var_16_2 + 0x50) != 0) && (EffDefHasInstances_19ab00(var_16_2) == 0)) {
                EffDefDestroy_1a0a90(arg0, *(s32 *)(var_16_2 + 0x44));
                break;
            } else {
                var_16_2 = *(u8 **)(var_16_2 + 0x58);
            }
        }
    } while (var_16_2 != NULL);
}
