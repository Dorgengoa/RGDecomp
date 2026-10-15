#include "types.h"

typedef struct S004324A0 {
    u8 f0_b0 : 1;             /* +0x0 */
    u8 f0_hi : 7;
    u8 f1;                    /* +0x1 */
    u8 f2;                    /* +0x2 */
    s8 f3;                    /* +0x3 */
} S004324A0;

void RecordStateSaveSlotInitMaybe_4324a0(S004324A0 *p)
{
    p->f0_b0 = 0;
    p->f1 = 0;
    p->f2 = 0;
    p->f3 = -1;
}
