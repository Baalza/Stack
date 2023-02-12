#include <iostream>
#include <cassert>
#include "stack.h"
/**
 * @brief Struttura del punto
 * Punto a due dimensioni
 */
struct punto
{
  int x; ///< coordinata x del punto
  int y; ///< coordinata y del punto

  /**
   * @brief Costruttore di default
   * @post x == 0
   * @post y == 0
   */
  punto() : x(0), y(0) {}
  /**
   * @brief Costruttore Secondario
   * 
   * @param xx valore da copiare nella coordinata x
   * @param yy valore da copaire nella coordinata y
   * @post x == xx
   * @post y == yy
   */
  punto(int xx, int yy) : x(xx), y(yy) {}
  /**
   * @brief Copy constructor
   * 
   * @param other punto da copiare
   * @post x = other.x
   * @post y = other.y
   */
  punto(const punto &other) : x(other.x), y(other.y) {}

  /**
   * @brief Operatore di assegnamento
   * 
   * @param other punto da copiare
   * @return ritorna un punto con coordinate preso dal punto passato alla funzione
   */
  punto &operator=(const punto &other)
  {
    x = other.x;
    y = other.y;
    return *this;
  }
  /**
   * @brief Operatore di uguaglianza tra due punti
   * Verifica che entrambe le coordinate dei due punti siano uguali
   * @param other punto da confrontare
   * @return true se i punti sono uguali
   * @return false se i punti sono diversi
   */
  bool operator==(const punto &other)const{
    return x == other.x && y == other.y;
  }
  /**
   * @brief Operatore di disuguaglianza tra due punti
   * Verifica che entrambe le coordinate dei due punti siano diverse
   * @param other punto da confrontare
   * @return true se i punti sono diversi
   * @return false se i punti sono uguali
   */
  bool operator!=(const punto &other)const{
    return (x != other.x | y != other.y);
  }
  /**
      Distruttore. 
    */
  ~punto() {}

  /**
 * @brief Funzione di stream
 *  Ridefinizione dell'operatore di stream per un punto.
    Necessario per l'operatore di stream della classe set.
 * 
 * @param os os stream di output
 * @param p punto da spedire sullo stream
 * @return lo stream di output  
 */
friend std::ostream &operator<<(std::ostream &os, const punto &p)
{
  os << "(" << p.x << "," << p.y << ")";
  return os;
}
bool coordinate_pari() const{
    return x%2 ==0 && y%2==0;
}
};//fine punto
/**
 * @brief Funtore predicato punti
 * Ritorna true se entrambe le coordinate del punto sono pari
 */
struct punto_pari
{
  bool operator()(punto i) const
  {
    return (i.x % 2 == 0 && i.y % 2 == 0);
  }
};
/**
 * @brief Funtore predicato interi
 * Ritorna true se l'intero è pari
 */
struct int_pari
{
  bool operator()(int i) const
  {
    return (i % 2 == 0);
  }
};
/**
 * @brief Funtore predicato stringhe
 * Ritorna true se la stringa contiene un numero di caratteri pari
 */
struct string_pari
{
  bool operator()(std::string i) const
  {
    return (i.size()%2 == 0);
  }
};

/** 
 * Nel seguente metodo vengono effettuati tutti i test su un set di punti
 */
