/*
 *  MaxiFactory.h
 *  Maximus
 *
 *  Created by User on 6/6/11.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#ifndef __MAXIFACTORY_H__
#define __MAXIFACTORY_H__


namespace Maximus
{

class cMRender;
    
class cMaxiFactory
{
private:
	//--------------------------------------------------------------------------
	/// @brief Constructor
	//--------------------------------------------------------------------------
    cMaxiFactory();
    
    
    //--------------------------------------------------------------------------
    /// @brief Destructor
    //--------------------------------------------------------------------------
    ~cMaxiFactory();
    
	//--------------------------------------------------------------------------
	/// @brief Copy constructor
	//--------------------------------------------------------------------------
    cMaxiFactory(const cMaxiFactory& rhs);
    
	//--------------------------------------------------------------------------
	/// @brief Copy assignment operator
	//--------------------------------------------------------------------------
    cMaxiFactory& operator = (const cMaxiFactory& rhs);
	
public:
	static cMaxiFactory& instance()
	{
		static cMaxiFactory fact;
		
		return fact; 
	}
	
    cMRender* createRenderer();

};
    
}

#endif
