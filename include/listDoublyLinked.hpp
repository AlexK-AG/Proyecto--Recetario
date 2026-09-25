#ifndef __LISTDOUBLYLINKED_H__
#define __LISTDOUBLYLINKED_H__

using namespace std;
#include <string>
#include <exception>
#include <fstream>
#include <sstream>
#include <cassert> 

template <class T>
class ListDoubly{
    class Node; //foward declaration

public:
    typedef Node* Position;

private:
    class Node{
    private:
        T data;
        Position next = nullptr;
        Position prev = nullptr;

    public:
        Node();
        Node(const T&);

        T& getData();
        Position getNext() const;
        Position getPrev() const;

        void setData(const T&);
        void setNext(const Position&);
        void setPrev(const Position&);
    };

    Position anchor = nullptr;
    
    bool isValid(const Position&) const;
    void addData(const ListDoubly<T>&);
    void sortDataQuick(Position, Position, int (*cmp)(const T&, const T&));
    Position partition(Position, Position, int (*cmp)(const T&, const T&));

    public:
    class Exception : public exception {
        private:
        std::string msg;
        
        public:
        Exception() noexcept : msg("Error indefinido") {}
        Exception(const Exception& ex) noexcept : msg(ex.msg) {}
        Exception(const std::string& m) : msg(m) {}
        Exception& operator=(const Exception& ex) noexcept {
            msg = ex.msg;
            return *this;
        }
        virtual ~Exception() {}
        virtual const char* what() const noexcept { return msg.c_str(); }
        };

    ListDoubly();
    ListDoubly(const ListDoubly<T>&);

    bool isEmpty() const;
    void insertData(const Position&, const T&);
    void deleteData(const Position&);
    Position getFirstPos() const;
    Position getLastPos() const;
    Position getPrevPos(const Position&) const;
    Position getNextPos(const Position&) const;

    Position findData(const T&) const;
    Position findDataByRecipeName(const T&, int (*cmp)(const T&, const T&)) const;
    Position findDataByCategory(const T&, int (*cmp)(const T&, const T&)) const;
    T& retrieve(const Position&);
    string toString() const;
    void deleteAll();

    ListDoubly<T>& operator=(const ListDoubly<T>&);

    bool isSorted(int (*cmp)(const T&, const T&)) const;
    void sortDataQuick(int (*cmp)(const T&, const T&));

    void writeToDisk(const std::string& fileName);
    void readFromDisk(const std::string& fileName);
};

//NODO

template<class T>
ListDoubly<T>::Node::Node()
{
    
}

template<class T>
ListDoubly<T>::Node::Node(const T& e) :data(e)
{
    
}

template<class T>
T& ListDoubly<T>::Node::getData()
{
    return this->data;
}

template<class T>
typename ListDoubly<T>::Position ListDoubly<T>::Node::getNext() const
{
    return this->next;
}

template<class T>
typename ListDoubly<T>::Position ListDoubly<T>::Node::getPrev() const
{
    return this->prev;
}

template<class T>
void ListDoubly<T>::Node::setData(const T& e)
{
    this->data = e;
}

template<class T>
void ListDoubly<T>::Node::setNext(const Position& n)
{
    this->next = n;
}

template<class T>
void ListDoubly<T>::Node::setPrev(const Position& p)
{
    this->prev = p;
}

//Lista doble

template<class T>
bool ListDoubly<T>::isValid(const Position& p) const
{
    Position aux(this->anchor);

    while(aux != nullptr){
        if(aux == p){
            return true;
        }

        aux = aux->getNext();
    }

    return false;
}

template<class T>
void ListDoubly<T>::addData(const ListDoubly<T>& l)
{
    Position aux(l.anchor), newNode, lastInserted(nullptr);

    while(aux != nullptr){
        newNode = new Node(aux->getData());
        if(newNode == nullptr){
            throw Exception("Memoria no disponible, copyAll");
        }

        if(lastInserted == nullptr){
            this->anchor = newNode;
        } else {
            lastInserted->setNext(newNode);
            newNode->setPrev(lastInserted);
        }

        lastInserted = newNode;
        aux = aux->getNext();
    }
}


template<class T>
ListDoubly<T>::ListDoubly() {}

template<class T>
ListDoubly<T>::ListDoubly(const ListDoubly<T>& l)
{
    this->addData(l);
}

