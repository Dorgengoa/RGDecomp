#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

class Obj3c {
public:
    u8 pad[0xC];
    VC_VPTR_MEMBER; void f8(s32 a0, void * a1, s32 a2) { VCM(void, (void *, s32, void *, s32), 0x8, a0, a1, a2); }
    void fC(s32 a0, void * a1, s32 a2) { VCM(void, (void *, s32, void *, s32), 0xC, a0, a1, a2); }
};

u8 *PtrAdd_42e2f0(u8 *, s32);
void HeapBlockLinkAfter_42e6f0(s32, void *, void *);
void DListNodeInit_42ec10(void *);

u8 *HeapBlockAllocAtEnd_42dc90(s32 arg0, u8 *arg1, s32 arg2, Obj3c *arg3) {
    s32 temp_22;
    s32 temp_3_2;
    s32 var_2;
    u32 temp_2;
    u8 *temp_16;
    u8 *temp_3;
    u8 *var_17;

    if (arg1 == NULL) {
        return NULL;
    }
    var_17 = arg1;
    temp_22 = (arg2 + 0xF) & ~0xF;
    temp_3 = arg1 + 0x10;
    temp_2 = *(u32 *)(arg1 + 0x10) - temp_22;
    if (temp_2 > 0x20) {
        *(s32 *)(temp_3) = temp_2 - 0x20;
        *(s32 *)(temp_3 + 4) = 0;
        var_17 = PtrAdd_42e2f0(temp_3 + 0x10, *(s32 *)(temp_3));
    }
    temp_16 = var_17 + 0x10;
    if (arg3 != NULL) {
        var_2 = *(s32 *)((u8 *)arg3 + 0) != 0;
        if (var_2 != 0) {
            var_2 = *(s32 *)((u8 *)arg3 + 4) != 0;
        }
        if (var_2 != 0) {
            arg3->fC(arg0, temp_16 + 0x10, arg2);
        } else {
            arg3->f8(arg0, temp_16 + 0x10, arg2);
        }
    }
    if (var_17 != arg1) {
        DListNodeInit_42ec10(var_17);
        *(s32 *)(var_17 + 0x14) = 0;
        *(s32 *)(var_17 + 0x10) = 0;
        *(s32 *)(var_17 + 0x18) = 0;
        *(s32 *)temp_16 = temp_22;
        HeapBlockLinkAfter_42e6f0(arg0, arg1, var_17);
    }
    temp_3_2 = *(s32 *)(temp_16 + 4) | 2;
    *(s32 *)(temp_16 + 4) = temp_3_2;
    *(s32 *)(temp_16 + 4) = temp_3_2 | 1;
    *(Obj3c **)(temp_16 + 8) = arg3;
    return temp_16 + 0x10;
}

}
