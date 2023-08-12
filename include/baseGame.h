#pragma once

class BaseGame
{
public:

    virtual const bool quit(); // Called every frame to determine if the game should quit
    virtual void iteration(); // Called once every frame
    virtual void destroy(); // Called after the game ends

    void start();
};