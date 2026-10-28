/* rgp:protos */
#define RGP_SELF_RecStackPopAndReset_1c41e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct A_FUN_001c41e0 A_FUN_001c41e0;
typedef struct B_FUN_001c41e0 B_FUN_001c41e0;
typedef struct C_FUN_001c41e0 C_FUN_001c41e0;

/*rgp*/
/*rgp*/
/*rgp*/

s32 RecStackPopAndReset_1c41e0(A_FUN_001c41e0 *a, B_FUN_001c41e0 *b)
{
    C_FUN_001c41e0 *c;

    c = ((C_FUN_001c41e0 *)RecStackGetSlot_1c4330(a, b));
    if (c == 0) {
        return -1;
    }
    RecStackPopTo_1c4020(a, b);
    MemStackReset_14d830(c);
    return 0;
}
