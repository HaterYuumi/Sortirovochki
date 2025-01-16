#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unordered_map>
using namespace std;


unordered_map<int, bool> used; // Используем словарь для отслеживания посещённых вершин


struct Trailer;

struct Lider {
    int key;     // Номер вершины
    int count;   // ( ) Число предшественников число входящих дуг
    Lider *nx;   // (Lider) Указатель на следующий элемент в списке вершин
    Trailer *tr; // TRAILER ( , указатель на Т список указателей на вершины которым ведут исходящие дуги )
};


struct Trailer {
    Lider *ld;   // LEADER, указатель на вершину в списке к которой ведет
                 // , TRAILER исходящая дуга из вершины к которой прикреплен
    Trailer *nx; // указатель на следующий элемент
};


void PrintAllParentsVertex(Lider* vertexes, int Vx) {
    if(vertexes) {
        Lider *ptrVx;
    
        for(ptrVx = vertexes; ptrVx && ptrVx->key!=Vx;ptrVx = ptrVx->nx);
        if(ptrVx) {
            Lider *ptrIx = vertexes;
            while(ptrIx) {
                Trailer *tmp = ptrIx->tr;
                while(tmp) {
                    if(tmp->ld == ptrVx)
                        printf("(%d, parent %d)\n", ptrVx->key, ptrIx->key);
                    tmp = tmp->nx;
                }
                ptrIx = ptrIx->nx;
            }
        }
    }
    else
        printf("NoVertexes");

}


bool IsEdge(Lider* v_A, Lider* v_B) {
    if(v_A && v_B) {
        Trailer *tmp = v_A->tr;
        
        while(tmp && tmp->ld!=v_B){
            tmp = tmp->nx;
        }
    
        if(tmp) return true;
    }
    
    return false;
}


void AddEdge(Lider*& vertexes, int vertexA, int vertexB) {
    Lider *ptrA = NULL, *ptrB=NULL;
    for(ptrA = vertexes; ptrA && ptrA->key != vertexA; ptrA = ptrA->nx);
    for(ptrB = vertexes; ptrB && ptrB->key != vertexB; ptrB = ptrB->nx);


    if(IsEdge(ptrA, ptrB))
        return;


    if(!ptrA) {
        ptrA = new Lider;
        
        ptrA->key = vertexA;
        ptrA->count = 0;
        ptrA->nx = NULL;
        ptrA->tr = NULL;
        
        ptrA->nx = vertexes;
        vertexes = ptrA;
    }
    
    if(!ptrB) {
        ptrB = new Lider;
        
        ptrB->key = vertexB;
        ptrB->count = 0;
        ptrB->nx = NULL;
        ptrB->tr = NULL;
        
        
        ptrB->nx = vertexes;
        vertexes = ptrB;
    }

    //!!!!!!!!!!!!!!!!!!ptrA!=NULL ptrB = !=NULL
    
    
    // Устанавливаем ребро
    
    ptrB->count++;
    //(*ptrB).count++;
    Trailer* elemTr = new Trailer;
    
    elemTr->ld = ptrB;
    
    Trailer* headTr = ptrA->tr;
    
    elemTr->nx = headTr;
    headTr = elemTr;
    ptrA->tr = headTr;
}

void PrintGraph(Lider* vertexes){
    if(vertexes == NULL)
        printf("Graph is Empty");
    else {
        while(vertexes) {
            Trailer* trTmp = vertexes->tr;
            
            if(!trTmp)
                printf("(%d,%d)\n",vertexes->key,0);
            else {
                while(trTmp) {
                    printf("(%d,%d)\n",vertexes->key,trTmp->ld->key);
                    trTmp = trTmp->nx;
                }
    
            }
            vertexes = vertexes->nx;
        }
    }
}


Lider* CreateLDnew(Lider*& vertexes) {
    Lider* LDnew = nullptr; // Новый список для хранения вершин без входящих дуг
    
    // Этап 1: Перемещение вершин без входящих дуг в начало LDnew
    Lider* prev = nullptr;
    Lider* curr = vertexes;
    
    while (curr) {
        if (curr->count == 0) { // Вершина без входящих дуг
            Lider* next = curr->nx;
            if (prev) {
                prev->nx = next;
            } else {
                vertexes = next;
            }
            curr->nx = LDnew;
            LDnew = curr;
            curr = next;
        } else {
            prev = curr;
            curr = curr->nx;
        }
    }
    
    // Обработка LDnew
    while (LDnew) {
        Lider* p = LDnew; // Головной элемент LDnew
        LDnew = LDnew->nx; // Убираем p из LDnew
        
        // Этап 2.1: Уменьшаем поле count у всех вершин, на которые имеются указатели в p->tr
        Trailer* T = p->tr;
        while (T) {
            T->ld->count--; // Уменьшаем count
            if (T->ld->count == 0) { // Если count стал 0
                Lider* temp = T->ld;
                temp->nx = LDnew;
                LDnew = temp;
            }
            Trailer* tmp = T;
            T = T->nx; // Переходим к следующему указателю
            delete tmp; // Удаляем узел TRAILER
        }
        
        // Этап 3: Вывод ключа вершины
        printf("%d ", p->key);
        
        // Этап 4: Удаление вершины
        delete p;
    }
    
    return vertexes; // Возвращаем оставшиеся вершины (если есть)
}


unordered_map<int, int> state; // Состояние вершин: 0 - не посещена, 1 - активна (в пути), 2 - обработана

void dfs(Lider* vertex) {
    state[vertex->key] = 1; // Помечаем вершину как активную (в пути)

    // Обходим всех соседей текущей вершины
    Trailer* neighbor = vertex->tr;
    while (neighbor) {
        Lider* nextVertex = neighbor->ld;

        if (state[nextVertex->key] == 0) {
            // Если сосед ещё не посещён, запускаем для него DFS
            dfs(nextVertex);
        } else if (state[nextVertex->key] == 1) {
            // Если сосед активен (в пути), то найден цикл
            std::cout << "Graph has a cycle!" << std::endl;
            exit(0); // Завершаем программу
        }

        neighbor = neighbor->nx; // Переход к следующему соседу
    }

    state[vertex->key] = 2; // Помечаем вершину как обработанную
}

bool HasCycle(Lider* vertexes) {
    Lider* current = vertexes;

    // Очищаем состояние всех вершин
    state.clear();

    // Запускаем DFS для всех компонент графа
    while (current) {
        if (state[current->key] == 0) { // Если вершина не посещена
            dfs(current);
        }
        current = current->nx;
    }

    return false; // Если программа не завершилась, циклов нет
}



int main() {
    Lider *graph = NULL;
    int vertexA = 0, vertexB = 0;
    
    AddEdge(graph,7,1);
    AddEdge(graph,2,1);
    AddEdge(graph,4,5);
    AddEdge(graph,5,1);
    AddEdge(graph,5,3);
    AddEdge(graph,6,2);
    AddEdge(graph,6,3);
    AddEdge(graph,6,5);
    AddEdge(graph,1,3);
    AddEdge(graph,3,2);
    // AddEdge(graph,0,0);
    
    puts("Print Graph");
    
    PrintGraph(graph);
    
    PrintAllParentsVertex(graph, 4);
    
    HasCycle(graph);
    
    
    return 0;
}