/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageAbilityScrollSettle_504d50 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00504D50 -- two mirrored arms keyed on p->f078 (1 or 2); each asks
 * func_2910A0 for a cursor pair, checks the SECOND out-parameter against a
 * sentinel, then re-lays the four rows and clears f078.
 *
 * f078 is loaded ONCE into $3 and compared against 1 then 2, so it is a NAMED
 * local, not two field reads. */

typedef struct Obj { u8 pad000[0x78]; s16 f078; } Obj;

/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_BtlChgPageAbilityScrollSettle_504d50(Obj *p)
{
    void *w;
    s32 x;
    s32 y;
    s16 t;

    w = normal_UiPageGetLayout_289b60(p);
    t = p->f078;
    if (t == 1) {
        UiGetWidgetPos_2910a0(w, 0xB, &x, &y);
        if (y == 0x68) {
            UiSetWidgetPos_290f60(w, 5, 0, 0x19);
            UiSetWidgetPos_290f60(w, 8, 0, 0x33);
            UiSetWidgetPos_290f60(w, 0xB, 0, 0x4D);
            UiSetWidgetPos_290f60(w, 0xE, 0, 0x67);
            p->f078 = 0;
            return 1;
        }
    } else if (t == 2) {
        UiGetWidgetPos_2910a0(w, 5, &x, &y);
        if (y == -1) {
            UiSetWidgetPos_290f60(w, 5, 0, 0x19);
            UiSetWidgetPos_290f60(w, 8, 0, 0x33);
            UiSetWidgetPos_290f60(w, 0xB, 0, 0x4D);
            UiSetWidgetPos_290f60(w, 0xE, 0, 0x67);
            p->f078 = 0;
            return 1;
        }
    }
    return 0;
}
