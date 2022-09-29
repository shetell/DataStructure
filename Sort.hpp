#include<iostream>
#include<vector>
using namespace std;

/*
插入排序：将待排序序列首个元素插入到已排序序列中该元素应该插入的位置(希尔排序是对序列做不同间隔的插入排序，间隔逐渐缩小)
选择排序：将待排序序列最小/最大的元素插入到已排序序列中最后的位置
交换排序：交换逆序对中的两个元素消除逆序对(冒泡排序、快速排序)
归并排序：逐个访问并比较两个待排序序列各自的某个元素，插入到新序列正确的位置(三个指针)
堆排序：将待排序序列调整为最大/小堆，将堆顶元素与堆底元素交换，这一步实现将堆顶元素放到正确位置，
        再对前面未排序部分做相同操作，已排序序列在后面
比较好的快速排序算法：选择首、尾和中间三个元素的中位数作为pivot，将其放到序列末尾，定义两个指针i和j，i在前j在后，i希望所指
元素小于pivot，j希望所指元素大于pivot。若i满足要求，i向后移动，直到不满足则停止，i停止后j向前移动，不超过i且不满足时则停止，
此时交换i和j所指元素，即可使得i和j重新满足要求，重复上述过程，直到i大于j，此时i的位置即为pivot应该存在的永久位置，将i处元素
与pivot交换即可，这就做完了一趟排序，后续递归解决pivot左右两边的序列即可。
*/

class Sort{
private:
    vector<int>* nums;
    int length;  
    void insertionSort(int gap){
        int temp;
        for(int i = gap+1; i < length; i++){
            temp = nums->at(i);
            int j = i-gap;
            while(j > 0 && nums->at(j) > temp){
                nums->at(j+gap) = nums->at(j);
                j -= gap;
            }
            nums->at(j+gap) = temp;
        }
    }

    void Merge(vector<int>* nums,int Lpos,int Rpos,int REnd){
        vector<int> temp(nums->size());
        int tempPos = Lpos;
        int LEnd = Rpos - 1;
        int NumElements = REnd - Lpos + 1;
        while(Lpos <= LEnd && Rpos <= REnd){
            if(nums->at(Lpos) <= nums->at(Rpos))
                temp[tempPos++] = nums->at(Lpos++);
            else
                temp[tempPos++] = nums->at(Rpos++);
        }
        while(Lpos <= LEnd)temp[tempPos++] = nums->at(Lpos++);
        while(Rpos <= REnd)temp[tempPos++] = nums->at(Rpos++);
        for(int i = 0; i < NumElements; i++ , REnd--){
            nums->at(REnd) = temp[REnd];
        }
    }

    void mergeSort(vector<int>* nums,int Left, int Right){
        int center;
        if(Left < Right){
            center = (Left + Right)/2;
            mergeSort(nums,Left,center);
            mergeSort(nums,center+1,Right);
            Merge(nums,Left,center+1,Right);
        }
    }

    int getPivot(vector<int>* nums, int low, int high){
        int pivot = nums->at(low);
        while(low < high){
            while(low < high && nums->at(high) >= pivot){high--;}
            if(low < high){nums->at(low)=nums->at(high);low++;}
            while(low < high && nums->at(low) <= pivot){low++;}
            if(low < high){nums->at(high)=nums->at(low);high--;}
        }
        nums->at(low) = pivot;
        return low;
    }

    void quickSort(vector<int>* nums,int low,int high){
        if(low >= high)return;
        int pivot = getPivot(nums,low,high);
        quickSort(nums,low,pivot-1);
        quickSort(nums,pivot+1,high);
    }

public: 
    Sort(vector<int>& nums){
        this->nums = &nums;
        this->length = nums.size();
    }

    void print(){
        for(int i = 0; i < nums->size(); i++){
            cout << nums->at(i) << " ";
        }
        cout << endl;
    }

    void InsertionSort(){
        insertionSort(1);
    }

    void ShellSort(){
        int k = 9;
        while(k > 0){
            insertionSort(k);
            k -= 2;
        }
    }

    void smp_selectSort(){
        for(int i = 0; i < length; i++){
            int min_index = i;
            for(int j = i + 1; j < length; j++){
                if(nums->at(j) < nums->at(min_index))min_index = j;
            }
            if(min_index != i){
                int temp = nums->at(i);
                nums->at(i) = nums->at(min_index);
                nums->at(min_index) = temp;
            }
        }
    }

    void MergeSort(){
        mergeSort(this->nums,0,length-1);
    }

    void BubbleSort(){
        int m = length;
        int lastExPos;
        while(m > 1){
            lastExPos = 1;
            for(int j = 0; j < m; j++){
                if(j==m-1)continue;
                if(nums->at(j) > nums->at(j+1)){
                    int temp = nums->at(j);
                    nums->at(j) = nums->at(j+1);
                    nums->at(j+1) = temp;
                    lastExPos = j+1;
                }  
            }
			m = lastExPos;
        }
    }

    void QuickSort(){
        quickSort(nums,0,nums->size()-1);
    }


};