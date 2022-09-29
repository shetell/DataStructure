#include<iostream>
#include<vector>
using namespace std;

class Heap{
private:
    void PercDown(int i){
        int parent,child;
        int temp = heap[i];
        for(parent = i; parent*2 <= heap.size(); parent = child){
            child = parent * 2;
            if(child != heap.size() && heap[child] < heap[child + 1])child++;//从左右儿子中找出大的和自身比较，决定去向
            if(temp >= heap[child])break;
            else heap[parent] = heap[child];
        }
        heap[parent] = temp;
    }
public:
    vector<int> heap;
    Heap(vector<int>& nums){
        heap = {100};
        for(int i = 0;i < nums.size();i++){
            heap.push_back(nums[i]);
        }
        for(int i = (heap.size()-1)/2; i > 0 ; i--){
            PercDown(i);//从最后一个有子节点的节点开始调整为局部堆，再向前做同样的操作，过滤过程就是调整过程
        }
        heap.erase(heap.begin());
    }

    void Insert(int val){
        int i = heap.size();
        for(;heap[i] < val && i > 1;i /= 2)heap[i] = heap[i/2];//这一步for循环找出插入位置
        heap[i] = val;
    }

    int PopMax(){
        int max = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        PercDown(0);
        return max;
    }

};