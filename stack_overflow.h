#ifndef STACK_OVERFLOW
#define STACK_OVERFLOW
#include <stdexcept>
/**
 * @brief Classe Eccezione
 * 
 * La classe implementa un'eccezione a run time in
 * caso di operazioni non consentite su stack pieno
 * 
 */
class stack_overflow : public std::runtime_error {
	
	public:
		/**
		 * @brief Costruttore 
		 * 
		 * @param message stringa contenente il messaggio
		 */
		stack_overflow(const std::string &message);

};

#endif