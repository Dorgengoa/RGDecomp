#include "types.h"

typedef struct E {
    u8 pad[0xC];
} E;

extern void *ActCfgGetCurTable_23ff20(void);
extern E    *ActDataGetExitEvntList_225d10(void *h);
extern s32   ActDataGetExitEvntCount_225ce0(void *h);
extern void  ActDataSetExitEvntCount_225cb0(void *h, s32 n);
extern s32   ScriptCallBuildCharaCmd_23f980(E *e, void *a, s32 b);

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
    if (ActDataGetExitEvntList_225d10(h) == NULL || ActDataGetExitEvntCount_225ce0(h) >= 0x20) {
        return 1;
    }
    base = ActDataGetExitEvntList_225d10(h);
    if (ScriptCallBuildCharaCmd_23f980(&base[ActDataGetExitEvntCount_225ce0(h)], a, b) != 0) {
        ActDataSetExitEvntCount_225cb0(h, ActDataGetExitEvntCount_225ce0(h) + 1);
    }
    return 1;
}