template<class T>
bool ListDoubly<T>::isEmpty() const
{
    return this->anchor == nullptr;
}

template<class T>
void ListDoubly<T>::insertData(const Position& p, const T& e)
{
    if(p != nullptr and !this->isValid(p)){
        throw Exception("Posicion invalida, insertData");
    }

    Position newNode(new Node(e)); //aux

    if(newNode == nullptr){
        throw Exception("Memoria no disponible, inserData");
    }

    if(p == nullptr) { //Insertar al pirncipio
        //newNode->setPrev(nullptr); Innecesaria
        newNode->setNext(this->anchor);

        if(anchor != nullptr){
            this->anchor->setPrev(newNode);
        }

        this->anchor = newNode;
        
    }else{ //Otra posicion
        newNode->setNext(p->getNext());
        newNode->setPrev(p);

        if(p->getNext() != nullptr){
            p->getNext()->setPrev(newNode);
        }
        p->setNext(newNode);
    }
}

template<class T>
void ListDoubly<T>::deleteData(const Position& p)
{
    if(!this->isValid(p)){
        throw Exception("Posicion invalida, deletData");
    }

    if(p->getPrev() != nullptr){
        p->getPrev()->setNext(p->getNext());
    }

    if(p->getNext() != nullptr){
        p->getNext()->setPrev(p->getPrev());
    }

    if(p == anchor){
        this->anchor = p->getNext();
    }

    delete(p);
}

template<class T>
typename ListDoubly<T>::Position ListDoubly<T>::getFirstPos() const
{
    return this->anchor;
}

template<class T>
typename ListDoubly<T>::Position ListDoubly<T>::getLastPos() const
{
    if(this->isEmpty()){
        return nullptr;
    }

    Position aux(this->anchor);

    while (aux->getNext() != nullptr) {
        aux = aux->getNext();
    }

    return aux;
}

template<class T>
typename ListDoubly<T>::Position ListDoubly<T>::getPrevPos(const Position& p) const
{
    return this-> isValid(p) ? p->getPrev() : nullptr;
}

template<class T>
typename ListDoubly<T>::Position ListDoubly<T>::getNextPos(const Position& p) const
{
    return this-> isValid(p) ? p->getNext() : nullptr;
}

template<class T>
typename ListDoubly<T>::Position ListDoubly<T>::findData(const T& e) const
{
    Position aux(this->anchor);

    while(aux != nullptr and aux->getData() != e){
        aux = aux->getNext();
    }

    return aux;
}

template <class T>
typename ListDoubly<T>::Position ListDoubly<T>::findDataByRecipeName(const T& e, int (*cmp)(const T&, const T&)) const {
  Position aux(this->anchor);
    while (aux != nullptr) {
        if (cmp(aux->getData(), e) == 0) {
            return aux; 
        }
        aux = aux->getNext();
    }
    return nullptr; 
}

template <class T>
typename ListDoubly<T>::Position ListDoubly<T>::findDataByCategory(const T& e, int (*cmp)(const T&, const T&)) const {
  Position aux(this->anchor);
    while (aux != nullptr) {
        if (cmp(aux->getData(), e) == 0) {
            return aux; 
        }
        aux = aux->getNext();
    }
    return nullptr; 
}

template<class T>
T& ListDoubly<T>::retrieve(const Position& p) 
{
    if(!this->isValid(p)){
        throw Exception("Posición inválida, retrieve");
    }

    return p->getData();
}

template<class T>
string ListDoubly<T>::toString() const
{
    string result;
    Position aux;

    while(aux != nullptr){
        result += aux->getData().toString() + "\n";

        aux = aux->getNext();
    }

    return result;
}

template<class T>
void ListDoubly<T>::deleteAll()
{
    Position aux;

    while(this->anchor != nullptr){
        aux = this->anchor;

        this->anchor = aux->getNext();
    }

    delete aux;
}

template<class T>
ListDoubly<T>& ListDoubly<T>::operator=(const ListDoubly<T>& l)
{
    this->deleteAll();

    this->addData(l);

    return *this;
}

//ORDENAMIENTO

