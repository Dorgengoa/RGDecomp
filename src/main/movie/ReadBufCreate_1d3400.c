#include "types.h"

typedef struct Obj_FUN_001d3400 {
    u8 pad000[0x14000];
    s32 a;             /* +0x14000 */
    s32 b;             /* +0x14004 */
    s32 c;             /* +0x14008 */
} Obj_FUN_001d3400;

s32 ReadBufCreate_1d3400(Obj_FUN_001d3400 *o)
{
    o->b = 0;
    o->a = 0;
    o->c = 0x14000;
    return 0;
}
