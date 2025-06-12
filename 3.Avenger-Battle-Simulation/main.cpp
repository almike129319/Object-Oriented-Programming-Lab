#include<bits/stdc++.h>
using namespace std;

int n,m,k,extrasuits;

class QNS{
    public:
        
        //constructors

    QNS(int power_level_inp=1000,int durability_inp=500,
        int energy_storage_inp=300,int heat_level_inp=0)        
    {
            power_level=min(5000,power_level_inp);
            durability=durability_inp;
            energy_storage=energy_storage_inp;
            heat_level=heat_level_inp;
    }
    QNS(const QNS& to_copy){         //copy constructor
        
        power_level=to_copy.power_level;
        durability=to_copy.durability;
        energy_storage=to_copy.energy_storage;
        heat_level=to_copy.heat_level;
    
    }

        //operators

    void operator + (QNS othersuit){     // used to add other suit attributes to this
        
        power_level+=othersuit.energy_storage;
        if(power_level>5000) power_level=5000;
        durability+=othersuit.durability;
        energy_storage+=othersuit.power_level;

    }
    void operator - (int damage){       //used decrease the durability by damage

        durability -= damage;
        energy_storage += damage;
        heat_level += damage;
    }
    void operator * (int factor){       //used to increase power,also increases heat,energy storage
        power_level=power_level+((power_level*factor)/100);
        if(power_level>5000) power_level=5000;
        energy_storage+= 5*factor;
        heat_level += factor;

    }
    void operator / (int factor){       //used to decrease heat, increase durability by factor

        durability+=factor;
        heat_level-=factor;
        if(heat_level<0) heat_level=0;

    }
    bool operator == (QNS othersuit){   //checks if two suits are of equal value
        
        if(power_level==othersuit.power_level&&durability==othersuit.durability) return true;
        return false;

    }
    bool operator < (QNS othersuit){    //checks if power+durability is greater tha one or not

        if(power_level+durability<(othersuit.power_level+othersuit.durability)) return true;
        return false;

    }
    
        // getters

    int getpower_level(){
        return power_level;
    }
    int get_durability(){
        return durability;
    }    
    int get_energy(){
        return energy_storage;
    }
    int get_heatlevel(){
        return heat_level;
    }

        //setters

    void set_powerlevel(int new_power){
        power_level=new_power;
    }
    void set_heatlevel(int new_heatlevel){ 
        heat_level=new_heatlevel;
    }
    void set_durability(int durabilityNew){
        durability=durabilityNew;
    }
    
    
        //methods
    void boostPower(int factor){        // adds power to suit
        (*this)*factor;
    }
    void boostPower(QNS otherSuit){     //adds other suit attributes to this
       (*this)+otherSuit;
    }
    
    private:
    
    int power_level;
    int durability;
    int energy_storage;
    int heat_level;

};

vector<QNS> suits;

class avengers{
    public:

        //constructors
    avengers (){}
    avengers(string avname,QNS avsuit,int strength){
        
        name=avname;
        suit=avsuit;
        attack_strength=strength; 
    
    }

        //methods
    
    void attack(avengers & enemy ){     // decreases enemy strength by factor
        enemy.suit-attack_strength;
    }
    void upgrade_suit(){ 
        suit+suits[k-extrasuits];
    }
    void repair(int x){         //restores some durability
        suit/x;
    }
    void print_status(){
        cout<<name<<' '<<suit.getpower_level()<<' '<<suit.get_durability()<<' '
            <<suit.get_energy()<<' '<<suit.get_heatlevel()<<'\n';
    }
    bool is_alive(){
        if(suit.get_durability()<=0) return false;
        return true;
    }
    bool is_overheat(){
        if(suit.get_heatlevel()>500) return true;
        return false;
    }
    // getters
    string getname() {
        return name;
    }
    QNS& getsuit(){
        return suit;
    }
    private:
    string name;
    QNS suit;
    int attack_strength;

};

class Battle{

    public:

