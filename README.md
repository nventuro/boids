# boids
[Craig Reynold's flocking behaviour](http://www.red3d.com/cwr/boids/), on C++ using [OpenFrameworks](http://openframeworks.cc).

I've only tested it on Linux 64 bits using OpenFrameworks 0.9, which uses C++11, but there's no reason why it shouldn't work on other platforms. I'll hopefully adding integration with [ofxDatGui](https://github.com/braitsch/ofxDatGui) soon.

## Features
 - Multiple boid types, each with different behaviours and graphical properties
 - Multiple behaviours (separation, cohesion, alignment, etc.)
 - Both the boids and the behaviours are fully configurable, allowing for complex iteractions
 - Full XML load/save mechanism

Right now, the addition of a new Boid or Behaviour type is somewhat cumbersome (there's quite a few places where this change needs to be reflected). I'll be working on simplifying this.
