/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: rohit
 *
 * Created on July 8, 2016, 10:35 PM
 */

#include <cstdlib>
#include "ConfigLib.hpp"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    system("pwd");
    
    ConfigLib conf("settings.txt");
//    cout<<conf.get("Nc")<<endl;
//    cout<<conf.get("car")<<endl;
//    cout<<conf.get("")<<endl;
//    cout<<conf.get("num_probes")<<endl;
    
    conf.put("car", "maruti");
    conf.put("house", "clean");
    conf.write();
    conf.overwrite("settings_final.txt");

    return 0;
}

