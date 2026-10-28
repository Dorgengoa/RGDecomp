/* rgp:protos */
#define RGP_SELF_normal_TransSaveQuitTickCb_518bc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal -- the gp `s8` latch gate.  Retail's `beql` branches INTO the body
 * and lets `b epilogue / addiu $2,$0,1` fall through, so the source is the
 * EARLY RETURN on != 0 (see src/overlays/normal/normal_TransSaveQuitCancelCb_518a90.c).
 * 0x00518B80 and 0x00518BC0 are byte-for-byte twins. */

typedef struct Obj {
    u8  pad000[0x10];
    s16 f10;
} Obj;

extern s8 D_00484820;   /* gp - 0x950 */

/*rgp*/

s32 normal_TransSaveQuitTickCb_518bc0(Obj *p)
{
    if (D_00484820 != 0) {
        return 1;
    }
    normal_TransSaveYesNoCursorBob_5188c0(p->f10, 0, 1);
    return 1;
}
