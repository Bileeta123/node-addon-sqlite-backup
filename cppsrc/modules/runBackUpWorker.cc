#include "backUpAsyncWorker.h"
#include <iostream>
#include <napi.h>

//callback function
void xProgress(int completed,int total){
       //Completion = 100% * (pagecount() - remaining()) / pagecount()
	std::cout << ".";
}

Value runBackUpAsyncWorker(const CallbackInfo& info) {
    Function callback = info[0].As<Function>();
    std::string dbFileName = info[1].As<String>().Utf8Value();
    std::string outputFileName = info[2].As<String>().Utf8Value();

    BackUpAsyncWorker* asyncWorker = new BackUpAsyncWorker(callback, dbFileName, outputFileName, xProgress);
    asyncWorker->Queue();
    std::string msg = "Created Back up job";
    return String::New(info.Env(),msg.c_str());
};

Object Init(Env env, Object exports) {
    exports["runBackUpAsyncWorker"] = Function::New(env, runBackUpAsyncWorker, std::string("runBackUpAsyncWorker"));
    return exports;
}

NODE_API_MODULE(addon, Init)