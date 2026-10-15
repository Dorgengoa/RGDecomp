#include "types.h"

struct V {u8 pad0[6];s16 flags;u8 pad[0x188];virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual u8 *get();};
extern "C" {
extern void NameTableFreeGroup_158ac0(s32, s16);
extern void DrawCtxVif1HandlerStop_15dc40(void);
extern s32 GetDrawCtxNameTable_15de40(void);
extern void MotionListGetPlayerState_1723a0(s32 *, s32, void *);
extern void EffectEntryReset_2dc550(void *);

typedef struct {
    void *unk0;
    void *unk4;
    s32 unk8;
    u8 padC[0x8];
    s16 unk14;
    u8 pad16[0xa0];
    s16 unkB6;
} T2d95f0_arg0;

void EffectEntryUpdateRelease_2d95f0(T2d95f0_arg0 *arg0)
{
    s32 arr[3];
    u8 sp30[0x30];
    void **temp_3;
    void *temp_3_2;
    s16 temp_5;
    s32 temp_2_2;
    s32 var_16;
    void **var_4;
    void *temp_2;
    V *temp_4;

    var_16 = 0;
    if (arg0->unk4 == NULL) {
        arg0->unk4 = arg0->unk0;
        arg0->unk8 = 0;
    }
    while (1) {
        temp_3 = *(void ***)((u8 *)arg0 + 0x4);
        if (temp_3 == NULL) {
            var_4 = 0;
        } else {
            var_4 = (void **)((u8 *)temp_3 + 0x10);
            temp_3_2 = *temp_3;
            arg0->unk4 = temp_3_2;
            if (temp_3_2 == NULL) {
                arg0->unk8 = 1;
            }
        }
        if (var_4 == NULL) {
            break;
        }
        temp_4 = (V *)*var_4;
        var_16 += 1;
        if (temp_4 != NULL && temp_4->flags != 0) {
            temp_2 = temp_4->get();
            if (temp_2 != NULL) {
                arr[0] = *(s32 *)((u8 *)temp_2 + 0x1F0);
                arr[1] = *(s32 *)((u8 *)temp_2 + 0x1F4);
                arr[2] = *(s32 *)((u8 *)temp_2 + 0x1F8);
                MotionListGetPlayerState_1723a0(arr, 0, sp30);
            }
        }
    }
    arg0->unk4 = NULL;
    arg0->unk8 = 0;
    if (var_16 == 0 && arg0->unkB6 != 0) {
        DrawCtxVif1HandlerStop_15dc40();
        temp_2_2 = GetDrawCtxNameTable_15de40();
        temp_5 = arg0->unk14;
        if (temp_5 >= 0x2DB && temp_5 < 0x30B) {
            NameTableFreeGroup_158ac0(temp_2_2, temp_5);
        }
        EffectEntryReset_2dc550(arg0);
    }
}

}
