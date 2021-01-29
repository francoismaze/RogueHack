#include <iostream>
#include "stdlib.h"
#include <map>
#include "game.h"
#include "pers.h"

int game::keyEvent(){
    if( !initialized){
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }
    int bytesWaiting;
    //int bytesWaiting;                                                                                                                                                        
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
};

void game::frameSleep(const int& ms){
    clock_t end;
    end = clock() + ms * CLOCKS_PER_SEC/1000;
    while( clock() < end){
        // wait 
    }
};

std::pair<int,int> from_key_to_move(int key){
    if ( key == 68 ) {//flèche gauche
        return std::make_pair(-1,0);
    }
    if ( key == 67 ) {//flèche droite
        return std::make_pair(1,0);
    }
    if ( key == 65 ) {//flèche basse
        return std::make_pair(0,-1);
    }
    if ( key == 66 ) {//flèche haute
        return std::make_pair(0,1);
    }
};

void game::startGame( board &b ){
    int key; //variable contenant la frappe
    std::pair<int, int> dim = b.get_dim();
    int nx = dim.first;
    int ny = dim.second;
    //o.create();
    //b.add_object( a );
    Hero h;
    while( true ){
        frameSleep(lap);
        if( keyEvent() ){
            int a = getchar();
            int b = getchar();
            int key = getchar(); //récupération de la frappe (3ème caractère pour différencier les flèches)
            heros.move( from_key_to_move(key) ); //maj du mouvement
        }
        b.backgroundClear();
        b.remove_perso( h );
        b.add_perso( h ); //ajout du perso au plateau
        b.printFrame( h ); //affichage du plateau
        /*bool out =  b.verifyBorder( s ); //vérifie si le serpent sort du plateau
        bool bite_tail = s.bite_tail(); //vérifie si le serpent se mord la queue
        bool traping = t.interact_with( s.get_body(0) ); //vérifie si le serpent tombe dans le piège
        if( out == false || bite_tail == false || traping ){
            std::cerr << "GAME OVER !" << std::endl; //jeu perdu - affichage du score
            std::cerr << "Votre score est : " << s.get_score() << std::endl;
            exit(1);
        }
        bool eat = a.interact_with( s.get_body(0) );
        if(eat){//le serpent a mangé la pomme
            b.remove_object( a );
            a.create( s, std::make_pair(0,0), nx, ny );//création d'une nouvelle pomme
            b.add_object( a );
            if (s.get_score()>1){//si le joueur a atteint un score de 2 au moins, on ajoute/dépace un piège
                b.remove_object( t );
                if (s.get_score()%2 == 1) {//on augmente le nombre de pièges un tour sur deux
                    t.set_size(t.get_size() + 1);
                };
                t.create( s, a.get_item(0), nx, ny );
                b.add_object( t );
            };
            s.incr_snl(); //on augmente la taille du serpent
            increase_speed();//on augmente la vitesse
        };
        s.update_coordinates();//maj des coordonnées du serpent
    }*/
    };
};