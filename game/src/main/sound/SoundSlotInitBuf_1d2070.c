/* rgp:protos */
#define RGP_SELF_SoundSlotInitBuf_1d2070 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern u32 strlen(s32);
extern void strcpy(s32, s32);

void SoundSlotInitBuf_1d2070(s32 p0, s32 p1, s32 p2, s32 p3)
{
    MemStackClear_14dff0((p0 + 0x30));
    MemStackInit_14d810((p0 + 0x30), p2, p3);
    if (strlen(p1) < 0x10) {
        strcpy((p0 + 0x30), p1);
    }
}
