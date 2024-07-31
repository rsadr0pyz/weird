#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define AVERAGE_CASE 1
#define WORST_CASE 2

typedef struct {
    double avr_time, avr_iterations;
} test_result; 

test_result run_binary_search(int element_amt, int sample_size, int mode);
int vector_binary_search(int* vec, int v_size, int searched_val, int* itt_out);


int main()
{
    srand(time(NULL));
    FILE* f = fopen("data", "w");
    fprintf(f, "x average worst\n");

    int start = 1;
    int increment = 1;
    int limit = 28;

    for(int i = start; i<=limit; i+=increment){
        //Size goes from 2 to 2^28.
        int size = pow(2, i);
    
        test_result avr_case = run_binary_search( size, 100000, AVERAGE_CASE);
        test_result worst_case = run_binary_search( size, 100000, WORST_CASE);

        printf("%d/%d\n", (i-start)/increment+1, (limit-start)/increment+1); // Current Progress.

        //Switch these lines for ploting time or iterations.
        fprintf(f, "%d %.15f %.15f\n", size, avr_case.avr_time, worst_case.avr_time);
        //fprintf(f, "%d %.15f %.15f\n", size, avr_case.avr_iterations, worst_case.avr_iterations);
    }

    fclose(f);
    return 0;
}



double get_timestamp()
{
    struct timespec now;
    timespec_get(&now, TIME_UTC);
    return now.tv_sec + ( ((double)now.tv_nsec) / 1e9 );
}

test_result run_binary_search(int vec_size, int sample_size, int mode)
{
    int* vec = malloc(vec_size*sizeof(int));

    for(int i = 0; i<vec_size; i++){
        vec[i] = i;
    }

    double total_time = 0;
    double total_itt = 0;
    for(int i = 0; i<sample_size;i++){
        
        int search_target, itt;
        switch (mode)
        {
            case AVERAGE_CASE:
                search_target = rand() % vec_size; //Random item in the vector
                break;
            case WORST_CASE:
                search_target = vec_size-1; // Biggest element in the vector
                break;
        }
        
        double start_time = get_timestamp();
        int found_idx = vector_binary_search(vec, vec_size, search_target, &itt);
        double time_taken = get_timestamp() - start_time;

        total_time += time_taken;  
        total_itt += itt;
    }

    free(vec);
    
    test_result res = {total_time / sample_size, total_itt / sample_size};
    return res;
}

int vector_binary_search(int* vec, int v_size, int searched_val, int* itt_out)
{
    *itt_out = 0;
    int start_idx = 0, end_idx = v_size-1;
    while(start_idx <= end_idx){
            *itt_out += 1;
            int check_idx = start_idx + (end_idx - start_idx)/2;
            int val = vec[check_idx];
            int diff = searched_val - val;
            
            if(diff == 0){
                    return check_idx;
            }else if(diff > 0){
                    start_idx = check_idx+1;
            }else{
                    end_idx = check_idx-1;
            }
            
    }
    return -1; //Not found.
}