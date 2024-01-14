#include "../src/Dictionary.h"

int main() {
    Dictionary* dict = Dictionary_New(1000);
    Dictionary_Add(dict, 1, "hello");

    int value = 5;
    Dictionary_Add(dict, 2, &value);

    void* outV1;
    bool succ = Dictionary_TryGet(dict, 1, &outV1);
    if (succ) {
        printf("Value1: %s\n", (char*)outV1);
    }

    void *outV2;
    succ = Dictionary_TryGet(dict, 2, &outV2);
    if (succ) {
        printf("Value2: %d\n", *(int*)(outV2));
    }

    succ = Dictionary_Remove(dict, 1);
    if (succ) {
        printf("Remove success\n");
    }

    succ = Dictionary_TryGet(dict, 1, &outV1);
    if (succ) {
        printf("Value1: %s\n", (char*)outV1);
    } else {
        printf("Value1 not found\n");
    }

    return 0;
}