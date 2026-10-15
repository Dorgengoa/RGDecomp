#include "types.h"

extern s32 D_00481BD4;
extern char D_004BBCE0[];
extern char D_0045C4D0[];
extern u32 strlen(const char *s);
extern void strcpy(char *d, const char *s);
extern void *GetLoaderMgr_1f59d0(void);
extern void MemStackClear_14dff0(char *p);
extern s32 HeapHandleAllocBack_1cdb10(void *p, s32 n);
extern void MemStackInit_14d810(char *p, s32 a, s32 n);
extern void MemStackReset_14d830(char *p);
extern void MemStackAlign64_14d8e0(char *p);

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
