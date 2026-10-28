/* rgp:protos */
#define RGP_SELF_UiSetWidgetVisible_290010 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Hub function, called from many already-merged src/ files (src/bodies2/*,
   src/p20c/*, src/p20e/*, src/p20f/*, src/p23c/*) -- their extern
   declarations pin the signature as (s32, s32, s32, s32) returning s32
   (a couple of callers discard the return value via a "void" decl). */

struct Tag00290010 {
    u8 pad0[0x1C];
    s16 f1C;
};

/*rgp*/
/*rgp*/


s32 UiSetWidgetVisible_290010(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    struct Tag00290010 *node;
    s32 mask;
    s32 tmp;

    node = UiFindWidget_290460(arg0, arg1);
    if (node == 0) {
        return 0;
    }
    mask = -2;
    if (arg3 == -1) {
        arg3 = 0x100;
    }
    if (arg2 != 0) {
        tmp = node->f1C;
        tmp &= mask;
        node->f1C = (s16)tmp;
    } else {
        node->f1C |= 1;
    }
    UiSetChildrenVisible_28ff30(arg0, node, arg2, arg3, 0);
    return 1;
}
