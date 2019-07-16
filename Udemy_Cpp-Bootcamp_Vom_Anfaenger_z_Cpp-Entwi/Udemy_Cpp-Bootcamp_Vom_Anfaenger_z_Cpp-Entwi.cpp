﻿#include <cstdlib> 
#include <ctime> 
#include <iostream>
#include <cstdlib>

using namespace std;






void mySpeed(int& actualSpeed, int  distanceDriven, int driveLength)
{
	string eingabe;

	cout << "GESCHWINDIGKEIT:     " << actualSpeed << "       Strecke gefahren: " << distanceDriven << endl;
	cout << "\n waehlen sie + oder - zum be- oder entschleunigen oder 0\n";// als info() auslagern

	cin >> eingabe;
	if (eingabe == "+")
	{
		actualSpeed += 10;
	}
	else if (eingabe == "-" && actualSpeed >= 10)
	{
		actualSpeed -= 10;
	}
	else if (eingabe == "0")
	{
	}
	else
	{
		cout << "\nFEHLERHAFTE EINGABE!\n";
		mySpeed(actualSpeed, distanceDriven, driveLength);
	}
}

void streckenCalc(int actualSpeed, int& distance)
{
	distance += actualSpeed;
}


void nextSignAhead(int distanceDriven, int* speedZone, int& i, int& k)
{
	if (distanceDriven >= k + 100)
	{
		i++;
		k += 300;
	}
	cout << "Die aktuelle Zone ist: " << speedZone[i];

	if (k < distanceDriven && distanceDriven < k + 100)
		cout << " und das naechste Schild bei " << k + 100 << " zeigt " << speedZone[i + 1] << " an.";

	cout << endl;
}
int strafzahlungen(int actualSpeed, int speedZone[], int i)
{
	if (actualSpeed > speedZone[i])
	{
		cout << "\nZU SCHNELL! " << (actualSpeed - speedZone[i]) * 3 << " als Strafe hinzugefuegt!\n";
		return ((actualSpeed - speedZone[i])*3);
	}
	else
	{
		cout << endl;
		return (0);
	}

}

void clearScreen(int anzahl)
{
	int t;
	for (t = 0; t < anzahl; t++)	//derzeit 25 ohne ^= 1 screen 
		cout << endl;
}



int myRandom(int i, int maxValue)
{
	i = 5;
	int ende = time(NULL);
	int j;
	i = 0;
	for (int j = 0; j < ende % 255; j++)
		i = (rand() % maxValue);

	return i;
}

void randomiseSpeedZone(int* speedZone, int& i)
{

	int possibleSpeedZones[] = { 10,30,50,80,100 };

	for (int j = 0; j < 16; j++)
	{
		i = myRandom(0, 5);
		speedZone[j] = possibleSpeedZones[i];
	}

}
void driving(int& actualSpeed, int* speedZone, int& distanceDriven, int driveLength,  int& clicks, int& k, int& strafe)
{
	int i = 0;

	while (distanceDriven < driveLength)
	{
																//gibt derzeitiges und etwaig next schild aus; i++
		nextSignAhead(distanceDriven, speedZone, i, k);			//def bei Distanz Anzeigeschild festzusetzten
		mySpeed(actualSpeed, distanceDriven, driveLength);
		
		streckenCalc(actualSpeed, distanceDriven);
		clearScreen(24);
		strafe+=strafzahlungen(actualSpeed, speedZone, i);
		++clicks;
	}
	
		cout << "\nSie sind in " << clicks << " Zeiteinheiten angekommen und haben eine Strafe von "
			<< strafe << " gesammelt!" ;
	
}

int main()
{
	int  i = 0, actualSpeed = 0, clicks = 0, distanceDriven = 0, driveLength = 1000, speedSign = 0, k = 100, strafe = 0;
	
	int speedZone[16];
	randomiseSpeedZone(speedZone, i);		//fill 16 slot array with random speedzones
	

	/*for (int j = 0; j < 16; j++)
		cout << speedZone[j] << endl;*/
	
	clearScreen(25);
	driving(actualSpeed, speedZone, distanceDriven, driveLength, clicks, k, strafe);

	
	return 1;
	
}