//
//  ControllerBase.cpp
//  ColorWindows
//
//  Created by Michael Flueckiger on 05.09.12.
//  Copyright (c) 2012 Ich. All rights reserved.
//

#include <iostream>
#include "ControllerBase.h"


ControllerBase::ControllerBase(){
	
}

ControllerBase::~ControllerBase(){
	
}

void ControllerBase::start(){
	isUpdating(true);
}

void ControllerBase::end(){
	isUpdating(false);
}