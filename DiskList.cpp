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
    char c = ' ';
    b.write(DiskNode(&c,0),0);
    b.close();
}

bool DiskList::push_front(const char* data)
{
    if (!b.openExisting(fn))
    {   cout<<"Warning: File does not exist<<endl;"<<endl;
        return false;
    }
    if (strlen(data) >= 256)
        return false;
    int n = b.fileLength();
    char* temp= new char[strlen(data)+1];
    DiskNode D = DiskNode("", 0);
    DiskNode head = DiskNode("",0);
    b.read(head,0);
    strcpy(temp,data);
    temp[strlen(data)] = '\0';
    b.write(DiskNode(temp,head.next),n);
    b.write(DiskNode(head.data,n),0);
    b.close();
    return true;
}
bool DiskList::remove(const char* data)
{
    if (!b.openExisting(fn))
    {   cout<<"Warning: File does not exist<<endl;"<<endl;
        return false;
    }
    int sign = 0;
    BinaryFile::Offset prev = 0;
    DiskNode current = DiskNode("",0);
    b.read(current,0);
    while(current.next!=0)
    {
        DiskNode nt = DiskNode("",0);
        b.read(nt,current.next);
        if (strcmp(nt.data,data)!=0)
        {
            prev = current.next;
            current = nt;
            
        }
        else
        {   b.write(DiskNode(current.data,nt.next),prev);
            prev = current.next;
            b.read(current,current.next);
            sign = 1;
        }
    }

    b.close();
    return sign;
}
void DiskList::printAll()
{
    if (!b.openExisting(fn))
    {   cout<<"Warning: File does not exist<<endl;"<<endl;
        return;
    }

    DiskNode d = DiskNode("",0);
    b.read(d,0);
    while (d.next != 0)
    {   b.read(d,d.next);
        int i=0;
        while (d.data[i] != '\0')
        {    cout<<d.data[i];
            i++;
        }
        cout<<endl;
    }
    
    
    b.close();
}
