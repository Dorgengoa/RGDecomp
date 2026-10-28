/* rgp:protos */
#define RGP_SELF_EffDefLinkInstance_19a650 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct A19A650 { u8 pad000[0xD8]; void *mD8; void *mDC; } A19A650;
typedef struct P19A650 { u8 pad000[0x5C]; A19A650 *m5C; } P19A650;
void EffDefLinkInstance_19a650(P19A650 *a, A19A650 *b)
{
    b->mDC = a->m5C;
    if (a->m5C != 0) {
        a->m5C->mD8 = b;
    }
    a->m5C = b;
}
