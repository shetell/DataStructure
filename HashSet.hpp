#include<iostream>
#include<vector>
#include<algorithm>
using namespace std; 

class MyHashSet {
public:
	vector<int> keys;
    MyHashSet() {
		
    }
    
    void add(int key) {
        if(!contains(key)){
		    keys.push_back(key);
        }
    }
    
    void remove(int key) {
        if(contains(key)){
            auto index = find(keys.begin(),keys.end(),key);
            keys.erase(index);
        }
    }
    
    bool contains(int key) {
        int index = find(keys.begin(),keys.end(),key)- keys.begin();
        return (index >= 0) && (index < keys.size());
    }

    void printKeys(){
        for(int i = 0; i < keys.size(); i++){
            cout << keys[i] << " " ;
        }
        cout << endl;
    }

};

int main(){
    MyHashSet* obj = new MyHashSet();
    obj->add(1);
    obj->add(2);
    cout << obj->contains(1) << endl;
    cout << obj->contains(3) << endl;
    obj->add(2);
    cout << obj->contains(2) << endl;
    obj->remove(2);
    cout << obj->contains(2) << endl;
    int a;
    cin >> a ;
    return 0;
}
