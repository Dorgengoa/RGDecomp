/* rgp:protos */
#define RGP_SELF_NumPutDoubleThunk_1b2840 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void NumPutDouble_1b29d0(void *a);

void NumPutDoubleThunk_1b2840(void *a, s32 b)
{
    volatile s32 t = b;

    NumPutDouble_1b29d0(a);
}
