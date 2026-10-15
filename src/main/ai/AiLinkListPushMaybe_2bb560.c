#include "types.h"
typedef struct S002bb560 {
    u8 pad00[0x14A];
    s16 arr[0x10];            /* +0x14A */
    u8 count;                 /* +0x16A */
} S002bb560;

void AiLinkListPushMaybe_2bb560(S002bb560 *s, s16 v)
{
    u8 n;

    n = s->count;
    if (n < 0x10) {
        s->arr[n] = v;
        s->count = s->count + 1;
    }
}
