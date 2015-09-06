# boids
Craig Reynold's flocking behaviour, on C++ using OpenFrameworks.

I've only tested it on Linux 64 bits using OpenFrameworks 0.8.4, but there's no reason why it shouldn't work on other platforms. I'll be porting to 0.9 soon, and hopefully adding integration with ofxDatGui.

## Features
    * Multiple boid types, each with different behaviours and graphical properties
    * Multiple behaviours (separation, cohesion, alignment, etc.)
    * Both the boids and the behaviours are fully configurable, allowing for complex iteractions
    * Full XML load/save mechanism

Right now, the addition of a new Boid or Behaviour type is somewhat cumbersome (there's quite a few places where this change needs to be reflected). I'll be working on simplifying this.