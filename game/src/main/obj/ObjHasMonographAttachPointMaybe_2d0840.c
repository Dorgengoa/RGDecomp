/* rgp:protos */
#define RGP_SELF_ObjHasMonographAttachPointMaybe_2d0840 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* trailing `sltu $2,$0,$2` is the `!= 0` on the last call's result. */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 ObjHasMonographAttachPointMaybe_2d0840(s32 id)
{
    void *h;
    void *rec;

    h = GetCurrentScene_1f5be0();
    if ((ObjRecGetFlags_1c3d90(h, 1, id) & 0x10000000) != 0) {
        return 0;
    }
    rec = ObjRecGetLiveObject_1c4a90(h, id);
    /* retail FALLS THROUGH into the ObjFindNthAttachPoint_1addc0 arm (beql past it), so
       that arm is the `if` body and the 0 is the tail. */
    if (rec != 0) {
        return ObjFindNthAttachPoint_1addc0(rec, 0xA0, 0) != 0;
    }
    return 0;
}
