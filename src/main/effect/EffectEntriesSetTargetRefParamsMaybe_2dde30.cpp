/* PARK: length 0xC8 vs retail 0xC4 (4 over) after 1 round. Not re-tried. */
#include "types.h"
extern "C" {

extern void *EffectEntryFindNodeById_2da140(void *arg0, void *arg1);

class VC_0 {
public:
    u8 pad[0x190];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void * f();
};
s32 EffectEntriesSetTargetRefParamsMaybe_2dde30(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 var_16;
    void *temp_2;
    void *temp_2_2;
    void *temp_4;

    var_16 = 0;
    do {
        temp_4 = (u8 *)arg0 + (var_16 * 0xE0);
        if (*(s16 *)((u8 *)temp_4 + 0xE) == *(s32 *)((u8 *)arg1 + 0x8)) {
            temp_2 = EffectEntryFindNodeById_2da140(temp_4, arg1);
            if (temp_2 != NULL) {
                temp_2_2 = ((VC_0 *)(temp_2))->f();
                if (temp_2_2 != NULL) {
                    *(s32 *)((u8 *)temp_2_2 + 0x30) = arg2;
                    *(s32 *)((u8 *)temp_2_2 + 0x34) = arg3;
                    *(s32 *)((u8 *)temp_2_2 + 0x38) = arg4;
                }
            }
        }
        var_16 += 1;
    } while (var_16 < 0x30);
    return 0;
}

}
