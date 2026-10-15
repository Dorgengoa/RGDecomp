/* main s27m: CLOSED by the s26 post-incremented-PARAMETER lever -- `E8 *arg0` +
   `ScriptGetInt_2490f0((s32) arg0++)`; `arg0++` as its own statement and `++arg0` at
   the second call are both still 2 bad. */
/* main s22: ScriptGetInt_2490f0 really takes ONE argument (its merged definition is
   `s32 ScriptGetInt_2490f0(Slot *v)`), and retail passes the UN-advanced arg0 -- the
   `arg0 += 8` belongs AFTER the call, which is why retail can sink it into the
   call's delay slot.  Corrected; the 2-word residue is unchanged (the +8 is
   still rematerialised at the use instead of living in $16). */
#include "types.h"

extern s32 ScriptGetCodeAddr_249050(s32);
extern void ScriptGetInt_2490f0(s32);
extern void EventCueListReset_249180(void *);
extern void *memcpy(void *, const void *, u32);
extern void *gEventContext;

/* 2 bad, right length: retail sinks `arg0 += 8` (in place, s0 += 8)
   into the delay slot of the ScriptGetInt_2490f0() call, then MOVES s0 into
   a0 for the ScriptGetCodeAddr_249050 call; ours computes `a0 = s0 + 8` fresh at
   the use site instead and leaves the call's delay slot empty.
   Statement order (+=8 before/after the call) and an inline
   `arg0 + 8` expression are both INERT -- same object either way. */
typedef struct { u8 b[8]; } E8;
s32 EvCmdCueSeqBegin_2483e0(E8 *arg0, s32 arg1) {
    s32 temp_2;
    void *temp_16;

    if (arg1 != 2) {
        return 0;
    }
    ScriptGetInt_2490f0((s32) arg0++);
    temp_2 = ScriptGetCodeAddr_249050((s32) arg0);
    temp_16 = *(void **)((u8 *)gEventContext + 4);
    *(s32 *)((u8 *)temp_16 + 0x470) = 0;
    if (temp_2 != 0) {
        memcpy((u8 *)temp_16 + 0x474, (void *)temp_2, 0x10);
        *(u8 *)((u8 *)temp_16 + 0x483) = 0;
    }
    EventCueListReset_249180(temp_16);
    return 1;
}
