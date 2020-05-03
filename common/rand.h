#pragma once
#include <random>
#include <vector>
using namespace std;

class RandInt {
private:
    mt19937 m_engine;
    uniform_int_distribution<int> m_dis;
    int m_min;
    int m_max;

public:
    RandInt(int min, int max) : m_min{ min }, m_max{ max }, m_dis{ min, max } {
        random_device rd;
        m_engine.seed(rd());
    }

    int Next() {
        return m_dis(m_engine);
    }
    
    vector<int> NextVector(int N) {
        vector<int> result(N);
        for (auto& it : result)
            it = m_dis(m_engine);
        return result;
    }

};
