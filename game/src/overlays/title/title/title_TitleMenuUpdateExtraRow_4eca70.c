/* rgp:protos */
#define RGP_SELF_title_TitleMenuUpdateExtraRow_4eca70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004ECA70 -- retarget the cursor widget when the
 * selection moves.  Two guards, then a two-armed layout block, then one shared
 * placement call whose y is an arithmetic function of the selection.
 *
 * The first guard is a `beql` whose delay slot carries `ld $31` -- the shared
 * epilogue -- so both exits are the FALL-THROUGH and the work is the
 * positively-guarded arm.
 */

typedef struct Obj_title_FUN_004eca70 {
    u8 pad000[0xE];
    s16 field00E;      /* +0xE  */
    u8 pad010[0x6];
    s16 field016;      /* +0x16 */
} Obj_title_FUN_004eca70;

extern s16 D_0048418C;
extern s16 D_0048419C;
extern s16 D_004841A0;
extern void *D_0048415C;
extern void *D_00484170;

/*rgp*/
/*rgp*/
/*rgp*/

void title_TitleMenuUpdateExtraRow_4eca70(void)
{
    Obj_title_FUN_004eca70 *o;

    if (D_004841A0 != D_0048419C) {
        if (D_0048418C == 0) {
            o = ((Obj_title_FUN_004eca70 *)UiEntryListFindByTag_28ea40(D_0048415C, 0x7531));
            if (D_0048419C != 0) {
                UiSetWidgetsVisibleById_291110(D_00484170, 0x66, 1, 1);
                UiSetWidgetPos_290f60(D_00484170, 4, 0xB8, 0x14F);
                UiSetWidgetPos_290f60(D_00484170, 0x66, 0xB9, 0x163);
                UiSetWidgetPos_290f60(D_00484170, 5, 0xB9, 0x177);
                o->field00E = 3;
                if (o->field016 == 2) {
                    o->field016 = 3;
                }
            } else {
                UiSetWidgetsVisibleById_291110(D_00484170, 0x66, 0, 1);
                UiSetWidgetPos_290f60(D_00484170, 4, 0xB8, 0x153);
                UiSetWidgetPos_290f60(D_00484170, 5, 0xB9, 0x16B);
                o->field00E = 2;
                if (o->field016 == 3) {
                    o->field016 = 2;
                }
            }
            UiSetWidgetPos_290f60(D_00484170, 2, 0xB4,
                        o->field016 * (0x18 - D_0048419C * 4) + 0x136);
        }
    }
}
