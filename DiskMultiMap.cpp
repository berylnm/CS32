//
//  DiskMultiMap.cpp
//  pj4
//
//  Created by Binyi Wu on 3/5/16.
//  Copyright © 2016 Binyi Wu. All rights reserved.
//

#include "DiskMultiMap.h"
#include "BinaryFile.h"
#include <iostream>
using namespace std;

DiskMultiMap::DiskMultiMap(){}
DiskMultiMap::~DiskMultiMap(){}

bool DiskMultiMap::createNew(const std::string& filename, unsigned int numBuckets)
{
    if (b.createNew(filename))
    {
        b.write(numBuckets,0);
        b.write(0,b.fileLength());
        return true;
    }
    return false;
}

bool DiskMultiMap::openExisting(const std::string &filename)
{
    if (!b.openExisting(filename))
        return false;
    return true;
}

void DiskMultiMap::close()
{
    b.close();
}
bool DiskMultiMap::insert(const std::string& key, const std::string& value, const std::string& context)
{
    if (key.size() > 120 || value.size() > 120 || context.size() > 120)
        return false;
    else
}
