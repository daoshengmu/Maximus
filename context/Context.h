/*
 *  Context.h
 *  Maximus
 *
 *  Created by User on 6/6/11.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#ifndef __CONTEXT_H__
#define __CONTEXT_H__


namespace Maximus
{
    
class Context
{
public:
    virtual ~Context() {};
    virtual bool Init() = 0;
    virtual void Terminate() = 0;
    virtual void* GetContext() = 0;
};

}

#endif /* __CONTEXT_H__ */