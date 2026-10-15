#include "types.h"

extern void *StrVectorDtor_1a21a0(void *, s16);
extern void OperatorDelete_100840(void *);

void *EffHdlTableBaseDtor_1a16e0(void *o, s16 flag)
{
    if (o != 0) {
        if (o != 0) {
            StrVectorDtor_1a21a0(o, 0);
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
