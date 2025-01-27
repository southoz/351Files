#ifndef _FILEUTILS_H_
#define _FILEUTILS_H_

#include <vector>
#include <string>

namespace FileUtils
{

//------------------------------------------------------------------------------
   // File operations
//------------------------------------------------------------------------------

   // Copy files to dest dir
   void copyFiles(const std::vector<std::string> &p_src, const std::string &p_dest);

   // Move files to dest dir
   void moveFiles(const std::vector<std::string> &p_src, const std::string &p_dest);

   // Remove files
   void removeFiles(const std::vector<std::string> &p_files);

   // Create new directory
   void makeDirectory(const std::string &p_file);

   // Rename a file
   void renameFile(const std::string &p_file1, const std::string &p_file2);

//------------------------------------------------------------------------------
   // File utilities
//------------------------------------------------------------------------------

   // Format file size to human readable (K, M, G)
   std::string formatSize(const unsigned long long int &p_size);

   // Lower case file extension
   std::string getLowercaseFileExtension(const std::string &p_name);

   // File exists?
   bool fileExists(const std::string &p_path);

   // Extract file name from a path
   std::string getFileName(const std::string &p_path);

   // Extract dir name from a path
   std::string getDirName(const std::string &p_path);

   // Dir size
   unsigned long long int getDirSize(const std::string &p_path);

   // File is text
   bool fileIsText(const std::string &p_path);

}

#endif
