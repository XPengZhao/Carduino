/************************************************************************************************************
 * DistanceSRF04.h - Arduino library for retrieving data from the SFR04 Distance sensor                     *
 * Copyright 2011 Jeroen Doggen (jeroendoggen@gmail.com)                                                    *
 * For more information: variable declaration, changelog,... see DistanceSRF04.h                            *
 ************************************************************************************************************
 * This library is free software; you can redistribute it and/or                                            *
 * modify it under the terms of the GNU Lesser General Public                                               *
 * License as published by the Free Software Foundation; either                                             *
 * version 2.1 of the License, or (at your option) any later version.                                       *
 *                                                                                                          *
 * This library is distributed in the hope that it will be useful,                                          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of                                           *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                                        *
 * Lesser General Public License for more details.                                                          *
 *                                                                                                          *
 * You should have received a copy of the GNU Lesser General Public                                         *
 * License along with this library; if not, write to the Free Software                                      *
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA                               *
 ***********************************************************************************************************/

/// <summary>
/// DistanceSRF04.cpp - Library for retrieving data from the GP2Y0A21YK IR Distance sensor.
/// For more information: variable declaration, changelog,... see DistanceSRF04.h
/// </summary>

#include <Arduino.h>
#include <DistanceSRF04.h>

/// <summary>
/// Constructor
/// </summary>
DistanceSRF04::DistanceSRF04()
{
}

/// <summary>
/// Begin function to set default pins
/// </summary>
void DistanceSRF04::begin()
{
	begin (2,3);
}

/// <summary>
/// Begin variables
/// - int trigPin: pin used to activate the sensor
/// - int echoPin: pin used to read the reflection
/// </summary>
void DistanceSRF04::begin(int echoPin, int trigPin)
{
	_trigPin=trigPin;
	_echoPin=echoPin;
	pinMode(_trigPin, OUTPUT);
	pinMode(_echoPin, INPUT);
	setAveraging(1);		      //1: all samples passed to higher level
}

/// <summary>
/// setAveraging(int avg): Sets how many samples have to be averaged in getDistanceCentimeter, default value is 100.
/// </summary>
void DistanceSRF04::setAveraging(int avg)
{
	_average=avg;
}

/// <summary>
/// getDistanceTime(): Returns the time between transmission and echo receive
/// </summary>
int DistanceSRF04::getDistanceTime()
{
	long sum = 0;
	
	for (int i=0;i<_average;i++)
	{
		digitalWrite(_trigPin, LOW);
		delayMicroseconds(2);
		digitalWrite(_trigPin, HIGH);
		delayMicroseconds(10);
		digitalWrite(_trigPin, LOW);
		_duration = pulseIn(_echoPin, HIGH);
		sum=sum+_duration;
	}
	return(int(sum/_average));
}

/// <summary>
/// getDistanceCentimeter(): Returns the distance in centimeters
/// </summary>
int DistanceSRF04::getDistanceCentimeter()
{
	return (getDistanceTime()/29/2);
}

/// <summary>
/// getDistanceInch(): Returns the distance in inches
/// </summary>
int DistanceSRF04::getDistanceInch()
{
	return (getDistanceTime()/74/2);
}

/// <summary>
/// isCloser: check whether the distance to the detected object is smaller than a given threshold
/// </summary>
boolean DistanceSRF04::isCloser(int threshold)
{
	if (threshold>getDistanceCentimeter())
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

/// <summary>
/// isFarther: check whether the distance to the detected object is smaller than a given threshold
/// </summary>
boolean DistanceSRF04::isFarther(int threshold)
{
	if (threshold<getDistanceCentimeter())
	{
		return true;
	}
	else
	{
		return false;
	}
}


