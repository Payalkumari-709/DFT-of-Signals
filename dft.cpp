#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class Complex{
    private:
    float real;
    float imag;

    //constructor
    public:
    Complex(float r=0,float i=0){
        real=r;
        imag=i;
    }

    //destructor
    ~Complex(){

    }

    //assignment operator overloading
    Complex operator=(const Complex &other){
        if(this != &other){
            real=other.real;
            imag=other.imag;
        }
        return *this;
    }

    //+ operator overloading
    Complex operator+(const Complex &other){
        return Complex(real+other.real ,imag+other.imag);
    }

    //operator * overloading
    Complex operator*(const Complex &other){
        return Complex( real * other.real -imag * other.imag,real * other.imag +imag * other.real);
    }

    //conjugate
    Complex conjugate(){
        return Complex(real,-imag);
    }

    //magnitude
    float magnitude(){
        return sqrt(real*real + imag*imag);
    }

    //argument
    float argument(){
        return atan2(imag,real) * 180.0 / M_PI;
    }


    //display cartesian
    void display() const
{

    const float EPS = 1e-10;

    float r = (fabs(real) < EPS) ? 0 : real;
    float im = (fabs(imag) < EPS) ? 0 : imag;

    if(r != 0)
        cout << r;

    if(im> 0)
    {
        if(r != 0)
            cout << "+";

        if(im == 1)
            cout << "i";
        else
            cout << im << "i";
    }

    else if(im < 0)
    {
        if(im == -1)
            cout << "-i";
        else
            cout << im << "i";
    }

    if(r == 0 && im == 0)
        cout << "0";
}

    // Display Polar Form
    void displayPolar()
    {
        cout << magnitude()<< "  "<< argument()<< "deg";
    }

    friend istream& operator>>(istream &in,Complex &c);
    friend ostream& operator<<(ostream &out,const Complex &c);



};

