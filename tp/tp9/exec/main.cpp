#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <BuzzerController.h>
#include "Partition.h"

int main() {
    BuzzerController::initBuzzer();
    Partition partition;
    // partition.partitionAuClair();
    partition.partitionPirates();
    return 0;
};
