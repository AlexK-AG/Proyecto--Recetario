#ifndef __LISTSIMPLELINKED_H__
#define __LISTSIMPLELINKED_H__

using namespace std;
#include <string>
#include <exception>
#include <fstream>
#include <sstream>
#include <cassert> 

/*template <class T>
class Node{
private:
    T data;
    Node* next;
};*/

template <class T>
class ListSimple{
    class Node; //foward declaration

public:
    typedef Node* Position;

private:
    class Node{
    private:
        T data;
        Position next = nullptr;

    public:
        Node();
        Node(const T&);

        T& getData();
        Position getNext() const;

        void setData(const T&);
        void setNext(const Position&);
    };

    Position anchor = nullptr;
    
    bool isValid(const Position&) const;
    void addData(const ListSimple<T>&);

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

        ListSimple();
        ListSimple(const ListSimple<T>&);

    bool isEmpty() const;
    void insertData(const Position&, const T&);
    void insertDataSorted(const T& e, int (*cmp)(const T&, const T&));
    void deleteData(const Position&);
    Position getFirstPos() const;
    Position getLastPos() const;
    Position getPrevPos(const Position&) const;
    Position getNextPos(const Position&) const;

    Position findData(const T&) const;
    Position findDataByName(const T&, int (*cmp)(const T&, const T&)) const;
    Position findDataByInterpreter(const T&, int (*cmp)(const T&, const T&)) const;
    T& retrieve(const Position&);
    T& retrieve2(const Position&) const;
    string toString() const;
    void deleteAll();

    ListSimple<T>& operator=(const ListSimple<T>&);

    void writeToDisk(const std::string&);
    void readFromDisk(const std::string&);
};

//NODO

template<class T>
ListSimple<T>::Node::Node()
{
    
}

template<class T>
ListSimple<T>::Node::Node(const T& e) :data(e)
{
    
}

template<class T>
T& ListSimple<T>::Node::getData()
{
    return this->data;
}

template<class T>
typename ListSimple<T>::Position ListSimple<T>::Node::getNext() const
{
    return this->next;
}

template<class T>
void ListSimple<T>::Node::setData(const T& e)
{
    this->data = e;
}

template<class T>
void ListSimple<T>::Node::setNext(const Position& p)
{
    this->next = p;
}

//Lista Simple

template<class T>
bool ListSimple<T>::isValid(const Position& p) const
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
void ListSimple<T>::addData(const ListSimple<T>& l)
{
    Position aux(l.anchor), newNode, lastInserted(this->getLastPos());

    while(aux != nullptr){
        newNode = new Node(aux->getData());
        if(newNode == nullptr){
            throw Exception("Memoria no disponible, copyAll");
        }

        if(lastInserted == nullptr){
            this->anchor = newNode;
        }else{
            lastInserted->setNext(newNode);
        }

        lastInserted = newNode;
        aux = aux->getNext();
    }
}

template<class T>
ListSimple<T>::ListSimple() {}

template<class T>
ListSimple<T>::ListSimple(const ListSimple<T>& l)
{
    this->addData(l);
}

template<class T>
bool ListSimple<T>::isEmpty() const
{
    return this->anchor == nullptr;
}

template<class T>
void ListSimple<T>::insertData(const Position& p, const T& e)
{
    if(p != nullptr and !this->isValid(p)){
        throw Exception("Posicion invalida, insertData");
    }

    Position newNode(new Node(e)); //aux

    if(new Node == nullptr){
        throw Exception("Memoria no disponible, inserData");
    }

    if(p == nullptr) { //Insertar al pirncipio
        newNode->setNext(this->anchor);
        this->anchor=newNode;
    }else{ //Otra posicion
        newNode->setNext(p->getNext());
        p->setNext(newNode);
    }
}

