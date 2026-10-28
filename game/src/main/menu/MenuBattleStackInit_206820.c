/* rgp:protos */
#define RGP_SELF_MenuBattleStackInit_206820 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_00481BCC;
extern char D_004BBC80[];
extern char D_0045C4E8[];
extern u32 strlen(const char *s);
extern void strcpy(char *d, const char *s);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MenuBattleStackInit_206820(void)
{
    void *p;

    if (D_00481BCC != 0) {
        return 0;
    }
    p = GetLoaderMgr_1f59d0();
    if (p != 0) {
        MemStackClear_14dff0(D_004BBC80);
        MemStackInit_14d810(D_004BBC80, HeapHandleAllocBack_1cdb10(p, 0x1890), 0x1890);
        if (strlen(D_0045C4E8) < 0x10) {
            strcpy(D_004BBC80, D_0045C4E8);
        }
        MemStackReset_14d830(D_004BBC80);
        MemStackAlign64_14d8e0(D_004BBC80);
        D_00481BCC = 1;
    }
    return 0;
}
