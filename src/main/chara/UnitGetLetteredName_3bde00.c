#include "types.h"
extern void strcpy(char *arg0, char *arg1);
extern s32 strlen(char *arg0);
extern char *D_00454650[26];

void UnitGetLetteredName_3bde00(void *arg0, char *arg1)
{
    s32 len;
    s32 c;
    void *p;
    char *d;
    char *s;

    if (arg1 == 0 || (p = *(void **)((u8 *)arg0 + 0x234)) == NULL) {
        return;
    }
    {
        strcpy(arg1, *(char **)((u8 *)p + 4));
        len = strlen(arg1);
        c = *(s8 *)((u8 *)arg0 + 0x238);
        if (c != 0) {
            c -= 0x41;
            if (c >= 0 && c < 26) {
                s = D_00454650[c];
                d = arg1 + len;
                d[0] = s[0];
                d[1] = s[1];
                d[2] = 0;
            }
        }
    }
}
