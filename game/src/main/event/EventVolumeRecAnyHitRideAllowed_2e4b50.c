/* rgp:protos */
#define RGP_SELF_EventVolumeRecAnyHitRideAllowed_2e4b50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent { u8 b[0x40]; } Ent;

typedef struct Self {
    u8   pad000[0x10];
    Ent *m10;
    s32  m14;
} Self;

/*rgp*/

s32 EventVolumeRecAnyHitRideAllowed_2e4b50(Self *self, void *b)
{
    Ent *p;
    s32  i;

    p = self->m10;
    if (p == 0 || self->m14 <= 0) {
        return 0;
    }
    for (i = 0; i < self->m14; i++, p++) {
        if (EventVolumeContainsPointRideAllowed_2e5170(p, b) != 0) {
            return 1;
        }
    }
    return 0;
}
