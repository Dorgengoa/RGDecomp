#include "types.h"

/* lw $3,0x40($4) (deref field40); li $2,1; sd $0,0x90($3) (clear 8 bytes);
   jr $31; sw $0,0x8C($3) (delay slot, clear 4 more bytes). Store order is
   source order: +0x90 (8 bytes) first, then +0x8C (4 bytes) last. Return
   1. */

typedef struct Obj2_func_00111538 {
    u8 pad000[0x8C];
    s32 f8C;      /* +0x8C */
    s64 f90;      /* +0x90 */
} Obj2_func_00111538;

typedef struct Obj_func_00111538 {
    u8 pad000[0x40];
    Obj2_func_00111538 *field40;   /* +0x40 */
} Obj_func_00111538;

s32 MpegClearPtsOverrideMaybe_111538(Obj_func_00111538 *o)
{
    Obj2_func_00111538 *q = o->field40;
    q->f90 = 0;
    q->f8C = 0;
    return 1;
}
