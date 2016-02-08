//
//  DB.cpp
//  TypingTrainer
//
//  Created by 中地功貴 on 2016/02/08.
//  Copyright © 2016年 中地功貴. All rights reserved.
//

#include "DB.hpp"
#include <fstream>

DB::DB(){
    Load();
}

void DB::Load(){
    std::ifstream ifs("../../../../../scraping/data.txt");
    std::string str;
    if (ifs.fail())
    {
        std::cerr << "失敗" << std::endl;
        return;
    }
    while (getline(ifs, str))
    {
        list.push_back(str);
    }
    
    cout << list.size() << endl;
    
    //重複を削除
    std::sort(list.begin(), list.end());
    list.erase(std::unique(list.begin(), list.end()), list.end());
    
    cout << list.size() << endl;
}

vector<string> DB::getRandom(int count)
{
    srand( (unsigned int)time( NULL ) );
    vector<string> pickup;
    while (true) {
        int index = rand() % list.size();
        pickup.push_back(list[index]);
        
        //重複を削除
        std::sort(pickup.begin(), pickup.end());
        pickup.erase(std::unique(pickup.begin(), pickup.end()), pickup.end());

        if(pickup.size() == count){
            break;
        }
    }
    return pickup;
}
