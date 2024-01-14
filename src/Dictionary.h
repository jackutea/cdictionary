#ifndef C_DICTIONARY_H__
#define C_DICTIONARY_H__

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DictionaryLogNA(x) printf("%s:%d %s", __FILE__, __LINE__, x)
#define DictionaryLog(x, ...)                                                                                                                                  \
    printf("%s:%d ", __FILE__, __LINE__);                                                                                                                      \
    printf(x, __VA_ARGS__)

typedef struct Dictionary Dictionary;
typedef struct DictionaryEntry DictionaryEntry;

struct DictionaryEntry {
    int key;
    void *value;
    DictionaryEntry *next;
    bool isExists;
};

struct Dictionary {
    DictionaryEntry *all;
    int count;
    int capacity;
};

static Dictionary *Dictionary_New(int capacity) {
    Dictionary *dict = (Dictionary *)calloc(1, sizeof(Dictionary));
    dict->all = (DictionaryEntry *)calloc(capacity, sizeof(DictionaryEntry));
    dict->count = 0;
    dict->capacity = capacity;
    return dict;
}

static void Dictionary_Free(Dictionary *dict) {
    free(dict->all);
    free(dict);
}

static void Dictionary_Add(Dictionary *dict, int key, void *value) {
    DictionaryEntry *all = dict->all;
    if (dict->count >= dict->capacity) {
        // log error
        DictionaryLogNA("[error]Dictionary is full\r\n");
        return;
    }
    int index = key % dict->capacity;
    DictionaryEntry *entry = &all[index];
    if (!entry->isExists) {
        entry->key = key;
        entry->value = value;
        entry->isExists = true;
        entry->next = NULL;
    } else {
        while (entry->next != NULL) {
            entry = entry->next;
        }
        DictionaryEntry *newEntry = (DictionaryEntry *)malloc(sizeof(DictionaryEntry));
        newEntry->key = key;
        newEntry->value = value;
        newEntry->isExists = true;
        newEntry->next = NULL;
        entry->next = newEntry;
    }
}

static bool Dictionary_TryGet(Dictionary *dict, int key, void **value) {

    DictionaryEntry *all = dict->all;
    int index = key % dict->capacity;

    DictionaryEntry *entry = &all[index];
    if (!entry->isExists) {
        return false;
    }
    while (entry != NULL) {
        if (entry->isExists && entry->key == key) {
            *value = entry->value;
            return true;
        }
        entry = entry->next;
    }
    return false;
}

static bool Dictionary_Remove(Dictionary *dict, int key) {
    DictionaryEntry *all = dict->all;
    int index = key % dict->capacity;

    DictionaryEntry *entry = &all[index];
    if (!entry->isExists) {
        return false;
    }
    while (entry != NULL) {
        if (entry->isExists && entry->key == key) {
            entry->isExists = false;
            if (entry->next != NULL) {
                DictionaryEntry *next = entry->next;
                memcpy(entry, next, sizeof(DictionaryEntry));
                free(next);
            }
            return true;
        }
        entry = entry->next;
    }
    return false;
}

#endif