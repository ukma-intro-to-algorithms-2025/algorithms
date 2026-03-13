#include <stdio.h>                   
#include <stdlib.h>               
#include <math.h>                  
#include <float.h>                  
#include <string.h>                 
#include "../include/point.h"        

int are_collinear(PointPtr p, PointPtr q, PointPtr r, PointPtr s) {  //колінеарність 4 точок
    double slope_pq = slope_to(p, q);    
    double slope_pr = slope_to(p, r);   //обчислення нахилів 
    double slope_ps = slope_to(p, s);   
    
    if (fabs(slope_pq - slope_pr) > 1e-9) return 0;  
    if (fabs(slope_pq - slope_ps) > 1e-9) return 0;  
    return 1;  
}  

int is_line_printed(PointPtr* line, PointPtr** printed_lines, int num_printed) {  //перевірка дублікатів ліній
    for (int i = 0; i < num_printed; i++) {  
        int match = 1;             //початково співпадіння 1                
        for (int j = 0; j < 4; j++) {                 
            if (line[j] != printed_lines[i][j]) {     // Якщо точки не співпадають
                match = 0;                              // співпадіння 0
                break;                                 
            }                                        
        }                                            
        if (match) return 1;                        
    }                                             
    return 0;                                         
}                                                    

void find_collinear_brute(PointPtr* points, int n) {  // пошук колінеарних точок "грубою силою"
    if (n < 4) {                                     
        printf("Need at least 4 points to find collinear sets\n");  
        return;                                        
    }                                              
    printf("Brute Force \n");         
    
    PointPtr** printed_lines = NULL;       
    int num_printed = 0;      
    int capacity = 0;       
    for (int i = 0; i < n - 3; i++) {              //цикли для всіх чотирьох точок
        for (int j = i + 1; j < n - 2; j++) {         
            for (int k = j + 1; k < n - 1; k++) {        
                for (int l = k + 1; l < n; l++) {         
                    if (are_collinear(points[i], points[j], points[k], points[l])) {  // Перевірка колінеарності
                        PointPtr line[4] = {points[i], points[j], points[k], points[l]};  // Масив з 4 точок
                        
                        qsort(line, 4, sizeof(PointPtr), compare_points); 
                        
                        if (!is_line_printed(line, printed_lines, num_printed)) {  
                            print_collinear_line(line, 4); 
                            
                            if (num_printed >= capacity) { 
                                capacity = capacity == 0 ? 10 : capacity * 2;  
                                printed_lines = realloc(printed_lines, capacity * sizeof(PointPtr*));  
                            }  
                            printed_lines[num_printed] = malloc(4 * sizeof(PointPtr)); 
                            memcpy(printed_lines[num_printed], line, 4 * sizeof(PointPtr));  
                            num_printed++;  
                        }  
                    }  
                }  
            }  
        } 
    } 
    
    for (int i = 0; i < num_printed; i++) { 
        free(printed_lines[i]);             
    }                                        
    free(printed_lines);                    
    
    if (num_printed == 0) {                   
        printf("No sets of 4 collinear points found.\n"); 
    } else {                                
        printf("\nTotal %d distinct lines found.\n", num_printed); 
    }                                         
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
    find_collinear_brute(points, n);             
    free_points_array(points, n);             
    return 0;     
}               