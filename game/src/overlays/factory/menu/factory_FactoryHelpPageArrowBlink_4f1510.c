/* rgp:protos */
#define RGP_SELF_factory_FactoryHelpPageArrowBlink_4f1510 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj {
    u8  pad00[0x68];
    s16 f68;
    u8  pad6A[0x6];
    u8  f70;
} Obj;

extern void *D_004807E8;                        /* _gp - 0x4988 */
extern f32   D_0047D4E8;                        /* _gp - 0x7C88 */
extern f32   D_0047D4EC;                        /* _gp - 0x7C84 */
extern f32   D_0047D488;                        /* _gp - 0x7CE8 */
extern f32   D_0047D418;                        /* _gp - 0x7D58 */

/*rgp*/
/*rgp*/

void factory_FactoryHelpPageArrowBlink_4f1510(Obj *o)
{
    if (o->f70 == 0) {
        return;
    }
    if (o->f68 == 0) {
        if (UiGetWidgetAlpha_290770(D_004807E8, 0x96) > D_0047D4E8) {
            UiFadeWidgetAlpha_290690(D_004807E8, 0x96, D_0047D488, D_0047D418, -1.0f);
            o->f68 = 1;
        }
    } else if (o->f68 != 0) {
        if (UiGetWidgetAlpha_290770(D_004807E8, 0x96) < D_0047D4EC) {
            UiFadeWidgetAlpha_290690(D_004807E8, 0x96, 1.0f, D_0047D418, -1.0f);
            o->f68 = 0;
        }
    }
}
