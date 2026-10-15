#include "types.h"

typedef struct {
    u32 fieldA : 6;
    u32 fieldB : 3;
    u32 fieldC : 4;
    u32 fieldD : 8;
    u32 fieldE : 8;
    u32 fieldF : 3;
} S00409e30;

void RevelationBoardCellReset_409e30(S00409e30 *arg0) {
    arg0->fieldA = 0x3F;
    arg0->fieldB = 7;
    arg0->fieldC = 0;
    arg0->fieldD = 0;
    arg0->fieldE = 0;
}
