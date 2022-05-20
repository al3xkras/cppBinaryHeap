#include <iostream>
#include <cmath>

struct WeightedItem {
public:
    int weight;
    std::string s;

    WeightedItem() : weight(0), s(" ") {};
    WeightedItem(int weight, std::string s) : weight(weight), s(std::move(s)) {}

};
struct BinaryHeap {
public:

    int size;

    WeightedItem* items;

    explicit BinaryHeap(int size){
        this->size=(int)(pow(2,ceil(log2(size)))-1);
        items = new WeightedItem[this->size];
    }



    WeightedItem getLeftChild(int index) const{
        if (2*index+1>=size) {
            return {-1,""};
        }
        return items[2 * index + 1];
    }

    WeightedItem getRightChild(int index) const{
        if (2*index+2>=size) {
            return {-1,""};
        }
        return items[2 * index + 2];
    }

    WeightedItem popMax() const{
        if (items[0].weight == 0)
            return items[0];

        int index = 0;

        WeightedItem max = items[index];
        items[index]=WeightedItem();

        while (index*2<size){
            WeightedItem l = getLeftChild(index);
            WeightedItem r = getRightChild(index);

            if (l.weight==0 && r.weight==0)
                break;

            if (r.weight>=l.weight){
                items[index]=items[2 * index + 2];
                items[2 * index + 2]=WeightedItem();
                index = 2*index+2;
            } else {
                items[index]=items[2 * index + 1];
                items[2 * index + 1]=WeightedItem();
                index = 2*index+1;
            }
        }

        return max;
    }

    void insert(WeightedItem priority) const{

        int index = 0;

        if (items[0].weight == 0){
            items[0]=priority;
            return;
        }

        if (size<=1) {
            std::cerr << "[BinaryHeap is full] " << std::endl;
            throw std::exception();
        }

        bool left_side = false;
        while (getRightChild(index).weight!=0 && getLeftChild(index).weight!=0){

            if (priority.weight<=0) {
                break;
            }

            if (priority.weight > items[index].weight){
                WeightedItem tmp = items[index];
                items[index]=priority;
                priority=tmp;
            }

            WeightedItem priority_r = getRightChild(index);
            WeightedItem priority_l = getLeftChild(index);

            if (priority.weight > priority_r.weight){
                index = 2*index+2;
                items[index] = priority;
                priority = priority_r;
            } else if (priority.weight > priority_l.weight){
                index = 2*index+1;
                items[index] = priority;
                priority = priority_l;
            } else {
                index = 2*index+2;
            }

            if (!left_side && index*2>size){
                left_side = true;
                index = 1;
                if (priority.weight > items[index].weight){
                    WeightedItem tmp = items[index];
                    items[index]=priority;
                    priority=tmp;
                }
                continue;
            } else if (index*2>size){
                std::cerr<<"[BinaryHeap is full] ";
                throw std::exception();
            }

        }

        if (getRightChild(index).weight==0){
            items[2 * index + 2]=priority;
        } else if (getLeftChild(index).weight==0){
            items[2 * index + 1]=priority;
        }

    }

    virtual ~BinaryHeap() {
        delete items;
    }
};

void print_array(WeightedItem* b, int size){
    for (int i=0;i<size;i++){
        std::cout<<" ["<<b[i].weight<<" "<<b[i].s<<"] ";
    }
    std::cout<<std::endl;
}

int main(){

    BinaryHeap b(6);

    b.insert(WeightedItem(25,"fs"));
    print_array(b.items, b.size);

    b.insert(WeightedItem(32,"weffeg"));
    print_array(b.items, b.size);

    b.insert(WeightedItem(2,"ewgaaa"));
    print_array(b.items, b.size);

    b.insert(WeightedItem(1,"gwaeeegw"));
    print_array(b.items, b.size);

    b.insert(WeightedItem(55,"egfew"));
    print_array(b.items, b.size);

    b.insert(WeightedItem(534,"efew"));
    print_array(b.items, b.size);

    b.insert(WeightedItem(789,"4w4f"));
    print_array(b.items, b.size);

    for (int i=0; i<b.size; i++){
        WeightedItem w = b.popMax();
        std::cout<<"Max "<<w.weight<<" "<<w.s<<"   ";
        print_array(b.items, b.size);
    }

}