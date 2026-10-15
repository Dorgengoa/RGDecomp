#include "types.h"
/* insect 0x0051C0F0 -- 72 bytes, 18 instructions.  0x5A-byte entries. */

typedef struct Ent {
    u8 pad00[0x50];
    s8 f50;                         /* +0x50 */
    u8 pad51[0x54 - 0x51];
    s8 f54;                         /* +0x54 */
    u8 pad55[0x5A - 0x55];
} Ent;

typedef struct Obj {
    u8   pad00[0x04];
    Ent *f04;                       /* +0x04 */
    u8   pad08[0x18 - 0x08];
    s16  f18;                       /* +0x18 */
} Obj;

s32 insect_InsectBattleLogHasUnread_51c0f0(Obj *o)
{
    Ent *p;
    s32  i;
    s16  n;

    p = o->f04;
    n = o->f18;
    for (i = 0; i < n; i++, p++) {
        if (p->f54 == 0) {
            break;
        }
        if (p->f50 != 0) {
            return 1;
        }
    }
    return 0;
}
