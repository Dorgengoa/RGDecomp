#include "types.h"
/* insmenu 0x004F6180 -- three calls on the same object; the parameter is held
 * in $16 because the last of them takes the pointer itself. */

typedef struct Obj Obj;
struct Obj {
    u8  pad00[0x12];
    s16 f12;
    s16 f14;
    s16 f16;
};

extern void insmenu_InsectVsSaveHighlightOption_4f6bb0(s32 a);
extern void insmenu_InsectVsSaveListRefresh_4ebc30(s32 a, s32 b);
extern void func_3777A0(void *a, s32 b, s32 c);

s32 insmenu_InsectVsLoadSlotMoveCb_4f6180(Obj *o)
{
    insmenu_InsectVsSaveHighlightOption_4f6bb0(o->f12);
    insmenu_InsectVsSaveListRefresh_4ebc30(o->f16, 0);
    func_3777A0(o, 0x890C, 1);
    return 1;
}
