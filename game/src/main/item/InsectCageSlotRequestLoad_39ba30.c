/* rgp:protos */
#define RGP_SELF_InsectCageSlotRequestLoad_39ba30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S_0039ba30 {
    u8 pad0[4];
    s32 f4;
    u8 pad8[0x1C - 8];
    s16 f1C;
    s16 f1E;
    s32 f20;
} S_0039ba30;

/*rgp*/
/*rgp*/
/*rgp*/

s32 InsectCageSlotRequestLoad_39ba30(S_0039ba30 *self, s32 p1, void *p2, s32 p3, s32 p4)
{
    if (((short)InsectCageSlotGetState_39bb00(self)) == 2) return 1;
    if (((short)InsectCageSlotGetState_39bb00(self)) == 1) return 1;
    InsectCageSlotRelease_39b9c0(self);
    if (p2 == 0) goto zero;
    if (p4 != 0) goto ok;
zero:
    return 0;
ok:
    LoadHandleRequestFile_1ccbb0(&self->f4 + 1, p2);
    self->f4 = p4;
    self->f1C = p1;
    self->f20 = p3;
    self->f1E = 1;
    return 1;
}
