#include "types.h"

typedef struct {
    u8 pad0[0x10];
    s16 unk10;
    u8 pad12[0x14 - 0x12];
    s16 unk14;
    u8 pad16[0x18 - 0x16];
    s16 unk18;
    s16 unk1A;
    u8 pad1C[0x20 - 0x1C];
    s32 unk20;
} Elem0033C060;

extern s32 ConstructNewArray_100710(s32, void *, s32, s32, s32);
extern s32 MemStackNew_14e1b0(s32);
extern void StatusEffectSlotCtor_33c0f0(void);

void StatusEffectSlotsAlloc_33c060(Elem0033C060 **arg0) {
    s32 i;
    Elem0033C060 *p;

    *arg0 = (Elem0033C060 *)ConstructNewArray_100710(MemStackNew_14e1b0(0xE10), (void *)StatusEffectSlotCtor_33c0f0, 0, 0xE0, 0x10);
    i = 0;
    do {
        p = (Elem0033C060 *)((u8 *)*arg0 + (i * 0xE0));
        i += 1;
        p->unk10 = 0;
        p->unk14 = -1;
        p->unk18 = -1;
        p->unk1A = -1;
        p->unk20 = -1;
    } while (i < 0x10);
}
