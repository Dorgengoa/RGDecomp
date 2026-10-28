/* rgp:protos */
#define RGP_SELF_SetInteractState_27a660 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S36 { s32 w[9]; } S36;

extern S36 D_004D7C40;

void SetInteractState_27a660(S36 *p)
{
    S36 t __attribute__((aligned(16)));

    t = *p;
    D_004D7C40 = t;
}
