#include "types.h"
#include "vm_slot.h"

/* Clone of EffDefCmdEntryEmitter_19b8d0 (same normalized opcode stream) -- see that file's
   header, including the residue note (this one hits the identical 24/65
   register-coloring residue). Field offsets are shifted (unk2C instead of
   unk30, sub-table head at 0x8C instead of 0x84) and it dispatches to
   PtrListAppend_1a9800 instead of PtrListAppend_19b590. */

typedef struct StrNode0019bd50 {
    struct StrNode0019bd50 *next; /* 0x0 */
    char *str;                    /* 0x4 */
} StrNode0019bd50;

typedef struct SubTable0019bd50 {
    u8 pad0[0x8C];
    StrNode0019bd50 *head; /* 0x8C */
} SubTable0019bd50;

typedef struct Container0019bd50 {
    u8 pad0[0x20];
    s32 unk20;
    SubTable0019bd50 *unk24;
    u8 pad28[0x2C - 0x28];
    void *unk2C;
} Container0019bd50;

extern s32 strcmp(const char *, const char *);
extern s32 SlotGetInt_15f720(Slot *v);
extern void PtrListAppend_1a9800(void *a, s32 unused, void *c);

static inline char **find0019bd50(SubTable0019bd50 *tbl, char *str)
{
    StrNode0019bd50 *node;
    char **found;

    if (str == NULL) {
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

s32 EffDefCmdEntryObject_19bd50(Slot *slots, s32 count, Container0019bd50 **arg2)
{
    Container0019bd50 *c;
    s32 i;
    char *str;
    char **found;

    c = *arg2;
    if (c->unk2C == 0) {
        return 0;
    }
    for (i = 0; i < count; i++) {
        str = (char *) SlotGetInt_15f720(slots++);
        if (str != 0) {
            found = find0019bd50(c->unk24, str);
            if (found != NULL) {
                PtrListAppend_1a9800(c->unk2C, c->unk20, found);
            }
        }
    }
    return 1;
}
