#include "types.h"

typedef struct Node18f {
    struct Node18f *next;
    u8 pad[0xC];
    u8 *data;
} Node18f;

typedef struct {
    s32 unk0;
    Node18f **unk4;
    Node18f *unk8;
} T18fef0_arg0;

static inline u8 *nextnode(T18fef0_arg0 *a) {
    Node18f *p = a->unk8;
    if (p == NULL) {
        return NULL;
    }
    a->unk8 = p->next;
    return p->data;
}

void FuncDataTableCalcKindFlags_18fef0(T18fef0_arg0 *arg0) {
    s32 i;
    s32 fl;
    u8 *e;

    i = 1;
    do {
        arg0->unk8 = NULL;
        if (arg0->unk4 != 0 && i >= 0 && i < 11) {
            arg0->unk8 = arg0->unk4[i];
        }
        fl = 0;
        while ((e = nextnode(arg0)) != NULL) {
            arg0->unk0 |= 1;
            switch (i) {
            case 1:
                fl |= 0x10;
                break;
            case 3:
                fl |= 0xA;
                if (*(s32 *)(e + 0x78) != 0) {
                    fl |= 0x40;
                }
                break;
            case 2:
                fl |= 0x86;
                if (*(s32 *)(e + 0x78) != 0) {
                    fl |= 0x40;
                }
                break;
            case 4:
                fl |= 0x20;
                if (*(s32 *)(e + 0x78) == 2) {
                    fl |= 0x40;
                }
                break;
            case 8:
                fl |= 0x80;
                break;
            case 6:
                fl |= 0x100;
                break;
            }
            arg0->unk0 |= fl;
        }
        i++;
        arg0->unk8 = NULL;
    } while (i < 13);
}
