#include <stdio.h>
#include "../lib/zlib.h"

unsigned long file_size(char *filename)
{
   FILE *pFile = fopen(filename, "rb");
   fseek (pFile, 0, SEEK_END);
   unsigned long size = ftell(pFile);
   fclose (pFile);
   return size;
}

int compress_file(const char *infilename, const char *outfilename)
{
   FILE *infile = fopen(infilename, "rb");
   gzFile outfile = gzopen(outfilename, "wb");
   if (!infile || !outfile)
   return -1;

   char inbuffer[128];
   int num_read = 0;
   unsigned long total_read = 0, total_wrote = 0;
   while ((num_read = fread(inbuffer, 1, sizeof(inbuffer), infile)) > 0) {
      total_read += num_read;
      gzwrite(outfile, inbuffer, num_read);
   }
   fclose(infile);
   gzclose(outfile);
   //printf("Read %ld bytes, Wrote %ld bytes, Compression factor %4.2f%%\n", total_read, file_size(outfilename), (1.0-file_size(outfilename)*1.0/total_read)*100.0);
   return 1;
}