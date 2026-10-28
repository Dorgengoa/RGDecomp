/* rgp:protos */
#define RGP_SELF_ModelObjExRemoveAttachById_1b0b10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct N {
    struct N *next;
    struct N *prev;
    u8 pad8[0xc];
    s32 id;
} N;

typedef struct {
    u8 pad[0x51C];
    N *head;
} O;

/*rgp*/
/*rgp*/
/*rgp*/

void ModelObjExRemoveAttachById_1b0b10(O * arg0, s32 arg1)
{
    N *p;
    N *q;
    N *n;

    for (p = arg0->head; p != NULL; p = p->next) {
        if (arg1 == p->id) {
            if (p->prev != NULL) {
                q = p->prev;
                n = p->next;
                q->next = n;
                if (n != NULL) {
                    n->prev = q;
                }
                q = p->prev;
                while (q->prev != NULL) {
                    q = q->prev;
                }
            } else {
                if (p->next != NULL) {
                    p->next->prev = NULL;
                }
                q = p->next;
            }
            p->prev = NULL;
            p->next = NULL;
            arg0->head = q;
        }
    }
    MotionEventListRemoveById_1b4a10((u8 *)arg0 + 0x568, arg1);
    ModelObjExEffectsStop_1b0880(arg0, arg1, 0);
    ModelObjRemoveAttachById_1ae2b0(arg0, arg1);
}
