The purpose of the simulator is to set the standard for the CPU's behaviour. It abstracts away the CPU internals for the most part into a black-box, and simulates what the final behaviour of the CPU should be, without worrying about the internals or implementation. I.e. it is a functional simulator. So, the simulator can be defined with the following parameters:

Components:
- 64 kB ROM (instructions)
- 4 GB RAM (data)
- 32 general purpose registers: x0 to x31:
	- x0 wired to 0
- pc (program counter)

The state of the CPU/simulator at any given time is the state of the above components.
For the simulator design, I will be following the Google C++ Style Guide with a few modifications. While I would like to use something like Doxygen for commenting and formatting, this project is small enough that doing so wouldn't make sense.