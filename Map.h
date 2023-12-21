#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <stdexcept>
#include "Employee.h"

// Deklaracja wyprzedzająca ma zastosowanie w dwóch kontekstach. Po pierwsze wtedy kiedy mamy dwie klasy i one 
// korzystają z siebie nawzajem (np. tworzą obiekty siebie nawzajem jako pola albo referencje itd.). Kompilator staje
// się świadomy istnienia klas dopiero jak je przeczyta, więc nie wie o klasie drugiej dopóki nie przeczyta pierwszej
// i nie zacznie czytać drugiej. Dlatego w pierwszej klasie nie można tworzyć obiektów klasy drugiej. Stosując deklarację
// wyprzedzającą informujemy, że taka klasa istnieje i wtedy możemy odwoływać się do klasy napisanej później.
//class Employee;

template <typename Key, typename Value>
class Map
{
private:
    struct Node
    {
        Key key;
        Value value;
        Node *next;
        Node(const Key &k, const Value &v, Node *n = nullptr) : key(k), value(v), next(n) {}
    };

    Node *head;

public:
    Map() : head(nullptr) {}
    ~Map()
    {
		Free();
    }

    // Copy constructor
    Map(const Map &other)
		: Map() // Delegecja do konstruktora domyślnego.
    {
        Node *current = other.head;
        while (current != nullptr)
        {
            add(current->key, current->value);
            current = current->next;
        }
    }
    
    void Swap(Map &other)
    {
		Node *tmp = head;
		head = other.head;
		other.head = tmp;
	}
    
    void Free()
    {
        while (head != nullptr)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
	}

    // Assignment operator
    Map &operator=(const Map &other)
    {
        if (this != &other)
        {
			// Create a temporary object using the copy constructor.
			// Then swap the contents of tmp and this. After the operator returns
			// the local copy tmp will be destroyed, hence destroying our
			// previous map.
			Map tmp(other);
			Swap(tmp);
        }
        return *this;
    }

    // Add key-value pair to the map
    void add(const Key &key, const Value &value, bool replace = false)
    {
		Value *found = find(key);
        if (found != nullptr)
        {
			if(replace)
				*found = value;
			else
				throw std::runtime_error("Key already exists in the map.");
        }
        else
        {
			head = new Node(key, value, head);
		}
    }

    // Find value associated with the given key
    Value *find(const Key &key) const
    {
		
        Node *current = head;
        while (current != nullptr)
        {
            if (current->key == key)
            {
                return &(current->value);
            }
            current = current->next;
        }
        return nullptr; // Key not found
    }

    // Overload <<
    friend std::ostream &operator<<(std::ostream &os, const Map &map)
    {		
        Node *current = map.head;
        while (current != nullptr)
        {
            os << "Key: " << current->key << ", Value: " << current->value << std::endl;
            current = current->next;
        }
        return os;
    }
};

#endif // MAP_H
