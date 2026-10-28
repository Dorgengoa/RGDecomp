/* rgp:protos */
#define RGP_SELF_title_TitleLoadPortMoveCb_4ee270 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EE270 -- two calls that both take the same halfword
 * field, a byte flag store, and a constant return.  The sq/lq of $16 keeps
 * the object pointer alive across the first call: allocation, not source.
 */

typedef struct Obj_title_FUN_004ee270 {
    u8 pad000[0x12];
    s16 field012;      /* +0x12 */
    u8 pad014[0x2];
    s16 field016;      /* +0x16 */
} Obj_title_FUN_004ee270;

extern u8 D_00484218;
/*rgp*/
/*rgp*/

s32 title_TitleLoadPortMoveCb_4ee270(Obj_title_FUN_004ee270 *o)
{
    SaveSetPort_37b7c0(o->field012);
    title_TitleLoadPortCursorBob_4edaf0(o->field012, 0, 1);
    D_00484218 = 5;
    return 1;
}
