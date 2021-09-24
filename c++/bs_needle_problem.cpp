#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <cmath>
#include <chrono>



namespace myk {

class BNP {

    std::random_device seed_gen;
    uint64_t seed;
    std::mt19937 engine;

  public:
    static constexpr uint8_t NEEDLE_LENGTH = 5;                 // 針の長さ(l)
    static constexpr uint8_t LINE_WIDTH = NEEDLE_LENGTH * 2;    // 線の幅(w)

    std::vector<double> dropPoint{};               // 針の中心と線までの距離 
    std::vector<double> dropAngle{};               // sinΘ 
    uint64_t touchLineCount{0};                     // 針が線に触れた数

    BNP() : seed{seed_gen()}, engine{seed} { }
    ~BNP() { }

    void drop() {
        //std::mt19937 engine{this->seed};
        std::uniform_real_distribution<> dist{0, 1};
        dropPoint.push_back(dist(engine) * LINE_WIDTH / 2.0L);
        dropAngle.push_back(simulation2());
    }

    // ===============================================
    // 針が線に触れている数を集計。                  < 
    // ===============================================
    void totalingTouchLine() {
        for (auto i = 0; i < dropAngle.size(); i++) {
             // 1/2*l+sinΘ
            double h = (BNP::NEEDLE_LENGTH >> 2) + dropAngle[i];
            if (h >= dropPoint[i]) {
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
        uint8_t r = 0;
        return 0;
    }

    // ===================================================
    // 単位円内にランダムに点を置き、                    <
    // 一様な分布を用いてΘをランダムに決定しsinΘを返す。 <
    // ===================================================
    double simulation2() {
        double radius = 0.0L;
        double dy = 0.0L;
        double dx = 0.0L;
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

using namespace myk;

int main(int argc, char* argv[]) {
    std::chrono::system_clock::time_point start, end;
    start = std::chrono::system_clock::now(); // 計測開始
    BNP bnp{};
    constexpr auto TIMES = 30000;
    for (auto i = 0; i < TIMES; i++) bnp.drop();
    bnp.totalingTouchLine();
    double pi = bnp.calc();
    end = std::chrono::system_clock::now(); // 計測終わり
    std::cout << "π= " << pi << std::endl;
    std::cout << "触れた回数:" << bnp.touchLineCount << std::endl;

    double time = static_cast<double>(
                std::chrono::duration_cast<std::chrono::microseconds>(end - start)
                .count() / 1000.0F
            ); // 秒
    std::cout << "経過時間" << std::round(time * 1000) / 1000 << std::endl; 

}


