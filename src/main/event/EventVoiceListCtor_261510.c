#include "types.h"

/* A byte-identical twin of Vec4VectorCtor_2614f0 twenty bytes further on -- two
   classes with the same three-word body, emitted separately because they are
   separate constructors, not one shared out of line. */

typedef struct Triple2 {
    s32 a, b, c;
} Triple2;

Triple2 *EventVoiceListCtor_261510(Triple2 *t)
{
    t->a = 0;
    t->b = 0;
    t->c = 0;
    return t;
}
