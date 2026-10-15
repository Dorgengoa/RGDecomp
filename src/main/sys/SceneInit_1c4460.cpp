#include "types.h"

class E28 {
public:
    u8 pad0[0x20];
    virtual void init();
    s32 unk24;
};

struct E58 {
    u8 pad[0x58];
};

struct Own001c4460 {
    s32 w0[64];
    E58 a[64];
    s32 unk1700;
    s32 w1704[64];
    s32 unk1804;
    s32 unk1808;
    s32 unk180C;
    s32 n1810;
    E28 b[224];
    s32 n3B14;
    E28 c[8];
    s32 n3C58;
    E28 d[20];
    s32 n3F7C;
    E28 e[4];
    u8 m4020[0x4340 - 0x4020];
    s32 unk4340;
    s32 unk4344;
    s32 unk4348;
    s32 unk434C;
    s32 unk4350;
    u8 pad4354[0x4380 - 0x4354];
    s32 unk4380;
};

extern "C" {
void MemStackClear_14dff0(E58 *);
void SceneTableInit_196130(u8 *);
}

extern "C" void SceneInit_1c4460(Own001c4460 *self)
{
    s32 i;

    for (i = 0; i < 64; i++) {
        self->w0[i] = 0;
        self->w1704[i] = -1;
        MemStackClear_14dff0(&self->a[i]);
    }
    self->unk1700 = -1;
    self->unk1804 = 0;
    self->unk4350 = -1;
    self->unk180C = 0;
    self->unk1808 = 0;
    self->n1810 = 0xE0;
    for (i = 0; i < self->n1810; i++) {
        self->b[i].init();
    }
    self->n3B14 = 8;
    for (i = 0; i < self->n3B14; i++) {
        self->c[i].init();
    }
    self->n3C58 = 0x14;
    for (i = 0; i < self->n3C58; i++) {
        self->d[i].init();
    }
    self->unk4380 = -1;
    self->n3F7C = 4;
    for (i = 0; i < self->n3F7C; i++) {
        self->e[i].init();
    }
    SceneTableInit_196130(self->m4020);
    self->unk4340 = -1;
    self->unk4344 = -1;
    self->unk4348 = -1;
    self->unk434C = -1;
}
