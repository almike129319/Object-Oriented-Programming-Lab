#include<bits/stdc++.h>
using namespace std;


class Complex{      //class for Complex numbers;

    //contains Complex numbers in the form of real 
    public:
    Complex (long long int a=0,long long int b=0){  //constructor
        real=a;
        img=b;
    }
    Complex operator * (Complex b){     //operator overloading for * operation for two Complex numbers
        Complex c;
        long long int x=real*b.real-img*b.img;
        long long int y=real*b.img+img*b.real;
        return Complex(x,y);
    }
    Complex operator * (long long int b){     //operator overloading for * operation for Complex number and integer
        Complex c;
        c.real=b*real;
        c.img=b*img;
        return c;
    }
    Complex operator + (long long int b){    //operator overloading for + operation for Complex number and integer
        Complex c;
        c.real=b+real;
        c.img=img;
        return c;
    }
    Complex operator + (Complex b){     //operator overloading for + operation for Complex numbers
        Complex c;
        c.real=real+b.real;
        c.img=img+b.img;
        return c;
    }
    Complex operator - (Complex b){     //operator overloading for - operation for Complex numbers
        Complex c;
        c.real=real-b.real;
        c.img=img-b.img;
        return c;
    }
    friend ostream& operator<<(ostream& out, const Complex& c) {
            out <<c.real<<' '<<c.img;

        return out;
    }
    long long int real;     //real part of Complex number
    long long int img;      //imaginary part of Complex number
};

string operator*(const string &s,int n) {
    string result;
    for (int i=0;i<n;i++) {
        result+=s;
    }
    return result;
}


template<typename type>
class polymul;   //forward declaration

template<typename type>
class evaluation;      //forward declaration

template<typename type>
class poly_diff;        //forward declaration

template<typename type>
class polynomial{

    public:
    polynomial (){}
    polynomial (long long int deg_inp){
        deg=deg_inp;
        coef.resize(deg+1,type(0));
    }
    polynomial(vector<type> vec_inp,long long int deg_inp){   //constructor
        deg=deg_inp;
        coef=vec_inp;
    }
    polynomial<type> operator * (polynomial<type> &a){   //multiplies two polynimals
        
        polymul<type> mul;
        polynomial<type> c=mul.multiply(*this,a); 
        return c;   
    }
    
    void print(){   //prints the polynomial
        for(int i=0;i<=deg;i++){
            cout<<coef[i]<<' ';
        }
        cout<<'\n';
    }
    void print_float(){   //prints the polynomial
        for(int i=0;i<=deg;i++){
            cout <<fixed<<setprecision(6)<<coef[i]<<" ";
        }
        cout<<'\n';
    }
    
    long long int deg;  //degree of polynomail
    vector<type> coef;  //contains coef for x^(index)

    friend class polymul<type>;
    friend class evaluation<type>;
    friend class poly_diff<type>;
};
template<typename type>
polynomial<type> addpoly (polynomial<type> &a,polynomial<type> &b){   //adds two polynomials
    polynomial<type> c(max(b.deg,a.deg));
    
    for(int i=0;i<=c.deg;i++){
        if(i>a.deg){
            c.coef[i]=b.coef[i];
        }
        else if(i>b.deg){
            c.coef[i]=a.coef[i];
        }
        else{
            c.coef[i]=b.coef[i]+a.coef[i];
        }
    }
    return c;
}
template<typename type>
polynomial<type> subtract_poly(polynomial<type> &a,polynomial<type> &b){
    polynomial<type> c(max(b.deg,a.deg));
    
    for(int i=0;i<=c.deg;i++){
        if(i>a.deg){
            c.coef[i]=b.coef[i]*-1;
        }
        else if(i>b.deg){
            c.coef[i]=a.coef[i];
        }
        else{
            c.coef[i]=a.coef[i]-b.coef[i];
        }
    }
    return c;
}

