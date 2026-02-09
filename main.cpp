#include <iostream>
#include <thread>
#include <condition_variable>

#include "Buffer.h"

Buffer buffer;
std::condition_variable cheio;
std::condition_variable vazio;

int main() {
    std::cout << "Exemplo de Produtor - Consumidor" << std::endl;

    std::jthread produtor([&]() {
        for (int i = 1; i <= buffer.MaximoValor; ++i) {
            std::unique_lock l{buffer.mutex};
            // Simula a produção de um item
            cheio.wait(l, [&]() { return buffer.fila.size() < buffer.MaximoValor; });
            buffer.fila.push(i);
            std::cout << "Produzido " << i << std::endl;
            cheio.notify_one();
            l.unlock();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
    std::jthread consumidor([&]() {
        for (int i = 1; i <= buffer.MaximoValor; ++i) {
            std::unique_lock l{buffer.mutex};

            // Simula o consumo de um item
            vazio.wait(l, [&]() { return !buffer.fila.empty(); });
            int item = buffer.fila.front();
            buffer.fila.pop();
            std::cout << "Consumido " << item << std::endl;
            vazio.notify_one();
            l.unlock();
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    });
    return 0;
}
