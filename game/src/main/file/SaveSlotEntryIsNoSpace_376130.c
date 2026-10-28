/* rgp:protos */
#define RGP_SELF_SaveSlotEntryIsNoSpace_376130 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S00376130 {
    s8 f0;                    /* +0x0 */
    s8 f1;                    /* +0x1 */
} S00376130;

s32 SaveSlotEntryIsNoSpace_376130(S00376130 *p)
{
    if (p->f0 == 0) {
        if (p->f1 == 3) {
            return 1;
        }
    }
    return 0;
}
