#include<iostream>
#include<stdexcept>
#include<bits/stdc++.h>

using namespace std;

class nTuple{
    private:
    int n; //n will be the dimension
    float *data;//declaration of starting address of vector data
    
    public:
    //constructor (parameterized)
    nTuple(int dimension){
        if(dimension <= 0){
            throw invalid_argument("Error : Vector dimension must be greater than 0.");
        }

        n= dimension;
        data=new float[n];

        //taking input of the vector from the user
        cout<<"Enter "<<n<<" elements of the vector: ";

        for(int i=0;i<n;i++){
            cin>>data[i];
        }
    }

    //copy constructor
    nTuple(const nTuple &other){
        n=other.n;
        data=new float[n];

        for(int i=0;i<n;i++){
            data[i]=other.data[i];
        }
    }

    //destructor
    ~nTuple(){
        delete[] data;
        
    }

    //operator + overload
    nTuple operator+(const nTuple &other){
        if(n != other.n){
            throw invalid_argument("Error: dimensions of both vectors must be equal for addition");
        }

        nTuple result(*this);//result initially points to v1//calling through copy constructor
        for(int i=0;i<n;i++){
            result.data[i]=data[i]+other.data[i];
        }
        return result;
    }

    //operater * float scaler multiplication overloading
    nTuple operator*(float scaler){
        nTuple result(*this);
        for(int i=0;i<n;i++){
            result.data[i]=scaler * data[i];
        }
        return result;
    }

    //inner product
    float innerProduct(const nTuple &other){
        if(n!=other.n){
             throw invalid_argument("Error: dimensions of both vectors must be equal for dot product");


        }

        float result=0.0;
        for(int i=0;i<n;i++){
            result=result+(data[i]*other.data[i]);
        }
        return result;
    }

    void display(){
        cout <<"(";
        for(int i=0;i<n;i++){
            cout<<data[i];
            if(i<n-1) cout<<",";
        }
        cout<<")";
    }



};

int main(){
    //object 
    try{
        int n;
        cout<<"enter the dimension of vector: ";
        cin>>n;

        cout<<"\nenter vector 1 :\n";
        nTuple v1(n);

        cout<<"\nenter vector 2 :\n";
        nTuple v2(n);

        //addition 
        nTuple sum =v1+v2;
        
        cout<<"\n vector 1= ";
        v1.display();
        cout<<"\n vector 2= ";
        v2.display();
        cout<<"\n sum= ";
        sum.display();

       // Scalar Multiplication
        float scalar;

        cout << "\n\nEnter scalar value: ";
        cin >> scalar;

        nTuple scaled =v1*scalar ;
        cout<<"\n v1 *  "<<scalar<<" = ";
        scaled.display();

        //inner product
        float dotp=v1.innerProduct(v2);
        cout << "\n\nInner Product (v1 . v2) = "
             << dotp << endl;



    }
    catch(const exception &e){
        cout<<e.what()<<endl;
    }
    return 0;
}
