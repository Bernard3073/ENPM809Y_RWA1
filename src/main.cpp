#include<iostream>
#include<vector>
#include<sstream>
#include<algorithm>

signed int num_parts;
std::vector<int> boxes, part_per_box;
std::vector<int> fill_box;

/**
* @brief Get the total number of parts to be placed in boxes* 
* @return unsigned Number of parts entered by the user
*/
unsigned int get_total_parts();
/**
 * @brief Get the total number of boxes for each type
 * @param <data_structure> Data structure to hold box/part  information
 */
void get_total_boxes(std::vector<int>& boxes);
/**
 * @brief Get the number of parts for each box type
 * @param <data_structure> Data structure to hold box/part information
 */
void get_part_per_box(std::vector<int>& part_per_box);
/**
 * @brief Fill up boxes from user inputs
 * 
 */
void fill_up_boxes(const std::vector<int> &fill_box);


struct s1{
    unsigned int a{};
    unsigned int b{};
};

struct s2{
    unsigned int a{};
    unsigned int b{};
};

struct rwa1{
    s1 member1{};
    s2 member2{};
};

unsigned int get_total_parts(){
    std::cout << "How many parts in total? ";
    bool is_positive = false;
    while(std::cin >> num_parts){
        if(num_parts > 0) break;
        else{
            std::cout << "Please enter a positive number !!!!" << '\n';
            std::cout << "How many parts in total? ";
        }
    }
    return num_parts;
}

void get_total_boxes(std::vector<int>& boxes){
    
    std::string input;
    int num;
    while(true){
        std::cout << "How many boxes for S/M/L/XL? ";
        getline(std::cin, input);
        std::istringstream istr(input);
        while(istr >> num){
            if(num < 0) break;
            boxes.push_back(num);
        }
        if(boxes.size()==4) break;
        else{
            std::cin.clear();
            boxes.clear();
            std::cerr << "Please enter four positive numbers!\n";
        }
    }
}

void get_part_per_box(std::vector<int>& part_per_box){
    std::string input;
    int num;
    while(true){
        std::cout << "How many parts per box for S/M/L/XL? ";
        getline(std::cin, input);
        std::istringstream istr(input);
        while(istr >> num){
            if(num < 0) break;
            part_per_box.push_back(num);
        }
        if(part_per_box.size()==4) break;
        else{
            std::cin.clear();
            part_per_box.clear();
            std::cerr << "Please enter four positive number !\n";
        }
    }
}

void fill_up_boxes(const std::vector<int> &fill_box){
}

std::string box_type(int var){
    switch(var){
        case 3: return "XL"; 
        case 2: return "L";
        case 1: return "M";
        case 0: return "S";
        default: break;
    }
}

int main(){
    num_parts = get_total_parts();
    std::cin.ignore();
    get_total_boxes(boxes);
    get_part_per_box(part_per_box);
    std::cout << "Boxes that can be built with " << num_parts << " pegs:" << '\n';
    std::cout << "-------------------------------------------------" << '\n';
    
    for(int i=boxes.size()-1; i >= 0; i--){
        if(part_per_box[i] > num_parts){
            std::cout << box_type(i) << " box " << "(" << boxes[i] << " x "<< part_per_box[i] << " max) : 0 -- remaining parts: " << num_parts << '\n';
            continue;
        }
        int j = 0;
        while(num_parts > part_per_box[i] && j != boxes[i]){
            num_parts -= part_per_box[i];
            j++;
        }
        std::cout << box_type(i) << " box " << "(" << boxes[i] << " x "<< part_per_box[i] << " max): " << j << " -- remaining parts: " << num_parts << '\n';
    }
    std::cout << "parts not in boxes:" << num_parts << '\n';
    // s1 var1{ 1, 2 };//initialize a and b for s1
    // s2 var2{ 3, 4 };//initialize a and b for s2
    // rwa1 application{var1, var2};//initialize member1 and member2 for rwa1
    // std::cout << application.member1.a << '\n';
    // std::cout << application.member1.b << '\n';
    // std::cout << application.member2.a << '\n';
    // std::cout << application.member2.b << '\n';
}