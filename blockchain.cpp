#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include "SHA256.h"

//Note: this is an implementation of a private blockchain I created just for fun to understand how the technology works
 
using namespace std;
using namespace std::chrono;

struct block
{
    block* prev = nullptr;
    block* next = nullptr;
    string data = "";
    string hashNo = "";
};

int main()
{
    
    // //example of running hash
    // cout << "yo" << endl;
    // SHA256 hasher;
    // cout << hasher.hash("a") << endl;
    // cout << hasher.hash("a") << endl;
    // cout << hasher.hash("b") << endl;

    // block a;
    // a.next = new block;
    // const void* address = static_cast<const void*>(a.next);
    // stringstream ss;
    // ss << address;
    // a.data = ss.str();
    // cout << a.data << endl << a.next << endl;

    block* start = nullptr;

    block aloft;
    start = &aloft;
    aloft.hashNo = "aloft";
    aloft.next = new block;
    aloft.next->prev = start;

    block *curr = aloft.next;
    
    string counter = "1";//this is to show a unique transaction every time lol

    while(true)
    {
        cout << "Current block is connected to the previous block, whose hash was " << curr->prev->hashNo << endl;
        cout << "Transaction number of block = " << counter << endl;
        string total = counter + curr->prev->hashNo;
        int possible_hash = 0;
        curr->data = total;


        while(true)
        {
            auto start = high_resolution_clock::now();
            string attemptHash = total+to_string(possible_hash);
            SHA256 h;
            string temp = h.hash(attemptHash);//couting the attempt hash here looks cool
            cout << attemptHash << endl;
            if(temp[0] == '0' && temp[1] == '0' && temp[2] == '0' && temp[3] == '0' && temp[4] == '0')
            {
                cout << "Hash found! It is " << possible_hash << endl;
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Time taken to mine this block is " << duration.count() << " milliseconds" << endl;
                break;
            }
            possible_hash++;

        }
        cout << "Enter next transaction info to continue, and q to quit" << endl;
        string garbage;
        cin >> garbage;
        curr->hashNo = to_string(possible_hash);
        if(garbage == "q"){break;}



        curr->hashNo = to_string(possible_hash);
        block* abcdefg = new block;
        curr->next = abcdefg;
        abcdefg->prev = curr;
        curr = curr->next;
        counter = garbage;
    
    }



    cout << endl << "FULL BLOCKCHAIN STATS" << endl;

    block *iterate = aloft.next;
    int i = 0;

    while(iterate != nullptr)
    {
        SHA256 h;
        cout << "Block #" << i << endl;
        cout << "Data: " << iterate->data << endl;
        cout << "Hash: " << iterate->hashNo << endl;
        cout << "Hash verification result: " << h.hash(iterate->data + iterate->hashNo) << endl;
        cout << endl;
        iterate = iterate->next;
        i++;
    }

    
}
