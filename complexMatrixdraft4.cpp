#include<iostream>
#include<bits/stdc++.h>

using namespace std;

class Complex
{
private:
    float real;
    float imag;

public:

    // Constructor
    Complex(float r=0,float i=0)
    {
        real = r;
        imag = i;
    }

    // Destructor
    ~Complex()
    {
    }

    // Assignment operator 
    Complex& operator=(const Complex &other)
    {
        if(this != &other)
        {
            real = other.real;
            imag = other.imag;
        }

        return *this;
    }

    // Addition
    Complex operator+(const Complex &other) const
    {
        return Complex(
            real + other.real,
            imag + other.imag
        );
    }

    // Multiplication
    Complex operator*(const Complex &other) const
    {
        return Complex(
            real * other.real -
            imag * other.imag,

            real * other.imag +
            imag * other.real
        );
    }

    // Conjugate
    Complex conjugate() const
    {
        return Complex(real,-imag);
    }

    // Display
    void display() const
    {
        if(real != 0)
            cout << real;

        if(imag > 0)
        {
            if(real != 0)
                cout << "+";

            if(imag == 1)
                cout << "i";
            else
                cout << imag << "i";
        }

        else if(imag < 0)
        {
            if(imag == -1)
                cout << "-i";
            else
                cout << imag << "i";
        }

        if(real == 0 && imag == 0)
            cout << "0";
    }

    friend istream& operator>>(istream &in,
                               Complex &c);
};



istream& operator>>(istream &in,
                    Complex &c)
{
    string s;
    in >> s;

    c.real = 0;
    c.imag = 0;

    if(s.find('i') != string::npos)
    {
        size_t pos = string::npos;

        for(size_t i=1;i<s.length();i++)
        {
            if(s[i]=='+' || s[i]=='-')
            {
                pos = i;
                break;
            }
        }

        if(pos != string::npos)
        {
            c.real =
                stof(s.substr(0,pos));

            string imagPart =
                s.substr(pos,
                         s.length()-pos-1);

            c.imag = stof(imagPart);
        }
        else
        {
            string imagPart =
                s.substr(0,
                         s.length()-1);

            if(imagPart == "")
                c.imag = 1;

            else if(imagPart == "-")
                c.imag = -1;

            else
                c.imag = stof(imagPart);
        }
    }
    else
    {
        c.real = stof(s);
        c.imag = 0;
    }

    return in;
}



class ComplexVector
{
private:
    int n;
    Complex *data;

public:

    // Constructor
    ComplexVector(int size=0)
    {
        n = size;

        if(n > 0)
            data = new Complex[n];
        else
            data = nullptr;
    }

    // Copy Constructor
    ComplexVector(
            const ComplexVector &other)
    {
        n = other.n;

        data = new Complex[n];

        for(int i=0;i<n;i++)
        {
            data[i] = other.data[i];
        }
    }

    // Assignment Operator
    ComplexVector& operator=(
            const ComplexVector &other)
    {
        if(this != &other)
        {
            delete[] data;

            n = other.n;

            data = new Complex[n];

            for(int i=0;i<n;i++)
            {
                data[i] = other.data[i];
            }
        }

        return *this;
    }

    // Destructor
    ~ComplexVector()
    {
        delete[] data;
    }

    // Input
    void input()
    {
        for(int i=0;i<n;i++)
        {
            cin >> data[i];
        }
    }

    // []
    Complex& operator[](int index)
    {
        return data[index];
    }

    const Complex& operator[](
            int index) const
    {
        return data[index];
    }

    void display() const
    {
        cout << "( ";

        for(int i=0;i<n;i++)
        {
            data[i].display();

            if(i<n-1)
                cout << " ";
        }

        cout << " )";
    }
};



class ComplexMatrix
{
private:

    int rows;
    int cols;

    ComplexVector *col;

public:

    // Constructor
    ComplexMatrix(
            int r,
            int c,
            bool takeInput=true)
    {
        if(r<=0 || c<=0)
        {
            throw invalid_argument(
                "Invalid dimensions."
            );
        }

        rows = r;
        cols = c;

        col = new ComplexVector[cols];

        for(int j=0;j<cols;j++)
        {
            col[j] =
                ComplexVector(rows);
        }

        if(takeInput)
        {
            cout << "Enter each column vector:\n";

            for(int j=0;j<cols;j++)
            {
                cout << "Column "
                     << j+1
                     << ": ";

                col[j].input();
            }
        }
    }

