/* rgp:protos */
#define RGP_SELF_MapSceneCfgImg_193600 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct T {
    s32  lim;
    void *arr[1];
} T;

extern T   *D_004812F4;
extern s32  D_004812F8;
extern s32  D_004812FC;
/*rgp*/
extern s32   strlen(const char *s);
extern char *strcpy(char *d, const char *s);
/*rgp*/

s32 MapSceneCfgImg_193600(void *argv, s32 argc)
{
    char *s;
    void *p;
    u32 len;
    u32 n;

    if (D_004812FC >= D_004812F4->lim || argc <= 0) {
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
    D_004812F4->arr[D_004812FC] = p;
    D_004812FC = D_004812FC + 1;
    return 1;
}