// Input Operator
istream& operator>>(istream &in,Complex &c)
{
    string s;
    in >> s;

    c.real = 0;
    c.imag = 0;

    // Contains imaginary part?

    if(s.find('i') != string::npos)
    {
        size_t pos = string::npos;

        // Search for + or - separating real and imag
        
        for(size_t i=1;i<s.length();i++)
        {
            if(s[i]=='+' || s[i]=='-')
            {
                pos = i;
                break;
            }
        }
        // Form: x+yi or x-yi
        
        if(pos != string::npos)
        {
            c.real =
                stof(s.substr(0,pos));

            string imagPart =
                s.substr(pos,
                         s.length()-pos-1);

            c.imag = stof(imagPart);
        }

        // Pure imaginary

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
    if(c.real != 0)
        out << c.real;

    if(c.imag > 0)
    {
        if(c.real != 0)
            out << "+";

        if(c.imag == 1)
            out << "i";
        else
            out << c.imag << "i";
    }

    else if(c.imag < 0)
    {
        if(c.imag == -1)
            out << "-i";
        else
            out << c.imag << "i";
    }

    if(c.real == 0 && c.imag == 0)
        out << "0";

    return out;
}

class ComplexVector{
    private:
    int n ;
    Complex *data;

    public:
    //constructor
    ComplexVector(int size =0){
        n=size;
        if(n>0)  data=new Complex[n];
        else data =nullptr;
    }
    //copy constructor
    ComplexVector(const ComplexVector &other){
        n=other.n;
        data=new Complex[n];
        for(int i=0;i<n;i++){
            data[i]=other.data[i];
        }
    }

    //assignment opertaor
    ComplexVector &operator=(const ComplexVector &other){
        
        if(this != &other){
            delete[] data;
            n = other.n;
            data = new Complex[n];

            for(int i=0;i<n;i++){
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

    //subscript operator overloading
    Complex& operator[](int index)
    {
        return data[index];
    }

    const Complex& operator[](int index) const
    {
        return data[index];
    }

    int size() const
{
    return n;
}

    //display
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

class ComplexMatrix{
    private:
        int rows;
        int cols;
        ComplexVector *col; 

    public:
    //constructor 
    
    ComplexMatrix(int r,int c,bool takeInput = true)
    {
        if(r <= 0 || c <= 0)
        {
            throw invalid_argument("Invalid matrix dimensions.");
        }

        rows = r;
        cols = c;

        col = new ComplexVector[cols];

        for(int j=0;j<cols;j++)
        {
            col[j] =ComplexVector(rows);
        }

        if(takeInput)
        {
            cout << "Enter each column vector:\n";

            for(int j=0;j<cols;j++)
            {
                cout << "Column "<< j+1<< ": ";

                col[j].input();
            }
        }
    }

        // Copy Constructor
    ComplexMatrix(const ComplexMatrix &other)
    {
        rows = other.rows;
        cols = other.cols;

        col = new ComplexVector[rows];

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
    ComplexMatrix operator+(const ComplexMatrix &other){
        if(rows != other.rows ||cols != other.cols){
            throw invalid_argument("Addition impossible.");
        }

        ComplexMatrix result(rows,cols,false);

        for(int j=0;j<cols;j++){
            for(int i=0;i<rows;i++){
                result.col[j][i]=col[j][i]+other.col[j][i];
            }
        }

        return result;
    }

    // Scalar Multiplication
    ComplexMatrix operator*(const Complex &scalar)
    {
        ComplexMatrix result(rows,cols,false);

        for(int j=0;j<cols;j++){
            for(int i=0;i<rows;i++){
                result.col[j][i]=col[j][i]*scalar;
            }
        }

        return result;
    }

    // Matrix Multiplication
    ComplexMatrix operator*(const ComplexMatrix &other) {
        if(cols != other.rows){
            throw invalid_argument("Multiplication impossible." );
        }

        ComplexMatrix result(rows,other.cols,false);

        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<other.cols;j++){result.col[j][i]= Complex(0,0);

                for(int k=0;k<cols;k++){
                    result.col[j][i]=result.col[j][i]+col[k][i]*other.col[j][k];
                }
            }
        }

        return result;
    }

    //  // Conjugate
    // ComplexMatrix conjugate()
    // {
    //     ComplexMatrix result(rows,cols,false);

    //     for(int j=0;j<cols;j++)
    //     {
    //         for(int i=0;i<rows;i++)
    //         {
    //             result.col[j][i] =col[j][i].conjugate();
    //         }
    //     }

    //     return result;
    // }

    // Matrix × Vector Multiplication
ComplexVector operator*(const ComplexVector &v)
{
    if(cols != v.size())
    {
        throw invalid_argument(
            "Matrix and vector dimensions do not match."
        );
    }

    ComplexVector result(rows);

    for(int i = 0; i < rows; i++)
    {
        result[i] = Complex(0,0);

        for(int j = 0; j < cols; j++)
        {
            result[i] =result[i]+col[j][i] * v[j];
        }
    }

    return result;
}

ComplexVector& operator[](int index)
{
    return col[index];
}

const ComplexVector& operator[](int index) const
{
    return col[index];
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

class DFT
{
public:

    static ComplexMatrix generateDFTMatrix(int N)
    {
        ComplexMatrix W(N,N,false);

        for(int k=0;k<N;k++)
        {
            for(int n=0;n<N;n++)
            {
                double theta =2.0*M_PI*k*n/N;

                W[n][k] =Complex(cos(theta),-sin(theta));
            }
        }

        return W;
    }
};

int main()
{
    try
    {
        int N;

        cout<<"Enter number of samples : ";
        cin>>N;

        ComplexVector signal(N);

        cout<<"\nEnter signal samples:\n";

        signal.input();

        cout<<"\nInput Signal:\n";

        signal.display();

        cout<<"\n\nGenerating DFT Matrix...\n";

        ComplexMatrix W =DFT::generateDFTMatrix(N);

        cout<<"\nDFT Matrix:\n";

        W.display();

        ComplexVector spectrum =W * signal;

        cout<<"\nDFT Output:\n";

        spectrum.display();

        cout<<endl;
    }

    catch(exception &e)
    {
        cout<<e.what()<<endl;
    }

    return 0;
}

