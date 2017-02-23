#include <robotmain.h>
//Changed "" to <>

int main(void)
{
    int lowPow = 15;
    int highPow = 30;
    RobotMain robot;
    robot.waitForRedDetected(10);
    robot.driveForward(lowPow,9);
    robot.turnLeft(lowPow, 90.);
    robot.driveForward(lowPow, 13);
    robot.turnLeft(lowPow,90.);
    robot.driveForward(lowPow, 3);
    robot.driveForward(highPow, 14);
    robot.turnRight(lowPow, 90.);
    robot.driveForward(lowPow, 30);
    robot.turnLeft(lowPow, 90.);
    robot.driveForward(lowPow, 30);
    robot.driveStop();

}
