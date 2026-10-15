#include "types.h"

/* Member of the 2-member BYTE-IDENTICAL group headed by VoiceFileCheckStubMaybe_2618c0; the shape and
   every lever are documented there.  Build "<prefix><name><suffix>" in a 0x40-byte stack buffer
   and throw it away -- the result is never read, so this is a stub whose body
   survived because the string calls are external.  The first parameter is
   unused; `$4` is overwritten with the buffer address at entry. */

extern char *strcpy(char *, const char *);
extern char *strcat(char *, const char *);

extern char D_0045F0F8[];
extern char D_0045F108[];

s32 VoiceFileCheckStubMaybe_261f30(void *unused, const char *name)
{
    char buf[0x40];

    strcpy(buf, D_0045F0F8);
    strcat(buf, name);
    strcat(buf, D_0045F108);
    return 1;
}
