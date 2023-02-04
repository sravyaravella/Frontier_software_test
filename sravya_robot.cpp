#include <iostream>
#include <string>
#include <regex>
using namespace std;
const int max_width=5,max_length=5;
//Maximum width and Maximum length of the table  top.Modify this to increase the size of the grid
class Robot {
public:
    int x, y;
    string facing;
    bool movement;

    Robot() { //Robot is intitially placed at 0,0 location facing North. 
        x = 0;
        y = 0;
        facing = "NORTH";
        movement = false;
    }

    void place(int x, int y, string facing) {
    	//Before placing the robot, checking if the given input values are valid and that are not outside the boundary of the grid 
        if (x >= 0 && x < max_width && y >= 0 && y < max_length && 
        	(facing == "NORTH" || facing == "SOUTH" || facing == "EAST" || facing == "WEST")) { //checking if the given facing is appropriate.
            this->x = x;
            this->y = y;
            this->facing = facing;
            this->movement = false;
            cout<<"Placed Robot at give location:"<<x<<","<<y<<","<<facing<<endl;
        }
        else cout<<"Invalid Input, Please provide valid instruction!"<< endl;
        return;
    }

    void move() { //Moves the robot 1 step forward in the direction it is facing
        if (movement) return;
        else if (facing == "NORTH" && y+1 < max_length) { //Moving the robot forward of it is not placed at the top end  of table top.
        	y++;
        	cout<<"Moved robot one step towards NORTH"<<endl;
        }
        else if (facing == "SOUTH" && y-1 >= 0) { //Moving the robot downward of it is not placed at the bottom end  of table top.
        	y--;
        	cout<<"Moved robot one step towards SOUTH"<<endl;
        }
        else if (facing == "EAST" && x+1 < max_width){ //Moving the robot towards right of it is not placed at the rightmost-end   of table top.
        	x++;
        	cout<<"Moved robot one step towards EAST"<<endl;
        }
        else if (facing == "WEST" && x-1 >= 0) { //Moving the robot towards left if it is not placed at the lefttmost-end   of table top
        	x--;
        	cout<<"Moved robot one step towards WEST"<<endl;
        }
        else cout<<"Cannot move robot forward, Please change direction of the robot!!" << endl;
        return;
    }

    void left() {
        if (facing == "NORTH"){ // 90° anticlockwise direction of NORTH is WEST
        	facing = "WEST";
        	cout<<"Robot turned left, It is now facing WEST"<<endl;
        }	
        
        else if (facing == "SOUTH") { // 90° anticlockwise direction of SOUTH is EAST
        	facing = "EAST";
        	cout<<"Robot turned left, It is now facing EAST"<<endl;
        }
        else if (facing == "EAST") { // 90° anticlockwise direction of EAST is NORTH
        	facing = "NORTH";
        	cout<<"Robot turned left, It is now facing NORTH"<<endl;
        }
        else { // 90° anticlockwise direction of WEST is SOUTH
        	facing = "SOUTH";
        	cout<<"Robot turned left, It is now facing SOUTH"<<endl;
        }
        return;
    }

    void right() {
        if (facing == "NORTH"){ // 90° clockwise direction of NORTH is EAST
        	facing = "EAST";
        	cout<<"Robot turned right, It is now facing EAST"<<endl;
        }	
        
        else if (facing == "SOUTH") { // 90° clockwise direction of SOUTH is WEST
        	facing = "WEST";
        	cout<<"Robot turned right, It is now facing WEST"<<endl;
        }
        else if (facing == "EAST") { // 90° clockwise direction of EAST is SOUTH
        	facing = "SOUTH";
        	cout<<"Robot turned right, It is now facing SOUTH"<<endl;
        }
        else { // 90° clockwise direction of WEST is NORTH
        	facing = "NORTH";
        	cout<<"Robot turned right, It is now facing NORTH"<<endl;
        }
        return;
    }

    void report() { //Outputs the location of Robot.
        cout << "Robot is at location:" << x << "," << y << "," << facing << endl;
        printGrid(); 
        return;
    }
	void printGrid(){ //Representation of the Grid of size (max_width * max_height)
		for(int j = 0; j < max_width; j++) cout<<" ---";
		cout<<endl;
    	for(int i = 0; i < max_length; i++){
        	for(int j = 0; j <max_width; j++){
            	if(j == 0) cout<<"|";
            	if(j == x && i == max_length-y-1) cout << " * |"; // * represents the placement of robot.
             	else cout<<"   |";
        	}
        	cout<<max_length-i-1<<endl;
        	for(int j = 0; j < max_width; j++) cout<<" ---";
        cout<<endl;
		}
		for(int j = 0; j < max_width; j++) cout<<"  "<<j<<" ";
		cout<<endl;
	}
};

int main() {
    cout << "Enter your input for the Robot. Type 'exit' to stop the program:" << endl;
    string input; //Case-insensitive input
    Robot rb;
    while (cin >> input && input != "exit") {
        int l = input.size();
        for (int i = 0; i < l; i++) input[i] = toupper(input[i]); //Converting the given input to Uppercase
        if (input.find("MOVE") != string::npos) rb.move(); //input accepts move and move(), checking if the given instruction is to move the robot and calling the move() funtcion.
        else if (input.find("LEFT") != string::npos) rb.left();//input accepts left and left(), checking if the given instruction is to turn left  and calling the left() funtcion.
        else if (input.find("RIGHT") != string::npos) rb.right();//input accepts right and right(), checking if the given instruction is to right and calling the right() funtcion.
        else if (input.find("REPORT") != string::npos) rb.report();//input accepts report and report(), checking if the given instruction is to report the location and calling report().
        else if (input.find("PLACE") != string::npos) { //if the input is to place the robot at given location
           /* int width = input[6] - 48;
            int length = input[8] - 48;
            string dir = input.substr(11, 5);*/
			regex pattern("PLACE\\((\\d)\\s?,\\s?(\\d)\\s?,\\s?'?([A-Z]+)'?\\)"); //using regex for pattern matching (place(1,2,'south'),  matches[0] contains PLACE
			smatch matches;
			if (regex_search(input, matches, pattern) && matches.size() >= 4) {
    			int width = stoi(matches[1].str());  //matches[1] & matches[2] contains width & height respectively>>matching pattern: \d
    			int length = stoi(matches[2].str());
    			string dir = matches[3].str(); //matches[3] contains given direction >>matching pattern : '?([A-Z]+)'
            	rb.place(width, length, dir);
			}
			else cout << "Invalid Input:" << input << " Please enter valid input!" << endl;
        }
        else cout << "Invalid Input:" << input << " Please enter valid input!" << endl;
    }
    return 0;
}

