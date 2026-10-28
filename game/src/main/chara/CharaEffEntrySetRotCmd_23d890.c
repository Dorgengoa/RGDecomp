/* rgp:protos */
#define RGP_SELF_CharaEffEntrySetRotCmd_23d890 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec;

/*rgp*/
/*rgp*/
extern u8 D_004BCE60[0x400];
extern u8 D_004BCE8C[0x400];


s32 CharaEffEntrySetRotCmd_23d890(u8 *arg0, s32 arg1) {
    Vec a __attribute__((aligned(16)));
    Vec b __attribute__((aligned(16)));
    s32 base;

    if (arg1 != 1 && arg1 != 3) {
        return 0;
    }
    if (*(s32 *)D_004BCE60 == 0 || *(s16 *)D_004BCE8C >= 0x80) return 1;
    base = *(s32 *)D_004BCE60 + *(s16 *)D_004BCE8C * 0x7C;
    if (arg1 == 1) {
        {
            u8 *q = (u8 *)&a;
            u32 n = 16;
            if (q != NULL) {
                do {
                    *q = 0;
                    n--;
                    q++;
                } while (n != 0);
            }
        }
        a.y = ScriptArgGetFloat_23fbc0(arg0);
        CharaEffEntrySetRot_230080(base, &a);
    } else {
        {
            u8 *q = (u8 *)&b;
            u32 n = 16;
            if (q != NULL) {
                do {
                    *q = 0;
                    n--;
                    q++;
                } while (n != 0);
            }
        }
        b.x = ScriptArgGetFloat_23fbc0(arg0);
        b.y = ScriptArgGetFloat_23fbc0(arg0 + 8);
        b.z = ScriptArgGetFloat_23fbc0(arg0 + 0x10);
        CharaEffEntrySetRot_230080(base, &b);
    }
    return 1;
}
