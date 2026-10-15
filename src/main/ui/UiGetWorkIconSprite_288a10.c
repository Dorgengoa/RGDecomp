#include "types.h"

extern void  WorkIconCopyItemIcon_28df20(void *cfg, s32 id);
extern char *strcpy(char *d, const char *s);
extern char  D_00460EB8[];

typedef struct Cfg {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} Cfg;

typedef struct Info {
    s32  id;      /* +0x00 */
    char name[16];/* +0x04 */
    s16  m14;
    s16  m16;
    s16  m18;
    s16  m1A;
} Info;

s32 UiGetWorkIconSprite_288a10(s32 id, Info *out)
{
    Cfg cfg;

    if (out == 0) {
        return 0;
    }
    if (id >= 0) {
        cfg.a = 0;
        cfg.c = 0x20;
        cfg.d = 0x20;
        cfg.b = 0x40;
        WorkIconCopyItemIcon_28df20(&cfg, id);
        strcpy(out->name, D_00460EB8);
        out->id = 0x32B;
        out->m14 = 0;
        out->m16 = 0x40;
        out->m18 = 0x20;
        out->m1A = 0x20;
    } else {
        out->id = 0;
        out->m16 = 0;
        out->m14 = 0;
        out->m1A = 0;
        out->m18 = 0;
        return 0;
    }
    return 1;
}
