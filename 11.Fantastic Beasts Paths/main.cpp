#include<bits/stdc++.h>
using namespace std;

//class for storing island and its attributes
class Island{
    public:
    Island(){}
    Island(string id) :islandId(id){}
    
    // funtion that sets the center for each shape
    virtual void set_center(){
        return ;
    }
    // function that finds radius for each shape and sets it
    virtual void findRadius(){ return; }
    
    //setters
    void set_xc(int xc_inp) { xc = xc_inp; }
    void set_yc(int yc_inp) { yc = yc_inp; }
    void set_r(double r_inp){ r = r_inp*1.0; }

    // getters
    int get_xc() { return xc; }
    int get_yc() { return yc; }
    double get_r() {return r;}
    string getId() {return islandId;}

    private:
    
    string islandId;     // stores the island id of the island
    int xc,yc;  //co-ordinates of the center of the island
    double r; //larget distance from center of island to a point in island
    vector<Island*> connections; //vector that contains connected islands with the current island

    friend istream &operator >>(istream& stream,Island * &c);
    friend ostream &operator <<(ostream& stream,Island * c);
};

//class for shapes of rectangle
class Rectangle : public Island{
    public:
    Rectangle (int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4,string id)
    :x1(x1),y1(y1),x2(x2),y2(y2),x3(x3),y3(y3),x4(x4),y4(y4),Island(id)
    {}
    //sets the center for rectangle island
    void set_center(){
        
        set_xc((x1+x2+x3+x4)/4);
        set_yc((y1+y2+y3+y4)/4);
        return ;
    
    }
    //sets the radius for rectamgle island
    void findRadius(){ 

        int xc = get_xc();
        int yc = get_yc();
        double r = 0.0;
        //getting maximum distance among all vertices
        r = sqrt((xc-x1)*(xc-x1)+(yc-y1)*(yc-y1));
        set_r(r);
        return; 
    }
    
    private:
    int x1,y1,x2,y2,x3,y3,x4,y4;
};
// class for shape of type triangle
class Triangle :public Island{
    
    public:
    Triangle (int x1,int y1,int x2,int y2,int x3,int y3,string id)
    :x1(x1),y1(y1),x2(x2),y2(y2),x3(x3),y3(y3),Island(id)
    {}

    //sets the center for triangle island
    void set_center(){
        set_xc((x1+x2+x3)/3);
        set_yc((y1+y2+y3)/3);
        return ;
    }
    //sets the radius for triangle island
    void findRadius(){

        int xc = get_xc();
        int yc = get_yc();
        double r =0.0;
        r = max( r, sqrt((xc-x1)*(xc-x1)+(yc-y1)*(yc-y1)));
        r = max( r, sqrt((xc-x2)*(xc-x2)+(yc-y2)*(yc-y2)));
        r = max( r, sqrt((xc-x3)*(xc-x3)+(yc-y3)*(yc-y3)));
        set_r(r);
    
    }
    private:
    int x1,y1,x2,y2,x3,y3;
};
//class for the shape circle
class Circle :public Island{
    public:
    Circle (int x1,int y1,int r,string id)
    :x1(x1),y1(y1),r(r),Island(id)
    {}
    void set_center(){
        set_xc(x1);
        set_yc(y1);
        return ;
    }
    void findRadius(){

        set_r(r*1.0);
    }
    private:
    int x1,y1,r;
};

istream &operator >>(istream& cin,Island *& c){   //operator overloading to take island as input
    
    string str;
    cin>>str;

    string id;
    cin>>id;
    // cout<<str<<' '<<id<<'\n';
    if(str=="TRIANGLE"){
        // cout<<"1done"<<'\n';
        int x1,y1,x2,y2,x3,y3;
        cin>>x1>>y1>>x2>>y2>>x3>>y3;
        // cout<<"done"<<'\n';
        c = new Triangle(x1,y1,x2,y2,x3,y3,id);
        // cout<<"done"<<'\n';
    }
    else if(str=="CIRCLE"){
        int x1,y1,r;
        cin>>x1>>y1>>r;
        c = new Circle(x1,y1,r,id);
    }
    else if(str=="RECTANGLE"){
        int x1,y1,x2,y2,x3,y3,x4,y4;
        cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4;
        c=new Rectangle(x1,y1,x2,y2,x3,y3,x4,y4,id);
    }
    c->set_center();
    c->findRadius();
    return cin;

}

