//
//  DB.hpp
//  TypingTrainer
//
//  Created by 中地功貴 on 2016/02/08.
//  Copyright © 2016年 中地功貴. All rights reserved.
//

#ifndef DB_hpp
#define DB_hpp

#include <iostream>
#include <stdio.h>
#include <vector>

#endif /* DB_hpp */

using namespace std;

class DB
{
protected:
    void Load();
public:
    vector<string> list;
    DB();
    vector<string> getRandom(int count);
};