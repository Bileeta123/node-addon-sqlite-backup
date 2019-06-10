#include "backUpAsyncWorker.h"
#include <iostream>
#include <napi.h>
#include <cstring>
#include <string>
#include <stdio.h>

extern "C" {
  #include "sqlitebackup.h" //a C header, so wrap it in extern "C"
}
extern "C" {
  #include "compress.h" //a C header, so wrap it in extern "C"
}

BackUpAsyncWorker::BackUpAsyncWorker(Function& callback, std::string dbFileName, std::string outputFileName, void(*xProgress)(int, int))
    : AsyncWorker(callback), dbFileName(dbFileName), outputFileName(outputFileName), xProgress(xProgress) {};


void BackUpAsyncWorker::Execute() {
//    std::cout << "The initial string is : ";
//    std::cout << dbFilePath << std::endl;
//    std::cout << outputFilePath << std::endl;
//    std::cout << "-------*************---------";
    //dbFilePath.append(".sqlite");

   // const char *backUpFileName =  "tmpsqlbk.sqlite";

    char * backUpFileName = new char [outputFileName.length()+1];
    std::strcpy (backUpFileName, outputFileName.c_str());

    dbFileName.append(".sqlite");
    int success = createBackup(dbFileName.c_str(), backUpFileName, xProgress);
    if (success == 1) {
        success = compress_file(backUpFileName, outputFileName.append(".gz").c_str());
        if (success != 1) {
            SetError ("Failed to compress the back up file "  + outputFileName);
        }
    }
    else {
        SetError ("Failed to open the DB "  + dbFileName);
    }
    remove(backUpFileName);
};

void BackUpAsyncWorker::OnOK() {
    std::string msg = "Completed SQ LITE DB Backup";
    Callback().Call({Env().Null(), String::New(Env(), msg)});
};