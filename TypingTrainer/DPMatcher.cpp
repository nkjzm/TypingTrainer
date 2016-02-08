//
//  DPMatcher.cpp
//  TypingTrainer
//
//  Created by 中地功貴 on 2016/02/08.
//  Copyright © 2016年 中地功貴. All rights reserved.
//

#include "DPMatcher.hpp"

DPMatcher::DPMatcher()
    {
        errorChars.insert(pair<string,string>("inserted",   "I"));
        errorChars.insert(pair<string,string>("deleted",    "D"));
        errorChars.insert(pair<string,string>("substituted","S"));
        errorChars.insert(pair<string,string>("mixed",      "*"));
    }
Result DPMatcher::match(string expected, string input)
    {
        int ysize = (int)expected.length();
        int xsize = (int)input.length();
        
        int score[xsize+1][ysize+1];
        
        vector<vector<Point>> vector (xsize+1, std::vector<Point>(ysize+1));
        
        score[0][0] = 0;
        for (int y = 1; y <= ysize; ++y) {
            score[0][y] = y;
            vector[0][y] = Point(0,y - 1);
        }
        for (int x = 1; x <= xsize; ++x) {
            score[x][0] = x;
            vector[x][0] = Point(x - 1, 0);
        }
        
        for (int x = 1; x <= xsize; ++x) {
            for (int y = 1; y <= ysize; ++y) {
                
                int mx, my,rate;
                
                char e = (y-1)<ysize ? expected[y - 1] : ' ';
                char i = (x-1)<xsize ? input[x - 1] : ' ';
                int incorrect = (int)(bool)(e != i);
                int min = std::min(
                                   score[x - 1][y - 1] + (2 * incorrect),
                                   score[x - 1][y] + incorrect
                                   );
                min = std::min(min,
                               score[x][y - 1] + incorrect
                               );
                if (min == score[x - 1][y - 1] + (2 * incorrect)) {
                    mx = x - 1;
                    my = y - 1;
                    rate = 2;
                } else if (min == score[x - 1][y] + incorrect) {
                    mx = x - 1;
                    my = y;
                    rate = 1;
                } else {
                    mx = x;
                    my = y - 1;
                    rate = 1;
                }
                score[x][y] = score[mx][my] + (incorrect * rate);
                vector[x][y] = Point(mx,my);
            }
        }
        
#ifdef __DEBUG
        for (int x = 0; x <= xsize; ++x) {
            for (int y = 0; y <= ysize; ++y) {
                cout << "(" << score[x][y] << ")";
            }
            cout << endl;
        }
#endif
        
        Result result(xsize + 1);
        
        int x = xsize, y = ysize;
        while (true) {
            
            if(x ==  0 && y == 0){
                break;
            }
            Point v = vector[x][y];
            
#ifdef __DEBUG
            std::cout << "x:" << x << ", y:" << y << ", v.x:" << v.x << ", v.y:" << v.y <<"\n";
#endif
            
            if (x != v.x && y == v.y) {
                result.underlines[x - 1] = "~";
                result.errors[x - 1] = errorChars[(result.errors[x - 1] != " " ? "mixed" : "inserted")];
                ++result.errcount;
            } else if (x == v.x && y != v.y) {
                result.errors[x] = errorChars[(result.errors[x] != " " ? "mixed" : "deleted")];
                ++result.errcount;
            } else if (x != v.x && y != v.y && score[x][y] != score[v.x][v.y]) {
                result.underlines[x - 1] = "~";
                result.errors[x - 1] = errorChars[(result.errors[x - 1] != " " ? "mixed" : "substituted")];
                ++result.errcount;
            }
            
            x = v.x, y = v.y;
            
        }
        
        return result;
    }
 

