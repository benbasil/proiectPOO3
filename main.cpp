#include <iostream>
#define DIM 100
#include <cmath>

using namespace std;



// -------------------------- exercitiu template ------------------------------------///

// template pentru un stack
template <class T> class Stack {
public:
    Stack();
    void push(T const&);
    T pop();
    T varf() const;
    bool empty();
private:
    T arr[DIM];
    int top;
};
template <class T> Stack<T>::Stack(){
    top = -1;
}
template <class T> T Stack<T>::varf() const{
    if (top == -1)
        throw out_of_range("empty stack");
    else
        return arr[top];
}
template <class T> void Stack<T>::push(T const& elem){
    top++;
    arr[top] = elem;
}
template <class T> T Stack<T>::pop(){
    T aux;
    aux = arr[top];
    top--;
    return aux;
}
template <class T> bool Stack<T>::empty(){
    if (top > -1)
        return false;
    else
        return true;
}


// ---------------------------- END exercitiu template -----------------------------------//

// ----------------------------- Exercitiu design pattern: factory -----------------------//

class FormaGeometrica{
protected:
    string nume_forma;
public:

    FormaGeometrica(string nume_forma){
        this->nume_forma = nume_forma;
        numar_forme++;
    }
    FormaGeometrica(const FormaGeometrica& forma){
        nume_forma = forma.nume_forma;
    }
    FormaGeometrica(){
        nume_forma = "";
    }
    virtual ~FormaGeometrica(){
        nume_forma.clear();
        numar_forme--;
    }

    virtual double arie() = 0;
    virtual double perimetru() = 0;

    virtual void afisare() {
        cout << nume_forma << ' ';
    }

    int static getNumar_Forme(){
        return numar_forme;
    }

private:
    int static numar_forme;

};

class Dreptunghi:public FormaGeometrica{

public:
    double arie (){
        return l * L;
    }
    double perimetru (){
        return 2*(L + l);
    }
    Dreptunghi(double l = 0, double L = 0):FormaGeometrica("Dreptunghi"){
        this->l = l;
        this->L = L;
    }
    ~Dreptunghi(){
        l = 0;
        L = 0;
    }

    virtual void afisare() {
        FormaGeometrica::afisare();
        cout << l << ' ' << L << "; perimetru = " << perimetru() << "; arie = " << arie() << endl;
    }

private:
    double l, L;
};

class Triunghi:public FormaGeometrica{
public:
    double arie (){
        double semiperimetru = latura1 + latura2 + latura3;
        semiperimetru /= 2;
        return sqrt(semiperimetru*(semiperimetru - latura1)*(semiperimetru - latura2)*(semiperimetru - latura3)); //Calculul ariei triunghiului prin formula lui Heron;
    }
    double perimetru(){
        return latura1 + latura2 + latura3;
    }
    Triunghi(double latura1 = 0, double latura2 = 0, double latura3 = 0):FormaGeometrica("Triunghi"){
        this->latura1 = latura1;
        this->latura2 = latura2;
        this->latura3 = latura3;
    }

    ~Triunghi(){
        latura1 = 0;
        latura2 = 0;
        latura3 = 0;
    }
    virtual void afisare() {
        FormaGeometrica::afisare();
        cout << latura1 << ' ' << latura2 << ' ' << latura3 << "; perimetru = " <<perimetru() << "; arie = " <<arie() << endl;
    }
private:
    double latura1, latura2, latura3;
};

class FabricaForma {
public:
    virtual FormaGeometrica* creareForma(double x=0, double y=0, double z=0) = 0;
};

class FabricaDreptunghi : public FabricaForma {
public:
    FormaGeometrica* creareForma (double x=0, double y=0, double z=0) override {
        return new Dreptunghi(x, y);
    }
};

class FabricaTriunghi : public FabricaForma{
public:
    FormaGeometrica* creareForma (double x=0, double y=0, double z=0)override {
        return new Triunghi(x,y,z);
    }
};

FabricaForma* client(string forma){
    if (forma == "Dreptunghi")
        return new FabricaDreptunghi();
    else
        return new FabricaTriunghi();
}


int FormaGeometrica::numar_forme = 0;
//---------------------------------- END factory --------------------------------------//

int main()
{
    // -------------------- verificari exercitiu template ------------------//

    cout << "// -------------------- verificari exercitiu template ------------------//" << endl << endl;


    Stack<int> integers;
    Stack<string> strings;
    //cout << integers.varf();
    integers.push(1);
    integers.push(2);
    integers.push(3);
    integers.push(4);

    cout << integers.pop() <<endl;
    cout << integers.varf() <<endl;

    strings.push("aba");
    strings.push("abababa");
    strings.push("chacha");
    strings.push("chachacha");

    cout << strings.pop() <<endl;
    cout << strings.pop() <<endl;
    cout << strings.varf() <<endl;

    cout << "-------------------- END verificari exercitiu template ------------------" << endl << endl;

    // -------------------- END verificari exercitiu template ------------------//



    // -------------------- verificari design pattern: fabrica -----------------//
    // am implementat o fabrica de forme: dreptunghiuri sau triunghiuri;
    cout << "-------------------- verificari design pattern: fabrica -----------------" << endl << endl;


    FabricaForma* fabricadreptunghi = client("Dreptunghi");
    FabricaForma* fabricatriunghi = client("Triunghi");

    FormaGeometrica* forma1 = fabricadreptunghi -> creareForma(10, 20);
    FormaGeometrica* forma2 = fabricadreptunghi -> creareForma(40, 60);

    FormaGeometrica* forma3 = fabricatriunghi -> creareForma(60, 20, 50);
    FormaGeometrica* forma4 = fabricatriunghi -> creareForma(40, 60, 50);

    forma1->afisare();
    forma2->afisare();
    forma3->afisare();
    forma4->afisare();

    cout << "-------------------- END verificari design pattern: fabrica -----------------" << endl << endl;

  // -------------------- END  verificari design pattern: fabrica -----------------//
    return 0;
}
