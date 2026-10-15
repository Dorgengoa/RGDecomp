#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_00407340 Obj_FUN_00407340;

extern void DataTableRowReset_407b30(Obj_FUN_00407340 *);

Obj_FUN_00407340 *DataTableRowCtor_407340(Obj_FUN_00407340 *o)
{
    DataTableRowReset_407b30(o);
    return o;
}
