/* rgp:protos */
#define RGP_SELF_ActDataEvnt_23bfe0 1
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

s32 ActDataEvnt_23bfe0(void *a, s32 b)
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
    if (((E *)ActDataGetEvntList_225d20(h)) == NULL || ((short)ActDataGetEvntCount_225cf0(h)) >= 0x20) {
        return 1;
    }
    base = ((E *)ActDataGetEvntList_225d20(h));
    if (ScriptCallBuildCharaCmd_23f980(&base[((short)ActDataGetEvntCount_225cf0(h))], a, b) != 0) {
        ActDataSetEvntCount_225cc0(h, ((short)ActDataGetEvntCount_225cf0(h)) + 1);
    }
    return 1;
}
