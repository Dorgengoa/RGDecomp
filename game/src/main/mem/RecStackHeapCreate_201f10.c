/* rgp:protos */
#define RGP_SELF_RecStackHeapCreate_201f10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u32   strlen(const char *s);
extern char *strcpy(char *d, const char *s);

s32 RecStackHeapCreate_201f10(char *a, s32 *b, const char *c, void *d)
{
    void *h;
    s32   id;
    void *p;

    if (a == 0) goto bad;
    if (b == 0) goto bad;
    if (c != 0) goto ok;
bad:
    return -1;
ok:
    if (*b >= 0) return *b;
    *b = -1;
    h = GetCurrentScene_1f5be0();
    id = RecStackPush_1c4240(h, c);
    if (id < 0) return -1;
    p = MemStackAllocAligned64_14da10(RecStackGetSlot_1c4330(h, id), d);
    if (p == 0) return -1;
    MemStackHeapInit_14dee0(a, p, d);
    if (strlen(c) < 0x10) strcpy(a, c);
    MemStackHeapReinit_14de90(a);
    *b = id;
    return id;
}
