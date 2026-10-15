#include "types.h"

/* MW C++ destructor with the delete flag:
       if (this) { <body>; if (flag > 0) operator delete(this); }
       return this;
   The (s16) narrowing of the flag is retail's dsll32/dsra32 pair. */

extern void *ScreenMarkerMgrBaseDtor_31c0a0(void *, s16);
extern void OperatorDelete_100840(void *);

void *ScreenMarkerMgrDtor_31bd70(void *o, s16 flag)
{
    if (o != 0) {
        ScreenMarkerMgrBaseDtor_31c0a0(o, -1);
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
