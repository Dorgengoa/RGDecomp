#include "types.h"
/* normal 0x004F2A20 -- open: reset, blank the 16 slot widgets (0x2E..0x3D),
 * clear the 0x398 sub-object and mark the panel live. */

typedef struct Obj {
    u8  pad000[0x378];
    s16 f378;
    u8  pad37A[0x398 - 0x37A];
    u8  f398[4];
} Obj;

extern void normal_FieldHudEnemyListAllocMaybe_4f2870(Obj *p);
extern void func_2907A0(Obj *p, u16 id, f32 x);
extern void func_3A80E0(void *p);

extern void normal_FieldHudActivate_4f2a20(Obj *p);

void normal_FieldHudActivate_4f2a20(Obj *p)
{
    s32 i;

    normal_FieldHudEnemyListAllocMaybe_4f2870(p);
    for (i = 0; i < 16; i++) {
        func_2907A0(p, (u16)(i + 0x2E), 0.0f);
    }
    func_3A80E0(&p->f398);
    p->f378 = 1;
}
