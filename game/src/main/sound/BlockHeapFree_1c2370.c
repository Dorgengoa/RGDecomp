/* rgp:spin */ extern void rg_spin_hint(unsigned int); extern void rg_spin_halt(unsigned int);
#line 1
/* rgp:protos */
#define RGP_SELF_BlockHeapFree_1c2370 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct N2370 {
    s32 key;
    s32 x4;
    s32 x8;
    struct N2370 *next;
    struct N2370 *prev;
} N2370;

void BlockHeapFree_1c2370(N2370 *arg0, s32 arg1) {
    N2370 *node;
    N2370 *next;

    if (arg1 == 0) {
        return;
    }
    node = *(N2370 **)((u8 *)arg0 + 0x24);
    arg0 = 0;
    if (node == 0) {
        return;
    }
    while (node != 0) {
        if (node->key == arg1) {
            break;
        }
        arg0 = node;
        node = node->next;
    }
    if (node == 0) {
        for (; (rg_spin_halt(0x001C23B4), 1);) {
        }
    } else {
        arg0->x8 = node->x8;
        next = node->next;
        arg0->next = next;
        if (next != 0) {
            next->prev = arg0;
        }
        node->prev = 0;
        node->next = 0;
        node->key = 0;
        node->x8 = 0;
        node->x4 = 0;
    }
}
