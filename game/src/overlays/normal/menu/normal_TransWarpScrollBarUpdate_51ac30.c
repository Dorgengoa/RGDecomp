/* rgp:protos */
#define RGP_SELF_normal_TransWarpScrollBarUpdate_51ac30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0051AC30 -- clamp of the gp counter to 4, kept in $16 across the
 * calls.  The clamp is an UNCONDITIONAL `k = 4` followed by the guarded
 * overwrite -- retail hoists the 4 into the `beq` delay slot; a ternary gives
 * `beql` instead (1 bad word at 0x0051AC44).  It is kept in $16 across the
 * three calls.  The counter is passed VERBATIM as argument three of
 * normal_TransWarpScrollBarLayout_51b700 (retail never reloads $6), then re-read after the calls
 * for the second store. */

typedef struct Hdl {
    u8  pad00[0xE];
    s16 f0E;
    u8  pad10[0x2];
    s16 f12;
} Hdl;

extern s32   D_00484850;          /* gp - 0x920 */
extern void *D_00484710;          /* gp - 0xA60 */
extern void *D_00484720;          /* gp - 0xA50 */

/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransWarpScrollBarUpdate_51ac30(void)
{
    Hdl *h;
    s32  n;
    s32  k;

    n = D_00484850;
    k = 4;
    if (n < 5) {
        k = n - 1;
    }
    normal_TransWarpScrollBarLayout_51b700(0x86, 5, n, 0);
    UiSetWidgetPos_290f60(D_00484710, 0x75D9, 0x1E5, 0x127);
    h = ((Hdl *)UiEntryListFindByTag_28ea40(D_00484720, 8));
    h->f0E = k;
    h->f12 = D_00484850 - 1;
    return 1;
}
