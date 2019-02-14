#pragma once
#include <napi.h>
using namespace Napi;

class BackUpAsyncWorker : public AsyncWorker {

    public:
        BackUpAsyncWorker(Function& callback, std::string dbFileName, std::string outputFileName, void(*xProgress)(int, int));
        virtual ~BackUpAsyncWorker() {};

        void Execute();
        void OnOK();

    private:
        std::string dbFileName;
        std::string outputFileName;
        void(*xProgress)(int, int);
};