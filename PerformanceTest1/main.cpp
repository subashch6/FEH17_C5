#include "robotmain.h"


int main(void)
{
    int lowPow = 15;
    int highPow = 40;
    RobotMain robot;
    robot.waitForRedDetected(10);

    robot.driveForward(lowPow,10);
    LCD.WriteLine("0");
    robot.turnLeft(lowPow, 90.);
    LCD.WriteLine("1");
    robot.driveForward(lowPow, 13);
    LCD.WriteLine("2");
    robot.turnLeft(lowPow,90.);
    LCD.WriteLine("3");
    //robot.driveForward(lowPow, 1);
    LCD.WriteLine("4");
    robot.driveForward(highPow, 24);
    LCD.WriteLine("5");
    Sleep(.5);
    robot.turnRight(lowPow, 90.);
    LCD.WriteLine("6");
    robot.driveForward(lowPow, 8);
    LCD.WriteLine("7");
    robot.turnLeft(lowPow, 90.);
    LCD.WriteLine("8");
    robot.driveForward(lowPow, 20);
    Sleep(5);
    LCD.WriteLine("9");
    robot.driveStop();
    LCD.WriteLine("10");
    robot.driveBackward(lowPow,15);
    robot.turnLeft(lowPow, 90);
    robot.driveForward(lowPow, 15);

}
