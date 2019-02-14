#include "sqlitebackup.h"
#include <stdio.h>
#include "../lib/sqlite3.c"

int backupDb(
  sqlite3 *pDb,               /* Database to back up */
  const char *zFilename,      /* Name of file to back up to */
  void(*xProgress)(int, int)  /* Progress function to invoke */
){
  int rc;                     /* Function return code */
  sqlite3 *pFile;             /* Database connection opened on zFilename */
  sqlite3_backup *pBackup;    /* Backup handle used to copy data */

  /* Open the database file identified by zFilename. */
  rc = sqlite3_open(zFilename, &pFile);
  if( rc==SQLITE_OK ){

    /* Open the sqlite3_backup object used to accomplish the transfer */
    pBackup = sqlite3_backup_init(pFile, "main", pDb, "main");
    if( pBackup ){

      /* Each iteration of this loop copies 5 database pages from database
      ** pDb to the backup database. If the return value of backup_step()
      ** indicates that there are still further pages to copy, sleep for
      ** 250 ms before repeating. */
      do {
        rc = sqlite3_backup_step(pBackup, 5);
        xProgress(
            sqlite3_backup_remaining(pBackup),
            sqlite3_backup_pagecount(pBackup)
        );
        if( rc==SQLITE_OK || rc==SQLITE_BUSY || rc==SQLITE_LOCKED ){
          sqlite3_sleep(250);
        }
      } while( rc==SQLITE_OK || rc==SQLITE_BUSY || rc==SQLITE_LOCKED );

      /* Release resources allocated by backup_init(). */
      (void)sqlite3_backup_finish(pBackup);
    }
    rc = sqlite3_errcode(pFile);
  }

  /* Close the database connection opened on database file zFilename
  ** and return the result of this function. */
  (void)sqlite3_close(pFile);
  return rc;
}

//Execute database backup function
int createBackup(
        const char *dbFileName,      /* Name of D file */
        const char *backupFilename,  /* Name of file to back up to */
        void(*xProgress)(int, int)
    )
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;

//    printf("The dbFileName: %s\n", dbFileName);
//    printf("The backupFilename: %s\n", backupFilename);

	rc = sqlite3_open_v2(dbFileName, &db, SQLITE_OPEN_READONLY, NULL);
	if( rc ){
//      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return 0;
   } else {
//	  fprintf(stderr, "Opened database successfully\n");
	  backupDb(db, backupFilename, xProgress);
	  return 1;
   }

    sqlite3_close(db);
}