#include <iostream>
#include <thread>
#include <condition_variable>

#include "Buffer.h"

Buffer buffer;
std::condition_variable nao_vazio;
std::condition_variable nao_cheio;

int main() {
    std::cout << "Exemplo de Produtor - Consumidor" << std::endl;

    std::jthread produtor([&]() {
        for (int i = 1; i <= buffer.MaximoValor; ++i) {
            std::unique_lock l{buffer.mutex};
            // Simula a produção de um item
            nao_cheio.wait(l, [&]() { return buffer.fila.size() < buffer.MaximoValor; });
            buffer.fila.push(i);
            std::cout << "Produzido " << i << std::endl;
            nao_vazio.notify_one();
            l.unlock();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
    std::jthread consumidor([&]() {
        for (int i = 1; i <= buffer.MaximoValor; ++i) {
            std::unique_lock l{buffer.mutex};

            // Simula o consumo de um item
            nao_vazio.wait(l, [&]() { return !buffer.fila.empty(); });
            const int item = buffer.fila.front();
            buffer.fila.pop();
            std::cout << "Consumido " << item << std::endl;
            nao_cheio.notify_one();
            l.unlock();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
    return 0;
}
