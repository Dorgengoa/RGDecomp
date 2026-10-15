#include "types.h"

/* Drains TextReaderParseStatement_15f430 until it reports failure. The object is held in $16
   because the callee takes it in $4 and a second argument goes in $5, so the
   argument register cannot carry it across the loop. */

extern s32 TextReaderParseStatement_15f430(void *self, s32 mode);

void TextReaderParseAll_15f3f0(void *self)
{
    while (TextReaderParseStatement_15f430(self, 1) >= 0) {
        ;
    }
}
