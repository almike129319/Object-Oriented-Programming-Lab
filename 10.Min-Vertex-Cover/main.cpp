#include<bits/stdc++.h>
using namespace std;

class sentinel{        //base class for sentinel contains their attributes and their functions

    public:

    sentinel(int id_inp, string name_inp, string rank_inp) 
        :id(id_inp),name(name_inp),rank(rank_inp){}
    virtual int count_high_ranked(vector<int> vec){
        return 0;
    }
    string get_rank() {
        return rank;
    }
    int get_id(){
        return id;
    }
    private:
    int id;
    string name;
    string rank;
};

class senapati :public sentinel {       //class contains functions of senapati    
    public:
    senapati (int id , string name) :sentinel(id,name,"senapati"){}
    int count_high_ranked(vector<int> vec){
        return 0;
    }
};

class dandanayaka :public sentinel {    //class contains the functions of dandanayaka
    public:
    dandanayaka(int id , string name) :sentinel(id,name,"dandanayaka"){}
    int count_high_ranked(vector<int> vec){
        // cout<<88<<'\n';
        return vec[0];
    }
};
class chaturangini :public sentinel {   //class contains the functions of sentinel
    public:
    chaturangini (int id , string name) :sentinel(id,name,"chaturangini"){}
    int count_high_ranked(vector<int> vec){
        // cout<<44<<'\n';
        return vec[0]+vec[1];
    }
};

class comp{             //funtor for comparing two sentinel pointers based on their rank and id
    public:
    bool operator () (sentinel * a,sentinel * b){
            if(a->get_rank() == "senapati"){
                if(b->get_rank() == "senapati"){
                    return a->get_id() < b->get_id();
                }
                else return true;
            }
            else if (a->get_rank() == "dandanayaka"){
                if(b->get_rank() == "senapati") return false;
                else if(b->get_rank() == "chaturangini") return true;
                else {
                    return a->get_id() < b->get_id();
                }
            }
            else if (a->get_rank() == "chaturangini"){
                if(b->get_rank() == "chaturangini") {
                    return a->get_id() < b->get_id();
                }
                else return false;
            }
            return true;
    }
};

template<typename type>
class kingdom{              //class that contains attributes and funtions of the kingdom

    public:

    kingdom(int n){
        no_of_sentinels = n;
        sentinels.resize(n);
        sentinels_unsorted.resize(n);
        adj_list.resize(n);
        count_of_each_rank.resize(3);
        count_of_each_rank[0] = count_of_each_rank[1] =count_of_each_rank[2] =0;
        vis.resize(no_of_sentinels);
        fill(vis.begin(), vis.end(), 0);
        active_men = 0;
    }

    void input_adj_list(){      //takes the edges 
        
        for(int i=0;i<no_of_sentinels-1;i++){
            int a,b;
            cin>>a>>b;
            // cout<<no_of_sentinels<<' '<<a<<' '<<b<<'\n';
            adj_list[a].push_back(b);
            adj_list[b].push_back(a);
        }
    }
    void type1(){       //outputs number of active sentinels req to monitor all roads
        dfs(0);
    }
    int get_active_men(){
        return active_men;
    }
    int dfs(int i){      //dfs using dp for finding min vertes cover
        
        int child_sum=0;
        int children = 0;
        vis[i] =1;
        for(auto child:adj_list[i]){
            if(vis[child] == 0) {
                child_sum += dfs(child);
                children++;
            }
        }
        int value = 0;
        if(children > child_sum){
            active_men++;
            value =1;
        }
        // cout<<i<<' '<<value<<'\n';
        return value;

    }
    void input_sentinels(){     //inputs the sentinels
        
        for(int i=0;i<no_of_sentinels;i++){
            string name,rank;
            cin>>name>>rank;
            if(rank == "SENAPATI"){
                // cout<<"senapati\n";
                sentinels[i] = new senapati(i,name);
                sentinels_unsorted[i] = new senapati(i,name);
                count_of_each_rank[0]++;
            }
            else if(rank == "DANDANAYAKA"){
                // cout<<i<<' '<<"dandanayaka\n";
                sentinels[i] = new dandanayaka(i,name);
                sentinels_unsorted[i] = new dandanayaka(i,name);
                count_of_each_rank[1]++;
            }
            else {
                // cout<<"chaturangini"<<' '<<i<<'\n';
                sentinels[i] = new chaturangini(i,name);
                sentinels_unsorted[i] = new chaturangini(i,name);
                count_of_each_rank[2] ++;
            }
        }
    }
    void type2(){       //sorts the sentinels according to their ranks using comp funtor
        
        sort (sentinels.begin(), sentinels.end(), comp());
        
    }
    void print_sentinels(){
        for(auto s : sentinels){
            cout<<s->get_id()<<' ';
        }
        cout<<'\n';
    }
    int type3( int i ){    //returns the number of higher ranked sentinels present than the sentinel at index i
        // cout<<count_of_each_rank[0]<<' '<<count_of_each_rank[1]<<' '<<count_of_each_rank[2]<<' '<<i<<'\n';
        return sentinels_unsorted[i]->count_high_ranked(count_of_each_rank);
    }

    private:
    int no_of_sentinels;        //contains no.of sentinels
    vector<int> count_of_each_rank;     //cotains the no.of people in rank 
    vector<sentinel *> sentinels;   // contans the list of the sentinels and their ids
    vector<sentinel *> sentinels_unsorted; //contains the sorted list of sentinels
    vector<vector<type>> adj_list ; //contains the edtges of the graph
    vector<int> vis;
    int active_men;
};
int main(){

    int no_of_sentinels;
    cin>>no_of_sentinels;

    kingdom<int> empire(no_of_sentinels);
    
    empire.input_adj_list();
    empire.input_sentinels();

    int queries;
    cin>>queries;

    empire.type1();
    empire.type2();
    for(int i = 0;i<queries;i++){
        int type;
        cin>>type;
        if(type == 1){
            cout<<empire.get_active_men()<<'\n';
        }
        else if(type == 2){
            empire.print_sentinels();
        }
        else{
            int ind;
            cin>>ind;
            cout<<empire.type3(ind)<<'\n';
        }
    }
}