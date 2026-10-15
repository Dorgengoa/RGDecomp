#include "types.h"

extern void *D_004DB92C[3];
extern void CharaResetStateMaybe_212c50(void *);

s32 AiCmdCharaResetStateMaybe_2cb380(void)
{
    void *p;

    p = D_004DB92C[0];
    if (p != 0) {
        CharaResetStateMaybe_212c50(p);
    }
    return 1;
}
