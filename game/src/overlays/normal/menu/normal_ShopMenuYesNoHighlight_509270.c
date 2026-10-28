/* rgp:protos */
#define RGP_SELF_normal_ShopMenuYesNoHighlight_509270 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00509270 -- three s16 stores into a 0x20-stride array.  The
 * `dsll32/dsra32 ..,24` is an s32 parameter with an explicit (s8) cast; the
 * 0x5264B8 read is NAMED so it survives the first `sh` (load-across-store). */
typedef struct Ent { u8 pad00[8]; s16 f08; u8 pad0A[0x20 - 0x0A]; } Ent;
extern s16 normal_D_005264B8[];
extern s16 normal_D_005264BA[];
/*rgp*/
extern Ent *normal_ShopMenuYesNoHighlight_509270(s32 n, s32 a, s32 b);
Ent *normal_ShopMenuYesNoHighlight_509270(s32 n, s32 a, s32 b)
{
    Ent *e = ((Ent *)UiGetWidgetSprite_28fe10(a, b, 0));
    s16 t;
    if (e != 0) {
        t = normal_D_005264B8[0];
        e[0].f08 = t;
        e[1].f08 = t;
        e[(s8)n].f08 = normal_D_005264BA[0];
    }
    return e;
}
