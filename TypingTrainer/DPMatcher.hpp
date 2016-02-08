//
//  DPMatcher.hpp
//  TypingTrainer
//
//  Created by 中地功貴 on 2016/02/08.
//  Copyright © 2016年 中地功貴. All rights reserved.
//

#ifndef DPMatcher_hpp
#define DPMatcher_hpp

#include <iostream>
#include <strings.h>

#include <map>
#include <vector>

using namespace std;

#endif /* DPMatcher_hpp */

struct Point{
public:
    int x;
    int y;
    Point(){}
    Point(int _x,int _y)
    {
        x = _x;
        y = _y;
    }
};

struct Result{
public:
    vector<string> underlines;
    vector<string> errors;
    int errcount = 0;
    Result(int size)
    {
        underlines.resize(size);
        errors.resize(size);
        for(int i=0;i<size;++i){
            underlines[i] = " ";
            errors[i] = " ";
        }
    }
};

class DPMatcher{
private:
    map <string, string> errorChars;
public:
    DPMatcher();
    Result match(string expected, string input);
};
