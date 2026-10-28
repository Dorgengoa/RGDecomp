/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuTextClipDrawCb_503840 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00503840 -- the object at 0x004DB150 is materialised with a
 * `lui %hi / addiu %lo` RELOCATION pair (not `lui/ori` of a folded constant),
 * and both arms still test it against zero, so the source references a SYMBOL
 * and holds it in a pointer local. */

extern u8 D_004DB150[];

/*rgp*/
/*rgp*/

s32 normal_BtlChgMenuTextClipDrawCb_503840(void *a, s32 b, s32 c, s32 d, s32 e)
{
    u8 *p;

    p = D_004DB150;
    if (e != 0) {
        if (p != NULL) {
            TextStyleSetClipRect_26f620(p, 0xDC, 0x1E3, 0x160, 0x1AB);
        }
    } else {
        if (p != NULL) {
            TextStyleClearClipRect_26f600((void *)(p));
        }
    }
    return 1;
}
