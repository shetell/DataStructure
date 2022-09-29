#include<vector>
#include<iostream>
using namespace std;

class MyHashMap {
public:

    vector<int> Key;
    vector<int> Value;

    MyHashMap() {}
    
    bool contains(int key){
        int index = find(Key.begin(),Key.end(),key) - Key.begin();
        return (index >= 0) && (index < Key.size());
    }

    auto index(int key){
        return find(Key.begin(),Key.end(),key) - Key.begin();
    }

    void put(int key, int value) {
        if(!contains(key)){
            Key.push_back(key);
            Value.push_back(value);
        }
        else{
            auto it = index(key);
            Value[it] = value;
        }
    }
    
    int get(int key) {
        if(!contains(key)){
            return -1;
        }
        else{
            auto it = index(key);
            return Value[it]; 
        }
    }
    
    void remove(int key) {
        if(!contains(key)){
            return;
        }
        else{
            auto it = index(key);
            Key.erase(it+Key.begin());
            Value.erase(it+Value.begin());
        }
    }
};