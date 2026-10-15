#include "types.h"

extern s32 RecStackGetSlot_1c4330(void *, s32);
extern void MemStackInit_14d810(s32, s32, s32);
extern u32 strlen(void *);
extern void strcpy(s32, void *);
extern void MemStackRefCountInc_14d7e0(s32);

extern u8 D_0045B060[];

struct Obj0 {
    s32 m00;
    u8 pad004[0x16FC];
    s32 m1700;
};

void SceneMainStackInit_1c4370(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 r0;

    r0 = RecStackGetSlot_1c4330(p0, 0);
    if (r0 != 0) {
        p0->m00 = -1;
        MemStackInit_14d810(r0, p1, p2);
        if (strlen(D_0045B060) < 0x10) {
            strcpy(r0, D_0045B060);
        }
        MemStackRefCountInc_14d7e0(r0);
        p0->m1700 = 0;
    }
}
