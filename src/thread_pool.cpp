#include "thread_pool.h"

ThreadPool::ThreadPool(size_t threadCount)
{
    for (size_t i = 0; i < threadCount; i++)
    {
        // Create threads
        m_Workers.emplace_back([this] {
            while (true)
            {
                std::function<void()> task;

                {
                    std::unique_lock<std::mutex> lock(m_Mutex);

                    // Let thread sleep until:
                    // 1. there is tasks to do
                    // OR
                    // 2. its time to quit (stop)
                    m_Condition.wait(lock, [this] { return m_Stop || !m_Tasks.empty(); });

                    if (m_Stop && m_Tasks.empty())
                        return; // Stop loop

                    // Here std::move() is used to move task instead of copying it
                    task = std::move(m_Tasks.front());
                    m_Tasks.pop();
                } // Mutex unlocked here

                // Run task
                task();
            }
        });
    }
}

ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(m_Mutex);
        m_Stop = true;
    } // Mutex unlocked here

    m_Condition.notify_all();

    for (std::thread &worker : m_Workers)
        worker.join();
}

void ThreadPool::enqueue(std::function<void()> task)
{
    {
        std::unique_lock<std::mutex> lock(m_Mutex);
        m_Tasks.push(std::move(task));
    } // Mutex unlocked here

    m_Condition.notify_one();
}
