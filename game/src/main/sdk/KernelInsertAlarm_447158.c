/* rgp:protos */
#define RGP_SELF_KernelInsertAlarm_447158 1
#include "port/game_protos.h"
#line 1
typedef struct { unsigned short t; unsigned short pad; int w[4]; } A;
extern int D_80076700;
extern A D_80076740[];
extern int func_076038(int, unsigned short);
int KernelInsertAlarm_447158(int a, int b)
{
    int i, j;
    for (i = 0; i < D_80076700; i++) {
        if (b < func_076038(a, D_80076740[i].t)) {
            for (j = D_80076700 - 1; j >= i; j--)
                D_80076740[j + 1] = D_80076740[j];
            break;
        }
    }
    return i;
}
