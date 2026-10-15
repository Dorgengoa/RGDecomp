#include "types.h"
/* insect 0x004EC450 -- the f_setkind shape; 0x41200000 is 10.0f, stored with
 * `lui` + `sw` because its low half is zero. */
typedef struct InsectSlot {
    s32 kind; s32 arg; s32 f08; s32 f0C; s32 f10; f32 f14;
} InsectSlot;
extern void insect_InsectSeqCmdInit_4ec490(InsectSlot *s);
void insect_InsectSeqCmdMoveInit_4ec450(InsectSlot *s)
{
    insect_InsectSeqCmdInit_4ec490(s);
    s->f0C = 0;
    s->kind = 0x2;
    s->arg = 0;
    s->f10 = 0;
    s->f14 = 10.0f;
}
