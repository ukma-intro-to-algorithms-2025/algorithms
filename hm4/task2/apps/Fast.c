#include <stdio.h>                  
#include <stdlib.h>                
#include <math.h>                
#include <float.h>                  
#include <string.h>              
#include "../include/point.h"    

typedef struct {                   
    PointPtr point;               
    double slope;                    
} PointWithSlope;        

int compare_point_with_slope(const void* a, const void* b) {  // порівняння для точок з нахилом
    const PointWithSlope* pa = (const PointWithSlope*)a; 
    const PointWithSlope* pb = (const PointWithSlope*)b;  
    
    if (fabs(pa->slope - pb->slope) < 1e-9) {  // Якщо нахили майже рівні (з точністю до 1e-9)
        return compare_points(&pa->point, &pb->point);  // Порівняти точки за координатами
    }                                             
    if (pa->slope < pb->slope) return -1;          // Якщо нахил a менше нахилу b, повернути -1
    return 1;                                
}                                                

int is_subset_of_printed(PointPtr* line, int line_len, PointPtr** printed_lines, int* printed_lengths, int num_printed) {  // дублікати ліній
    for (int i = 0; i < num_printed; i++) {              
        if (printed_lengths[i] >= line_len) {             
            int all_found = 1;                            
            for (int j = 0; j < line_len; j++) {          
                int found = 0;                         
                for (int k = 0; k < printed_lengths[i]; k++) {
                    if (line[j] == printed_lines[i][k]) {          
                        found = 1;                                 
                        break;                                  
                    }                                            
                }                                            
                if (!found) {                                    
                    all_found = 0;                          
                    break;                                    
                }                               
            }                                              
            if (all_found) return 1;                       
        }                                           
    }                                                   
    return 0;                                         
}                                              

void find_collinear_fast(PointPtr* points, int n) {
    if (n < 4) {
        printf("Need at least 4 points to find collinear sets\n");
        return; 
    }
    
    printf("Fast Algorithm \n");
    
    qsort(points, n, sizeof(PointPtr), compare_points);
    
    PointPtr** printed_lines = NULL;
    int* printed_lengths = NULL;
    int num_printed = 0;
    int capacity = 0;
    
    for (int i = 0; i < n; i++) { // Цикл по кожній точці як базовій
        PointWithSlope* slopes = (PointWithSlope*)malloc((n - i - 1) * sizeof(PointWithSlope)); 
        if (!slopes) {
            printf("Memory allocation failed\n");
            return;
        }
    
        int slope_count = 0; 
        for (int j = i + 1; j < n; j++) { 
            slopes[slope_count].point = points[j];
            slopes[slope_count].slope = slope_to(points[i], points[j]); //обчислення нахилу між точками i та j
            slope_count++;
        }
        
        qsort(slopes, slope_count, sizeof(PointWithSlope), compare_point_with_slope);
        
        int start = 0;  
        while (start < slope_count) {
            int end = start + 1;  
            double current_slope = slopes[start].slope;
            
            // РОЗШИРЮЄМО ГРУПУ - додаємо всі точки з таким самим нахилом
            // Умови:
            // 1. end < slope_count - не вийшли за межі масиву
            // 2. нахил поточного елемента майже дорівнює current_slope
            while (end < slope_count && 
                   fabs(slopes[end].slope - current_slope) < 1e-9) {
                end++; 
            }
            
            int group_size = end - start;
            
            if (group_size >= 3) {
                int total_points = group_size + 1;
                PointPtr* line_points = (PointPtr*)malloc(total_points * sizeof(PointPtr));
                
                if (!line_points) {
                    printf("Memory allocation failed\n");
                    free(slopes);
                    for (int k = 0; k < num_printed; k++) { 
                        free(printed_lines[k]);
                    }
                    free(printed_lines);
                    free(printed_lengths);
                    return;
                } 

                line_points[0] = points[i]; 
                for (int k = 0; k < group_size; k++) { 
                    line_points[k + 1] = slopes[start + k].point;
                }
                
                qsort(line_points, total_points, sizeof(PointPtr), compare_points); //сотування за напрямком 
                if (!is_subset_of_printed(line_points, total_points, printed_lines, printed_lengths, num_printed)) { 
                    print_collinear_line(line_points, total_points); 
                    
                    if (num_printed >= capacity) { 
                        capacity = capacity == 0 ? 10 : capacity * 2;
                        printed_lines = realloc(printed_lines, capacity * sizeof(PointPtr*));
                        printed_lengths = realloc(printed_lengths,capacity * sizeof(int));
                        
                        if (!printed_lines || !printed_lengths) {
                            printf("Memory reallocation failed\n");
                            free(line_points);
                            free(slopes);
                            return;
                        }
                    }
                    //перевірка дублікатів
                    printed_lines[num_printed] = line_points; 
                    printed_lengths[num_printed] = total_points;
                    num_printed++;
                } else {
                    free(line_points);
                }
            }
            
            start = end;
        }
        
        free(slopes);
    }
    
    if (num_printed == 0) {
        printf("No sets of 4 collinear points found.\n");
    } else {
        printf("\nTotal %d distinct lines found.\n", num_printed);
    }
    
    for (int i = 0; i < num_printed; i++) {
        free(printed_lines[i]);
    }
    free(printed_lines);
    free(printed_lengths);
}

int main(int argc, char* argv[]) {           
    if (argc != 2) {                      
        printf("Usage: %s <input_file>\n", argv[0]); 
        return 1;                                
    }                                         
    
    int n;                                      
    PointPtr* points = read_points_from_file(argv[1], &n);  
    
    if (!points) {                            
        return 1;                               
    }                               
    
    printf("Read %d points from %s\n", n, argv[1]);  
    find_collinear_fast(points, n);         
    
    free_points_array(points, n);          
    return 0;                                  
}   