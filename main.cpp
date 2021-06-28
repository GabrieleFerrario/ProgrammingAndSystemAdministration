#include "set.h"
#include <iostream>
#include <string>
using namespace std;
/**
	Funzione globale e generica che dato un Set generico
	e un predicato booleano, ritorna un nuovo set composto
	da tutti gli elementi del set che non soddisfano il predicato
	
	@brief Filtra il set in base al predicato
	
	@param S set generico su tipi T
	@param P predicato booleano generico
	@return set generico composto dai dati filtrati
	
*/
template <typename T,typename Eql,typename Pred>
set<T,Eql> filter_out(set <T,Eql> &S,Pred P)
{
	typename set<T,Eql>::const_iterator i,ie;
	set<T,Eql> sf;
	for(i=S.begin(),ie=S.end(); i!=ie; i++)
	{
		if(!P(*i))
			sf.add(*i);
	}
	return sf;
}
/**
	Ridefinizione dell'operatore + che dati due set generici su
	tipi T, ritorna un set su tipi T contenente gli elementi dei 
	due set.(se i due set hanno almeno un elemento in comune viene
	sollevata un'eccezione)
	
	@brief Ridefinizione dell'operatore +
	
	@param s1 set generico su tipi T
	@param s2 set generico su tipi T
	@return set di tipi T composto da tutti gli elementi di s1 e s2
	@throw eccezione causata dall'inserimento di un valore già presente

*/
template <typename T,typename Eql>
set<T,Eql> operator+(const set <T,Eql> &s1,const set <T,Eql> &s2)
{
	typename set<T,Eql>::const_iterator i,ie;
	set <T,Eql> s=s1;
	for(i=s2.begin(),ie=s2.end(); i!=ie; i++)
	{
		s.add(*i);
	}
	return s;
}
/**
	Funtore che ritorna true se il valore è compreso tra due valori
	
	@brief Funtore che verifica se il valore è compreso in un intervallo
*/
struct between {
	int min;
	int max;
public:
	between(int mn, int mx) 
		: min(mn), max(mx){	}


