#include "types.h"
/* normal 0x00519E50 -- leaf tail call, the gp handle is inserted as the FIRST
 * argument so both incoming registers shift up one slot. */

extern void *D_00484714;          /* gp - 0xA5C */

extern void func_377690(void *a, void *b, void *c);

void normal_TransSaveProgressWindowShow_519e50(void *a, void *b)
{
    func_377690(D_00484714, a, b);
}
