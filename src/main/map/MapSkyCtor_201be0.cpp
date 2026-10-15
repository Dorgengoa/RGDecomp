#include "types.h"

class Sub {
    u8 pad[0xE0];
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
};

extern "C" {
void MapSkyResetModels_17f8a0(void *);
extern u8 D_0046FFA0[];
extern u8 D_0046FFC0[];
}

extern "C" void *MapSkyCtor_201be0(u8 *arg0) {
    u8 *p;

    p = arg0 + 0x10;
    do {
        *(u8 **)(p + 0x1B0) = D_0046FFC0;
        *(u8 **)(p + 0xF0) = D_0046FFA0;
        ((Sub *)(p + 0x10))->v10();
        p += 0x1C0;
    } while (p < arg0 + 0x710);
    p = arg0 + 0x730;
    do {
        *(u8 **)(p + 0x1B0) = D_0046FFC0;
        *(u8 **)(p + 0xF0) = D_0046FFA0;
        ((Sub *)(p + 0x10))->v10();
        p += 0x1C0;
    } while (p < arg0 + 0xE30);
    p = arg0 + 0xE50;
    do {
        *(u8 **)(p + 0x1B0) = D_0046FFC0;
        *(u8 **)(p + 0xF0) = D_0046FFA0;
        ((Sub *)(p + 0x10))->v10();
        p += 0x1C0;
    } while (p < arg0 + 0x1550);
    *(u8 **)(arg0 + 0x1710) = D_0046FFC0;
    *(u8 **)(arg0 + 0x1650) = D_0046FFA0;
    ((Sub *)(arg0 + 0x1570))->v10();
    MapSkyResetModels_17f8a0(arg0);
    return arg0;
}