	bool operator()(int n) const {
		return (n>=min) && (n<max);
	}
};
/**
	Funtore che ritorna true se il valore è pari
	
	@brief Funtore che ritorna true se il valore è pari
*/
struct pari
{
	bool operator()(int n) const
	{
		return (n%2) == 0;
	}
};
/**
	Funtore che ritorna true se il valore è dispari
	
	@brief Funtore che ritorna true se il valore è dispari
*/
struct dispari
{
	bool operator()(int n) const
	{
		return (n%2) != 0;
	}
};
/**
	Funtore per il confronto tra due interi
	Ritorna true se sono uguali.
	
	@brief Funtore per il confronto tra interi
*/
struct equal_int
{
	bool operator()(int a,int b) const
	{
		return a == b;
	}
};
void test_metodi_fondamentali() {

	set<int> s1;

	s1.add(11);
	s1.add(12);
	s1.add(10);

	cout << "stampa di s1 dopo inserimenti"<<endl<< s1 << endl;

	set<int> s2(s1);

	cout << "stampa di s2" << endl << s2 << endl;

	set<int> s3;

	s3 = s1;	

	cout << "stampa di s3" << endl << s3 << endl;
	
	set<int> s4;
	try{
		s4=s3+s1;
		cout<<"stampa di s4 (concatenazione di s3 e s1): "<<s4<<endl;

	}catch(equal_element_exception e)
	{
		cout<<"Errore elementi duplicati!"<<endl;
	}
}
void test_uso() {
	
	int a[5] = {7, 9, 12, 9, 1};
	try{
		set<int> s(a,a+5);
	}catch(equal_element_exception e)
	{
		cout<<"Errore elemento duplicato nella sequenza!"<<endl;
		a[3]=90;
	}
	set <int> s(a,a+5);
	cout << "stampa di s costruito con gli iteratori" <<endl << s <<endl;

	cout << "size di s: " << s.conta_elementi() << endl;	
	assert(s.conta_elementi() == 5);

	assert(s[2] == 12);

	assert(s[0] == 7);
	
	assert(s[4] == 1);
	
	int b[7] = {70, 91, 120, 20, 10,100,909};
	set<int> s1(b+1,b+6);
	set<int> s2=s+s1;
	cout<<"stampa di s2:"<<endl<<s2<<endl;
	set<int> sp=filter_out(s2,pari());
	cout<<"elementi NON pari(dispari) di s2:"<<endl<<sp<<endl;
	cout<<"elementi NON dispari(pari) di s2:"<<endl<<filter_out(s2,dispari())<<endl;
	cout<<"elementi NON compresi tra 5 e 30 di s2:"<<endl<<filter_out(s2,between(5,30))<<endl;

}
void test_vario()
{
	typedef set<int,equal_int> set_type;
	
	set_type s1;
	s1.add(1);
	try{
		s1.add(1);
	}catch(equal_element_exception e)
	{
		cout<<"Errore!"<<endl;
	}
	s1.add(2);
	s1.add(3);
	try{
		s1.add(3);
	}catch(equal_element_exception e)
	{
		cout<<"Errore!"<<endl;
	}
	
	cout<<"s1:"<<endl<<s1;
	set_type s2(s1);
	cout<<"s2:"<<endl<<s2;
	set_type s3=s2;
	cout<<"s3:"<<endl<<s3;
	assert(s3[2]==3);
	cout<<"s3[1]:"<<s3[1]<<endl;
	try{
		s1.remove(0);
		cout<<"lista dopo cancellazione: "<<endl<<s1;
	}catch(not_found_element_exception e)
	{
		cout<<"Errore! elemento non trovato"<<endl;
	}
	s1.remove(2);
	cout<<"lista dopo cancellazione: "<<endl<<s1;
	s1.remove(3);
	cout<<"lista dopo cancellazione: "<<endl<<s1;
	s1.remove(1);
	cout<<"lista dopo cancellazione: "<<endl<<s1;
	try{
		s1.remove(3);
		cout<<"lista dopo cancellazione: "<<endl<<s1;
	}catch(not_found_element_exception e)
	{
		cout<<"Errore! elemento non trovato"<<endl;
	}
	
	set<int> sp,sf,sc;
	sp.add(1);
	sp.add(6);
	sf.add(4);
	sf.add(9);
	sf.add(7);
	sf.add(10);
	sf.add(12);
	sc=sp+sf;
	cout<<"risultato concatenazione:"<<endl<<sc<<endl;
}
/**
	Funtore per il confronto tra due stringhe. 
	Ritorna true se sono uguali.
	
	@brief Funtore per il confronto tra due stringhe
*/
struct compare_string
{
	bool operator()(string a, string b) const
	{
		return a.compare(b) == 0;
	}		
};
/**
	funtore che ritorna true se la stringa è minore di un valore
	passato come parametro del costruttore.
	
	@brief funtore per testare set con le stringhe 
*/
struct lunghezza
{
	int l;
	lunghezza(int m): l(m){}
	bool operator()(string s) const
	{
		int ls=s.length();
		return ls<l;
	}
};
void test_stringhe() {
	cout<<"Test su stringhe"<<endl;

	set<string, compare_string> s;

	cout<<"Insertimento dei valori 'pippo', 'pluto', 'paperino', 'topolino'"<<endl;
	s.add("pippo");
	s.add("pluto");	
	s.add("paperino");
	s.add("topolino");
	assert(s[1]=="pluto");
	cout<<"contenuto di s:"<<endl<<s<<endl;
	string s1,s2;
	s1="ciao";
	s2="prova";
	set<string,compare_string> se1,se2;
	se1.add(s1);
	try{
		se1.add(s1);
	}
	catch(equal_element_exception e)
	{
		cout<<"errore elemento gia' presente"<<endl;
	}
	se1.add(s2);
	
	se2=s+se1;
	cout<<"concatenazione:"<<endl<<se2<<endl;
	cout<<"elementi se2 con lunghezza maggiore di 6:"<<endl<<filter_out(se2,lunghezza(6))<<endl;
	s=se2;
	cout<<"s[2]:"<<s[2]<<endl;
	cout<<"contenuto se2:"<<endl<<se2<<endl;
	se2.remove("paperino");
	cout<<"contenuto se2 senza paperino:"<<endl<<se2<<endl;
	se2.remove("pippo");
	cout<<"contenuto se2 senza pippo:"<<endl<<se2<<endl;
	se2.remove("prova");
	cout<<"contenuto se2 senza prova:"<<endl<<se2<<endl;
	try{
		se2.remove("paperino");
		cout<<"contenuto se2 senza paperino:"<<endl<<se2<<endl;
	}catch(not_found_element_exception e)
	{
		cout<<"Errore stringa non trovata!"<<endl;
	}
	se2.remove("topolino");
	cout<<"contenuto se2 senza topolino:"<<endl<<se2<<endl;
	se2.remove("ciao");
	cout<<"contenuto se2 senza ciao:"<<endl<<se2<<endl;
	se2.remove("pluto");
	cout<<"contenuto se2 senza pluto:"<<endl<<se2<<endl;
	try{
		se2.remove("pluto");
		cout<<"contenuto se2 senza pluto:"<<endl<<se2<<endl;
	}catch(not_found_element_exception e)
	{
		cout<<"Errore stringa non trovata!"<<endl;
	}
}
/**
	Struttura che definisce un punto in due dimensioni
	
	@brief Struttura che definisce un punto in due dimensioni
*/
struct point {
	int x; ///< coordinata x del punto
	int y; ///< coordinata y del punto

