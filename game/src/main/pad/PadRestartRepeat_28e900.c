/* rgp:protos */
#define RGP_SELF_PadRestartRepeat_28e900 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Buf_FUN_0028e900 {
    s32 f000;
    u8 pad004[0x100];
    u8 f104;
    u8 pad105[0xB];
} Buf_FUN_0028e900;

typedef struct Obj_FUN_0028e900 Obj_FUN_0028e900;

/*rgp*/
/*rgp*/
/*rgp*/

void PadRestartRepeat_28e900(s32 unused, Obj_FUN_0028e900 *o, s32 *p)
{
    Buf_FUN_0028e900 b __attribute__((aligned(16)));

    b.f000 = 0;
    b.f104 = 0;
    PadSaveRepeatConfig_1838f0(o, &b);
    PadClearRepeatState_183e20(o, p);
    PadApplyRepeatConfig_183800(o, &b);
}
