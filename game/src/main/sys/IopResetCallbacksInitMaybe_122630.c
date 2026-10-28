#include "types.h"

extern void memset(void);

asm void IopResetCallbacksInitMaybe_122630(void)
{
    .set noreorder;
    lui        $2, 0x44;
    lui        $3, 0x44;
    lui        $4, 0x49;
    sw         $0, 0x78C8($2);
    sw         $0, 0x78CC($3);
    addiu      $4, $4, -0x2978;
    daddu      $5, $0, $0;
    j          memset;
    addiu     $6, $0, 0x200;
}
