#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

class Intcode {

    public:

        // Load a set of instructions into the machine
        void load_sequence(string instruction_sequence);

        void execute();  // Begin instruction execution
        void receive(long immediate);   // Queue a number into the input vector

        bool halted_temporary();  // Check if waiting on a value
        bool halted_terminal();   // Check if halted

        // Store a value at a specific address in memory
        void set(long address, long immediate);
        
        // Load a specific address from memory
        long load(long address);

        // A queue of values to be processed by code (3) instructions
        vector<long> in;

        // Used to chain together multiple Intcode machines
        vector<long> * next = nullptr;

    private:

        map<long, long> memory; // Intcode memory
        map<long, long> backup; // Backup memory to reset
        
        long ins_ptr;   // Instruction pointer
        long rel_ptr;   // Relative pointer

        bool waiting = false;   // Not done, waiting on prior Intcode to send
        bool halted = false;    // Instruction set completed - halted

        // The next opcode of the next operation
        int operation;

        // Registers
        long r1, r2, r3;

        // Respective register modes
        //  0 = address, 1 = immediate, 2 = relative
        long p1, p2, p3;

        // Load the next instruction from memory (as denoted by ins_ptr)
        //  Initializes all registers and modes
        void load_instruction();

        // Get the value denoted by a register and mode
        long load_register(long r, int mode);

        // ***** Instructions *****
        void add(); // 1 - Add
        void mul(); // 2 - Multiply
        void set(); // 3 - Set a register
        void out(); // 4 - Output a register value
        void bgz(); // 5 - Branch to r2 if r1 > 0
        void bez(); // 6 - Branch to r2 if r1 == 0
        void slt(); // 7 - Set r3 to r1<r2
        void seq(); // 8 - Set r3 to r1==r2
        void srl(); // 9 - Set the relative instruction pointer

        void exit(); // 99 - Terminate

        // Get the next inputted value from the input vector
        long get_next();

        // Check if any inputted values are in the queue
        void check_incoming();
};
