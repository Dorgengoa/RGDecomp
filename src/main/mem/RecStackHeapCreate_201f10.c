#include "types.h"

extern void *GetCurrentScene_1f5be0(char *a);
extern s32   RecStackPush_1c4240(void *h, const char *c);
extern void *RecStackGetSlot_1c4330(void *h, s32 id);
extern void *MemStackAllocAligned64_14da10(void *q, void *d);
extern void  MemStackHeapInit_14dee0(char *a, void *p, void *d);
extern void  MemStackHeapReinit_14de90(char *a);
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
    h = GetCurrentScene_1f5be0(a);
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
