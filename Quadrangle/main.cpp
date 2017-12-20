#include <bits/stdc++.h>
#include "mylist.h"

using namespace std;

class Quadrangle {

protected:
    double dim1;
    double dim2;
    string name;
public:

    virtual double area() = 0;

    Quadrangle() {
        this->name = "quadrangle";
        dim1 = dim2 = 0;
    }

    Quadrangle(double _dim1, double _dim2) : dim1(_dim1), dim2(_dim2) {
        this->name = "quadrangle";
    }

    virtual void draw() {
        cout << "Waring!" << endl;
    };

    virtual string what() {
        return name;
    }

    virtual ~Quadrangle() = default;
};


class Parallelogram : public Quadrangle {
public:
    virtual double Width() {
        return dim1;
    }

    virtual double Height() {
        return dim2;
    }

    Parallelogram() {
        name = "Parallelogram";
    }

    Parallelogram(double _dim1, double _dim2) : Quadrangle(_dim1, _dim2) {
        name = "Parallelogram";
    }

    double area() override {
        return Width() * Height();
    }

    void draw() override {
        cout << "\
   ************\n\
  ************\n\
 ************\n\
************" << endl;
        cout << "Width:" << Width() << "\nHeight:" << Height() << endl;
    }

    string what() override {
        return name;
    }

    ~Parallelogram() override = default;
};

class Rect : virtual public Parallelogram {
public:
    Rect() {
        name = "Rectangle";
    }

    Rect(double _dim1, double _dim2) : Parallelogram(_dim1, _dim2) {
        name = "Rectangle";
    }

    void draw() override {
        cout << "\
************\n\
************\n\
************\n\
************" << endl;
        cout << "Width:" << dim1 << "\nHeight:" << dim2 << endl;
    }

    string what() override {
        return name;
    }

    ~Rect() override = default;
};

class Diamond : virtual public Parallelogram {
public:
    Diamond() {
        name = "Diamond";
    }

    Diamond(double _dim1, double _dim2) : Parallelogram(_dim1, _dim2) {
        name = "Diamond";
    }

    double area() override {
        return Width() * Height() / 2.0;
    }

    void draw() override {
        cout << "     *\n\
    ***\n\
   *****\n\
  *******\n\
 *********\n\
***********\n\
 *********\n\
  *******\n\
   *****\n\
    ***\n\
     *" << endl;
        cout << "Width:" << dim1 << "\nHeight:" << dim2 << endl;
    }

    string what() override {
        return name;
    }

    ~Diamond() override = default;
};

class Square : public Rect, public Diamond {
public:
    Square() {
        name = "Square";
    }

    explicit Square(double _dim1) {
        name = "Square";
        dim1 = dim2 = _dim1;
    }

    double Width() final {
        return dim1;
    }

    double Height() final {
        return dim1;
    }

    double area() final {
        return Width() * Width();
    }

    void draw() final {
        cout << "****\n\
****\n\
****\n\
****" << endl;
        cout << "Width:" << dim1 << "\nHeight:" << dim2 << endl;
    }

    string what() override {
        return name;
    }

    ~Square() final = default;
};

class Trapezoid : public Quadrangle {
    double dim3;
public:
    Trapezoid() {
        name = "Trapezoid";
        dim3 = 0;
    }

    double Width() {
        return dim1;
    }

    double Height() {
        return dim2;
    }

    double Width2() {
        return dim3;
    }

    double area() override {
        return (Width2() + Width()) / 2.0 * Height();
    }

    Trapezoid(double _dim1, double _dim2, double _dim3) : Quadrangle(_dim1, _dim2), dim3(_dim3) {
        name = "Trapezoid";
    }

    void draw() final {
        cout << "    ****\n\
   ******\n\
  ********\n\
 **********\n\
************" << endl;
        cout << "Width:" << dim1 << "\nWidth2:" << dim3 << "\nHeight:" << dim3 << endl;
    }

    string what() override {
        return name;
    }

    ~Trapezoid() final = default;
};

void guess_area(double _ans) {
//    return;
    while (true) {
        cout << "Please input area" << endl;
        double ans;
        cin >> ans;
        if (fabs(ans - _ans) < 0.1) {
            cout << "Yes!" << endl << endl;
            return;
        } else {
            cout << "No ! TRY again ..." << endl;
        }
    }
}

int main() {

    Rect r1;
    Square r2;
    Parallelogram r3;
    Trapezoid r4;
    Diamond r5;

    int a[5];
    int cnt(0);
    mylist<Quadrangle *> l;
    memset(a, 0, sizeof a);
    random_device rd;
    while (cnt < 5) {
        int now = rd() % 5;
        now = rd() % 5;
        if (a[now]) continue;
        cnt++;
        a[now] = 1;
        if (now == 0) {
            int dim1 = rd() % 10 + 1;
            int dim2 = rd() % 10 + 1;
            while (dim2 == dim1) dim2 = rd() % 10 + 1;
            r1 = *(new Rect(dim1, dim2));
            r1.draw();
            guess_area(r1.area());
            l.push_back(&r1);
        } else if (now == 1) {
            int dim1 = rd() % 10 + 1;
            r2 = *(new Square(dim1));
            r2.draw();
            guess_area(r2.area());
            l.push_back(&r2);
        } else if (now == 2) {
            int dim1 = rd() % 10 + 1;
            int dim2 = rd() % 10 + 1;
            while (dim2 == dim1) dim2 = rd() % 10 + 1;
            r3 = *(new Parallelogram(dim1, dim2));
            r3.draw();
            guess_area(r3.area());
            l.push_back(&r3);
        } else if (now == 3) {
            int dim1 = rd() % 10 + 1;
            int dim2 = rd() % 10 + 1;
            while (dim2 == dim1) dim2 = rd() % 10 + 1;
            int dim3 = rd() % 10 + 1;
            r4 = *(new Trapezoid(dim1, dim2, dim3));
            r4.draw();
            guess_area(r4.area());
            l.push_back(&r4);
        } else if (now == 4) {
            int dim1 = rd() % 10 + 1;
            int dim2 = rd() % 10 + 1;
            r5 = *(new Diamond(dim1, dim2));
            r5.draw();
            guess_area(r5.area());
            l.push_back(&r5);
        }
    }

    cout << endl << "-------------------------" << endl;
    cout << "Review:" << endl;
    auto f = [](Quadrangle *q) {
        cout << endl << q->what() << ":" << endl;
        q->draw();
    };
    l.traverse(f);


    /* //test for list iterator :)
     *
     * cout << endl << "-------------------------" << endl;
    cout << endl << "-------------------------" << endl;
    for (auto it=l.begin();it!=l.end();it++)
        (*it)->draw();

        */

}
