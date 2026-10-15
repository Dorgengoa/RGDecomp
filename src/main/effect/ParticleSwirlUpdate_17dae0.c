#include "types.h"
#include "vec.h"

typedef struct Part {
    Vec4 pos;       /* 0x00 */
    f32 s;          /* 0x10 */
    s32 t;          /* 0x14 */
    s32 life;       /* 0x18 */
    u8 pad1C[4];
} Part;

typedef struct Obj {
    s32 on;         /* 0x00 */
    u8 pad4[0xC];
    Vec4 base;      /* 0x10 */
    u8 pad20[0x70];
    Part part[20];  /* 0x90 */
} Obj;

extern f32 Sinf_128fd0(f32);
extern s32 Rand_133710(void);
extern void *memset(void *, s32, u32);
extern f32 D_0047D1FC;
extern f32 D_0047D288;
extern f32 D_0047DADC;

void ParticleSwirlUpdate_17dae0(Obj *__restrict o)
{
    Part *free;
    Part *p;
    s32 i;
    s32 k;

    if (o->on == 0) {
        return;
    }
    free = 0;
    for (i = 0; i < 20; i++) {
        p = &o->part[i];
        if (p->life <= 0) {
            free = p;
            break;
        }
        if (!(p->t < p->life)) {
            memset(p, 0, 0x20);
            continue;
        }
        k = i * 2;
        p->pos.y += D_0047D288;
        p->pos.x = o->base.x + 5.0f * Sinf_128fd0(D_0047D1FC * ((f32)(p->t + k) / 10.0f));
        p->pos.z = o->base.z + 5.0f * Sinf_128fd0(D_0047D1FC * ((f32)(p->t + k + 10) / 8.0f));
        p->s -= D_0047DADC;
        p->t++;
    }
    if (free != 0) {
        free->pos = o->base;
        free->s = 7.0f;
        free->t = Rand_133710() % 20;
        free->life = 30;
    }
}
