#include<iostream>
#include<cmath>
using namespace std;
class Term {
	friend class Polynomial;
	friend istream& operator>>(istream& is, Polynomial& poly);
	friend ostream& operator<<(ostream& os, Polynomial poly);
private:
	float coef; //coefficient.
	int exp;    //exponent.
};
class Polynomial {
private:
	void resize() {
		if(termArray!=nullptr){
			int newcapacity = capacity * 2;
			Term* newarray = new Term[newcapacity];
			copy(termArray, termArray + capacity, newarray);
			delete[] termArray;
			termArray = newarray;
			capacity = newcapacity;
		}
		else {
			capacity = 2;
			termArray = new Term[capacity];
		}
	}
	Term* termArray; //array of nonzero terms.
	int capacity;    //size of termArray.
	int terms;       //number of nonzero terms.
	//p(x) = a₀x^(e₀) + ... + (an)(x^(en));a set of ordered pairs of <ei,ai>,
	//where ai is a nonzero float coefficient and ei is non-negative integer exponent.
public:
	Polynomial():termArray(nullptr),capacity(0),terms(0){}
	Polynomial(const Polynomial& poly) {
		terms = poly.terms;
		capacity = poly.capacity;
		termArray = new Term[capacity];
		for (int i = 0; i < terms; i++) {
			termArray[i] = poly.termArray[i];
		}
	}
	~Polynomial() { delete[] termArray; }
	//Construct the ploynomial p(x) = 0.
	Polynomial Add(Polynomial poly);
	//Return the sum of the polynomials *this and poly.
	Polynomial Mult(Polynomial poly);
	//Return the product of the polynomials *this and poly.
	float Eval(float f);
	//Evaluate the polynomial *this at f and return the result.
	friend istream& operator>>(istream& is, Polynomial& poly);
	friend ostream& operator<<(ostream& os, Polynomial poly);
};
Polynomial Polynomial::Add(Polynomial poly) {
	Polynomial total;
	total.resize();
	int i = 0, j = 0, k = 0;
	while (i < terms || j < poly.terms) {
		if (i < terms && j < poly.terms) {
			if (termArray[i].exp == poly.termArray[j].exp) {
				total.termArray[k].exp = termArray[i].exp;
				total.termArray[k].coef = termArray[i].coef + poly.termArray[j].coef;
				i++;
				j++;
			}
			else if (termArray[i].exp > poly.termArray[j].exp) {
				total.termArray[k].exp = termArray[i].exp;
				total.termArray[k].coef = termArray[i].coef;
				i++;
			}
			else if (termArray[i].exp < poly.termArray[j].exp) {
				total.termArray[k].exp = poly.termArray[j].exp;
				total.termArray[k].coef = poly.termArray[j].coef;
				j++;
			}
		}
		else if (i < terms && j >= poly.terms) {
			total.termArray[k].exp = termArray[i].exp;
			total.termArray[k].coef = termArray[i].coef;
			i++;
		}
		else if (i >= terms && j < poly.terms) {
			total.termArray[k].exp = poly.termArray[j].exp;
			total.termArray[k].coef = poly.termArray[j].coef;
			j++;
		}
		k++;
		total.terms = k;
		if (k >= total.capacity) {
			total.resize();
		}
	}
	return total;
}
Polynomial Polynomial::Mult(Polynomial poly) {
	Polynomial total;
	total.resize();
	int k = 0;
	for (int i = 0; i < terms; i++) {
		for (int j = 0; j < poly.terms; j++) {
			total.termArray[k].exp = termArray[i].exp + poly.termArray[j].exp;
			total.termArray[k].coef = termArray[i].coef * poly.termArray[j].coef;
			k++;
			total.terms = k;
			if (k >= total.capacity) {
				total.resize();
			}
		}
	}
	int g = 0;
	Polynomial result;
	result.resize();
	for (int i = 0; i < total.terms; i++) {
		result.termArray[g].exp = total.termArray[i].exp;
		result.termArray[g].coef = total.termArray[i].coef;
		for (int j = i+1; j < total.terms; j++) {
			if (total.termArray[i].exp == total.termArray[j].exp) {
				result.termArray[g].coef += total.termArray[j].coef;
				total.termArray[j].exp = 0;
				total.termArray[j].coef = 0;
			}
		}
		g++;
		result.terms = g;
		if (g >= result.capacity) {
			result.resize();
		}
	}
	for (int i = 0; i < result.terms; i++) {
		for (int n = 0; n < result.terms - 1; n++) {
			if (result.termArray[n].exp < result.termArray[n + 1].exp) {
				swap(result.termArray[n].exp, result.termArray[n + 1].exp);
				swap(result.termArray[n].coef, result.termArray[n + 1].coef);
			}
		}
	}
	return result;
}
float Polynomial::Eval(float f) {
	float total = 0;
	for (int i = 0; i < terms; i++) {
		total += termArray[i].coef * pow(f, termArray[i].exp);
	}
	return total;
}
istream& operator>>(istream& is, Polynomial& poly) {
	poly.resize();
	cout << "輸入項數：";
	is >> poly.terms;
	while (poly.capacity < poly.terms) {
		poly.capacity = poly.capacity * 2;
	}
	poly.resize();
	for (int i = 0; i < poly.terms; i++) {
		cout << "輸入(係數 指數)：";
		is >> poly.termArray[i].coef >> poly.termArray[i].exp;
	}
	return is;
}
ostream& operator<<(ostream& os, Polynomial poly) {
	for (int i = 0; i < poly.terms; i++) {
		if (poly.termArray[i].exp == 0 && poly.termArray[i].coef == 0) continue;
		if (i > 0 && i <= poly.terms && poly.termArray[i].coef >= 0) os << "+";
		if (poly.termArray[i].coef == 1) {
			if (poly.termArray[i].exp == 0) {
				os << poly.termArray[i].coef;
			}
			else {
				os << "x^" << poly.termArray[i].exp;
			}
		}
		else {
			if (poly.termArray[i].exp == 0) {
				os << poly.termArray[i].coef;
			}
			else {
				os << poly.termArray[i].coef << "x^" << poly.termArray[i].exp;
			}
		}
	}
	return os;
}
int main() {
	Polynomial p1, p2;
	cout << "輸入第一份多項式：" << endl;
	cin >> p1;
	cout << "輸入第二份多項式：" << endl;
	cin >> p2;
	cout << "p1:" << p1 << endl;
	cout << "p2:" << p2 << endl;
	cout << "Sum=" << p1.Add(p2) << endl;
	cout << "Mult=" << p1.Mult(p2) << endl;
	cout << "帶值：";
	float f;
	cin >> f;
	cout << "p1(" << f <<") =" << p1.Eval(f) << endl;
	return 0;
}