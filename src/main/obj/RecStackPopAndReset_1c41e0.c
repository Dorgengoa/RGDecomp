#include "types.h"

typedef struct A_FUN_001c41e0 A_FUN_001c41e0;
typedef struct B_FUN_001c41e0 B_FUN_001c41e0;
typedef struct C_FUN_001c41e0 C_FUN_001c41e0;

extern C_FUN_001c41e0 *RecStackGetSlot_1c4330(A_FUN_001c41e0 *a, B_FUN_001c41e0 *b);
extern void RecStackPopTo_1c4020(A_FUN_001c41e0 *a, B_FUN_001c41e0 *b);
extern void MemStackReset_14d830(C_FUN_001c41e0 *c);

s32 RecStackPopAndReset_1c41e0(A_FUN_001c41e0 *a, B_FUN_001c41e0 *b)
{
    C_FUN_001c41e0 *c;

    c = RecStackGetSlot_1c4330(a, b);
    if (c == 0) {
        return -1;
    }
    RecStackPopTo_1c4020(a, b);
    MemStackReset_14d830(c);
    return 0;
}
