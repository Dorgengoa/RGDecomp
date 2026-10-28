/* rgp:protos */
#define RGP_SELF_MoviePlayerOpen_1d61a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct S1D61A0 { u8 pad000[0xD8]; s32 fD8; s32 fDC; u8 fE0; u8 fE1; };

/*rgp*/

void MoviePlayerOpen_1d61a0(void *a, struct S1D61A0 *p)
{
    MovieOpen_1d5cf0(a, p, (u8 *)p + 0x80, (u8 *)p + 0xC0, p->fD8, p->fDC, p->fE0, p->fE1);
}
