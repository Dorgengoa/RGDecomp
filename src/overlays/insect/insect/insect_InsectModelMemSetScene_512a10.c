#include "types.h"
/* insect 0x00512A10 -- one-call wrapper storing the result at +0x00.  The
 * argument is this function's own $4 passed through, so it leaves no
 * instruction behind. */
typedef struct WRec { s32 f00; } WRec;

extern s32 func_1F5BE0(WRec *o);

void insect_InsectModelMemSetScene_512a10(WRec *o)
{
    o->f00 = func_1F5BE0(o);
}
