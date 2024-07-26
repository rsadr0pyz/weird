#ifndef _VECTOR_H
#define _VECTOR_H


typedef void* data_type;
typedef struct Vector Vector;

typedef int (predicate_func)(void* val_filter, data_type d2);
typedef int (compar_func)(data_type d1, data_type d2);


Vector* vector_build();

void vector_insert_at(Vector* v, int idx, data_type data);

void vector_remove_at(Vector* v, int idx);   

void vector_push_back(Vector* v, data_type data);

data_type vector_get(Vector* v, int idx);

void vector_set(Vector*v, int idx, data_type data);

int vector_size(Vector* v);

void vector_swap(Vector* v, int idx1, int idx2);

void vector_free(Vector* v);

int vector_binary_search(Vector* v, void* val_filter, compar_func compar);

int vector_bubble_sort(Vector* v, compar_func compar);

data_type vector_find_first(Vector* v, void* val_filter, predicate_func predicate);

void vector_allocate(Vector* v, int amt);

#endif