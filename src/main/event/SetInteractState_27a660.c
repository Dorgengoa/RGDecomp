#include "types.h"

typedef struct S36 { s32 w[9]; } S36;

extern S36 D_004D7C40;

void SetInteractState_27a660(S36 *p)
{
    S36 t;

    t = *p;
    D_004D7C40 = t;
}
