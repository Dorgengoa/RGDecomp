/* rgp:protos */
#define RGP_SELF_MinimapCtor_32a800 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Struct0032a800 {
    u8 pad0[0x106];
    s16 unk106;
} Struct0032a800;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *memset(void *a, s32 b, s32 c);

Struct0032a800 *MinimapCtor_32a800(Struct0032a800 *arg0)
{
    EntryListCtor_323880((u8 *) arg0 + 0x12C);
    MinimapSetFadeAlpha_32a1d0(arg0, 1.0f);
    MinimapSetFadeMode_329de0(arg0, 0, -1.0f);
    MinimapSetFadeDuration_32a170(arg0, 16.0f);
    MinimapSetWinSize_324c50(arg0, 0xA0, 0x90);
    arg0->unk106 = -1;
    memset((u8 *) arg0 + 0x20, 0, 0x10);
    MinimapSetSizeClamped_324960(arg0, 0x140, 0x140);
    MinimapSetWinSize_324c50(arg0, 0xA0, 0x90);
    MinimapResetScroll_324900(arg0);
    return arg0;
}
