#pragma once
#include "Arp/System/Commons/Threading/Thread.hpp"

#include <queue>
#include <utility>
#include <chrono>

namespace BufferedExchange
{
    class MyWorker
    {

    public: // Methods the Threads call.

        //for automatic repeating WorkerThread
        void RunSingle(void)
        {
            ++this->RunCount;
            process();
        };

        //"Endless loop" for normal thread
        void Run(void *)
        {
		while (!this->Stop)
		{
			RunSingle();
			Arp::Thread::Sleep(1000);
		}
        };

        //Static thread implementation
        static void RunStatic(void *pParam)
        {
            ((MyWorker *)pParam)->Run(nullptr);
        };

    public: // Construction
        MyWorker() : RunCount(0),
                     Stop(true)
        {
            Log::Info("------------------- MyWorker Constructed: {0}",Stop);
        }
        ~MyWorker()
        {
            Log::Info("------------------- MyWorker Deconstructed: {0}",Stop);
            Stop = true;
        }
    public: // Properties
        int RunCount;
        bool Stop;
        Arp::Mutex d1;

    private:
        // use thread safe data storage of your choice or implement with semaphores|mutex etc.

        // active queue for processing
        std::queue<std::pair<double, int>> data_toprocess;

        // active queue for storing
        std::queue<std::pair<double, int>> data_store;

        // Timepoint of last SetData command to log time between entries.
        std::chrono::high_resolution_clock::time_point last_time{};

    private:
        void process()
        {
            try
            {
                while (!data_toprocess.empty() && !Stop)
                {
                    // Do something with the first element of this queue
                    if (data_toprocess.front().second % (int)1000 == (int)0)
                    {
                        Log::Info("--- Thread time:{0} data:{1}", data_toprocess.front().first, data_toprocess.front().second);
                    }
                    data_toprocess.pop();
                }

                while (data_store.size() < 10 && !Stop)
                {
                    Thread::Sleep(10);
                }
                if (d1.TryLock())
                {
                    Log::Info("--- Swap Thread queue pointers data_store<<-->>data_toprocess");
                    std::swap(data_store, data_toprocess);
                    d1.Unlock();
                }
            }
            catch (Exception &e)
            {
		Log::Error("--- Exception during ThreadProcess:{0}",Thread::GetCurrentThreadId());
		Log::Error("--- {0}",e.GetMessage());
                Stop = true;
            }
        };

    public: // Data Interface
        // 0 = Okay || 1 = Error
        bool SetData(int x)
        {
            bool result{false};
            // make sure only one process can push to the queue at once.
            try
            {
                d1.Lock();
                auto time =  std::chrono::high_resolution_clock::now();
                data_store.push(std::pair<double, int>( std::chrono::duration_cast<std::chrono::duration<double>>(time - last_time).count(), x));
                last_time = time;
                d1.Unlock();
            }
            // error handling for pushing  //full buffer etc.
            catch (Exception &e)
            {
		Log::Error("--- Exception in SetData Function called by:{0}",Thread::GetCurrentThreadId());
		Log::Error("--- {0}",e.GetMessage());
                result = true; // error Occured
            }
            return result;
        };

    };

} // namespace BufferedExchange
