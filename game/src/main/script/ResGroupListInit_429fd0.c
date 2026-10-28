/* rgp:protos */
#define RGP_SELF_ResGroupListInit_429fd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s16 id;
    u8 pad[0xE];
} Elem;

typedef struct {
    s32 x0;
    Elem *x4;
    s16 x8;
    __extension__ unsigned short a : 2;
    unsigned short b : 14;
} __attribute__((aligned(2))) Obj;

typedef struct {
    u8 pad[0x164];
    u16 flags;
    u8 pad166[2];
    u8 heap[4];
} Src;

/*rgp*/
/*rgp*/
extern void *memset(void *, s32, s32);
/*rgp*/

s32 ResGroupListInit_429fd0(Obj *self, Src *src, s16 arg2, s32 count, Obj **out, s32 arg5)
{
    s32 n;
    Elem *p;

    if (src != NULL) {
        self->a = src->flags;
    } else {
        self->a = 3;
    }
    self->x0 = arg5;
    self->x8 = arg2;
    self->b = count;
    if (out != NULL) {
        *out = self;
    }
    if (count <= 0) {
        self->x4 = NULL;
        return 0;
    }
    n = count + 1;
    p = ((Elem *)ConstructNewArray_100710(ArenaNewChecked_42c9a0(n * 0x10 + 0x10, src->heap, 4, 4), UiTextElemInit_2931a0, 0, 0x10, n));
    self->x4 = p;
    if (p != NULL) {
        memset(p, 0, n * sizeof(Elem));
        self->x4[count].id = -1;
    } else {
        self->b = 0;
        return 0;
    }
    return 1;
}
