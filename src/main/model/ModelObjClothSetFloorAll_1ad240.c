#include "types.h"

typedef struct { u8 pad[0x170]; } E_001ad240;
typedef struct { u8 pad[0x204]; s32 f204; E_001ad240 *f208; } T_001ad240;

extern void DynClothSetFloor_1693f0(E_001ad240 *, f32);

void ModelObjClothSetFloorAll_1ad240(T_001ad240 *p, f32 v)
{
    s32 i;

    for (i = 0; i < p->f204; i++) {
        DynClothSetFloor_1693f0(&p->f208[i], v);
    }
}
