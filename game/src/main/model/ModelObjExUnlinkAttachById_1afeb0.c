/* rgp:protos */
#define RGP_SELF_ModelObjExUnlinkAttachById_1afeb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Node001afeb0 {
    struct Node001afeb0 *next;
    struct Node001afeb0 *prev;
    u8 pad8[0xC];
    s32 id;
} Node001afeb0;

/*rgp*/

void ModelObjExUnlinkAttachById_1afeb0(u8 *arg0, s32 arg1) {
    Node001afeb0 *n;
    Node001afeb0 *head;
    Node001afeb0 *prev;
    Node001afeb0 *next;

    n = *(Node001afeb0 **)(arg0 + 0x51C);
    while (n != NULL) {
        if (arg1 == n->id) {
            prev = n->prev;
            if (prev != NULL) {
                next = n->next;
                prev->next = next;
                if (next != NULL) {
                    next->prev = prev;
                }
                head = n->prev;
                while (head->prev != NULL) {
                    head = head->prev;
                }
            } else {
                if (n->next != NULL) {
                    n->next->prev = NULL;
                }
                head = n->next;
            }
            n->prev = NULL;
            n->next = NULL;
            *(Node001afeb0 **)(arg0 + 0x51C) = head;
        }
        n = n->next;
    }
    MotionEventListRemoveById_1b4a10(arg0 + 0x568, (int)arg1);
}
