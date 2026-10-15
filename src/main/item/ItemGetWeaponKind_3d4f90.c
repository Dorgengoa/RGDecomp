#include "types.h"

extern s32 ItemDefGetWeaponData_40e110(void *arg0);

s32 ItemGetWeaponKind_3d4f90(void *arg0)
{
    void **fields = (void **)arg0;
    void *p;
    s8 temp_3;

    if (ItemDefGetWeaponData_40e110(fields[4]) == 0) {
        return -1;
    }
    p = fields[4];
    temp_3 = *(s8 *)((u8 *)p + 0x2);
    if (temp_3 == 0) {
        return 0;
    }
    if (temp_3 == 1) {
        return 1;
    }
    return -1;
}
