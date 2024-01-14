# C Dictionary
- Add / TryGet / Remove
- Key: long, Value: void*
- One .h File
- Freeze Capacity

# Quick Start
``` C
void main() {

    // New
    Dictionary* dict = Dictionary_New(1000);

    // Add
    Dictionary_Add(dict, 1, "hello");

    int *value1 = malloc(sizeof(int));
    *value1 = 123;
    Dictionary_Add(dict, 2, value1);

    // Get
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

    // Remove
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

    // Free
    free(value1);
    Dictionary_Free(dict);
    
}

```