#include "types.h"

/* The base initialiser under TextReaderCtor_15f140: three zeroes and the receiver
   back. The store order is 0x4, 0x8, 0x0 -- not ascending -- so it is three
   member assignments in source order, not a clear. */

typedef struct Base0015f190 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Base0015f190;

Base0015f190 *TextReaderBaseCtor_15f190(Base0015f190 *b)
{
    b->unk4 = 0;
    b->unk8 = 0;
    b->unk0 = 0;
    return b;
}
