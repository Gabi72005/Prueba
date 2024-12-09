#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"
#include "C:\Users\gabri\OneDrive\Escritorio\UPV\PRA\Código\Practicas\P1" // Modifica esta ruta si es necesario

template <typename V>
class HashTable : public Dict<V> {
private:
    int n; // Número de elementos actuales en la tabla
    int max; // Número total de cubetas
    ListLinked<TableEntry<V>>* table; // Array de punteros a listas enlazadas

    // Función hash
    int h(std::string key) {
        int ascii_sum = 0;
        for (char c : key) {
            ascii_sum += static_cast<int>(c);
        }
        return ascii_sum % max;
    }

public:
    // Constructor
    HashTable(int size) : n(0), max(size) {
        table = new ListLinked<TableEntry<V>>[max];
    }

    // Destructor
    ~HashTable() {
        delete[] table;
    }

    // Devuelve la capacidad de la tabla
    int capacity() const {
        return max;
    }

    // Sobrecarga del operador []
    V operator[](std::string key) {
        int index = h(key);
        for (const auto& entry : table[index]) {
            if (entry.key == key) {
                return entry.value;
            }
        }
        throw std::runtime_error("Clave no encontrada");
    }

    // Sobrecarga del operador <<
    friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &ht) {
        for (int i = 0; i < ht.max; ++i) {
            out << "Cubeta " << i << ": ";
            for (const auto& entry : ht.table[i]) {
                out << "{" << entry.key << ": " << entry.value << "} ";
            }
            out << "\n";
        }
        return out;
    }

    // Métodos insert, search y remove (implementación usando ListLinked)
    void insert(std::string key, V value) {
        int index = h(key);
        for (auto& entry : table[index]) {
            if (entry.key == key) {
                entry.value = value;
                return;
            }
        }
        table[index].insertFront(TableEntry<V>(key, value));
        ++n;
    }

    V search(std::string key) {
        int index = h(key);
        for (const auto& entry : table[index]) {
            if (entry.key == key) {
                return entry.value;
            }
        }
        throw std::runtime_error("Clave no encontrada");
    }

    void remove(std::string key) {
        int index = h(key);
        table[index].removeIf([&key](const TableEntry<V>& entry) {
            return entry.key == key;
        });
        --n;
    }
};

#endif
