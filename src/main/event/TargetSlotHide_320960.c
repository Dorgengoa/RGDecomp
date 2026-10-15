#include "types.h"

typedef struct Obj_FUN_00320960 {
    u8 pad000[0x34];
    s32 f34;
} Obj_FUN_00320960;

extern const u8 D_00527020[];
extern void TargetRefClear_2e71d0(Obj_FUN_00320960 *o);
extern s32 GetLoadedOverlayId_1c3200(void);
extern void func_4F1260(const u8 *p);

void TargetSlotHide_320960(Obj_FUN_00320960 *o)
{
    o->f34 = 1;
    TargetRefClear_2e71d0(o);
    if (GetLoadedOverlayId_1c3200() == 3) {
        func_4F1260(D_00527020);
    }
}
