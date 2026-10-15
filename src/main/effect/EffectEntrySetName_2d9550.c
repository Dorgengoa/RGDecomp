#include "types.h"

extern char *strcpy(char *, const char *);
extern s32 NameHash16_2e3470(s32);

typedef struct S2D9 {
    u8 pad00[0xBC];
    char name[0xDC - 0xBC];
    s16 fDC;
} S2D9;

void EffectEntrySetName_2d9550(S2D9 *o, const char *src)
{
    if (src != 0) {
        strcpy(o->name, src);
        o->fDC = (s16)NameHash16_2e3470((s32)o->name);
    }
}
