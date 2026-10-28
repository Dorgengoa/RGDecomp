/* rgp:protos */
#define RGP_SELF_EventCastCtor_261530 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Constructor: clear three words, run XformRecCtorMaybe_261680 over the eight 0x60-byte
   sub-objects at +0x10, then two more initialisers, and hand the receiver
   back. The loop is a POINTER walk compared against the end of the array --
   retail compares with sltu against self+0x310, an unsigned pointer compare,
   not an index. */

typedef struct Sub00261530 {
    u8 bytes[0x60];
} Sub00261530;

typedef struct Obj00261530 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    u8 padC[0x4];
    Sub00261530 sub[8];    /* +0x10 .. +0x310 */
} Obj00261530;

/*rgp*/
/*rgp*/
/*rgp*/

Obj00261530 *EventCastCtor_261530(Obj00261530 *self)
{
    Sub00261530 *s;

    self->unk0 = 0;
    self->unk4 = 0;
    self->unk8 = 0;
    s = self->sub;
    do {
        XformRecCtorMaybe_261680(s);
        s++;
    } while (s < &self->sub[8]);
    XformRecArrayResetMaybe_2615a0(self->sub);
    EventCastInit_24d310(self);
    return self;
}
