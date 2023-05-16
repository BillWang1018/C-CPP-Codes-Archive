#include <iostream>
#include <cmath>
#define CYCLE_SIZE 10e2
#define MAX_CYCLE 10e2
using namespace std;

class BasicAttr {
private:
    double spd;
public:
    double getAtkTime() { return CYCLE_SIZE/spd; };
    void setSpd(double s) { spd = s; };
    void addSpd(double s) { spd += s; };

};

class JY {
private:
    class SG {
    private:
        BasicAttr attr;
        int atkCount;
    public:
        SG() { attr.setSpd(60), atkCount=3; };
        int getAtkCount() { return atkCount; };
        void setAtkCount(int c) { atkCount = c; };
        void addAtkCount(int c) { atkCount += c, attr.addSpd(c*10); };
        void resetAtkCount() { SG(); };
    };
public:
    BasicAttr attr;
    SG sg;
};



int main() {
    freopen("output.txt","w",stdout);

    double speed;
    cin >> speed;

    JY jy;
    jy.attr.setSpd(speed);

    bool useTech = true;
    if(useTech) {
        jy.sg.addAtkCount(3);
    }



    double cycle{}; // a cycle -> one CYCLE_SIZE steps
    int cycleCount{};

    while(cycleCount <= MAX_CYCLE) {
        cycle += 0.001;
        if(cycle-cycleCount >= 1) {
            cycleCount++;
            cycle=0;
        }

        if(jy.attr.getAtkTime());



    }
    
    return 0;
}