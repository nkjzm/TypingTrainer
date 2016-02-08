//
//  Application.cpp
//  TypingTrainer
//
//  Created by 中地功貴 on 2016/02/08.
//  Copyright © 2016年 中地功貴. All rights reserved.
//

#include "Application.hpp"

Application::Application()
{
    while (true) {
        cout << "==========" << endl;
        cout << "コマンドを入力してください。" << endl;
        cout << "## 終了\t:0" << endl;
        cout << "## 開始\t:1" << endl;
        string num;
        while(true){
            cout << "コマンド: ";
            getline(cin,num);
            if(num == "0"){
                return;
            }else if(num == "1"){
                train();
                break;
            }else{
                cout << "正しい数字を入力してください。" << endl;
            }
        }
    }
}

void Application::train()
{
    vector<string> sentense = db.getRandom(limit);
    
    int count = 0;
    int errcount = 0;
    int inputcount = 0;
    
    setbuf(stdout, NULL);
    
    for(int i=3;i>0;--i){
        cout << "トレーニング開始まで…" << i << endl;
        sleep( 1 );
    }
    cout << "スタート!" << endl;
    
    std::chrono::system_clock::time_point  start, end; // 型は auto で可
    start = std::chrono::system_clock::now(); // 計測開始時間
    
    while(true){
        cout << "----------" << endl;
        usleep(200000);
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
        
        //途中経過表示
        string eva = GetEvaluation((float)(A.length() - res.errcount) / (float)A.length());
        std::cout << "[" << A.length() - res.errcount << "/" << A.length() << "]" << eva << endl;
        
        //最終結果用
        errcount += res.errcount;
        inputcount += B.length();
        
        if(++count>=limit){
            break;
        }
    }
    int score = ((float)inputcount - (float)errcount)/(float)inputcount * 100.0;
    cout << "Score: " << score << "%" << endl;
    
    end = std::chrono::system_clock::now();  // 計測終了時間
    double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count(); //処理に要した時間をミリ秒に変換
    cout << "1文字あたりの平均入力時間: " << elapsed << "[ms]" << endl;
}

string Application::GetEvaluation(float rate)
{
    if(rate >= 1){
        return "\t # Perfect";
    }else if(rate>0.8){
        return "\t # Good";
    }else if(rate>0.6){
        return "\t # OK";
    }else{
        return "\t # BAD";
    }
}