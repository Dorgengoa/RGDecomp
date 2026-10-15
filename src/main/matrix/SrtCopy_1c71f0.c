#include "types.h"

typedef struct Sub_FUN_001c71f0 {
    u8 d[0x10];
} Sub_FUN_001c71f0;

typedef struct Obj_FUN_001c71f0 {
    Sub_FUN_001c71f0 f00;
    Sub_FUN_001c71f0 f10;
    Sub_FUN_001c71f0 f20;
    Sub_FUN_001c71f0 f30;
    Sub_FUN_001c71f0 f40;
} Obj_FUN_001c71f0;

extern void VecCopyAsDir_1cbe20(Sub_FUN_001c71f0 *a, Sub_FUN_001c71f0 *b);
extern void VecCopyAsPoint_1cbe10(Sub_FUN_001c71f0 *a, Sub_FUN_001c71f0 *b);

void SrtCopy_1c71f0(Obj_FUN_001c71f0 *a, Obj_FUN_001c71f0 *b)
{
    VecCopyAsDir_1cbe20(&a->f00, &b->f00);
    VecCopyAsDir_1cbe20(&a->f10, &b->f10);
    VecCopyAsPoint_1cbe10(&a->f20, &b->f20);
    VecCopyAsDir_1cbe20(&a->f30, &b->f30);
    VecCopyAsDir_1cbe20(&a->f40, &b->f40);
}
