#include "types.h"
#pragma opt_common_subs off
extern "C" {

extern void DListRemove_42e4e0(s32 arg0, void *arg1);
extern void *DListGetNext_42eb30(void *arg0);
extern void *DListGetPrev_42eb40(void *arg0);

class VC_0 {
public:
    u8 pad[0xC];
    virtual void d0();
    virtual void d1();
    virtual void f(void * x0);
};
void *HeapBlockFreeCoalesce_42d9c0(s32 arg0, void *arg1, s32 arg2)
{
    void *temp_16;
    void *temp_2;
    void *temp_2_2;
    void *temp_4;
    void *var_18;
    void *vtbl;
    void *h2;
    void *h3;

    var_18 = arg1;
    if (var_18 == NULL) {
        return NULL;
    }
    temp_16 = (u8 *)var_18 + 0x10;
    if (arg2 != 0) {
        temp_4 = *(void **)((u8 *)temp_16 + 0x8);
        if (temp_4 != NULL) {
            vtbl = *(void **)((u8 *)temp_4 + 0xC);
            ((VC_0 *)(temp_4))->f((u8 *)temp_16 + 0x10);
        }
    }
    *(s32 *)((u8 *)temp_16 + 0x4) = 0;
    temp_2 = DListGetNext_42eb30(var_18);
    if (temp_2 != NULL) {
        h2 = (u8 *)temp_2 + 0x10;
        if (!(*(s32 *)((u8 *)temp_16 + 0x4) & 2) && !(*(s32 *)((u8 *)h2 + 0x4) & 2)) {
            *(s32 *)temp_16 = *(s32 *)temp_16 + *(s32 *)h2 + 0x20;
            DListRemove_42e4e0(arg0, temp_2);
        }
    }
    temp_2_2 = DListGetPrev_42eb40(var_18);
    if (temp_2_2 != NULL) {
        h3 = (u8 *)temp_2_2 + 0x10;
        if (!(*(s32 *)((u8 *)h3 + 0x4) & 2) && !(*(s32 *)((u8 *)temp_16 + 0x4) & 2)) {
            *(s32 *)h3 = *(s32 *)h3 + *(s32 *)temp_16 + 0x20;
            DListRemove_42e4e0(arg0, var_18);
            var_18 = temp_2_2;
        }
    }
    return var_18;
}

}
