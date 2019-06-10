const nodeAddonForSqliteBackup = require('./build/Release/node-addon-sqlite-backup');

// nodeAddonForSqliteBackup.runBackUpAsyncWorker(BackUpWorkerCompletion, 'erpdb-25-0', 'test.sqlite');
//
// function BackUpWorkerCompletion (err, result) {
//   if (err) {
//     console.log("Back Up Worker returned an error: ", err);
//   } else {
//     console.log("Back Up Worker returned '"+result+"'.");
//   }
// }
module.exports = nodeAddonForSqliteBackup;