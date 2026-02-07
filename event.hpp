#ifndef EVENT_HPP
#define EVENT_HPP

class event{
protected:
    bool persistent;
    char representation;
public:
    virtual int encounter() = 0;

    char map_representation();
};

#endif