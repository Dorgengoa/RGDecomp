/* rgp:protos */
#define RGP_SELF_MenuObjBreedSlotAssign_385950 1
#define RGP_SELF_find00385950 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Item00385950 {
    s32 unk0;
    s32 unk4;
} Item00385950;

/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_00463EC0[0x400];
extern u8 D_004832A0;

static inline Item00385950 *find00385950(s32 arg0) {
    s32 i;
    Item00385950 *p;
    for (i = 0; i < 2; i++) {
        p = (Item00385950 *)(arg0 + i * 0x7A0 + 0x13B0);
        if (((unsigned char)MenuObjSlotIsActive_3849d0(p)) == 0) {
            return p;
        }
    }
    return NULL;
}

void MenuObjBreedSlotAssign_385950(s32 arg0, s32 arg1, s32 arg2) {
    Item00385950 *p;

    if (arg1 == 0 || arg2 == 0) {
        return;
    }
    p = find00385950(arg0);
    if (p == NULL) {
        return;
    }
    ModelObjPlayMotionByName_1867a0((u8 *)p + 0x10, D_00463EC0, 0);
    p->unk0 = arg1;
    p->unk4 = arg2;
    InsectCageSePlay_3844b0(&D_004832A0, 2);
}
