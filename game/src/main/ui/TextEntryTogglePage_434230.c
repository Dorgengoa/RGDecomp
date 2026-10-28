/* rgp:protos */
#define RGP_SELF_TextEntryTogglePage_434230 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj00434230 {
    u8 pad0[0xE0];
    s16 unkE0;
    s16 unkE2;
} Obj00434230;

/*rgp*/

void TextEntryTogglePage_434230(Obj00434230 *self)
{
    s16 temp_6;

    temp_6 = self->unkE0;
    if ((temp_6 == 1) || (temp_6 == 3)) return;
    if (self->unkE2 == 0) {
        self->unkE2 = 1;
    } else {
        self->unkE2 = 0;
    }
    TextEntrySetPageTexts_434160(self, self->unkE2);
}
