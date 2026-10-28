/* rgp:protos */
#define RGP_SELF_SaveSlotEntryIsBadData_376090 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S00376090 {
    s8 f0;                    /* +0x0 */
    s8 f1;                    /* +0x1 */
} S00376090;

s32 SaveSlotEntryIsBadData_376090(S00376090 *p)
{
    if (p->f0 == 1) {
        if (p->f1 == 2) {
            return 1;
        }
    }
    return 0;
}
