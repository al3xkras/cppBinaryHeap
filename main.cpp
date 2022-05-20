#include <iostream>
#include <cmath>

struct BinaryHeap {

public:

    int size;
    int* elements;

    explicit BinaryHeap(int size){
        this->size=(int)(pow(2,ceil(log2(size)))-1);
        elements = new int[this->size];
        for (int i=0; i<this->size;i++)
            elements[i]=0;
    }

    int getLeftChild(int index) const{
        if (2*index+1>=size) return 0;
        return elements[2*index+1];
    }

    int getRightChild(int index) const{
        if (2*index+2>=size) return 0;
        return elements[2*index+2];
    }

    int popMax() const{
        if (elements[0]==0)
            return elements[0];

        int index = 0;

        int max = elements[index];
        elements[index]=0;

        while (index*2<size){
            int l = getLeftChild(index);
            int r = getRightChild(index);

            if (l==0 && r==0)
                break;

            if (r>=l){
                elements[index]=elements[2*index+2];
                elements[2*index+2]=0;
                index = 2*index+2;
            } else {
                elements[index]=elements[2*index+1];
                elements[2*index+1]=0;
                index = 2*index+1;
            }
        }

        return max;
    }

    void insert(int priority) const{

        int index = 0;

        if (elements[0]==0){
            elements[0]=priority;
            return;
        }

        if (size<=1) {
            std::cerr << "[BinaryHeap is full] " << std::endl;
            throw std::exception();
        }

        bool left_side = false;
        while (getRightChild(index)!=0 && getLeftChild(index)!=0){

            if (priority<=0) {
                break;
            }

            if (priority>elements[index]){
                int tmp = elements[index];
                elements[index]=priority;
                priority=tmp;
            }

            int priority_r = getRightChild(index);
            int priority_l = getLeftChild(index);

            if (priority > priority_r){
                index = 2*index+2;
                elements[index] = priority;
                priority = priority_r;
            } else if (priority > priority_l){
                index = 2*index+1;
                elements[index] = priority;
                priority = priority_l;
            } else {
                index = 2*index+2;
            }

            if (!left_side && index*2>size){
                left_side = true;
                index = 1;
                if (priority>elements[index]){
                    int tmp = elements[index];
                    elements[index]=priority;
                    priority=tmp;
                }
                continue;
            } else if (index*2>size){
                std::cerr<<"[BinaryHeap is full] ";
                throw std::exception();
            }

        }

        if (getRightChild(index)==0){
            elements[2*index+2]=priority;
        } else if (getLeftChild(index)==0){
            elements[2*index+1]=priority;
        }

    }

    virtual ~BinaryHeap() {
        delete elements;
    }
};

void print_array(int* b, int size){
    for (int i=0;i<size;i++){
        std::cout<<b[i]<<" ";
    }
    std::cout<<std::endl;
}

int main(){

    BinaryHeap b(6);

    b.insert(25);
    print_array(b.elements,b.size);

    b.insert(5);
    print_array(b.elements,b.size);

    b.insert(25);
    print_array(b.elements,b.size);

    b.insert(10);
    print_array(b.elements,b.size);

    b.insert(30);
    print_array(b.elements,b.size);

    b.insert(40);
    print_array(b.elements,b.size);

    b.insert(4);
    print_array(b.elements,b.size);

    for (int i=0; i<b.size; i++){
        std::cout<<"Max "<<b.popMax()<<"   ";
        print_array(b.elements,b.size);
    }

    std::cout<<b.getLeftChild(0)<<std::endl;
}