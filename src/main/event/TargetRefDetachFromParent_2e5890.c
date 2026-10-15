#include "types.h"

/* Not the Var family -- a "tag from a helper call" dispatch that mutates
   an Item pointed at by p0->m4.  jtbl_004617F0 is 11 entries (0-10);
   three tags (0,1,6) are empty/no-op (their table slots point straight
   at the shared exit label, no code needed); two PAIRS of tags
   (2,3 and 4,5) share COMPUTED-vs-DIRECT variants of the same
   "clear field4 if flag28 set" body; two MORE pairs (7,8 and 9,10)
   duplicate a "clear m34/m38" body as two separate text copies (the
   established non-adjacent-cluster duplication idiom) -- write it as
   FOUR separate case clusters even though 4-vs-5 and 7-8-vs-9-10 are
   textually identical, to get the duplicate code layout right. */

typedef struct Item {
    u8 pad000[0x4];
    s32 field4;
    u8 pad008[0x28 - 0x8];
    s8 flag28;
    u8 pad029[0x34 - 0x29];
    s32 m34;
    s32 m38;
} Item;

typedef struct Obj {
    u8 pad000[0x4];
    Item *m4;
} Obj;

extern Item *ModelGetRootFrame_1511a0(Item *);
extern s32 TargetRefGetKind_2e7130(Obj *);

void TargetRefDetachFromParent_2e5890(Obj *p0)
{
    s32 tag;
    Item *it;

    if (p0->m4 == 0) {
        return;
    }
    tag = TargetRefGetKind_2e7130(p0);
    switch (tag) {
    case 0:
    case 1:
        break;
    case 2:
    case 3:
        it = ModelGetRootFrame_1511a0(p0->m4);
        if (it->flag28 != 0) {
            it->field4 = 0;
        }
        break;
    case 4:
        it = p0->m4;
        if (it->flag28 != 0) {
            it->field4 = 0;
        }
        break;
    case 5:
        it = p0->m4;
        if (it->flag28 != 0) {
            it->field4 = 0;
        }
        break;
    case 6:
        break;
    case 7:
    case 8:
        it = p0->m4;
        it->m34 = 0;
        it->m38 = 0;
        break;
    case 9:
    case 10:
        it = p0->m4;
        it->m34 = 0;
        it->m38 = 0;
        break;
    }
}
