#include <iostream>
#include <stdio.h>

const int weight1 = 1;
const int weight2 = 2;
const int weight3 = 3;


void processVariables(int v1, int v2, int v3, int v4, int v5, int v6);
void generateData(int interval);


float calcError(int sensors[], int sensorSize);

int main(int argc, char** argv) {
	
	printf("Aritficial!\n");
	generateData(100);
	
	printf("\n\nSimulated!\n");
	processVariables(900, 600, 20, 20, 600, 900); 	//__i__
	processVariables(600, 200, 20, 200, 600, 900); 	//_i___
	processVariables(600, 20, 20, 600, 900, 900); 	//_i___
	processVariables(20, 20, 600, 900, 900, 900); 	//i____
	processVariables(20, 600, 900, 900, 900, 900); 	//i____
	processVariables(900, 600, 20, 20, 600, 900); 	//__i__
	processVariables(900, 900, 400, 20, 20, 600); 	//___i_
	processVariables(900, 900, 900, 400, 20, 20); 	//____i
	processVariables(900, 900, 900, 900, 600, 20); 	//____i
		
	system("pause");
	return 0;	

}



void generateData(int interval) {
	
	for(int i = 0; i < 10; i++) {
		for(int j = 1023; j > 0; j -= interval) {
			switch(i) {
				case 0:
					processVariables(1024, 1024, j, 1024, 1024, 1024);
					break;
				case 1:
					processVariables(1024, j, j, 1024, 1024, 1024);
					break;
				case 2:
					processVariables(1024, j, 1024, 1024, 1024, 1024);
					break;
				case 3:
					processVariables(j, j, 1024, 1024, 1024, 1024);
					break;
				case 4:
					processVariables(j, 1024, 1024, 1024, 1024, 1024);
					break;
				case 5:
					processVariables(1024, 1024, 1024, j, 1024, 1024);
					break;
				case 6:
					processVariables(1024, 1024, 1024, j, j, 1024);
					break;
				case 7:
					processVariables(1024, 1024, 1024, 1024, j, 1024);
					break;
				case 8:
					processVariables(1024, 1024, 1024, 1024, j, j);
					break;
				case 9:
					processVariables(1024, 1024, 1024, 1024, 1024, j);
					break;
				default:
					processVariables(1024, 1024, 1024, 1024, 1024, 1024);
					break;
			}
		}
	}
	
}




void processVariables(int v1, int v2, int v3, int v4, int v5, int v6) {
	int data[6] = {v1, v2, v3, v4, v5, v6};
	printf("To: (%4d, %4d, %4d, %4d, %4d, %4d): \tError = %f\n", data[0], data[1], data[2], data[3], data[4], data[5], calcError(data, 5));
}

float calcError(int sensors[], int sensorSize) {
	
	float leftHandAux[3] = { 
		-sensors[0] * weight3, 
		-sensors[1] * weight2, 
		-sensors[2] * weight1 
	};
	float rightHandAux[3] = { 
		sensors[5] * weight3, 
		sensors[4] * weight2, 
		sensors[3] * weight1 
	};
	
	float leftIntersection[sensorSize] = { 
		leftHandAux[2],
		(leftHandAux[2] + leftHandAux[1]) / 2,
		leftHandAux[1],
		(leftHandAux[1] + leftHandAux[0]) / 2,
		leftHandAux[0]
	};
	
	float rightIntersection[sensorSize] = { 
		rightHandAux[2],
		(rightHandAux[2] + rightHandAux[1]) / 2,
		rightHandAux[1],
		(rightHandAux[1] + rightHandAux[0]) / 2,
		rightHandAux[0]
	};
	
	int lessLeft = 1, lessRight = 1, lessLeftIdx = 0, lessRightIdx = 0, lessLeftAux = -9999999, lessRightAux = 9999999;
	float leftLessSum = 0, leftMajorSum = 0, rightLessSum = 0, rightMajorSum = 0;
	
	for(int i = 0; i < sensorSize; i++) {		
		if(leftIntersection[i] > lessLeftAux) {
			lessLeftAux = leftIntersection[i];
			lessLeftIdx = i;
		}
	}
	for(int i = 0; i <= lessLeftIdx; i++) leftLessSum += leftIntersection[i];
	for(int i = lessLeftIdx; i < sensorSize; i++) leftMajorSum += leftIntersection[i];
	
	
	for(int i = 0; i < sensorSize; i++) {
		if(rightIntersection[i] < lessRightAux) {
			lessRightAux = rightIntersection[i];
			lessRightIdx = i;
		}
	}
	for(int i = 0; i <= lessRightIdx; i++) rightLessSum += rightIntersection[i];
	for(int i = lessRightIdx; i < sensorSize; i++) rightMajorSum += rightIntersection[i];
	
	float calcLeftSomatory = leftLessSum - leftMajorSum;
	float calcRightSomatory = rightLessSum - rightMajorSum;
	
	return ((calcLeftSomatory + calcRightSomatory) * 100) / 14849.5;
}




