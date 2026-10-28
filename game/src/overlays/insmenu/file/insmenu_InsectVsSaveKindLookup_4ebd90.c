/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsSaveKindLookup_4ebd90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004EBD90 (156 bytes) -- look the running scene's three-part key up in a
 * ten-byte table and hand back the two s16 the entry carries.
 *
 * ★ The table walks by `addiu $8, $8, 0xA`, so the entry is a 5 x s16 record and
 * the cursor is a POINTER, not an index.
 * ★ The first term's mismatch branches LIKELY to the latch with the cursor bump
 * duplicated into its delay slot while the other two branch to a shared bump --
 * one `&&` chain, not three `if`s.
 * ★ The scene key members are `lw` and the table's are `lh`, so the two sides of
 * each compare are different widths and only the table is s16. */

typedef struct Key Key;
struct Key {
    s32 field00;
    s32 field04;
    s32 field08;
};

typedef struct Ctx Ctx;
struct Ctx {
    u8  pad0000[0x1188];
    Key *field1188;
};

typedef struct Handle Handle;
struct Handle {
    u8  pad00[0x24];
    Ctx *field24;
};

typedef struct Entry Entry;
struct Entry {
    s16 field0;
    s16 field2;
    s16 field4;
    s16 field6;
    s16 field8;
};

extern Entry insmenu_D_004F9F20[];

/*rgp*/

void insmenu_InsectVsSaveKindLookup_4ebd90(s16 *out, s16 *out2)
{
    const Entry *e;
    Key *key;
    s32 k0;
    s32 k1;
    s32 k2;

    key = ((Handle *)GetGameData_1fede0())->field24->field1188;
    k0 = key->field00;
    k1 = key->field04;
    k2 = key->field08;
    for (e = insmenu_D_004F9F20; e->field0 != -1; e++) {
        if (e->field0 == k0 && e->field2 == k1 && e->field4 == k2) {
            *out = e->field6;
            *out2 = e->field8;
            return;
        }
    }
    *out = 0;
}
