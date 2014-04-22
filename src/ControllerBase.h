//
//  ControllerBase.h
//  ColorWindows
//
//  Created by Michael Flueckiger on 05.09.12.
//  Copyright (c) 2012 Ich. All rights reserved.
//

#ifndef ColorWindows_ControllerBase_h
#define ColorWindows_ControllerBase_h



#endif

class ControllerBase{
public:
	ControllerBase();
	virtual ~ControllerBase();
	
	// nicht gebraucht, da nix zu zeichnen für Controller
	void _draw(){};
	
	virtual void start();	
	virtual void end();
	
private:
	
	
};