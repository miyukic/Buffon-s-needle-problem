/*
 * clang++-11 bs_needle_problem.cpp -I/usr/include/python3.8 -I$HOME/.local/lib/python3.8/site-packages/numpy/core/include -lpython3.8
 */
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <cmath>
#include <chrono>
#include <utility>
#include "./lib/matplotlibcpp.h"
//#include <algorithm>
//#include <numbers>



namespace myk {

constexpr double PI = 3.141592653589793238462643383279502884L;

class BNP {

    std::random_device seed_gen;
    uint64_t seed;

  public:
    std::mt19937 engine;

    static constexpr uint8_t NEEDLE_LENGTH = 5;                 // 針の長さ(l)
    static constexpr uint8_t LINE_WIDTH = NEEDLE_LENGTH * 2;    // 線の幅(w)

    std::vector<double> dropPoint{};               // 針の中心と線までの距離 
    std::vector<double> dropAngle{};               // sinΘ 
    uint64_t touchLineCount{0};                    // 針が線に触れた数

    BNP() : seed{seed_gen()}, engine{seed} { }
    ~BNP() { }

    void drop() {
        //std::mt19937 engine{this->seed};
        std::uniform_real_distribution<> dist{0, 1};
//std::cout << dist(engine) << std::endl;
        dropPoint.push_back(dist(engine) * (LINE_WIDTH / 2));
        dropAngle.push_back(simulation2());
    }

    // ===============================================
    // 針が線に触れている数を集計。                  < 
    // ===============================================
    void totalingTouchLine() {
        for (std::size_t i = 0; i < dropAngle.size(); i++) {
             // 1/2*l+sinΘ
            double h = ((double)BNP::NEEDLE_LENGTH / 2) * dropAngle.at(i);
            if (h >= dropPoint.at(i)) {
                this->touchLineCount++;
            }
        }
    }

    double calc() const {
        uint64_t numberOfTrials = dropAngle.size();
        std::cout << "回数:" << numberOfTrials << std::endl;

        return (double) numberOfTrials / this->touchLineCount;
    }


    // ==================================================
    // 単位円上にランダムに点を置き、一様な分布を用いて <
    // Θをランダムに決定しsinΘを返す。                  <
    // ==================================================
    double simulation() {
        // WIP
        //uint8_t r = 0;
        return 0;
    }


    // ===================================================
    // 単位円内にランダムに点を置き、                    <
    // 一様な分布を用いてΘをランダムに決定しsinΘを返す。 <
    // ===================================================
    double simulation2() {
        double radius = 0.0;
        double dy = 0.0;
        double dx = 0.0;
        std::uniform_real_distribution<> dist{0, 1};
            while (true) {
                dx = dist(engine);
                dy = dist(engine);
                if (dx == 0 && dy == 0) continue;
                if (sqrtl(powl(dx, 2) + powl(dy, 2)) <= 1) {
                    radius = sqrtl(powl(dx, 2) + powl(dy, 2));
                    break;
                }
            }
            double sin_theta = dy / radius;
            return sin_theta;
        }

};


} // namespace myk end


using myk::BNP;

int main() {

    std::chrono::system_clock::time_point start, end;

    start = std::chrono::system_clock::now(); // 計測開始
    BNP bnp{};
    constexpr auto TIMES = 5000000;
    for (auto i = 0; i < TIMES; i++) bnp.drop();
    bnp.totalingTouchLine();
    double pi = bnp.calc();
    end = std::chrono::system_clock::now(); // 計測終わり

    double time = static_cast<double>(
                std::chrono::duration_cast<std::chrono::microseconds>(end - start)
                .count() / (1000.0 * 1000.0)
            ); // 秒 

    std::cout << "π= " << pi << std::endl;
    std::cout << "触れた回数:" << bnp.touchLineCount << std::endl;
    std::cout << "経過時間:" << std::round(time * 1000) / 1000 << " 秒" << std::endl; 


    // グラフ表示
    
    //0~180°からランダムに選びsinΘをベクターに格納
    std::vector<double> y2;
    for (auto i = 0; i < TIMES; i++) {
        std::uniform_real_distribution<> dist{0, 1};
        y2.push_back(std::sin(dist(bnp.engine) * myk::PI));
    }
    namespace plt = matplotlibcpp;
    plt::subplot(2, 1, 1);
    plt::hist(y2, 100, "darkcyan");
    plt::subplots_adjust({{"hspace", 0.6}});

    //BNPオブジェクトのdropAngleをベクターに格納
    //std::vector<double> y3{};
    //for (auto i = 0; i < TIMES; i++) {
    //    y3.push_back(bnp.dropAngle.at(i));
    //}

    plt::subplot(2, 1, 2);
    plt::hist(bnp.dropAngle, 100, "c");

    plt::show();

    // グラフ表示終わり

    
}