template<typename type>
class polymul{   //multiplies two polynomials 
    public:
    polynomial<type> multiply(polynomial<type> &a,polynomial<type> &b){
        // function that multiplies two polynomials using divide and conquer
        
        while(a.deg>b.deg){
            b.coef.push_back(type(0));
            b.deg++;
        }
        while(b.deg>a.deg){
            a.coef.push_back(type(0));
            a.deg++;
        }
        if (a.deg==0||b.deg==0) { 
            polynomial<type>c(a.deg + b.deg);
            for (int i=0;i<=a.deg;i++) {
                for (int j=0;j<=b.deg;j++) {
                    c.coef[i+j]=c.coef[i+j]+(a.coef[i]*b.coef[j]);
                }
            }
            return c;
        }
        long long int mid=(a.deg)/2;
        polynomial<type> a0(mid),a1(a.deg-mid-1),b0(mid),b1(b.deg-mid-1);

        for(int i=0;i<=mid;i++){
            a0.coef[i]=a.coef[i];
            b0.coef[i]=b.coef[i];
        }
        for(int i=mid+1;i<=a.deg;i++){
            a1.coef[i-mid-1]=a.coef[i];
            b1.coef[i-mid-1]=b.coef[i];
        }
        
        polynomial<type> pd1=multiply(a0,b0);
        polynomial<type> pd2=multiply(a1,b1);
        polynomial<type> pd6=addpoly(a0,a1);
        polynomial<type> pd5=addpoly(b0,b1);
        polynomial<type> pd3=multiply(pd6,pd5);
        polynomial<type> pd7=subtract_poly(pd3,pd1);
        polynomial<type> pd4=subtract_poly(pd7,pd2);
        polynomial<type> result(a.deg,b.deg);

        for(int i=0;i<=result.deg;i++){
            if(i<=pd1.deg){
                result.coef[i]=result.coef[i]+pd1.coef[i];
            }
            if(i<=pd2.deg){
                result.coef[i+2*mid+2]=result.coef[i+2*mid+2]+pd2.coef[i];
            }
            if(i<=pd4.deg){
                result.coef[i+mid+1]=result.coef[i+mid+1]+pd4.coef[i];
            }
        }
        return result;
        
    } 
};

template<typename type>
class evaluation{          //evaluates the given polynomial at a given point for given type
    public:
    type eval(polynomial<type> &p , long long int val,type &ans){
        
        ans=p.coef[p.deg];
        for(int i=p.deg-1;i>=0;i--){
            ans=ans*val+p.coef[i];
        }
        return ans;
    }
};

template<>
class evaluation<string> {
public:
    string eval(polynomial<string> &p, long long int val, string &ans) {
        long long int val_pow_i=1;
        
        for (int i=0;i<=p.deg;i++) {
            ans=p.coef[i]*val_pow_i+ans;
            val_pow_i*=val;
        }
        return ans;
    }
};

template<typename type>
class poly_dif{      //differentiates the given polynomial of given type 
    public:
    polynomial<type> diff(polynomial<type> &p){
        if(p.deg==0){
            polynomial<type> differ_poly(0);
            differ_poly.coef[0]=type(0);
            return differ_poly;
        }
        polynomial<type> differ_poly(p.deg-1);
        
        for(int i=0;i<=differ_poly.deg;i++){
            differ_poly.coef[i]=p.coef[i+1]*(i+1);
        }
        return differ_poly;
    }
};

