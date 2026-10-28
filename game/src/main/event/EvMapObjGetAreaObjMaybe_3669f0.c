/* rgp:protos */
#define RGP_SELF_EvMapObjGetAreaObjMaybe_3669f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S_003669f0 {
    u8 pad0[0xA0];
    s32 fA0;
} S_003669f0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvMapObjGetAreaObjMaybe_3669f0(S_003669f0 *self, s32 i)
{
    s32 buf[0x140] __attribute__((aligned(16)));
    void *a;
    void *b;
    s32 n;
    a = GetMapMgr_201a90();
    b = TargetRefGetId_2e7120(&self->fA0);
    a = MapSlotsFindById_1e4b90(a, b, 0);
    if (a == 0) goto zeroA;
    if (((unsigned char)MapDataIsLoaded_1e79d0(a)) != 0) goto ok;
zeroA:
    return 0;
ok:
    n = MapDataFindObjsByName_1e6d40(a, EvMapObjGetName_366b90(self), buf, 0x140);
    if (i < 0) goto zero;
    if (n > i) goto ok2;
zero:
    return 0;
ok2:
    return buf[i];
}
