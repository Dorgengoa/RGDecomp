/* rgp:protos */
#define RGP_SELF_normal_TransMenuLocationNameSet_5173c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005173C0 -- label bring-up: set the string from the name table,
 * and when the item type is 10 append the count through the format string. */

typedef struct Act { u8 pad00[0x4CA0]; s16 f4CA0; } Act;
typedef struct Ent { u8 pad00[0x18]; Act *f18; } Ent;

extern char       normal_D_00527F60[];
extern char normal_D_00526720[];

extern void *D_004846E8;          /* gp - 0xA88 */
extern void *D_00484774;          /* gp - 0x9FC */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void  Sprintf_1343b8(char *dst, const char *fmt, const char *s, s32 n);
/*rgp*/
/*rgp*/

void normal_TransMenuLocationNameSet_5173c0(void *p)
{
    Ent *e;
    s32  n;

    UiSetWidgetVisible_290010(D_004846E8, p, 1, -1);
    e = ((Ent *)GetGameData_1fede0());
    UiSetTextString_28f510(D_004846E8, p, ((char *)MsgTableLookup_28aa30(D_00484774, e->f18->f4CA0)), 0);
    if (PartyGetLocationGroupIdMaybe_3cb150(e->f18) == 10) {
        n = PartyGetFloorNum_3cb000(e->f18);
        if (n > 0) {
            Sprintf_1343b8(normal_D_00527F60, normal_D_00526720,
                        ((char *)MsgTableLookup_28aa30(D_00484774, e->f18->f4CA0)), n);
            UiSetTextString_28f510(D_004846E8, p, normal_D_00527F60, 0);
        }
    }
    UiSetTextFont_290a80(D_004846E8, p, 2, 0);
    UiSetTextColor_290a40(D_004846E8, p, 0xFF303030, 0);
}
