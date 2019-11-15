#include <iostream>

using namespace std;

class FoodItem {
    private:
        long long UPCcode;
        string description;

    public:
        FoodItem(){
            UPCcode = 0;
            description = "";
        }
        long long getUPCcode() const{
            return UPCcode;
        }
        string getDescription() const{
            return description;
        }
        void setUPC(long long code){UPCcode = code;};

        void setDescription(string desc){description = desc;};
        friend bool operator<(const FoodItem& oneItem, const FoodItem& otherItem){
            if(oneItem.UPCcode < otherItem.UPCcode)
                return 1;
            return 0;
        }
        friend bool operator>(const FoodItem& oneItem, const FoodItem& otherItem){
            if(oneItem.UPCcode > otherItem.UPCcode)
                return 1;
            return 0;
        }
        friend bool operator==(const FoodItem& oneItem, const FoodItem& otherItem){
            if(oneItem.UPCcode == otherItem.UPCcode)
                return 1;
            return 0;
        }
        friend bool operator!=(const FoodItem& oneItem, const FoodItem& otherItem){ 
            return !(oneItem == otherItem);
        }
        friend ostream& operator<<(ostream& os, const FoodItem& item){
            os<<item.UPCcode<<": "<<item.description<<endl;
            return os;
        }

};