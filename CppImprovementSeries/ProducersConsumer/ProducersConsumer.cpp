#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include <fstream>
#include <syncstream>

int main() {
    using namespace std::chrono_literals;

    std::atomic_size_t value = 10;
    std::atomic_bool isTenWriting = false;
    std::atomic_bool isValueChanged = true;
    std::atomic_bool quit = false;

    auto quiter = [&isTenWriting, &isValueChanged]() {
        std::this_thread::sleep_for(50ms);
        isTenWriting.store(true);
        isTenWriting.notify_all();
        std::this_thread::sleep_for(50ms);
        isTenWriting.store(false);
        isTenWriting.notify_all();

        std::this_thread::sleep_for(50ms);
        isValueChanged.store(true);
        isValueChanged.notify_all();
        std::this_thread::sleep_for(50ms);
        isValueChanged.store(false);
        isValueChanged.notify_all();
    };

    std::jthread p1([&value, &isTenWriting, &isValueChanged, &quit]() {
        while (!quit.load()) {
            isTenWriting.wait(false);
            isValueChanged.wait(true);
            if (quit.load()) {
                break;
            }
            auto valueDup = value.load();
            valueDup = (valueDup + 10) % 100;
            value.store(valueDup == 0 ? 10 : valueDup);
            isValueChanged.store(true);
            isValueChanged.notify_one();
            isTenWriting.store(false);
            isTenWriting.notify_one();
        }
    });

    std::jthread p2([&value, &isTenWriting, &isValueChanged, &quit]() {
        while (!quit.load()) {
            isTenWriting.wait(true);
            isValueChanged.wait(true);
            if (quit.load()) {
                break;
            }
            auto valueDup = value.load();

            auto lastDigit = valueDup % 10;
            lastDigit = (lastDigit + 1) % 10;

            valueDup = valueDup / 10 * 10 + lastDigit;

            value.store(valueDup);
            if (valueDup % 10 == 0) {
                isTenWriting.store(true);
                isTenWriting.notify_one();
            }
            else {
                isValueChanged.store(true);
                isValueChanged.notify_one();
            }
        }
    });

    std::jthread w([&value, &isValueChanged, &quit]() {
        while (!quit.load()) {
            isValueChanged.wait(false);
            if (quit.load()) {
                break;
            }
            std::cout << time(0) << " " << value.load() << std::endl;
            std::this_thread::sleep_for(1s);
            isValueChanged.store(false);
            isValueChanged.notify_all();
        }
    });

    std::jthread fileReader([&quit, &quiter]() {
        std::string filename("control.txt");
        {
            std::fstream f(filename, std::ios_base::trunc | std::ios_base::out);
        }
        while (!quit.load()) {
            std::this_thread::sleep_for(1s);
            std::fstream f(filename, std::ios_base::in);
            f.seekg(0);
            std::string s;
            f >> s;
            f.close();
            if (s == "quit") {
                quit.store(true);
                quiter();
            }
        }
    });

    return 0;
}