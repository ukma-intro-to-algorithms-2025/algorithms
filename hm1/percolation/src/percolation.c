#include "percolation.h"
#include "../../dynamic_connectivity/src/dynamic_connectivity.h"
#include <stdlib.h>
#include <stdbool.h>

static int index_1d(Percolation* p, int row, int col) {  //функція перетворення 2д координат у 1д
    return row * p->n + col;
}

Percolation* percolation_create(int n) { 
    if (n <= 0) return NULL;

    Percolation* p = (Percolation*)malloc(sizeof(Percolation)); 
    if (!p) return NULL;
    
    //ініціалізація полів 
    p->n = n;           //розмір сітки    
    p->open_count = 0;  //початково відкритих клітинок немає

    int size = n * n;   
    p->open = (bool*)calloc(size, sizeof(bool)); //виділення пам'яті під масив статусів клітинок
    if (!p->open) {
        free(p); 
        return NULL;
    }
    //віртуальні вершини
    p->top = size;       //верх 
    p->bottom = size + 1; //низ

    //union-find
    p->uf = dc_create(size + 2);
    if (!p->uf) {
        free(p->open);
        free(p);
        return NULL;
    }
    return p; 
}
//функція відкриття клітинки
void percolation_open(Percolation* p, int row, int col) {
    if (!p) return;
    if (row < 0 || row >= p->n || col < 0 || col >= p->n) return; //корординати індексів

    int idx = index_1d(p, row, col); //перетворення у 1д індекс
    if (p->open[idx]) return;
     
    //відкриття клітинки
    p->open[idx] = true;
    p->open_count++;

    if (row == 0) //підєднання до верхньої вершини
        dc_union(p->uf, idx, p->top);

    if (row == p->n - 1)  //підєднання до нижньої вершини
        dc_union(p->uf, idx, p->bottom);
    //масиви для перевірки сусідніх клітинок
    const int dr[4] = {-1, 1, 0, 0};  //рядки
    const int dc[4] = {0, 0, -1, 1};  //стовпці

    for (int i = 0; i < 4; i++) {  
        int r = row + dr[i]; 
        int c = col + dc[i];
        //сусідні клітинки в межах сітки
        if (r >= 0 && r < p->n && c >= 0 && c < p->n) {
            int nidx = index_1d(p, r, c); //індекс сусідньої клітинки
            if (p->open[nidx]) { //якщо сусідня клітинка відкрита, об'єднуємо їх
                dc_union(p->uf, idx, nidx);
            }
        }
    }
}

bool percolation_is_open(Percolation* p, int row, int col) {
    if (!p) return false;
    //відкриті координати в межах сітки
    if (row < 0 || row >= p->n || col < 0 || col >= p->n) return false;
    // true - відкрита false - закрита
    return p->open[index_1d(p, row, col)];
}

bool percolation_percolates(Percolation* p) {
    if (!p) return false;
    //чи з'єднані віртуальні вершини
    return dc_connected(p->uf, p->top, p->bottom) != 0;
}

int percolation_number_of_open_sites(Percolation* p) {
    if (!p) return 0;
    return p->open_count; //лічильник відкритих клітинок
}

void percolation_destroy(Percolation* p) {
    if (!p) return;

    dc_free(p->uf); //звільнення union-Find
    free(p->open);  //звільнення масиву статусів клітинок
    free(p);      //звільнення структури
}