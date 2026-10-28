/* rgp:protos */
#define RGP_SELF_RevelationBoardCellReset_409e30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    __extension__ unsigned int fieldA : 6;
    unsigned int fieldB : 3;
    unsigned int fieldC : 4;
    unsigned int fieldD : 8;
    unsigned int fieldE : 8;
    unsigned int fieldF : 3;
} __attribute__((aligned(4))) S00409e30;

void RevelationBoardCellReset_409e30(S00409e30 *arg0) {
    arg0->fieldA = 0x3F;
    arg0->fieldB = 7;
    arg0->fieldC = 0;
    arg0->fieldD = 0;
    arg0->fieldE = 0;
}
