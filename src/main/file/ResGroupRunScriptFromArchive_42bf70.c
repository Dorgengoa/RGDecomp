#include "types.h"

extern char * strcpy(char *, const char *);
extern char * strcat(char *, const char *);
extern void * ArchiveGetFileByPath_1c2800(s32, char *, s32 *);
extern s32 ResGroupRunScript_42be50(s32, s32, void *, s32);

/* `h == 0 || len <= 0` : the two tests branch the SAME way to the join, and
   the shared `h = 0` is duplicated into the beql delay slot.
   The trailing andi 0xFF is the u8 return. */

extern char *D_00480260;

u8 ResGroupRunScriptFromArchive_42bf70(s32 p0, s32 p1, s32 p2, char *p3)
{
    s32 len;
    char buf[140];
    void *h;

    strcpy(buf, p3);
    strcat(buf, D_00480260);
    len = 0;
    h = ArchiveGetFileByPath_1c2800(p2, buf, &len);
    if (h == 0 || len <= 0) {
        h = 0;
    }
    if (h == 0) {
        return 0;
    }
    return ResGroupRunScript_42be50(p0, p1, h, len);
}
