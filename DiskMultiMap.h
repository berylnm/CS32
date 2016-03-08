//
//  DiskMultiMap.hpp
//  pj4
//
//  Created by Binyi Wu on 3/5/16.
//  Copyright © 2016 Binyi Wu. All rights reserved.
//

#ifndef DISKMULTIMAP_H_
#define DISKMULTIMAP_H_

#include <string>
#include "BinaryFile.h"
#include "MultiMapTuple.h"

class DiskMultiMap
{
public:
    
    class Iterator
    {
    public:
        Iterator();
        // You may add additional constructors
        bool isValid() const;
        Iterator& operator++();
        MultiMapTuple operator*();
        
    private:
        // Your private member declarations will go here
    };
    
    DiskMultiMap();
    ~DiskMultiMap();
    bool createNew(const std::string& filename, unsigned int numBuckets);
    bool openExisting(const std::string& filename);
    void close();
    bool insert(const std::string& key, const std::string& value, const std::string& context);
    Iterator search(const std::string& key);
    int erase(const std::string& key, const std::string& value, const std::string& context);
    
private:
    // Your private member declarations will go here
    BinaryFile b;
    struct DiskNode
    {
        MultiMapTuple m;
        int next;
    };
};

#endif // DISKMULTIMAP_H_