#include "types.h"
#pragma opt_common_subs off

class E28 {
public:
    u8 pad0[0x20];
    VC_VPTR_MEMBER; void init() { VCM0(void, 0x8); }
    s32 unk24;
};

struct E58 {
    u8 pad[0x58];
};

struct Own001c6fe0 {
    u8 pad0[0x100];
    E58 a[64];
    u8 pad1700[0x1814 - 0x1700];
    E28 b[224];
    u8 pad3B14[4];
    E28 c[8];
    u8 pad3C58[4];
    E28 d[20];
    u8 pad3F7C[4];
    E28 e[4];
    u8 m4020[0x4360 - 0x4020];
    u8 m4360[0x4394 - 0x4360];
    void *vt;
};

extern "C" {
void MemStackCtor_14e030(E58 *);
void SceneTableInit_196130(E28 *);
void SceneWindInit_1c39e0(u8 *);
extern u8 D_004710F0[];
extern u8 D_00471100[];
extern u8 D_00471110[];
extern u8 D_00471120[];
extern u8 D_00471130[];
extern u8 D_004711F8[];
}

struct E28raw {
    u8 pad[0x20];
    void *vt;
};

#define SETVT(p, v) (((E28raw *)(p))->vt = (v))

extern "C" Own001c6fe0 *SceneCtor_1c6fe0(Own001c6fe0 *self)
{
    E58 *q;
    E28 *p;
    E28 *end;

    self->vt = D_004710F0;
    q = self->a;
    do {
        MemStackCtor_14e030(q);
        q++;
    } while (q < &self->a[64]);
    p = self->b;
    do {
        SETVT(p, D_00471130);
        p->init();
        SETVT(p, D_00471120);
        p->init();
        p++;
    } while (p < &self->b[224]);
    p = self->c;
    do {
        SETVT(p, D_00471130);
        p->init();
        SETVT(p, D_00471100);
        p->init();
        p++;
    } while (p < &self->c[8]);
    p = self->d;
    do {
        SETVT(p, D_00471130);
        p->init();
        SETVT(p, D_00471110);
        p->init();
        p++;
    } while (p < &self->d[20]);
    p = self->e;
    do {
        SETVT(p, D_00471130);
        p->init();
        SETVT(p, D_004711F8);
        p->init();
        p++;
    } while (p < (end = &self->e[4]));
    SceneTableInit_196130(end);
    SceneWindInit_1c39e0(self->m4360);
    return self;
}
