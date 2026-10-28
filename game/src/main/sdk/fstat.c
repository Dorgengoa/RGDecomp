#include "types.h"

asm void fstat(void)
{
    .set noreorder;
    addiu      $2, $0, 0x2000;
    sd         $0, 0x48($5);
    sw         $2, 0x4($5);
    jr         $31;
    daddu     $2, $0, $0;
}