void test_custom()
{
    Stack<punto> st1;
    Stack<punto> st2(st1);
    Stack<punto> st3=st1;
    punto vettore[2] = {punto(2,2), punto(2,2)};
    st1.fill(vettore, vettore+2);
    assert(st1.stored_elements() == 0);
    assert(st2.stored_elements() == 0);
    assert(st3.stored_elements() == st1.stored_elements());
    assert(st1.size()==0);
    assert(st2.size()==0);
    assert(st3.size()==0);
    assert(st1.is_empty());
    assert(st1.is_full()); // uno stack con size = 0 è sia pieno che vuoto
    punto punto1(1, 2);
    punto punto2(3, 4);
    punto punto3(5, 6);
    punto punto4(7, 8);
    punto punto5(1, 2);
    try{
        st1.push(punto1);
    }catch(const stack_overflow &e){
        std::cout<< e.what()<< std::endl;
    }
    Stack<punto> st4(4);
    try{
        st4.top();
    }catch(const stack_underflow &e){
        std::cout<< e.what()<< std::endl;
    }
    try{
        st4.pop();
    }catch(const stack_underflow &e){
        std::cout<< e.what()<< std::endl;
    }
    st4.push(punto1);
    st4.push(punto2);
    st4.push(punto3);
    st4.push(punto4);
    std::cout<<st4<<std::endl;
    assert(st4.stored_elements() == st4.size());
    Stack<punto> st5=st4;
    Stack<punto> st6(st4);
    assert(!st4.is_empty());
    assert(st4.is_full());
    assert(st4.top()== punto4);
    std::cout<<st5<<std::endl;
    assert(st5.top()== punto4);
    assert(st6.top()== punto4);
    assert(st4.size()==4);
    assert(!st4.is_empty());
    assert(st4.is_full());
    st4.pop();
    assert(st4.stored_elements() == st4.size() - 1);
    std::cout<<st4<<std::endl;
    assert(!st4.is_full());
    assert(!st4.is_empty());
    assert(st4.size()==4);
    assert(st4.top()== punto3);
    st4.push(punto4);
    assert(st4.top()== punto4);
    st4.clear(); //Metodo per svuotare lo stack
    assert(st4.is_empty());
    //std::cout<<st4<<std::endl;
    punto punti[4] = {punto1,punto2,punto3,punto4};
    Stack<punto> st7(punti,punti+4); //metodo 2 constructor con coppia di iteratori
    std::cout<<st7<<std::endl;
    Stack<punto> st8(3);
    st8.push(punto4);
    std::cout<<st8<<std::endl;
    st8.fill(punti,punti+4); //metodo 3 come il 2 ma con la clear
    std::cout<<st8<<std::endl;
    st8.pop();
    st8.pop();
    st8.pop();
    assert(st8.stored_elements() == 0);
    try{
      st8.pop();
    }catch(...) {
    }
    st8.push(punto(3,5));
    assert(st8.stored_elements() == 1);
    punto setPunti[4] = {punto(-1, 6), punto(1, 1), punto(1, -4), punto(1, -3)};
    Stack<punto> st9(setPunti, setPunti + 4);
    Stack<punto>::const_iterator i, b, e;
    assert(b == e);         //metodo 4
    i = st9.begin();
    Stack<punto>::const_iterator ii(i);
    assert(i == ii);
    assert((*i) == (*ii));
    i++;
    ii++;
    assert(i == ii);
    assert((*i) == (*ii));
    ++i;
    ii++;
    assert(i == ii);
    assert((*i) == (*ii));
    assert((*i) == punto(1,1) && *ii == punto(1,1));
    i++;
    assert(i != ii);
    assert((*i) != (*ii));
    const punto *p = &(*i);
    assert(*p == punto(-1, 6));
    i = ii;
    assert(i == ii);
    i = st9.begin();
    assert(!i->coordinate_pari());
    punto punto6(2,4);
    assert(st9.checkif(punto6, punto_pari()));
}
/** 
 * Nel seguente metodo vengono effettuati tutti i test su un set di interi
 */
void test_int()
{
    Stack<int> st1;
    Stack<int> st2(st1);
    Stack<int> st3=st1;
    assert(st1.size()==0);
    assert(st2.size()==0);
    assert(st3.size()==0);
    assert(st1.is_empty());
    assert(st1.is_full());
    try{
        st1.push(1);
    }catch(const stack_overflow &e){
        std::cout<< e.what()<< std::endl;
    }
    Stack<int> st4(4);
    try{
        st4.top();
    }catch(const stack_underflow &e){
        std::cout<< e.what()<< std::endl;
    }
    try{
        st4.pop();
    }catch(const stack_underflow &e){
        std::cout<< e.what()<< std::endl;
    }
    st4.push(1);
    st4.push(2);
    st4.push(3);
    st4.push(4);
    std::cout<<st4<<std::endl;
    Stack<int> st5=st4;
    Stack<int> st6(st4);
    assert(!st4.is_empty());
    assert(st4.is_full());
    assert(st4.top()== 4);
    std::cout<<st5<<std::endl;
    assert(st5.top()== 4);
    assert(st6.top()== 4);
    assert(st4.size()==4);
    assert(!st4.is_empty());
    assert(st4.is_full());
    st4.pop();
    assert(st4.stored_elements() == st4.size() - 1);
    std::cout<<st4<<std::endl;
    assert(!st4.is_full());
    assert(!st4.is_empty());
    assert(st4.size()==4);
    assert(st4.top()== 3);
    st4.push(4);
    assert(st4.top()== 4);
    st4.clear(); //Metodo per svuotare lo stack
    assert(st4.is_empty());
    assert(st4.stored_elements() == 0);
    //std::cout<<st4<<std::endl;
    int interi[4] = {1,2,3,4};
    Stack<int> st7(interi,interi+4); //metodo 2 constructor con coppia di iteratori
    std::cout<<st7<<std::endl;
    Stack<int> st8(3);
    st8.push(4);
    std::cout<<st8<<std::endl;
    st8.fill(interi,interi+4); //metodo 3 come il 2 ma con la clear
    std::cout<<st8<<std::endl;
        st8.pop();
    st8.pop();
    st8.pop();
    assert(st8.stored_elements() == 0);
    try{
      st8.pop();
    }catch(...) {
    }
    st8.push(-3);
    assert(st8.stored_elements() == 1);
    int setInteri[4] = {2, 4, 5, 7};
    Stack<int> st9(setInteri, setInteri + 4);
    Stack<int>::const_iterator i, b, e;
    assert(b == e);         //metodo 4
    i = st9.begin();
    Stack<int>::const_iterator ii(i);
    assert(i == ii);
    assert((*i) == (*ii));
    i++;
    ii++;
    assert(i == ii);
    assert((*i) == (*ii));
    ++i;
    ii++;
    assert(i == ii);
    assert((*i) == (*ii));
    assert((*i) == 4 && *ii == 4);
    i++;
    assert(i != ii);
    assert((*i) != (*ii));
    const int *p = &(*i);
    assert(*p == 2);
    i = ii;
    assert(i == ii);
    i = st9.begin();
    int num(6);
    assert(st9.checkif(num, int_pari()));
}
/** 
 * Nel seguente metodo vengono effettuati tutti i test su un set di stringhe
 */
