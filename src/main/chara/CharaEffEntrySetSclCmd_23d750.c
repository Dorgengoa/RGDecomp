#include "types.h"

typedef struct {
    u8 pad[0x7C];
} E7C;

extern void CharaEffEntrySetScale_230050(E7C *arg0, f32 *arg1);
extern f32 ScriptArgGetFloat_23fbc0(u8 *arg0);
extern E7C *D_004BCE60[];
extern s16 D_004BCE8C[];

s32 CharaEffEntrySetSclCmd_23d750(u8 *arg0, s32 arg1)
{
    f32 b[4];
    f32 a[4];
    E7C *p;
    f32 f;
    u8 *q;
    u32 n;

    if (arg1 != 1 && arg1 != 3) {
        return 0;
    }
    if (D_004BCE60[0] == NULL || D_004BCE8C[0] >= 0x80) {
        return 1;
    }
    p = &D_004BCE60[0][D_004BCE8C[0]];
    if (arg1 == 1) {
        f = ScriptArgGetFloat_23fbc0(arg0);
        q = (u8 *)b;
        n = 0x10;
        if (q != NULL) {
            do {
                *q = 0;
                n--;
                q++;
            } while (n != 0);
        }
        b[0] = f;
        b[1] = f;
        b[2] = f;
        CharaEffEntrySetScale_230050(p, b);
        return 1;
    }
    q = (u8 *)a;
    n = 0x10;
    if (q != NULL) {
        do {
            *q = 0;
            n--;
            q++;
        } while (n != 0);
    }
    a[0] = ScriptArgGetFloat_23fbc0(arg0);
    a[1] = ScriptArgGetFloat_23fbc0(arg0 + 8);
    a[2] = ScriptArgGetFloat_23fbc0(arg0 + 0x10);
    CharaEffEntrySetScale_230050(p, a);
    return 1;
}
