//
// Created by S861321135 on 09/02/2026.
//

#ifndef PRODUTOR_CONSUMIDOR_BUFFER_H
#define PRODUTOR_CONSUMIDOR_BUFFER_H
#include <mutex>
#include <queue>


struct Buffer {
    std::queue<int> fila;
    std::mutex mutex;
    int MaximoValor = 10;
};


#endif //PRODUTOR_CONSUMIDOR_BUFFER_H
