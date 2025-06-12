#include<bits/stdc++.h>
using namespace std;
#define int long long

class card{         //calss for representing the cards of different types
    public:

    virtual int area(){     //virtual function for getting the area of the given card
       return 0;
    }
    virtual void print(){   //for printing the card

    }
    virtual string type(){  //for getting the type of the card
        return "";
    }
    virtual bool operator >= (card * c){    
    
        return this->area()>= c->area();
    
    }
     bool operator < (card * c){
    
        return this->area() < c->area();
    
    }
    
    private:
    friend istream &operator >>(istream& stream,card * &c);
    friend ostream &operator <<(ostream& stream,card * &c);

    
};
class triangle:public card {     //class for representing the triangle cards
    public:
    triangle (int base,int height) :b(base),h(height) {}
    int area(){
        return b*h/2;
    }
    virtual string type(){
        return "TRIANGLE";
    }
    void print(){
        cout<<"TRIANGLE"<<' '<<b<<' '<<h;
    }
    private:
    int b;  //base
    int h;  //height
};
class square: public card{      //class for representing the square cards
    public:
    square (int side) :a(side) {}
    int area(){
        return a*a;
    }
    string type(){
        return "SQUARE";
    }
    void print(){
        cout<<"SQUARE"<<' '<<a;
    }
    private:
    int a;  //side value of the square
};
class rectangle :public card {      //class for representing the rectangle cards
    public:
    rectangle (int l,int b) :l(l),b(b) {}
    int area(){
        return l*b;
    }
    string type(){
        return "RECTANGLE";
    }
    void print(){
        cout<<"RECTANGLE"<<' '<<l<<' '<<b;
    }
    int l;  //length of rectangle
    int b;  //breadth
    string shape;
};
istream &operator >>(istream& cin,card * &c){   //operator overloading to take card as input
    string str;
    cin>>str;
    if(str=="TRIANGLE"){
        int b,h;
        cin>>b>>h;
        c=new triangle(b,h);
    }
    else if(str=="SQUARE"){
        int a;
        cin>>a;
        c=new square(a);
    }
    else if(str=="RECTANGLE"){
        int l,b;
        cin>>l>>b;
        c=new rectangle(l,b);
    }
    return cin;
}
ostream &operator <<(ostream& stream,card * &c){ //operator overloading for printing the card
    c->print();
    return stream;
}
class card_organiser{   //class for organising and computing LIS of cards
    public: 
    int lower (card* target) {
      int left=0;
      int right=piles.size();  // Exclusive
  
      while(left<right){
          int mid=(right+left)/2;
  
          if(piles[mid]->area()<target->area()){
              left=mid + 1;
          }
          else{
              right=mid;
          }
      }
  
      return left;  // First index where area >= target->area()
  }
  
    void addCard(card* c){  //adds class to the pile
       index[c]=j++;
        if(piles.size()==0) {
            //cout<<c->area()<<' '<<1<<'\n';
            piles.push_back(c);
            dp.push_back({c});
            return;
        }
        else {
           int i = lower(c);
            if(i==piles.size()) {
                
                piles.push_back(c);
                int n=piles.size();
                //int n1=LIS.size();
                //cout<<n<<' '<<n1<<'\n';
                //cout<<c->area()<<' '<<2<<'\n';
                dp.push_back({c});
            }
            else {
                piles[i]=c;
                dp[i].push_back(c);
                //cout<<c->area()<<' '<<3<<'\n';
            }
        }
        
        
        return ;
    
    }
    int get_pileCount() {   //returns the size of the pile
    //   for(auto d:dp){
    //     for(auto c: d) cout<<c<<' '<<index[c]<<'\n';
    // }  
      return piles.size();
    }
    void get_LIS() {  //gives the longest subsequence possible till now
      
      int n= dp.size();
      vector<card *> LIS;     //has the LIS till now
      LIS.push_back(dp[n-1][0]);
      card * cur = dp[n-1][0];

      for(int i=n-2;i>=0;i--){
        for(auto c: dp[i]){
          if(c->area()<cur->area() and index[c]<index[cur]){
            cur = c;
            LIS.push_back(c);
            break;
          }
        }
      }
      reverse(LIS.begin(),LIS.end());
      
        cout<<this->get_pileCount()<<'\n';
        for(auto c: LIS) cout<<c<<'\n';
    }
    private:
    int j=0;
    vector<vector<card *>> dp;
    map<card*,int> index;
    vector<card *> piles;   //represents the current piles
    

};
int32_t main(){

    int queries;
    cin>>queries;
    
    vector<card*> cards;
    card * c;
    
    int type_of_query;
    card_organiser gamble;

    for (int i=0;i<queries;i++){
        
        cin>>type_of_query;
        if(type_of_query==1){
            cin>>c;
            gamble.addCard(c);        
        }
        else if(type_of_query==2){
            cout<<gamble.get_pileCount()<<'\n';
        }
        else{
           gamble.get_LIS();
        }
    }
}