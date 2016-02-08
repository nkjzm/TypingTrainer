//
//  main.cpp
//  TypingTrainer
//
//  Created by 中地功貴 on 2016/02/08.
//  Copyright © 2016年 中地功貴. All rights reserve/Users/kohki/Projects/TypingTrainer/TypingTrainer/DPMatcher.cppd.
//

//#define __DEBUG

#include <iostream>
#include <chrono>
#include <unistd.h>

#include "DPMatcher.hpp"
#include "DB.hpp"

using namespace std;


int main(int argc, const char * argv[])
{
    int limit = 10;
    
    DB db;
    vector<string> sentense = db.getRandom(limit);
    
    int count = 0;
    int errcount = 0;
    int inputcount = 0;

    std::chrono::system_clock::time_point  start, end; // 型は auto で可
    start = std::chrono::system_clock::now(); // 計測開始時間

    while(true){
        cout << "----------" << endl;
        string A = sentense[count];
        cout << A << endl;
        string B;
        getline(cin,B);
        if(B == ""){
            continue;
        }
        DPMatcher dpMatcher;
        Result res = dpMatcher.match(A, B);
        for(int i=0;i<res.underlines.size();++i){
            cout << res.underlines[i];
        }
        cout << endl;
        for(int i=0;i<res.errors.size();++i){
            cout << res.errors[i];
        }
        cout << endl;
        errcount += res.errcount;
        inputcount += B.length();
        if(++count>=limit){
            break;
        }
        //std::cout << "error:" << res.errcount << endl;
    }
    int score = ((float)inputcount - (float)errcount)/(float)inputcount * 100.0;
    cout << "Score: " << score << "%" << endl;
    
    end = std::chrono::system_clock::now();  // 計測終了時間
    double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count(); //処理に要した時間をミリ秒に変換
    cout << "1文字あたりの平均入力時間: " << elapsed << "[es]" << endl;
    
    return 0;
}
