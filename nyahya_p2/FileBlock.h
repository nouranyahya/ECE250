#ifndef FILEBLOCK_H
#define FILEBLOCK_H

#include <string>
#include <vector>

class FileBlock{
private:
    unsigned int ID;              //unique ID of file block
    std::vector<char> payload;    //payload data up to 500 characters
    unsigned int checksum;        

public:
    FileBlock(unsigned int ID, const std::string& data); //constructor
    unsigned int getID() const;    //return ID of file block
    unsigned int compute_checksum() const;  //compute and return checksum
    bool validate_checksum() const;
    void set_payload(const std::string& data, bool recomputeChecksum = true); //sets payload data
};
#endif
