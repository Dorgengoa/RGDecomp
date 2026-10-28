/* rgp:protos */
#define RGP_SELF_AllocId 1
#include "port/game_protos.h"
#line 1
typedef unsigned long u64 __attribute__((mode(DI)));
typedef void (*AlarmHandler)(int, unsigned short, void *);
typedef struct { unsigned short t; unsigned short t2; int id; AlarmHandler handler; void *arg; int gp; } A;
extern int D_80076700;
extern u64 D_80076708;
extern A D_80076740[];
extern int func_076058(int, int);
extern void func_076460(unsigned short);
static __inline__ int AllocId(void)
{
    int i;
    u64 m = D_80076708;
    for (i = 0; i < 0x40; i++) {
        if (((m >> i) & 1) == 0) {
            D_80076708 = m | ((u64)1 << i);
            return i;
        }
    }
    return -1;
}
int KernelSetAlarm_447260(unsigned short time, AlarmHandler handler, void *arg); /* [port] asmexclude: gnu-asm body cut -- bound later, see EXCLUDED.tsv */
























