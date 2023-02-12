#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <ostream>
#include <exception>
#include <algorithm>
#include <iterator> // std::forward_iterator_tag
#include <cstddef>  // std::ptrdiff_t
#include "stack_overflow.h"
#include "stack_underflow.h"
#include "negative_size.h"
/**
 * @brief 
 * La classe implementa un generico stack di oggetti T
   gli elementi sono organizzati in una pila. Un elemento che viene inserito
   nello stack con il metodo push è posto "sopra" gli altri elementi già presenti nello stack.
   E' possibile prelevare dallo stack un elemento, tramite il metodo pop.
   Una volta che un elemento è prelevato, deve essere rimosso dallo
  stack. Lo stack ha una dimensione fissa che è decisa in fase di costruzione. Quando lo stack è pieno,
  viene lanciata un eccezione.

 * @tparam T 
 */
template<typename T>
class Stack {
    T *_data;
    int _top;
    unsigned int _size;

public:
    /**
     * @brief Costruttore secondario
     * Viene creato lo stack di grandezza size
     * @param size 
     * @post top = -1
     * @post _size = size
     * @post _data = nullptr
     * @throw negative_size eccezzione lanciata in caso di dimensione negativa
     */
   explicit Stack(int size) : _top(-1), _size(0), _data(nullptr) {
        if(size <0){
            throw negative_size("Impossibile creare uno stack con dimensione negativa");
        }
        _size = size;
        try{
            _data = new T[size];
        }catch(...){
            clear();
            throw;
        }

    }
    /**
     * @brief Costruttore di default
     * Viene creato lo stack copiando 
     * @post top = -1
     * @post _size = 0
     * @post _data = nullptr
     */
    Stack() : _top(-1), _size(0), _data(nullptr) {
        
    }
   /**
    * @brief Operatore di assegnamento
    * 
    * @param other stack da copiare
    * @return Stack& reference allo stack this
    */
    Stack& operator=(const Stack &other){
        if (this != &other){
            Stack tmp(other);
            std::swap(_data, tmp._data);
            std::swap(_size, tmp._size);
            std::swap(_top, tmp._top);
        }
        return *this;
    }
     /**
      * @brief Copy constructor
      * Viene creato lo stack copiando i dati membro a membro.
      * @param other stack da copiare
      * @post _data = nullptr
      * @post _size = grandezza dello stack passato come paramentro
      * @post _top = puntatore dello stack passato come paramentro 
      */
    Stack(const Stack &other) : _data(nullptr), _size(other._size), _top(other._top){
        try{
            _data = new T[_size];
            for(unsigned int i = 0; i<_size; i++){
               _data[i] = other._data[i];
            }
        }catch (...){
            clear();
            throw;
        }
    }

    /**
     * @brief Distruttore
     * 
     */
    ~Stack() {
        clear();
    }
    /**
     * @brief Clear
     * Metodo usato per svuotare lo stack
     * 
     */
    void clear(){
        delete[] _data;
        _data = nullptr;
        _size= 0;
        _top = -1;
    }
    /**
     * @brief size
     * Metodo che restituisce la grandezza di uno stack
     * @return unsigned int 
     */
    unsigned int size() const{
        return _size;
    }
    /**
     * @brief is_empty
     * Metodo che restituisce true se uno stack è vuoto, false altrimenti
     * @return true 
     * @return false 
     */
    bool is_empty() const{
        return _top == -1;
    }
    /**
     * @brief is_full
     * Metodo che restituisce true se uno stack è pieno, false altrimenti
     * @return true 
     * @return false 
     */
    bool is_full() const{
        return _top == _size -1;
    }
    /**
     * @brief push
     * Metodo che inserisce in cima allo stack l'oggetto T passato come paramentro
     * @param value 
     * @throw stack_underflow viene lanciata un eccezione se lo stack è pieno
     */
    void push(const T &value){
        if(is_full()){
            throw stack_overflow("Stack overflow");
        }else{
            _top++;
            _data[_top] = value;
            
        }
    }
     /**
      * @brief pop
      * Metodo che rimuove l'elemento in cima allo stack
      * @return T 
      * @throw stack_underflow viene lanciata un eccezione se lo stack è vuoto
      */
     void pop() {
        if (_top == -1) {
            throw stack_underflow("Stack underflow");
        }
        _top--;
    }
    /**
     * @brief top
     * Metoto che restituisce il primo elemento dalla cima dello stack senza rimuoverlo
     * @return const T& 
     * @throw stack_underflow viene lanciata un eccezione se lo stack è vuoto
     */
    const T& top() const{
        if(is_empty()){
            throw stack_underflow("Stack underflow");
        }
        return _data[_top];
    }
  template <typename Q>
  /**
   * @brief Costruttore secondario
   * Data una coppia di puntatori begin e end che puntano rispettivamente
   * all'inizio e alla fine di una sequenza di elementi viene creato uno stack e riempito
   * con gli elementi di questa sequenza
   * @param b 
   * @param e 
   */
  Stack(Q b, Q e) : _data(nullptr), _size(0), _top(-1){
    unsigned int cont = 0;
    Q be = b;
    try
    {
      for (; be != e; ++be){
        cont++;
        
    }
      _data= new T [cont];
      _size = cont;
      for (; b != e; ++b){
        push(static_cast<T>(*b)); 
    }
    
    }catch (...)
    {
      clear();
      throw;
    }
  }
  /**
   * @brief Funzione che ritorna il numero di elementi salvati
   * 
   * @return unsigned int numero di elementi salvati
   */
  unsigned int stored_elements() const{
    return _top + 1;
  }

