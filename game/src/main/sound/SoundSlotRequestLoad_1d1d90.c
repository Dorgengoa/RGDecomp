/* rgp:protos */
#define RGP_SELF_SoundSlotRequestLoad_1d1d90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S_001d1d90 {
    u8 pad0[0xC];
    s32 fC;
    s32 f10;
} S_001d1d90;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 SoundSlotRequestLoad_1d1d90(S_001d1d90 *self, s32 p1, void *p2)
{
    s32 r;
    if (p1 < 0) return 0;
    if (self->f10 == p1) return 1;
    if (self->fC == p1) return 1;
    LoaderReleaseHandle_1ccb70((void *)self);
    self->fC = -1;
    if (p1 < 0) goto zero;
    r = SoundSlotGetBankId_1d2130(self);
    if (r > 12) goto zero;
    if (p2 != 0) goto ok;
zero:
    return 0;
ok:
    if (self->f10 == 0xF4240) goto call;
    if (self->f10 == p1) return 1;
call:
    SoundSlotFree_1d21e0(self);
    if (((short)LoadHandleRequestFile_1ccbb0(self, p2)) < 0) return 0;
    self->fC = p1;
    return 1;
}
