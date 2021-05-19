#ifndef _FILE_LISTER_H_
#define _FILE_LISTER_H_

#include <vector>
#include <string>
#include <SDL.h>
#include "sdlutils.h"

// Class used to store file info
struct T_FILE
{
    // Constructor
    T_FILE(void):
        m_name(""),
        m_size(0),
        m_textureNormal(NULL)
    {}

    // Constructor
    T_FILE(const std::string &p_name, const unsigned long int &p_size):
        m_name(p_name),
        m_size(p_size),
        m_textureNormal(NULL)
    {}

    // Copy constructor
    T_FILE(const T_FILE &p_source):
        m_name(p_source.m_name),
        m_size(p_source.m_size),
        m_textureNormal(NULL)
    {}

    // Operator =
    const T_FILE &operator =(const T_FILE &p_source)
    {
        m_name = p_source.m_name;
        m_size = p_source.m_size;
        m_textureNormal = NULL;
        return *this;
    }

    // Destructor
    ~T_FILE(void)
    {
        if (m_textureNormal != NULL)
        {
            SDL_DestroyTexture(m_textureNormal);
            m_textureNormal = NULL;
        }
    }

    // File attributes
    std::string m_name;
    unsigned long int m_size;
    SDL_Texture *m_textureNormal;
};

class CFileLister
{
    public:

    // Constructor
    CFileLister(void);

    // Destructor
    virtual ~CFileLister(void);

    // Read the contents of the given path
    // Returns false if the path does not exist
    const bool list(const std::string &p_path);

    // Get an element in the list (dirs and files combined)
    const T_FILE &operator[](const unsigned int p_i) const;

    // Get the number of dirs/files
    const unsigned int getNbDirs(void) const;
    const unsigned int getNbFiles(void) const;
    const unsigned int getNbTotal(void) const;

    // True => directory, false => file
    const bool isDirectory(const unsigned int p_i) const;

    // Get index of the given dir name, 0 if not found
    const unsigned int searchDir(const std::string &p_name) const;

    private:

    // Forbidden
    CFileLister(const CFileLister &p_source);
    const CFileLister &operator =(const CFileLister &p_source);

    // The list of files/dir
    std::vector<T_FILE> m_listDirs;
    std::vector<T_FILE> m_listFiles;
};

#endif