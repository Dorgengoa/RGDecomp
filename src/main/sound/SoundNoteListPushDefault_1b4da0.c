#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 SoundNoteListPush_1b4cd0(s32, s32, s32, s32, f32, f32);

s32 SoundNoteListPushDefault_1b4da0(s32 a4, s32 a5, s32 a6, s32 a7)
{
    return SoundNoteListPush_1b4cd0(a4, a5, a6, a7, -1.0f, 0.0f);
}
