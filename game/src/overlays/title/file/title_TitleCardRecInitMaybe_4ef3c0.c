/* rgp:protos */
#define RGP_SELF_title_TitleCardRecInitMaybe_4ef3c0 1
#include "port/game_protos.h"
#line 1
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

/*rgp*/

Obj_title_FUN_004ef3c0 *title_TitleCardRecInitMaybe_4ef3c0(Obj_title_FUN_004ef3c0 *o)
{
    McCardInfoClear_3761d0(o);
    o->field01C = 0;
    return o;
}
