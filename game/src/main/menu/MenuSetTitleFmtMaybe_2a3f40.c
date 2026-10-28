/* rgp:protos */
#define RGP_SELF_MenuSetTitleFmtMaybe_2a3f40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_002a3f40 {
    s32 f00;
    u8 pad004[0x16E];
    char f172[0x10];
} Obj_FUN_002a3f40;

typedef struct H_FUN_002a3f40 H_FUN_002a3f40;

extern H_FUN_002a3f40 *D_004823D8;
/*rgp*/
extern void Sprintf_1343b8(char *d, const char *f, char *a);
/*rgp*/
/*rgp*/

s32 MenuSetTitleFmtMaybe_2a3f40(Obj_FUN_002a3f40 *o, char *s)
{
    Sprintf_1343b8(o->f172, ((const char *)MsgTableLookup_28aa30(D_004823D8, 0x44F)), s);
    UiSetTextString_28f510(o->f00, 0xB4, o->f172, 0);
    UiSetTextCenteredX_28f300(o->f00, 0xB4, 0x9C, 0);
    return 1;
}
