/* rgp:protos */
#define RGP_SELF_EventVolumeRecAnyHit_2e4c70 1
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

s32 EventVolumeRecAnyHit_2e4c70(Self *self, void *b, f32 f)
{
    Ent *p;
    s32  i;

    p = self->m10;
    if (p == 0 || self->m14 <= 0) {
        return 0;
    }
    for (i = 0; i < self->m14; i++, p++) {
        if (((unsigned char)EventVolumeContainsPoint_2e51f0(p, b, f)) != 0) {
            return 1;
        }
    }
    return 0;
}
