# node-addon-sqlite-backup

Node Addon for sqlite backup

Sqlite db file will backed up using the sqlite back up API. Compressed using zlib and placed in the given output path.

```
/**
 * The given sqlite db file will backed up using the sqlite back up API,
 * and compressed using zlib
 * and placed in the given output path.
 *
 * Parameter definition
 * BackUpWorkerCompletion: Call back function,
 * DB File Name: path for the sqlite file without the extension .sqlite
 * Output File name: path to place the compress output
 */

nodeAddonForSqliteBackup.runBackUpAsyncWorker(BackUpWorkerCompletion, dbFilePath, outputPath);

function BackUpWorkerCompletion (err, result) {
  if (err) {
    console.log("Back Up Worker returned an error: ", err);
  } else {
    console.log("Back Up Worker returned '"+result+"'.");
  }
}
```