/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsStateRowFind_4ec020 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004EC020 (276 bytes) -- copy the running scene's six key words out
 * through six pointer parameters, then find the table row for the first three.
 *
 * ★ `h->field24->field1188` is re-derived at all SIX stores, so the source
 * writes the whole chain each time rather than naming a local for it -- one
 * local for the handle only.
 * ★ The three compares reload through the OUT pointers (`lw $5, 0x0($21)`), so
 * the loop reads the parameters back rather than the values it just stored.
 * ★ Six pointer parameters plus nothing on the stack: the EABI passes eight
 * integer arguments in $4..$11. */

typedef struct Key Key;
struct Key {
    s32 field00;
    s32 field04;
    s32 field08;
    u8  pad0C[4];
    s32 field10;
    s32 field14;
    s32 field18;
};

typedef struct Ctx Ctx;
struct Ctx {
    u8   pad0000[0x1188];
    Key *field1188;
};

typedef struct Handle Handle;
struct Handle {
    u8   pad00[0x24];
    Ctx *field24;
};

typedef struct Row Row;
struct Row {
    s16 field00;
    s16 field02;
    s16 field04;
    u8  pad06[0xE];
};

extern Row insmenu_D_004F9A50[];

/*rgp*/

const Row *insmenu_InsectVsStateRowFind_4ec020(s32 *a, s32 *b, s32 *c, s32 *d, s32 *e, s32 *f)
{
    Handle *h;
    const Row *p;

    h = ((Handle *)GetGameData_1fede0());
    *a = h->field24->field1188->field00;
    *b = h->field24->field1188->field04;
    *c = h->field24->field1188->field08;
    *d = h->field24->field1188->field10;
    *e = h->field24->field1188->field14;
    *f = h->field24->field1188->field18;
    for (p = insmenu_D_004F9A50; p->field00 != -1; p++) {
        if (p->field00 == *a && p->field02 == *b && p->field04 == *c) {
            return p;
        }
    }
    return 0;
}
