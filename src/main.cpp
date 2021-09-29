/**
 * @file main.cpp
 * @author Bo-Shiang Wang (bwang24@umd.edu)
 * @brief 
 * @version 0
 * @date 2021-09-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include<iostream>
#include<vector>
#include<sstream>
#include<algorithm>

unsigned int total_parts;
unsigned int remaining_parts;
std::vector<int> boxes, part_per_box;
std::vector<std::pair<int, int>> fill_box;

/**
* @brief Get the total number of parts to be placed in boxes* 
* @return unsigned Number of parts entered by the user
*/
unsigned int get_total_parts();
/**
 * @brief Get the total number of boxes for each type
 * @param std::vector<int> Data structure to hold box/part information
 */
void get_total_boxes(std::vector<int>& boxes);
/**
 * @brief Get the number of parts for each box type
 * @param std::vector<int> Data structure to hold box/part information
 */
void get_part_per_box(std::vector<int>& part_per_box);
/**
 * @brief Fill up boxes from user inputs
 * @param std::vector<std::pair<int, int>> Data structure to hold box/part information
 */
void fill_up_boxes(const std::vector<std::pair<int, int>> &fill_box);
/**
 * @brief check the type of box
 * 
 * @param var box number
 * @return std::string for box type
 */
std::string box_type(int var);


unsigned int get_total_parts(){
    std::cout << "How many parts in total? ";
    bool is_positive = false;
    // read input from the terminal and check if it is valid
    while(std::cin >> total_parts){
        if(total_parts > 0) break;
        else{
            std::cout << "Please enter a positive number !!!!" << '\n';
            std::cout << "How many parts in total? ";
        }
    }
    return total_parts;
}

void get_total_boxes(std::vector<int>& boxes){
    
    std::string input;
    int num;
    // read input from the terminal and check if it is valid
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
    // read input from the terminal and check if it is valid
    while(true){
        std::cout << "How many parts per box for S/M/L/XL? ";
        getline(std::cin, input);
        std::istringstream istr(input);
        while(istr >> num){
            if(num < 0){
                std::cerr << "Please enter four positive number !\n";
                break;
            }
            bool flag = true;
            // check if the parts per box is in ascending order
            if(!part_per_box.empty()){
                int parts_max = part_per_box[3];
                for(int i=0; i < part_per_box.size()-1; i++){
                    if(part_per_box[i] >= part_per_box[i+1]) flag = false;
                }
            }
            if(flag == false){
                std::cout << "parts per box should be ascending order for S/M/L/XL !!!" << '\n';
                break;
            }
            part_per_box.push_back(num);
        }
        if(part_per_box.size()==4) break;
        else{
            std::cin.clear();
            part_per_box.clear();        
        }
    }
}

void fill_up_boxes(const std::vector<std::pair<int, int>> &fill_box){
    std::cout << "Boxes that can be built with " << total_parts << " pegs:" << '\n';
    std::cout << "-------------------------------------------------" << '\n';
    int n = fill_box.size();
    for(int i=n-1; i>=0; i--){
        std::cout << box_type(i) << " box " << "(" << boxes[i] << " x "<< part_per_box[i] << " max): " << fill_box[n-1-i].first << " -- remaining parts: " << fill_box[n-1-i].second << '\n';
    }
    std::cout << "parts not in boxes:" << remaining_parts << '\n';
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
    // call function to get total number of parts
    total_parts = get_total_parts();
    std::cin.ignore();
    // call function to get total number of boxes of each type 
    get_total_boxes(boxes);
    // call function to get the max number of parts per box type
    get_part_per_box(part_per_box);

    // insert values inside fill_box
    remaining_parts = total_parts;
    for(int i=boxes.size()-1; i >= 0; i--){
        if(part_per_box[i] > remaining_parts){
            fill_box.push_back(std::make_pair(0, remaining_parts));
            continue;
        }
        int j = 0;
        while(remaining_parts > part_per_box[i] && j != boxes[i]){
            remaining_parts -= part_per_box[i];
            j++;
        }
        fill_box.push_back(std::make_pair(j, remaining_parts));
    }

    // call function to fill up boxes and to display result
    fill_up_boxes(fill_box);
}