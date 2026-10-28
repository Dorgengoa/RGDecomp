#include "types.h"
#pragma opt_common_subs off

class VC_408 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s32 x0) { return VCM(s32, (void *, s32), 0x70, x0); }
};

extern "C" s32 WorldSubsysLinkIds_408c00(void *arg0, void *arg1)
{
    void *top;
    s32 i;
    void *e21_2;
    void **p6;
    s32 v4;
    VC_408 *t4;
    void *e21;
    s32 j;
    s32 k;

    if (arg1 == NULL) {
        return 0;
    }
    top = *(void **)((u8 *)arg0 + 0x8C);
    if (top == NULL) {
        return 0;
    }
    if (*(s16 *)((u8 *)arg0 + 0x7C) <= 0) {
        return 0;
    }
    i = 0;
    while (i < *(s16 *)((u8 *)arg0 + 0x7C)) {
        e21 = *(void **)((u8 *)top + 0x8);
        j = 0;
        while (j < *(s16 *)((u8 *)top + 0x4)) {
            t4 = *(VC_408 **)((u8 *)*(void **)((u8 *)arg1 + 0x44) + 0x8);
            *(s32 *)((u8 *)e21 + 0x0) = t4->f(*(s16 *)((u8 *)e21 + 0x0));
            p6 = *(void ***)((u8 *)e21 + 0x8);
            k = 0;
            while (k < *(s16 *)((u8 *)e21 + 0x4)) {
                v4 = *(s16 *)p6;
                if (v4 >= 0 && v4 < *(s16 *)((u8 *)top + 0x4)) {
                    *p6 = (u8 *)*(void **)((u8 *)top + 0x8) + v4 * 0x1C;
                } else {
                    *p6 = 0;
                }
                k += 1;
                p6 += 1;
            }
            j += 1;
            e21 = (u8 *)e21 + 0x1C;
        }
        e21_2 = *(void **)((u8 *)top + 0x10);
        j = 0;
        while (j < *(s16 *)((u8 *)top + 0xC)) {
            t4 = *(VC_408 **)((u8 *)*(void **)((u8 *)arg1 + 0x40) + 0x8);
            *(s32 *)e21_2 = t4->f(*(s16 *)e21_2);
            j += 1;
            e21_2 = (u8 *)e21_2 + 4;
        }
        i += 1;
        top = (u8 *)top + 0x18;
    }
    return 1;
}
