#include "types.h"

class VE303C90 {
public:
    u8 pad000[0xDC];
    virtual void d0();
    virtual void d1();
    virtual void v2(s32);
};

extern "C" void *strcpy(void *, const void *);
extern "C" char D_004621E8[];

extern "C" void EvDoorObjPlayOpen_303c90(u8 *arg0, s8 arg1) {
    if (((*(u32 *)(arg0 + 0xD0) & 0x80000000) != 0) ^ 1) {
        *(u16 *)(arg0 + 0x19E) = 0;
        strcpy(arg0 + 0x18C, D_004621E8);
        *(u16 *)(arg0 + 0x19C) = 1;
        *(u8 *)(arg0 + 0x1A1) = 1;
        *(u8 *)(arg0 + 0x1A2) = 1;
        *(u8 *)(arg0 + 0x1A0) = arg1;
        ((VE303C90 *)arg0)->v2(0);
    }
}
