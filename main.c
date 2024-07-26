#include "Vector.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define BEST_CASE 0
#define AVERAGE_CASE 1
#define WORST_CASE 2

typedef struct {
    double avr_time, avr_iterations;
} _test_res; 

static double _get_timestamp();
static _test_res _run_binary_search(int element_amt, int sample_size, int mode);



int main()
{
    srand(time(NULL));
    FILE* f = fopen("data", "w");
    fprintf(f, "x best average worst\n");

    int start = 1;
    int increment = 1;
    int limit = 28;

    for(int i = start; i<=limit; i+=increment){
        //Size goes from 2 to 2^28.
        int size = pow(2, i);
        int sample_size = 1000000;
    
        _test_res best_case = _run_binary_search( size, sample_size, BEST_CASE);
        _test_res avr_case = _run_binary_search( size, sample_size, AVERAGE_CASE);
        _test_res worst_case = _run_binary_search( size, sample_size, WORST_CASE);

        printf("%d/%d\n", (i-start)/increment+1, (limit-start)/increment+1);

        fprintf(f, "%d %.15f %.15f %.15f\n", size, best_case.avr_time, avr_case.avr_time, worst_case.avr_time);

    }

    fclose(f);
    return 0;
}



static double _get_timestamp()
{
    struct timespec now;
    timespec_get(&now, TIME_UTC);
    return now.tv_sec + ( ((double)now.tv_nsec) / 1e9 );
}

static int _diff_number(void* v1, void* v2)
{
    return *(int*) v1 - *(int*) v2;
}

static _test_res _run_binary_search( int element_amt, int sample_size, int mode)
{
    Vector* vec = vector_build();

    vector_allocate(vec, element_amt);
    for(int i = 0; i<element_amt; i++){
        int* p = malloc(sizeof(int));
        *p = i;
        vector_push_back(vec, p);
    }

    double total_time = 0;
    double total_itt = 0;
    for(int i = 0; i<sample_size;i++){
        
        int search_target;
        switch (mode)
        {
            case BEST_CASE:
                search_target = *(int*)vector_get(vec, (vector_size(vec)-1)/2);
                break;
            case AVERAGE_CASE:
                search_target = *(int*)vector_get(vec, rand() % element_amt);
                break;
            case WORST_CASE:
                search_target = *(int*)vector_get(vec, vector_size(vec)-1);
                break;
        }
        
        double start_time = _get_timestamp();
        int itt = vector_binary_search(vec, &search_target, _diff_number);
        double time_taken = _get_timestamp() - start_time;

        total_time += time_taken;  
        total_itt += itt;
    }

    for(int i = 0; i<element_amt; i++){
        free(vector_get(vec, i));
    }
    vector_free(vec);  
    
    _test_res res = {total_time / sample_size, total_itt / sample_size};
    return res;
}
