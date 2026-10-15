#include "types.h"

typedef struct S003F5DE0 {
    u8 pad0[0x2];
    u8 f2;                    /* +0x2 */
    u8 pad3[0x9];
    void *fC;                 /* +0xC */
} S003F5DE0;

void *AbilityDataGetKind1Rec_3f5de0(S003F5DE0 *p)
{
    if (p->f2 == 1) {
        if (p->fC != 0) {
            return p->fC;
        }
    }
    return 0;
}
