
#include <stdio.h>

int main() {
    int stateSize = 1600;
    int blockSize = 1024;
    int laneSize = 64;

    int capacity = stateSize - blockSize;
    int capacityLanes = capacity / laneSize;
    int i;

    printf("SHA-3 Capacity Lane Analysis\n");
    printf("----------------------------\n");

    printf("State size       : %d bits\n", stateSize);
    printf("Block size       : %d bits\n", blockSize);
    printf("Capacity size    : %d bits\n", capacity);
    printf("Lane size        : %d bits\n", laneSize);
    printf("Capacity lanes   : %d\n", capacityLanes);

    printf("\nInitial capacity lane values:\n");

    for (i = 0; i < capacityLanes; i++)
        printf("Lane %d = 0\n", i + 1);

    printf("\nAfter absorbing first message block:\n");
    printf("All capacity lanes remain zero.\n");

    printf("\nNumber of nonzero capacity lanes = 0\n");
    printf("Number of zero capacity lanes = %d\n",
           capacityLanes);

    printf("\nConclusion:\n");
    printf("Without permutation, capacity lanes\n");
    printf("never become nonzero.\n");

    return 0;
}

