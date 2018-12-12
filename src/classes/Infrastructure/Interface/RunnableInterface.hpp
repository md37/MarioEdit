#pragma once

class RunnableInterface {

public:

    virtual void start()=0;
    virtual bool isStarted() const=0;

};