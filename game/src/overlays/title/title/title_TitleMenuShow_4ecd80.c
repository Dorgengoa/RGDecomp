/* rgp:protos */
#define RGP_SELF_title_TitleMenuShow_4ecd80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004ECD80 -- turn a group of sub-parts on or off.  Both
 * `beql` delay slots carry the NEXT block's load, so these are ordinary
 * independent tests, not an epilogue merge.
 */

typedef struct Obj_title_FUN_004ecd80 {
    u8 pad000[0x4];
    void *field004;    /* +0x4 */
} Obj_title_FUN_004ecd80;

extern s16 D_0048419C;
extern f32 D_0047D578;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 title_TitleMenuShow_4ecd80(Obj_title_FUN_004ecd80 *o)
{
    UiSetWidgetsVisibleById_291110(o->field004, 1, 1, 1);
    if (IsTgsDemoBuild_207f20() != 0) {
        UiSetWidgetsVisibleById_291110(o->field004, 3, 0, 1);
        UiSetWidgetsVisibleById_291110(o->field004, 4, 0, 1);
        UiSetWidgetsVisibleById_291110(o->field004, 5, 0, 1);
        UiSetWidgetsVisibleById_291110(o->field004, 0x66, 0, 1);
    }
    if (D_0048419C != 0) {
        UiSetWidgetsVisibleById_291110(o->field004, 0x66, 1, 1);
    } else {
        UiSetWidgetsVisibleById_291110(o->field004, 0x66, 0, 1);
    }
    UiSetWidgetAlpha_2907a0(o->field004, 1, 0.0f);
    UiFadeWidgetAlpha_290690(o->field004, 1, 1.0f, D_0047D578, -1.0f);
    return 1;
}
