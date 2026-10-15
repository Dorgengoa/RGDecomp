#include "types.h"

extern u8    D_00484A68;
extern void *D_004807E4;
extern void *D_004807E8;
extern void *D_004807EC;
extern void  func_291910(void *p);

void factory_FactoryMenuDraw_4ec430(void)
{
    if (D_00484A68 != 0) {
        func_291910(D_004807E4);
        func_291910(D_004807E8);
        func_291910(D_004807EC);
    }
}
