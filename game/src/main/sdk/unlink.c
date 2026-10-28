#include "types.h"
extern s32 *GetReent_12f4d0(void);   /* __errno */

asm s32 unlink(const char *path)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    jal        GetReent_12f4d0;
    nop;
    addiu      $3, $0, 0x5;
    ld         $31, 0x0($29);
    sw         $3, 0x0($2);
    addiu      $2, $0, -0x1;
    jr         $31;
    addiu     $29, $29, 0x10;
}
