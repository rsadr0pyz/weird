#include "Vector.h"

#include <stdlib.h>
#include <stdio.h>


struct Vector {
        int size;
        int allocated;
        data_type* data;
};


// STATIC FUNCTIONS

// Creates an empty space at a position
static void _vector_allocate_at(Vector* v, int idx, int amt)
{
        data_type* new_data = malloc(sizeof(data_type) * (v->allocated+amt) );
        
        for(int i=0; i<v->size; i++){
                int position = i;
                if(i >= idx){
                        position++;
                }
                new_data[position] = v->data[i];
        }
        free(v->data);
        v->data = new_data;
        v->allocated+= amt;
}


// PUBLIC FUNCTIONS

Vector* vector_build()
{
        Vector* v = calloc(1, sizeof(Vector));
        return v;
}


void vector_insert_at(Vector* v, int idx, data_type data)
{
        if(v->allocated == v->size){
                _vector_allocate_at(v, idx, 1);
        }
        else{
                for(int i = v->size; i>idx; i--){
                        v->data[i] = v->data[i-1];
                }
        }

        v->data[idx] = data;
        v->size++;
}


void vector_push_back(Vector* v, data_type data)
{
        vector_insert_at(v, v->size, data);
}


void vector_remove_at(Vector* v, int idx)
{
        for(int i=idx; i<v->size-1; i++){
                v->data[i] = v->data[i+1];
        }
        v->size--;       
}


data_type vector_find_first(Vector* v, void* val_filter, predicate_func predicate)
{
        for(int i=0; i<v->size; i++){
                data_type data = vector_get(v,i);
                if(predicate(val_filter, data)){
                        return data;
                }
        }
        return NULL;
}

int vector_binary_search(Vector* v, void* val_filter, compar_func compar)
{
        int att = 0;
        int start_idx = 0, end_idx = vector_size(v)-1;
        while(start_idx <= end_idx){
                int check_idx = start_idx + (end_idx - start_idx)/2;
                void* val = vector_get(v, check_idx);
                int diff = compar(val_filter, val);
                att++;
                if(diff == 0){
                        return att;
                }else if(diff > 0){
                        start_idx = check_idx+1;
                }else{
                        end_idx = check_idx-1;
                }
                
        }
        return att;
}

int vector_bubble_sort(Vector* v, compar_func compar)
{
        int swaped = 1;
        int itt = 0;
        for(int j = 0; j<vector_size(v)-1; j++){
                swaped = 0;
                for(int i = 0; i<vector_size(v)-1-j; i++){
                        if(compar(vector_get(v, i), vector_get(v, i+1)) > 0){
                                vector_swap(v,i, i+1);
                                swaped = 1;
                        }
                        itt++;
                }
                itt++;
                if(!swaped) break;
        }
        return itt;
}


void vector_set(Vector*v, int idx, data_type data){
        v->data[idx] = data;
}


void vector_swap(Vector* v, int idx1, int idx2)
{
        data_type d1 = vector_get(v, idx1);
        v->data[idx1] = vector_get(v, idx2);
        v->data[idx2] = d1;
}


data_type vector_get(Vector* v, int idx){
        return v->data[idx];
}


int vector_size(Vector* v){
        return v->size;
}


int vector_allocated_size(Vector* v)
{
        return v->allocated;
}


void vector_allocate(Vector* v, int amt)
{
        _vector_allocate_at(v, vector_size(v)-1, amt);
}


void vector_free(Vector* v){
        free(v->data);
        free(v);
}