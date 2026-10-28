/* rgp:protos */
#define RGP_SELF_title_TitleLoadPortTickCb_4ee190 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EE190 -- an early out, then a saturating decrement
 * of a counter before a call.  Every path returns 1.
 *
 * `blezl` is `<= 0` and LIKELY, so the guarded body is the decrement and its
 * delay slot (`lh $4, 0x12($4)`) belongs to the SKIP path -- which is why the
 * same load appears twice in the listing.
 */

typedef struct Obj_title_FUN_004ee190 {
    u8 pad000[0x12];
    s16 field012;      /* +0x12 */
} Obj_title_FUN_004ee190;

extern s8 D_00484214;
extern s8 D_00484218;
/*rgp*/

s32 title_TitleLoadPortTickCb_4ee190(Obj_title_FUN_004ee190 *o)
{
    s8 n;

    if (D_00484214 != 0) {
        return 1;
    }
    n = D_00484218;
    if (n > 0) {
        D_00484218 = n - 1;
    }
    title_TitleLoadPortCursorBob_4edaf0(o->field012, 0, 1);
    return 1;
}
