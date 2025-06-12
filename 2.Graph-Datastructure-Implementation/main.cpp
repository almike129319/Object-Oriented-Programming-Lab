#include<bits/stdc++.h>
using namespace std;

class Graph{
    public:
    
    void operator +(Graph &g2){                                            //union
        
        int n2=max(edge_list.size(),g2.edge_list.size());
        edge_list.resize(n2);
        for(int i=0;i<n2;i++){
            for(int j=i+1;j<n2;j++){
                if(!is_edge(i,j)&&g2.is_edge(i,j)) add_edge(i,j);
            }
        }
    }
    void operator -(Graph &g2){                                            //intersection

        int n2=edge_list.size();
        for(int i=0;i<n2;i++){
            for(int j=i+1;j<n2;j++){

                if(is_edge(i,j)&&!g2.is_edge(i,j)) remove_edge(i,j); 
        
            }
        }
    }

    void operator !(){                                                     //complement

        int n=edge_list.size();
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(!is_edge(i,j)) add_edge(i,j);
                else remove_edge(i,j);
            }
        }

    }

    bool is_reachable(int a,int b){                                         //is_reachble
         
         if (a>=(int)edge_list.size()||b>=(int)edge_list.size()) return false;
        queue<int> q;
        vector<bool> visited(edge_list.size(), false);
        q.push(a);
        visited[a] = true;
        while(!q.empty()){
            int parent=q.front();
            q.pop();
            if(parent==b) return true;
            for(int child:edge_list[parent]){
                if (!visited[child]) {
                    visited[child]=true;
                    q.push(child);
                }
            }
        }
        return false;
    }

    void add_edge(int n1,int n2){  
                                                //add_edge
        if(is_edge(n1,n2)) return;
        edge_list[n1].push_back(n2);
        edge_list[n2].push_back(n1);
    }

    void remove_edge(int i,int j){                                        //remove_edge

        if(!is_edge(i,j)) return;
        edge_list[i].erase(find(edge_list[i].begin(),edge_list[i].end(),j));
        edge_list[j].erase(find(edge_list[j].begin(),edge_list[j].end(),i));
    }
    bool is_edge(int n1,int n2){                                           //checks if there is edge b/w i,j
      
        if(n1>=(int)edge_list.size()||n2>=(int)edge_list.size()) return false;
        return find(edge_list[n1].begin(), edge_list[n1].end(), n2)!=edge_list[n1].end();
    }
    void order(){   
                                                               //sorts each element of vector
      for(int i=0;i<(int)edge_list.size();i++){
        sort(edge_list[i].begin(),edge_list[i].end());
      }
    }
    private:
    vector<vector<int>> edge_list;

    friend ostream &operator <<(ostream& stream,const Graph & g);
    friend istream &operator >>(istream& stream,Graph & g);

};
ostream &operator <<(ostream& stream,const Graph & g){                   //output

    int n=g.edge_list.size();
    for(int i=0;i<n;i++){
        stream << "Vertex "<<i<<": ";
        for(int j:g.edge_list[i]){
            stream<<j<<' ';
        }
        stream<<'\n';
    }
    return stream;

}
istream &operator >>(istream& stream,Graph & g){                        //input
    int n,m;
    stream>>n>>m;
    g.edge_list.resize(n);
    
    int u,v;
    for(int i=0;i<m;i++){
        stream>>u>>v;
        g.add_edge(u,v);    
    }
    return stream;
}

int main(){
    
    string str;
    cin>>str;
    Graph g;
    
    while(str!="end"){
        if(str=="Graph") cin>>g;
        else if(str=="printGraph") {g.order(); cout<<g;}
        else if(str=="union"){ string s; cin>>s; Graph g2;cin>>g2; g+g2; }
        else if(str=="intersection") {string s; cin>>s; Graph g2;cin>>g2; g-g2;}
        else if(str=="complement") !g;
        else if(str=="remove_edge") {int i,j; cin>>i>>j; g.remove_edge(i,j); }
        else if(str=="add_edge") {int i,j; cin>>i>>j; g.add_edge(i,j);}
        else if(str=="isReachable") {
            int a,b;
            cin>>a>>b;
            if(g.is_reachable(a,b)) cout<<"Yes"<<'\n';
            else cout<<"No"<<'\n';
        }
        cin>>str;
    }
}