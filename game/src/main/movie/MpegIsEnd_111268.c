#include "types.h"

typedef struct Obj_FUN_00111268 {
    u8 pad000[0x40];
    s32 *p;            /* +0x40 */
} Obj_FUN_00111268;

asm s32 MpegIsEnd_111268(Obj_FUN_00111268 *o)
{
    .set noreorder;
    lw         $3, 0x40($4);
    jr         $31;
    lw        $2, 0x0($3);
}
