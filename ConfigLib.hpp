/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConfigLib.hpp
 * Author: rohit
 *
 * Created on July 8, 2016, 10:36 PM
 */

#pragma once

#ifndef CONFIGLIB_HPP
#define CONFIGLIB_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <map>

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

using namespace std;

class ConfigLib {
public:
    ConfigLib(const string &filename) {
        fname = filename;
        file.open(fname.c_str(), ios::in);
        if(!file) {
            exists = false;
            cout<<"Config file "<<fname<<" not found.\n";
        } else {
            exists = true;
        }
        if(exists) {
            while(file) {
                file.getline(buf, sizeof(buf)-1);
                //cout<<buf<<endl;
                parse();
            }
            file.close();
        }
    }
    
    string get(string key) {
        return store[key];
    }
    
    void put(string key, string value) {
        store[key] = value;
    }
    
    void write() {
        if(exists) {
            cout<<"Cannot overwrite an existing file."<<endl;
            return;
        }
        overwrite(fname);
    }
    
    void overwrite(string new_fname) {
        file.open(new_fname.c_str(), ios::out);
        if(!file) {
            cout<<"Unable to save to "<<new_fname<<endl;
        } else {
            cout<<"Created fresh Config in "<<new_fname<<endl;
        }
        for(std::map<string,string>::iterator it = store.begin(); it != store.end(); it++) {
            cout<<it->first<<"="<<it->second<<endl;
            file<<it->first<<"="<<it->second<<endl;
        }
        file.close();
    }
private:
    fstream file;
    string fname;
    bool exists;
    char buf[1024];
    
    map<string,string> store;
    
    void parse() {
        string key, value;
        bool k=true;
        int start = 0;
        for(int i=0; i<sizeof(buf) && buf[i]!='\0'; i++) {
            if(buf[i]==' ') {
                continue;
            } else {
                start = i;
                break;
            }
        }
        if(buf[start]=='#') {
            return;
        }
        for(int i=start; i<sizeof(buf) && buf[i]!='\0'; i++) {
            if(buf[i]=='#') {
                break;
            }
            if(k && buf[i]=='=') {
                k=false;
                i++;
            }
            if(k) {
                key.push_back(buf[i]);
            } else {
                value.push_back(buf[i]);
            }
        }
        trim(key);
        trim(value);
        if(key.length()==0) {
            return;
        }
        cout<<key<<" : "<<value<<endl;
        store[key] = value;
    }
};

#endif /* CONFIGLIB_HPP */
