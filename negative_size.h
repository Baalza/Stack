#ifndef NEGATIVE_SIZE
#define NEGATIVE_SIZE
#include <stdexcept>
/**
 * @brief Classe Eccezione
 * 
 * La classe implementa un'eccezione a run time in
 * caso di size negativa
 * 
 */
class negative_size : public std::runtime_error {
	
	public:
		/**
		 * @brief Costruttore 
		 * 
		 * @param message stringa contenente il messaggio
		 */
		negative_size(const std::string &message);

};

#endif