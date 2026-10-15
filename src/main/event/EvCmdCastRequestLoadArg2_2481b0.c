#include "types.h"

/* Head of a 2-member BYTE-IDENTICAL group (80 B each): EvCmdCastRequestLoadArg2_2481b0 /
   EvCmdCastRequestLoadArg2_248280.  The destination sub-object is computed from the event
   context BEFORE either call, and the cursor is a POST-INCREMENT on an 8-byte
   element type -- the same R8 rule as src/s25a/EvCmdMesWinSetStyle_241fa0.c.  The first
   ScriptGetCodeAddr_249050 result is dropped. */

typedef struct R8 {
    u8 b[8];
} R8;

struct Obj0;

struct Obj0 {
    u8  pad000[0x4];
    u8 *m4;
};

extern struct Obj0 *gEventContext;
extern void *ScriptGetCodeAddr_249050(void *vm);
extern void  EventCastRequestLoad_24bc30(void *dst, void *src);

void EvCmdCastRequestLoadArg2_2481b0(R8 *p)
{
    u8 *dst;

    dst = gEventContext->m4 + 0x60;
    ScriptGetCodeAddr_249050(p++);
    EventCastRequestLoad_24bc30(dst, ScriptGetCodeAddr_249050(p));
}
