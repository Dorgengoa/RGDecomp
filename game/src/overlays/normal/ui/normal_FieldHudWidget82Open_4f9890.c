/* rgp:protos */
#define RGP_SELF_normal_FieldHudWidget82Open_4f9890 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F9890 -- open widget 0x82 only when func_1FEDE0's record says
 * mode 1.  The `beql` on the null test carries the shared `ld $31`. */

typedef struct Obj {
    u8  pad000[0x378];
    s16 f378;
    u8  pad37A[0x4A4 - 0x37A];
    s16 f4A4;
} Obj;

typedef struct Sub { u8 pad00[0x22]; s16 f22; } Sub;
typedef struct Rec { u8 pad00[0xC]; Sub *f0C; } Rec;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_FieldHudWidget82Open_4f9890(Obj *p)
{
    Rec *r;

    if (p->f378 != 0) {
        r = ((Rec *)GetGameData_1fede0());
        if (r == NULL) {
            return;
        }
        if (r->f0C->f22 == 1) {
            UiSetWidgetsVisibleById_291110(p, 0x82, 1, 1);
            UiSetWidgetPos_290f60(p, 0x82, 0x12, 0x5A);
            UiSetWidgetAlpha_2907a0(p, 0x82, 1.0f);
            p->f4A4 = 1;
        }
    }
}
