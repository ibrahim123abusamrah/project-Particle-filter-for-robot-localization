# project-Particle-filter-for-robot-localization
AI project: Particle filter for robot localization  

A robot is located on a long corridor and moving along it. It uses a heat sensor that measures the  temperate of its position. This temperature depends on the heat radiators on the wall. 
A robot is located on a long corridor and moving along it. It uses a heat sensor that measures the  temperate of its position. This temperature depends on the heat radiators on the wall. The following  figure shows an example of temperature readings around the corridor, the two radiates (in red)  participate in the change of temperature reading (in blue). The robot and its direction are shown in  black. Few particles are shown in green. 
Use the idea of particle filter to perform robot localization in 1-d space. 
To generate the same temperature reading as in the curve, use: 
y=cosθ+1/2*cos(3*θ+0.23) +1/2*cos(5*θ−0.4)+1/2*cos(7*θ+2.09)+1/2*cos(9*θ−3) change θ between 0 and 1 with 0.001 increment each time. 
You should submit C++ code that prints the position of each particle at each time. Hints: 
• Z=y +- small random error 
• StartX=? Constant in your program 
• Stepsize>1 
• No change in direction 
• To calculate W, use Gaussian function