template<class T>
bool ListDoubly<T>::isSorted(int (*cmp)(const T&, const T&)) const {
    // Casos especiales: lista vacía o con un solo elemento siempre está ordenada
    if (this->isEmpty() || this->anchor->getNext() == nullptr) {
        return true;
    }

    Position current = this->anchor;
    Position next = current->getNext();

    while (next != nullptr) {
        // Si el elemento actual es mayor que el siguiente según el criterio
        if (cmp(current->getData(), next->getData()) > 0) {
            return false;
        }
        current = next;
        next = next->getNext();
    }

    return true;
}

template <class T>
void ListDoubly<T>::sortDataQuick(int (*cmp)(const T&, const T&)) {
    if (this->isEmpty() || this->anchor->getNext() == nullptr) {
        return; // Lista vacia o con un solo elemento ya esta ordenada
    }
    
    Position last = getLastPos();
    sortDataQuick(this->anchor, last, cmp);
}

template <class T>
void ListDoubly<T>::sortDataQuick(Position leftEdge, Position rightEdge, int (*cmp)(const T&, const T&)) {
    if (leftEdge == nullptr || rightEdge == nullptr || leftEdge == rightEdge || 
        leftEdge == rightEdge->getNext()) {
        return; // Criterio de paro
    }
    
    // Partición
    Position pivot = partition(leftEdge, rightEdge, cmp);
    
    // Ordenar recursivamente las sublistas
    sortDataQuick(leftEdge, pivot->getPrev(), cmp);
    sortDataQuick(pivot->getNext(), rightEdge, cmp);
}

template <class T>
typename ListDoubly<T>::Position ListDoubly<T>::partition(Position left, Position right, int (*cmp)(const T&, const T&)) {
    // Elegimos el Uultimo elemento como pivote
    T pivotData = right->getData();
    
    Position i = left->getPrev(); // Indice del elemento más pequeño
    
    for (Position j = left; j != right; j = j->getNext()) {
        if (cmp(j->getData(), pivotData) <= 0) { // Usamos la función de comparación
            // Incrementamos el índice del elemento más pequeño
            i = (i == nullptr) ? left : i->getNext();
            
            // Intercambiamos los datos de los nodos i y j
            if (i != j) {
                T temp = i->getData();
                i->setData(j->getData());
                j->setData(temp);
            }
        }
    }
    
    // Intercambiamos el pivote con el elemento en i+1
    i = (i == nullptr) ? left : i->getNext();
    T temp = i->getData();
    i->setData(right->getData());
    right->setData(temp);
    
    return i;
}

template <class T>
void ListDoubly<T>::writeToDisk(const std::string& fileName) {
    std::ofstream file(fileName, std::ios_base::trunc);
    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo para escritura");
    }
    Position aux = anchor;
    while (aux != nullptr) {
        file << aux->getData() << "\n";
        aux = aux->getNext();
    }
    file.close();
}

template <class T>
void ListDoubly<T>::readFromDisk(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw Exception("No se pudo abrir el archivo: " + fileName);
    }

    if(this->isEmpty()){
        std::string line;
        while (std::getline(file, line)) {
            // Eliminar espacios en blanco al inicio/final
            line.erase(0, line.find_first_not_of(" \t\n\r"));
            line.erase(line.find_last_not_of(" \t\n\r") + 1);


            if (line.empty()) continue;

            try {
                std::istringstream ss(line);
                T obj;
                if (ss >> obj) { // Usar el operador >> sobrecargado
                    this->insertData(this->getLastPos(), obj);
                } else {
                    throw Exception("Error al parsear línea: " + line);
                }
            } catch (const std::exception& e) {
                file.close();
                throw Exception(std::string("Error procesando línea: ") + e.what());
            }
        }
    } else {
        this->deleteAll(); // Limpiar la lista actual
        std::string line;
        while (std::getline(file, line)) {
            // Eliminar espacios en blanco al inicio/final
            line.erase(0, line.find_first_not_of(" \t\n\r"));
            line.erase(line.find_last_not_of(" \t\n\r") + 1);


            if (line.empty()) continue;

            try {
                std::istringstream ss(line);
                T obj;
                if (ss >> obj) { // Usar el operador >> sobrecargado
                    this->insertData(this->getLastPos(), obj);
                } else {
                    throw Exception("Error al parsear línea: " + line);
                }
            } catch (const std::exception& e) {
                file.close();
                throw Exception(std::string("Error procesando línea: ") + e.what());
            }
        }
    }
    file.close();
}

#endif // __LISTDOUBLYLINKED_H__