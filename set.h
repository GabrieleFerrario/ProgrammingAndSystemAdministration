#ifndef SET_H
#define SET_H

#include <iostream>
#include <cassert>
#include <ostream>	
#include <cstddef>	
#include <algorithm>
#include <iterator>

/**
	@file set.h 
	@brief Dichiarazione della classe set.
**/

/**
	Classe che implementa l'eccezione custom che si verifica quando 
	si cerca di inserire un elemento già presente nel set.
	
	@brief Eccezione custom che rappresenta l'evento, elemento già presente nel set.

*/
class equal_element_exception{};
/**

	Classe che implementa l'eccezione custom che si verifica quando 
	si cerca di eliminare un elemento non presente nel set.
	
	@brief Eccezione custom che rappresenta l'evento di elemento non trovato.
*/
class not_found_element_exception{};
/**
	Funtore di confronto generico per tipi standard che valuta l'uguaglianza 
	tra i due dati ritornando true se a==b.
	
	@brief Funtore di comparazione generico per tipi standard.
*/
template <typename T>
struct a_equal_b {
	bool operator()(const T &a, const T &b) const {
		return a==b;
	}
};
/**
	Classe che implementa un set di dati generici T.
	Il confronto tra i dati è effettuato tramite un funtore di confronto Eql.
	Di default il funtore usa gli operatori di confronto per i tipi standard.
	
	@brief Classe che rappresenta un set dinamico di dati generici.
	
	@param T tipo del dato
	@param Eql funtore di confronto tra due dati
*/
template <typename T, 
	typename Eql=a_equal_b<T> > 
class set {
	/**
		Struttura di supporto interna che implementa un elemento del set.
		
		@brief Elemento del set
	*/
	struct Nodo {
		T value; ///< Dato inserito nel set
		Nodo *next;///< puntatore all'elemento successivo del set
		
		/**
			Costruttore di default per istanziare un nodo vuoto.
			
			@brief Costruttore di default
		*/
		Nodo() : next(0) {} 
		/**
			Costruttore secondario che inizializza il nodo
			
			@brief Costruttore secondario
			
			@param v valore del dato
			@param n puntatore all'elemento successivo
		*/
		Nodo(const T &v, Nodo* n = 0)
		: value(v), next(n){}
	};
	
	Nodo* _head; ///< puntatore al primo elemento del set
	
	Eql _equal; ///< oggetto funtore per il confronto
	
public:
	/**
		Costruttore di default per istanziare un set vuoto
		
		@brief Costruttore di default
	*/
	set() : _head(0) {}
	/**
		Costruttore di copia. Permette di istanziare un set con i valori
		presi da un altro set.
		
		@brief Costruttore di copia
		
		@param other set da copiare
		@throw eccezione di allocazione di memoria
	*/
	set(const set &other) 
	: _head(0) { 
		const Nodo *tmp = other._head;
		
		try{
			while(tmp != 0)
			{
				add(tmp->value);
				tmp = tmp -> next;
			}
		}catch(...)
		{
			clear();
			throw;
		}
	}
	/**
		Operatore di assegnamento. Permette la copia tra set.
		
		@brief Operatore di assegnamento
		
		@param other set da copiare
		@return reference a this
		@throw eccezione di allocazione di memoria
	*/
	set& operator = (const set &other) {
		if(&other != this) {
			set tmp(other);
			std::swap(tmp._head, _head);
		}
			
		return *this;
	}
	/**
		Distruttore. Rimuove la memoria allocata.
		
		@brief Distruttore
	*/
	~set() {
		clear();
	}
	/**
		Cancella il contenuto del set
		
		@brief cancella il contenuto del set
	*/
	void clear() {
		Nodo *tmp = _head;
		
		while (tmp != 0)
		{
			Nodo *next = tmp->next; 	
			delete tmp;				
			tmp = next;				
		}
		_head=0;
	}
	/**
		Inserisce un elemento nel set in coda se non è già presente
		nel set, il confronto è definito dal funtore di confronto
		
		@brief Permette l'inserimento di elemento se non presente nel set
		
		@param value valore da inserire
		@throw eccezione causata dall'inserimento di un valore già presente
	*/	
	void add(const T &value) {
		Nodo *n=new Nodo(value);
		
		if(_head==0)
		{
			_head=n;
			return ;
		}
		
		Nodo *tmp= _head;
		Nodo *prev = _head;

		while(tmp!=0)
		{
			if(_equal(tmp->value, value)) {
				delete n;
				throw equal_element_exception();
			}
			prev=tmp;
			tmp=tmp->next;
		}
		prev->next=n;
	}
	/**
		Determina il numero di elementi presenti nel set
		
		@brief Numero elementi nel set
		
		@return numero di elementi inseriti nel set
	*/
	unsigned int conta_elementi() const {
		int cont=0;
		Nodo *tmp= _head;
		while(tmp!=0)
		{
			cont++;
			tmp=tmp->next;
		}
		return cont;
	}
	/**
		Metodo per accedere al valore index-esimo del set.
		Accesso ai dati in lettura
		
		@brief accesso in lettura al valore index-esimo
		
		@pre E' necessario che size>index
		@param index Indice dell'elemento del set da leggere
		@return L'elemento index-esimo
	*/
	const T& operator[](unsigned int index) const
	{
		assert(index<conta_elementi()); // pre-condizione
		Nodo *tmp= _head;
		for(int i=0;i<index;i++)
		{
			tmp=tmp->next;
		}
		return tmp->value;
	}
	/**
		Metodo che permette di eliminare un elemento dal set se è presente
		
		@brief Eliminazione elemento dal set
		
		@param value valore da eliminare
		@throw eccezione causata dall'eliminazione di un valore non presente
	*/
	void remove(const T &value)
	{
		Nodo *n;
		Nodo *pa= _head;
		Nodo *pp= _head;
		bool find=false;
		if(pa!=0)
		{
			if(_equal(pa->value,value))
			{
				n=_head;
				_head=pa->next;
				delete n;
				return ;
			}
			while(pa!=0 && !_equal(pa->value,value))
			{
				pp=pa;
				pa=pa->next;
			}
			if(pa!=0 && _equal(pa->value,value))
			{
				find=true;
				n=pa;
				pp->next=pa->next;
				delete n;
			}
		}
		if(!find)
				throw not_found_element_exception();
	}
	/**
		Costruttore secondario che costruisce il set a partire
		da una sequenza generica di dati indentificata da due iteratori.
		
		@brief Costruttore che usa iteratori
		
		@param begin iteratore di inizio della sequenza
		@param end interatore di fine della sequenza
		@throw eccezione di allocazione di memoria
		@throw eccezione dovuta all'inserimento di elementi uguali
	*/
	template <typename Q>
	set(Q begin, Q end) : _head(0) {
		try {		
			for(; begin!=end;begin++) {
				add(static_cast<T>(*begin));		
			}
		}
		catch(...) {
			clear();
			throw;
		}
	}
	/**
		Iteratore costante del set
		
		@brief Iteratore costante del set
	*/
	class const_iterator {
			
