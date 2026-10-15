#include "types.h"
/* insect 0x004F1490 -- 76 bytes.  func_1343B8 is the sprintf-alike, so the
 * 0x80-byte frame local is a text buffer and D_00524BC8 is its format. */

extern void func_1343B8(void *dst, const char *fmt, ...);
extern void insect_InsectBattleDrawTextRec_4f1410(s32 a, void *r, void *b);
extern const char D_00524BC8[];

void insect_InsectBattleDrawNumberRec_4f1490(s32 a, void *r)
{
    char buf[0x80];

    func_1343B8(buf, D_00524BC8);
    insect_InsectBattleDrawTextRec_4f1410(a, r, buf);
}
