/* rgp:protos */
#define RGP_SELF_insect_InsectBattleDrawNumberRec_4f1490 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F1490 -- 76 bytes.  func_1343B8 is the sprintf-alike, so the
 * 0x80-byte frame local is a text buffer and insect_D_00524BC8 is its format. */

extern void Sprintf_1343b8(void *dst, const char *fmt, ...);
/*rgp*/
extern char insect_D_00524BC8[];

void insect_InsectBattleDrawNumberRec_4f1490(s32 a, void *r)
{
    char buf[0x80] __attribute__((aligned(16)));

    Sprintf_1343b8(buf, insect_D_00524BC8);
    insect_InsectBattleDrawTextRec_4f1410(a, r, buf);
}