    // Copy Constructor
    ComplexMatrix(
            const ComplexMatrix &other)
    {
        rows = other.rows;
        cols = other.cols;

        col = new ComplexVector[cols];

        for(int j=0;j<cols;j++)
        {
            col[j] = other.col[j];
        }
    }

    // Destructor
    ~ComplexMatrix()
    {
        delete[] col;
    }

    // Addition
    ComplexMatrix operator+(
            const ComplexMatrix &other)
    {
        if(rows != other.rows ||
           cols != other.cols)
        {
            throw invalid_argument(
                "Addition impossible."
            );
        }

        ComplexMatrix result(
                rows,
                cols,
                false);

        for(int j=0;j<cols;j++)
        {
            for(int i=0;i<rows;i++)
            {
                result.col[j][i]
                    =
                    col[j][i]
                    +
                    other.col[j][i];
            }
        }

        return result;
    }

    // Scalar Multiplication
    ComplexMatrix operator*(
            const Complex &scalar)
    {
        ComplexMatrix result(
                rows,
                cols,
                false);

        for(int j=0;j<cols;j++)
        {
            for(int i=0;i<rows;i++)
            {
                result.col[j][i]
                    =
                    col[j][i]
                    *
                    scalar;
            }
        }

        return result;
    }

    // Matrix Multiplication
    ComplexMatrix operator*(
            const ComplexMatrix &other)
    {
        if(cols != other.rows)
        {
            throw invalid_argument(
                "Multiplication impossible."
            );
        }

        ComplexMatrix result(
                rows,
                other.cols,
                false);

        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<other.cols;j++)
            {
                result.col[j][i]
                    = Complex(0,0);

                for(int k=0;k<cols;k++)
                {
                    result.col[j][i]
                    =
                    result.col[j][i]
                    +
                    col[k][i]
                    *
                    other.col[j][k];
                }
            }
        }

        return result;
    }

    // Conjugate
    ComplexMatrix conjugate()
    {
        ComplexMatrix result(
                rows,
                cols,
                false);

        for(int j=0;j<cols;j++)
        {
            for(int i=0;i<rows;i++)
            {
                result.col[j][i]
                    =
                    col[j][i]
                    .conjugate();
            }
        }

        return result;
    }

    // Hermitian
    ComplexMatrix hermitian()
    {
        ComplexMatrix result(
                cols,
                rows,
                false);

        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<cols;j++)
            {
                result.col[i][j]
                    =
                    col[j][i]
                    .conjugate();
            }
        }

        return result;
    }

    // Display
    void display() const
    {
        for(int i=0;i<rows;i++)
        {
            cout << "( ";

            for(int j=0;j<cols;j++)
            {
                col[j][i].display();

                if(j < cols-1)
                    cout << "  ";
            }

            cout << " )\n";
        }
    }
};



int main()
{
    try
    {
        int r1,c1,r2,c2;

        cout << "Rows of Matrix A: ";
        cin >> r1;

        cout << "Columns of Matrix A: ";
        cin >> c1;

        cout << "\nMatrix A\n";

        ComplexMatrix A(r1,c1);

        cout << "\nRows of Matrix B: ";
        cin >> r2;

        cout << "Columns of Matrix B: ";
        cin >> c2;

        cout << "\nMatrix B\n";

        ComplexMatrix B(r2,c2);

        cout << "\nMatrix A:\n";
        A.display();

        cout << "\nMatrix B:\n";
        B.display();

        if(r1==r2 && c1==c2)
        {
            ComplexMatrix sum =
                    A + B;

            cout << "\nA + B:\n";
            sum.display();
        }
        else
        {
            cout << "\nAddition not possible.\n";
        }

        if(c1==r2)
        {
            ComplexMatrix product =
                    A * B;

            cout << "\nA * B:\n";
            product.display();
        }
        else
        {
            cout << "\nMultiplication not possible.\n";
        }

        Complex scalar;

        cout << "\nEnter complex scalar: ";
        cin >> scalar;

        ComplexMatrix scaled =
                A * scalar;

        cout << "\nScalar Multiplication:\n";
        scaled.display();

        cout << "\nConjugate of A:\n";
        A.conjugate().display();

        cout << "\nHermitian of A:\n";
        A.hermitian().display();
    }

    catch(exception &e)
    {
        cout << e.what() << endl;
    }

    return 0;
}