/* rgp:protos */
#define RGP_SELF_MenuBattleIconStackInit_206710 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_00481BD4;
extern char D_004BBCE0[];
extern char D_0045C4D0[];
extern u32 strlen(const char *s);
extern void strcpy(char *d, const char *s);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MenuBattleIconStackInit_206710(void)
{
    void *p;

    if (D_00481BD4 != 0) {
        return 0;
    }
    p = GetLoaderMgr_1f59d0();
    if (p != 0) {
        MemStackClear_14dff0(D_004BBCE0);
        MemStackInit_14d810(D_004BBCE0, HeapHandleAllocBack_1cdb10(p, 0x1900), 0x1900);
        if (strlen(D_0045C4D0) < 0x10) {
            strcpy(D_004BBCE0, D_0045C4D0);
        }
        MemStackReset_14d830(D_004BBCE0);
        MemStackAlign64_14d8e0(D_004BBCE0);
        D_00481BD4 = 1;
    }
    return 0;
}
