//
// Created by joseph on 4/30/22.
//

#ifndef KAMIS_ALGO_LOG_H
#define KAMIS_ALGO_LOG_H


#include <chrono>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>

class algo_log : public nlohmann::json {
public:
    using clock = std::chrono::steady_clock;
    using time_point = clock::time_point;
    using duration = std::chrono::duration<float>;

    algo_log(algo_log const&) = delete;
    void operator=(algo_log const&) = delete;

    static algo_log& logger() {
        static algo_log logger;
        return logger;
    }

    void set_name(std::string _algo_name) {
        algo_name = std::move(algo_name);
    }

    void start_timer() {
        timer_start = clock::now();
        timer_running = true;
    }

    duration end_timer() {
        if (timer_running) {
            time = clock::now() - timer_start;
            (*this)["time"] = time.count();
            return time;
        } else
            return duration::zero();
    }

    duration get_time() {
        if (!timer_running)
            return clock::now() - timer_start;
        else
            return time;
    }

    void write(std::string fname, bool dump = true, int spacing = 2) {
        std::ofstream file(fname.c_str());
        file << std::setw(spacing) << *this;
        if (spacing > 0)
            file << std::endl;
        if (dump) this->dump(spacing);
    }

    void instance(std::string name) {
        (*this)["instance"] = name;
    }

    template<typename weight>
    void solution(weight w) {
        (*this)["solution"] = w;
    }

    void dump(int spacing = 2) {
        std::cout << std::setw(spacing) << *this << std::endl;
    }

private:
    algo_log() {};

    bool timer_running;
    time_point timer_start;
    duration time;

    std::string algo_name;
};


#endif //KAMIS_ALGO_LOG_H
