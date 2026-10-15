#include "types.h"

typedef struct A {
    u8 pad00[0x6D];
    u8 f6D;
} A;

extern A *D_00484A48;

u8 factory_FactoryBlueprintIsListOpen_4e9f20(void)
{
    A *o;

    o = D_00484A48;
    if (o != 0) {
        return o->f6D;
    }
    return 0;
}
