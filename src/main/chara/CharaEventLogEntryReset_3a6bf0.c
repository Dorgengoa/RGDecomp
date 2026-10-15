#include "types.h"

typedef struct S003A6BF0 {
    s16 f0;                   /* +0x0 */
    s16 f2;                   /* +0x2 */
    s16 f4;                   /* +0x4 */
    u8 f6_b0 : 1;             /* +0x6 */
    u8 f6_hi : 7;
} S003A6BF0;

void CharaEventLogEntryReset_3a6bf0(S003A6BF0 *p)
{
    p->f0 = -1;
    p->f2 = -1;
    p->f4 = 0;
    p->f6_b0 = 0;
}
