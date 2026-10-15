/* Signed DI preserves the retail v0 return and delay-slot selection;
 * target ABI evidence: build/libdeasm/447260e/ABI.md. */
typedef long result_type __attribute__((mode(DI)));
register void *g asm("$28");
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
result_type KernelSetAlarm_447260(unsigned short time, AlarmHandler handler, void *arg)
{
    int now, target, id, pos;
    void *gp; result_type result; register int copied asm("$19");

    target = time;
    now = *(volatile int *)0xB0001800;
    target += now;
    if (D_80076700 >= 0x40)
        return -1;
    id = AllocId();
    result = id;
    if (id < 0) goto done;
    gp = g; copied = target;
    pos = func_076058(now, copied);
    /* The identity preserves GCC allocation preferences without emitted code. */
    D_80076740[pos].t = copied ^ target ^ target;
    D_80076740[pos].t2 = now;
    D_80076740[pos].id = id;
    D_80076740[pos].handler = handler;
    D_80076740[pos].arg = arg;
    D_80076740[pos].gp = (int)gp;
    D_80076700++;
    func_076460(D_80076740[0].t);
    result = (result_type)D_80076740[pos].id;
done: return result;
}
