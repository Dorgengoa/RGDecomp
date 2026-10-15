#include "types.h"

extern void DestroyArray_1005b0(void *, void (*)(void), s32, s32);

extern u8 D_00495FB0[];
extern void CdDirTableDtor_183720(void);

void CdDirTablesDtor_183700(void)
{
    DestroyArray_1005b0(D_00495FB0, CdDirTableDtor_183720, 0xC, 2);
}
