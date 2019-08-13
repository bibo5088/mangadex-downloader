#ifndef MANGADEX_DOWNLOADER_SEPHAMORE_H
#define MANGADEX_DOWNLOADER_SEPHAMORE_H

#include <mutex>
#include <condition_variable>

class Semaphore {
public:
    explicit Semaphore(int count_ = 0)
            : count(count_) {}

    void notify();

    void wait();

private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;
};

class ScopedSemaphore {
    Semaphore &s;
public:
    ScopedSemaphore(Semaphore &ss) : s{ss} { s.wait(); }

    ~ScopedSemaphore() { s.notify(); }
};

#endif //MANGADEX_DOWNLOADER_SEPHAMORE_H
