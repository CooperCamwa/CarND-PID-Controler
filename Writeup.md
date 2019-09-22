Main porpuse of project: implementing PID controler for steering wheel angle to keep the vehicle in its track safe and as smooth as possibel. The track has some curvature.
Programing languege: c++

programing files can be found in "src" folder
Programing files are:
	- json.hpp (without any changes)
    - PID.cpp (and its header PID.h): to design a PID controler. These data are modified to meet the project requirements
    - main.cpp: to apply the desiged PID controler to the vehicle which drives in UDACITY Simulation environment. This file is modified to meet the project requirements.
    
Structure of PID.cpp
first all errors for proportional (err_p), derivative (err_d) and integral (err_i) parts of PID controller are initialized with 0.
during the simulation these errors are alway updated as follows:
	- err_p: is always equal to updated cross track error (cte)
    - err_d: is subtrachtion of err_p from cte
    - err_i: is the sum of last err_i and updated cte.
    

structure of main.cpp
first of all the accpetable range of steering wheel angel is defined.
The most costly part of project is to  find the proper coefficients for PID controler (cp, cd and ci). first I 've tried to find the PID coefficient with try and error. Here the following values:
cp = 0.05,cd = 5,ci = 0.002.
But the controller was not really good.

The next step was to apply a twiddle algorithm such as Sebastian explains in the course. This time the vehicle can move in the track without driving out from track. The drive is not really smooth, but it could stay in the track.

After updating the cross track error (cte) the needed current steering wheel angle will be calculated based on errors and PID-coefficient (cp, cd and ci).
Then the calculated steering wheel angle must be checkrd if it is allowd defined range.



