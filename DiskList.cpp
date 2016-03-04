//
//  DiskList.cpp
//  project4
//
//  Created by Binyi Wu on 3/3/16.
//  Copyright © 2016 Binyi Wu. All rights reserved.
//
#include <iostream>
#include "DiskList.h"
using namespace std;

DiskList::DiskList(const std::string& filename)
{
    fn = filename;
    b.createNew(filename);
    b.write(0,0);
    b.close();
}

bool DiskList::push_front(const char* data)
{
    b.openExisting(fn);
    if (strlen(data) >= 256)
        return false;
    int n = b.fileLength();
    int length = strlen(data);
    b.write(data, length,n);
    b.write(length,b.fileLength());
    b.write(n,b.fileLength());
    b.close();
    return true;
}
bool DiskList::remove(const char* data)
{   b.openExisting(fn);
    int sign = 0;
    int n = b.fileLength();
    n=n-4;
    while (n>=4)
    {
        int k,j;
        b.read(k,n);
        b.read(j,n-4);
        char* a = new char[j+1];
        if (!b.read(a,j,k))
            return false;
        else
        {
            if (strcmp(a,data)!=0)
            {
                n=k-4;
                continue;
            }
            else
            {
                int temp;
                b.read(temp,k-4);
                b.write(temp,n);
                b.read(temp,k-8);
                b.write(temp,n-4);
                sign = 1;
            }
        }
        
    }
    b.close();
    return sign;
}
void DiskList::printAll()
{
    b.openExisting(fn);
    int n = b.fileLength();
    n=n-4;
    while (n>=4)
    {
        int k,j;
        b.read(k,n);
        b.read(j,n-4);
        char* a = new char[j];
        if (!b.read(a,j,k))
           cout<<"Error: undefined behavior"<<endl;
        else
            for (int c = 0; c<j; c++)
            {
                cout<<a[c];
            }
        cout<<endl;
        n = k-4;
    }
    b.close();
}
