#include "types.h"

extern const char D_0045F110[];
extern const char D_0045F128[];
extern const char D_0045F130[];
extern char *strcpy(char *d, const char *s);
extern char *strcat(char *d, const char *s);

s32 VoicePakCheckStubMaybe_261f80(char *unused, char *b, char *c)
{
    char b1[0x40];
    char b2[0x40];

    strcpy(b1, D_0045F110);
    strcat(b1, b);
    strcat(b1, D_0045F128);
    strcat(b2, c);
    strcat(b2, D_0045F130);
    return 1;
}
