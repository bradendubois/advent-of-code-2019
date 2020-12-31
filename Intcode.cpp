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

        // Save a value given a register and mode
        void set_register(long address, int mode, long value);

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

void Intcode::load_sequence(string instructions) {

    stringstream convert(instructions);
    vector<long> seq;

    long r = 0;
    while (convert.good()) {
        string ins;
        getline(convert, ins, ',');
        stringstream code(ins);
        long x;
        code >> x;
        memory[r] = x;
        r++;
    }

    ins_ptr = 0;
    rel_ptr = 0;
    in.clear();
}

void Intcode::load_instruction() {
    int code = memory[ins_ptr];
    operation = code % 100;
    code /= 100;

    p1 = code % 10;
    code /= 10;
    p2 = code % 10;
    code /= 10;
    p3 = code;

    r1 = memory[ins_ptr+1];
    r2 = memory[ins_ptr+2];
    r3 = memory[ins_ptr+3];
}

long Intcode::load_register(long r, int mode) {
    if (mode == 0) {
        return memory[r];
    } else if (mode == 1) {
        return r;
    } else if (mode == 2) {
        return memory[rel_ptr+r];
    } else {
        cout << "REGISTER DECODE ERROR" << endl;
        return 0;
    }
}

void Intcode::set_register(long address, int mode, long value) {
    if (mode == 0) {
        memory[address] = value;
    } else if (mode == 2) {
        memory[rel_ptr+address] = value;
    } else {
        cout << "REGISTER STORE ERROR" << endl;
    }
}

void Intcode::execute() {
    
    check_incoming();

    while (!(halted_temporary() || halted_terminal())) {

        /*
        for (int i = 0; i < memory.size(); i++) {
            cout << memory[i] << " ";
        } cout << endl;
        */
       
        load_instruction();

        switch (operation) {
            case (1):   // Add
                add();
                break;
            case (2):   // Multiply
                mul();
                break;
            case (3):   // Set a register
                set();
                break;
            case (4):   // Output a register value
                out();
                break;
            case (5):   // Branch to r2 if r1 > 0
                bgz();
                break;
            case (6):   // Branch to r2 if r1 == 0
                bez();
                break;
            case (7):   // Set r3 to r1<r2
                slt();
                break;
            case (8):   // Set r3 to r1==r2
                seq();
                break;
            case (9):   // Set the relative base
                srl();
                break;
            case (99):  // Terminate
                exit();
                break;
            default:
                cout << "READ ERROR: Instruction and Pointer, " << memory[ins_ptr] << ", " << ins_ptr << endl;
                break;
        };
    }
}

void Intcode::receive(long immediate) {
    in.push_back(immediate);
}
    
bool Intcode::halted_temporary() {
    return waiting;
}

bool Intcode::halted_terminal() {
    return halted;
} 

void Intcode::add() {
    set_register(r3, p3, load_register(r1, p1) + load_register(r2, p2));
    ins_ptr += 4;
}

void Intcode::mul() {
    set_register(r3, p3, load_register(r1, p1) * load_register(r2, p2));
    ins_ptr += 4;
}

void Intcode::set() {
    if (in.size() == 0) {
        waiting = true;
        return;
    }

    set_register(r1, p1, get_next());
    ins_ptr += 2;
}

void Intcode::out() {
    if (next == nullptr) {
        cout << load_register(r1, p1) << endl;
        ins_ptr += 2;
        return;
    }

    (*next).push_back(load_register(r1, p1));
    ins_ptr += 2;
}

void Intcode::bgz() {
    ins_ptr = (load_register(r1, p1) > 0 ? load_register(r2, p2) : ins_ptr+3);
}

void Intcode::bez() {
    ins_ptr = (load_register(r1, p1) == 0 ? load_register(r2, p2) : ins_ptr+3);
}

void Intcode::slt() {
    set_register(r3, p3, (load_register(r1, p1) < load_register(r2, p2) ? 1 : 0));
    ins_ptr += 4;
}

void Intcode::seq() {
    set_register(r3, p3, (load_register(r1, p1) == load_register(r2, p2) ? 1 : 0));
    ins_ptr += 4;
}

void Intcode::exit() {
    halted = true;
}

void Intcode::srl() {
    rel_ptr += load_register(r1, p1);
    ins_ptr += 2;
}

long Intcode::get_next() {
    if (in.size() == 0) 
        return -1;
    long n = in.front();
    reverse(in.begin(), in.end());
    in.pop_back();
    reverse(in.begin(), in.end());
    return n;
}

void Intcode::check_incoming() {
    if (in.size() > 0) waiting = false;
}

void Intcode::set(long address, long immediate) {
    memory[address] = immediate;
}

long Intcode::load(long address) {
    return memory[address];
}