#include "types.h"

typedef struct Obj00426d70B {
    u8 pad0[0x8];
    void *unk8;
} Obj00426d70B;

typedef struct Obj00426d70C {
    u8 pad0[0x78];
    s32 unk78;
} Obj00426d70C;

typedef struct Obj00426d70A {
    void *unk0;
    s32 unk4;
    s16 unk8;
} Obj00426d70A;

extern void D_00472250(void);
extern void D_0047C730(void);
extern void D_0047C8B0(void);

Obj00426d70A *TreasureBoxViewCtor_426d70(Obj00426d70A *self, Obj00426d70B *arg1, s16 arg2)
{
    self->unk0 = &D_00472250;
    self->unk0 = &D_0047C8B0;
    self->unk0 = &D_0047C730;
    if (arg1 != NULL) {
        self->unk4 = ((Obj00426d70C *)arg1->unk8)->unk78;
    } else {
        self->unk4 = 0;
    }
    self->unk8 = arg2;
    return self;
}
