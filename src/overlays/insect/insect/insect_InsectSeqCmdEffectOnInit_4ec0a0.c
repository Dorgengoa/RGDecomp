#include "types.h"
/* insect 0x004EC0A0 -- the f_setkind shape clearing a halfword and two bytes. */
typedef struct InsectSlot {
    s32 kind; s32 arg; s32 f08; s16 f0C; u8 f0E; u8 f0F;
} InsectSlot;
extern void insect_InsectSeqCmdInit_4ec490(InsectSlot *s);
void insect_InsectSeqCmdEffectOnInit_4ec0a0(InsectSlot *s)
{
    insect_InsectSeqCmdInit_4ec490(s);
    s->kind = 0xF;
    s->arg = 0;
    s->f0C = 0;
    s->f0E = 0;
    s->f0F = 0;
}
