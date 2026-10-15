/* MATCH (s41m). Stale pre-match note follows -- PARKED after 3 round trips: 42/42 words, 7 bad (one control-flow region).
   Retail's `beql $3,$2(-1),.L...88` takes the likely branch ON EQUAL (i.e.
   polarity is "if (x == -1) goto shared; " with the increment folded into
   the taken delay slot); both `if (x==-1) y++;` and the inverted
   `if (x!=-1) {} else y++;` compiled to the IDENTICAL bnel/!=-1 form here --
   mwcc did not choose retail's polarity from source rephrasing alone. */
#include "types.h"

extern s32 SignalSema(s32);
extern s32 WaitSema(s32);
extern s32 (*D_0044AE10[])(void *);
extern s32 D_0048142C;
extern s32 D_00481434;
extern s32 D_00481440;
extern s32 D_00481444;
extern s32 D_00481448;
extern u8 D_0049D510[];

void SoundCmdWorkerThread_1b6c10(void)
{
    s32 (*fn)(void *);
    s32 done;

    done = 0;
    D_00481444 = 1;
    while (!done) {
        WaitSema(D_0048142C);
        D_00481448 = 0;
        if (D_00481440 > 0 && D_00481440 < 0x27) {
            fn = D_0044AE10[D_00481440];
            if (fn != NULL) {
                D_00481448 = fn(D_0049D510);
            }
        }
        switch (D_00481440) {
        case -1:
            done++;
        }
        SignalSema(D_00481434);
    }
    D_00481444 = 2;
}
