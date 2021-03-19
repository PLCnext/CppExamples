#pragma once
#include "Arp/System/Commons/Threading/Thread.hpp"
#include "Arp/System/Commons/Exceptions/Exceptions.h"
#include "Arp/System/Commons/Chrono/SystemTick.hpp"

#include <queue>
#include <utility>


namespace BufferedExchange
{
	using namespace std::chrono;
	template<typename S>
    class MyWorker
    {
	#define MAX_ELEMENTS 1000
	#define MIN_QUEUE_SIZE_TO_PROCESS 10

    public: // Properties
        int RunCount;
        bool Stop;
        Arp::Mutex d1;

    public: // Methods the Threads call.

        // single Execution e.g. for WorkerThreads.
        void RunSingle(void)
        {
            ++this->RunCount;
            process();
        };

        //"Endless loop" for normal thread
        void Run(void *t)
        {
			while (!this->Stop)
			{
				RunSingle();
				// Sleep for X ms until next RunSingle execution.
				Arp::Thread::Sleep(999);
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


    private:
        // use thread safe data storage of your choice or implement with semaphores|mutex etc.


        // active queue for processing
        std::queue<std::pair<double, S>> data_toprocess;

        // active queue for storing
        std::queue<std::pair<double, S>> data_storage;

        // Timepoint of last SetData command to log time between entries.
        std::chrono::nanoseconds last_time{};

    private:
        void process()
        {
            try
            {
            	// print first Element of the queue
            	if(!data_toprocess.empty()){
            		Log::Info("---------------- {2} firstElement: time:{0}  data:{1} ",
					data_toprocess.front().first,
					data_toprocess.front().second,
					Thread::GetCurrentThread()->GetName());
            	}

            	// add another Mutex here if you need to ensure only one thread is processing the data.
                while (!data_toprocess.empty() && !Stop)
                {
                    // Do something with the first element of this queue
                	// in this case we are printing the Last Elemnt of the the queue.
                    if (data_toprocess.size() == 1)
                    {
                        Log::Info("----------------{2} lastElement time:{0}  data:{1}",
                        		data_toprocess.front().first,
								data_toprocess.front().second,
								Thread::GetCurrentThread()->GetName());
                    }

                    // remove first element.
                    data_toprocess.pop();
                }

                //check data_storage size to wait for right amount to be processed.
                //you might want to collect data (e.g. before sending them via TCP to)
                //And while you are not processing you do not need to swap.
                while (data_storage.size() < MIN_QUEUE_SIZE_TO_PROCESS && !Stop)
                {
                    Thread::Sleep(10);
                }
                // Get a lock on the Store to swap it.
                // this operation is blocking but only blocks the thread.
                d1.Lock();
				Log::Info("----------------{0} Swap queue pointers data_storage<<-->>data_toprocess", Thread::GetCurrentThread()->GetName());
				std::swap(data_storage, data_toprocess);
				d1.Unlock();

            }
            catch (...)
            {
                Stop = true;
            }
        };

    public: // Data Interface
        // 1 = Okay || 0 = Error
        bool SetData(S x)
        {
            bool result{true};
            // make sure only one process can push to the queue at once.
            d1.Lock();
            try
            {
            	if(Stop) {
            		throw InvalidOperationException("Data processing is stopped please do not push");
				 }
            	 if(data_storage.size() > MAX_ELEMENTS) {
            		 throw OutOfMemoryException("DataStore has to many elements already!");
            	 }
            	// Lock to ensure the data_storage does not swap during push.

                auto time =  Arp::System::Commons::Chrono::SystemTick::GetNanoTick();
                data_storage.push(std::pair<double, S>( duration_cast<duration<double>>(time - last_time).count(), x));
                last_time = time;
            }
            // error handling for pushing  // full buffer etc.
            catch (InvalidOperationException &e){
            	Log::Error("--- Exception in ThreadProcess:{0}",Thread::GetCurrentThread()->GetName());
            	Log::Error("--- {0}",e.GetMessage());
            	// Do something to fix this or rethrow to handle elsewhere?


                result = false;
            }
            catch (OutOfMemoryException &e){
            	Log::Error("--- Exception in ThreadProcess:{0}",Thread::GetCurrentThread()->GetName());
            	Log::Error("--- {0}",e.GetMessage());
            	Log::Error("--- Process Queue:{0}, Store Queue:{1} ",	data_toprocess.size(),data_storage.size());
            	// Do something to fix this or rethrow to handle elsewhere?

                result = false;
            }
            catch (Exception &e)
            {
        		Log::Error("--- Exception in ThreadProcess:{0}",Thread::GetCurrentThread()->GetName());
        		Log::Error("--- {0}",e.GetMessage());
                Stop = true;
                result = false;

            }
            d1.Unlock();
            return result;
        };

    };

} // namespace BufferedExchange
