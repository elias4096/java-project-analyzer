#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool
{
  public:
    ThreadPool(size_t threadCount);
    ~ThreadPool();

    void enqueue(std::function<void()> task);

  private:
    std::vector<std::thread> m_Workers = {};
    std::queue<std::function<void()>> m_Tasks = {};

    std::mutex m_Mutex;
    std::condition_variable m_Condition;

    bool m_Stop = false;
};
