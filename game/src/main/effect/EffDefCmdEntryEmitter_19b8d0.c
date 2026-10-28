/* rgp:protos */
#define RGP_SELF_EffDefCmdEntryEmitter_19b8d0 1
#define RGP_SELF_lookup0019b8d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vm_slot.h"

/* s41 agent10: MATCH (inlined lookup helper). */

typedef struct StrNode0019b8d0 {
    struct StrNode0019b8d0 *next; /* 0x0 */
    char *str;                    /* 0x4 */
} StrNode0019b8d0;

typedef struct SubTable0019b8d0 {
    u8 pad0[0x84];
    StrNode0019b8d0 *head; /* 0x84 */
} SubTable0019b8d0;

typedef struct Container0019b8d0 {
    u8 pad0[0x20];
    s32 unk20;
    SubTable0019b8d0 *unk24;
    u8 pad28[0x30 - 0x28];
    void *unk30;
} Container0019b8d0;

/*rgp*/
/*rgp*/

static inline char **lookup0019b8d0(SubTable0019b8d0 *tbl, char *str)
{
    StrNode0019b8d0 *node;
    char **found;

    if (str == 0) {
        return NULL;
    }
    for (node = tbl->head; node != NULL; node = node->next) {
        found = &node->str;
        if (found != NULL && *found != NULL && strcmp(str, *found) == 0) {
            return found;
        }
    }
    return NULL;
}

s32 EffDefCmdEntryEmitter_19b8d0(Slot *slots, s32 count, Container0019b8d0 **arg2)
{
    Container0019b8d0 *c;
    Slot *s;
    s32 i;
    char *str;
    char **found;

    c = *arg2;
    s = slots;
    if (c->unk30 == 0) {
        return 0;
    }
    for (i = 0; i < count; i++) {
        str = (char *) SlotGetInt_15f720(s++);
        if (str != 0) {
            found = lookup0019b8d0(c->unk24, str);
            if (found != NULL) {
                PtrListAppend_19b590(c->unk30, c->unk20, found);
            }
        }
    }
    return 1;
}