    void startbattle() {}       //simulates the battle
    void print_battlelog(){     // prints battle log
        for(auto str:battlelog){
            cout<<str<<'\n';
        }
    }
    //sums the power and durability of heros and enemies and
    // return 1 if it is greater than 0
    int result(){
        int herosum=0,enemysum=0;               
        for(auto h:heroes) {
            if(h.getsuit().get_durability()<0) continue;
            herosum+=h.getsuit().get_durability()+h.getsuit().getpower_level();
        }
        for(auto h:enemies) {
            if(h.getsuit().get_durability()<0) continue;
            enemysum+=h.getsuit().get_durability()+h.getsuit().getpower_level();
        }                      
        if(enemysum>herosum) return -1;
        else if(enemysum<herosum) return 1;
        else return 0;
    }
    void addhero( avengers a) {
        heroes.push_back(a);
    }
    void addenemy( avengers a) {
        enemies.push_back(a);
    }
    
    avengers* getavenger(string name){
      avengers a;
        for(avengers &h:heroes) {
            if(h.getname()==name) return &h;
        }
        for(auto &h:enemies) {
            if(h.getname()==name) return &h;
        }
        return &a;
    }
    void add_to_log(string tobe_added){
        battlelog.push_back(tobe_added);
    }

    private:
    vector<avengers> heroes;
    vector<avengers> enemies;
    vector<string> battlelog;
};

int main(){
    cin>>k>>n>>m;
    Battle b;
   
    for(int i=0;i<k;i++){           //input of suits
        int p,d,e,h;
        cin>>p>>d>>e>>h;
        QNS *s=new QNS(p,d,e,h);
        suits.push_back(*s);
    }
   
    string name;
    int strength;
   
    for(int i=0;i<n+m;i++){         //input of avengers
        cin>>name>>strength;
        
        if(i>=k) {
            cout<<name<<" is out of fight"<<'\n'; continue;
        }  

        avengers *a = new avengers(name,suits[i],strength); 
        
        if(i<n){
            b.addhero(*a);         
        }
        else b.addenemy(*a);
    }
   
    extrasuits=k-(n+m);
    
    string cmd;
    cin>>cmd;
    
    while(cmd!="End"){
        
        if(cmd=="BattleBegin") b.startbattle();
        
        else if(cmd=="Attack"){
            string name1,name2;
            cin>>name1>>name2;
            
            avengers * av1=b.getavenger(name1);
            avengers * av2=b.getavenger(name2);

            if(av2->is_alive()&&!av1->is_overheat()){
                if(av2->is_alive()){

                    string s=name1+" attacks "+name2;
                    b.add_to_log(s);
                    av1->attack(* av2);
                    if(!av2->is_alive()) {
                        s=name2+" suit destroyed";
                        b.add_to_log(s);
                    }
                    else if(av2->is_overheat()){
                        s=name2+" suit overheated";
                        b.add_to_log(s);
                    }
                }
            }
            
        }
        
        else if(cmd=="Repair"){
            cin>>name;
            int factor;
            cin>>factor;
            b.getavenger(name)->repair(factor);
            string s=name+" repaired";
            b.add_to_log(s);
        }
        
        else if(cmd=="BoostPowerByFactor"){
            cin>>name;
            int factor;
            cin>>factor;
            b.getavenger(name)->getsuit().boostPower(factor);
            string s=name;
            s+=" boosted";
            b.add_to_log(s);
            if(b.getavenger(name)->is_overheat()) {
                s=name+" suit overheated";
                b.add_to_log(s);
            }
        }
        
        else if(cmd=="BoostPower") {
            cin>>name;
            int p,d,e,h;
            cin>>p>>d>>e>>h;
            QNS temp_suit(p,d,e,h);
            b.getavenger(name)->getsuit().boostPower(temp_suit);
            string s=name;
            s+=" boosted";
            b.add_to_log(s);
            if(b.getavenger(name)->is_overheat()) {
                s=name+" suit overheated";
                b.add_to_log(s);
            }
        }
        
        else if(cmd=="AvengerStatus"){
            cin>>name;
            b.getavenger(name)->print_status();
        }
        
        else if(cmd=="Upgrade"){
            cin>>name;
            string s=name;
            if(extrasuits>0){
                b.getavenger(name)->upgrade_suit();
                extrasuits--;
                s=name+" upgraded";
                b.add_to_log(s);
            }
            else {
            s=name+" upgrade Fail";
            b.add_to_log(s);
            }
        }

        else if(cmd=="PrintBattleLog") b.print_battlelog();
        
        else if(cmd=="BattleStatus") {
            if(b.result()==1) cout<<"heroes are winning"<<'\n';
            else if(b.result()==0) cout<<"tie"<<'\n';
            else cout<<"enemies are winning"<<'\n';
        }
        
        cin>>cmd;
    }

}