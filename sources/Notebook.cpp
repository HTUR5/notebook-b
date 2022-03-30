#include "Notebook.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;
using namespace ariel;
using ariel::Direction;


const int row_len = 100;


namespace ariel {
    Notebook::Notebook(){}

    Notebook:: ~Notebook(){}

    void Notebook::write(int page, int row, int col, Direction dir, std::string msg){
        //check the bounds of the notebook
        if(page < 0 || row < 0 || col < 0 || col >= row_len) {
            throw std::invalid_argument("cant write out of notebook bounds");
        }
        if(Direction::Horizontal == dir && (unsigned long)msg.length() + (unsigned long)col > row_len) {
            throw std::invalid_argument("cant write out of notebook bounds");  
        }
        //check the msg is with valid chars
        for(int i = 0; i < msg.length(); i++) {
            char msg_at_i = msg.at((unsigned long)i);
            if(msg_at_i < ' ' || msg_at_i >= '~') {
                throw std::invalid_argument("cant write invalid chars");  
            }
        }
        //Horizontal case
        if(Direction::Horizontal == dir) {
            if(pages[page].count(row) == 0) {
                for(int i = 0; i < row_len; i++) {
                    pages[page][row].push_back('_');
                }
            }
            for(unsigned long i = 0; i < msg.length(); i++) {
                if(pages[page][row].at((unsigned long)col+i) != '_') {
                    throw std::invalid_argument("cant write where it is already writen");
                }
            }
                pages[page][row].replace((unsigned long)col, msg.length(), msg);
        }
        //Vertical case
        if(Direction::Vertical == dir) {
            for(int i = 0; i < msg.length(); i++) {
                if(pages[page].count(row+i) == 0) {
                    for(int j = 0; j < row_len; j++) {
                        pages[page][row+i].push_back('_');
                    }
                 }
            }
            for(int i = 0; i < msg.length(); i++) {
                if(pages[page][row+i].at((unsigned long)col) != '_') {
                    throw std::invalid_argument("cant write where it is already writen");
                }
            pages[page][row+i].replace((unsigned long)col, 1, msg.substr((unsigned long)i,1));
            }
        }
    }

    std::string Notebook::read(int page, int row, int col, Direction dir, int len) {
        if(len < 0 || page < 0 || row < 0 || col < 0 || col >= row_len) {
            throw std::invalid_argument("cant write out of notebook bounds");
        }
        if(Direction::Horizontal == dir && len + col > row_len) {
            throw std::invalid_argument("cant write out of notebook bounds");  
        }
        if(Direction::Horizontal == dir) {
            if(pages[page].count(row) == 0) {
                string defult_str;
                for(int i = 0; i < len; i++) {
                    defult_str.push_back('_');
                }
                return defult_str;
            }
            string str = pages[page][row];
            string r = str.substr((unsigned long)col, (unsigned long)len);
            return r;
        }
        //vetical case
        string str;
        for(int i = 0; i< len; i++) {
            if(pages[page].count(row+i) == 0) {
                str += '_';
            } else {
                str += pages[page][row+i].at((unsigned long)col);
            }
        }
        return str;
    }

    void Notebook::erase(int page, int row, int col, Direction dir, int len){
        if(len< 0 || page < 0 || row < 0 || col < 0 || col >= row_len) {
            throw std::invalid_argument("cant write out of notebook bounds");
        }
        if(Direction::Horizontal == dir && len + col > row_len) {
            throw std::invalid_argument("cant write out of notebook bounds");  
        }
        //Horizontal case
        if(Direction::Horizontal == dir) {
            if(pages[page].count(row) == 0) {
                for(int i = 0; i < row_len; i++) {
                    pages[page][row].push_back('_');
                }
            }
            for(unsigned long i = 0; i < len; i++) {
                pages[page][row].replace((unsigned long)col+i, 1, "~");
            }
        }
        //Vertical case
        if(Direction::Vertical == dir) {
            for(int i = 0; i < len; i++) {
                if(pages[page].count(row+i) == 0) {
                    for(int j = 0; j < row_len; j++) {
                        pages[page][row+i].push_back('_');
                    }
                 }
            }
            for(int i = 0; i < len; i++) {
                pages[page][row+i].replace((unsigned long)col, 1, "~");
            }
        }

    }

    void Notebook::show(int page){
        if(page < 0) {
            throw std::invalid_argument("cant write out of notebook bounds");
        }
        int maxKey = INT_MIN;
        int minKey = INT_MAX;
        for (auto const & key: pages[page]) {
            if(key.first < minKey) {minKey = key.first;}
            if(key.first > maxKey) {maxKey = key.first;}
        }
        if(minKey == INT_MAX) {return;}
        while(minKey <= maxKey) {
            if(pages[page].count(minKey) != 0) {
              std :: cout << minKey << ':' << pages[page][minKey] << endl;  
            }
            minKey++;
        }
    }
}