void test_string()
{
    Stack<std::string> st1;
    Stack<std::string> st2(st1);
    Stack<std::string> st3=st1;
    assert(st1.size()==0);
    assert(st2.size()==0);
    assert(st3.size()==0);
    assert(st1.is_empty());
    assert(st1.is_full());
    try{
        st1.push("pippo");
    }catch(const stack_overflow &e){
        std::cout<< e.what()<< std::endl;
    }
    Stack<std::string> st4(4);
    try{
        st4.top();
    }catch(const stack_underflow &e){
        std::cout<< e.what()<< std::endl;
    }
    try{
        st4.pop();
    }catch(const stack_underflow &e){
        std::cout<< e.what()<< std::endl;
    }
    st4.push("pippo");
    st4.push("pluto");
    st4.push("paperino");
    st4.push("cip");
    Stack<std::string>::const_iterator be,e2;
    be = st4.begin();
    e2 = st4.end();
    while (be!=e2)
    {
      std::cout<<*be<<" ";
      be++;
    }
    std::cout<< std::endl;
    std::cout<<st4<<std::endl;
    Stack<std::string> st5=st4;
    Stack<std::string> st6(st4);
    assert(!st4.is_empty());
    assert(st4.is_full());
    assert(st4.top()== "cip");
    std::cout<<st5<<std::endl;
    assert(st5.top()== "cip");
    assert(st6.top()== "cip");
    assert(st4.size()== 4);
    assert(!st4.is_empty());
    assert(st4.is_full());
    st4.pop();
    std::cout<<st4<<std::endl;
    assert(!st4.is_full());
    assert(!st4.is_empty());
    assert(st4.size()==4);
    assert(st4.top()== "paperino");
    st4.push("cip");
    assert(st4.top()== "cip");
    st4.clear(); //Metodo per svuotare lo stack
    assert(st4.is_empty());
    //std::cout<<st4<<std::endl;
    std::string stringhe[4] = {"pippo", "pluto", "paperino", "cip"};
    Stack<std::string> st7(stringhe,stringhe+4); //metodo 2 constructor con coppia di iteratori
    std::cout<<st7<<std::endl;
    Stack<std::string> st8(3);
    st8.push("cip");
    std::cout<<st8<<std::endl;
    st8.fill(stringhe,stringhe+4); //metodo 3 come il 2 ma con la clear
    std::cout<<st8<<std::endl;
    st8.pop();
    st8.pop();
    st8.pop();
    assert(st8.stored_elements() == 0);
    try{
      st8.pop();
    }catch(...) {
    }
    st8.push("cipppppp");
    assert(st8.stored_elements() == 1);
    
    std::string setStringhe[4] = {"pippo", "pluto", "paperino", "cip"};
    Stack<std::string> st9(setStringhe, setStringhe + 4);
    Stack<std::string>::const_iterator i, b, e;
    assert(b == e);         //metodo 4
    i = st9.begin();
    Stack<std::string>::const_iterator ii(i);
    assert(i == ii);
    assert((*i) == (*ii));
    i++;
    ii++;
    assert(i == ii);
    assert((*i) == (*ii));
    ++i;
    ii++;
    assert(i == ii);
    assert((*i) == (*ii));
    assert((*i) == "pluto" && *ii == "pluto");
    i++;
    assert(i != ii);
    assert((*i) != (*ii));
    const std::string *p = &(*i);
    assert(*p == "pippo");
    i = ii;
    assert(i == ii);
    i = st9.begin();
    std::string str = "paperino";
    assert(st9.checkif(str, string_pari()));
}

void load_data(Stack<int> &st){
  int vettore[] = {0,1,2,3,4,5,6};
  st.fill(vettore, vettore + 7);
}
void load_data(Stack<punto> &st){
  punto vettore[] = {punto(2,2), punto(3,3)};
  st.fill(vettore, vettore + 2);
}

void test_constness(const Stack<int> &st){
  assert(st.top() == 4);
  assert(st.stored_elements() == 5 &&st.size() == 5);
  assert(st.is_full());
  assert(!st.is_empty());
}
void test_constness2(const Stack<punto> &st){
  assert(st.top() == punto(3,3));
  assert(st.stored_elements() == 2 && st.size() == 5);
  assert(!st.is_full());
  assert(!st.is_empty());
  st.checkif(punto(2,2), punto_pari());
}


int main(){
  Stack<int> stack(5);
  Stack<punto> stack2(5);
  load_data(stack);
  load_data(stack2);
  test_constness(stack);
  test_constness2(stack2);
  test_custom();
  test_int();
  test_string();
 return 0;
}