#include "types.h"
/* normal 0x00519DD0 -- reads two s16 fields of the argument and posts the
 * 0x75A1 event; the object pointer is held in $16 across the two calls. */

typedef struct Box {
    u8  pad00[0x12];
    s16 f12;
    u8  pad14[0x2];
    s16 f16;
} Box;

extern void normal_TransSaveHighlightOption_519e70(s32 a);
extern void normal_TransSaveSlotListRefreshMaybe_518a80(s32 a);
extern void func_3777A0(void *p, s32 b, s32 c);

s32 normal_TransSaveSlotMoveCb_519dd0(Box *p)
{
    normal_TransSaveHighlightOption_519e70(p->f12);
    normal_TransSaveSlotListRefreshMaybe_518a80(p->f16);
    func_3777A0(p, 0x75A1, 1);
    return 1;
}
