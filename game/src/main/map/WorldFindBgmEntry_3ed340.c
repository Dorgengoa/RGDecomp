/* rgp:protos */
#define RGP_SELF_WorldFindBgmEntry_3ed340 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E_003ed340 {
    u8 pad0[0x18];
    s32 f18;
} E_003ed340;

typedef struct T_003ed340 {
    u8 pad0[0x34];
    s32 f34;
} T_003ed340;

typedef struct S_003ed340 {
    u8 pad0[8];
    T_003ed340 *f8;
    u8 pad0C[0x18 - 0xC];
    s32 f18;
} S_003ed340;

/*rgp*/
/*rgp*/

E_003ed340 *WorldFindBgmEntry_3ed340(S_003ed340 *self, s32 idx)
{
    E_003ed340 *e;
    s32 n;
    s32 i;
    s32 r;
    if (idx < 0) return 0;
    if (self->f8 != 0) goto g1;
    return 0;
g1:
    r = PartyGetLocationGroupIdMaybe_3cb150(self->f18);
    n = 0;
    e = ((E_003ed340 *)GroupGetSubEntryRange_4112f0(self->f8->f34, (s16)r, (s16)idx, &n));
    if (e == 0) goto zeroB;
    if (n > 0) goto ok;
zeroB:
    return 0;
ok:
    i = 0;
    while (i < n) {
        if ((e->f18 & 2) != 0) return e;
        i++;
        e++;
    }
    return 0;
}
