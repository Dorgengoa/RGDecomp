/* rgp:protos */
#define RGP_SELF_normal_ShopMenuTiledPanelDrawCb_510d10 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00510D10 -- posts one map-marker request: a seven-word block built
 * on the frame and handed to func_28C430.  Pass-33 LIST rank: 96 bytes, 24
 * instructions, ONE conditional branch, 3 calls.
 *
 * The FIRST parameter is never read -- `lw $4,-0xBA8($28)` overwrites it
 * before any use -- but it still occupies $4, so the block's three words come
 * from arguments 2, 3 and 4 and the guard is on argument 5 in $8. */

typedef struct Req {
    s32  a;
    s32  b;
    s32  c;
    s32  d;
    f32 *e;
    f32 *f;
    s32  g;
} Req;

extern void *D_004845B4;          /* gp - 0xBBC */
extern void *D_004845C8;          /* gp - 0xBA8 */

/*rgp*/
/*rgp*/

extern s32 normal_ShopMenuTiledPanelDrawCb_510d10(void *unused, s32 a, s32 b, s32 c, s32 on);

s32 normal_ShopMenuTiledPanelDrawCb_510d10(void *unused, s32 a, s32 b, s32 c, s32 on)
{
    Req t __attribute__((aligned(16)));

    if (on != 0) {
        t.a = a;
        t.b = b;
        t.c = c;
        t.d = 0x32E;
        t.e = ((f32 *)UiGetWidgetColor_2904b0(D_004845C8, 0x32));
        t.f = ((f32 *)UiGetWidgetColor_2904b0(D_004845C8, 0x3C));
        t.g = (s32)D_004845B4;
        UiDrawSpriteTiled_28c430(&t);
    }
    return 1;
}
