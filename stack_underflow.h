#ifndef STACK_UNDERFLOW
#define STACK_UNDERFLOW
#include <stdexcept>
/**
 * @brief Classe Eccezione
 * 
 * La classe implementa un'eccezione a run time in
 * caso di operazioni non consentite su stack vuoto
 * 
 */
class stack_underflow : public std::runtime_error {
	
	public:
		/**
		 * @brief Costruttore 
		 * 
		 * @param message stringa contenente il messaggio
		 */
		stack_underflow(const std::string &message);

};

#endif