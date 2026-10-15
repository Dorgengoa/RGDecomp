#include "types.h"
/* insmenu 0x004F5050 -- the parameter is held in $16 because three of the four
 * calls read it. */
extern void insmenu_InsectVsSaveHighlightOption_4f6bb0(s32 a);
extern void func_37A2B0(s32 a);
extern void insmenu_InsectVsTeamListTitleUpdate_4f5400(void);
extern void func_3777A0(void *a, s32 b, s32 c);
typedef struct Obj Obj;
struct Obj { u8 pad00[0x12]; s16 f12; s16 f14; s16 f16; };
s32 insmenu_InsectVsTeamListMoveCb_4f5050(Obj *o)
{
    insmenu_InsectVsSaveHighlightOption_4f6bb0(o->f12);
    func_37A2B0(o->f16);
    insmenu_InsectVsTeamListTitleUpdate_4f5400();
    func_3777A0(o, 0x890C, 1);
    return 1;
}
