/* rgp:protos */
#define RGP_SELF_ResGroupListInit_42a390 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E42a390 {
    u8 pad0[0x30];
    f32 m30;
    f32 m34;
    f32 m38;
    f32 m3C;
    u8 pad40[0x94 - 0x40];
} E42a390;

typedef struct F42a390 {
    s32 m0;
    E42a390 *m4;
    s16 m8;
    __extension__ unsigned short flag : 2;
    unsigned short count : 14;
} __attribute__((aligned(2))) F42a390;

typedef struct O42a390 {
    u8 pad0[0x164];
    u16 m164;
    u8 pad166[2];
    u8 heap[4];
} O42a390;

/*rgp*/
extern void memset(void *, s32, u32);

s32 ResGroupListInit_42a390(F42a390 *arg0, O42a390 *arg1, s16 arg2, s32 arg3, F42a390 **arg4, s32 arg5)
{
    s32 n;
    E42a390 *e;
    s32 i;

    if (arg1 != NULL) {
        arg0->flag = arg1->m164;
    } else {
        arg0->flag = 3;
    }
    arg0->m0 = arg5;
    arg0->m8 = arg2;
    arg0->count = arg3;
    if (arg4 != NULL) {
        *arg4 = arg0;
    }
    if (arg3 <= 0) {
        arg0->m4 = NULL;
        return 0;
    }
    n = arg3 + 1;
    arg0->m4 = ((E42a390 *)ArenaNewChecked_42c9a0(n * 0x94, arg1->heap, 4, 4));
    if (arg0->m4 != NULL) {
        memset(arg0->m4, 0, n * sizeof(E42a390));
        e = arg0->m4;
        for (i = 0; i < arg3; i++, e++) {
            e->m30 = 1.0f;
            e->m34 = 1.0f;
            e->m38 = 1.0f;
            e->m3C = 1.0f;
        }
        return 1;
    }
    arg0->count = 0;
    return 0;
}