ostream &operator <<(ostream& stream,Island * c){
    
    stream<<c->getId();
    return stream;

}

// funtion finds if two given islands overlap or not
bool isOverlap(Island * a,Island * b){
    
    int xa = a->get_xc(), ya = a->get_yc();
    int xb = b->get_xc(), yb = b->get_yc();
    // cout<< xa<<' '<<ya<<' '<<xb<<' '<<yb<<'\n';
    double dist = sqrt((xa-xb)*(xa-xb) + (ya-yb)*(ya-yb));

    double ra = a->get_r(), rb = b->get_r();
    // cout<<ra+rb<<' '<<dist<<'\n';
    if(ra+rb >= dist) return true;
    else return false;

}

//class contains all the island in the ocean
class Group_of_islands{

    public:
    Group_of_islands(int n):n(n){
        Islands.resize(n);
        adj_list.resize(n);
    }
    void input(){   //inputs the islands
        
        for(int i= 0;i< n; i++){
            cin>>Islands[i];
            // cout<<i<<'\n';
            mp[i] = Islands[i]->getId();
        }
    }
    //adds the connections between islands
    void addEdges(){

        // cout<<n<<'\n';
        for(int i = 0;i<n;i++){
            for(int j = i+1;j<n;j++){
                // cout<<i<<' '<<j<<'\n';
                if(isOverlap(Islands[i],Islands[j])) {
                    // cout<<i<<' '<<j<<'\n';
                    adj_list[i].push_back(j);
                    adj_list[j].push_back(i);
                }
            }
        }
    }
    void check(){
    
      int mask = (1<<n) -1;
      int max_len = 0;
      int end = -1;
      int best_mask = 0;
      vector<vector<int>> dp(mask+1,vector<int>(n,0)),parent(mask+1,vector<int>(n,-1));
      for(int i = 0;i<n;i++) {
          dp[1<<i][i] = 1;
      }
      for(int i = 1; i<=mask; i++){
          for(int j = 0;j<n; j++){
              
              if(i & (1<<j)) {
                  int prev_mask = i ^ (1<<j);
                  // cout<<i<<' '<<j<<' '<<prev_mask<<'\n';
                  if(prev_mask == 0) {
                      dp[i][j] = 1;
                      parent[i][j] = -1;
                  }
                  else {
                  for( auto child: adj_list[j]){
                      if(prev_mask & (1<<child)){

                          if(dp[prev_mask][child]+1 > dp[i][j]) {
                              // cout<<i<<' '<<j<<' '<<child<<'\n';
                              dp[i][j] = dp[prev_mask][child]+1;
                              parent[prev_mask][j] = child;
                          }           
                      }
                  }
                  }
                  if(max_len <= dp[i][j]) end = j,max_len = dp[i][j],best_mask = i;
                  // cout<<max_len<<' '<<dp[i][j]<<'\n';
              }
              
          }
      }

      // cout<<max_len<<' '<<end<<' '<<best_mask<<'\n';
      // cout<<parent[6][1]<<' '<<parent[1][0]<<' '<<parent[2][0]<<'\n';
      if( max_len == n) cout<<"YES"<<'\n';
      else cout<<"NO"<<'\n'<<max_len<<'\n';
      print_path(end,best_mask,parent);
     
  }
  void print_path(int node,int mask,vector<vector<int>> & parent){
      
  vector<string> path;
  while (node != -1 and mask != 0) {
      cout <<mp[node]<<' ';
      // cout<<mask<<' '<<node<<'\n';
      mask =mask^ (1 << node);
      node = parent[mask][node];
      // cout<<mask<<' ';
      // cout<<node<<'\n';
  }
  
  
  }
    private:
    int n;
    vector<int> longest_path;
    map<int,string> mp;
    vector<vector<int>> adj_list; 
    vector<Island*> Islands; //list of all the islands in the ocean
};


int main(){

    int n;
    cin>>n;
    Group_of_islands Archipalego(n);

    Archipalego.input();
    Archipalego.addEdges();
    Archipalego.check();

}