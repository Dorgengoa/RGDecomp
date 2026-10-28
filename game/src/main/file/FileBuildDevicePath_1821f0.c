/* rgp:protos */
#define RGP_SELF_FileBuildDevicePath_1821f0 1
#define RGP_SELF_clr 1
#define RGP_SELF_clr2 1
#define RGP_SELF_clr3 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern s8 *strcat(s8 *, const s8 *);
extern s8 *strcpy(s8 *, const s8 *);
extern s8 D_00459740[];
extern s8 D_00459748[];
extern s32 D_0047E00C;
extern s8 D_00495EB0[];

static inline void clr(s8 *p, u32 n) {
    if (p != NULL) {
        do {
            *p = 0;
            n -= 1;
            p += 1;
        } while (n != 0);
    }
}

static inline void clr2(void *d, s32 n) {
    s8 *p = d;
    if (p != NULL) {
        do {
            *p++ = 0;
        } while (--n != 0);
    }
}

static inline void clr3(void *d, u32 n) {
    s8 *p = d;
    if (p != NULL) {
        do {
            *p = 0;
            n -= 1;
            p += 1;
        } while (n != 0);
    }
}

s32 FileBuildDevicePath_1821f0(u8 *arg0, s8 *arg1)
{
    s32 sp15C;
    s8 sp50[0x100] __attribute__((aligned(16)));
    s8 sp40[0x10] __attribute__((aligned(16)));
    s32 var_16;
    s32 var_2;
    s8 *var_3;
    s32 temp_2;
    u8 *junk;
    s8 c;

    sp15C = 0;
    var_16 = PathParseDevice_182350((void *)arg0, sp50, &sp15C);
    if (var_16 == -1) {
        var_16 = D_0047E00C;
        if (*(s8 *)(arg0 + 0x1) == 0x3A) {
            sp15C = 1;
        }
    } else {
        sp15C = 1;
    }
    clr(sp40, 0x10);
    if (var_16 == 0) {
        strcpy(sp40, D_00459740);
    }
    if (var_16 == 3) {
        strcpy(sp40, D_00459748);
    }
    strcpy(arg1, sp40);
    if (sp15C == 0) {
        strcat(arg1, D_00495EB0);
    }
    strcat(arg1, sp50);
    if (var_16 == 3) {
        temp_2 = *arg1;
        while (temp_2 != 0) {
            c = temp_2;
            if (c >= 0x41 && c < 0x5B) {
                *arg1 += 0x20;
            }
            arg1 += 1;
            temp_2 = *arg1;
        }
    }
    return var_16;
}