template<class T>
void ListSimple<T>::insertDataSorted(const T& e, int (*cmp)(const T&, const T&)) {
    Position newNode = new Node(e);
    if (newNode == nullptr) {
        throw Exception("Memoria no disponible, insertDataSorted");
    }

    // Caso 1: Lista vacía o nuevo elemento es menor que el primero
    if (this->isEmpty() || cmp(e, this->anchor->getData()) <= 0) {
        newNode->setNext(this->anchor);
        this->anchor = newNode;
        return;
    }

    // Caso 2: Buscar posición de inserción
    Position current = this->anchor;
    while (current->getNext() != nullptr && 
        cmp(e, current->getNext()->getData()) > 0) {
        current = current->getNext();
    }

    // Insertar el nuevo nodo
    newNode->setNext(current->getNext());
    current->setNext(newNode);
}

template<class T>
void ListSimple<T>::deleteData(const Position& p)
{
    if(!this->isValid(p)){
        throw Exception("Posicion invalida, deletData");
    }

    if(p == this->anchor){ //Eliminar el primero
        this->anchor = p->getNext();
    }else{ //Culaquier dato
        this->getPrevPos(p)->setNext(p->getNext());
    }

    delete(p);
}

template<class T>
typename ListSimple<T>::Position ListSimple<T>::getFirstPos() const
{
    return this->anchor;
}

template<class T>
typename ListSimple<T>::Position ListSimple<T>::getLastPos() const
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
typename ListSimple<T>::Position ListSimple<T>::getPrevPos(const Position& p) const
{
    Position aux(this->anchor);

    while(aux != nullptr and aux->getNext() != p){
        aux = aux->getNext();
    }

    return aux;
}

template<class T>
typename ListSimple<T>::Position ListSimple<T>::getNextPos(const Position& p) const
{
    if(!this->isValid(p)){
        return nullptr;
    }

    return p->getNext();
}

template<class T>
typename ListSimple<T>::Position ListSimple<T>::findData(const T& e) const
{
    Position aux(this->anchor);

    while(aux != nullptr and aux->getData() != e){
        aux = aux->getNext();
    }

    return aux;
}

template <class T>
typename ListSimple<T>::Position ListSimple<T>::findDataByName(const T& e, int (*cmp)(const T&, const T&)) const {
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
typename ListSimple<T>::Position ListSimple<T>::findDataByInterpreter(const T& e, int (*cmp)(const T&, const T&)) const {
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
T& ListSimple<T>::retrieve(const Position& p) 
{
    if(!this->isValid(p)){
        throw Exception("Posición inválida, retrieve");
    }

    return p->getData();
}

template<class T>
T& ListSimple<T>::retrieve2(const Position& p) const
{
    if(!this->isValid(p)){
        throw Exception("Posición inválida, retrieve");
    }

    return p->getData();
}

template<class T>
string ListSimple<T>::toString() const
{
    string result;
    Position aux = this->anchor;

    while(aux != nullptr){
        result += aux->getData().toString() + "\n";

        aux = aux->getNext();
    }

    return result;
}

template<class T>
void ListSimple<T>::deleteAll()
{
    Position aux = nullptr;

    while(this->anchor != nullptr){
        aux = this->anchor;
        this->anchor = aux->getNext();
        delete aux;
    }
}

template<class T>
ListSimple<T>& ListSimple<T>::operator=(const ListSimple<T>& l)
{
    this->deleteAll();

    this->addData(l);

    return *this;
}

template<class T>
void ListSimple<T>::writeToDisk(const std::string& fileName) {
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

template<class T>
void ListSimple<T>::readFromDisk(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw Exception("No se pudo abrir el archivo para lectura");
    }
    
    this->deleteAll(); // Limpiar la lista actual
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::istringstream ss(line);
        T data;
        if (ss >> data) { // Asume que T tiene operador >>
            this->insertData(this->getLastPos(), data);
        }
    }
    file.close();
}

#endif // __LISTSIMPLELINKED_H__