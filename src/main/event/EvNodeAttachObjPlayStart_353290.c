#include "types.h"

struct T353290 { u8 pad000[0xD0]; u32 fD0; u8 pad0D4[0x64]; u8 f138[0x10]; s16 f148; s16 f14A; };

extern const char D_00462998[];
extern char *strcpy(char *dst, const char *src);

s32 EvNodeAttachObjPlayStart_353290(struct T353290 *p)
{
    s32 ok;

    ok = !(p->fD0 & 0x80000000);
    if (ok) goto run;
    return 0;
run:
    strcpy((char *)p->f138, D_00462998);
    p->f14A = 0;
    p->f148 = 1;
    return 1;
}
