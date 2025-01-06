#include <iostream>
#include <stdexcept>
using namespace std;
struct Term {
    float coef;
    int exp;
    Term* link;
};
class Polynomial {
private:
    Term* head;
    Term* getNode(float coef, int exp) {
        Term* newNode = new Term;
        newNode->coef = coef;
        newNode->exp = exp;
        newNode->link = nullptr;
        return newNode;
    }
    void attach(float coef, int exp) {
        if (coef == 0) return;
        Term* newNode = getNode(coef, exp);
        Term* last = head;
        while (last->link != head) {
            last = last->link;
        }
        last->link = newNode;
        newNode->link = head;
    }
public:
    Polynomial() {
        head = getNode(0, -1);
        head->link = head;
    }
    Polynomial(const Polynomial& poly) {
        head = getNode(0, -1);
        head->link = head;
        Term* current = poly.head->link;
        while (current != poly.head) {
            attach(current->coef, current->exp);
            current = current->link;
        }
    }
    ~Polynomial() {
        Term* current = head->link;
        while (current != head) {
            Term* toDelete = current;
            current = current->link;
            delete toDelete;
        }
        delete head;
    }
    Polynomial& operator=(const Polynomial& poly) {
        if (this == &poly) return *this;
        Term* current = head->link;
        while (current != head) {
            Term* toDelete = current;
            current = current->link;
            delete toDelete;
        }
        head->link = head;
        current = poly.head->link;
        while (current != poly.head) {
            attach(current->coef, current->exp);
            current = current->link;
        }
        return *this;
    }
    Polynomial operator+(const Polynomial& b) const {
        Polynomial result;
        Term* aTerm = head->link;
        Term* bTerm = b.head->link;
        while (aTerm != head || bTerm != b.head) {
            if (aTerm != head && (bTerm == b.head || aTerm->exp > bTerm->exp)) {
                result.attach(aTerm->coef, aTerm->exp);
                aTerm = aTerm->link;
            }
            else if (bTerm != b.head && (aTerm == head || bTerm->exp > aTerm->exp)) {
                result.attach(bTerm->coef, bTerm->exp);
                bTerm = bTerm->link;
            }
            else {
                float sumCoef = aTerm->coef + bTerm->coef;
                if (sumCoef != 0) {
                    result.attach(sumCoef, aTerm->exp);
                }
                aTerm = aTerm->link;
                bTerm = bTerm->link;
            }
        }
        return result;
    }
    Polynomial operator*(const Polynomial& b) const {
        Polynomial result;
        Term* aTerm = head->link;
        while (aTerm != head) {
            Term* bTerm = b.head->link;
            while (bTerm != b.head) {
                float newCoef = aTerm->coef * bTerm->coef;
                int newExp = aTerm->exp + bTerm->exp;
                Term* current = result.head->link;
                Term* prev = result.head;
                while (current != result.head && current->exp > newExp) {
                    prev = current;
                    current = current->link;
                }
                if (current != result.head && current->exp == newExp) {
                    current->coef += newCoef;
                    if (current->coef == 0) {
                        prev->link = current->link;
                        delete current;
                    }
                }
                else {
                    Term* newNode = result.getNode(newCoef, newExp);
                    prev->link = newNode;
                    newNode->link = current;
                }
                bTerm = bTerm->link;
            }
            aTerm = aTerm->link;
        }
        return result;
    }
    float evaluate(float x) const {
        float result = 0;
        Term* current = head->link;
        while (current != head) {
            result += current->coef * pow(x, current->exp);
            current = current->link;
        }
        return result;
    }
    friend istream& operator>>(istream& is, Polynomial& poly) {
        int n;
        cout << "��J�h����������: ";
        is >> n;
        for (int i = 0; i < n; ++i) {
            float coef;
            int exp;
            cout << "��J�Y�ƩM���� (coef exp): ";
            is >> coef >> exp;
            poly.attach(coef, exp);
        }

        return is;
    }
    friend ostream& operator<<(ostream& os, const Polynomial& poly) {
        if (poly.head->link == poly.head) {
            os << "0";
            return os;
        }
        Term* current = poly.head->link;
        bool isFirstTerm = true;
        while (current != poly.head) {
            float coef = current->coef;
            int exp = current->exp;
            if (coef != 0) {
                if (!isFirstTerm && coef > 0) os << "+";
                if (exp == 0) {
                    os << coef;
                }
                else if (exp == 1) {
                    if (coef == 1) {
                        os << "x";
                    }
                    else if (coef == -1) {
                        os << "-x";
                    }
                    else {
                        os << coef << "x";
                    }
                }
                else {
                    if (coef == 1) {
                        os << "x^" << exp;
                    }
                    else if (coef == -1) {
                        os << "-x^" << exp;
                    }
                    else {
                        os << coef << "x^" << exp;
                    }
                }
                isFirstTerm = false;
            }

            current = current->link;
        }
        return os;
    }
};
int main() {
    Polynomial p1, p2;
    cout << "��J�Ĥ@�Ӧh����:" << endl;
    cin >> p1;
    cout << "��J�ĤG�Ӧh����:" << endl;
    cin >> p2;
    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    Polynomial sum = p1 + p2;
    cout << "Sum: " << sum << endl;
    Polynomial product = p1 * p2;
    cout << "Product: " << product << endl;
    float x;
    cout << "��J�N�J���� x: ";
    cin >> x;
    cout << "p1(" << x << ") = " << p1.evaluate(x) << endl;
    cout << "p2(" << x << ") = " << p2.evaluate(x) << endl;
    return 0;
}