		public:
			typedef std::forward_iterator_tag iterator_category;
			typedef T                         value_type;
			typedef ptrdiff_t                 difference_type;
			typedef const T*                  pointer;	
			typedef const T&                  reference;		

			const_iterator() : n(0) {}
		
			const_iterator(const const_iterator &other) : n(other.n) {}
		
			const_iterator& operator=(const const_iterator &other)
			{ 
				n = other.n;
				return *this;
			} 

			~const_iterator() {
				n=0;
			} 
			
			// Ritorna il dato riferito dall'iteratore (dereferenziamento)
			reference operator*() const 
			{
				return n->value;
			}
			
			// Ritorna il puntatore al dato riferito dall'iteratore
			pointer operator->() const 
			{ 
				return &(n->value);  
			} 

			// Operatore di iterazione post-incremento
			const_iterator operator++(int) 
			{ 
				const_iterator old(*this);
				n = n->next;
				return old;
			}

			// Operatore di iterazione pre-incremento
			const_iterator& operator++() 
			{ 
				n = n->next;
				return *this;
			}
			
			// Uguaglianza
			bool operator==(const const_iterator &other) const 
			{
				return n == other.n;
			}
			
			// Diversita'
			bool operator!=(const const_iterator &other) const 
			{
				return n != other.n;
			}
		
		private:
			const Nodo *n; 
			
			// La classe container deve essere messa friend dell'iteratore per poter
			// usare il costruttore di inizializzazione.
			friend class set;
			
			//Costruttore privato di inizializzazione 
			const_iterator(const Nodo* nn) : n(nn){} 
		
		};
		/**
			Ritorna l'iteratore all'inizio della sequenza dei dati
			
			@brief iteratore all'inizio della sequenza
			
			@return iteratore all'inizio della sequenza
		*/
		const_iterator begin() const {
			return const_iterator(_head);
		}
		/**
			Ritorna l'iteratore alla fine della sequenza dei dati
			
			@brief iteratore alla fine della sequenza
			
			@return iteratore alla fine della sequenza
		*/
		const_iterator end() const {
			return const_iterator(0); 
		}
		
};
/**
	Ridefinizione dell'operatore di stream per la stampa del contenuto 
	del set.
	
	@brief Ridefinizione dell'operatore di stream
	
	@param os oggetto stream di output
	@param s set da stampare
	@return reference allo stream di output
*/
template <typename T, typename Eql>
std::ostream &operator<<(std::ostream &os,
	const set<T,Eql> &s) {
		
	typename set<T,Eql>::const_iterator i, ie;
	
	for(i = s.begin(), ie = s.end(); i!=ie; i++) {
		os << *i << std::endl;
	}
	return os;
}
#endif
