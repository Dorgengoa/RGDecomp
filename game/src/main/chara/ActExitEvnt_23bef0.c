/* rgp:protos */
#define RGP_SELF_ActExitEvnt_23bef0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E {
    u8 pad[0xC];
} E;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 ActExitEvnt_23bef0(void *a, s32 b)
{
    void *h;
    E *base;

    if (b <= 0) {
        return 0;
    }
    h = ActCfgGetCurTable_23ff20();
    if (h == NULL) {
        return 1;
    }
    if (((E *)ActDataGetExitEvntList_225d10(h)) == NULL || ((short)ActDataGetExitEvntCount_225ce0(h)) >= 0x20) {
        return 1;
    }
    base = ((E *)ActDataGetExitEvntList_225d10(h));
    if (ScriptCallBuildCharaCmd_23f980(&base[((short)ActDataGetExitEvntCount_225ce0(h))], a, b) != 0) {
        ActDataSetExitEvntCount_225cb0(h, ((short)ActDataGetExitEvntCount_225ce0(h)) + 1);
    }
    return 1;
}