int main(){

    int number_of_queries;
    cin>>number_of_queries;

    while(number_of_queries--){
        int operation;
        cin>>operation;

        string type;
        cin>>type;  

        if(operation==1){
            
            if(type=="integer"){
                
                long long int deg;
                
                cin>>deg;
                deg--;
                vector<long long int> vec_inp(deg+1);
                for(int i=0;i<=deg;i++){
                    cin>>vec_inp[i];
                }
                polynomial<long long int> p1(vec_inp,deg);  
                
                cin>>deg;
                deg--;
                vector<long long int> vec_inp2(deg+1);
                for(int i=0;i<=deg;i++){
                    cin>>vec_inp2[i];
                }
                polynomial<long long int> p2(vec_inp2,deg);
                polynomial<long long int> p3=p1*p2;
                p3.print();
            }
            else if(type=="float"){
                long long int deg;
                
                cin>>deg;
                deg--;
                vector<long double> vec_inp(deg+1);
                for(int i=0;i<=deg;i++){
                    cin>>vec_inp[i];
                }
                polynomial<long double> p1(vec_inp,deg);  
                
                cin>>deg;
                deg--;
                vector<long double> vec_inp2(deg+1);
                for(int i=0;i<=deg;i++){
                    cin>>vec_inp2[i];
                }
                polynomial<long double> p2(vec_inp2,deg);
                polynomial<long double> p3=p1*p2;
                p3.print_float();
            }
            else if(type=="complex"){
                long long int deg;
                cin>>deg;
                deg--;
                long long int a,b;
                vector<Complex> vec_inp(deg+1);
                for(int i=0;i<=deg;i++){
                    cin>>a>>b;
                    vec_inp[i]=Complex(a,b);
                }
                polynomial<Complex> p1(vec_inp,deg);
                cin>>deg;
                deg--;
                vector<Complex> vec_inp2(deg+1);
                for(int i=0;i<=deg;i++){
                    cin>>a>>b;
                    vec_inp2[i]=Complex(a,b);
                }
                polynomial<Complex> p2(vec_inp2,deg);
                polynomial<Complex> p3=p1*p2;
                p3.print();
            }             
        }
        else if(operation==2){

            if(type=="integer"){
            
                long long int deg;
                cin>>deg;
                deg--;
                vector<long long int> vec_inp(deg+1);
                for(int i=0;i<=deg;i++){
                    cin>>vec_inp[i];
                }
                polynomial<long long int> p1(vec_inp,deg);  
                long long int val;
                cin>>val;
                evaluation<long long int> e;
                long long int ans=0;
                cout<<e.eval(p1,val,ans)<<'\n';
            }
            else if(type=="float"){
                long long int deg;
                cin>>deg;
                deg--;
                vector<long double> vec_inp(deg+1);
                for(int i=0;i<=deg;i++){
                    cin>>vec_inp[i];
                }
                polynomial<long double> p1(vec_inp,deg);  
                long long int val;
                cin>>val;
                evaluation<long double> e;
                long double ans=0.0;
                e.eval(p1,val,ans);
                cout<<fixed<<setprecision(6)<<ans<<endl;
            }
            else if(type=="string"){

                long long int deg;
                cin>>deg;
                deg--;
                string s;
                vector<string> vec_inp(deg+1);
                for(int i=0;i<=deg;i++){
                    cin>>vec_inp[i];
                }
                polynomial<string> p1(vec_inp,deg);

                long long int val;
                cin>>val;
                evaluation<string> e;
                string ans="";
                cout<<e.eval(p1,val,ans)<<'\n';
            }
        }
        else if(operation==3){
            if(type=="integer"){
                long long int deg;
                cin>>deg;
                deg--;
                vector<long long int> vec_inp(deg+1);
                for(int i=0;i<=deg;i++){
                    cin>>vec_inp[i];
                }
                polynomial<long long int> p1(vec_inp,deg);
                poly_dif<long long int> d;
                polynomial<long long int> p2=d.diff(p1);
                p2.print();
            }
            else if(type=="float"){
                
                long long int deg;
                cin>>deg;
                deg--;
                vector<long double> vec_inp(deg+1);
                for(int i=0;i<=deg;i++){
                    cin>>vec_inp[i];
                }
                polynomial<long double> p1(vec_inp,deg);
                poly_dif<long double> d;
                polynomial<long double> p2=d.diff(p1);
                p2.print_float();
            }
        }
    }
}