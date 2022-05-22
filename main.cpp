#include <iostream>
#include <cmath>



struct WeightedItem {
public:
    int weight;
    std::string s;

    WeightedItem() : weight(0), s(" ") {};
    WeightedItem(int weight, std::string s) : weight(weight), s(std::move(s)) {}

    bool operator==(const WeightedItem &rhs) const {
        return weight == rhs.weight;
    }

    bool operator!=(const WeightedItem &rhs) const {
        return !(rhs == *this);
    }
};

void print_array(WeightedItem* b, int size){
    for (int i=0;i<size;i++){
        std::cout<<" ["<<b[i].weight<<" "<<b[i].s<<"] ";
    }
    std::cout<<std::endl;
}

struct BinaryHeap {
public:

    WeightedItem none{-1,""};
    WeightedItem zero{0,""};

    int size;
    WeightedItem* items;

    explicit BinaryHeap(int size){
        this->size=(int)(pow(2,ceil(log2(size)))-1);
        items = new WeightedItem[this->size];
        for (int i=0;i<this->size;i++){
            items[i]=zero;
        }
    }

    static int rightIndex(int index){
        return 2*index+2;
    }

    static int leftIndex(int index){
        return 2*index+1;
    }

    static bool isLeftChild(int index){
        return (index&1)==1;
    }

    static bool isRightChild(int index){
        return (index&1)==0;
    }

    static int parentIndex(int index){
        return ((index&1) == 0)
            ? index/2-1
            : index/2;
    }

    WeightedItem& get(int index){
        if (index>=size){
            return none;
        } else if (items[index].weight==0){
            return zero;
        }
        return items[index];
    }

    WeightedItem& getLeftChild(int index){
        int i = leftIndex(index);
        if (i>=size) {
            return none;
        }
        return items[i];
    }

    WeightedItem& getRightChild(int index){
        int i = rightIndex(index);
        if (i>=size) {
            return (none);
        }
        return items[i];
    }

    WeightedItem& getParent(int index){
        if (index==0){
            return none;
        }
        return items[parentIndex(index)];
    }

    bool checkAndSwap(int index, WeightedItem* item) const{
        if (index>size) return false;
        if ((*item).weight>items[index].weight){
            WeightedItem tmp = items[index];
            items[index]=*item;
            (*item) = tmp;
            return true;
        }
        return false;
    }

    void insert(WeightedItem& item) {

        int index = 0;

        while (item!=zero) {

            WeightedItem current = get(index);

            if (current==none){

                index = parentIndex(index);

                if (isRightChild(index)){
                    index = leftIndex(parentIndex(index));
                } else {

                    while (isLeftChild(index)){
                        index = parentIndex(index);
                    }
                    index = leftIndex(parentIndex(index));

                }

                checkAndSwap(index, &item);

                if (get(index)==none){
                    std::cerr<<"full";
                    return;
                }

                continue;

            } else if (current==zero) {
                items[index]=item;
                break;
            }

            checkAndSwap(index, &item);
            checkAndSwap(rightIndex(index), &item);
            checkAndSwap(leftIndex(index), &item);

            index = rightIndex(index);
        }
    }

    void setPriority(int index, int priority){

        WeightedItem current = get(index);

        if (current==none || current==zero){
            std::cerr<<"\nno item with index "<<index<<" found\n";
            return;
        }

        if (size==1 || index==0 && getLeftChild(0)==zero && getRightChild(0)==zero){
            items[0].weight=priority;
            return;
        }

        current.weight = priority;

        WeightedItem parent;
        WeightedItem left;
        WeightedItem right;

        do {

            parent = getParent(index);
            left = getLeftChild(index);
            right = getRightChild(index);

            if (parent!=none && current.weight>parent.weight) {

                items[index] = parent;
                index = parentIndex(index);

            } else if ( (right!=none && right.weight > current.weight) ||
                        (left!=none && left.weight > current.weight) ){

                if ( left!=none && (right==none || left.weight>right.weight) ){
                    items[index] = left;
                    index = leftIndex(index);
                } else {
                    items[index] = right;
                    index = rightIndex(index);
                }

            } else {

                break;

            }

            items[index]=current;

        } while (true);


    }

    WeightedItem popMax() {

        WeightedItem max = get(0);

        WeightedItem max_copy{max.weight,max.s};

        setPriority(0,0);

        if (max.weight==0){
            std::cerr<<"binary heap is empty";
            throw std::exception();
        }

        return max_copy;
    }

};



int main(){

    /*BinaryHeap b(30000);


    std::ifstream is("input.txt");

    std::string command;

    while (is>>command){
        if (command=="ADD"){
            std::string s;
            is>>s;

            int p;
            is>>p;

            b.insert({p,s});

        } else if (command=="POP") {
            WeightedItem item = b.popMax();
            std::cout<<item.s<<" "<<item.weight<<std::endl;
        } else if (command=="CHANGE") {
            std::string str;
            is >> str;

            int priority;
            is >> priority;
            int i;
            for (i=0; i<b.size; i++){
                if (b.items[i].s == str) break;
            }
            b.setPriority(i, priority);
        }

        //print_array(b.items,3);
    }*/

    //is.close();
    BinaryHeap b(512);

    for (int i=0; i<b.size; i++){
        WeightedItem w = WeightedItem(i/2 + 10 + i*i +1,"");
        b.insert(w);
        //b.setPriority(i/2 + i/3,2*i+34);
        //print_array(b.items,b.size);
        //std::cout<<(5+i)*204 + i/2 + i*i<<std::endl;
    }

    WeightedItem w = WeightedItem(3451,"");

    for (int i=0; i<b.size; i++){
        WeightedItem max = b.popMax();

        std::cout<<max.weight<<" "<<max.s<<std::endl;
        //print_array(b.items,b.size);
    }

}