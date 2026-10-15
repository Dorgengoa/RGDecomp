#include "types.h"

/* A constructor: zero three words and hand back `this`. Written in C rather
   than C++ because the return of the object pointer is explicit in the
   reference and there is no vtable store to place. */

typedef struct Triple {
    s32 a, b, c;
} Triple;

Triple *Vec4VectorCtor_2614f0(Triple *t)
{
    t->a = 0;
    t->b = 0;
    t->c = 0;
    return t;
}
