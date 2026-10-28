/* rgp:protos */
#define RGP_SELF_MapSceneCfgPcp_193530 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct T {
    u8   pad00[0x44];
    s32  lim;
    void *arr[1];
} T;

extern T   *D_004812F4;
extern s32  D_004812F8;
extern s32  D_00481300;
/*rgp*/
extern s32   strlen(const char *s);
extern char *strcpy(char *d, const char *s);
/*rgp*/

s32 MapSceneCfgPcp_193530(void *argv, s32 argc)
{
    char *s;
    void *p;
    u32 len;
    u32 n;

    if (D_00481300 >= D_004812F4->lim || argc <= 0) {
        return 0;
    }
    s = ((char *)SlotGetInt_15f720(argv));
    if (s == NULL) {
        return 0;
    }
    len = strlen(s) + 1;
    if ((len & 0xF) != 0) {
        n = (len >> 4) + 1;
    } else {
        n = len >> 4;
    }
    p = MemStackAllocQw_14d950(D_004812F8, n);
    strcpy(p, s);
    D_004812F4->arr[D_00481300] = p;
    D_00481300 = D_00481300 + 1;
    return 1;
}
