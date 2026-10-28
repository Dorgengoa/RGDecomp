/* rgp:protos */
#define RGP_SELF_normal_FieldHudLogClose_4f88b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F88B0 -- hides the 0x79 group: blanks its five 0x7A.. children
 * to fully transparent and clears the 0x3CC flag. */

typedef struct Obj { u8 pad000[0x3CC]; u8 f3CC; } Obj;

/*rgp*/
/*rgp*/

extern void normal_FieldHudLogClose_4f88b0(Obj *p);

void normal_FieldHudLogClose_4f88b0(Obj *p)
{
    u16 id;
    s32 i;

    UiSetWidgetVisible_290010(p, 0x79, 0, -1);
    id = 0x7A;
    for (i = 0; i < 5; i++) {
        UiSetWidgetColor_2905b0(p, id, 0.0f, 0.0f, 0.0f, 0.0f);
        id++;
    }
    p->f3CC = 0;
}
