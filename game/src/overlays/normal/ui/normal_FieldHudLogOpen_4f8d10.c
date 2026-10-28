/* rgp:protos */
#define RGP_SELF_normal_FieldHudLogOpen_4f8d10 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F8D10 -- shows the 0x79 group: sets the 0x3CC flag, picks the
 * group's variant from the save context's 0x2C field, then drives its five
 * 0x7A.. children to fully opaque white.  `$18 = 0x7A` appears in BOTH arms
 * because the scheduler copies the shared tail store into the `b` delay slot;
 * it is ONE source statement after the if/else. */

typedef struct Obj {
    u8  pad000[0x378];
    s16 f378;
    u8  pad37A[0x3CC - 0x37A];
    u8  f3CC;
} Obj;

typedef struct Sub  { u8 pad000[0x2C]; s16 f02C; } Sub;
typedef struct Root { u8 pad000[0xC]; Sub *f00C; } Root;

/*rgp*/
/*rgp*/
/*rgp*/

extern void normal_FieldHudLogOpen_4f8d10(Obj *p);

void normal_FieldHudLogOpen_4f8d10(Obj *p)
{
    Root *r;
    u16   id;
    s32   i;

    if (p->f378 == 0) {
        return;
    }
    p->f3CC = 1;
    r = ((Root *)GetGameData_1fede0());
    if (r->f00C->f02C == 0) {
        UiSetWidgetVisible_290010(p, 0x79, 0, -1);
    } else {
        UiSetWidgetVisible_290010(p, 0x79, 1, -1);
    }
    id = 0x7A;
    for (i = 0; i < 5; i++) {
        UiSetWidgetColor_2905b0(p, id, 1.0f, 1.0f, 1.0f, 1.0f);
        id++;
    }
}
