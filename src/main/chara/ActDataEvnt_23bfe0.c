#include "types.h"

typedef struct E {
    u8 pad[0xC];
} E;

extern void *ActCfgGetCurTable_23ff20(void);
extern E    *ActDataGetEvntList_225d20(void *h);
extern s32   ActDataGetEvntCount_225cf0(void *h);
extern void  ActDataSetEvntCount_225cc0(void *h, s32 n);
extern s32   ScriptCallBuildCharaCmd_23f980(E *e, void *a, s32 b);

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
    if (ActDataGetEvntList_225d20(h) == NULL || ActDataGetEvntCount_225cf0(h) >= 0x20) {
        return 1;
    }
    base = ActDataGetEvntList_225d20(h);
    if (ScriptCallBuildCharaCmd_23f980(&base[ActDataGetEvntCount_225cf0(h)], a, b) != 0) {
        ActDataSetEvntCount_225cc0(h, ActDataGetEvntCount_225cf0(h) + 1);
    }
    return 1;
}
