#include "eekernel.h"

typedef unsigned long u64 __attribute__((mode(DI)));
typedef struct { unsigned short t; unsigned short t2; int id; int w[3]; } A;
extern int D_80076700;
extern u64 D_80076708;
extern A D_80076740[];
typedef long s64 __attribute__((mode(DI)));
extern int func_076038(int, s64);
extern void func_076460(unsigned short);
int KernelReleaseAlarm_4473a0(int id)
{
    int i, j, n;
    int ret = -1;
    int t;

    if (D_80076700 > 0) {
        for (i = 0; i < D_80076700; i++) {
            if (id == D_80076740[i].id) {
                if (D_80076740[i].t == *(volatile int *)0xB0001820 && (*(volatile int *)0x1000F000 & 0x1000))
                    return -1;
                t = D_80076740[i].t2;
                for (j = i; j < D_80076700 - 1; j++)
                    D_80076740[j] = D_80076740[j + 1];
                D_80076700--;
                D_80076708 &= ~((u64)1 << id);
                if (i == 0)
                    func_076460(D_80076740[0].t);
                if (D_80076700 == 0)
                    *(volatile int *)0xB0001810 = 0x83;
                {
                    int *tp = (int *)0xB0001800;
                    if (t)
                        tp = (int *)((unsigned)tp ^ (unsigned)t ^ (unsigned)t);
                    ret = func_076038(t, *tp) - t;
                }
                break;
            }
        }
    }
    SyncLoad();
    return ret;
}
