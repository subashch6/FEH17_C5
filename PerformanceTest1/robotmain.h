#ifndef ROBOTMAIN_H
#define ROBOTMAIN_H

#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>



class RobotMain
{
public:
    RobotMain();
    void driveForward(int power, double inches);
    void driveBackward(int power, double inches);
    void driveStop();
    void turnLeft(int power, double angle);
    void turnRight(int power, double angle);

    //wait until red detected with CDS Cell
    void waitForRedDetected(double timeoutSec);

    //red detected or not
    bool redDetected();
private:
    void drive(int left_motor, int right_motor);

    //Setup inputs
    void setup();

    //radius from pivot point to wheel
    static const float RADIUS = 3.50;
    static const float INCH_TO_COUNTS_RIGHT = 20;
    static const float INCH_TO_COUNTS_LEFT = 20;
    static const float RED_DETECT_THRES = 1.20;

    //Motor Variable
    FEHMotor *right_motor;
    FEHMotor *left_motor;

    //Encoder variables
    DigitalEncoder *left_encoder;
    DigitalEncoder *right_encoder;
    
    //CDS Variable
    AnalogInputPin *cds_cell;

    //Bump switch variables
    DigitalInputPin *bump_back_right;
    DigitalInputPin *bump_back_left;
    DigitalInputPin *bump_front_right;
    DigitalInputPin *bump_front_left;


    //Calculate distance
    int distanceConvStraight(double inches);
    int distanceConvArc(double angle);

    //Average Calculation
    double average(double num1, double num2);

    //Switch Pressed
    bool switchActive(DigitalInputPin * inputPin);


};

#endif // ROBOTMAIN_H
