#include <iostream>
#include <chrono>
#include <thread>
#include "streaming-worker.h"

using namespace Nan;
using namespace v8;
using namespace std;


class Factorizer : public StreamingWorker {
    public:
    Factorizer(Callback * data, Callback * complete, Callback *error_callback, v8::Local<v8::Object>& options)
    : StreamingWorker(data, complete, error_callback) {

        N = -1;
        if (options->IsObject()){
            v8::Local<v8::Value> n_ = options->Get(New<v8::String>("n").ToLocalChecked());
            if ( n_->IsNumber()){
                N = n_->NumberValue();
            }
        }
        if ( N < 0){
            SetErrorMessage("I cannot compute prime factorization of negative numbers (overflowed long long?)!");
        }
    }
    void send_factor(const AsyncProgressWorker::ExecutionProgress& progress, long long factor){
        MessageSend tosend("decompose factor", std::to_string(factor));
        writeToNode(progress, tosend);
    }

    //executes in the new worker thread (background)
    void Execute(const AsyncProgressWorker::ExecutionProgress& progress){
        long long n = N;
        while ( n % 2 == 0){
            send_factor(progress, 2);
            n = n /2;
        }
        for (long long i = 3; i <= n; i += 2) {
            while(n % i == 0){
                send_factor(progress, i);
                n = n / i;
            }
        for (long long i = 3; i <= n; i += 2){
            while (n%i == 0){
                send_factor(progress, i);
                n = n/i;
            }
        }
        }
    }
    private:
    long long N;
};

StreamingWorker * create_worker(Callback * data, Callback * complete, Callback * error_callback,
v8::Local<v8::Object> & options){
    return new Factorizer(data, complete, error_callback, options);
}

NODE_MODULE(addon, StreamWorkerWrapper::Init)