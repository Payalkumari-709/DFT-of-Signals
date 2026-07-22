#include <iostream>
#include<bits/stdc++.h>
#include <cmath>
#include <string>
#include <stdexcept>

using namespace std;

class Complex
{
private:
    float real;
    float imag;

public:

    // Constructor
    Complex(float r = 0, float i = 0)
    {
        real = r;
        imag = i;
    }

    // Destructor
    ~Complex()
    {
    }

    // Assignment Operator
    Complex& operator=(const Complex &other)
    {
        if (this != &other)
        {
            real = other.real;
            imag = other.imag;
        }

        return *this;
    }

    // Complex Addition
    Complex operator+(const Complex &other) const
    {
        return Complex(
            real + other.real,
            imag + other.imag
        );
    }

    // Complex Multiplication
    Complex operator*(const Complex &other) const
    {
        return Complex(
            real * other.real -
            imag * other.imag,

            real * other.imag +
            imag * other.real
        );
    }

    // Magnitude
    float magnitude() const
    {
        return sqrt(real * real + imag * imag);
    }

    // Real Part
    float getReal() const
    {
        return real;
    }

    // Imaginary Part
    float getImag() const
    {
        return imag;
    }

    // Argument
    float argument() const
    {
        return atan2(imag, real) * 180.0 / M_PI;
    }

    

    //conjugate
    Complex conjugate() const{

    return Complex(real, -imag);
    }

    // Display Rectangular Form
    void display() const
    {
        if (real != 0)
            cout << real;

        if (imag > 0)
        {
            if (real != 0)
                cout << "+";

            if (imag == 1)
                cout << "i";
            else
                cout << imag << "i";
        }
        else if (imag < 0)
        {
            if (imag == -1)
                cout << "-i";
            else
                cout << imag << "i";
        }

        if (real == 0 && imag == 0)
            cout << "0";
    }

    
     //display for polar
    void displayPolar(){
        cout<<magnitude()<<"  ";
        cout<<argument()<<" deg ";

    }

    // Input Operator
    friend istream& operator>>(istream &in,Complex &c);

    // Output Operator
    friend ostream& operator<<(ostream &out,const Complex &c);
};


// Input Operator
istream& operator>>(istream &in,
                    Complex &c)
{
    string s;
    in >> s;

    c.real = 0;
    c.imag = 0;

    if (s.find('i') != string::npos)
    {
        size_t pos = string::npos;

        for (size_t i = 1; i < s.length(); i++)
        {
            if (s[i] == '+' || s[i] == '-')
            {
                pos = i;
                break;
            }
        }

        // x+yi or x-yi
        if (pos != string::npos)
        {
            c.real = stof(
                s.substr(0, pos)
            );

            string imagPart =
                s.substr(pos,
                         s.length() - pos - 1);

            c.imag = stof(imagPart);
        }

        // Pure imaginary
        else
        {
            string imagPart =
                s.substr(0,
                         s.length() - 1);

            if (imagPart == "")
                c.imag = 1;

            else if (imagPart == "-")
                c.imag = -1;

            else
                c.imag = stof(imagPart);
        }
    }

    // Pure real
    else
    {
        c.real = stof(s);
        c.imag = 0;
    }

    return in;
}


// Output Operator
ostream& operator<<(ostream &out,const Complex &c)
{
    if (c.real != 0)
        out << c.real;

    if (c.imag > 0)
    {
        if (c.real != 0)
            out << "+";

        if (c.imag == 1)
            out << "i";
        else
            out << c.imag << "i";
    }
    else if (c.imag < 0)
    {
        if (c.imag == -1)
            out << "-i";
        else
            out << c.imag << "i";
    }

    if (c.real == 0 && c.imag == 0)
        out << "0";

    return out;
}



class ComplexVector
{
private:
    int n;
    Complex *data;

public:

    // Constructor
    ComplexVector(int dimension)
    {
        if (dimension <= 0)
        {
            throw invalid_argument(
                "Vector dimension must be positive."
            );
        }

        n = dimension;

        data = new Complex[n];

        cout << "Enter "<< n << " complex numbers separated by spaces:\n";

        for (int i = 0; i < n; i++)
        {
            cin >> data[i];
        }
    }

    // Copy Constructor
    ComplexVector(const ComplexVector &other)
    {
        n = other.n;

        data = new Complex[n];

        for (int i = 0; i < n; i++)
        {
            data[i] = other.data[i];
        }
    }

    // Destructor
    ~ComplexVector()
    {
        delete[] data;
    }

    // Vector Addition
    ComplexVector operator+(const ComplexVector &other)
    {
        if (n != other.n)
        {
            throw invalid_argument(
                "Dimensions must be equal."
            );
        }

        ComplexVector result(*this);

        for (int i = 0; i < n; i++)
        {
            result.data[i] =data[i] + other.data[i];
        }

        return result;
    }

    // Complex Scalar Multiplication
    ComplexVector operator*(const Complex &scalar)
    {
        ComplexVector result(*this);

        for (int i = 0; i < n; i++)
        {
            result.data[i] =data[i] * scalar;
        }

        return result;
    }

    // Inner Product
   Complex innerProduct(const ComplexVector &other)
{
    if (n != other.n)
    {
        throw invalid_argument(
            "Dimensions must be equal."
        );
    }

    Complex sum(0,0);

    for(int i=0;i<n;i++)
    {
        sum =sum +(data[i] *other.data[i].conjugate());
    }

    return sum;
}

    // Display Vector
    void display() const
    {
        cout << "(";

        for (int i = 0; i < n; i++)
        {
            data[i].display();

            if (i < n - 1)
                cout << ", ";
        }

        cout << ")";
    }
};



int main()
{
    try
    {
        int n;

        cout << "Enter vector dimension: ";
        cin >> n;

        cout << "\nEnter Vector 1:\n";
        ComplexVector v1(n);

        cout << "\nEnter Vector 2:\n";
        ComplexVector v2(n);

        // Addition
        ComplexVector sum = v1 + v2;

        cout << "\nVector 1 = ";
        v1.display();

        cout << "\nVector 2 = ";
        v2.display();

        cout << "\nSum = ";
        sum.display();

        // Complex Scalar
        Complex scalar;

        cout << "\n\nEnter complex scalar: ";
        cin >> scalar;

        ComplexVector scaled =
            v1 * scalar;

        cout << "\nScaled Vector = ";
        scaled.display();

        // Inner Product
        Complex dot =
            v1.innerProduct(v2);

        cout << "\nInner Product = ";
        dot.display();

        cout << "\n\nComplex Scalar Information";

        cout << "\nRectangular Form = ";
        scalar.display();

        cout << "\nPolar Form = ";
        scalar.displayPolar();

        cout << "\nMagnitude = "
             << scalar.magnitude();

        cout << "\nReal Part = "
             << scalar.getReal();

        cout << "\nImaginary Part = "
             << scalar.getImag();

        cout << "\nArgument = "
             << scalar.argument()
             << " degrees\n";
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
    }

    return 0;
}