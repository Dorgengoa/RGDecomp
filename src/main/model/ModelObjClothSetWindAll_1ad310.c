#include "types.h"

typedef struct { u8 pad[0x170]; } E_001ad310;
typedef struct { u8 pad[0x204]; s32 f204; E_001ad310 *f208; } T_001ad310;

extern void DynClothSetWind_169410(E_001ad310 *, void *, f32);

void ModelObjClothSetWindAll_1ad310(T_001ad310 *p, void *q, f32 v)
{
    s32 i;

    for (i = 0; i < p->f204; i++) {
        DynClothSetWind_169410(&p->f208[i], q, v);
    }
}
