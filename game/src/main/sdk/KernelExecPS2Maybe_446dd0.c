/* rgp:protos */
#define RGP_SELF_KernelExecPS2Maybe_446dd0 1
#include "port/game_protos.h"
#line 1
typedef struct { int w0, w4, status, entry, w10, gp; unsigned short h18, h1a; int w1c, w20, w24, w28, w2c, entry2, argc, args; char pad[0x4C - 0x3C]; } T;
extern int *D_80074728;
extern int *D_8007472C;
extern int (*D_80074730)(int);
extern int (*D_80074734)(int, int);
extern int (*D_80074738)(void);
extern int (*D_8007473C)(void);
extern int (*D_80074740)(int);
extern int (*D_80074744)(int);
extern T *D_80074748;
extern void (*D_80074768)(void);
extern void (*D_8007476C)(void);
extern int (*D_80074770)(int, char *);
extern int D_80074778;
extern void func_0743C8(void);
int KernelExecPS2Maybe_446dd0(int entry, int gp, int argc, char **argv)
{
    int cur, i, p;
    cur = *D_80074728;
    D_80074730(cur);
    D_80074734(cur, 0);
    for (i = 1; i < 0x100; i++) {
        int st = D_80074748[i].status;
        if (st == 0) continue;
        if (i == cur) continue;
        if (st == 0x10) {
            D_80074740(i);
        } else {
            D_80074744(i);
            D_80074740(i);
        }
    }
    D_8007473C();
    D_80074738();
    *D_8007472C = 0;
    func_0743C8();
    p = D_80074778;
    for (i = 0; i < argc; i++)
        p = D_80074770(p, argv[i]);
    D_80074748[cur].entry = entry;
    D_80074748[cur].args = D_80074778;
    D_80074748[cur].h18 = 0;
    D_80074748[cur].w24 = 0;
    D_80074748[cur].w1c = 0;
    D_80074748[cur].w20 = 0;
    D_80074748[cur].gp = gp;
    D_80074748[cur].entry2 = entry;
    D_80074748[cur].argc = argc;
    D_80074748[cur].h1a = 0;
    D_8007476C();
    D_80074768();
    return entry;
}
