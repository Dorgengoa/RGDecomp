#include "types.h"

extern void *ArchiveGetFileByPath_1c2800(void *, void *, s32 *);
extern s32 MsgTableParseText_28aab0(void *, void *, s32);

s32 MsgTableLoadFromArchive_202a50(void *a, void *b, void *c)
{
    s32 len;
    void *r;
    if (a == 0) goto zero;
    if (b == 0) goto zero;
    if (c != 0) goto ok;
zero:
    return 0;
ok:
    len = 0;
    r = ArchiveGetFileByPath_1c2800(a, b, &len);
    if (r == 0) goto zero2;
    if (*(volatile s32 *)&len > 0) goto ok2;
zero2:
    return 0;
ok2:
    return MsgTableParseText_28aab0(c, r, len);
}
