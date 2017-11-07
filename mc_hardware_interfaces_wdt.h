#pragma once

class wdt_base {
public:
    virtual void init ( void ) const = 0;
    virtual void reset ( void ) const = 0;
    virtual void reset_service ( void ) const = 0;
};
