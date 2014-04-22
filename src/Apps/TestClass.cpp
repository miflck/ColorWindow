//
//  ScreenSaver.cpp
//  ColorWindows
//
//  Created by Michael Flueckiger on 06.09.12.
//  Copyright (c) 2012 Ich. All rights reserved.
//

#include <iostream>
#include "TestClass.h"

TestClass::TestClass(){
    cout<<"init TestClass"<<endl;

}


TestClass::~TestClass(){

}
 

void TestClass::update(){
    cout<<"TestClass is updating"<<endl;

    
}

void TestClass::draw(){
    cout<<"TestClass is drawing"<<endl;
}