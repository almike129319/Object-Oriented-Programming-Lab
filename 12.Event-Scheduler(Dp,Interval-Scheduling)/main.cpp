#include<bits/stdc++.h>
using namespace std;
#define double long double
#define int long long
class Event{
    public:

    Event(){}
    Event(int s,int e){
        start = s;
        end = e;
    }
    virtual double calculateProfit(){
        return 0.0;
    }
    int get_start(){ return start;}
    int get_end() {return end;}
    private:
    int start;
    int end;

    friend istream &operator >>(istream& cin,Event* &event);
};

class Concert :public Event{
    public:
    Concert(){}
    Concert(int s,int e,int price,int sold,int artist_fee_inp,int logistic_inp )
    :Event(s,e)
    {
        start = s;
        end = end;
        ticket_price = price;
        ticket_sold = sold;
        artist_fee = artist_fee_inp;
        logistic = logistic_inp;
    }
    double calculateProfit(){

        double ticket_revenue = 1.0*ticket_price * ticket_sold;
        ticket_revenue = ticket_revenue - ((0.18)*ticket_revenue);

        int cost = artist_fee + logistic;

        double net_profit = ticket_revenue - (double)cost;
        if(net_profit > (2.0*(double)cost)) {
            net_profit = 0.7*net_profit;
        }

        return net_profit;
    }
    private:
    int start;
    int end;
    int ticket_price;
    int ticket_sold;
    int artist_fee;
    int logistic;
};

class TheaterShow :public Event{
    public:
    TheaterShow(){}
    TheaterShow(int s,int e,int base_price_inp,int seats_inp,int venue_cost_inp )
    :Event(s,e)
    {
        start = s;
        end = end;
        base_price = base_price_inp;
        total_seats = seats_inp;
        venue_cost = venue_cost_inp;
    }
    double calculateProfit(){
    
        double ticket_revenue = (total_seats/4)*(2*base_price) + ((total_seats*3)/4)*base_price;
        ticket_revenue = 1.0*ticket_revenue - (0.18*ticket_revenue);
        
        int popcorn_revenue = (total_seats/4)*150;

        double net_profit = ticket_revenue + 1.0*popcorn_revenue - 1.0*venue_cost;

        return net_profit;
    }
    private:
    int start;
    int end;
    int base_price;
    int total_seats;
    int venue_cost;
};


class Wedding :public Event{
    public:
    Wedding(){}
    Wedding(int s,int e,int base_price_inp,int guests_inp,int decoration_cost_inp,int venue_cost_inp )
    :Event(s,e)
    {
        start = s;
        end = end;
        base_price = base_price_inp;
        decoration_cost = decoration_cost_inp;
        guest_count = guests_inp;
        venue_cost = venue_cost_inp;
    }
    double calculateProfit(){

        int net_venue_cost = venue_cost;
        if(guest_count > 200){
            net_venue_cost = 3*venue_cost;
        }

        int catering_cost = 100*guest_count;
        if( guest_count > 100) catering_cost = 70*guest_count;

        double net_profit ;
        net_profit = base_price - net_venue_cost - decoration_cost - catering_cost;

        return net_profit;
    }
    private:
    int start;
    int end;
    int base_price;
    int decoration_cost;
    int guest_count;
    int venue_cost;
};

istream &operator >>(istream& cin,Event* &event){

    int type;
    cin>>type;

    if(type == 1){
        int s,e,ticket_price,ticket_sold,artist_fee,logistic;
        cin>>s>>e>>ticket_price>>ticket_sold>>artist_fee>>logistic;

        event = new Concert(s,e,ticket_price,ticket_sold,artist_fee,logistic);
    }
    else if(type == 2){
        
        int s,e,base_price,total_seats,venue_cost;
        cin>>s>>e>>base_price>>total_seats>>venue_cost;

        event = new TheaterShow(s,e,base_price,total_seats,venue_cost);
    }
    else if(type == 3){

        int s,e,base_price,decoration_cost,guest_count,venue_cost;
        cin>>s>>e>>base_price>>decoration_cost>>guest_count>>venue_cost;

        event = new Wedding(s,e,base_price,guest_count,decoration_cost,venue_cost);
    }

    return cin;
    
}
class Comparator{
    public:
    bool operator()(Event * a,Event * b){
        int sa = a->get_start(),ea = a->get_end();
        int sb = b->get_start(), eb= b->get_end();

        if(sa < sb){
            return true;
        }
        else if(sa >sb) return false;
        else{
            return ea<eb;
        }

        return false;
    }
};

class EventOrganiser{
  
    public:
    EventOrganiser(){}
    EventOrganiser(int n){
        n_events = n;
        events.resize(n_events);
    }
    void input(){
        for(int i=0;i<n_events;i++){
            cin>>events[i];
        
        // cout<<events[i]->get_start()<<' '<<events[i]->get_end()<<'\n';
        }
    }

    double max_profit(){

        sort(events.begin(),events.end(),Comparator());

        vector<double> dp(n_events+1,0.0);
        vector<int> start_times(n_events);

        int n= n_events;

        for(int i=0;i<n;i++){
            
            start_times[i] = events[i]->get_start();
            // cout<<start_times[i]<<' '<<events[i]->calculateProfit()<<'\n';
        }

        for(int i=n-1;i>=0;i--){
            if(i == n-1){
                double zero = 0.0;
                dp[i] = max(zero,events[i]->calculateProfit()); 
            }
            else{

                int e = events[i]->get_end();
                double profit = events[i]->calculateProfit();

                auto itr  = lower_bound(start_times.begin(),start_times.end(),e);

                int k = itr - start_times.begin();
                if(itr == start_times.end()){
                    dp[i] = max(dp[i+1],profit);
                }
                else{
                    dp[i] = max(dp[i+1],profit+dp[k]);
                }
            }
        }
        cout << fixed << setprecision(2) << dp[0] << '\n';

        return 0.0;
    }

    // int lb(int l,int r,int val,vector<Event*> vec){

    //     while(l<r){
    //         int mid = (l+r)/2;

    //         if(vec[mid]->get_end() <= val){
    //             l = mid;
    //         }
    //         else {
    //             r = mid-1;
    //         }

    //         if(r-l == 1){
    //             if(vec[l]->get_end() < )
    //         }
    //     }
    // }


    private:

    int n_events;
    vector<Event *> events;
};
int32_t main(){

    int n;
    cin>>n;

    EventOrganiser myself(n);
    myself.input();
    myself.max_profit();

}