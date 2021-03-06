#include <utility>
#include <cmath>
using namespace std;

class person{
    public :
        void move (int x0,int y0){
            coord.second+=x0;
            coord.first+=y0;
        } // Change la position, à utiliser surement avec des + ou -1 seulement pour éviter des téléportations
        pair<int,int> getpos(){
            return coord;
        }
        char getchar(){
            return e;
        }
        bool isalive(){
            return alive;
        }
    private :
        std::pair <int,int> coord;
        char e; // char de représentation
    protected:
        person(int x0,int y0,int h0,char c0,int str0):coord(x0,y0),h(h0),str(str0){}; //Constructeur private à accéder grace aux sous-classe !PAS DE PERSON H DANS LE CODE!
        int h; //points de vie
        bool alive= true;
        int str; //point de force
};

class enemy:public person{
    void hit(int d,Hero* H){
        if (h-d>0){
            h-=d; //réduit sa vie
        }
        else{
            die(H);
            alive=false;//meurt si il a plus de vie
        }
    }
    void die(Hero* H){
        H->plusexp(expgiven);
    }
    private:
        int expgiven; //expérience donnée au joueur en mourant
    protected:
        enemy(int x0,int y0,int h0,char c0,int str0,int expgiven0):person(x0,y0,h0,c0,str0),expgiven(expgiven0){};
};

class bat:public enemy{
    public :
        bat(int x0,int y0):enemy(x0,y0,3,'~',1,20){
        };
};

class DK:public enemy{
    public :
        DK(int x0,int y0):enemy(x0,y0,30,'£',5,1000){
        };
};

class goblin:public enemy{
    public :
        goblin(int x0,int y0):enemy(x0,y0,6,'ù',2,50){
        };
};

class skeleton:public enemy{
    public :
        skeleton(int x0,int y0):enemy(x0,y0,8,'$',3,100){
        };
};

class bme:public enemy{
    public :
        bme(int x0,int y0):enemy(x0,y0,2,'ç',1,10){
        };
};

class Hero:public person{
    public :
        Hero(int x0,int y0):person(x0,y0,10,'@',2),mana(10),exp(0),level(1),intel(3),armor(1){
        };
        void plusexp(int plus){
            exp+=plus; // rajoute l'exp au personnage
            getlevel();
        }
        void getlevel(){
            while (exp < pow(level,2) ){
                level +=1;
                h+=5;
                hmax+=5;
                str+=2;
                intel+=2;
            }
        }
        void hit(int d){
            if (d<h){
                h-=d;
            }
            else{
                alive=false;
            }
        }
    private:
        int mana; //point de magie nécéssaire pour prendre des dégats
        int level; // le niveau du personnage
        int intel; //point d'intelligence, comme les points de force mais pour la magie
        int gold; // argent
        int exp; //expérience du personnage(à augmenter pour gagner en niveau)  
        int armor; // armure du personnage
        int hmax=10;
};