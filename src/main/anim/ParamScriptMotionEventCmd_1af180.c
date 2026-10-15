/* PARK (round 1): length 0x16C vs retail 0x17C; raw-stack struct layout guessed. */
#include "types.h"

#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern s32 SlotGetInt_15f720(s32);
extern s32 ArchiveGetFileDataEx_181d40(s32, s32, s32 *, s32 *);
extern void MotionEventCfgParse_1b45c0(void *, s32 *, s32);
extern void MotionEventListBindHandlers_1b4700(void *, s32 *);
extern void *memset(void *, s32, s32);
extern s32 D_0049D450[4];
extern s32 D_0049D45C[4];
extern void *D_0049D4E0[4];
extern s32 D_0049D4E4[4];
extern s32 D_0049D4E8[4];

s32 ParamScriptMotionEventCmd_1af180(s32 arg0, s32 arg1)
{
    s32 spFC;
    s32 spF8;
    s32 sp[0x30 / 4];
    s32 sp90[0x30 / 4];
    s32 temp_17;
    s32 temp_23;
    s32 temp_2;
    s32 temp_2_2;
    s32 var_20;
    s32 var_19;
    void *temp_18;

    temp_18 = D_0049D4E0[0];
    temp_17 = D_0049D45C[0];
    if (temp_18 == NULL || temp_17 == 0) {
        return 0;
    }
    {
        temp_23 = D_0049D450[0];
        var_20 = 0;
        while (var_20 < arg1) {
            temp_2 = SlotGetInt_15f720(arg0 + (var_20 * 8));
            var_19 = temp_2;
            spF8 = 0;
            temp_2_2 = ArchiveGetFileDataEx_181d40(temp_23, temp_2, &spFC, &spF8);
            if (temp_2_2 != 0) {
                if (spF8 != 0) {
                    var_19 = spF8;
                }
                memset(sp, 0, 0x30);
                sp[2] = temp_17;
                sp[4] = var_19;                       /* spD0 */
                sp[0] = D_0049D4E8[0];                    /* spC0 */
                sp[5] = temp_2_2;                      /* spD4 */
                sp[1] = D_0049D4E4[0];                    /* spC4 */
                *(void **)&sp[3] = (u8 *)temp_18 + 0x1F0; /* spCC */
                sp[6] = spFC;                          /* spD8 */
                MotionEventCfgParse_1b45c0((u8 *)temp_18 + 0x568, sp, D_0049D4E8[0]);
            }
            var_20 += 1;
        }
        *(void **)((u8 *)temp_18 + 0x574) = temp_18;
        *(void **)((u8 *)temp_18 + 0x57C) = temp_18;
        *(void **)((u8 *)temp_18 + 0x584) = temp_18;
        *(void **)((u8 *)temp_18 + 0x58C) = temp_18;
        memset(sp90, 0, 0x30);
        *(void **)&sp90[7] = (u8 *)temp_18 + 0x570; /* spAC */
        *(void **)&sp90[8] = (u8 *)temp_18 + 0x578; /* spB0 */
        *(void **)&sp90[9] = (u8 *)temp_18 + 0x580; /* spB4 */
        *(void **)&sp90[10] = (u8 *)temp_18 + 0x588; /* spB8 */
        MotionEventListBindHandlers_1b4700((u8 *)temp_18 + 0x568, sp90);
        return 1;
    }
    return 0;
    return 0;
}
