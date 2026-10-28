/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuSetMemberFace_501d40 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00501D40 -- one of a family of three near-identical "resolve
 * widget + colour-table lookup" units (see also 004F6F80, 005058D0): fetch a
 * widget record, then either use a caller-supplied entity (b != -1) or skip
 * straight to the table search with a NULL state pointer when b == -1 (which
 * retail dereferences unconditionally at +0x2C -- reproduced verbatim, not a
 * defensive NULL check on our part). */

typedef struct SA {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
    s16 f08;
    s16 f0A;
    s16 f0C;
    s16 f0E;
    u8  pad10[0x10];
} SA;

typedef struct Root {
    u8    pad000[0x18];
    void *f018;
} Root;

typedef struct St {
    u8  pad00[0x2C];
    s16 f2C;
} St;

extern void *D_0048449C;              /* gp - 0xCD4 */
extern s16 normal_D_00525120[0x21];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_BtlChgMenuSetMemberFace_501d40(s32 a, s32 b)
{
    SA   *r;
    Root *root;
    void *obj;
    St   *st;
    s16   tbl[0x21] __attribute__((aligned(16)));
    s16  *src;
    s16  *dst;
    s32   i;
    s16   target;

    if (D_0048449C == 0) {
        return 0;
    }
    r = ((SA *)UiGetWidgetSprite_28fe10(D_0048449C, a, 0));
    if (r == 0) {
        return 0;
    }
    st = 0;
    if (b != -1) {
        root = ((Root *)GetGameData_1fede0());
        if (root == 0) {
            return 1;
        }
        obj = PartyGetMemberChara_3c2420(root->f018, b);
        if (obj == 0) {
            return 2;
        }
        st = ((St *)CharaGetIconRecMaybe_3ae3e0(obj));
        if (st == 0) {
            return 3;
        }
    }
    src = (s16 *)normal_D_00525120;
    dst = tbl;
    i = 0x21;
    do {
        *dst++ = *src++;
        i--;
    } while (i > 0);
    target = st->f2C;
    r->f0A = 0;
    r->f08 = 0;
    for (i = 0; i < 10; i++) {
        if (tbl[i * 3] == target) {
            r->f08 = tbl[i * 3 + 1];
            r->f0A = tbl[i * 3 + 2];
        }
    }
    r->f0C = 0x4C;
    r->f04 = 0x4C;
    r->f0E = 0x12;
    r->f06 = 0x12;
    return 0;
}
