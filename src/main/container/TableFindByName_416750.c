#include "types.h"

/* Member of the 5-member clone group headed by TableFindByName_4159e0; the shape and
   every lever are documented there.  The members differ in ONE
   token, the entry stride (0x10 / 0xC / 0x34 / 0x8 / 0x8).

   Linear search of a name table.  The flag is a `u8` compared `== 0`: that is
   what emits `daddiu $16, $0, 0x1` and reads it back through
   `andi $2, $16, 0xFF`.  A `bool` under `if (!flag)` branches on the register
   directly and loses BOTH andi words; `bool` under `if (flag == false)` is the
   SAME OBJECT as this.  The first character is compared inline and only a hit
   pays for the call.

   Two shape rules carry it: `differ` is cleared by a nested `if`, not assigned
   the comparison's value -- `differ = call != 0` folds to one `sltu` and frees
   the callee-saved register retail spends -- and the counter is advanced in
   the loop HEADER, before the cursor, per session 24's comma-operator rule. */

typedef struct Entry {
    u8    pad000[0x4];
    char *m4;
} Entry;

typedef struct Pool {
    u8     pad000[0x7C];
    s16    m7C;
    u8     pad07E[0xE];
    Entry *m8C;
} Pool;

s32 StrNotEqual_1f5300(const char *a, const char *b);

Entry *TableFindByName_416750(Pool *p, const char *name)
{
    Entry *e;
    s32    i;
    u8     differ;
    char  *en;

    e = p->m8C;
    if (e == 0 || p->m7C <= 0) {
        return 0;
    }
    for (i = 0; i < p->m7C; i++, e = (Entry *)((u8 *)e + 0xC)) {
        en = e->m4;
        differ = 1;
        if (*en == *name) {
            if (StrNotEqual_1f5300(en + 1, name + 1) == 0) {
                differ = 0;
            }
        }
        if (differ == 0) {
            return e;
        }
    }
    return 0;
}
