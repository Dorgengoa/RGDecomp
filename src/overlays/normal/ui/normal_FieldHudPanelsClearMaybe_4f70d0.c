#include "types.h"
/* normal 0x004F70D0 -- close: run the module-wide teardown, blank and re-place
 * the 0x02 widget, then clear the three 20-byte records at 0x300 and mark each
 * slot free (-1). */

typedef struct Rec { s32 f000; u8 pad004[0x14 - 4]; } Rec;   /* stride 20 */

typedef struct Obj {
    u8  pad000[0x300];
    Rec f300[3];
    u8  pad33C[0x378 - 0x33C];
    s16 f378;
} Obj;

extern void normal_FieldHudPanelFrameLayout_4f87c0(void);
extern void func_290010(Obj *p, u16 id, s32 c, s32 d);
extern void func_290F60(Obj *p, u16 id, s32 c, s32 d);
extern void func_131B60(void *p, s32 v, s32 n);

extern void normal_FieldHudPanelsClearMaybe_4f70d0(Obj *p);

void normal_FieldHudPanelsClearMaybe_4f70d0(Obj *p)
{
    s32 i;

    if (p->f378 == 0) {
        return;
    }
    normal_FieldHudPanelFrameLayout_4f87c0();
    func_290010(p, 2, 0, -1);
    func_290F60(p, 2, 0, 0x178);
    for (i = 0; i < 3; i++) {
        func_131B60(&p->f300[i], 0, 0x14);
        p->f300[i].f000 = -1;
    }
}
