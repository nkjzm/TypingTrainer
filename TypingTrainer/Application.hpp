//
//  Application.hpp
//  TypingTrainer
//
//  Created by 中地功貴 on 2016/02/08.
//  Copyright © 2016年 中地功貴. All rights reserved.
//

#ifndef Application_hpp
#define Application_hpp

#include <stdio.h>
#include <chrono>
#include <unistd.h>

#include "DPMatcher.hpp"
#include "DB.hpp"

#endif /* Application_hpp */

class Application{
protected:
    DB db;
    int limit = 10;
public:
    Application();
    void train();
    string GetEvaluation(float rate);
};