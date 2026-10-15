#include "types.h"

/* title.bin overlay, 0x004EF3C0 -- call, clear a field, return the argument.
 *
 * The sq/lq of $16 is register allocation keeping the argument alive across
 * the call, not source: write it as a local and let the compiler choose.
 */

typedef struct Obj_title_FUN_004ef3c0 {
    u8 pad000[0x1C];
    s32 field01C;      /* +0x1C */
} Obj_title_FUN_004ef3c0;

extern void func_3761D0(Obj_title_FUN_004ef3c0 *o);

Obj_title_FUN_004ef3c0 *title_TitleCardRecInitMaybe_4ef3c0(Obj_title_FUN_004ef3c0 *o)
{
    func_3761D0(o);
    o->field01C = 0;
    return o;
}
