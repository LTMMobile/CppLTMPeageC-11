//
//  main.cpp
//  LTMPeageC++11
//

#include <iostream>
#include <thread>
#include <mutex>
#include <random>

int const max_voiture = 256;
std::mutex verrou_peage;

// Thread
void voiture(int n) {
    verrou_peage.lock();
    std::cout << "la voiture " << std::this_thread::get_id() << ", entre pour payer" << std::endl;
    
    // random
    static std::default_random_engine re {};
    using Dist = std::uniform_int_distribution<int>;
    static Dist uid {};
    auto ms = std::chrono::milliseconds(uid(re, Dist::param_type{1000,5000}));
    std::this_thread::sleep_for(ms);
    
    std::cout << "la voiture " << std::this_thread::get_id() << ", sort" << std::endl;
    verrou_peage.unlock();
}

std::thread * tab[max_voiture];

int main(int argc, const char * argv[]) {

    int nb_voiture = 0;
    std::cout << "Entrez le nombre de voiture ?" << std::endl;
    std::cin >> nb_voiture;
    
    if( nb_voiture > 0 && nb_voiture < max_voiture ) {
        //
        for( int t = 0; t < nb_voiture; t++ ) {
            tab[t] = new std::thread {std::bind(voiture, t)};
        }
        
        for ( int i=0; i < nb_voiture; i++ ) {
            tab[i]->join();
            delete tab[i];
            tab[i] = nullptr;
        }
    }else {
        std::cout << "cas invalide" << std::endl;
    }
    
    return 0;
}

