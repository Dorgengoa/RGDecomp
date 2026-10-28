/* rgp:protos */
#define RGP_SELF_normal_ThinkMenuSetPrompt_520800 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00520800 -- copy-or-clear of the 0x80-byte normal_D_00528090 buffer.
 * Both arms reload the buffer address, so it is written at each use. */

extern u8 normal_D_00528090;

extern void strcpy(const u8 *d, const u8 *s);
extern void memset(const u8 *p, s32 v, s32 n);

s32 normal_ThinkMenuSetPrompt_520800(const u8 *s)
{
    if (s != NULL) {
        strcpy(&normal_D_00528090, s);
    } else {
        memset(&normal_D_00528090, 0, 0x80);
    }
    return 1;
}
