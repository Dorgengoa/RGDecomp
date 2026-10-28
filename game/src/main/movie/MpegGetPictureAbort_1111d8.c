/* rgp:protos */
#define RGP_SELF_MpegGetPictureAbort_1111d8 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* lw $3,0x40($4) (deref field40 pointer); li $2,1; jr $31;
   sw $2,0x878($3) (delay slot) -- set a flag word far out in the pointee,
   return 1. */

typedef struct Obj2_func_001111D8 {
    u8 pad000[0x878];
    s32 flag878;     /* +0x878 */
} Obj2_func_001111D8;

typedef struct Obj_func_001111D8 {
    u8 pad000[0x40];
    Obj2_func_001111D8 *field40;   /* +0x40 */
} Obj_func_001111D8;

s32 MpegGetPictureAbort_1111d8(Obj_func_001111D8 *o)
{
    o->field40->flag878 = 1;
    return 1;
}
