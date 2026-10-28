/* rgp:protos */
#define RGP_SELF_insect_InsectLiveTalkRecordClear_523ab0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00523AB0 -- 40 bytes.  Clear eleven words. */

void insect_InsectLiveTalkRecordClear_523ab0(s32 *a)
{
    s32 i;

    for (i = 0; i < 0xB; i++) {
        a[i] = 0;
    }
}
