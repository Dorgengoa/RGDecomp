#include "types.h"
/* insect 0x004EC060 -- the f_setkind shape clearing two more words. */
typedef struct InsectSlot {
    s32 kind; s32 arg; s32 f08; s32 f0C; s32 f10;
} InsectSlot;
extern void insect_InsectSeqCmdInit_4ec490(InsectSlot *s);
void insect_InsectSeqCmdRotateInit_4ec060(InsectSlot *s)
{
    insect_InsectSeqCmdInit_4ec490(s);
    s->kind = 0x10;
    s->arg = 0;
    s->f0C = 0;
    s->f10 = 0;
}
