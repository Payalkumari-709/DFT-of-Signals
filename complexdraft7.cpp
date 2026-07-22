#include <iostream>
#include <cmath>
#include <string>
#include<bits/stdc++.h>

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

    // Addition
    Complex operator+(const Complex &other)
    {
        return Complex(
            real + other.real,
            imag + other.imag
        );
    }

    // Complex Multiplication
    Complex operator*(const Complex &other)
    {
        return Complex(
            real * other.real - imag * other.imag,
            real * other.imag + imag * other.real
        );
    }

    // Input Operator
    friend istream& operator>>(istream &in, Complex &c);

    // Output Operator
    friend ostream& operator<<(ostream &out, const Complex &c);

    //display cartesian

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

    // Display Polar Form
    // void displayPolar() const
    // {
    //     float r = sqrt(real * real + imag * imag);

    //     float theta =
    //         atan2(imag, real) * 180.0 / M_PI;

    //     cout << r << " ∠ " << theta << "°";
    // }



    float magnitude() const
{
    return sqrt(real * real + imag * imag);
}

float getReal() const
{
    return real;
}

float getImag() const
{
    return imag;
}

float argument() const
{
    return atan2(imag, real) * 180.0 / M_PI;
}

Complex& operator=(const Complex &other)
{
    if(this != &other)
    {
        real = other.real;
        imag = other.imag;
    }

    return *this;
}

Complex conjugate() const
{
    return Complex(real, -imag);
}

void displayPolar() const
{
    cout << magnitude()
         << " ∠ "
         << argument()
         << "°";
}
};


// Input Operator Overloading
istream& operator>>(istream &in, Complex &c)
{
    string s;
    in >> s;

    c.real = 0;
    c.imag = 0;

    // Contains imaginary part?
    if (s.find('i') != string::npos)
    {
        size_t pos = string::npos;

        // Search for + or - separating real and imag
        for (size_t i = 1; i < s.length(); i++)
        {
            if (s[i] == '+' || s[i] == '-')
            {
                pos = i;
                break;
            }
        }

        // Form: x+yi or x-yi
        if (pos != string::npos)
        {
            c.real = stof(s.substr(0, pos));

            string imagPart =
                s.substr(pos, s.length() - pos - 1);

            c.imag = stof(imagPart);
        }

        // Pure imaginary
        else
        {
            string imagPart =
                s.substr(0, s.length() - 1);

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


// Output Operator Overloading
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


int main()
{
    Complex c1, c2;

    cout << "Enter first complex number: ";
    cin >> c1;

    cout << "Enter second complex number: ";
    cin >> c2;

    Complex sum = c1 + c2;
    Complex product = c1 * c2;

    cout << "\nFirst Complex Number = "
         << c1;

    cout << "\nPolar Form = ";
    c1.displayPolar();

    cout << "\n\nSecond Complex Number = "
         << c2;

    cout << "\nPolar Form = ";
    c2.displayPolar();

    cout << "\n\nSum = " << sum;

    cout << "\nPolar Form of Sum = ";
    sum.displayPolar();

    cout << "\n\nProduct = "
         << product;

    cout << "\nPolar Form of Product = ";
    product.displayPolar();

    cout << endl;

    cout << "\nMagnitude = "
     << c1.magnitude();

cout << "\nReal Part = "
     << c1.getReal();

cout << "\nImaginary Part = "
     << c1.getImag();

cout << "\nArgument = "
     << c1.argument()
     << " degrees";

     Complex conj = c1.conjugate();

cout << "\nConjugate = ";
conj.display();

    return 0;
}