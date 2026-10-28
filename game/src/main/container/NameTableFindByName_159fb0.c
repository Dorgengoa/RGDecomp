/* rgp:protos */
#define RGP_SELF_NameTableFindByName_159fb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* s54m: rewritten -- the m2c draft did not compile (int -> short * return). */
typedef struct Entry {
    s16 id;
    s16 pad2;
    s32 pad4;
    s8 name[1];
} Entry;

typedef struct Node {
    Entry *e;
    struct Node *next;
} Node;

s8 *strcpy(s8 *, s8 *);                             /* extern */
s8 *strcat(s8 *, s8 *);                             /* extern */
s32 strcmp(s8 *, s8 *);                             /* extern */

Entry *NameTableFindByName_159fb0(u8 *arg0, s8 *arg1, s32 arg2) {
    s8 buf[128] __attribute__((aligned(16)));
    s8 *name;
    s8 *p;
    s32 h;
    Node *n;

    name = arg1;
    if (arg1 == 0) {
        return 0;
    }
    if (*(s8 *)(arg0 + 0x1E4) != 0) {
        strcpy(buf, arg1);
        strcat(buf, (s8 *)(arg0 + 0x1E4));
        name = buf;
    }
    p = name;
    h = 0;
    for (; *p != 0; p++) {
        h = ((((h & 0xFF) << 8) + *p) % 101) & 0xFF;
    }
    n = ((Node **)(arg0 + 0x30))[h & 0xFF];
    while (n != 0) {
        if (strcmp(name, n->e->name) == 0) {
            if (arg2 < 0 || n->e->id == arg2) {
                return n->e;
            }
        }
        n = n->next;
    }
    return 0;
}
