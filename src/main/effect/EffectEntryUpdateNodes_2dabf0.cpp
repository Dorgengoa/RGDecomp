#include "types.h"
#pragma opt_common_subs off
#undef NULL
#define NULL 0
extern "C" {

extern void ModelMotionEventReleaseHandlers_1b02b0(s32);
extern void EffectNodeStepScript_2dad50(void *, void *);

class VC_0 {
public:
    u8 pad[0x190];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual s32 f();
};
class VC_1 {
public:
    u8 pad[0x190];
    virtual void d0();
    virtual void f();
};
void EffectEntryUpdateNodes_2dabf0(void *arg0)
{
    void *temp_3;
    void *temp_3_2;
    s32 temp_3_5;
    s32 temp_2;
    void **var_16;
    void **var_4;
    void *temp_4;
    void *temp_4_2;
    void *temp_5;

    if (*(s16*)((u8 *)arg0 + 0xBA) & 1) {
        if (*(void **)((u8 *)arg0 + 0x4) == NULL) {
            *(void **)((u8 *)arg0 + 0x4) = *(void **)((u8 *)arg0 + 0x0);
            *(s32 *)((u8 *)arg0 + 0x8) = 0;
        }
        for (;;) {
            temp_3 = *(void **)((u8 *)arg0 + 0x4);
            if (temp_3 == NULL) {
                var_4 = NULL;
            } else {
                var_4 = (void **)((u8 *)temp_3 + 0x10);
                temp_3_2 = *(void **)temp_3;
                *(void **)((u8 *)arg0 + 0x4) = temp_3_2;
                if (temp_3_2 == NULL) {
                    *(s32 *)((u8 *)arg0 + 0x8) = 1;
                }
            }
            if (var_4 == NULL) {
                break;
            }
            temp_4 = *var_4;
            if (temp_4 != NULL) {
                temp_2 = ((VC_0 *)(temp_4))->f();
                if (temp_2 != 0) {
                    ModelMotionEventReleaseHandlers_1b02b0(temp_2);
                }
            }
        }
        *(void **)((u8 *)arg0 + 0x4) = NULL;
        *(s32 *)((u8 *)arg0 + 0x8) = 0;
    } else {
        if (*(void **)((u8 *)arg0 + 0x4) == NULL) {
            *(void **)((u8 *)arg0 + 0x4) = *(void **)((u8 *)arg0 + 0x0);
            *(s32 *)((u8 *)arg0 + 0x8) = 0;
        }
        for (;;) {
            temp_3 = *(void **)((u8 *)arg0 + 0x4);
            if (temp_3 == NULL) {
                var_16 = NULL;
            } else {
                var_16 = (void **)((u8 *)temp_3 + 0x10);
                temp_3_2 = *(void **)temp_3;
                *(void **)((u8 *)arg0 + 0x4) = temp_3_2;
                if (temp_3_2 == NULL) {
                    *(s32 *)((u8 *)arg0 + 0x8) = 1;
                }
            }
            if (var_16 == NULL) {
                break;
            }
            temp_5 = *var_16;
            if (temp_5 != NULL) {
                temp_3_5 = *(s16 *)((u8 *)temp_5 + 0x0);
                if (temp_3_5 != 1 && temp_3_5 != 2) {
                } else {
                    EffectNodeStepScript_2dad50(arg0, temp_5);
                }
                temp_4_2 = *var_16;
                ((VC_1 *)(temp_4_2))->f();
            }
        }
        *(void **)((u8 *)arg0 + 0x4) = NULL;
        *(s32 *)((u8 *)arg0 + 0x8) = 0;
    }
}

}
