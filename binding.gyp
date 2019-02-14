{
    "targets": [{
        "target_name": "node-addon-sqlite-backup",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "cppsrc/modules/runBackUpWorker.cc",
            "cppsrc/modules/backUpAsyncWorker.cc",
            "cppsrc/modules/sqlitebackup.c",
            "cppsrc/modules/compress.c"
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'libraries': [],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }]
}