#include <iostream>

#include "../Intcode.cpp"

int main() {

    string instructions;
    cin >> instructions;

    Intcode machines [50];
    deque<long> outputs[50];

    for (int i = 0; i < 50; i++) {
        machines[i].load_sequence(instructions);
        machines[i].receive(i);
        machines[i].next = &outputs[i];
    }

    long packet_destination, X, Y, first_packet = -1, last_NAT = -1, NAT_x = -1, NAT_y = -1;
    bool idle;

    while (1) {

        idle = true;

        for (int i = 0; i < 50; i++) {

            if (machines[i].halted_temporary()) {
                machines[i].receive(-1);
            } else {
                idle = false;
            }

            machines[i].execute();

            for (int j = 0; j < outputs[i].size(); j += 3) {

                packet_destination = outputs[i][j];
                X = outputs[i][j+1];
                Y = outputs[i][j+2];

                if (packet_destination == 255) {
                    if (first_packet == -1) {
                        first_packet = Y;
                    }

                    NAT_x = X;
                    NAT_y = Y;
                }

                if (packet_destination < 50) {
                    machines[packet_destination].receive(X);
                    machines[packet_destination].receive(Y);
                }
            }

            outputs[i].clear();
        }

        if (idle && NAT_x != -1 && NAT_y != -1) {
            if (last_NAT == NAT_y) {
                break;
            }

            machines[0].receive(NAT_x);
            machines[0].receive(NAT_y);

            last_NAT = NAT_y;
            NAT_x = -1;
            NAT_y = -1;
        }
    }

    /**************** Part One ****************/
    cout << first_packet << endl;

    /**************** Part Two ****************/
    cout << NAT_y << endl;

}