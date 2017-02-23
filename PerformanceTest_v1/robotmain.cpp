#include "robotmain.h"

RobotMain::RobotMain()
{
    setup();
}

void RobotMain::setup()
{
    right_motor = new FEHMotor(FEHMotor::Motor1,12.0);
    left_motor = new FEHMotor(FEHMotor::Motor0,12.0);
    cds_cell = new AnalogInputPin(FEHIO::P0_0);
    bump_back_right = new DigitalInputPin(FEHIO::P1_0);
    bump_back_left = new DigitalInputPin(FEHIO::P1_1);
    bump_front_right = new DigitalInputPin(FEHIO::P3_0);
    bump_front_left = new DigitalInputPin(FEHIO::P1_3);
    left_encoder = new DigitalEncoder(FEHIO::P0_2);
    right_encoder = new DigitalEncoder(FEHIO::P0_3);
}

void RobotMain::drive(int rightMotor, int leftMotor)
{
    right_motor->SetPercent(rightMotor);
    left_motor->SetPercent(leftMotor);
}

void RobotMain::driveStop()
{
    left_motor->SetPercent(0);
    right_motor->SetPercent(0);
}

void RobotMain::driveForward(int power, double inches)
{
    int countsNeeded = distanceConvStraight(inches);
    right_encoder->ResetCounts();
    left_encoder->ResetCounts();
    drive(power, power);
    double averageCounts = average(right_encoder->Counts(), left_encoder->Counts());
    while(averageCounts < countsNeeded && !(/*bump_front_left &&*/ bump_front_right))
    {
        averageCounts = average(right_encoder->Counts(), left_encoder->Counts());
    }
    driveStop();
}

void RobotMain::driveBackward(int power, double inches)
{
    int countsNeeded = distanceConvStraight(inches);
    right_encoder->ResetCounts();
    left_encoder->ResetCounts();
    drive(-power, -power);
    double averageCounts = average(right_encoder->Counts(), left_encoder->Counts());
    while(averageCounts < countsNeeded && !(bump_back_left && bump_back_right))
    {
        averageCounts = average(right_encoder->Counts(), left_encoder->Counts());
    }
    driveStop();

}

void RobotMain::turnLeft(int power, double angle)
{
    int countsNeeded = distanceConvArc(angle);
    right_encoder->ResetCounts();
    left_encoder->ResetCounts();
    drive(-power, power);
    double averageCounts = average(right_encoder->Counts(), left_encoder->Counts());
    while(averageCounts < countsNeeded)
    {
        averageCounts = average(right_encoder->Counts(), left_encoder->Counts());
    }
    driveStop();
}

void RobotMain::turnRight(int power, double angle)
{
    int countsNeeded = distanceConvArc(angle);
    right_encoder->ResetCounts();
    left_encoder->ResetCounts();
    drive(power, -power);
    double averageCounts = average(right_encoder->Counts(), left_encoder->Counts());
    while(averageCounts < countsNeeded)
    {
        averageCounts = average(right_encoder->Counts(), left_encoder->Counts());
    }
    driveStop();
}


int RobotMain::distanceConvStraight(double inches)
{
    double encCounts = inches * average(INCH_TO_COUNTS_RIGHT, INCH_TO_COUNTS_LEFT);
    return encCounts;
}


int RobotMain::distanceConvArc(double angle)
{
    double inches = (angle/360.0) * (2 * 3.14159265359 * RADIUS);
    double encCounts = distanceConvStraight(inches);
    return encCounts;
}

double RobotMain::average(double num1, double num2)
{
    double total = num1 + num2;
    double average = total/2.0;
    return average;
}

void RobotMain::waitForRedDetected(double timeoutSec)
{
    double waitUntil = TimeNow() + timeoutSec;
    while(cds_cell->Value() < RED_DETECT_THRES && TimeNow() < waitUntil);
}

bool RobotMain::redDetect()
{
    bool detected = cds_cell->Value() > RED_DETECT_THRES;
    return detected;
}
