#include "types.h"

typedef struct S_003a5f40 {
    u8 pad0[2];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 6;
    u8 pad3[1];
    s32 f4;
} S_003a5f40;

extern s32 StatusEntryIsRunning_3a6190(void);
extern s32 StatusEntryHasFlag2Maybe_3a6130(S_003a5f40 *);

s32 StatusEntryExpire_3a5f40(S_003a5f40 *self, s32 b)
{
    if (b != 0) goto ok;
    if (StatusEntryIsRunning_3a6190() == 0) goto zero;
    if (StatusEntryHasFlag2Maybe_3a6130(self) == 0) goto ok;
zero:
    return 0;
ok:
    self->b1 = 1;
    self->f4 = 0;
    return 1;
}
