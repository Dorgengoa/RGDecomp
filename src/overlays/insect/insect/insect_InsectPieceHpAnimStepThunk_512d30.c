#include "types.h"
/* insect 0x00512D20 -- 8 bytes, `j insect_InsectPieceHpAnimStep_512d30` + nop. */

extern void insect_InsectPieceHpAnimStep_512d30(void);

void insect_InsectPieceHpAnimStepThunk_512d30(void)
{
    insect_InsectPieceHpAnimStep_512d30();
}
