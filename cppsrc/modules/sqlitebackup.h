#ifndef SQLITE_BACKUP_H
#define SQLITE_BACKUP_H

int createBackup(const char *dbFileName,      /* Name of D file */
                 const char *backupFilename,  /* Name of file to back up to */
                 void(*xProgress)(int, int));

#endif