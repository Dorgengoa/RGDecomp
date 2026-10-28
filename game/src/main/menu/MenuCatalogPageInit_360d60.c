/* rgp:protos */
#define RGP_SELF_MenuCatalogPageInit_360d60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u32 strlen(const char *);
extern char *strcpy(char *, const char *);
extern void *memset(void *, s32, s32);
extern char D_00462D28[];

struct Req {
    char *name;
    char *name2;
    s32 kind;
    s32 size;
};

void MenuCatalogPageInit_360d60(u8 *o, s32 a, s32 b, s32 c, s32 d)
{
    struct Req req __attribute__((aligned(16)));
    void *p;
    void *h;

    *(s32 *)(o + 0x274) = a;
    *(s32 *)(o + 0x278) = b;
    *(s32 *)(o + 0x27C) = c;
    *(s32 *)(o + 0x280) = d;
    p = GetLoaderMgr_1f59d0();
    if (p != 0) {
        MemStackClear_14dff0(o + 0x178);
        h = HeapHandleAllocBack_1cdb10(p, 0x1400);
        MemStackHeapInit_14dee0(o + 0x178, h, 0x1400);
        if (strlen(D_00462D28) < 0x10) {
            strcpy((char *)(o + 0x178), D_00462D28);
        }
        MemStackHeapReinit_14de90(o + 0x178);
        memset(&req, 0, 0x10);
        req.name = (char *)(o + 0x178);
        req.name2 = (char *)(o + 0x178);
        req.kind = 0x20A;
        req.size = 0x10;
        EffTableInit_1a10f0(o + 0x5C, &req);
        *(s8 *)(o + 0x271) = 0;
    }
}
