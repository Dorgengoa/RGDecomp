/* ObjTypeMonographPreUpdate_372060 -- BYTE-IDENTICAL to merged EvTargetPointObjPreUpdate_2f9280 (148 B); source cloned
   by build/zz/s23_clonesrc.py, symbol renamed, nothing else
   changed.  Verified by sha1 over the retail bytes. */
#include "types.h"

/* MAIN ObjTypeMonographPreUpdate_372060 -- copies the 0x10..0x57 block up to 0x58..0x9F.
   The first 36 bytes go as three 12-byte float sub-struct assignments
   (batched lwc1 x3 / swc1 x3); the remaining 36 bytes are a single
   struct assignment, which mwcc emits as its word block-copy loop. */

typedef struct V3 { f32 x, y, z; } V3;
typedef struct B36 { u32 w[9]; } B36;

extern void EvObjPreUpdateBase_2f9930(u8 *);

void ObjTypeMonographPreUpdate_372060(u8 *p)
{
    EvObjPreUpdateBase_2f9930(p);
    *(V3 *)(p + 0x58) = *(V3 *)(p + 0x10);
    *(V3 *)(p + 0x64) = *(V3 *)(p + 0x1C);
    *(V3 *)(p + 0x70) = *(V3 *)(p + 0x28);
    *(B36 *)(p + 0x7C) = *(B36 *)(p + 0x34);
}
