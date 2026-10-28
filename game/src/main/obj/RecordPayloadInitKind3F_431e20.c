/* rgp:protos */
#define RGP_SELF_RecordPayloadInitKind3F_431e20 1
#define RGP_SELF_setf 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct BF431 { u8 a : 1; u8 b : 1; u8 c : 1; u8 r : 5; } BF431;
typedef struct S431 { s32 x0; BF431 bf; u8 p5[7]; s32 xC; u8 n[20][0xE0]; } S431;
/*rgp*/
/*rgp*/
static inline void setf(BF431 *f, s32 v) { f->a = v; f->b = v; f->c = v; }
void RecordPayloadInitKind3F_431e20(S431 *s)
{
    u8 *node;
    s32 i;
    s->x0 = 0x278;
    setf(&s->bf, 0);
    RecordStateSaveSlotInitMaybe_4324a0(s->p5);
    s->xC = 0;
    node = s->n[0];
    i = 0;
    do {
        InsectTeamInit_4324d0(node);
        i++;
        node += 0xE0;
    } while (i < 0x14);
}
