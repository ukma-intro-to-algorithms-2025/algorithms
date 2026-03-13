#include <stdio.h>                   
#include <math.h>                
#include <float.h>                  
#include <string.h>                   
#include "../include/point.h"         

PointPtr create_point(int x, int y) { 
    PointPtr p = (PointPtr)malloc(sizeof(Point)); 
    if (p) {                          
        p->x = x;         // Присвоєння присвоєння відповідних значень
        p->y = y;         
    }                                   
    return p;                         
}                                    

void destroy_point(PointPtr p) {      
    free(p);                        
}                                  

int compare_points(const void* a, const void* b) {  // порівняння точок
    const Point* pa = (const Point*)a;   // Приведення типу a до вказівника на Point
    const Point* pb = (const Point*)b;   // Приведення типу b до вказівника на Point
    
    if (pa->y < pb->y) return -1;        // Якщо y першої точки менше, повернути -1
    if (pa->y > pb->y) return 1;         // Якщо y першої точки більше, повернути 1
    if (pa->x < pb->x) return -1;        // Якщо x першої точки менше (при рівних y), повернути -1
    if (pa->x > pb->x) return 1;         // Якщо x першої точки більше (при рівних y), повернути 1
    return 0;                             // Якщо точки повністю рівні, повернути 0
}                                

double slope_to(PointPtr p1, PointPtr p2) {  // Визначення функції обчислення нахилу
    if (p1->x == p2->x && p1->y == p2->y) {  //якщо координати співпадають
        return -INFINITY;                     
    }                                    
    if (p1->x == p2->x) {     //якщо x координати рівні
        return INFINITY;                   
    }                                      
    if (p1->y == p2->y) {  // Якщо y координати рівні 
        return 0.0;                      
    }                                      
    return (double)(p2->y - p1->y) / (double)(p2->x - p1->x);  //обчислення нахилу у/х
}                                     

PointPtr* read_points_from_file(const char* filename, int* n) {  //читання з файлу input
    FILE* file = fopen(filename, "r");   
    if (!file) {                        
        printf("Error opening file %s\n", filename); 
        return NULL;                     
    }                                    
    if (fscanf(file, "%d", n) != 1) {     
        printf("Error reading number of points\n"); 
        fclose(file);                   
        return NULL;                       
    }                                       
    
    PointPtr* points = (PointPtr*)malloc(*n * sizeof(PointPtr)); 
    if (!points) {                      
        fclose(file);                    
        return NULL;                     
    }      
    
    for (int i = 0; i < *n; i++) {          //читання кожної точки з файлу
        int x, y;                          
        if (fscanf(file, "%d %d", &x, &y) != 2) { 
            printf("Error reading point %d\n", i); 
            for (int j = 0; j < i; j++) {      // Якщо сталася помилка, звільнити вже створені точки
                destroy_point(points[j]);     
            }                                   
            free(points);                     
            fclose(file);        
            return NULL;                        
        }                                    
        points[i] = create_point(x, y);    
    }               
    fclose(file);                               
    return points;                            
}                                          

void free_points_array(PointPtr* points, int n) {  // Визначення функції звільнення масиву точок
    for (int i = 0; i < n; i++) {               // Цикл по всіх точках масиву
        if (points[i]) {                      
            destroy_point(points[i]);         
        }                                       
    }                                          
    free(points);                              
}                                            

void print_collinear_line(PointPtr* line_points, int count) {  //виведення лінії точок
    for (int i = 0; i < count; i++) {        
        if (i > 0) printf(" -> ");           
        printf("(%d, %d)", line_points[i]->x, line_points[i]->y);  
    }                                          
    printf("\n");                                 
}                                          

static void swap(void *a, void *b, size_t size) {  
    char *tmp = malloc(size);                     
    memcpy(tmp, a, size);                      
    memcpy(a, b, size);                          
    memcpy(b, tmp, size);                       
    free(tmp);                                 
}                                                 

void insertion_sort(void *base, size_t n, size_t size, int (*cmp)(const void*, const void*)) {
    char *arr = (char *)base;                   
    for (size_t i = 1; i < n; i++) {             
        char *key = malloc(size);                    
        memcpy(key, arr + i * size, size);     
        int j = i - 1;                                
        while (j >= 0 && cmp(arr + j * size, key) > 0) {  
            memcpy(arr + (j + 1) * size, arr + j * size, size);                             
            j--;                                    
        }                                             
        memcpy(arr + (j + 1) * size, key, size);     
        free(key);                             
    }                                           
}                                                   

void selection_sort(void *base, size_t n, size_t size, int (*cmp)(const void*, const void*)) {  
    char *arr = (char *)base;                    
    for (size_t i = 0; i < n - 1; i++) {           
        size_t min = i;                              
        for (size_t j = i + 1; j < n; j++) {         
            if (cmp(arr + j * size, arr + min * size) < 0) 
                min = j;                             
        }                                             
        if (min != i)                                  
            swap(arr + i * size,                       
                 arr + min * size,                    
                 size);                                
    }                                                 
}                                                      

void shell_sort(void *base, size_t n, size_t size, int (*cmp)(const void*, const void*)) { 
    char *arr = (char *)base;                     
    for (size_t gap = n / 2; gap > 0; gap /= 2) {  
        for (size_t i = gap; i < n; i++) {        
            char *temp = malloc(size);                
            memcpy(temp, arr + i * size, size);       
            size_t j;                               
            for (j = i; j >= gap && cmp(arr + (j - gap) * size, temp) > 0; 
                 j -= gap) {                          
                memcpy(arr + j * size, arr + (j - gap) * size, size);     
            }                                           
            memcpy(arr + j * size, temp, size);         
            free(temp);                                   
        }                                             
    }                                                
}                                                     