/* rgp:protos */
#define RGP_SELF_TreasureBoxRecFind_427b00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E_00427b00 {
    u8 pad0[2];
    s16 f2;
    s16 f4;
    u8 pad6[0x52];
} E_00427b00;

typedef struct S_00427b00 {
    u8 pad0[0x7C];
    s16 f7C;
    u8 pad7E[0xE];
    E_00427b00 *f8C;
} S_00427b00;

E_00427b00 *TreasureBoxRecFind_427b00(S_00427b00 *self, s32 k1, s32 k2)
{
    E_00427b00 *p = self->f8C;
    s32 n;
    s32 j;
    if (p == 0) goto zero;
    n = self->f7C;
    if (n > 0) goto ok;
zero:
    return 0;
ok:
    j = 0;
    while (j < n) {
        if (p->f2 == k1) {
            if (p->f4 == k2) return p;
        }
        j++;
        p++;
    }
    return 0;
}