	point(int xx, int yy) : x(xx), y(yy) {}
};
/**
	Funtore per il confronto tra due punti.
	Ritorna true se i due punti hanno la stessa coordinata x
	e la stessa coordinata y.
	
	@brief Funtore per il confronto tra due punti
*/
struct compare_point {
	bool operator()(const point &p1, const point &p2) const {
		return ((p1.x==p2.x)&&(p1.y==p2.y));
	} 
};
/**
	Ridefinizione dell'operatore di stream << per i punti.
	
	@brief Ridefinizione dell'operatore di stream
*/
ostream &operator<<(ostream &os, const point &p) {
	cout<<"("<<p.x<<","<<p.y<<")";
	return os;
}
/**
	Funtore che ritorna true se la coordinata x o la 
	coordinata y è maggiore o uguale a due valori
	passati come parametro al costruttore.
	
	@brief funtore per testare i punti
*/
struct sup
{
	int xx;
	int yy;
	sup(int m,int n): xx(m),yy(n){}
	bool operator()(point p) const
	{
		return p.x>=xx || p.y>=yy;
	}
};
void test_point(void) {

	set<point,compare_point> s;

	cout<<"Test su point"<<endl;

	cout<<"Insertimento dei valori (1,1), (1,2), (2,7), (0,0), (5,4)"<<endl;
	s.add(point(1,1));
	s.add(point(1,2));
	s.add(point(2,7));
	s.add(point(0,0));
	s.add(point(5,4));
	try{
		s.add(point(1,2));
	}catch(equal_element_exception e)
	{
		cout<<"punto (1,2) gia' presente"<<endl;
	}
	cout<<"Stampa:"<<endl<<s<<endl;

	cout<<"Stampa con iteratori (rimozione (0,0))"<<endl;
	point p(0,0);
	s.remove(p);

	set<point, compare_point>::const_iterator i,ie;

	for(i=s.begin(),ie=s.end(); i!=ie; ++i)
		cout<<*i<<endl;
	
	cout<<"eliminazione (10,1)"<<endl;
	try{
		s.remove(point(10,1));
	}catch(not_found_element_exception e)
	{
		cout<<"errore elemento non presente!"<<endl;
	}
	set<point,compare_point> sc=s;
	cout<<"copia di s"<<endl<<sc<<endl;
	cout<<"s[3]:"<<s[3]<<endl;
	point p1(0,0);
	set<point,compare_point> s3;
	s3.add(point (10,1));
	s3.add(point (9,4));
	s3.add(point (1,2));
	s3.add(point (1,10));
	s3.add(point (4,1));
	set<point,compare_point> s4;
	try{
		s4=s+s3;
	}catch(equal_element_exception e)
	{
		cout<<"Errore concatenazione!"<<endl;
	}
	s3.remove(point (1,2));
	s4=s+s3;
	cout<<"risultato concatenazione di due punti"<<endl<<s4<<endl;
	cout<<"elementi della concatenazione con coordinata x<5 o y<5:"<<endl<<filter_out(s4,sup(5,5))<<endl;
}
int main()
{
	test_metodi_fondamentali();
	
	test_vario();
	
	test_uso();
	
	test_stringhe();
	
	test_point();
	
	return 0;
}