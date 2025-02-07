#include "FileBlock.h"

FileBlock::FileBlock(unsigned int ID, const std::string& data) : ID(ID), payload(500, 0), checksum(0) {
    set_payload(data); //initialize payload with data
    //initialize 500 bytes in payload with 0, also set checksum to 0
    //call set_payload to initialize it and compute initial checksum
}

unsigned int FileBlock::getID() const{
    return ID;
}

unsigned int FileBlock::compute_checksum() const{
    unsigned int sum = 0;
        for(size_t i = 0; i<payload.size(); i++){
        sum += static_cast<unsigned char>(payload[i]);
    }
    return sum % 256; //return checksum
}

bool FileBlock::validate_checksum() const{
    return compute_checksum()==checksum; //return true if values match means uncorrupted data
}

void FileBlock::set_payload(const std::string& data, bool recompute_checksum){
    std::fill(payload.begin(), payload.end(), 0); //reset payload to 0
    std::copy(data.begin(), data.end(), payload.begin()); //copy data into payload
    if(recompute_checksum){
        //if recompute_checksum true, data uncorrupted
        checksum = compute_checksum(); //update checksum
    }
}
