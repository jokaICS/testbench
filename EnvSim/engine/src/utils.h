//     Project: EnvSim
//      Module: libenvsim / utils.h
// Description: Common utility functions
//
// History:
// - 22.09.15, J. Kastner: initial version

#ifndef ENGINE_UTILS_H
#define ENGINE_UTILS_H

#include <stdlib.h>
#include <stdbool.h>

#define MALLOC(type) ((type*) malloc(sizeof(type)));


// Elements of a singly linked list
typedef struct LIST_ENTRY {
  char *data;
  struct LIST_ENTRY *tail;
} es_ListEntry;

// Appends the specified data element to the end of a list,
// represented by the specified list entry.
// Returns the new list tail.
es_ListEntry* es_list_append(es_ListEntry *list, char *data);

// Executes the specified function f for each element in the provided list.
// Whenever f() returns false, the corresponding list entry is removed from the list;
// otherwise, the entry will remain in the updated list.
// Returns the head of the filtered list.
es_ListEntry* es_list_filter(es_ListEntry *list, bool (*f)(char*));

// Removes the head from the specified list and writes its data entry
// at the location specified by **data. Returns the new head of the list.
es_ListEntry* es_list_remove_head(es_ListEntry *list, char **data);

// Inserts a new entry into a sorted linked list and returns the link to the new
// list head. The sorting order is determined by the cmp function, which must return <0
// if data1<data2, >0 if data1>data2, and 0 otherwise.
es_ListEntry* es_list_insert(es_ListEntry *list, char *data, int (*cmp)(char *data1, char *data2));

// Encodes nbytes from the specified bytes buffer as a HEX string
// and writes the result into the specified hexbuf. The size of hexbuf
// must be at least 2*nbytes+1.
void es_bytes_to_hex(size_t nbytes, char* bytes, char* hexbuf);

// Decodes nbytes from the specified HEX string into the provided buffer
void es_hex_to_bytes(size_t nbytes, char* hex, char* bytesbuf);

#endif //ENGINE_UTILS_H