  template <typename Q>
  /**
   * @brief Fill
   * Metodo che data una coppia di puntatori begin e end che puntano rispettivamente
   * all'inizio e alla fine di una sequenza di elementi viene svuotato lo stack da tutti gli elementi che contiene
   * e riempito con gli elementi della sequenza fino a riempimento
   * @param b 
   * @param e 
   */
  void fill(Q b, Q e){
    unsigned int size = _size;
    clear();
    try
    {
      _size = size;
      _data = new T[_size];
      
      while(!is_full() && b!=e){
        push(static_cast<T>(*b));
        ++b;
      }
    
    }catch (...)
    {
      clear();
      throw;
    }
  }
    /**
   * @brief Funzione di stream
   * Funzione GLOBALE che implementa l'operatore di stream.
     La funzione è templata sulla sett ed è messa
     friend perchè accediamo ai dati privati di set.
   * @param os stream di output
   * @param s set da spedire sullo stream
   * @return lo stream di output 
   */
  friend std::ostream &operator<<(std::ostream &os, const Stack &st)
  {
    for(int i=0; i<st._top+1; i++){
        os<<st._data[i] <<" ";
    }
    return os;
  }
  /**
   * @brief const_iterator
   * La classe implementa i const iterator per iterare sugli elementi
   */
  class const_iterator {

  public:
    typedef std::forward_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef const T* pointer;
    typedef const T& reference;
  
    const_iterator() : ptr(nullptr), stack(nullptr) {
    }
    
    const_iterator(const const_iterator &other) : ptr(other.ptr), stack(other.stack) {
    }

    const_iterator& operator=(const const_iterator &other) {
      ptr = other.ptr;
      stack = other.stack;
      return *this;
    }

    ~const_iterator() { 
    }

    reference operator*() const {
      return * ptr;
    }

    pointer operator->() const {
      return (ptr);
    }
    
    const_iterator operator++(int) {
      const_iterator tmp(*this);
      if(ptr == &stack->_data[0])
        ptr = nullptr;
      else
        ptr--;
      return tmp;
    }

    const_iterator& operator++() {
      if(ptr == &stack->_data[0])
        ptr = nullptr;
      else
        ptr--;
      return *this;
    }

    bool operator==(const const_iterator &other) const {
      return (ptr == other.ptr);
    }
    
    bool operator!=(const const_iterator &other) const {
      return !(other == *this);
    }

  private:
    friend class Stack; 
    const Stack *stack;
    const T *ptr;

    const_iterator(const T *p, const Stack *st) : ptr(p), stack(st){ }
    
  }; 
  const_iterator begin() const {
    return const_iterator(&_data[_top], this);
  }
  
  const_iterator end() const {
    return const_iterator(nullptr, this);
  } 
  /**
   * @brief Metodo che applica il predicato P a un elemento generico della classe
   * restituendo true o false se il predicato viene soddisfatto o meno
   * @tparam P 
   * @param value 
   * @param pred 
   * @return true 
   * @return false 
   */
  template<typename P>
  bool checkif(const T& value, P pred) const{
    return pred(value);
  }
}; //fine stack.h
#endif